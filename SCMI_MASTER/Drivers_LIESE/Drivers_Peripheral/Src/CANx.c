/*
 * CANx.c
 *
 *  Created on: 23 ene 2023
 *      Author: jurl9
 */

#include "CANx.h"
#include "RCC.h"
#include "NVIC.h"

bool CAN1Tx=false, CAN2Tx=false;
uint8_t CANStatus=0;//Para errores y estado de CAN
CAN_TxandRxHeader_TypeDef *ptrRx, *ptrTx;//Apuntadores a estructuras
CAN_Handler *can1, *can2;

void CANx_GPIO(GPIO_TypeDef *Port_, uint8_t Pin_){
	RCC_EnPort(Port_);
	GPIOx_InitAF(Port_, Pin_, GPIO_OTYPER_PP, GPIO_OSPEEDR_HS, GPIO_AFR_AFSEL_CAN);
}

/*
 * dual_mode: Indicates if both CAN are used
 * nofltrCANslave: Number of filter for CAN2 as slave
 * nofltrArray: Number of filters to configure
 */
void CANx_Init(CAN_Handler *canBus, CAN_FilterTypeDef *fltr, CAN_DualFilterID_n_MaskTypeDef * fltr_ID2_Mask2, CAN_BitTimingTypeDef *tq, bool dual_mode, uint8_t nofltrCANslave,  uint8_t nofltrArray){

	if(dual_mode){
		SET_BIT(RCC_APB1ENR , RCC_APB1ENR_CAN1EN | RCC_APB1ENR_CAN2EN);
	}
	else{//One BusCan used
		if(canBus->Register==CAN1){
			SET_BIT(RCC_APB1ENR , RCC_APB1ENR_CAN1EN);

		}
		else if(canBus->Register==CAN2){
			SET_BIT(RCC_APB1ENR , RCC_APB1ENR_CAN2EN);
		}
	}

	SET_BIT(canBus->Register->MCR, CAN_MCR_RESET);//Reset
	CANx_WaitResetFlag(&(canBus->Register->MSR), CAN_MCR_RESET);//Wait for confirmation

	SET_BIT(canBus->Register->MCR, CAN_MCR_INRQ);//Initialization request
	CANx_WaitSetFlag(&(canBus->Register->MSR), CAN_MSR_INAK);//Wait for confirmation

	CLEAR_BIT(canBus->Register->MCR, CAN_MCR_SLEEP);//SLEEP MODE OFF
	CANx_WaitResetFlag(&(canBus->Register->MSR), CAN_MSR_SLAK);

	CLEAR_BIT(canBus->Register->MCR, CAN_MCR_TXFP);//Priority driven by the identifier of the message
	CLEAR_BIT(canBus->Register->MCR, CAN_MCR_RFLM);//Receive FIFO not locked on overrun.
	CLEAR_BIT(canBus->Register->MCR, CAN_MCR_NART);//The CAN hardware will automatically retransmit the message until it has been
	//successfully transmitted according to the CAN standard.
	//Modificar, si no se desea retransmitir NART=1.
	CLEAR_BIT(canBus->Register->MCR, CAN_MCR_AWUM);//The Sleep mode is left on software request
	CLEAR_BIT(canBus->Register->MCR, CAN_MCR_ABOM);//The Bus-Off state is left on software request,
	CLEAR_BIT(canBus->Register->MCR, CAN_MCR_TTCM);//Time Triggered Communication mode disabled.
	CLEAR_BIT(canBus->Register->MCR, CAN_MCR_RESET);//Normal operation.
	CLEAR_BIT(canBus->Register->MCR, CAN_MCR_DBF);//CAN working during debug

	//---------------------------------------------CAN2 Initialization Here---------------------------------------------------

	CANx_BitTiming(canBus, tq);

	CANx_CfgFilters(canBus, fltr, fltr_ID2_Mask2, dual_mode, nofltrCANslave, nofltrArray);

	CLEAR_BIT(canBus->Register->MCR, CAN_MCR_INRQ);//Initialization request off
	CANx_WaitResetFlag(&(canBus->Register->MSR), CAN_MSR_INAK);
	CANStatus=CAN_NORMAL; //Normal mode operation

}

/*
 * indexFltr: Select 0-27 filter to configure
 * bitscale: 16 or 32 bits scale filter
 * ID: identifier filter
 * Mask: Mask filter
 * modeFltr: Select between Identifier Mask Mode or Identifier List Mode
 * FIFO: Select in which FIFO will be stored data when filter achieves
 */
