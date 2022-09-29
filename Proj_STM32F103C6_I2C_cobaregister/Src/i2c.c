/*
 * i2c.c
 *
 *  Created on: Jul 19, 2022
 *      Author: lime
 */


#include "i2c.h"
/*
I2C2
PB10 -> SCL
PB11 -> SDA

I2C1
PB6 -> SCL
PB7 -> SDA

*/
	volatile int tmp;

// i2c_init()
void i2c_init(char i2c,unsigned short speed_mode)
{
	RCC->APB2ENR |= 1;

	if(i2c==1)
	{
		RCC->APB1ENR |= 0x200000;
		// Pin enable
		init_GP(PB,6,OUT50,O_AF_OD);
		init_GP(PB,7,OUT50,O_AF_OD);
		I2C1->CR1 |= 0x8000;
		I2C1->CR1 &= ~0x8000;
		I2C1->CR2 =0x8;
		I2C1->CCR = speed_mode;
		I2C1->TRISE = 0x9;
		I2C1->CR1 |= 1;
	}
}

// Start step
void i2c_start(char i2c)
{
	if(i2c==1)
	{
		I2C1->CR1 |= 0x100;
		while (!(I2C1->SR1 & 1)){};
	}
}

// Sending the address + R or Write
void i2c_add(char i2c, char address,char RW)
{
	if(i2c==1)
	{
		I2C1->DR = (address|RW);
		while((I2C1->SR1 & 2)==0){};
		while((I2C1->SR1 & 2)){
			tmp = I2C1->SR1;
			tmp = I2C1->SR2;
			if((I2C1->SR1 & 2)==0)
			{
				break;
			}
		}
	}
}
// Sending data step
void i2c_data(char i2c,char data)
{
	if(i2c==1)
	{
		while((I2C1->SR1 & 0x80) == 0){}
			I2C1->DR = data;
		while((I2C1->SR1 & 0x80) == 0){}
	}
}
// Stop step
void i2c_stop(char i2c)
{
	if(i2c==1)
	{
		tmp = I2C1->SR1;
		tmp = I2C1->SR2;
		I2C1->CR1 = 0x200;
	}
}
// i2c_write()
void i2c_write(char i2c, char address,char data[])
{
	int i = 0;

	i2c_start(i2c);

	i2c_add(i2c,address,0);

	while(data[i])
		{
			i2c_data(i2c,data[i]);
			i++;
		}
//	i2c_stop(i2c);
}
