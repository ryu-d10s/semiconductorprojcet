// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.2 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xfc_snn_top.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XFc_snn_top_CfgInitialize(XFc_snn_top *InstancePtr, XFc_snn_top_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Ctrl_BaseAddress = ConfigPtr->Ctrl_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XFc_snn_top_Start(XFc_snn_top *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XFc_snn_top_ReadReg(InstancePtr->Ctrl_BaseAddress, XFC_SNN_TOP_CTRL_ADDR_AP_CTRL) & 0x80;
    XFc_snn_top_WriteReg(InstancePtr->Ctrl_BaseAddress, XFC_SNN_TOP_CTRL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XFc_snn_top_IsDone(XFc_snn_top *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XFc_snn_top_ReadReg(InstancePtr->Ctrl_BaseAddress, XFC_SNN_TOP_CTRL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XFc_snn_top_IsIdle(XFc_snn_top *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XFc_snn_top_ReadReg(InstancePtr->Ctrl_BaseAddress, XFC_SNN_TOP_CTRL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XFc_snn_top_IsReady(XFc_snn_top *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XFc_snn_top_ReadReg(InstancePtr->Ctrl_BaseAddress, XFC_SNN_TOP_CTRL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XFc_snn_top_EnableAutoRestart(XFc_snn_top *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XFc_snn_top_WriteReg(InstancePtr->Ctrl_BaseAddress, XFC_SNN_TOP_CTRL_ADDR_AP_CTRL, 0x80);
}

void XFc_snn_top_DisableAutoRestart(XFc_snn_top *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XFc_snn_top_WriteReg(InstancePtr->Ctrl_BaseAddress, XFC_SNN_TOP_CTRL_ADDR_AP_CTRL, 0);
}

void XFc_snn_top_Set_n_steps(XFc_snn_top *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XFc_snn_top_WriteReg(InstancePtr->Ctrl_BaseAddress, XFC_SNN_TOP_CTRL_ADDR_N_STEPS_DATA, Data);
}

u32 XFc_snn_top_Get_n_steps(XFc_snn_top *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XFc_snn_top_ReadReg(InstancePtr->Ctrl_BaseAddress, XFC_SNN_TOP_CTRL_ADDR_N_STEPS_DATA);
    return Data;
}

void XFc_snn_top_Set_clear_state(XFc_snn_top *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XFc_snn_top_WriteReg(InstancePtr->Ctrl_BaseAddress, XFC_SNN_TOP_CTRL_ADDR_CLEAR_STATE_DATA, Data);
}

u32 XFc_snn_top_Get_clear_state(XFc_snn_top *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XFc_snn_top_ReadReg(InstancePtr->Ctrl_BaseAddress, XFC_SNN_TOP_CTRL_ADDR_CLEAR_STATE_DATA);
    return Data;
}

void XFc_snn_top_InterruptGlobalEnable(XFc_snn_top *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XFc_snn_top_WriteReg(InstancePtr->Ctrl_BaseAddress, XFC_SNN_TOP_CTRL_ADDR_GIE, 1);
}

void XFc_snn_top_InterruptGlobalDisable(XFc_snn_top *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XFc_snn_top_WriteReg(InstancePtr->Ctrl_BaseAddress, XFC_SNN_TOP_CTRL_ADDR_GIE, 0);
}

void XFc_snn_top_InterruptEnable(XFc_snn_top *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XFc_snn_top_ReadReg(InstancePtr->Ctrl_BaseAddress, XFC_SNN_TOP_CTRL_ADDR_IER);
    XFc_snn_top_WriteReg(InstancePtr->Ctrl_BaseAddress, XFC_SNN_TOP_CTRL_ADDR_IER, Register | Mask);
}

void XFc_snn_top_InterruptDisable(XFc_snn_top *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XFc_snn_top_ReadReg(InstancePtr->Ctrl_BaseAddress, XFC_SNN_TOP_CTRL_ADDR_IER);
    XFc_snn_top_WriteReg(InstancePtr->Ctrl_BaseAddress, XFC_SNN_TOP_CTRL_ADDR_IER, Register & (~Mask));
}

void XFc_snn_top_InterruptClear(XFc_snn_top *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XFc_snn_top_WriteReg(InstancePtr->Ctrl_BaseAddress, XFC_SNN_TOP_CTRL_ADDR_ISR, Mask);
}

u32 XFc_snn_top_InterruptGetEnabled(XFc_snn_top *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XFc_snn_top_ReadReg(InstancePtr->Ctrl_BaseAddress, XFC_SNN_TOP_CTRL_ADDR_IER);
}

u32 XFc_snn_top_InterruptGetStatus(XFc_snn_top *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XFc_snn_top_ReadReg(InstancePtr->Ctrl_BaseAddress, XFC_SNN_TOP_CTRL_ADDR_ISR);
}

