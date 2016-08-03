/*
 * This file is part of the openfat project.
 *
 * Copyright (C) 2011  Department of Physics, University of Otago
 * Written by Gareth McMullin <gareth@blacksphere.co.nz>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* MMC Card interface implementation.
 */


#include <stdint.h>
#include <string.h>

#include "mmc.h"
#include "openfat/leaccess.h"
#include "HW_SPI.h"

#define MMC_SECTOR_SIZE		512

static uint8_t spi_readwrite( uint8_t data)
{
	/*while(SPI_SR(spi) & SPI_SR_BSY);
	SPI_DR(spi) = data;
	while(!(SPI_SR(spi) & SPI_SR_RXNE));
	return SPI_DR(spi);*/
    //SPI_SendByte(data);
    return SPI_RecvByte();
}

static void mmc_select(const struct mmc_port *mmc)
{
	/*gpio_clear(mmc->cs_port, mmc->cs_pin);*/
	/* Wait for not busy */
	//while(spi_readwrite(mmc->spi, 0xFF) == 0);
    ChipSelect();
    SPI_SendByte(0xff);
}

static void mmc_release(const struct mmc_port *mmc)
{
	//gpio_set(mmc->cs_port, mmc->cs_pin);
	/* Must cycle clock 8 times after CS is released */
    ChipDeselect();
	SPI_SendByte( 0xFF);  
}

static void 
mmc_write_buffer(const struct mmc_port *mmc, const uint8_t *buf, int len)
{
	while(len--)
		SPI_SendByte(*buf++);
}

static void 
mmc_read_buffer(const struct mmc_port *mmc, uint8_t *buf, int len)
{
	while(len--)
		*buf++ = SPI_RecvByte();
}

#define TOKEN_START_SINGLE_READ		0xFE
#define TOKEN_START_MULTI_READ		0xFE
#define TOKEN_START_SINGLE_WRITE	0xFE
#define TOKEN_START_MULTI_WRITE		0xFD
#define TOKEN_STOP_MULTI_WRITE		0xFC

static int
mmc_receive_block(const struct mmc_port *mmc, uint8_t *buf, int len)
{
	/* wait for token */
	while((*buf = SPI_RecvByte()) == 0xFF);

	if(*buf != TOKEN_START_SINGLE_READ) /* Start data token */
		return -1;

	mmc_read_buffer(mmc, buf, len);

	/* Discard CRC bytes */
	SPI_SendByte( 0xFF);
	SPI_SendByte( 0xFF);
	
	return 0;

}

static int
mmc_transmit_block(const struct mmc_port *mmc, const uint8_t *buf, int len)
{
	/* wait for not busy */
	while(SPI_RecvByte() != 0xFF);

	/* Send token */
	SPI_SendByte( TOKEN_START_SINGLE_WRITE);

	/* Sent data frame */
	mmc_write_buffer(mmc, buf, len);

	/* Send dummy CRC bytes */
	SPI_SendByte( 0xFF);
	SPI_SendByte( 0xFF);

	/* Return response code, zero on no error */
	return SPI_RecvByte( );
}

static uint8_t
mmc_command(const struct mmc_port *mmc, uint8_t cmd, uint32_t arg)
{
	uint8_t buf[6];
	uint8_t ret;

	buf[0] = cmd | 0x40;
	/* argument is packed big-endian */
	buf[1] = (arg >> 24) & 0xFF;
	buf[2] = (arg >> 16) & 0xFF;
	buf[3] = (arg >> 8) & 0xFF;
	buf[4] = arg & 0xFF;
	buf[5] = (cmd == MMC_GO_IDLE_STATE) ? 0x95 : 1; /* CRC here */

	mmc_select(mmc);
	mmc_write_buffer(mmc, buf, sizeof(buf));

	do { /* Wait for response byte */
		ret = SPI_RecvByte( );
	} while(ret & 0x80);

	return ret;
}

static uint16_t mmc_get_sector_size(const struct block_device *dev)
{
	(void)dev;
	return MMC_SECTOR_SIZE;
}

