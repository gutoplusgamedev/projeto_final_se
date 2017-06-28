/**
 * \file
 *
 * \brief  Custom Serial Chat Profile
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
 *    Atmel microcontroller product.
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

/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel
 *Support</a>
 */

// <<< Use Configuration Wizard in Context Menu >>>
// <h> Custom Serial Chat Profile Configuration
// =======================
#ifndef __BLE_PROFILE_H__
#define __BLE_PROFILE_H__
#include "at_ble_api.h"

/****************************************************************************************
*							        Macros	                                     		*
****************************************************************************************/

/** @brief APP_SPOG_FAST_ADV between 0x0020 and 0x4000 in 0.625 ms units (20ms to 10.24s). */
//	<o> Fast Advertisement Interval <100-1000:50>
//	<i> Defines inteval of Fast advertisement in ms.
//	<i> Default: 100
//	<id> csc_fast_adv
#define APP_CSC_FAST_ADV				(1600) //1000 ms

/** @brief APP_CSC_ADV_TIMEOUT Advertising time-out between 0x0001 and 0x028F in 
 *seconds, 0x0000 disables time-out.*/
//	<o> Advertisement Timeout <1-655>
//	<i> Defines interval at which advertisement timeout in sec.
//	<i> Default: 655
//	<id> csc_adv_timeout
#define APP_CSC_ADV_TIMEOUT				(655) // 10 min

/** @brief scan_resp_len is the length of the scan response data */
//	<o> Scan Response Buffer <1-20>
//	<i> Defines size of buffer for scan response.
//	<i> Default: 10
//	<id> csc_scan_resp_len
#define SCAN_RESP_LEN					(10)

/** @brief Advertisement appearance type  */
#define ADV_DATA_APPEARANCE_TYPE		(0x19)

/** @brief Advertisement data name length  */
#define ADV_DATA_NAME_LEN				(6)

/** @brief Advertisement data type */
#define ADV_DATA_NAME_TYPE				(0x09)

/** @brief Advertisement name */
//	<s.9>	Advertising String
//	<i>	String Descriptor describing in advertising packet.
//	<id> cscp_adv_data_name_data
#define ADV_DATA_NAME_DATA				("AT-CSC")

/** @brief Advertisement type length */
#define ADV_TYPE_LEN					(0x01)

/** @brief Advertisement 128bit UUID type */
#define ADV_DATA_128_UUID_TYPE		    (0x07)

/** @brief Custom serial chat UUID length */
#define CSC_UUID_128_LEN				(16)

/** @brief Discovery sucess status */
#define AT_DISCOVER_SUCCESS				(10)

/**@brief start and end handle */
#define START_HANDLE					(0x0001)
#define END_HANDLE						(0xffff)


/****************************************************************************************
*							        Enumerations	                                   	*
****************************************************************************************/
/**@brief type of attribute discovery */
typedef enum
{
	/// Discovery Disable
	DISCOVER_IDLE = 0,
	
	/// Discover Service
	DISCOVER_SERVICE,
	
	/// Discover Include Service
	DISCOVER_INCLUDE_SERVICE,
	
	/// Discover Characteristic
	DISCOVER_CHARACTERISTIC,
	
	/// Discover Descriptor
	DISCOVER_DESCRIPTOR,
	
}ble_discovery_role;

/****************************************************************************************
*							        Structures                                     		*
****************************************************************************************/

/* Typedef for csc profile */
typedef struct ble_profile_data_t
{
	/** To check the buffer pointer */
	uint8_t *buff_ptr;
	/** To check the buffer length */
	uint16_t buff_len;
	/** To check the service discovery status */
	uint8_t devicedb;
	/** To check the type of discovery */
	uint8_t discover_role;
	/** Connection related information*/
	at_ble_connected_t conn_params;
	/**Instance for SPOG service*/
	at_ble_primary_service_found_t csc_serv;
	/** Information of characteristics found */
	at_ble_characteristic_found_t csc_char;
	/** Information of descriptor found */
	at_ble_descriptor_found_t csc_desc;
}ble_profile_data_t;

