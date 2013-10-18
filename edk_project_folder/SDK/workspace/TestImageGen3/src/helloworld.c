/*
 * Copyright (c) 2009 Xilinx, Inc.  All rights reserved.
 *
 * Xilinx, Inc.
 * XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A
 * COURTESY TO YOU.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
 * ONE POSSIBLE   IMPLEMENTATION OF THIS FEATURE, APPLICATION OR
 * STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION
 * IS FREE FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE
 * FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION.
 * XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO
 * THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO
 * ANY WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE
 * FROM CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

/*
 * helloworld.c: simple test application
 */
#include <stdio.h>

#include "platform.h"
#include "xparameters.h"
#include "camera_interface_module.h"

#include "config.h"
#include "camera_tools.h"
#include "network_tools.h"


#include <xemaclite.h>


void print(char *str);

int test_send_image_over_network() {

	my_xemac_init();

	u16* buff1 = (u16 *)BUFFER_1;
	u16* buff2 = (u16 *)(2+BUFFER_1+(WIDTH*HEIGHT*2));



	u16 color[2] = {0x001f, 0xf800};
	// one static images
	unsigned int i;
	for (i = 0; i< WIDTH*HEIGHT;i++) {
		buff1[i] = color[0]; //rgb565
	}


	//send video stream
	i=1;
	int h;
	while(1) {
		//changing the image base on i
		for(h=0;h<HEIGHT;h++) {
			buff1[h*WIDTH+(i%WIDTH)] = color[0];
			buff1[h*WIDTH+((i+5)%WIDTH)] = color[1];
		}

		//send the image
		send_image_over_network(buff1, i++);

		//xil_printf("pic1 nr: %d\r\n", i);

		i = i%10000; // limits the number of frames in the stream to 100000 and start over again
	}
	return 0;
}
/*
int test_send_itp_packet(){

	// //////////////////////////////////////////////////////
	//test network transmission
	// //////////////////////////////////////////////////////
	int Status;

	Status = my_xemac_init();

	u8 data[8] = {1, 2, 3 ,4, 1, 2, 3, 4};
	ITP_Packet_Header header;
	header.width = 1;
	header.height = 2;
	header.total_packets_per_image = 2;
	header.packet_nr_of_image = 1;
	header.image_data_offset = 0;
	header.data_length = 8;
	header.image_nr = 1;
	send_itp_packet(&header, &data);

	return 0;

}

int test_camera_interface_module () {


	u32 * buff = (u32 *)BUFFER_1;


	buff[0] = 0x44;

	//test camera interface module
	xil_printf("buffer: %d\r\n",buff[0]);

	xil_printf("ready: %x \r\n",camera_interface_module_ready());
	start_get_frame((void *)BUFFER_1);
	xil_printf("GO signal sent. \r\n");

	camera_interface_module_wait_ready();
	xil_printf("finished\r\n");

	int* bus_adr = (int*) CAMERA_INTERFACE_MODULE_GET_MST_CMD_SM_IP2BUS_ADDR;

	xil_printf("MST_IP2BUS_ADDR       : %x\r\n", CAMERA_INTERFACE_MODULE_GET_MST_IP2BUS_ADDR);
	xil_printf("TARGET_ADDRESS        : %x\r\n", CAMERA_INTERFACE_MODULE_GET_TARGET_ADDRESS);
	xil_printf("MST_CMD_SM_IP2BUS_ADDR: %x\r\n", bus_adr);
	xil_printf("OUTPUT_DATA           : %x\r\n\r\n", CAMERA_INTERFACE_MODULE_GET_OUTPUT_DATA);



	return 0;
}
*/
/**
 * This is the function for the final application.
 * It repeats reading the images from the camera and sends them over network.
 * Single/Double buffering can be switched.
 */
int streaming(){

	int single_buffering = 1;
	int frame_number = 1;

	int b; // for switching buffers
	int store_buffer = BUFFER_1;
	int send_buffer = BUFFER_2;

	if (single_buffering) {
		//single buffering
		while(1) {
			start_get_frame((void *)BUFFER_1);
			camera_interface_module_wait_ready();
			send_image_over_network((void*)BUFFER_1, frame_number++);
		}
	} else {
		//dubble buffering
		start_get_frame((void *)store_buffer);
		while(1) {
			camera_interface_module_wait_ready();

			//switch buffers
			b = store_buffer;
			store_buffer = send_buffer;
			send_buffer = b;

			start_get_frame((void *)store_buffer);
			send_image_over_network((void*)send_buffer, frame_number++);
		}
	}
	return 0;
}

int main()
{
	init_platform();

	//streaming
	//test_camera_interface_module();
	//test_send_itp_packet();
	test_send_image_over_network();


	xil_printf("finished\r\n");
	xil_printf("finished\r\n");

    cleanup_platform();

    return 0;
}
