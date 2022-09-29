/*
 * pn532_stm32f1.h
 *
 *  Created on: Jul 18, 2022
 *      Author: lime
 */

#ifndef INC_PN532_STM32F1_H_
#define INC_PN532_STM32F1_H_

#include "pn532.h"

void PN532_Init(PN532* dev);
int PN532_Reset(void);
void PN532_Log(const char* log);

int PN532_SPI_ReadData(uint8_t* data, uint16_t count);
int PN532_SPI_WriteData(uint8_t *data, uint16_t count);
bool PN532_SPI_WaitReady(uint32_t timeout);
int PN532_SPI_Wakeup(void);
void PN532_SPI_Init(PN532* dev);

#endif /* INC_PN532_STM32F1_H_ */