void CANx_SetCfgFilter(CAN_Handler * canBus, CAN_FilterTypeDef * fltr, CAN_DualFilterID_n_MaskTypeDef * fltr_ID2_Mask2){
	//SET_BIT(canBus->Register->FMR, CAN_FMR_FINIT);//Initialization mode for the filters.
	CLEAR_BIT(canBus->Register->FA1R, (1UL<<fltr->indexFltr));//Desactive Filter
	CLEAR_BIT(canBus->Register->FiR[fltr->indexFltr].FiR1, 0xFFFFFFFF);//CLEAR ID
	CLEAR_BIT(canBus->Register->FiR[fltr->indexFltr].FiR2, 0xFFFFFFFF);//CLEAR MASK

	if(fltr->bitscale&1UL){//32 bits scale
		SET_BIT(canBus->Register->FS1R, (fltr->bitscale&1UL)<<fltr->indexFltr);//Dual 16 bits scale or Single 32 bits scale, for all 28 filters
		if(fltr->IDE){
			SET_BIT(canBus->Register->FiR[fltr->indexFltr].FiR1, (((fltr->ID_L&0xFFFF)<<CAN_F0R1_FB3_Pos)|(((fltr->ID_H&0x1FFF)<<16)<<CAN_F0R1_FB3_Pos)));//Extended ID for 32 bits scale
			SET_BIT(canBus->Register->FiR[fltr->indexFltr].FiR2, (((fltr->Mask_L&0xFFFF)<<CAN_F0R1_FB3_Pos)|(((fltr->Mask_H&0x1FFF)<<16)<<CAN_F0R1_FB3_Pos)));//Mask for 32 bits scale, 0->Not compare, 1->Compare
			//IDE, RTR, must be set, reset or don't care?
		}
		else{
			SET_BIT(canBus->Register->FiR[fltr->indexFltr].FiR1, ((fltr->ID_L&0x7FF)<<CAN_F0R1_FB21_Pos));//Standard ID for 32 bits scale
			SET_BIT(canBus->Register->FiR[fltr->indexFltr].FiR2, ((fltr->Mask_L&0x7FF)<<CAN_F0R1_FB21_Pos));//Mask for 32 bits scale, 0->Not compare, 1->Compare
		}
	}
	else{//Dual 16 bits scale: ID[15:0], MASK[16:31]
		CLEAR_BIT(canBus->Register->FS1R, (fltr->bitscale&1UL)<<fltr->indexFltr);//Dual 16 bits scale or Single 32 bits scale, for all 28 filters

		if(fltr->IDE){
			SET_BIT(canBus->Register->FiR[fltr->indexFltr].FiR1, ((0x3&fltr->ID_H)<<1)|((0x8000&fltr->ID_L)>>15)|(1<<3));//Extended ID for 16 bits
			SET_BIT(canBus->Register->FiR[fltr->indexFltr].FiR1, (((0x3&fltr->Mask_H)<<16)<<1)|((0x8000&fltr->Mask_L)<<1)|(1<<19));//Mask for 16 bits scale
		}
		else{

			SET_BIT(canBus->Register->FiR[fltr->indexFltr].FiR1, ((0x7FF&fltr->ID_L)<<5));//Standard ID for 16 bits
			SET_BIT(canBus->Register->FiR[fltr->indexFltr].FiR1, (((0x7FF&fltr->Mask_L)<<16)<<5));//Mask for 16 bits scale
		}
		if(fltr_ID2_Mask2->IDE){
			SET_BIT(canBus->Register->FiR[fltr->indexFltr].FiR2, ((0x3&fltr_ID2_Mask2->ID_H)<<1)|((0x8000&fltr_ID2_Mask2->ID_L)>>15)|(1<<3));//Extended ID for 16 bits
			SET_BIT(canBus->Register->FiR[fltr->indexFltr].FiR2,(((0x3&fltr_ID2_Mask2->Mask_H)<<16)<<1)|((0x8000&fltr->Mask_L)<<1)|(1<<19));//Mask for 16 bits scale
			//IDE, RTR?
		}
		else{
			SET_BIT(canBus->Register->FiR[fltr->indexFltr].FiR2,  ((0x7FF&fltr_ID2_Mask2->ID_L)<<5));//Standard ID for 16 bits scale
			SET_BIT(canBus->Register->FiR[fltr->indexFltr].FiR2,  (((0x7FF&fltr_ID2_Mask2->Mask_L)<<16)<<5));//Mask for 16 bits scale, 0->Not compare, 1->Compare
			//IDE, RTR?
		}
	}

	SET_BIT(canBus->Register->FM1R, (fltr->modeFltr&1UL)<<fltr->indexFltr);//Filter modes. 0: Two 32-bit registers of filter bank x are in Identifier Mask mode.
	//1: registers of filter bank x are in Identifier List mode.
	SET_BIT(canBus->Register->FFA1R, (fltr->FIFO&1UL)<<fltr->indexFltr);// assigned to FIFO 0 or 1
	SET_BIT(canBus->Register->FA1R, 1UL<<fltr->indexFltr);//active Filter
	//CLEAR_BIT(canBus->Register->FMR, CAN_FMR_FINIT);//Initialization mode off
}

