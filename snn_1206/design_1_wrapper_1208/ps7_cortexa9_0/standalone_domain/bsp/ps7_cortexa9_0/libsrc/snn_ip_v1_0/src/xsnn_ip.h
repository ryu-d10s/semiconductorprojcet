// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.2 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XSNN_IP_H
#define XSNN_IP_H

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
#include "xsnn_ip_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
#else
typedef struct {
    u16 DeviceId;
    u32 Ctrl_BaseAddress;
} XSnn_ip_Config;
#endif

typedef struct {
    u32 Ctrl_BaseAddress;
    u32 IsReady;
} XSnn_ip;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XSnn_ip_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XSnn_ip_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XSnn_ip_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XSnn_ip_ReadReg(BaseAddress, RegOffset) \
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
int XSnn_ip_Initialize(XSnn_ip *InstancePtr, u16 DeviceId);
XSnn_ip_Config* XSnn_ip_LookupConfig(u16 DeviceId);
int XSnn_ip_CfgInitialize(XSnn_ip *InstancePtr, XSnn_ip_Config *ConfigPtr);
#else
int XSnn_ip_Initialize(XSnn_ip *InstancePtr, const char* InstanceName);
int XSnn_ip_Release(XSnn_ip *InstancePtr);
#endif

void XSnn_ip_Start(XSnn_ip *InstancePtr);
u32 XSnn_ip_IsDone(XSnn_ip *InstancePtr);
u32 XSnn_ip_IsIdle(XSnn_ip *InstancePtr);
u32 XSnn_ip_IsReady(XSnn_ip *InstancePtr);
void XSnn_ip_EnableAutoRestart(XSnn_ip *InstancePtr);
void XSnn_ip_DisableAutoRestart(XSnn_ip *InstancePtr);


void XSnn_ip_InterruptGlobalEnable(XSnn_ip *InstancePtr);
void XSnn_ip_InterruptGlobalDisable(XSnn_ip *InstancePtr);
void XSnn_ip_InterruptEnable(XSnn_ip *InstancePtr, u32 Mask);
void XSnn_ip_InterruptDisable(XSnn_ip *InstancePtr, u32 Mask);
void XSnn_ip_InterruptClear(XSnn_ip *InstancePtr, u32 Mask);
u32 XSnn_ip_InterruptGetEnabled(XSnn_ip *InstancePtr);
u32 XSnn_ip_InterruptGetStatus(XSnn_ip *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
