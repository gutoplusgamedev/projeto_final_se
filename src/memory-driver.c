#include "memory-driver.h"

struct spi_module at25dfx_spi;
struct at25dfx_chip_module at25dfx_chip;

void flash_memory_init(void)
{
	struct at25dfx_chip_config at25dfx_chip_conf;
	struct spi_config at25dfx_spi_config;

	spi_get_config_defaults(&at25dfx_spi_config);
	at25dfx_spi_config.mode_specific.master.baudrate = AT25DFX_CLOCK_SPEED;
	at25dfx_spi_config.mux_setting = AT25DFX_SPI_PINMUX_SETTING;
	at25dfx_spi_config.pinmux_pad0 = AT25DFX_SPI_PINMUX_PAD0;
	at25dfx_spi_config.pinmux_pad1 = AT25DFX_SPI_PINMUX_PAD1;
	at25dfx_spi_config.pinmux_pad2 = AT25DFX_SPI_PINMUX_PAD2;
	at25dfx_spi_config.pinmux_pad3 = AT25DFX_SPI_PINMUX_PAD3;

	spi_init(&at25dfx_spi, AT25DFX_SPI, &at25dfx_spi_config);
	spi_enable(&at25dfx_spi);

	at25dfx_chip_conf.type = AT25DFX_MEM_TYPE;
	at25dfx_chip_conf.cs_pin = AT25DFX_CS;

	at25dfx_chip_init(&at25dfx_chip, &at25dfx_spi, &at25dfx_chip_conf);

	DBG_LOG ("Flash memory successfuly initialized.");
}

void flash_memory_read (uint16_t address, uint16_t* target_buffer, uint16_t size)
{
	at25dfx_chip_wake(&at25dfx_chip);
	if (at25dfx_chip_check_presence(&at25dfx_chip) != STATUS_OK) 
	{
		DBG_LOG ("Something is not right with the memory. Could not perform read operation.");
	}
	at25dfx_chip_set_sector_protect(&at25dfx_chip, address, false);
	at25dfx_chip_read_buffer(&at25dfx_chip, address, target_buffer, size);
	at25dfx_chip_set_sector_protect(&at25dfx_chip, address, true);
	at25dfx_chip_sleep(&at25dfx_chip);
}

void flash_memory_write (uint16_t address, uint16_t* source_buffer, uint16_t size)
{
	at25dfx_chip_wake(&at25dfx_chip);
	if (at25dfx_chip_check_presence(&at25dfx_chip) != STATUS_OK)
	{
		DBG_LOG ("Something is not right with the memory. Could not perform write operation.");
	}
	at25dfx_chip_set_sector_protect(&at25dfx_chip, address, false);
	at25dfx_chip_write_buffer(&at25dfx_chip, address, source_buffer, size);
	at25dfx_chip_set_sector_protect(&at25dfx_chip, address, true);
	at25dfx_chip_sleep(&at25dfx_chip);
}