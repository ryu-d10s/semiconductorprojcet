/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */
#include <stdio.h>
#include "xparameters.h"
#include "xil_cache.h"
#include "xil_printf.h"
#include "xaxidma.h"
#include "xfc_snn_top.h"

#define N_STEPS 16
#define WORDS_PER_STEP 128  // 4096 neurons / 32 bits = 128 words

#define TX_WORDS   (N_STEPS * WORDS_PER_STEP)
#define RX_WORDS   (N_STEPS)

// DDR buffers aligned for cache operations
static u32 tx_buf[TX_WORDS] __attribute__ ((aligned(64)));
static u32 rx_buf[RX_WORDS] __attribute__ ((aligned(64)));

int main() {
    int status;
    xil_printf("===== SNN DMA Application Start =====\r\n");

    // --------------------------------------------------
    // 1. Prepare Input Spike Data
    // --------------------------------------------------
    for (int i = 0; i < TX_WORDS; i++) tx_buf[i] = 0;
    // Example: Force first word as full spike pattern
    for (int w = 0; w < WORDS_PER_STEP; w++)
        tx_buf[w] = 0xFFFFFFFF;  // all spikes ON for test

    for (int i = 0; i < RX_WORDS; i++) rx_buf[i] = 0;

    int tx_bytes = TX_WORDS * sizeof(u32);
    int rx_bytes = RX_WORDS * sizeof(u32);

    // Cache operations (VERY IMPORTANT)
    Xil_DCacheFlushRange((UINTPTR)tx_buf, tx_bytes);
    Xil_DCacheInvalidateRange((UINTPTR)rx_buf, rx_bytes);

    // --------------------------------------------------
    // 2. Initialize DMA
    // --------------------------------------------------
    XAxiDma AxiDma;
    XAxiDma_Config *DmaCfg = XAxiDma_LookupConfig(XPAR_AXIDMA_0_DEVICE_ID);
    if (!DmaCfg) {
        xil_printf("No DMA config found\r\n");
        return XST_FAILURE;
    }
    status = XAxiDma_CfgInitialize(&AxiDma, DmaCfg);
    if (status != XST_SUCCESS) {
        xil_printf("DMA init failed\r\n");
        return XST_FAILURE;
    }
    if (XAxiDma_HasSg(&AxiDma)) {
        xil_printf("ERROR: DMA configured as SG, expected Simple mode\r\n");
        return XST_FAILURE;
    }

    // --------------------------------------------------
    // 3. Initialize HLS IP (fc_snn_top)
    // --------------------------------------------------
    XFc_snn_top FcIp;
    status = XFc_snn_top_Initialize(&FcIp, XPAR_XFC_SNN_TOP_0_DEVICE_ID);
    if (status != XST_SUCCESS) {
        xil_printf("HLS IP init failed\r\n");
        return XST_FAILURE;
    }

    // Set parameters
    XFc_snn_top_Set_n_steps(&FcIp, N_STEPS);
    XFc_snn_top_Set_clear_state(&FcIp, 1);

    // Start SNN IP
    XFc_snn_top_Start(&FcIp);

    // --------------------------------------------------
    // 4. Start DMA Transfers
    // --------------------------------------------------
    // Start RX (S2MM) first, then TX (MM2S)
    status = XAxiDma_SimpleTransfer(&AxiDma, (UINTPTR)rx_buf,
                                    rx_bytes, XAXIDMA_DEVICE_TO_DMA);
    if (status != XST_SUCCESS) {
        xil_printf("S2MM start failed\r\n");
        return XST_FAILURE;
    }

    status = XAxiDma_SimpleTransfer(&AxiDma, (UINTPTR)tx_buf,
                                    tx_bytes, XAXIDMA_DMA_TO_DEVICE);
    if (status != XST_SUCCESS) {
        xil_printf("MM2S start failed\r\n");
        return XST_FAILURE;
    }

    // --------------------------------------------------
    // 5. Wait for completion
    // --------------------------------------------------
    while (XAxiDma_Busy(&AxiDma, XAXIDMA_DMA_TO_DEVICE));
    while (XAxiDma_Busy(&AxiDma, XAXIDMA_DEVICE_TO_DMA));
    while (!XFc_snn_top_IsDone(&FcIp));

    // Cache invalidate to see fresh data
    Xil_DCacheInvalidateRange((UINTPTR)rx_buf, rx_bytes);

    // --------------------------------------------------
    // 6. Print Results
    // --------------------------------------------------
    xil_printf("===== SNN Output =====\r\n");
    for (int t = 0; t < N_STEPS; t++)
        xil_printf("t=%d : 0x%08x\r\n", t, rx_buf[t]);

    xil_printf("===== Application End =====\r\n");
    return 0;
}
