
/**
 * \file
 *
 * \brief Custom Serial Chat Service Declarations
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
// =======================
#ifndef __BLE_SERVICE_H__
#define __BLE_SERVICE_H__

/****************************************************************************************
*							        Macros	                                     		*
****************************************************************************************/
/** @brief Custom serial chat UUID length */
#define CSC_UUID_128_LEN				(16)

/****************************************************************************************
*							        Structures                                     		*
****************************************************************************************/
/** @brief Custom serial chat service info */
typedef struct ble_service
{
	at_ble_uuid_t	serv_uuid; 
	at_ble_handle_t	serv_handle; 
	at_ble_characteristic_t	endpoint_characteristics;  
}ble_service;

/**	@fn at_ble_status_t ble_service_initialize(uint8_t *buf, uint16_t len);
 *  @brief Initializes the bluetooth service at a pre-defined service UUID.
 * @param buf The starting characteristic's data.
 * @param len The size of the characteristic's buffer.
 * @return Returns AT_BLE_SUCCESS if succeeded. Error code otherwise.
 **/
at_ble_status_t ble_service_initialize(uint8_t *buf, uint16_t len);

/**	@fn at_ble_status_t ble_service_send_data(uint16_t connhandle, uint8_t *databuf, uint16_t datalen);
 *  @brief Sends data through a pre-established service.
 * @param connhandle The handle of the connection to which the data is going to be sent.
 * @param databuff The data to be sent.
 * @param datalen The size of the buffer to be sent.
 * @return Returns AT_BLE_SUCCESS if succeeded. Error code otherwise.
 **/
at_ble_status_t ble_service_send_data(uint16_t connhandle, uint8_t *databuf, uint16_t datalen);


#endif
// </h>

// <<< end of configuration section >>>
