/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

#include "openfat.h"
#include "openfat/mbr.h"
#include "mmc.h"

static volatile uint32_t time_counter;

int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */

	/*struct mmc_port spi2;
	struct block_mbr_partition part;
	struct fat_vol_handle vol;
	struct fat_file_handle file;

    mmc_init();
    mbr_partition_init(&part, (struct block_device *)&spi2, 0);
    assert(fat_vol_init((struct block_device *)&part, &vol) == 0);
    
    time_counter = 0;
	char dirname[20];
	char filename[20];
	char buffer[2000];
    int i;
    for( i = 0; i < 100; i++) 
	{
		sprintf(dirname, "Dir%d", i);
		fat_mkdir(&vol, dirname);
		assert(fat_chdir(&vol, dirname) == 0);
        int j;
		for( j = 0; j < 100; j++) {
			sprintf(filename, "File%d", j);
			assert(fat_create(&vol, filename, O_WRONLY, &file) == 0);
			assert(fat_write(&file, buffer, sizeof(buffer)) == sizeof(buffer));
		}
		assert(fat_chdir(&vol, "..") == 0);
	}
    asm("bkpt");
    
    assert(fat_open(&vol, ".", 0, &file) == 0);
    */
    
    struct mmc_port spi2;
    struct block_mbr_partition part;
	FatVol vol;
	FatFile file;
	char buffer[128];

    mmc_init();
    mbr_partition_init(&part, (struct block_device *)&spi2, 0);

	fat_vol_init((struct block_device *)&part, &vol);

	fat_open(&vol, "TEST.TXT", O_RDONLY, &file);
	fat_read(&file, buffer, sizeof(buffer));
    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
