#include "sensor-driver.h"
#include "at25dfx.h"

void sensor_initialize (uint8_t size)
{
	sensor_data.sampled_data = (uint16_t*)malloc(sizeof(uint16_t) * size);
	sensor_data.next_sample_index = 0;
	sensor_data.buffer_size = size;
}

void sensor_add_sampled_data (uint16_t data)
{
	sensor_data.sampled_data[sensor_data.next_sample_index] = data;
	sensor_data.last_sampled_value = data;
	sensor_data.next_sample_index = (sensor_data.next_sample_index + 1) % sensor_data.buffer_size;
}
