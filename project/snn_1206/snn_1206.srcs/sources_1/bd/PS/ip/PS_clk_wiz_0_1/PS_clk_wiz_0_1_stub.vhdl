-- Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2019.2 (win64) Build 2708876 Wed Nov  6 21:40:23 MST 2019
-- Date        : Thu Dec 11 01:39:40 2025
-- Host        : IT23-JS running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode synth_stub
--               c:/snn_1206/snn_1206.srcs/sources_1/bd/PS/ip/PS_clk_wiz_0_1/PS_clk_wiz_0_1_stub.vhdl
-- Design      : PS_clk_wiz_0_1
-- Purpose     : Stub declaration of top-level module interface
-- Device      : xc7z020clg484-1
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity PS_clk_wiz_0_1 is
  Port ( 
    PL_clk_out : out STD_LOGIC;
    LCD_clk_out : out STD_LOGIC;
    reset : in STD_LOGIC;
    locked : out STD_LOGIC;
    clk_in1 : in STD_LOGIC
  );

end PS_clk_wiz_0_1;

architecture stub of PS_clk_wiz_0_1 is
attribute syn_black_box : boolean;
attribute black_box_pad_pin : string;
attribute syn_black_box of stub : architecture is true;
attribute black_box_pad_pin of stub : architecture is "PL_clk_out,LCD_clk_out,reset,locked,clk_in1";
begin
end;
