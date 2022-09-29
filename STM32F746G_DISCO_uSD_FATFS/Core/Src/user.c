/*
 * user.c
 *
 *  Created on: Dec 4, 2020
 *      Author: wroblema
 */


#include "stm32f7xx_hal.h"
#include "fatfs.h"


char FileName[] = "XXX.CSV";
int RunTest = 0;
int ClrStats = 0;
int NewFile = 0;
int FmtCard = 0;

uint8_t workBuffer[_MAX_SS];
char Buff[100] = {0};


void SD_Card_Init(void)
{
  FRESULT res;                                          /* FatFs function common result code */
  uint32_t byteswritten, bytesread;                     /* File write/read counts */
  uint8_t wtext[] = "This is STM32 working with FatFs"; /* File write buffer */
  uint8_t rtext[100];                                   /* File read buffer */



	/*##-1- Link the micro SD disk I/O driver ##################################*/
	// done in main() call to MX_FATFS_Init()


	// ##-2- Register the file system object to the FatFs module ###########
	if ((res = f_mount(&SDFatFS, (TCHAR const*)SDPath, 0)) != FR_OK) Error_Handler();


	// ##-3- Create a FAT file system (format) on the logical drive ########
	/* WARNING: Formatting the uSD card will delete all content on the device */
	// if you comment out the next line the code will keep creating new files with incremental names
	if((res = f_mkfs((TCHAR const*)SDPath, FM_ANY, 0, workBuffer, sizeof(workBuffer))) != FR_OK) Error_Handler();


	// ##-4- Create and Open a new text file object with write access ######
	int i; res = FR_TIMEOUT; // fake set result to engage the loop
	for (i = 0; ((i < 1000) && (res != FR_OK) && (res != FR_DISK_ERR)); i++)
	{
		sprintf(FileName, "%03d.TXT", i); res = FR_TIMEOUT; // fake set result to engage the loop
		res = f_open(&SDFile, FileName, FA_CREATE_NEW | FA_READ | FA_WRITE);
	}
	if ((res == FR_DISK_ERR) || (i == 1000))
	{
		Error_Handler();
	}

	/*##-5- Write data to the text file ################################*/
	res = f_write(&SDFile, wtext, sizeof(wtext), (void *)&byteswritten);
	if((byteswritten == 0) || (res != FR_OK))
	{
		/* 'STM32.TXT' file Write or EOF Error */
		Error_Handler();
	}

	// ##-7- Close the open text file ######################################
	if((res = f_close(&SDFile)) != FR_OK)
	{
		Error_Handler();
	}

	/*##-7- Open the text file object with read access ###############*/
	if(res = f_open(&SDFile, FileName, FA_READ) != FR_OK)
	{
		/* 'STM32.TXT' file Open for read Error */
		Error_Handler();
	}

	/*##-8- Read data from the text file ###########################*/
	res = f_read(&SDFile, rtext, sizeof(rtext), (UINT*)&bytesread);
	if((bytesread == 0) || (res != FR_OK))
	{
		/* 'STM32.TXT' file Read or EOF Error */
		Error_Handler();
	}

	/*##-9- Close the open text file #############################*/
	f_close(&SDFile);

	/*##-10- Compare read data with the expected data ############*/
	if((bytesread != byteswritten))
	{
		/* Read data is different from the expected data */
		Error_Handler();
	}

#if 0
  // ##-12- Unlink the SD disk I/O driver ################################
  FATFS_UnLinkDriver(SDPath);
#endif
}
