/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "fatfs.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

CRC_HandleTypeDef hcrc;

DMA2D_HandleTypeDef hdma2d;

SD_HandleTypeDef hsd1;

/* USER CODE BEGIN PV */
FRESULT res; // fatfs return code
FATFS SDFatFs; /* Work area (filesystem object) for logical drive */
FIL MyFile; // file object

char SdPath[10];
uint32_t byteswritten, bytesread;

int datainput_1[999],datainput_2[999],datainput_3[999];
int number_data;
char *txtResult;
char datain1[200],dataraw[999][200];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SDMMC1_SD_Init(void);
static void MX_DMA2D_Init(void);
static void MX_CRC_Init(void);
/* USER CODE BEGIN PFP */
void mySD_Init();
void mySD_Mount();
void error1();
void reset();
void soal1();
void soal2();
void soal3();
void soal4();
void soal5();
void read_file(char *namafile);
void save_data_file(char *namafile, dataInput datatulis);

typedef enum _bool {
	false = 0,
	true = 1
} boolean;

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
TS_StateTypeDef  ts;
char xTouchStr[10];
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* Enable I-Cache---------------------------------------------------------*/
  SCB_EnableICache();

  /* Enable D-Cache---------------------------------------------------------*/
  SCB_EnableDCache();

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SDMMC1_SD_Init();
  MX_FATFS_Init();
  MX_DMA2D_Init();
  MX_CRC_Init();
  /* USER CODE BEGIN 2 */

  BSP_SDRAM_Init(); /* Initializes the SDRAM device */
  __HAL_RCC_CRC_CLK_ENABLE(); /* Enable the CRC Module */
  BSP_TS_Init(480, 272);//Inisialisasi 480x272 color LCD-TFT with capacitive touch screen
  BSP_LCD_Init(); //Inisialisasi LCD on
  BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, LCD_FB_START_ADDRESS); //Initializes the LCD layer in ARGB8888 format (32 bits per pixel).
  BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);//LCD select layer

  //Delay Process
  BSP_LCD_Clear(LCD_COLOR_DARKGREEN);
  BSP_LCD_SetBackColor(LCD_COLOR_DARKGREEN);
  BSP_LCD_SetTextColor(LCD_COLOR_BROWN);
  BSP_LCD_DisplayStringAt(0, 100, (uint8_t*)"LOADING...", CENTER_MODE); // print text loading... dari koordinat tengah
  HAL_Delay(1000); // delay 1 detik
  BSP_LCD_Clear(LCD_COLOR_DARKGREEN);//clear lcd

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	 mySD_Init(); // inisialisasi microsd
	 mySD_Mount(); // mount microsd

