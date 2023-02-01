/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
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

#include <stdint.h>
#include "GPIOx.h"
#include "RCC.h"
#include "SYSTICK.h"
#include "NVIC.h"

#include "CANx.h"

void CANx_SetParFLTR(CAN_FilterTypeDef * FLTR, uint8_t index, uint8_t scale, uint16_t IDL, uint16_t IDH, uint16_t MaskL, uint32_t MaskH, uint8_t mode, uint8_t FIFO );

int main(void)
{
	CAN_FilterTypeDef FLTR[2];
	CAN_Handler can;
	CAN_BitTimingTypeDef tq;
	can.Register=CAN1;
	//Los prescaladores se seleccionan por n=1,2,...,8. Siendo 2^n el valor del preescalador
	SystClock_Init(2,0,80,1,0,0);//SYSCLK -> PLLP, SYSPLL -> HSI, SYSCLK -> 80MHz, preAHB1 -> divided by 2^1
	//preAPB1 -> Not divided, preAPB2 -> not divided, APB1 = 40MHZ, APB2=40MHz.
	//NVIC_SetCFGR(CAN1_Rx0_IRQ, 3);

	CANx_SetParFLTR(&FLTR[0], 0, CAN_FS1R_S32, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, CAN_FM1R_MaskMode, CAN_FFA1R_FIFO0);
	//0->Filter 0; CAN_FS1R_S32->32 bits scale; 0xFFFF->IDL,  0xFFFF->IDH;  0xFFFF->MaskL,  0xFFFF->MaskH;
	//CAN_FM1R_MaskMode-> ID in mask mode; CAN_FFA1R_FIFO0-> assigned to FIFO 0
	CANx_SetParFLTR(&FLTR[1], 1, CAN_FS1R_S32, 1200, 1200, 0xFFFF, 0xFFFF, CAN_FM1R_MaskMode, CAN_FFA1R_FIFO1);

	//Time quanta Parameters
	tq.ntq = 16;//16 times
	tq.kbps = 1000;//1Mbps
	tq.SJW = 0;//SJW=1

	CANx_Init(&can, FLTR, &tq, false, 0, 3);//can struct; array of sturct FLTR; tq struct; false->No dual mode; 0->Number of filter for CAN2;
	//3->Number of filters to configure

	CANx_TxData(&can, 1200, 0x1111, 0x1111, 8, false, 0);
	CANx_TxData(&can, 0xFFFFFFFF, 0x2222, 0x2222, 8, false, 1);
	//Use LEC error for better performance

    /* Loop forever */
	for(;;);
}

void CANx_SetParFLTR(
		CAN_FilterTypeDef * FLTR,
		uint8_t index,
		uint8_t scale,
		uint16_t IDL,
		uint16_t IDH,
		uint16_t MaskL,
		uint32_t MaskH,
		uint8_t mode,
		uint8_t FIFO )
{
	FLTR->indexFltr=index;
	FLTR->bitscale=scale;
	FLTR->ID_L=IDL;
	FLTR->ID_H=IDH;
	FLTR->Mask_L=MaskL;
	FLTR->Mask_H=MaskH;
	FLTR->modeFltr=mode;
	FLTR->FIFO=FIFO;
}