void CANx_CfgFilters(CAN_Handler * canBus, CAN_FilterTypeDef * fltr, CAN_DualFilterID_n_MaskTypeDef * fltr_ID2_Mask2, bool dual_mode, uint8_t nofltrCANslave,  uint8_t nofltrArray){

	uint8_t i=0, aux=0;

	SET_BIT(canBus->Register->FMR, CAN_FMR_FINIT);//Initialization mode for the filters.

	if(!dual_mode){//Un solo módulo CAN para usar

		CLEAR_BIT(canBus->Register->FMR, (CAN_FMR_CAN2SB));//All 28 filters managed by one can

	}
	else{
		SET_BIT(canBus->Register->FMR, ((28-nofltrCANslave)<<CAN_FMR_CAN2SB_Pos));//filters managed by can slave
	}

	for (i = 0; i < nofltrArray; ++i) {
		CANx_SetCfgFilter(canBus, &fltr[i], &fltr_ID2_Mask2[aux]);//Recorremos el arreglo de estructuras
		if(fltr->indexFltr==fltr_ID2_Mask2->indexFltr){
			aux++;
		}
	}

	CLEAR_BIT(canBus->Register->FMR, CAN_FMR_FINIT);//Initialization mode off
}

/*
 * kbps Data bit rate Kilobits/seg
 * ntq number of time quanta
 * SJW value for resynchronization
 */
bool CANx_BitTiming(CAN_Handler * canBus, CAN_BitTimingTypeDef *tq){

	bool flag=true;
	uint8_t nt1t2=0; //Define total time for tSeg1+tSeg2, don't consider Sync time
	uint8_t nt1=0, nt2=0; //Segment 1 and segment 2. Maximum value Segment 2: Value programmable (8-1)=7
	uint32_t fq ;//fq=1/tq -> tq = tbits/ntq
	uint16_t BRP ;//(ClockFreq/fq) - 1

	if(tq->ntq > 25){//Supera el máximo número de tiempo de cuantización
		tq->ntq = 25; //Colocamos el máximo valor por defecto
	}

	if(tq->kbps>1000000){//Máxima tasa de transferencia 1Mbps CAN 2.0
		tq->kbps = 1000000; //1Mbps
	}

	fq = tq->kbps * tq->ntq;//Calculando frecuencia del tiempo cuántico
	BRP = ((currentAHB1CLK*1000000) / (fq));//Baud rate prescaler

	fq = ((currentAHB1CLK*1000000)/BRP) / (tq->ntq);//Rehusamos variable para calcular el tiempo total de 1 bit

	while((fq>(tq->kbps)||(fq!=tq->kbps))&&(BRP<=1023)){
		(tq->ntq)++;//Incrementamos el tiempo cuántico
		fq = ((currentAHB1CLK*1000000)/BRP) / (tq->ntq);//Rehusamos variable para calcular el tiempo total de 1 bit
		if(tq->ntq > 25){//Supera el máximo número de tiempo de cuantización
			tq->ntq = 1; //Colocamos el máximo valor por defecto
			BRP++;
		}
	}

	nt1t2 = tq->ntq - 1;

	if(fq!=tq->kbps){//Si no hay coincidencia se busca un valor cercano
		BRP = ((currentAHB1CLK*1000000) / (fq));//Baud rate prescaler
		while(fq>(tq->kbps)){
			(tq->ntq)++;//Incrementamos el tiempo cuántico
			fq = ((currentAHB1CLK*1000000)/BRP) / (tq->ntq);//Rehusamos variable para calcular el tiempo total de 1 bit
			if(tq->ntq > 25){//Supera el máximo número de tiempo de cuantización
				tq->ntq = 1; //Colocamos el máximo valor por defecto
				BRP++;
			}
		}
	}

	if((BRP<0)||(BRP>1023)){
		flag=false;//Can't preformance bit rate with Clock frequency
	}
	else{
		flag=true;
		nt2 = nt1t2 / 2;
		//nt1 = nt2;

		if(nt2>=8){
			nt2 = 8;//Máximo valor Segmento 2
			nt1 = nt1t2 - nt2;//Valor Segmento 1
		}
		else{
			nt1 = 2; //Rehusamos variables
			nt2-=nt1;//Decrementamos el valor
			nt1 =nt1t2 - nt2;//Calculamos el valor

			while((nt2<1)||(nt2>8)||(nt1==0)){
				nt1--;
				nt2-=nt1;
			}

			nt1 =nt1t2 - nt2; //Calculamos el valor

			if((nt2<1)||(nt2>8)){//Verificamos coincidencia
				nt2 = 1;//Mínimo valor Segmento 2
				nt1 = nt1t2 - nt2;//Valor Segmento 1
			}

		}

		if(tq->SJW){//Resynchronization
			SET_BIT(canBus->Register->BTR , (tq->SJW<<CAN_BTR_SJW_Pos));
		}
		else{
			CLEAR_BIT(canBus->Register->BTR , (3<<CAN_BTR_SJW_Pos));
		}

		CLEAR_BIT(canBus->Register->BTR , (CAN_BTR_BRP));
		CLEAR_BIT(canBus->Register->BTR , (CAN_BTR_TS1));
		CLEAR_BIT(canBus->Register->BTR , (CAN_BTR_TS2));

		SET_BIT(canBus->Register->BTR , ((BRP-1)<<CAN_BTR_BRP_Pos));//Baud rate prescaler
		SET_BIT(canBus->Register->BTR , ((nt1-1)<<CAN_BTR_TS1_Pos));//number of time quanta for tS1
		SET_BIT(canBus->Register->BTR , ((nt2-1)<<CAN_BTR_TS2_Pos));//number of time quanta for tS2

	}

	return flag;

}