static int mmc_read_sectors(const struct block_device *bldev,
		uint32_t sector, uint32_t count, void *buf)
{
	const struct mmc_port *mmc = (void*)bldev;
	uint32_t i;
 
	mmc_select(mmc);
	for(i = 0; i < count; i++) {
		mmc_command(0, MMC_READ_SINGLE_BLOCK, 
				(sector + i) * MMC_SECTOR_SIZE);
		mmc_receive_block(mmc, buf, MMC_SECTOR_SIZE);
		buf += MMC_SECTOR_SIZE;
	}
	mmc_release(mmc);

	return i;
}

static int mmc_write_sectors(const struct block_device *bldev,
		uint32_t sector, uint32_t count, const void *buf)
{
	const struct mmc_port *mmc = (void*)bldev;
	uint32_t i;
 
	mmc_select(mmc);
	for(i = 0; i < count; i++) {
		mmc_command(0, MMC_WRITE_BLOCK, 
				(sector + i) * MMC_SECTOR_SIZE);
		mmc_transmit_block(mmc, buf, MMC_SECTOR_SIZE);
		buf += MMC_SECTOR_SIZE;
	}
	mmc_release(mmc);

	return i;
}

int 
mmc_init(void)
{
	uint8_t ocr[4];

	/* Intialise structure */
	//memset(mmc, 0, sizeof(*mmc));

	/* Block device methods */
	/*mmc->bldev.get_sector_size = mmc_get_sector_size;
	mmc->bldev.read_sectors = mmc_read_sectors;
	mmc->bldev.write_sectors = mmc_write_sectors;
    
	mmc->spi = spi;
	mmc->cs_port = cs_port;
	mmc->cs_pin = cs_pin;*/

	/* Do hardware init */
	/* Peripheral clocks must already be enabled.  
	 * SPI pins must already be configured. */
	/*spi_init_master(mmc->spi, 
			SPI_CR1_BAUDRATE_FPCLK_DIV_2, 
			SPI_CR1_CPOL_CLK_TO_1_WHEN_IDLE, 
			SPI_CR1_CPHA_CLK_TRANSITION_2, 
			SPI_CR1_CRCL_8BIT,
			SPI_CR1_MSBFIRST);*/
	/* Ignore the stupid NSS pin */
	/*spi_enable_software_slave_management(mmc->spi);
	spi_set_nss_high(mmc->spi);
    
	spi_enable(mmc->spi);*/

	/* SD nCS pin init */
	/*gpio_mode_setup(mmc->cs_port, GPIO_MODE_OUTPUT, 
			GPIO_PUPD_NONE, mmc->cs_pin);*/
    SPI_Init();
	/* Do card init ... */
    int i;
	for( i = 0 ; i < 80; i++) SPI_SendByte( 0xff);

	if(mmc_command(0, MMC_GO_IDLE_STATE, 0) != 1)
    {
		 if(mmc_command(0, MMC_ACMD, 0) <= 1){}; 
    }

	/* Wait for card to initialize */
	while(mmc_command(0, MMC_SEND_OP_COND, 0) != 1);

	if(mmc_command(0, MMC_READ_OCR, 0) != 0) 
		return -1; /* Can't read OCR? */

	mmc_read_buffer(0, ocr, sizeof(ocr));
	/* FIXME: Check OCR for acceptable voltage range... */

	
	/* All cards support 512 byte block access and this is the default
	 * after reset.  If disk size or other info is needed this can
	 * be read from CSD in future.
	 */
	if(0) {
		uint8_t csd[16];
		if(mmc_command(0, MMC_SEND_CSD, 0) != 0) 
			return -1; /* Can't read CSD? */
		mmc_receive_block(0, csd, sizeof(csd));

		uint32_t read_bl_len = csd[5] & 0x0F;
		uint32_t c_size = (csd[8] >> 6) + (csd[7] << 3) + 
				((csd[6] & 0x03) << 10);
		uint32_t c_size_mult = ((csd[10] & 0x80) >> 7) + 
				((csd[9] & 0x03) << 1);
		uint32_t blocknr = (c_size + 1) << (c_size_mult + 2 + read_bl_len);
		(void)blocknr;
	}

	mmc_release(0);

	return 0;
}

