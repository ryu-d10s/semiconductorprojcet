#include "platform.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "xaxidma.h"
#include "xil_cache.h"
#include "xsnn_ip.h"   // HLS SNN IP 드라이버 헤더 (IP 이름에 맞게)

// ==========================================
// Configuration
// ==========================================
#define DMA_DEV_ID          XPAR_AXIDMA_0_DEVICE_ID
#define SNN_IP_DEV_ID       XPAR_SNN_IP_0_DEVICE_ID   // xparameters.h 안 이름에 맞게 확인

// DDR 내 버퍼 베이스 주소 (디자인마다 다를 수 있음)
#define MEM_BASE_ADDR       0x01000000
#define TX_BUFFER_BASE      (MEM_BASE_ADDR + 0x00100000)
#define RX_BUFFER_BASE      (MEM_BASE_ADDR + 0x00300000)

#define T_TIMESTEPS         10
#define N_INPUT             256
#define N_OUTPUT            10

// We send 1 spike per AXI-stream word (1 byte stored in LSB)
#define N_SPIKES            (T_TIMESTEPS * N_INPUT)   // 2560
#define N_WORDS_IN          N_SPIKES                  // 2560 32-bit words
#define N_WORDS_OUT         1                         // one 32-bit result

// DMA Busy 대기 타임아웃 (loop 카운트)
#define DMA_TIMEOUT_COUNT   100000000

// ==========================================
// Global variables
// ==========================================
static XAxiDma AxiDma;
static XSnn_ip SnnIp;          // HLS SNN IP 인스턴스

static u32 *TxBufferPtr = (u32 *)TX_BUFFER_BASE;
static u32 *RxBufferPtr = (u32 *)RX_BUFFER_BASE;

// UART inbyte prototype (standalone BSP usually provides this)
extern char inbyte(void);

// ==========================================
// Helper: Initialize AXI DMA
// ==========================================
int init_dma(void)
{
    XAxiDma_Config *CfgPtr;
    int Status;

    CfgPtr = XAxiDma_LookupConfig(DMA_DEV_ID);
    if (!CfgPtr) {
        xil_printf("No config found for AXI DMA %d\r\n", DMA_DEV_ID);
        return XST_FAILURE;
    }

    Status = XAxiDma_CfgInitialize(&AxiDma, CfgPtr);
    if (Status != XST_SUCCESS) {
        xil_printf("AXI DMA init failed (Status=%d)\r\n", Status);
        return XST_FAILURE;
    }

    // Ensure Scatter-Gather mode is disabled (we use Simple mode)
    if (XAxiDma_HasSg(&AxiDma)) {
        xil_printf("AXI DMA is in SG mode, not supported in this example\r\n");
        return XST_FAILURE;
    }

    xil_printf("AXI DMA init OK.\r\n");
    return XST_SUCCESS;
}

// ==========================================
// Helper: Initialize SNN IP (HLS)
// ==========================================
int init_snn_ip(void)
{
    int Status;
    XSnn_ip_Config *CfgPtr;

    CfgPtr = XSnn_ip_LookupConfig(SNN_IP_DEV_ID);
    if (!CfgPtr) {
        xil_printf("No config found for SNN IP (ID=%d)\r\n", SNN_IP_DEV_ID);
        return XST_FAILURE;
    }

    Status = XSnn_ip_CfgInitialize(&SnnIp, CfgPtr);
    if (Status != XST_SUCCESS) {
        xil_printf("SNN IP init failed (Status=%d)\r\n", Status);
        return XST_FAILURE;
    }

    xil_printf("SNN IP init OK.\r\n");
    return XST_SUCCESS;
}

