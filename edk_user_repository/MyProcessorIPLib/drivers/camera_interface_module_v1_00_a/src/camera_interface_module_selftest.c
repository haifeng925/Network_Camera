/*****************************************************************************
* Filename:          /home/marco/xilinx/14.3/ISE_DS/edk_user_repository/MyProcessorIPLib/drivers/camera_interface_module_v1_00_a/src/camera_interface_module_selftest.c
* Version:           1.00.a
* Description:       Contains a diagnostic self-test function for the camera_interface_module driver
* Date:              Wed Jan 16 11:19:55 2013 (by Create and Import Peripheral Wizard)
*****************************************************************************/


/***************************** Include Files *******************************/

#include "camera_interface_module.h"

/************************** Constant Definitions ***************************/

#define CAMERA_INTERFACE_MODULE_SELFTEST_BUFSIZE  4   /* Size of buffer (for transfer test) in bytes */

/************************** Variable Definitions ****************************/

static Xuint8 __attribute__((aligned (128))) SrcBuffer[CAMERA_INTERFACE_MODULE_SELFTEST_BUFSIZE];   /* Source buffer      */
static Xuint8 __attribute__((aligned (128))) DstBuffer[CAMERA_INTERFACE_MODULE_SELFTEST_BUFSIZE];   /* Destination buffer */

/************************** Function Definitions ***************************/

/**
 *
 * Run a self-test on the driver/device. Note this may be a destructive test if
 * resets of the device are performed.
 *
 * If the hardware system is not built correctly, this function may never
 * return to the caller.
 *
 * @param   baseaddr_p is the base address of the CAMERA_INTERFACE_MODULE instance to be worked on.
 *
 * @return
 *
 *    - XST_SUCCESS   if all self-test code passed
 *    - XST_FAILURE   if any self-test code failed
 *
 * @note    Caching must be turned off for this function to work.
 * @note    Self test may fail if data memory and device are not on the same bus.
 *
 */