void CANx_Tx(CAN_Handler * canBus, CAN_TxandRxHeader_TypeDef * TxHeader){
	uint8_t indexMailBox = TxHeader->Index ;

	CLEAR_BIT(canBus->Register->MailBoxTx[indexMailBox].TIxR, 0xFFFFFFFF);//CLEAR
	CLEAR_BIT(canBus->Register->MailBoxTx[indexMailBox].TDTxR, 0xFFFFFFFF);//CLEAR
	CLEAR_BIT(canBus->Register->MailBoxTx[indexMailBox].TDLxR , 0xFFFFFFFF);//CLEAR
	CLEAR_BIT(canBus->Register->MailBoxTx[indexMailBox].TDHxR , 0xFFFFFFFF);//CLEAR

	if(TxHeader->IDE){
		SET_BIT(canBus->Register->MailBoxTx[indexMailBox].TIxR, CAN_TI0R_IDE);//Extended identifier.
		SET_BIT(canBus->Register->MailBoxTx[indexMailBox].TIxR, (TxHeader->Identifier)<<CAN_TI0R_EXID_Pos);//ID
	}
	else{
		CLEAR_BIT(canBus->Register->MailBoxTx[indexMailBox].TIxR, CAN_TI0R_IDE);//Standard identifier.
		SET_BIT(canBus->Register->MailBoxTx[indexMailBox].TIxR, (TxHeader->Identifier)<<CAN_TI0R_STID_Pos);//ID
	}
	if(TxHeader->RTR){//Remote Frame
		SET_BIT(canBus->Register->MailBoxTx[indexMailBox].TIxR, CAN_TI1R_RTR);//Remote frame
	}
	else{//Data Frame
		CLEAR_BIT(canBus->Register->MailBoxTx[indexMailBox].TIxR, CAN_TI1R_RTR);//Data frame
		SET_BIT(canBus->Register->MailBoxTx[indexMailBox].TDTxR, TxHeader->DLC);//Data length max 8 bytes
		SET_BIT(canBus->Register->MailBoxTx[indexMailBox].TDLxR , TxHeader->DataL);//Low DATA
		SET_BIT(canBus->Register->MailBoxTx[indexMailBox].TDHxR , TxHeader->DataH);//High DATA
	}
	SET_BIT(canBus->Register->MailBoxTx[indexMailBox].TIxR , CAN_TI0R_TXRQ);//Transmission request

	//Success
	//CANx_SetLEC(canBus);//Actualizamos el estado de error LEC

}

//MAILBOX Configuration
//Trama de datos
/*
 * DataH and DataL: Data to send
 * DLC: Data length code
 * ExID: Extended Identifier
 * indexMailBox: Number of Mailbox Tx to use
 */
void CANx_TxData(CAN_Handler * canBus, CAN_TxandRxHeader_TypeDef * TxHeader){

	TxHeader->RTR = CAN_TIxR_Data;//Aseguramos que será trama de datos

	CANx_Tx(canBus, TxHeader);

	CANx_TxSuccess(&(canBus->Register->TSR), TxHeader->Index);
	//Success
	CANx_SetLEC(canBus);//Actualizamos el estado de error LEC

}
//Trama Remota
void CANx_TxRemote(CAN_Handler * canBus, CAN_TxandRxHeader_TypeDef * TxHeader){

	TxHeader->RTR = CAN_TIxR_Remote;//Aseguramos que será trama remota

	CANx_Tx(canBus, TxHeader);

	CANx_TxSuccess(&(canBus->Register->TSR), TxHeader->Index);
	//Success
	CANx_SetLEC(canBus);//Actualizamos el estado de error LEC

}

