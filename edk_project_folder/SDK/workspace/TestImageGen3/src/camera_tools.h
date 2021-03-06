/*
 * camera_tools.h
 *
 *  Created on: Feb 27, 2013
 *      Author: marco
 */

#ifndef CAMERA_TOOLS_H_
#define CAMERA_TOOLS_H_


#include "camera_interface_module.h"


#define CAMERA_INTERFACE_MODULE_GET_TARGET_ADDRESS \
	CAMERA_INTERFACE_MODULE_mReadReg(XPAR_CAMERA_INTERFACE_MODULE_0_BASEADDR, CAMERA_INTERFACE_MODULE_SLV_REG1_OFFSET)


#define CAMERA_INTERFACE_MODULE_GET_OUTPUT_DATA \
	CAMERA_INTERFACE_MODULE_mReadReg(XPAR_CAMERA_INTERFACE_MODULE_0_BASEADDR, CAMERA_INTERFACE_MODULE_SLV_REG2_OFFSET)

#define CAMERA_INTERFACE_MODULE_GET_MST_IP2BUS_ADDR \
	CAMERA_INTERFACE_MODULE_mReadReg(XPAR_CAMERA_INTERFACE_MODULE_0_BASEADDR, CAMERA_INTERFACE_MODULE_SLV_REG3_OFFSET)


#define CAMERA_INTERFACE_MODULE_GET_MST_CMD_SM_IP2BUS_ADDR \
	CAMERA_INTERFACE_MODULE_mReadReg(XPAR_CAMERA_INTERFACE_MODULE_0_BASEADDR, CAMERA_INTERFACE_MODULE_SLV_REG4_OFFSET)

//-----------------------------------------------------------------------------
/**
 * sends the go signal to the camera interface module.
 * camera interface module then starts to store one frame into the given buffer address.
 */
int start_get_frame(void * target_buffer);


//-----------------------------------------------------------------------------
/**
 * checks if the camera_interface_module finished storing
 * the frame in the buffer started by start_get_frame
 * return true if finished, else false
 *
 */
int camera_interface_module_ready(void);


//-----------------------------------------------------------------------------
/**
 * blocks until the camera interface module finished storing
 * the frame in the buffer started by start_get_frame
 */
int camera_interface_module_wait_ready(void);


//-----------------------------------------------------------------------------
#endif /* CAMERA_TOOLS_H_ */
