#ifndef SENSOR_DRIVER_H
#define SENSOR_DRIVER_H

#include <asf.h>

/** @struct sensor_data_t
	@brief Structure to hold sampled data.
**/
struct sensor_data_t
{
	uint16_t *sampled_data; /*!< Array of sampled data. */
	uint8_t buffer_size;  /*!< Amount of elements in the array. */
	uint16_t last_sampled_value; /*!< Holds the last value that was added to the 'sampled_data' buffer. */
	uint8_t next_sample_index;
} sensor_data_t;

struct sensor_data_t sensor_data; /*!< Instance to the sensor's data structure. */

/**	@fn void sensor_initialize (uint8_t size);
 *  @brief Initialized the sensor buffer with the given size. 
 * @param size The amount of elements the buffer can fit.
 **/
void sensor_initialize (uint8_t size);

/**	@fn void sensor_add_sampled_data (uint16_t data);
 *  @brief Adds a sampled data to the buffer. Goes to size - 1 and starts at 0 again (Circular).
 * @param data The value to be added.
 **/
void sensor_add_sampled_data (uint16_t data);

#endif