uint8_t CANx_RxFIFO0(CAN_Handler * canBus, CAN_TxandRxHeader_TypeDef * RxData ){
	if(canBus->Register->RF0R && CAN_RF0R_FMP0){
		if(CANx_GetLEC(canBus)!=CAN_ESR_LEC){//Revisamos si el último mensaje recibido tuvo algún error
			if((canBus->Register->MailBoxFIFORx[0].RIxR) & CAN_RI0R_IDE){//Extended Identifier
				RxData->Identifier = (canBus->Register->MailBoxFIFORx[0].RIxR & 0xFFFFFFF8)>>CAN_RI0R_EXID_Pos;
				RxData->IDE = true;
			}
			else{//Standard Identifier
				RxData->Identifier = (canBus->Register->MailBoxFIFORx[0].RIxR & 0xFFE00000)>>CAN_RI0R_STID_Pos;
				RxData->IDE = false;
			}

			RxData->DLC = canBus->Register->MailBoxFIFORx[0].RDTxR & 0xF;//Data Length Code

			if(!(canBus->Register->MailBoxFIFORx[0].RIxR & CAN_RI0R_RTR)){//Data frame
				RxData->DataL=canBus->Register->MailBoxFIFORx[0].RDLxR;
				RxData->DataH=canBus->Register->MailBoxFIFORx[0].RDHxR;
				RxData->RTR=CAN_RIxR_Data ;//Data Frame
			}
			else{
				RxData->RTR=CAN_RIxR_Remote ;//Remote Frame
			}
			RxData->Index = (canBus->Register->MailBoxFIFORx[0].RDTxR&0xFF00)>>CAN_RDT0R_FMI_Pos;//Filter Match Index
		}

		SET_BIT(canBus->Register->RF0R, CAN_RF0R_RFOM0);//Release FIFO output
	}
	return canBus->Register->RF0R & CAN_RF0R_FMP0;//Return status

}

uint8_t CANx_RxFIFO1(CAN_Handler * canBus, CAN_TxandRxHeader_TypeDef * RxData){

	if(canBus->Register->RF1R & CAN_RF0R_FMP0){
		if(CANx_GetLEC(canBus)!=CAN_ESR_LEC){//Revisamos si el último mensaje recibido tuvo algún error
			if(canBus->Register->MailBoxFIFORx[1].RIxR && CAN_RI1R_IDE){//Extended Identifier
				RxData->Identifier = (canBus->Register->MailBoxFIFORx[1].RIxR & 0xFFFFFFF8)>>CAN_RI1R_EXID_Pos;
				RxData->IDE = true;
			}
			else{//Standard Identifier
				RxData->Identifier = (canBus->Register->MailBoxFIFORx[1].RIxR & 0xFFE00000)>>CAN_RI1R_STID_Pos;
				RxData->IDE = false;
			}

			RxData->DLC=canBus->Register->MailBoxFIFORx[1].RDTxR & 0xF;//Data Length Code

			if(!(canBus->Register->MailBoxFIFORx[1].RIxR & CAN_RI1R_RTR)){//Data frame
				RxData->DataL=canBus->Register->MailBoxFIFORx[1].RDLxR;
				RxData->DataH=canBus->Register->MailBoxFIFORx[1].RDHxR;
				RxData->RTR=CAN_RIxR_Data ;//Data Frame
			}
			else{
				RxData->RTR=CAN_RIxR_Remote;//Data Frame
			}

			RxData->Index= (canBus->Register->MailBoxFIFORx[1].RDTxR&0xFF00)>>CAN_RDT1R_FMI_Pos;//Filter Match Index
		}
		SET_BIT(canBus->Register->RF1R, CAN_RF1R_RFOM1);//Release FIFO output
	}
	return canBus->Register->RF1R & CAN_RF1R_FMP1;//Return status
}

void CANx_BusOffRecovery(CAN_Handler * canBus){//Bit TEC>255
	if(CANx_GetError(canBus, CAN_ESR_BOFF)){
		SET_BIT(canBus->Register->MCR, CAN_MCR_ABOM);//SET ABOM: Recovering sequence automatic
	}
}

void CANx_CallBackRX0(CAN_Handler *can){
	if(can->Register->RF0R & CAN_RF0R_FMP0){//New Message
		CANx_RxFIFO0(can, ptrRx);//Lee el nuevo mensaje
	}
	else if(can->Register->RF0R & CAN_RF0R_FULL0){//FULL FIFO
		while(CANx_RxFIFO0(can, ptrRx)){//Lee los mensajes
			ptrRx++;//Cambiamos de dirección a siguiente estuctura
		}
	}
	else if(can->Register->RF0R & CAN_RF0R_FOVR0){//OVER FIFO
		while(CANx_RxFIFO0(can, ptrRx)){//Lee los mensajes
			ptrRx++;//Cambiamos de dirección
		}
	}
}

