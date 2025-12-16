// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.2 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xsnn_ip.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XSnn_ip_CfgInitialize(XSnn_ip *InstancePtr, XSnn_ip_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Ctrl_BaseAddress = ConfigPtr->Ctrl_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XSnn_ip_Start(XSnn_ip *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XSnn_ip_ReadReg(InstancePtr->Ctrl_BaseAddress, XSNN_IP_CTRL_ADDR_AP_CTRL) & 0x80;
    XSnn_ip_WriteReg(InstancePtr->Ctrl_BaseAddress, XSNN_IP_CTRL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XSnn_ip_IsDone(XSnn_ip *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XSnn_ip_ReadReg(InstancePtr->Ctrl_BaseAddress, XSNN_IP_CTRL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XSnn_ip_IsIdle(XSnn_ip *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XSnn_ip_ReadReg(InstancePtr->Ctrl_BaseAddress, XSNN_IP_CTRL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XSnn_ip_IsReady(XSnn_ip *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XSnn_ip_ReadReg(InstancePtr->Ctrl_BaseAddress, XSNN_IP_CTRL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XSnn_ip_EnableAutoRestart(XSnn_ip *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XSnn_ip_WriteReg(InstancePtr->Ctrl_BaseAddress, XSNN_IP_CTRL_ADDR_AP_CTRL, 0x80);
}

void XSnn_ip_DisableAutoRestart(XSnn_ip *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XSnn_ip_WriteReg(InstancePtr->Ctrl_BaseAddress, XSNN_IP_CTRL_ADDR_AP_CTRL, 0);
}

void XSnn_ip_InterruptGlobalEnable(XSnn_ip *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XSnn_ip_WriteReg(InstancePtr->Ctrl_BaseAddress, XSNN_IP_CTRL_ADDR_GIE, 1);
}

void XSnn_ip_InterruptGlobalDisable(XSnn_ip *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XSnn_ip_WriteReg(InstancePtr->Ctrl_BaseAddress, XSNN_IP_CTRL_ADDR_GIE, 0);
}

void XSnn_ip_InterruptEnable(XSnn_ip *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XSnn_ip_ReadReg(InstancePtr->Ctrl_BaseAddress, XSNN_IP_CTRL_ADDR_IER);
    XSnn_ip_WriteReg(InstancePtr->Ctrl_BaseAddress, XSNN_IP_CTRL_ADDR_IER, Register | Mask);
}

void XSnn_ip_InterruptDisable(XSnn_ip *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XSnn_ip_ReadReg(InstancePtr->Ctrl_BaseAddress, XSNN_IP_CTRL_ADDR_IER);
    XSnn_ip_WriteReg(InstancePtr->Ctrl_BaseAddress, XSNN_IP_CTRL_ADDR_IER, Register & (~Mask));
}

void XSnn_ip_InterruptClear(XSnn_ip *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XSnn_ip_WriteReg(InstancePtr->Ctrl_BaseAddress, XSNN_IP_CTRL_ADDR_ISR, Mask);
}

u32 XSnn_ip_InterruptGetEnabled(XSnn_ip *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XSnn_ip_ReadReg(InstancePtr->Ctrl_BaseAddress, XSNN_IP_CTRL_ADDR_IER);
}

u32 XSnn_ip_InterruptGetStatus(XSnn_ip *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XSnn_ip_ReadReg(InstancePtr->Ctrl_BaseAddress, XSNN_IP_CTRL_ADDR_ISR);
}

