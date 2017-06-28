#include "sensor-driver.h"
#include "at25dfx.h"

void sensor_initialize (uint8_t size)
{
	sensor_data.sampled_data = (uint16_t*)malloc(sizeof(uint16_t) * size);
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
	flash_memory_write(MEMORY_READ_ADDRESS, sensor_data.sampled_data, sensor_data.buffer_size);
}

void sensor_read_from_memory()
{
	flash_memory_read(MEMORY_READ_ADDRESS, sensor_data.sampled_data, sensor_data.buffer_size);
}

void sensor_print_data ()
{
	int i;
	for (i = 0; i < sensor_data.buffer_size; i++)
	{
		DBG_LOG ("sensor_data[%d] = %d.", i, sensor_data.sampled_data[i]);
	}
}