void CANx_CallBackRX1(CAN_Handler *can){
	if(can->Register->RF1R & CAN_RF1R_FMP1){//New Message
		CANx_RxFIFO1(can, ptrRx);//Lee el nuevo mensaje
	}
	else if(can->Register->RF1R & CAN_RF1R_FULL1){//FULL FIFO
		while(CANx_RxFIFO1(can, ptrRx)){//Lee los mensajes
			ptrRx++;//Cambiamos de dirección
		}
	}
	else if(can->Register->RF1R & CAN_RF1R_FOVR1){//OVER FIFO
		while(CANx_RxFIFO1(can, ptrRx)){//Lee los mensajes
			ptrRx++;//Cambiamos de dirección
		}
	}
}

void CANx_CallBackSCE(CAN_Handler *can){

	if(CANx_GetError(can, CAN_ESR_BOFF)){
		CANStatus=CAN_ESR_BOFF;//TEC or REC >= 255
		CANx_BusOffRecovery(can);//Enters in recovery mode
	}
	else if(CANx_GetError(can, CAN_ESR_EPVF)){
		CANStatus=CAN_ESR_EPVF;//TEC or REC >= 127
	}
	else if(CANx_GetError(can, CAN_ESR_EWGF)){
		CANStatus=CAN_ESR_EWGF;//TEC or REC >= 96
	}
	else if(CANx_GetError(can, CAN_ESR_LEC)){
		CANStatus=CAN_ESR_LEC;//Set error status
	}
	else if(can->Register->MSR&CAN_MSR_WKUI){
		CANStatus=CAN_MSR_WKUI;//Enters in Sleep mode
	}
	else if(can->Register->MSR&CAN_MSR_SLAKI){
		CANStatus=CAN_MSR_SLAKI;//Enters in Wake up mode
	}
}

void CAN1_TX_IRQHandler(){
	/* CAN1 TX interrupts                                                 */
	CANx_SetICPR(NVIC_CAN1Tx_ICPR0_Pos);
	//Becomes Empty
	if(CAN1->TSR & CAN_TSR_RQCP0){//Tx0 empty
		SET_BIT(CAN1->TSR, CAN_TSR_RQCP0);//Clear RQCP
		if(CAN1Tx){
			ptrTx->Index=0;}
	}
	else if(CAN1->TSR & CAN_TSR_RQCP1){//Tx1 empty
		SET_BIT(CAN1->TSR, CAN_TSR_RQCP1);//Clear RQCP
		if(CAN1Tx){
			ptrTx->Index=1;}
	}
	else if(CAN1->TSR & CAN_TSR_RQCP2){//Tx2 empty
		SET_BIT(CAN1->TSR, CAN_TSR_RQCP2);//Clear RQCP
		if(CAN1Tx){
			ptrTx->Index=2;}
	}
	if(CAN1Tx){//Se indica una transmisión
		CANx_Tx(can1, ptrTx);
		CANx_SetLEC(can1);
		CAN1Tx=false;
	}
}

void CAN1_RX0_IRQHandler(){
	/* CAN1 RX0 interrupts                                                */
	CANx_SetICPR(NVIC_CAN1Rx0_ICPR0_Pos);
	CANx_CallBackRX0(can1);

}
void CAN1_RX1_IRQHandler(){
	/* CAN1 RX1 interrupts                                                */
	CANx_SetICPR(NVIC_CAN1Rx1_ICPR0_Pos);
	CANx_CallBackRX1(can1);
}
void CAN1_SCE_IRQHandler(){
	/* CAN1 SCE interrupt                                                 */
	CANx_SetICPR(NVIC_CAN1SCE_ICPR0_Pos);
	CANx_CallBackSCE(can1);
}

