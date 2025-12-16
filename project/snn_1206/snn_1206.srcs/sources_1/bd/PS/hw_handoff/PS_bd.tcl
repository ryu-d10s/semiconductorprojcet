
################################################################
# This is a generated script based on design: PS
#
# Though there are limitations about the generated script,
# the main purpose of this utility is to make learning
# IP Integrator Tcl commands easier.
################################################################

namespace eval _tcl {
proc get_script_folder {} {
   set script_path [file normalize [info script]]
   set script_folder [file dirname $script_path]
   return $script_folder
}
}
variable script_folder
set script_folder [_tcl::get_script_folder]

################################################################
# Check if script is running in correct Vivado version.
################################################################
set scripts_vivado_version 2019.2
set current_vivado_version [version -short]

if { [string first $scripts_vivado_version $current_vivado_version] == -1 } {
   puts ""
   catch {common::send_msg_id "BD_TCL-109" "ERROR" "This script was generated using Vivado <$scripts_vivado_version> and is being run in <$current_vivado_version> of Vivado. Please run the script in Vivado <$scripts_vivado_version> then open the design in Vivado <$current_vivado_version>. Upgrade the design by running \"Tools => Report => Report IP Status...\", then run write_bd_tcl to create an updated script."}

   return 1
}

################################################################
# START
################################################################

# To test this script, run the following commands from Vivado Tcl console:
# source PS_script.tcl

# If there is no project opened, this script will create a
# project, but make sure you do not have an existing project
# <./myproj/project_1.xpr> in the current working folder.

set list_projs [get_projects -quiet]
if { $list_projs eq "" } {
   create_project project_1 myproj -part xc7z020clg484-1
   set_property BOARD_PART em.avnet.com:zed:part0:1.4 [current_project]
}


# CHANGE DESIGN NAME HERE
variable design_name
set design_name PS

# If you do not already have an existing IP Integrator design open,
# you can create a design using the following command:
#    create_bd_design $design_name

# Creating design if needed
set errMsg ""
set nRet 0

set cur_design [current_bd_design -quiet]
set list_cells [get_bd_cells -quiet]

if { ${design_name} eq "" } {
   # USE CASES:
   #    1) Design_name not set

   set errMsg "Please set the variable <design_name> to a non-empty value."
   set nRet 1

} elseif { ${cur_design} ne "" && ${list_cells} eq "" } {
   # USE CASES:
   #    2): Current design opened AND is empty AND names same.
   #    3): Current design opened AND is empty AND names diff; design_name NOT in project.
   #    4): Current design opened AND is empty AND names diff; design_name exists in project.

   if { $cur_design ne $design_name } {
      common::send_msg_id "BD_TCL-001" "INFO" "Changing value of <design_name> from <$design_name> to <$cur_design> since current design is empty."
      set design_name [get_property NAME $cur_design]
   }
   common::send_msg_id "BD_TCL-002" "INFO" "Constructing design in IPI design <$cur_design>..."

} elseif { ${cur_design} ne "" && $list_cells ne "" && $cur_design eq $design_name } {
   # USE CASES:
   #    5) Current design opened AND has components AND same names.

   set errMsg "Design <$design_name> already exists in your project, please set the variable <design_name> to another value."
   set nRet 1
} elseif { [get_files -quiet ${design_name}.bd] ne "" } {
   # USE CASES: 
   #    6) Current opened design, has components, but diff names, design_name exists in project.
   #    7) No opened design, design_name exists in project.

   set errMsg "Design <$design_name> already exists in your project, please set the variable <design_name> to another value."
   set nRet 2

} else {
   # USE CASES:
   #    8) No opened design, design_name not in project.
   #    9) Current opened design, has components, but diff names, design_name not in project.

   common::send_msg_id "BD_TCL-003" "INFO" "Currently there is no design <$design_name> in project, so creating one..."

   create_bd_design $design_name

   common::send_msg_id "BD_TCL-004" "INFO" "Making design <$design_name> as current_bd_design."
   current_bd_design $design_name

}

common::send_msg_id "BD_TCL-005" "INFO" "Currently the variable <design_name> is equal to \"$design_name\"."

