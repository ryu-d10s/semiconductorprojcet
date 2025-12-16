// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.2 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xfc_snn_top.h"

extern XFc_snn_top_Config XFc_snn_top_ConfigTable[];

XFc_snn_top_Config *XFc_snn_top_LookupConfig(u16 DeviceId) {
	XFc_snn_top_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XFC_SNN_TOP_NUM_INSTANCES; Index++) {
		if (XFc_snn_top_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XFc_snn_top_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XFc_snn_top_Initialize(XFc_snn_top *InstancePtr, u16 DeviceId) {
	XFc_snn_top_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XFc_snn_top_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XFc_snn_top_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

