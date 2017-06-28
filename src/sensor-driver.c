#include "sensor-driver.h"
#include "at25dfx.h"

void sensor_initialize (uint8_t size)
{
	sensor_data.sampled_data = (uint8_t*)malloc(sizeof(uint8_t) * size);
	sensor_data.next_sample_index = 0;
	sensor_data.buffer_size = size;
	flash_memory_init();
}

void sensor_add_sampled_data (uint16_t data)
{
	sensor_data.sampled_data[sensor_data.next_sample_index] = data;
	sensor_data.last_sampled_value = data;
	sensor_data.next_sample_index = (sensor_data.next_sample_index + 1) % sensor_data.buffer_size;
}

void sensor_write_to_memory ()
{
	uint8_t buffer[2];
	sensor_data.last_sampled_value = 25000;
	buffer[0] = (uint8_t)(sensor_data.last_sampled_value >> 8);
	buffer[1] = (uint8_t)(sensor_data.last_sampled_value);
	flash_memory_write(MEMORY_READ_ADDRESS, buffer, 2);
	DBG_LOG ("Writing %d.", sensor_data.last_sampled_value);
}

void sensor_read_from_memory()
{
	uint8_t data[2];
	flash_memory_read(MEMORY_READ_ADDRESS, data, 2);
	DBG_LOG ("data = %d and %d", data[0], data[1]);
	uint16_t value = data[0] << 8 | data[1];
	sensor_data.last_sampled_value = value;
	DBG_LOG("Last sampled value was: %d", value);
}