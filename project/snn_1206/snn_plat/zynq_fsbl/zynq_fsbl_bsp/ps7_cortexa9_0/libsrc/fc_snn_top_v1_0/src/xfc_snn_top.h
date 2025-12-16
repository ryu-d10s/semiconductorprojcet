// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.2 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XFC_SNN_TOP_H
#define XFC_SNN_TOP_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xfc_snn_top_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
#else
typedef struct {
    u16 DeviceId;
    u32 Ctrl_BaseAddress;
} XFc_snn_top_Config;
#endif

typedef struct {
    u32 Ctrl_BaseAddress;
    u32 IsReady;
} XFc_snn_top;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XFc_snn_top_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XFc_snn_top_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XFc_snn_top_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XFc_snn_top_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
int XFc_snn_top_Initialize(XFc_snn_top *InstancePtr, u16 DeviceId);
XFc_snn_top_Config* XFc_snn_top_LookupConfig(u16 DeviceId);
int XFc_snn_top_CfgInitialize(XFc_snn_top *InstancePtr, XFc_snn_top_Config *ConfigPtr);
#else
int XFc_snn_top_Initialize(XFc_snn_top *InstancePtr, const char* InstanceName);
int XFc_snn_top_Release(XFc_snn_top *InstancePtr);
#endif

void XFc_snn_top_Start(XFc_snn_top *InstancePtr);
u32 XFc_snn_top_IsDone(XFc_snn_top *InstancePtr);
u32 XFc_snn_top_IsIdle(XFc_snn_top *InstancePtr);
u32 XFc_snn_top_IsReady(XFc_snn_top *InstancePtr);
void XFc_snn_top_EnableAutoRestart(XFc_snn_top *InstancePtr);
void XFc_snn_top_DisableAutoRestart(XFc_snn_top *InstancePtr);

void XFc_snn_top_Set_n_steps(XFc_snn_top *InstancePtr, u32 Data);
u32 XFc_snn_top_Get_n_steps(XFc_snn_top *InstancePtr);
void XFc_snn_top_Set_clear_state(XFc_snn_top *InstancePtr, u32 Data);
u32 XFc_snn_top_Get_clear_state(XFc_snn_top *InstancePtr);

void XFc_snn_top_InterruptGlobalEnable(XFc_snn_top *InstancePtr);
void XFc_snn_top_InterruptGlobalDisable(XFc_snn_top *InstancePtr);
void XFc_snn_top_InterruptEnable(XFc_snn_top *InstancePtr, u32 Mask);
void XFc_snn_top_InterruptDisable(XFc_snn_top *InstancePtr, u32 Mask);
void XFc_snn_top_InterruptClear(XFc_snn_top *InstancePtr, u32 Mask);
u32 XFc_snn_top_InterruptGetEnabled(XFc_snn_top *InstancePtr);
u32 XFc_snn_top_InterruptGetStatus(XFc_snn_top *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
