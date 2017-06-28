#include "sensor-driver.h"
#include "at25dfx.h"

void sensor_initialize (uint8_t size)
{
	sensor_data.sampled_data = (uint8_t*)malloc(sizeof(uint8_t) * size);
	sensor_data.next_sample_index = 0;
	sensor_data.buffer_size = size;
	flash_memory_init();
}

uint16_t get_sample_mean ()
{
	uint16_t value = 0;
	int i;
	for (i = 0; i < sensor_data.buffer_size; i++)
	{
		value += sensor_data.sampled_data[i];
	}
	return value / sensor_data.buffer_size;
}

void sensor_add_sampled_data (uint16_t data)
{
	sensor_data.sampled_data[sensor_data.next_sample_index] = sensor_clamp_sampled_value (data);
	sensor_data.last_sampled_value = data;
	sensor_data.next_sample_index = (sensor_data.next_sample_index + 1) % sensor_data.buffer_size;
}

void sensor_write_to_memory ()
{
	uint8_t buffer[2];
	uint16_t mean = get_sample_mean();
	buffer[0] = (uint8_t)(mean >> 8);
	buffer[1] = (uint8_t)(mean);
	flash_memory_write(MEMORY_READ_ADDRESS, buffer, 2);
	DBG_LOG ("Writing sample mean '%d' in memory.", mean);
}

int sensor_clamp_sampled_value (int value)
{
	if (value < MIN_VALUE)
	{
		value = MIN_VALUE;
	}	
	else if (value > MAX_VALUE)
	{
		value = MAX_VALUE;
	}
	return value;
}

float sensor_inverse_lerp (int value)
{
	return (value - MIN_VALUE) / (float)(MAX_VALUE - MIN_VALUE);
}

void sensor_read_from_memory()
{
	uint8_t data[2];
	flash_memory_read(MEMORY_READ_ADDRESS, data, 2);
	sensor_data.read_mean_value = data[0] << 8 | data[1];
	DBG_LOG ("Last mean value was %d.", sensor_data.read_mean_value);
}