/*
 * camera_tools.c
 *
 *  Created on: Feb 27, 2013
 *      Author: marco
 */

#include "camera_tools.h"

#include "xparameters.h"


//-----------------------------------------------------------------------------
//send go signal to camera interface
int start_get_frame(void* target_buffer){
	    // 1. write 0x40 to the control register
	    CAMERA_INTERFACE_MODULE_mWriteReg(
	    		XPAR_CAMERA_INTERFACE_MODULE_0_BASEADDR,
	    		CAMERA_INTERFACE_MODULE_MST_CNTL_REG_OFFSET,
	    		MST_SGWR
	    );

	    // 2. write the target address to the address register
	    CAMERA_INTERFACE_MODULE_mWriteReg(
	        		XPAR_CAMERA_INTERFACE_MODULE_0_BASEADDR,
	        		CAMERA_INTERFACE_MODULE_MST_ADDR_REG_OFFSET,
	        		target_buffer
	    );

	    // 3. write valid byte lane value to the be register
	    CAMERA_INTERFACE_MODULE_mWriteReg(
	        		XPAR_CAMERA_INTERFACE_MODULE_0_BASEADDR,
	        		CAMERA_INTERFACE_MODULE_MST_BE_REG_OFFSET,
	        		0xffff
	    );

	    // 4. write 0x0004 to the length register
	    CAMERA_INTERFACE_MODULE_mWriteReg(
	        		XPAR_CAMERA_INTERFACE_MODULE_0_BASEADDR,
	        		CAMERA_INTERFACE_MODULE_MST_LEN_REG_OFFSET,
	        		1
	    );
	    // 5. write 0x0a to the go register, this will start the master write operation
	    CAMERA_INTERFACE_MODULE_mWriteReg(
	        		XPAR_CAMERA_INTERFACE_MODULE_0_BASEADDR,
	        		CAMERA_INTERFACE_MODULE_MST_GO_PORT_OFFSET,
	        		MST_START
	    );

	return 0;
}

//-----------------------------------------------------------------------------
int camera_interface_module_ready(void){
	return 0!= CAMERA_INTERFACE_MODULE_mReadSlaveReg0(XPAR_CAMERA_INTERFACE_MODULE_0_BASEADDR, 0);
}


//-----------------------------------------------------------------------------
int camera_interface_module_wait_ready(void) {
	while (camera_interface_module_ready()==0);
	return 0;
}