//	 	BSP_LCD_Clear(LCD_COLOR_GREEN);//clear lcd

		//SOAL1
		BSP_TS_GetState(&ts); // Returns status and positions of the touch screen.
		BSP_LCD_SetBackColor(LCD_COLOR_GREEN);
		BSP_LCD_DisplayStringAt(0, 20, (uint8_t*)"SOAL 1", CENTER_MODE);
		BSP_LCD_SetBackColor(LCD_COLOR_GREEN);
		// Jika SOAL 1 ditekan
		if (ts.touchX[0] >= 220 && ts.touchX[0] <= 260 && ts.touchY[0] >= 20 && ts.touchY[0] <= 50)
		{
			BSP_LCD_Clear(LCD_COLOR_DARKGREEN);
			soal1(); // mengubah data soal 1
			// Membuat tampilan pesan soal sudah dikonvert
			BSP_LCD_Clear(LCD_COLOR_WHITE);
			BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
			BSP_LCD_DisplayStringAt(0, 90, (uint8_t *)"BERHASIL CONVERT SOAL1", CENTER_MODE);
			BSP_LCD_DisplayStringAt(0, 110, (uint8_t *)"dan SIMPAN", CENTER_MODE);
			HAL_Delay(1000);
			BSP_TS_ResetTouchData(&ts);
			BSP_LCD_Clear(LCD_COLOR_DARKGREEN);
		}

		//SOAL2
		BSP_TS_GetState(&ts); // Returns status and positions of the touch screen.
		BSP_LCD_SetBackColor(LCD_COLOR_GREEN);
		BSP_LCD_DisplayStringAt(0, 70, (uint8_t*)"SOAL 2", CENTER_MODE);
		BSP_LCD_SetBackColor(LCD_COLOR_GREEN);
		if (ts.touchX[0] >= 220 && ts.touchX[0] <= 260 && ts.touchY[0] >= 70 && ts.touchY[0] <= 100)
		{
			BSP_LCD_Clear(LCD_COLOR_DARKGREEN);
			soal2();

			BSP_LCD_Clear(LCD_COLOR_WHITE);
			BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
			BSP_LCD_DisplayStringAt(0, 90, (uint8_t *)"BERHASIL CONVERT SOAL", CENTER_MODE);
			BSP_LCD_DisplayStringAt(0, 110, (uint8_t *)"dan SIMPAN", CENTER_MODE);
			HAL_Delay(1000);
			BSP_TS_ResetTouchData(&ts);
			BSP_LCD_Clear(LCD_COLOR_DARKGREEN);
		} // if touch soal 2

		//SOAL3
		BSP_TS_GetState(&ts); // Returns status and positions of the touch screen.
		BSP_LCD_SetBackColor(LCD_COLOR_GREEN);
		BSP_LCD_DisplayStringAt(0, 120, (uint8_t*)"SOAL 3", CENTER_MODE);
		BSP_LCD_SetBackColor(LCD_COLOR_GREEN);
		if (ts.touchX[0] >= 220 && ts.touchX[0] <= 260 && ts.touchY[0] >= 120 && ts.touchY[0] <= 150)
		{
			BSP_LCD_Clear(LCD_COLOR_DARKGREEN);
			soal3();

			BSP_LCD_Clear(LCD_COLOR_WHITE);
			BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
			BSP_LCD_DisplayStringAt(0, 90, (uint8_t *)"BERHASIL CONVERT SOAL", CENTER_MODE);
			BSP_LCD_DisplayStringAt(0, 110, (uint8_t *)"dan SIMPAN", CENTER_MODE);
			HAL_Delay(1000);
			BSP_TS_ResetTouchData(&ts);
			BSP_LCD_Clear(LCD_COLOR_DARKGREEN);
		}// if touch soal 3

		//SOAL4
		BSP_TS_GetState(&ts); // Returns status and positions of the touch screen.
		BSP_LCD_SetBackColor(LCD_COLOR_GREEN);
		BSP_LCD_DisplayStringAt(0, 170, (uint8_t*)"SOAL 4", CENTER_MODE);
		BSP_LCD_SetBackColor(LCD_COLOR_GREEN);
		if (ts.touchX[0] >= 220 && ts.touchX[0] <= 260 && ts.touchY[0] >= 170 && ts.touchY[0] <= 200)
		{
			BSP_LCD_Clear(LCD_COLOR_DARKGREEN);
			soal4();

			BSP_LCD_Clear(LCD_COLOR_WHITE);
			BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
			BSP_LCD_DisplayStringAt(0, 90, (uint8_t *)"BERHASIL CONVERT SOAL", CENTER_MODE);
			BSP_LCD_DisplayStringAt(0, 110, (uint8_t *)"dan SIMPAN", CENTER_MODE);
			HAL_Delay(1000);
			BSP_TS_ResetTouchData(&ts);
			BSP_LCD_Clear(LCD_COLOR_DARKGREEN);
		} // if touch soal 4

		//SOAL5
		BSP_TS_GetState(&ts); // Returns status and positions of the touch screen.
		BSP_LCD_SetBackColor(LCD_COLOR_GREEN);
		BSP_LCD_DisplayStringAt(0, 220, (uint8_t*)"SOAL 5", CENTER_MODE);
		BSP_LCD_SetBackColor(LCD_COLOR_GREEN);
		if (ts.touchX[0] >= 220 && ts.touchX[0] <= 260 && ts.touchY[0] >= 220 && ts.touchY[0] <= 250)
		{
			BSP_LCD_Clear(LCD_COLOR_DARKGREEN);
			soal5();

			BSP_LCD_Clear(LCD_COLOR_WHITE);
			BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
			BSP_LCD_DisplayStringAt(0, 90, (uint8_t *)"BERHASIL CONVERT SOAL", CENTER_MODE);
			BSP_LCD_DisplayStringAt(0, 110, (uint8_t *)"dan SIMPAN", CENTER_MODE);
			HAL_Delay(1000);
			BSP_TS_ResetTouchData(&ts);
			BSP_LCD_Clear(LCD_COLOR_DARKGREEN);
		} // if touch soal 5

		//Menu Text Box
		BSP_LCD_DisplayStringAt(0, 20, (uint8_t*)"SOAL 1", CENTER_MODE);
		BSP_LCD_SetBackColor(LCD_COLOR_GREEN);
		BSP_LCD_DisplayStringAt(0, 70, (uint8_t*)"SOAL 2", CENTER_MODE);
		BSP_LCD_SetBackColor(LCD_COLOR_GREEN);
		BSP_LCD_DisplayStringAt(0, 120, (uint8_t*)"SOAL 3", CENTER_MODE);
		BSP_LCD_SetBackColor(LCD_COLOR_GREEN);
		BSP_LCD_DisplayStringAt(0, 170, (uint8_t*)"SOAL 4", CENTER_MODE);
		BSP_LCD_SetBackColor(LCD_COLOR_GREEN);
		BSP_LCD_DisplayStringAt(0, 220, (uint8_t*)"SOAL 5", CENTER_MODE);
	/* Close the file */

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  } // while 1
  /* USER CODE END 3 */
} // main

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 200;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 8;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_6) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief CRC Initialization Function
  * @param None
  * @retval None
  */