XStatus CAMERA_INTERFACE_MODULE_SelfTest(void * baseaddr_p)
{
  int     Index;
  Xuint32 baseaddr;
  Xuint8  Reg8Value;
  Xuint16 Reg16Value;
  Xuint32 Reg32Value;
  
  /*
   * Check and get the device address
   */
  /*
   * Base Address maybe 0. Up to developer to uncomment line below.
  XASSERT_NONVOID(baseaddr_p != XNULL);
   */
  baseaddr = (Xuint32) baseaddr_p;

  xil_printf("******************************\n\r");
  xil_printf("* User Peripheral Self Test\n\r");
  xil_printf("******************************\n\n\r");

  /*
   * Write to user logic slave module register(s) and read back
   */
  xil_printf("User logic slave module test...\n\r");
  xil_printf("   - write 1 to slave register 0 word 0\n\r");
  CAMERA_INTERFACE_MODULE_mWriteSlaveReg0(baseaddr, 0, 1);
  Reg32Value = CAMERA_INTERFACE_MODULE_mReadSlaveReg0(baseaddr, 0);
  xil_printf("   - read %d from register 0 word 0\n\r", Reg32Value);
  if ( Reg32Value != (Xuint32) 1 )
  {
    xil_printf("   - slave register 0 word 0 write/read failed\n\r");
    return XST_FAILURE;
  }
  xil_printf("   - write 2 to slave register 1 word 0\n\r");
  CAMERA_INTERFACE_MODULE_mWriteSlaveReg1(baseaddr, 0, 2);
  Reg32Value = CAMERA_INTERFACE_MODULE_mReadSlaveReg1(baseaddr, 0);
  xil_printf("   - read %d from register 1 word 0\n\r", Reg32Value);
  if ( Reg32Value != (Xuint32) 2 )
  {
    xil_printf("   - slave register 1 word 0 write/read failed\n\r");
    return XST_FAILURE;
  }
  xil_printf("   - write 3 to slave register 2 word 0\n\r");
  CAMERA_INTERFACE_MODULE_mWriteSlaveReg2(baseaddr, 0, 3);
  Reg32Value = CAMERA_INTERFACE_MODULE_mReadSlaveReg2(baseaddr, 0);
  xil_printf("   - read %d from register 2 word 0\n\r", Reg32Value);
  if ( Reg32Value != (Xuint32) 3 )
  {
    xil_printf("   - slave register 2 word 0 write/read failed\n\r");
    return XST_FAILURE;
  }
  xil_printf("   - write 4 to slave register 3 word 0\n\r");
  CAMERA_INTERFACE_MODULE_mWriteSlaveReg3(baseaddr, 0, 4);
  Reg32Value = CAMERA_INTERFACE_MODULE_mReadSlaveReg3(baseaddr, 0);
  xil_printf("   - read %d from register 3 word 0\n\r", Reg32Value);
  if ( Reg32Value != (Xuint32) 4 )
  {
    xil_printf("   - slave register 3 word 0 write/read failed\n\r");
    return XST_FAILURE;
  }
  xil_printf("   - write 5 to slave register 4 word 0\n\r");
  CAMERA_INTERFACE_MODULE_mWriteSlaveReg4(baseaddr, 0, 5);
  Reg32Value = CAMERA_INTERFACE_MODULE_mReadSlaveReg4(baseaddr, 0);
  xil_printf("   - read %d from register 4 word 0\n\r", Reg32Value);
  if ( Reg32Value != (Xuint32) 5 )
  {
    xil_printf("   - slave register 4 word 0 write/read failed\n\r");
    return XST_FAILURE;
  }
  xil_printf("   - write 6 to slave register 5 word 0\n\r");
  CAMERA_INTERFACE_MODULE_mWriteSlaveReg5(baseaddr, 0, 6);
  Reg32Value = CAMERA_INTERFACE_MODULE_mReadSlaveReg5(baseaddr, 0);
  xil_printf("   - read %d from register 5 word 0\n\r", Reg32Value);
  if ( Reg32Value != (Xuint32) 6 )
  {
    xil_printf("   - slave register 5 word 0 write/read failed\n\r");
    return XST_FAILURE;
  }
  xil_printf("   - write 7 to slave register 6 word 0\n\r");
  CAMERA_INTERFACE_MODULE_mWriteSlaveReg6(baseaddr, 0, 7);
  Reg32Value = CAMERA_INTERFACE_MODULE_mReadSlaveReg6(baseaddr, 0);
  xil_printf("   - read %d from register 6 word 0\n\r", Reg32Value);
  if ( Reg32Value != (Xuint32) 7 )
  {
    xil_printf("   - slave register 6 word 0 write/read failed\n\r");
    return XST_FAILURE;
  }
  xil_printf("   - write 8 to slave register 7 word 0\n\r");
  CAMERA_INTERFACE_MODULE_mWriteSlaveReg7(baseaddr, 0, 8);
  Reg32Value = CAMERA_INTERFACE_MODULE_mReadSlaveReg7(baseaddr, 0);
  xil_printf("   - read %d from register 7 word 0\n\r", Reg32Value);
  if ( Reg32Value != (Xuint32) 8 )
  {
    xil_printf("   - slave register 7 word 0 write/read failed\n\r");
    return XST_FAILURE;
  }
  xil_printf("   - slave register write/read passed\n\n\r");

  /*
   * Setup user logic master module to receive/send data from/to remote memory
   */
  xil_printf("User logic master module test...\n\r");
  xil_printf("   - source buffer address is 0x%08x\n\r", SrcBuffer);
  xil_printf("   - destination buffer address is 0x%08x\n\r", DstBuffer);
  xil_printf("   - initialize the source buffer bytes with a pattern\n\r");
  xil_printf("   - initialize the destination buffer bytes to zero\n\r");
  for ( Index = 0; Index < CAMERA_INTERFACE_MODULE_SELFTEST_BUFSIZE; Index++ )
  {
    SrcBuffer[Index] = Index;
    DstBuffer[Index] = 0;
  }
  xil_printf("   - start user logic master module to receive bytes from the source\n\r");
  CAMERA_INTERFACE_MODULE_MasterRecvByte(baseaddr, (Xuint32) SrcBuffer, CAMERA_INTERFACE_MODULE_SELFTEST_BUFSIZE);
  while ( ! CAMERA_INTERFACE_MODULE_mMasterDone(baseaddr) ) {}
  xil_printf("   - transfer completed\n\r");
  xil_printf("   - start user logic master module to send bytes to the destination\n\r");
  CAMERA_INTERFACE_MODULE_MasterSendByte(baseaddr, (Xuint32) DstBuffer, CAMERA_INTERFACE_MODULE_SELFTEST_BUFSIZE);
  while ( ! CAMERA_INTERFACE_MODULE_mMasterDone(baseaddr) ) {}
  xil_printf("   - transfer completed\n\r");
  for ( Index = 0; Index < CAMERA_INTERFACE_MODULE_SELFTEST_BUFSIZE; Index++ )
  {
    if ( DstBuffer[Index] != SrcBuffer[Index] )
    {
      xil_printf("   - destination buffer byte %d is different from the source buffer\n\r", Index);
      xil_printf("   - master module data transfer failed\n\r");
      return XST_FAILURE;
    }
  }
  xil_printf("   - destination buffer's contents are same as the source buffer\n\r");
  xil_printf("   - master module data transfer passed\n\n\r");

  return XST_SUCCESS;
}
