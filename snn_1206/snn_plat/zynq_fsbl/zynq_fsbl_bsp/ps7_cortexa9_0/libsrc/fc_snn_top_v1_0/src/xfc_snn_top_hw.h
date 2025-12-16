// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.2 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================
// CTRL
// 0x00 : Control signals
//        bit 0  - ap_start (Read/Write/COH)
//        bit 1  - ap_done (Read/COR)
//        bit 2  - ap_idle (Read)
//        bit 3  - ap_ready (Read)
//        bit 7  - auto_restart (Read/Write)
//        others - reserved
// 0x04 : Global Interrupt Enable Register
//        bit 0  - Global Interrupt Enable (Read/Write)
//        others - reserved
// 0x08 : IP Interrupt Enable Register (Read/Write)
//        bit 0  - Channel 0 (ap_done)
//        bit 1  - Channel 1 (ap_ready)
//        others - reserved
// 0x0c : IP Interrupt Status Register (Read/TOW)
//        bit 0  - Channel 0 (ap_done)
//        bit 1  - Channel 1 (ap_ready)
//        others - reserved
// 0x10 : Data signal of n_steps
//        bit 31~0 - n_steps[31:0] (Read/Write)
// 0x14 : reserved
// 0x18 : Data signal of clear_state
//        bit 0  - clear_state[0] (Read/Write)
//        others - reserved
// 0x1c : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XFC_SNN_TOP_CTRL_ADDR_AP_CTRL          0x00
#define XFC_SNN_TOP_CTRL_ADDR_GIE              0x04
#define XFC_SNN_TOP_CTRL_ADDR_IER              0x08
#define XFC_SNN_TOP_CTRL_ADDR_ISR              0x0c
#define XFC_SNN_TOP_CTRL_ADDR_N_STEPS_DATA     0x10
#define XFC_SNN_TOP_CTRL_BITS_N_STEPS_DATA     32
#define XFC_SNN_TOP_CTRL_ADDR_CLEAR_STATE_DATA 0x18
#define XFC_SNN_TOP_CTRL_BITS_CLEAR_STATE_DATA 1