if { $nRet != 0 } {
   catch {common::send_msg_id "BD_TCL-114" "ERROR" $errMsg}
   return $nRet
}

##################################################################
# DESIGN PROCs
##################################################################



# Procedure to create entire design; Provide argument to make
# procedure reusable. If parentCell is "", will use root.
proc create_root_design { parentCell } {

  variable script_folder
  variable design_name

  if { $parentCell eq "" } {
     set parentCell [get_bd_cells /]
  }

  # Get object for parentCell
  set parentObj [get_bd_cells $parentCell]
  if { $parentObj == "" } {
     catch {common::send_msg_id "BD_TCL-100" "ERROR" "Unable to find parent cell <$parentCell>!"}
     return
  }

  # Make sure parentObj is hier blk
  set parentType [get_property TYPE $parentObj]
  if { $parentType ne "hier" } {
     catch {common::send_msg_id "BD_TCL-101" "ERROR" "Parent <$parentObj> has TYPE = <$parentType>. Expected to be <hier>."}
     return
  }

  # Save current instance; Restore later
  set oldCurInst [current_bd_instance .]

  # Set parent object as current
  current_bd_instance $parentObj


  # Create interface ports

  # Create ports
  set reset_rtl [ create_bd_port -dir I -type rst reset_rtl ]
  set_property -dict [ list \
   CONFIG.POLARITY {ACTIVE_HIGH} \
 ] $reset_rtl
  set reset_rtl_0 [ create_bd_port -dir I -type rst reset_rtl_0 ]
  set_property -dict [ list \
   CONFIG.POLARITY {ACTIVE_HIGH} \
 ] $reset_rtl_0
  set sys_clock [ create_bd_port -dir I -type clk -freq_hz 100000000 sys_clock ]
  set_property -dict [ list \
   CONFIG.PHASE {0.000} \
 ] $sys_clock

  # Create instance: CAM_mclk_GEN, and set properties
  set CAM_mclk_GEN [ create_bd_cell -type ip -vlnv xilinx.com:ip:clk_wiz:6.0 CAM_mclk_GEN ]
  set_property -dict [ list \
   CONFIG.CLKOUT1_JITTER {171.290} \
   CONFIG.CLKOUT1_PHASE_ERROR {97.646} \
   CONFIG.CLKOUT1_REQUESTED_OUT_FREQ {27.000} \
   CONFIG.CLK_IN1_BOARD_INTERFACE {sys_clock} \
   CONFIG.CLK_OUT1_PORT {CAM_mclk} \
   CONFIG.MMCM_CLKFBOUT_MULT_F {10.125} \
   CONFIG.MMCM_CLKOUT0_DIVIDE_F {37.500} \
   CONFIG.USE_BOARD_FLOW {true} \
 ] $CAM_mclk_GEN

  # Create instance: CAM_pdata_sync_FIFO, and set properties
  set CAM_pdata_sync_FIFO [ create_bd_cell -type ip -vlnv xilinx.com:ip:fifo_generator:13.2 CAM_pdata_sync_FIFO ]
  set_property -dict [ list \
   CONFIG.Data_Count_Width {10} \
   CONFIG.Empty_Threshold_Assert_Value {64} \
   CONFIG.Empty_Threshold_Negate_Value {65} \
   CONFIG.Enable_Safety_Circuit {true} \
   CONFIG.Fifo_Implementation {Independent_Clocks_Block_RAM} \
   CONFIG.Full_Flags_Reset_Value {1} \
   CONFIG.Full_Threshold_Assert_Value {800} \
   CONFIG.Full_Threshold_Negate_Value {32} \
   CONFIG.Input_Data_Width {16} \
   CONFIG.Output_Data_Width {32} \
   CONFIG.Output_Depth {512} \
   CONFIG.Performance_Options {First_Word_Fall_Through} \
   CONFIG.Programmable_Empty_Type {Single_Programmable_Empty_Threshold_Constant} \
   CONFIG.Programmable_Full_Type {Multiple_Programmable_Full_Threshold_Constants} \
   CONFIG.Read_Data_Count {true} \
   CONFIG.Read_Data_Count_Width {9} \
   CONFIG.Reset_Type {Asynchronous_Reset} \
   CONFIG.Use_Embedded_Registers {true} \
   CONFIG.Use_Extra_Logic {false} \
   CONFIG.Write_Data_Count {true} \
   CONFIG.Write_Data_Count_Width {10} \
   CONFIG.synchronization_stages {4} \
 ] $CAM_pdata_sync_FIFO

  # Create instance: LCD_pdata_FIFO, and set properties
  set LCD_pdata_FIFO [ create_bd_cell -type ip -vlnv xilinx.com:ip:fifo_generator:13.2 LCD_pdata_FIFO ]
  set_property -dict [ list \
   CONFIG.Empty_Threshold_Assert_Value {100} \
   CONFIG.Empty_Threshold_Negate_Value {101} \
   CONFIG.Enable_Safety_Circuit {true} \
   CONFIG.Fifo_Implementation {Independent_Clocks_Block_RAM} \
   CONFIG.Full_Flags_Reset_Value {1} \
   CONFIG.Full_Threshold_Assert_Value {500} \
   CONFIG.Full_Threshold_Negate_Value {499} \
   CONFIG.Input_Data_Width {32} \
   CONFIG.Output_Data_Width {16} \
   CONFIG.Output_Depth {2048} \
   CONFIG.Programmable_Empty_Type {Single_Programmable_Empty_Threshold_Constant} \
   CONFIG.Programmable_Full_Type {Single_Programmable_Full_Threshold_Constant} \
   CONFIG.Read_Data_Count_Width {11} \
   CONFIG.Reset_Type {Asynchronous_Reset} \
   CONFIG.Use_Extra_Logic {false} \
   CONFIG.Write_Data_Count {true} \
   CONFIG.Write_Data_Count_Width {10} \
 ] $LCD_pdata_FIFO

  # Create instance: SYS_clk_GEN, and set properties
  set SYS_clk_GEN [ create_bd_cell -type ip -vlnv xilinx.com:ip:clk_wiz:6.0 SYS_clk_GEN ]
  set_property -dict [ list \
   CONFIG.CLKOUT1_JITTER {130.958} \
   CONFIG.CLKOUT1_PHASE_ERROR {98.575} \
   CONFIG.CLKOUT2_JITTER {165.726} \
   CONFIG.CLKOUT2_PHASE_ERROR {98.575} \
   CONFIG.CLKOUT2_REQUESTED_OUT_FREQ {33.333} \
   CONFIG.CLKOUT2_USED {true} \
   CONFIG.CLK_IN1_BOARD_INTERFACE {sys_clock} \
   CONFIG.CLK_OUT1_PORT {PL_clk_out} \
   CONFIG.CLK_OUT2_PORT {LCD_clk_out} \
   CONFIG.MMCM_CLKFBOUT_MULT_F {10.000} \
   CONFIG.MMCM_CLKOUT0_DIVIDE_F {10.000} \
   CONFIG.MMCM_CLKOUT1_DIVIDE {30} \
   CONFIG.NUM_OUT_CLKS {2} \
   CONFIG.USE_BOARD_FLOW {true} \
 ] $SYS_clk_GEN

  # Create port connections
  connect_bd_net -net CAM_mclk_GEN_CAM_mclk [get_bd_pins CAM_mclk_GEN/CAM_mclk] [get_bd_pins CAM_pdata_sync_FIFO/rd_clk] [get_bd_pins CAM_pdata_sync_FIFO/wr_clk] [get_bd_pins LCD_pdata_FIFO/rd_clk] [get_bd_pins LCD_pdata_FIFO/wr_clk]
  connect_bd_net -net reset_rtl_0_1 [get_bd_ports reset_rtl_0] [get_bd_pins SYS_clk_GEN/reset]
  connect_bd_net -net reset_rtl_1 [get_bd_ports reset_rtl] [get_bd_pins CAM_mclk_GEN/reset]
  connect_bd_net -net sys_clock_1 [get_bd_ports sys_clock] [get_bd_pins CAM_mclk_GEN/clk_in1] [get_bd_pins SYS_clk_GEN/clk_in1]

  # Create address segments


  # Restore current instance
  current_bd_instance $oldCurInst

  validate_bd_design
  save_bd_design
}
# End of create_root_design()


##################################################################
# MAIN FLOW
##################################################################

create_root_design ""