static void MX_CRC_Init(void)
{

  /* USER CODE BEGIN CRC_Init 0 */

  /* USER CODE END CRC_Init 0 */

  /* USER CODE BEGIN CRC_Init 1 */

  /* USER CODE END CRC_Init 1 */
  hcrc.Instance = CRC;
  hcrc.Init.DefaultPolynomialUse = DEFAULT_POLYNOMIAL_ENABLE;
  hcrc.Init.DefaultInitValueUse = DEFAULT_INIT_VALUE_ENABLE;
  hcrc.Init.InputDataInversionMode = CRC_INPUTDATA_INVERSION_NONE;
  hcrc.Init.OutputDataInversionMode = CRC_OUTPUTDATA_INVERSION_DISABLE;
  hcrc.InputDataFormat = CRC_INPUTDATA_FORMAT_BYTES;
  if (HAL_CRC_Init(&hcrc) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CRC_Init 2 */

  /* USER CODE END CRC_Init 2 */

}

/**
  * @brief DMA2D Initialization Function
  * @param None
  * @retval None
  */
static void MX_DMA2D_Init(void)
{

  /* USER CODE BEGIN DMA2D_Init 0 */

  /* USER CODE END DMA2D_Init 0 */

  /* USER CODE BEGIN DMA2D_Init 1 */

  /* USER CODE END DMA2D_Init 1 */
  hdma2d.Instance = DMA2D;
  hdma2d.Init.Mode = DMA2D_M2M;
  hdma2d.Init.ColorMode = DMA2D_OUTPUT_ARGB8888;
  hdma2d.Init.OutputOffset = 0;
  hdma2d.LayerCfg[1].InputOffset = 0;
  hdma2d.LayerCfg[1].InputColorMode = DMA2D_INPUT_ARGB8888;
  hdma2d.LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;
  hdma2d.LayerCfg[1].InputAlpha = 0;
  if (HAL_DMA2D_Init(&hdma2d) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_DMA2D_ConfigLayer(&hdma2d, 1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN DMA2D_Init 2 */

  /* USER CODE END DMA2D_Init 2 */

}

/**
  * @brief SDMMC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SDMMC1_SD_Init(void)
{

  /* USER CODE BEGIN SDMMC1_Init 0 */

  /* USER CODE END SDMMC1_Init 0 */

  /* USER CODE BEGIN SDMMC1_Init 1 */

  /* USER CODE END SDMMC1_Init 1 */
  hsd1.Instance = SDMMC1;
  hsd1.Init.ClockEdge = SDMMC_CLOCK_EDGE_RISING;
  hsd1.Init.ClockBypass = SDMMC_CLOCK_BYPASS_DISABLE;
  hsd1.Init.ClockPowerSave = SDMMC_CLOCK_POWER_SAVE_DISABLE;
  hsd1.Init.BusWide = SDMMC_BUS_WIDE_1B;
  hsd1.Init.HardwareFlowControl = SDMMC_HARDWARE_FLOW_CONTROL_DISABLE;
  hsd1.Init.ClockDiv = 0;
  /* USER CODE BEGIN SDMMC1_Init 2 */

  /* USER CODE END SDMMC1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOI_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOI, GPIO_PIN_1, GPIO_PIN_RESET);

  /*Configure GPIO pin : PI1 */
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void mySD_Init(){
	res = BSP_SD_Init();//Inisialisas SD card
	if(res != FR_OK){
	BSP_LCD_Clear(LCD_COLOR_DARKGREEN); //Ketika LCD_Clear LCD berwarna putih
	BSP_LCD_SetBackColor(LCD_COLOR_DARKGREEN);//set background berwarna hijau
	BSP_LCD_SetTextColor(LCD_COLOR_BROWN);//set text berwarna coklat
	/*Display ERROR
	 *LCD pada koordinat X,Y dengan mode Center
	 *Ketika MICRO SD tidak terdeteksi*/
	BSP_LCD_DisplayStringAt(0, 100, (uint8_t*)"PLEASE INSERT MICRO SD", CENTER_MODE);
	error1();
	}
}

void mySD_Mount(){
	res = f_mount(&SDFatFs, "", 1);//Mounting MicroSD
	if(res != FR_OK){
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	BSP_LCD_SetBackColor(LCD_COLOR_DARKGREEN);
	BSP_LCD_SetTextColor(LCD_COLOR_BROWN);
	/*Display ERROR
	 *LCD pada koordinat X,Y dengan mode Center
	 *Ketika MICRO SD tidak termounting*/
	BSP_LCD_DisplayStringAt(0, 100, (uint8_t*)"Error! cannot mount SD Card!", CENTER_MODE);
	error1();
	}
}

//Baca File
void read_file(char *namafile){
	res = f_open(&MyFile, namafile, FA_READ);
    if(res != FR_OK){
    	BSP_LCD_DisplayStringAt(0, 100, (uint8_t*)"Can't Read/No data.txt!", CENTER_MODE);
    	  error1();
    }
	int i = 0;
	int j = 0;
	while(!f_eof(&MyFile)){
		f_gets(datain1,200,&MyFile);
		strcpy(dataraw[i], shift_trim(datain1));
		if(strlen(dataraw[i])>=0){j++;strcpy(dataraw[j], shift_trim(datain1));}
		i++;
	}
    f_close(&MyFile);
	number_data = j;
	if(strlen(dataraw[number_data]) == strlen(dataraw[number_data-1])){number_data=j-1;}
	else{number_data = j;}
}

//Fungsi save data ke file.txt (setelah di convert)
void save_data_file(char *namafile, dataInput datatulis){
	  res = f_open(&MyFile, namafile, FA_CREATE_ALWAYS|FA_WRITE);
	  if(res != FR_OK){
		  error1();
	  }

	  res = f_lseek(&MyFile, f_size(&MyFile));
	  if(res != FR_OK){
		  error1();
	  }
    for (int i = 0;i < (datatulis.ndata+1);i++){
		f_printf(&MyFile, "%s %s %s \n",  datatulis.Input1[i], datatulis.Input2[i],datatulis.Input3[i]);
	}
	  f_close(&MyFile);
}

/*=================================Fungsi proses soal1-5=============================*/
void soal1()
{
	read_file("data.txt");

	get_data_from_rawdata();
	dataInput dataBaca;
	dataBaca.Input1 = calloc(999,sizeof(char));
	dataBaca.Input2 = calloc(999,sizeof(char));
	dataBaca.Input3 = calloc(999,sizeof(char));

	for(int i=0;i<number_data+1;i++){
		dataBaca.Input1[i]=IntToStr(datainput_1[i]);
		dataBaca.Input2[i]=IntToStr(datainput_2[i]);
		dataBaca.Input3[i]=IntToStr(datainput_3[i]);
	}
	dataBaca.ndata = number_data;

	save_data_file("data_copy1.txt",dataBaca);

	free(dataBaca.Input1),dataBaca.Input1=NULL;
	free(dataBaca.Input2),dataBaca.Input2=NULL;
	free(dataBaca.Input3),dataBaca.Input3=NULL;
}

void soal2()
{
	read_file("data.txt");
	printf("jumlah data = %d\n",number_data);

	get_data_from_rawdata();
	dataInput dataBaca;
	dataBaca.Input1 = calloc(9999,sizeof(char));
	dataBaca.Input2 = calloc(9999,sizeof(char));
	dataBaca.Input3 = calloc(9999,sizeof(char));

	for(int i=0;i<number_data+1;i++){
		dataBaca.Input1[i]=IntToStr(datainput_1[i]);
		dataBaca.Input2[i]=",";
		dataBaca.Input3[i]=IntToStr(datainput_3[i]);
	}
	dataBaca.ndata = number_data;

	save_data_file("data_copy2.txt",dataBaca);

	free(dataBaca.Input1),dataBaca.Input1=NULL;
	free(dataBaca.Input2),dataBaca.Input2=NULL;
	free(dataBaca.Input3),dataBaca.Input3=NULL;
}

void soal3()
{
	read_file("data.txt");
	printf("jumlah data = %d\n",number_data);

	get_data_from_rawdata();
	dataInput dataBaca;
	dataBaca.Input1 = calloc(9999,sizeof(char));
	dataBaca.Input2 = calloc(9999,sizeof(char));
	dataBaca.Input3 = calloc(9999,sizeof(char));
	int count1=0;
	int count2=0;
	for(int i=0;i<number_data+1;i++){
		if(isGanjil(datainput_1[i])==0){
			count1++;
			dataBaca.Input1[count1] = IntToStr(datainput_1[i]);
		}
		if(isGanjil(datainput_2[i])==0){
			count1++;
			dataBaca.Input1[count1] = IntToStr(datainput_2[i]);
		}
		if(isGanjil(datainput_3[i])==0){
			count1++;
			dataBaca.Input1[count1] = IntToStr(datainput_3[i]);
		}

		if(isGanjil(datainput_1[i])==1){
			count2++;
			dataBaca.Input2[count2] = IntToStr(datainput_1[i]);
		}
		if(isGanjil(datainput_2[i])==1){
			count2++;
			dataBaca.Input2[count2] = IntToStr(datainput_2[i]);
		}
		if(isGanjil(datainput_3[i])==1){
			count2++;
			dataBaca.Input2[count2] = IntToStr(datainput_3[i]);
		}
	}

	dataBaca.ndata = (count1 > count2 ? count1 : count2);

	for(int i=0;i<dataBaca.ndata+1;i++){
		if(dataBaca.Input1[i]==NULL){dataBaca.Input1[i]="";}
		if(dataBaca.Input2[i]==NULL){dataBaca.Input2[i]="";}
		dataBaca.Input3[i]="";
	}

	save_data_file("data_copy3.txt",dataBaca);

	free(dataBaca.Input1),dataBaca.Input1=NULL;
	free(dataBaca.Input2),dataBaca.Input2=NULL;
	free(dataBaca.Input3),dataBaca.Input3=NULL;
}

void soal4()
{
	read_file("data.txt");
	printf("jumlah data = %d\n",number_data);

	get_data_from_rawdata();
	dataInput dataBaca;
	dataBaca.Input1 = calloc(9999,sizeof(char));
	dataBaca.Input2 = calloc(9999,sizeof(char));
	dataBaca.Input3 = calloc(9999,sizeof(char));

	int count=0;
	for(int i=0;i<number_data+1;i++){
		count++;
		dataBaca.Input1[count]=IntToStr(datainput_1[i]);
		count++;
		dataBaca.Input1[count]=IntToStr(datainput_2[i]);
		count++;
		dataBaca.Input1[count]=IntToStr(datainput_3[i]);
	}
	dataBaca.ndata = count;
	for(int i=0;i<dataBaca.ndata+1;i++){
		if(dataBaca.Input1[i]==NULL){dataBaca.Input1[i]="";}
		dataBaca.Input2[i]="";
		dataBaca.Input3[i]="";
	}

	save_data_file("data_copy4.txt",dataBaca);

	free(dataBaca.Input1),dataBaca.Input1=NULL;
	free(dataBaca.Input2),dataBaca.Input2=NULL;
	free(dataBaca.Input3),dataBaca.Input3=NULL;
}

void soal5()
{
	read_file("data.txt");
	printf("jumlah data = %d\n",number_data);

	get_data_from_rawdata();
	dataInput dataBaca;
	dataBaca.Input1 = calloc(9999,sizeof(char));
	dataBaca.Input2 = calloc(9999,sizeof(char));
	dataBaca.Input3 = calloc(9999,sizeof(char));

	int count=0;
	for(int i=0;i<number_data+1;i++){
		count++;
		dataBaca.Input1[count]=IntToStr(datainput_1[i]);
		count++;
		dataBaca.Input1[count]=IntToStr(datainput_2[i]);
		count++;
		dataBaca.Input1[count]=IntToStr(datainput_3[i]);
	}
	dataBaca.ndata = count;
	for(int i=0;i<dataBaca.ndata+1;i++){
		if(dataBaca.Input1[i]==NULL){dataBaca.Input1[i]="";}
		dataBaca.Input2[i]="";
		dataBaca.Input3[i]="";

		if(isGanjil(atoi(dataBaca.Input1[i]))==1 && atoi(dataBaca.Input1[i]) > 5){dataBaca.Input1[i]="ganjil > 5";}
		else if(isGanjil(atoi(dataBaca.Input1[i]))==0 && atoi(dataBaca.Input1[i]) > 5){dataBaca.Input1[i]="genap > 5";}
		else{dataBaca.Input1[i]=dataBaca.Input1[i];}
	}

	save_data_file("data_copy5.txt",dataBaca);

	free(dataBaca.Input1),dataBaca.Input1=NULL;
	free(dataBaca.Input2),dataBaca.Input2=NULL;
	free(dataBaca.Input3),dataBaca.Input3=NULL;
}
/*==============================================END OF Fungsi proses soal1-5==================================*/

//System Reset (restart Hardware) via push reset
//mengembalikan sistem ke posisi awal
void reset(){
	BSP_TS_GetState(&ts);
	BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(0, 150, (uint8_t *)"RESET", CENTER_MODE);
	if (ts.touchX[0] >= 180 && ts.touchX[0] <= 300 && ts.touchY[0] >= 140 && ts.touchY[0] <= 170){
		NVIC_SystemReset(); // Reset System
	}
}

//Error and restart
void error1(){
	while(1){
	reset();
	HAL_Delay(100);
	}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