void CAN2_TX_IRQHandler(){
	/* CAN2 TX interrupts                                                 */
	CANx_SetICPR(NVIC_CAN2Tx_ICPR1_Pos);
	//Becomes Empty

	if(CAN2->TSR & CAN_TSR_RQCP0){//Tx0 empty
		SET_BIT(CAN2->TSR, CAN_TSR_RQCP0);//Clear RQCP
		if(CAN2Tx){
			ptrTx->Index=0;}
	}
	else if(CAN2->TSR & CAN_TSR_RQCP1){//Tx1 empty
		SET_BIT(CAN2->TSR, CAN_TSR_RQCP1);//Clear RQCP
		if(CAN2Tx){
			ptrTx->Index=1;}
	}
	else if(CAN2->TSR & CAN_TSR_RQCP2){//Tx2 empty
		SET_BIT(CAN2->TSR, CAN_TSR_RQCP2);//Clear RQCP
		if(CAN2Tx){
			ptrTx->Index=2;}
	}
	if(CAN2Tx){//Se indica una transmisión
		CANx_Tx(can2, ptrTx);
		CANx_SetLEC(can2);
	}
}
void CAN2_RX0_IRQHandler(){
	/* CAN1 RX0 interrupts                                                */
	CANx_SetICPR(NVIC_CAN2Rx0_ICPR2_Pos);
	CANx_CallBackRX0(can2);
}
void CAN2_RX1_IRQHandler(){
	/* CAN1 RX1 interrupts                                                */
	CANx_SetICPR(NVIC_CAN2Rx1_ICPR2_Pos);
	CANx_CallBackRX1(can2);
}
void CAN2_SCE_IRQHandler(){
	/* CAN1 SCE interrupt                                                 */
	CANx_SetICPR(NVIC_CAN2SCE_ICPR2_Pos);
	CANx_CallBackSCE(can2);
}

void CANx_SetInt(CAN_Handler * canBus, uint32_t bitReg){
	SET_BIT(canBus->Register->IER, bitReg);
}

void CANx_ResetInt(CAN_Handler * canBus, uint32_t bitReg){
	CLEAR_BIT(canBus->Register->IER, bitReg);
}

void CANx_EnTxInt(CAN_Handler * canBus){
	SET_BIT(canBus->Register->IER, CAN_IER_TMEIE);
}

void CANx_DisTxInt(CAN_Handler * canBus){
	CLEAR_BIT(canBus->Register->IER, CAN_IER_TMEIE);
}

void CANx_EnFIFO0Ints(CAN_Handler * canBus){
	SET_BIT(canBus->Register->IER, CAN_IER_FMPIE0|CAN_IER_FFIE0|CAN_IER_FOVIE0);
}

void CANx_DisFIFO0Ints(CAN_Handler * canBus){
	CLEAR_BIT(canBus->Register->IER, CAN_IER_FMPIE0|CAN_IER_FFIE0|CAN_IER_FOVIE0);
}

void CANx_EnFIFO1Ints(CAN_Handler * canBus){
	SET_BIT(canBus->Register->IER, CAN_IER_FMPIE1|CAN_IER_FFIE1|CAN_IER_FOVIE1);
}

void CANx_DisFIFO1Ints(CAN_Handler * canBus){
	CLEAR_BIT(canBus->Register->IER, CAN_IER_FMPIE1|CAN_IER_FFIE1|CAN_IER_FOVIE1);
}

void CANx_EnSECInts(CAN_Handler * canBus){
	SET_BIT(canBus->Register->IER, CAN_IER_ERRIE|CAN_IER_EWGIE|CAN_IER_EPVIE|CAN_IER_BOFIE|CAN_IER_LECIE);
}

void CANx_DisSECInts(CAN_Handler * canBus){
	CLEAR_BIT(canBus->Register->IER, CAN_IER_ERRIE|CAN_IER_EWGIE|CAN_IER_EPVIE|CAN_IER_BOFIE|CAN_IER_LECIE);
}

void CANx_EnWakeupInt(CAN_Handler * canBus){
	SET_BIT(canBus->Register->IER, CAN_IER_WKUIE);
}

void CANx_DisWakeupInt(CAN_Handler * canBus){
	CLEAR_BIT(canBus->Register->IER, CAN_IER_WKUIE);
}

void CANx_EnSleepInt(CAN_Handler * canBus){
	SET_BIT(canBus->Register->IER, CAN_IER_SLKIE);
}

void CANx_DisSleepInt(CAN_Handler * canBus){
	CLEAR_BIT(canBus->Register->IER, CAN_IER_SLKIE);
}

uint32_t CANx_GetError(CAN_Handler * canBus, uint32_t bitReg){
	return canBus->Register->ESR & bitReg;
}

uint8_t CANx_GetLEC(CAN_Handler * canBus){
	return CANx_GetError(canBus, CAN_ESR_LEC);
}

void CANx_SetLEC(CAN_Handler * canBus){
	canBus->Register->ESR |= CAN_ESR_LEC;
}

/*
 * Receive error counter
 */
uint8_t CANx_GetREC(CAN_Handler * canBus){
	return (CANx_GetError(canBus, CAN_ESR_REC)>>CAN_ESR_REC_Pos);
}

/*
 * Transmit error counter
 */
uint8_t CANx_GetTEC(CAN_Handler * canBus){
	return (CANx_GetError(canBus, CAN_ESR_TEC)>>CAN_ESR_TEC_Pos);
}

