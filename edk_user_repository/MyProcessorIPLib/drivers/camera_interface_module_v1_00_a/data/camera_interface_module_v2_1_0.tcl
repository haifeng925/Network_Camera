##############################################################################
## Filename:          /home/marco/xilinx/14.3/ISE_DS/edk_user_repository/MyProcessorIPLib/drivers/camera_interface_module_v1_00_a/data/camera_interface_module_v2_1_0.tcl
## Description:       Microprocess Driver Command (tcl)
## Date:              Wed Jan 16 11:19:55 2013 (by Create and Import Peripheral Wizard)
##############################################################################

#uses "xillib.tcl"

proc generate {drv_handle} {
  xdefine_include_file $drv_handle "xparameters.h" "camera_interface_module" "NUM_INSTANCES" "DEVICE_ID" "C_BASEADDR" "C_HIGHADDR" 
}
