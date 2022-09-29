/*
 * i2c.h
 *
 *  Created on: Jul 19, 2022
 *      Author: lime
 */
#include "stm32f1xx.h"
#include "GPIO.h"

#ifndef I2C_H_
#define I2C_H_

#define i2c_FM 0x2d
#define i2c_SM 0xB4


void i2c_init(char i2c,unsigned short speed_mode);
void i2c_write(char i2c, char address,char data[]);

#endif /* I2C_H_ */