// ==========================================
// main
// ==========================================
int main()
{
    int Status;
    int iter = 0;

    init_platform();
    xil_printf("=== SNN FC-last DMA test (PC spikes) ===\r\n");

    Status = init_dma();
    if (Status != XST_SUCCESS) {
        xil_printf("DMA init failed. Exiting.\r\n");
        cleanup_platform();
        return XST_FAILURE;
    }

    Status = init_snn_ip();
    if (Status != XST_SUCCESS) {
        xil_printf("SNN IP init failed. Exiting.\r\n");
        cleanup_platform();
        return XST_FAILURE;
    }

    xil_printf("Using T_TIMESTEPS = %d, N_INPUT = %d, N_SPIKES = %d\r\n",
               T_TIMESTEPS, N_INPUT, N_SPIKES);
    xil_printf("TX_BUFFER_BASE = 0x%08lx, RX_BUFFER_BASE = 0x%08lx\r\n",
               (unsigned long)TX_BUFFER_BASE, (unsigned long)RX_BUFFER_BASE);
    xil_printf("Waiting for spikes from PC over UART...\r\n");

    // ======================================
    // Infinite loop: process many images
    // Each iteration:
    //   1) Wait for header "SNN"
    //   2) Receive 2560 spike bytes
    //   3) Pack to TX buffer (LSB)
    //   4) Run DMA MM2S + S2MM
    //   5) Start SNN IP
    //   6) Print predicted class
    // ======================================
    while (1) {
        xil_printf("\r\n========================================\r\n");
        xil_printf("Iteration %d: SNN waiting for header from PC...\r\n", iter);

        // ----------------------------------
        // 1) Wait for header "SNN"
        // ----------------------------------
        char h0, h1, h2;

        // 첫 글자 'S' 올 때까지 블로킹
        do {
            h0 = inbyte();
        } while (h0 != 'S');

        // 바로 다음 두 글자 읽기
        h1 = inbyte();
        h2 = inbyte();

        if (h1 != 'N' || h2 != 'N') {
            xil_printf("Bad header received at iter %d: '%c' '%c' (expected 'N' 'N')\r\n",
                       iter, h1, h2);
            // 다시 헤더 대기
            continue;
        }

        xil_printf("Header OK at iter %d. Receiving %d spike bytes...\r\n",
                   iter, N_SPIKES);

        // ----------------------------------
        // 2) Receive N_SPIKES bytes from UART
        //    and pack into 32-bit TX buffer
        // ----------------------------------
        for (int i = 0; i < N_SPIKES; i++) {
            unsigned char b = (unsigned char)inbyte();
            // LSB에 spike 저장
            TxBufferPtr[i] = (u32)b;
        }

        xil_printf("Iteration %d: Received all spikes from PC (count=%d).\r\n",
                   iter, N_SPIKES);

        // 디버깅용: RX 버퍼를 미리 특이 값으로 채워둠
        RxBufferPtr[0] = 0xDEADBEEF;

        // Flush TX buffer cache before DMA
        xil_printf("Iteration %d: Flushing TX cache, invalidating RX cache.\r\n", iter);
        Xil_DCacheFlushRange((UINTPTR)TxBufferPtr, N_WORDS_IN * sizeof(u32));
        Xil_DCacheInvalidateRange((UINTPTR)RxBufferPtr, N_WORDS_OUT * sizeof(u32));

        // ----------------------------------
        // 3) Start S2MM (device-to-DMA) for result
        // ----------------------------------
        xil_printf("Iteration %d: Starting S2MM (device->DDR)...\r\n", iter);
        Status = XAxiDma_SimpleTransfer(
            &AxiDma,
            (UINTPTR)RxBufferPtr,
            N_WORDS_OUT * sizeof(u32),
            XAXIDMA_DEVICE_TO_DMA
        );
        if (Status != XST_SUCCESS) {
            xil_printf("AXI DMA S2MM transfer failed at iter %d (Status = %d)\r\n",
                       iter, Status);
            continue;
        }

        // ----------------------------------
        // 4) Start MM2S (DMA-to-device) for spikes
        // ----------------------------------
        xil_printf("Iteration %d: Starting MM2S (DDR->device)...\r\n", iter);
        Status = XAxiDma_SimpleTransfer(
            &AxiDma,
            (UINTPTR)TxBufferPtr,
            N_WORDS_IN * sizeof(u32),
            XAXIDMA_DMA_TO_DEVICE
        );
        if (Status != XST_SUCCESS) {
            xil_printf("AXI DMA MM2S transfer failed at iter %d (Status = %d)\r\n",
                       iter, Status);
            continue;
        }

        // ----------------------------------
        // 5) Start SNN IP (ap_start=1)
        // ----------------------------------
        xil_printf("Iteration %d: Starting SNN IP...\r\n", iter);
        XSnn_ip_Start(&SnnIp);

        // ----------------------------------
        // 6) Wait for both DMA directions to complete
        //    (타임아웃 걸어서 무한 루프 방지)
        // ----------------------------------
        xil_printf("Iteration %d: Waiting for MM2S done...\r\n", iter);
        int timeout = DMA_TIMEOUT_COUNT;
        while (XAxiDma_Busy(&AxiDma, XAXIDMA_DMA_TO_DEVICE)) {
            if (--timeout <= 0) {
                xil_printf("ERROR: MM2S timeout at iter %d\r\n", iter);
                break;
            }
        }
        if (timeout <= 0) {
            // 필요하면 여기서 DMA reset 추가 가능
            continue;
        }

        xil_printf("Iteration %d: MM2S done.\r\n", iter);

        xil_printf("Iteration %d: Waiting for S2MM done...\r\n", iter);
        timeout = DMA_TIMEOUT_COUNT;
        while (XAxiDma_Busy(&AxiDma, XAXIDMA_DEVICE_TO_DMA)) {
            if (--timeout <= 0) {
                xil_printf("ERROR: S2MM timeout at iter %d\r\n", iter);
                break;
            }
        }
        if (timeout <= 0) {
            continue;
        }
        xil_printf("Iteration %d: S2MM done.\r\n", iter);

        // (옵션) IP 연산 완료 대기
        xil_printf("Iteration %d: Waiting for SNN IP done...\r\n", iter);
        timeout = DMA_TIMEOUT_COUNT;
        while (!XSnn_ip_IsDone(&SnnIp)) {
            if (--timeout <= 0) {
                xil_printf("ERROR: SNN IP done timeout at iter %d\r\n", iter);
                break;
            }
        }
        if (timeout <= 0) {
            continue;
        }
        xil_printf("Iteration %d: SNN IP done.\r\n", iter);

        // Invalidate RX buffer cache so CPU sees updated data
        Xil_DCacheInvalidateRange((UINTPTR)RxBufferPtr, N_WORDS_OUT * sizeof(u32));

        // ----------------------------------
        // 7) Read result from RX buffer
        //     snn_ip writes a 32-bit word, LSB = class index (0~9)
        // ----------------------------------
        xil_printf("Iteration %d: DMA complete. Rx[0] = 0x%08lx\r\n",
                   iter, (unsigned long)RxBufferPtr[0]);

        int out_class = (int)(RxBufferPtr[0] & 0xFF);

        xil_printf("Predicted class = %d\r\n", out_class);
        xil_printf("---- One sample processed. Ready for next. ----\r\n");

        iter++;
    }

    // We never reach here in this infinite loop design
    cleanup_platform();
    return XST_SUCCESS;
}
