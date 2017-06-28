#include "adc_driver.h"

struct adc_module *adc_initialize (enum adc_resolution sampling_res, bool initialize)
{
	struct adc_config config_adc; 
	struct adc_module *module = malloc(sizeof(struct adc_module));
	adc_get_config_defaults(&config_adc);
	config_adc.resolution = sampling_res;
	adc_init(module, ADC, &config_adc);
	if (initialize)
	{
		adc_enable(module);
	}
	return module;
}

void adc_get_data (struct adc_module *module, uint16_t *value)
{
	adc_start_conversion (module);
	while (adc_read(module, value) == STATUS_BUSY);
}