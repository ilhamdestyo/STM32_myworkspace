/*
 * myclock.h
 *
 *  Created on: Jul 19, 2022
 *      Author: lime
 */

#ifndef MYCLOCK_H_
#define MYCLOCK_H_

void systick_init(void);
void DelayMs(unsigned long t);
void systick_int(unsigned short uart_1_mgr[],unsigned short uart_2_mgr[],unsigned short uart_3_mgr[]);
void systick_int_start(void);
void Delaymicro(void);
void DelayUs(unsigned long t);

#endif /* MYCLOCK_H_ */
