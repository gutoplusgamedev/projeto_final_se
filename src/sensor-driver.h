#ifndef SENSOR_DRIVER_H
#define SENSOR_DRIVER_H

#include <asf.h>
#include "memory-driver.h"

#define MEMORY_READ_ADDRESS 0x10000 /*!< The memory adress where sensor data will be written to and read from. */

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

/**	@fn uint16_t get_sample_mean ();
 *  @brief Returns the mean value of the last read samples.
 **/
uint16_t get_sample_mean ();

/**	@fn void sensor_add_sampled_data (uint16_t data);
 *  @brief Adds a sampled data to the buffer. Goes to size - 1 and starts at 0 again (Circular).
 * @param data The value to be added.
 **/
void sensor_add_sampled_data (uint16_t data);

/**	@fn void sensor_write_to_memory ();
 *  @brief Writes current sample mean to memory block starting at MEMORY_READ_ADDRESS address (default 0x10000).
 **/
void sensor_write_to_memory ();

/**	@fn void sensor_read_from_memory ();
 *  @brief Overwrites current sample mean with memory block starting at MEMORY_READ_ADDRESS address (default 0x10000).
 **/
void sensor_read_from_memory ();

#endif