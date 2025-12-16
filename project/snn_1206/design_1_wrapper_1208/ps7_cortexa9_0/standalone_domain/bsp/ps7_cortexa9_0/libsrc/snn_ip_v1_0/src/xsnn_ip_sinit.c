// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.2 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xsnn_ip.h"

extern XSnn_ip_Config XSnn_ip_ConfigTable[];

XSnn_ip_Config *XSnn_ip_LookupConfig(u16 DeviceId) {
	XSnn_ip_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XSNN_IP_NUM_INSTANCES; Index++) {
		if (XSnn_ip_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XSnn_ip_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XSnn_ip_Initialize(XSnn_ip *InstancePtr, u16 DeviceId) {
	XSnn_ip_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XSnn_ip_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XSnn_ip_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

