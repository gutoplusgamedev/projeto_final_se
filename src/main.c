/**
 * \file
 *
 * \brief Custom Serial Chat Application declarations
 *
 * Copyright (c) 2016 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel micro controller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */

/**
 * \mainpage
 * \section preface Preface
 * This is the reference manual for the Custom Serial Chat Application declarations
 */
/*- Includes -----------------------------------------------------------------------*/
#include <asf.h>
#include "platform.h"
#include "console_serial.h"
#include "at_ble_api.h"
#include "ble_manager.h"
#include "main.h"
#include "ble_profile.h"
#include "ble_service.h"
#include "conf_extint.h"
#include "sio2host.h"  
#include "adc_driver.h"
#include "sensor-driver.h"

/* =========================== GLOBALS ============================================================ */

/* Received notification data structure */
csc_report_ntf_t recv_ntf_info;

/* Data length to be send over the air */
uint16_t send_length = 0;

/* Buffer data to be send over the air */
uint8_t send_data[APP_TX_BUF_SIZE];


static const ble_event_callback_t app_gap_handle[] = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	app_connected_event_handler,
	app_disconnected_event_handler,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL
};

/**
* @brief app_connected_state blemanager notifies the application about state
* @param[in] at_ble_connected_t
*/
static at_ble_status_t app_connected_event_handler(void *params)
{
	ALL_UNUSED(params);
	return AT_BLE_SUCCESS;
}

/**
 * @brief app_connected_state ble manager notifies the application about state
 * @param[in] connected
 */
static at_ble_status_t app_disconnected_event_handler(void *params)
{
		/* Started advertisement */
		ble_profile_start_advertising();		
		ALL_UNUSED(params);
		return AT_BLE_SUCCESS;
}

/* Function used for receive data */
static void csc_app_recv_buf(uint8_t *recv_data, uint8_t recv_len)
{
	uint16_t ind = 0;
	if (recv_len){
		for (ind = 0; ind < recv_len; ind++){
			sio2host_putchar(recv_data[ind]);
		}
		DBG_LOG("\r\n");
	}
}

/* Callback called for new data from remote device */
static void csc_prf_report_ntf_cb(csc_report_ntf_t *report_info)
{
	DBG_LOG("\r\n");
	csc_app_recv_buf(report_info->recv_buff, report_info->recv_buff_len);
}

#define BLE_BUFFER_SIZE 50

#define SAMPLED_DATA_AMOUNT 10

char ble_buffer[BLE_BUFFER_SIZE];
uint16_t current_sampled_value;

int main(void )
{
#if SAMG55 || SAM4S
	/* Initialize the SAM system. */
	sysclk_init();
	board_init();
#elif SAM0
	system_init();
#endif
	
	/* Initialize serial console */
	sio2host_init();
	
	struct adc_module *module = adc_initialize (ADC_RESOLUTION_16BIT, true);

	sensor_initialize(SAMPLED_DATA_AMOUNT);

	DBG_LOG("Initializing...");
	
	/* Initialize the buffer address and buffer length based on user input */
	ble_initialize_data_buffer(&send_data[0], APP_TX_BUF_SIZE);
	
	/* initialize the ble chip  and Set the device mac address */
	ble_device_init(NULL);
	
	/* Initializing the profile */
	ble_profile_initialize(NULL);
	
	/* Started advertisement */
	ble_profile_start_advertising();
	
	ble_mgr_events_callback_handler(REGISTER_CALL_BACK, BLE_GAP_EVENT_TYPE, app_gap_handle);
	
	/* Register the notification handler */
	notify_recv_ntf_handler(csc_prf_report_ntf_cb);
	
	/* Capturing the events  */
	while(true)
	{
		//Handle BLE related events.
		ble_event_task();
		sensor_add_sampled_data(adc_get_data(module));
		//Get the buffer zeroed and copy formatted data into it.
		bzero(ble_buffer, BLE_BUFFER_SIZE);
		sprintf(ble_buffer, "Current measured luminosity: %d.", sensor_data.last_sampled_value);
		//Broadcast data.
		ble_service_send_data(ble_profile_data.conn_params.handle, ble_buffer, BLE_BUFFER_SIZE);	
	}
	return 0;
}



