#ifndef adc_driver_h
#define adc_driver_h
#endif

#include "ASF/sam0/drivers/adc/adc.h"

/**
*	\file adc_driver.h
*	\brief Contains functions to initialize and sample ADC data.	
**/

/**	@fn adc_module *adc_initialize (adc_resolution sampling_res, bool initialize);
 *  @brief Initializes the adc converter.
 *
 * Initializes the adc converter with the given sampling parameter.
 *
 * @param sampling_res The sampling resolution of the conversion.
 * @param initialize If true, the module will be initialized now. Otherwise, initialization must be done manually.
 * @return Returns the adc_module instance.
 **/
struct adc_module *adc_initialize (enum adc_resolution sampling_res, bool initialize);


/**	@fn void adc_get_data (adc_module *module, uint16_t *value);
 *  @brief Samples the data from the ADC.
 *
 * Samples the data from the ADC.
 *
 * @param module The module from which the data is being sampled.
 * @sa adc_module *adc_initialize (adc_resolution sampling_res, bool initialize);
 * @return Returns the sampled data.
 **/
uint16_t adc_get_data (struct adc_module *module);