bool CANx_TxSuccess(volatile uint32_t *SR, uint8_t indexMailBox){
	bool flag=true;
	if(indexMailBox == 0){
		//LEC?
		while((!((*SR) & CAN_TSR_RQCP0))&&(!((*SR) & CAN_TSR_TXOK0))&&(!((*SR) & CAN_TSR_ALST0))&&(!((*SR) & CAN_TSR_TERR0)));//Espera alguna bandera

		if(((*SR) & CAN_TSR_ALST0)||((*SR) & CAN_TSR_TERR0)){//Error de transmisión
			flag = false;
		}
		else if(((*SR) & CAN_TSR_RQCP0)){
			while(!((*SR) & CAN_TSR_TXOK0));
			flag=true;
		}
		else if(((*SR) & CAN_TSR_TXOK0)){
			while(!((*SR) & CAN_TSR_RQCP0));
			flag=true;
		}

	}
	else if(indexMailBox ==1){
		while((!((*SR) & CAN_TSR_RQCP1))&&(!((*SR) & CAN_TSR_TXOK1))&&(!((*SR) & CAN_TSR_ALST1))&&(!((*SR) & CAN_TSR_TERR1)));//Espera alguna bandera

		if(((*SR) & CAN_TSR_ALST1)||((*SR) & CAN_TSR_TERR1)){//Error de transmisión
			flag = false;
		}
		else if(((*SR) & CAN_TSR_RQCP1)){
			while(((*SR) & CAN_TSR_TXOK1));
			flag=true;
		}
		else if(((*SR) & CAN_TSR_TXOK1)){
			while(((*SR) & CAN_TSR_RQCP1));
			flag=true;
		}
	}
	else if(indexMailBox == 2){
		while((!((*SR) & CAN_TSR_RQCP2))&&(!((*SR) & CAN_TSR_TXOK2))&&(!((*SR) & CAN_TSR_ALST2))&&(!((*SR) & CAN_TSR_TERR2)));//Espera alguna bandera

		if(((*SR) & CAN_TSR_ALST2)||((*SR) & CAN_TSR_TERR2)){//Error de transmisión
			flag = false;
		}
		else if(((*SR) & CAN_TSR_RQCP2)){
			while(((*SR) & CAN_TSR_TXOK2));
			flag=true;
		}
		else if(((*SR) & CAN_TSR_TXOK2)){
			while(((*SR) & CAN_TSR_RQCP2));
			flag=true;
		}
	}

	return flag;
}

void CANx_WaitSetFlag(volatile uint32_t *SR, uint32_t BitReg){
	//uint32_t flag = (*SR) & BitReg;
	while(!((*SR) & BitReg)){
		//flag = (*SR) & BitReg;
	}
}

void CANx_WaitResetFlag(volatile uint32_t *SR, uint32_t BitReg){
	//uint32_t flag = (*SR) & BitReg;
	while(((*SR) & BitReg)){
		//flag = (*SR) & BitReg;
	}
}

void CANx_SetICPR(uint8_t x){
	if(x==NVIC_CAN1Tx_ICPR0_Pos){
		NVIC_ICPR0 |= (1<<NVIC_CAN1Tx_ICPR0_Pos); //Limpia posible bandera pendiente
	}
	else if(x==NVIC_CAN1Rx0_ICPR0_Pos){
		NVIC_ICPR0 |= (1<<NVIC_CAN1Rx0_ICPR0_Pos); //Limpia posible bandera pendiente
	}
	else if(x==NVIC_CAN1Rx1_ICPR0_Pos){
		NVIC_ICPR0 |= (1<<NVIC_CAN1Rx1_ICPR0_Pos); //Limpia posible bandera pendiente
	}
	else if(x==NVIC_CAN1SCE_ICPR0_Pos){
		NVIC_ICPR0 |= (1<<NVIC_CAN1SCE_ICPR0_Pos); //Limpia posible bandera pendiente
	}
	else if(x==NVIC_CAN2Tx_ICPR1_Pos){
		NVIC_ICPR1 |= (1<<NVIC_CAN2Tx_ICPR1_Pos); //Limpia posible bandera pendiente
	}
	else if(x==NVIC_CAN2Rx0_ICPR2_Pos){
		NVIC_ICPR2 |= (1<<NVIC_CAN2Rx0_ICPR2_Pos); //Limpia posible bandera pendiente
	}
	else if(x==NVIC_CAN2Rx1_ICPR2_Pos){
		NVIC_ICPR2 |= (1<<NVIC_CAN2Rx1_ICPR2_Pos); //Limpia posible bandera pendiente
	}
	else if(x==NVIC_CAN2SCE_ICPR2_Pos){
		NVIC_ICPR2 |= (1<<NVIC_CAN2SCE_ICPR2_Pos); //Limpia posible bandera pendiente
	}

}
