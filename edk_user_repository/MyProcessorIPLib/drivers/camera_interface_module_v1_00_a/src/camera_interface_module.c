/*****************************************************************************
* Filename:          /home/marco/xilinx/14.3/ISE_DS/edk_user_repository/MyProcessorIPLib/drivers/camera_interface_module_v1_00_a/src/camera_interface_module.c
* Version:           1.00.a
* Description:       camera_interface_module Driver Source File
* Date:              Wed Jan 16 11:19:55 2013 (by Create and Import Peripheral Wizard)
*****************************************************************************/


/***************************** Include Files *******************************/

#include "camera_interface_module.h"

/************************** Function Definitions ***************************/


/**
 *
 * User logic master module to send/receive bytes to/from remote system memory.
 * While sending, the bytes are read from user logic local FIFO and write to remote system memory.
 * While receiving, the bytes are read from remote system memory and write to user logic local FIFO.
 *
 * @param   BaseAddress is the base address of the CAMERA_INTERFACE_MODULE device.
 * @param   DstAddress is the destination system memory address from/to which the data will be fetched/stored.
 * @param   Size is the number of bytes to be sent.
 *
 * @return  None.
 *
 * @note    None.
 *
 */
void CAMERA_INTERFACE_MODULE_MasterSendByte(Xuint32 BaseAddress, Xuint32 DstAddress, int Size)
{
  /*
   * Set user logic master control register for write transfer.
   */
  xil_io_out8(BaseAddress+CAMERA_INTERFACE_MODULE_MST_CNTL_REG_OFFSET, MST_SGWR);

  /*
   * Set user logic master address register to drive IP2Bus_Mst_Addr signal.
   */
  Xil_Out32(BaseAddress+CAMERA_INTERFACE_MODULE_MST_ADDR_REG_OFFSET, DstAddress);

  /*
   * Set user logic master byte enable register to drive IP2Bus_Mst_BE signal.
   */
  xil_io_out16(BaseAddress+CAMERA_INTERFACE_MODULE_MST_BE_REG_OFFSET, 0xFFFF);

  /*
   * Set user logic master length register.
   */
  xil_io_out16(BaseAddress+CAMERA_INTERFACE_MODULE_MST_LEN_REG_OFFSET, (Xuint16) Size);
  /*
   * Start user logic master write transfer by writting special pattern to its go port.
   */
  xil_io_out8(BaseAddress+CAMERA_INTERFACE_MODULE_MST_GO_PORT_OFFSET, MST_START);
}

void CAMERA_INTERFACE_MODULE_MasterRecvByte(Xuint32 BaseAddress, Xuint32 DstAddress, int Size)
{
  /*
   * Set user logic master control register for read transfer.
   */
  xil_io_out8(BaseAddress+CAMERA_INTERFACE_MODULE_MST_CNTL_REG_OFFSET, MST_SGRD);

  /*
   * Set user logic master address register to drive IP2Bus_Mst_Addr signal.
   */
  Xil_Out32(BaseAddress+CAMERA_INTERFACE_MODULE_MST_ADDR_REG_OFFSET, DstAddress);

  /*
   * Set user logic master byte enable register to drive IP2Bus_Mst_BE signal.
   */
  xil_io_out16(BaseAddress+CAMERA_INTERFACE_MODULE_MST_BE_REG_OFFSET, 0xFFFF);

  /*
   * Set user logic master length register.
   */
  xil_io_out16(BaseAddress+CAMERA_INTERFACE_MODULE_MST_LEN_REG_OFFSET, (Xuint16) Size);
  /*
   * Start user logic master read transfer by writting special pattern to its go port.
   */
  xil_io_out8(BaseAddress+CAMERA_INTERFACE_MODULE_MST_GO_PORT_OFFSET, MST_START);
}