/**@brief SPOG report notification or indication, notify to user. */
typedef struct csc_report_ntf
{
	/**< Received buffer pointer. */
	uint8_t *recv_buff;				
	/**< Received buffer length. */
	uint8_t recv_buff_len;			
	/**< Connection Handle. */
	at_ble_handle_t conn_handle;	
}csc_report_ntf_t;


/*Profile Information*/
ble_profile_data_t ble_profile_data;


/****************************************************************************************
*							        Basic types                                         *
****************************************************************************************/
/**@brief Receive notification callback */
typedef void (*recv_ntf_callback_t)(csc_report_ntf_t *);

/****************************************************************************************
*                                       Functions                                       *
****************************************************************************************/
/**	@fn void ble_initialize_data_buffer(uint8_t *databuf, uint16_t datalen);
 *  @brief Initializes the buffer to be used to broadcast data to BLE.
 * @param databuf The buffer to be initialized.
 * @param datalen The length of the buffer.
 **/
void ble_initialize_data_buffer(uint8_t *databuf, uint16_t datalen);

/**	@fn void ble_profile_initialize(void *param);
 *  @brief Initializes profile and the service.
 *	@sa at_ble_status_t ble_service_initialize(uint8_t *buf, uint16_t len);
 **/
void ble_profile_initialize(void *param);

/**	@fn at_ble_status_t ble_profile_disconnect_handler(void *params);
 *  @brief Handles disconnections.
 **/
at_ble_status_t ble_profile_disconnect_handler(void *params);

/**	@fn void ble_profile_start_advertising(void);
 *  @brief Starts advertising the device, i.e. makes it publicly visible and pairable.
 **/
void ble_profile_start_advertising(void);

/**	@fn at_ble_status_t ble_profile_char_changed_handler(void *params);
 *  @brief Handles characteristic changes, i.e. when the BLE device has transmitted data.
 **/
at_ble_status_t ble_profile_char_changed_handler(void *params);

/**	@fn at_ble_status_t ble_profile_connected_handler(void *params);
 *  @brief Handles connections.
 **/
at_ble_status_t ble_profile_connected_handler(void *params);

/**	@fn at_ble_status_t ble_profile_service_found_handler(void * params);
 *  @brief Called when the device is in the connection process and found a matching service.
 **/
at_ble_status_t ble_profile_service_found_handler(void * params);

/**	@fn at_ble_status_t ble_profile_char_found_handler(void *params);
 *  @brief Called when a characteristic was found during discovery process.
 **/
at_ble_status_t ble_profile_char_found_handler(void *params);

/**	@fn at_ble_status_t ble_profile_descriptor_found_handler(void *params);
 *  @brief Called when a characteristic's descriptor was found during discovery process.
 **/
at_ble_status_t ble_profile_descriptor_found_handler(void *params);

/**	@fn at_ble_status_t ble_profile_discovery_complete_handler(void *params);
 *  @brief Called when discovery is completed. It can be related to service, characteristics or descriptor.
 **/
at_ble_status_t ble_profile_discovery_complete_handler(void *params);

/**	@fn at_ble_status_t ble_profile_notification_handler(void *params);
 *  @brief Called when received a notification from the BLE device. For instance, to let us know a value has changed.
 **/
at_ble_status_t ble_profile_notification_handler(void *params);

/**	@fn at_ble_status_t ble_profile_write_notification_handler(void *params);
 *  @brief Called when we've transmitted a notification.
 **/
at_ble_status_t ble_profile_write_notification_handler(void *params);

/** @brief Function call the user defined callback for sending the receive data
*/
void notify_recv_ntf_handler(recv_ntf_callback_t recv_ntf_fn);

/** @brief Notification confirmation handler
*/

/**	@fn at_ble_status_t ble_profile_notification_confirmation_handler(void *params);
 *  @brief Called when a notification was successfully confirmed by the device.
 **/
at_ble_status_t ble_profile_notification_confirmation_handler(void *params);

#endif
// </h>

// <<< end of configuration section >>>
