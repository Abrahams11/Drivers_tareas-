/*
 * CANx.h
 *
 *  Created on: 23 ene 2023
 *      Author: jurl9
 */

#ifndef DRIVERS_PERIPHERAL_INC_CANX_H_
#define DRIVERS_PERIPHERAL_INC_CANX_H_

#include "stdio.h"
#include "stdbool.h"
#include "MacroFunctions.h"
#include "GPIOx.h"

extern bool CAN1Tx, CAN2Tx;
extern uint8_t CANStatus;

#define CAN1_Tx_IRQ              19UL
#define CAN1_Rx0_IRQ             20UL
#define CAN1_Rx1_IRQ             21UL
#define CAN1_SCE_IRQ             22UL

#define CAN2_Tx_IRQ              63UL
#define CAN2_Rx0_IRQ             64UL
#define CAN2_Rx1_IRQ             65UL
#define CAN2_SCE_IRQ             66UL

#define NVIC_CAN1Tx_ICPR0_Pos    19UL
#define NVIC_CAN1Rx0_ICPR0_Pos   20UL
#define NVIC_CAN1Rx1_ICPR0_Pos   21UL
#define NVIC_CAN1SCE_ICPR0_Pos   22UL

#define NVIC_CAN2Tx_ICPR1_Pos    31UL
#define NVIC_CAN2Rx0_ICPR2_Pos    0UL
#define NVIC_CAN2Rx1_ICPR2_Pos    1UL
#define NVIC_CAN2SCE_ICPR2_Pos    2UL

#define CAN_BASE    0x40006400

typedef struct{
	uint32_t  bps;
	uint8_t   ntq;
	uint8_t   SJW;
}CAN_BitTimingTypeDef;

typedef struct{
	uint8_t   indexFltr;
	uint8_t   bitscale;
	uint16_t  ID_L;
	uint16_t  ID_H;
	uint16_t  Mask_L;
	uint16_t  Mask_H;
	uint32_t  modeFltr;
	uint8_t   FIFO;
	bool      IDE;
}CAN_FilterTypeDef;

typedef struct{
	bool      IDE;
	uint8_t   indexFltr;
	uint16_t  ID_L;
	uint16_t  ID_H;
	uint16_t  Mask_L;
	uint16_t  Mask_H;
}CAN_DualFilterID_n_MaskTypeDef;

typedef struct{
	uint32_t Identifier;
	bool     IDE;
	uint8_t  DLC;
	uint8_t  RTR;
	uint32_t DataH;
	uint32_t DataL;
	uint8_t  Index;               //For Rx Index is for filter; For Tx Index is for Mailbox
}CAN_TxandRxHeader_TypeDef;

//x=0,1,2.

typedef struct
{
	volatile uint32_t     TIxR;
	volatile uint32_t    TDTxR;
	volatile uint32_t    TDLxR;
	volatile uint32_t    TDHxR;

}CAN_TypeDef_MailBoxTx;

typedef struct
{
	volatile uint32_t     RIxR;
	volatile uint32_t    RDTxR;
	volatile uint32_t    RDLxR;
	volatile uint32_t    RDHxR;

}CAN_TypeDef_MailBoxFIFORx;

typedef struct
{
	//i=0,1,...,27
	volatile uint32_t     FiR1;
	volatile uint32_t     FiR2;

}CAN_TypeDef_FilterBankRegister;

typedef struct
{
	volatile uint32_t                       MCR;
	volatile uint32_t                       MSR;
	volatile uint32_t                       TSR;
	volatile uint32_t                      RF0R;
	volatile uint32_t                      RF1R;
	volatile uint32_t                       IER;
	volatile uint32_t                       ESR;
	volatile uint32_t                       BTR;
    uint32_t                      RESERVED0[88];
	CAN_TypeDef_MailBoxTx          MailBoxTx[3];
	CAN_TypeDef_MailBoxFIFORx  MailBoxFIFORx[2];
	uint32_t                      RESERVED1[12];
	volatile uint32_t                       FMR;
	volatile uint32_t                      FM1R;
	uint32_t                          RESERVED2;
	volatile uint32_t                      FS1R;
	uint32_t                          RESERVED3;
	volatile uint32_t                     FFA1R;
	uint32_t                          RESERVED4;
	volatile uint32_t                      FA1R;
	uint32_t                       RESERVED5[8];
	CAN_TypeDef_FilterBankRegister      FiR[28];

}CAN_TypeDef;

typedef struct{
	CAN_TypeDef    *Register;//Registros de CAN
}CAN_Handler;

#define CAN1    ((CAN_TypeDef *)(CAN_BASE + 0x000UL))
#define CAN2    ((CAN_TypeDef *)(CAN_BASE + 0x400UL))


extern CAN_Handler *can1, *can2;

extern CAN_TxandRxHeader_TypeDef *ptrRx, *ptrTx;

/******************************************************************************/
/*                                                                            */
/*                         Controller Area Network                            */
/*                                                                            */
/******************************************************************************/
/*!<CAN control and status registers */
/*******************  Bit definition for CAN_MCR register  ********************/
#define CAN_MCR_INRQ_Pos       (0U)
#define CAN_MCR_INRQ_Msk       (0x1UL << CAN_MCR_INRQ_Pos)                      /*!< 0x00000001 */
#define CAN_MCR_INRQ           CAN_MCR_INRQ_Msk                                /*!<Initialization Request */
#define CAN_MCR_SLEEP_Pos      (1U)
#define CAN_MCR_SLEEP_Msk      (0x1UL << CAN_MCR_SLEEP_Pos)                     /*!< 0x00000002 */
#define CAN_MCR_SLEEP          CAN_MCR_SLEEP_Msk                               /*!<Sleep Mode Request */
#define CAN_MCR_TXFP_Pos       (2U)
#define CAN_MCR_TXFP_Msk       (0x1UL << CAN_MCR_TXFP_Pos)                      /*!< 0x00000004 */
#define CAN_MCR_TXFP           CAN_MCR_TXFP_Msk                                /*!<Transmit FIFO Priority */
#define CAN_MCR_RFLM_Pos       (3U)
#define CAN_MCR_RFLM_Msk       (0x1UL << CAN_MCR_RFLM_Pos)                      /*!< 0x00000008 */
#define CAN_MCR_RFLM           CAN_MCR_RFLM_Msk                                /*!<Receive FIFO Locked Mode */
#define CAN_MCR_NART_Pos       (4U)
#define CAN_MCR_NART_Msk       (0x1UL << CAN_MCR_NART_Pos)                      /*!< 0x00000010 */
#define CAN_MCR_NART           CAN_MCR_NART_Msk                                /*!<No Automatic Retransmission */
#define CAN_MCR_AWUM_Pos       (5U)
#define CAN_MCR_AWUM_Msk       (0x1UL << CAN_MCR_AWUM_Pos)                      /*!< 0x00000020 */
#define CAN_MCR_AWUM           CAN_MCR_AWUM_Msk                                /*!<Automatic Wakeup Mode */
#define CAN_MCR_ABOM_Pos       (6U)
#define CAN_MCR_ABOM_Msk       (0x1UL << CAN_MCR_ABOM_Pos)                      /*!< 0x00000040 */
#define CAN_MCR_ABOM           CAN_MCR_ABOM_Msk                                /*!<Automatic Bus-Off Management */
#define CAN_MCR_TTCM_Pos       (7U)
#define CAN_MCR_TTCM_Msk       (0x1UL << CAN_MCR_TTCM_Pos)                      /*!< 0x00000080 */
#define CAN_MCR_TTCM           CAN_MCR_TTCM_Msk                                /*!<Time Triggered Communication Mode */
#define CAN_MCR_RESET_Pos      (15U)
#define CAN_MCR_RESET_Msk      (0x1UL << CAN_MCR_RESET_Pos)                     /*!< 0x00008000 */
#define CAN_MCR_RESET          CAN_MCR_RESET_Msk                               /*!<bxCAN software master reset */
#define CAN_MCR_DBF_Pos        (16U)
#define CAN_MCR_DBF_Msk        (0x1UL << CAN_MCR_DBF_Pos)                       /*!< 0x00010000 */
#define CAN_MCR_DBF            CAN_MCR_DBF_Msk                                 /*!<bxCAN Debug freeze */
/*******************  Bit definition for CAN_MSR register  ********************/
#define CAN_MSR_INAK_Pos       (0U)
#define CAN_MSR_INAK_Msk       (0x1UL << CAN_MSR_INAK_Pos)                      /*!< 0x00000001 */
#define CAN_MSR_INAK           CAN_MSR_INAK_Msk                                /*!<Initialization Acknowledge */
#define CAN_MSR_SLAK_Pos       (1U)
#define CAN_MSR_SLAK_Msk       (0x1UL << CAN_MSR_SLAK_Pos)                      /*!< 0x00000002 */
#define CAN_MSR_SLAK           CAN_MSR_SLAK_Msk                                /*!<Sleep Acknowledge */
#define CAN_MSR_ERRI_Pos       (2U)
#define CAN_MSR_ERRI_Msk       (0x1UL << CAN_MSR_ERRI_Pos)                      /*!< 0x00000004 */
#define CAN_MSR_ERRI           CAN_MSR_ERRI_Msk                                /*!<Error Interrupt */
#define CAN_MSR_WKUI_Pos       (3U)
#define CAN_MSR_WKUI_Msk       (0x1UL << CAN_MSR_WKUI_Pos)                      /*!< 0x00000008 */
#define CAN_MSR_WKUI           CAN_MSR_WKUI_Msk                                /*!<Wakeup Interrupt */
#define CAN_MSR_SLAKI_Pos      (4U)
#define CAN_MSR_SLAKI_Msk      (0x1UL << CAN_MSR_SLAKI_Pos)                     /*!< 0x00000010 */
#define CAN_MSR_SLAKI          CAN_MSR_SLAKI_Msk                               /*!<Sleep Acknowledge Interrupt */
#define CAN_MSR_TXM_Pos        (8U)
#define CAN_MSR_TXM_Msk        (0x1UL << CAN_MSR_TXM_Pos)                       /*!< 0x00000100 */
#define CAN_MSR_TXM            CAN_MSR_TXM_Msk                                 /*!<Transmit Mode */
#define CAN_MSR_RXM_Pos        (9U)
#define CAN_MSR_RXM_Msk        (0x1UL << CAN_MSR_RXM_Pos)                       /*!< 0x00000200 */
#define CAN_MSR_RXM            CAN_MSR_RXM_Msk                                 /*!<Receive Mode */
#define CAN_MSR_SAMP_Pos       (10U)
#define CAN_MSR_SAMP_Msk       (0x1UL << CAN_MSR_SAMP_Pos)                      /*!< 0x00000400 */
#define CAN_MSR_SAMP           CAN_MSR_SAMP_Msk                                /*!<Last Sample Point */
#define CAN_MSR_RX_Pos         (11U)
#define CAN_MSR_RX_Msk         (0x1UL << CAN_MSR_RX_Pos)                        /*!< 0x00000800 */
#define CAN_MSR_RX             CAN_MSR_RX_Msk                                  /*!<CAN Rx Signal */

/*******************  Bit definition for CAN_TSR register  ********************/
#define CAN_TSR_RQCP0_Pos      (0U)
#define CAN_TSR_RQCP0_Msk      (0x1UL << CAN_TSR_RQCP0_Pos)                     /*!< 0x00000001 */
#define CAN_TSR_RQCP0          CAN_TSR_RQCP0_Msk                               /*!<Request Completed Mailbox0 */
#define CAN_TSR_TXOK0_Pos      (1U)
#define CAN_TSR_TXOK0_Msk      (0x1UL << CAN_TSR_TXOK0_Pos)                     /*!< 0x00000002 */
#define CAN_TSR_TXOK0          CAN_TSR_TXOK0_Msk                               /*!<Transmission OK of Mailbox0 */
#define CAN_TSR_ALST0_Pos      (2U)
#define CAN_TSR_ALST0_Msk      (0x1UL << CAN_TSR_ALST0_Pos)                     /*!< 0x00000004 */
#define CAN_TSR_ALST0          CAN_TSR_ALST0_Msk                               /*!<Arbitration Lost for Mailbox0 */
#define CAN_TSR_TERR0_Pos      (3U)
#define CAN_TSR_TERR0_Msk      (0x1UL << CAN_TSR_TERR0_Pos)                     /*!< 0x00000008 */
#define CAN_TSR_TERR0          CAN_TSR_TERR0_Msk                               /*!<Transmission Error of Mailbox0 */
#define CAN_TSR_ABRQ0_Pos      (7U)
#define CAN_TSR_ABRQ0_Msk      (0x1UL << CAN_TSR_ABRQ0_Pos)                     /*!< 0x00000080 */
#define CAN_TSR_ABRQ0          CAN_TSR_ABRQ0_Msk                               /*!<Abort Request for Mailbox0 */
#define CAN_TSR_RQCP1_Pos      (8U)
#define CAN_TSR_RQCP1_Msk      (0x1UL << CAN_TSR_RQCP1_Pos)                     /*!< 0x00000100 */
#define CAN_TSR_RQCP1          CAN_TSR_RQCP1_Msk                               /*!<Request Completed Mailbox1 */
#define CAN_TSR_TXOK1_Pos      (9U)
#define CAN_TSR_TXOK1_Msk      (0x1UL << CAN_TSR_TXOK1_Pos)                     /*!< 0x00000200 */
#define CAN_TSR_TXOK1          CAN_TSR_TXOK1_Msk                               /*!<Transmission OK of Mailbox1 */
#define CAN_TSR_ALST1_Pos      (10U)
#define CAN_TSR_ALST1_Msk      (0x1UL << CAN_TSR_ALST1_Pos)                     /*!< 0x00000400 */
#define CAN_TSR_ALST1          CAN_TSR_ALST1_Msk                               /*!<Arbitration Lost for Mailbox1 */
#define CAN_TSR_TERR1_Pos      (11U)
#define CAN_TSR_TERR1_Msk      (0x1UL << CAN_TSR_TERR1_Pos)                     /*!< 0x00000800 */
#define CAN_TSR_TERR1          CAN_TSR_TERR1_Msk                               /*!<Transmission Error of Mailbox1 */
#define CAN_TSR_ABRQ1_Pos      (15U)
#define CAN_TSR_ABRQ1_Msk      (0x1UL << CAN_TSR_ABRQ1_Pos)                     /*!< 0x00008000 */
#define CAN_TSR_ABRQ1          CAN_TSR_ABRQ1_Msk                               /*!<Abort Request for Mailbox 1 */
#define CAN_TSR_RQCP2_Pos      (16U)
#define CAN_TSR_RQCP2_Msk      (0x1UL << CAN_TSR_RQCP2_Pos)                     /*!< 0x00010000 */
#define CAN_TSR_RQCP2          CAN_TSR_RQCP2_Msk                               /*!<Request Completed Mailbox2 */
#define CAN_TSR_TXOK2_Pos      (17U)
#define CAN_TSR_TXOK2_Msk      (0x1UL << CAN_TSR_TXOK2_Pos)                     /*!< 0x00020000 */
#define CAN_TSR_TXOK2          CAN_TSR_TXOK2_Msk                               /*!<Transmission OK of Mailbox 2 */
#define CAN_TSR_ALST2_Pos      (18U)
#define CAN_TSR_ALST2_Msk      (0x1UL << CAN_TSR_ALST2_Pos)                     /*!< 0x00040000 */
#define CAN_TSR_ALST2          CAN_TSR_ALST2_Msk                               /*!<Arbitration Lost for mailbox 2 */
#define CAN_TSR_TERR2_Pos      (19U)
#define CAN_TSR_TERR2_Msk      (0x1UL << CAN_TSR_TERR2_Pos)                     /*!< 0x00080000 */
#define CAN_TSR_TERR2          CAN_TSR_TERR2_Msk                               /*!<Transmission Error of Mailbox 2 */
#define CAN_TSR_ABRQ2_Pos      (23U)
#define CAN_TSR_ABRQ2_Msk      (0x1UL << CAN_TSR_ABRQ2_Pos)                     /*!< 0x00800000 */
#define CAN_TSR_ABRQ2          CAN_TSR_ABRQ2_Msk                               /*!<Abort Request for Mailbox 2 */
#define CAN_TSR_CODE_Pos       (24U)
#define CAN_TSR_CODE_Msk       (0x3UL << CAN_TSR_CODE_Pos)                      /*!< 0x03000000 */
#define CAN_TSR_CODE           CAN_TSR_CODE_Msk                                /*!<Mailbox Code */

#define CAN_TSR_TME_Pos        (26U)
#define CAN_TSR_TME_Msk        (0x7UL << CAN_TSR_TME_Pos)                       /*!< 0x1C000000 */
#define CAN_TSR_TME            CAN_TSR_TME_Msk                                 /*!<TME[2:0] bits */
#define CAN_TSR_TME0_Pos       (26U)
#define CAN_TSR_TME0_Msk       (0x1UL << CAN_TSR_TME0_Pos)                      /*!< 0x04000000 */
#define CAN_TSR_TME0           CAN_TSR_TME0_Msk                                /*!<Transmit Mailbox 0 Empty */
#define CAN_TSR_TME1_Pos       (27U)
#define CAN_TSR_TME1_Msk       (0x1UL << CAN_TSR_TME1_Pos)                      /*!< 0x08000000 */
#define CAN_TSR_TME1           CAN_TSR_TME1_Msk                                /*!<Transmit Mailbox 1 Empty */
#define CAN_TSR_TME2_Pos       (28U)
#define CAN_TSR_TME2_Msk       (0x1UL << CAN_TSR_TME2_Pos)                      /*!< 0x10000000 */
#define CAN_TSR_TME2           CAN_TSR_TME2_Msk                                /*!<Transmit Mailbox 2 Empty */

#define CAN_TSR_LOW_Pos        (29U)
#define CAN_TSR_LOW_Msk        (0x7UL << CAN_TSR_LOW_Pos)                       /*!< 0xE0000000 */
#define CAN_TSR_LOW            CAN_TSR_LOW_Msk                                 /*!<LOW[2:0] bits */
#define CAN_TSR_LOW0_Pos       (29U)
#define CAN_TSR_LOW0_Msk       (0x1UL << CAN_TSR_LOW0_Pos)                      /*!< 0x20000000 */
#define CAN_TSR_LOW0           CAN_TSR_LOW0_Msk                                /*!<Lowest Priority Flag for Mailbox 0 */
#define CAN_TSR_LOW1_Pos       (30U)
#define CAN_TSR_LOW1_Msk       (0x1UL << CAN_TSR_LOW1_Pos)                      /*!< 0x40000000 */
#define CAN_TSR_LOW1           CAN_TSR_LOW1_Msk                                /*!<Lowest Priority Flag for Mailbox 1 */
#define CAN_TSR_LOW2_Pos       (31U)
#define CAN_TSR_LOW2_Msk       (0x1UL << CAN_TSR_LOW2_Pos)                      /*!< 0x80000000 */
#define CAN_TSR_LOW2           CAN_TSR_LOW2_Msk                                /*!<Lowest Priority Flag for Mailbox 2 */

/*******************  Bit definition for CAN_RF0R register  *******************/
#define CAN_RF0R_FMP0_Pos      (0U)
#define CAN_RF0R_FMP0_Msk      (0x3UL << CAN_RF0R_FMP0_Pos)                     /*!< 0x00000003 */
#define CAN_RF0R_FMP0          CAN_RF0R_FMP0_Msk                               /*!<FIFO 0 Message Pending */
#define CAN_RF0R_FULL0_Pos     (3U)
#define CAN_RF0R_FULL0_Msk     (0x1UL << CAN_RF0R_FULL0_Pos)                    /*!< 0x00000008 */
#define CAN_RF0R_FULL0         CAN_RF0R_FULL0_Msk                              /*!<FIFO 0 Full */
#define CAN_RF0R_FOVR0_Pos     (4U)
#define CAN_RF0R_FOVR0_Msk     (0x1UL << CAN_RF0R_FOVR0_Pos)                    /*!< 0x00000010 */
#define CAN_RF0R_FOVR0         CAN_RF0R_FOVR0_Msk                              /*!<FIFO 0 Overrun */
#define CAN_RF0R_RFOM0_Pos     (5U)
#define CAN_RF0R_RFOM0_Msk     (0x1UL << CAN_RF0R_RFOM0_Pos)                    /*!< 0x00000020 */
#define CAN_RF0R_RFOM0         CAN_RF0R_RFOM0_Msk                              /*!<Release FIFO 0 Output Mailbox */

/*******************  Bit definition for CAN_RF1R register  *******************/
#define CAN_RF1R_FMP1_Pos      (0U)
#define CAN_RF1R_FMP1_Msk      (0x3UL << CAN_RF1R_FMP1_Pos)                     /*!< 0x00000003 */
#define CAN_RF1R_FMP1          CAN_RF1R_FMP1_Msk                               /*!<FIFO 1 Message Pending */
#define CAN_RF1R_FULL1_Pos     (3U)
#define CAN_RF1R_FULL1_Msk     (0x1UL << CAN_RF1R_FULL1_Pos)                    /*!< 0x00000008 */
#define CAN_RF1R_FULL1         CAN_RF1R_FULL1_Msk                              /*!<FIFO 1 Full */
#define CAN_RF1R_FOVR1_Pos     (4U)
#define CAN_RF1R_FOVR1_Msk     (0x1UL << CAN_RF1R_FOVR1_Pos)                    /*!< 0x00000010 */
#define CAN_RF1R_FOVR1         CAN_RF1R_FOVR1_Msk                              /*!<FIFO 1 Overrun */
#define CAN_RF1R_RFOM1_Pos     (5U)
#define CAN_RF1R_RFOM1_Msk     (0x1UL << CAN_RF1R_RFOM1_Pos)                    /*!< 0x00000020 */
#define CAN_RF1R_RFOM1         CAN_RF1R_RFOM1_Msk                              /*!<Release FIFO 1 Output Mailbox */

/********************  Bit definition for CAN_IER register  *******************/
#define CAN_IER_TMEIE_Pos      (0U)
#define CAN_IER_TMEIE_Msk      (0x1UL << CAN_IER_TMEIE_Pos)                     /*!< 0x00000001 */
#define CAN_IER_TMEIE          CAN_IER_TMEIE_Msk                               /*!<Transmit Mailbox Empty Interrupt Enable */
#define CAN_IER_FMPIE0_Pos     (1U)
#define CAN_IER_FMPIE0_Msk     (0x1UL << CAN_IER_FMPIE0_Pos)                    /*!< 0x00000002 */
#define CAN_IER_FMPIE0         CAN_IER_FMPIE0_Msk                              /*!<FIFO Message Pending Interrupt Enable */
#define CAN_IER_FFIE0_Pos      (2U)
#define CAN_IER_FFIE0_Msk      (0x1UL << CAN_IER_FFIE0_Pos)                     /*!< 0x00000004 */
#define CAN_IER_FFIE0          CAN_IER_FFIE0_Msk                               /*!<FIFO Full Interrupt Enable */
#define CAN_IER_FOVIE0_Pos     (3U)
#define CAN_IER_FOVIE0_Msk     (0x1UL << CAN_IER_FOVIE0_Pos)                    /*!< 0x00000008 */
#define CAN_IER_FOVIE0         CAN_IER_FOVIE0_Msk                              /*!<FIFO Overrun Interrupt Enable */
#define CAN_IER_FMPIE1_Pos     (4U)
#define CAN_IER_FMPIE1_Msk     (0x1UL << CAN_IER_FMPIE1_Pos)                    /*!< 0x00000010 */
#define CAN_IER_FMPIE1         CAN_IER_FMPIE1_Msk                              /*!<FIFO Message Pending Interrupt Enable */
#define CAN_IER_FFIE1_Pos      (5U)
#define CAN_IER_FFIE1_Msk      (0x1UL << CAN_IER_FFIE1_Pos)                     /*!< 0x00000020 */
#define CAN_IER_FFIE1          CAN_IER_FFIE1_Msk                               /*!<FIFO Full Interrupt Enable */
#define CAN_IER_FOVIE1_Pos     (6U)
#define CAN_IER_FOVIE1_Msk     (0x1UL << CAN_IER_FOVIE1_Pos)                    /*!< 0x00000040 */
#define CAN_IER_FOVIE1         CAN_IER_FOVIE1_Msk                              /*!<FIFO Overrun Interrupt Enable */
#define CAN_IER_EWGIE_Pos      (8U)
#define CAN_IER_EWGIE_Msk      (0x1UL << CAN_IER_EWGIE_Pos)                     /*!< 0x00000100 */
#define CAN_IER_EWGIE          CAN_IER_EWGIE_Msk                               /*!<Error Warning Interrupt Enable */
#define CAN_IER_EPVIE_Pos      (9U)
#define CAN_IER_EPVIE_Msk      (0x1UL << CAN_IER_EPVIE_Pos)                     /*!< 0x00000200 */
#define CAN_IER_EPVIE          CAN_IER_EPVIE_Msk                               /*!<Error Passive Interrupt Enable */
#define CAN_IER_BOFIE_Pos      (10U)
#define CAN_IER_BOFIE_Msk      (0x1UL << CAN_IER_BOFIE_Pos)                     /*!< 0x00000400 */
#define CAN_IER_BOFIE          CAN_IER_BOFIE_Msk                               /*!<Bus-Off Interrupt Enable */
#define CAN_IER_LECIE_Pos      (11U)
#define CAN_IER_LECIE_Msk      (0x1UL << CAN_IER_LECIE_Pos)                     /*!< 0x00000800 */
#define CAN_IER_LECIE          CAN_IER_LECIE_Msk                               /*!<Last Error Code Interrupt Enable */
#define CAN_IER_ERRIE_Pos      (15U)
#define CAN_IER_ERRIE_Msk      (0x1UL << CAN_IER_ERRIE_Pos)                     /*!< 0x00008000 */
#define CAN_IER_ERRIE          CAN_IER_ERRIE_Msk                               /*!<Error Interrupt Enable */
#define CAN_IER_WKUIE_Pos      (16U)
#define CAN_IER_WKUIE_Msk      (0x1UL << CAN_IER_WKUIE_Pos)                     /*!< 0x00010000 */
#define CAN_IER_WKUIE          CAN_IER_WKUIE_Msk                               /*!<Wakeup Interrupt Enable */
#define CAN_IER_SLKIE_Pos      (17U)
#define CAN_IER_SLKIE_Msk      (0x1UL << CAN_IER_SLKIE_Pos)                     /*!< 0x00020000 */
#define CAN_IER_SLKIE          CAN_IER_SLKIE_Msk                               /*!<Sleep Interrupt Enable */
#define CAN_IER_EWGIE_Pos      (8U)

/********************  Bit definition for CAN_ESR register  *******************/
#define CAN_ESR_EWGF_Pos       (0U)
#define CAN_ESR_EWGF_Msk       (0x1UL << CAN_ESR_EWGF_Pos)                      /*!< 0x00000001 */
#define CAN_ESR_EWGF           CAN_ESR_EWGF_Msk                                /*!<Error Warning Flag */
#define CAN_ESR_EPVF_Pos       (1U)
#define CAN_ESR_EPVF_Msk       (0x1UL << CAN_ESR_EPVF_Pos)                      /*!< 0x00000002 */
#define CAN_ESR_EPVF           CAN_ESR_EPVF_Msk                                /*!<Error Passive Flag */
#define CAN_ESR_BOFF_Pos       (2U)
#define CAN_ESR_BOFF_Msk       (0x1UL << CAN_ESR_BOFF_Pos)                      /*!< 0x00000004 */
#define CAN_ESR_BOFF           CAN_ESR_BOFF_Msk                                /*!<Bus-Off Flag */

#define CAN_ESR_LEC_Pos        (4U)
#define CAN_ESR_LEC_Msk        (0x7UL << CAN_ESR_LEC_Pos)                       /*!< 0x00000070 */
#define CAN_ESR_LEC            CAN_ESR_LEC_Msk                                 /*!<LEC[2:0] bits (Last Error Code) */
#define CAN_ESR_LEC_0          (0x1UL << CAN_ESR_LEC_Pos)                       /*!< 0x00000010 */
#define CAN_ESR_LEC_1          (0x2UL << CAN_ESR_LEC_Pos)                       /*!< 0x00000020 */
#define CAN_ESR_LEC_2          (0x4UL << CAN_ESR_LEC_Pos)                       /*!< 0x00000040 */

#define CAN_ESR_TEC_Pos        (16U)
#define CAN_ESR_TEC_Msk        (0xFFUL << CAN_ESR_TEC_Pos)                      /*!< 0x00FF0000 */
#define CAN_ESR_TEC            CAN_ESR_TEC_Msk                                 /*!<Least significant byte of the 9-bit Transmit Error Counter */
#define CAN_ESR_REC_Pos        (24U)
#define CAN_ESR_REC_Msk        (0xFFUL << CAN_ESR_REC_Pos)                      /*!< 0xFF000000 */
#define CAN_ESR_REC            CAN_ESR_REC_Msk                                 /*!<Receive Error Counter */

/*******************  Bit definition for CAN_BTR register  ********************/
#define CAN_BTR_BRP_Pos        (0U)
#define CAN_BTR_BRP_Msk        (0x3FFUL << CAN_BTR_BRP_Pos)                     /*!< 0x000003FF */
#define CAN_BTR_BRP            CAN_BTR_BRP_Msk                                 /*!<Baud Rate Prescaler */
#define CAN_BTR_TS1_Pos        (16U)
#define CAN_BTR_TS1_Msk        (0xFUL << CAN_BTR_TS1_Pos)                       /*!< 0x000F0000 */
#define CAN_BTR_TS1            CAN_BTR_TS1_Msk                                 /*!<Time Segment 1 */
#define CAN_BTR_TS1_0          (0x1UL << CAN_BTR_TS1_Pos)                       /*!< 0x00010000 */
#define CAN_BTR_TS1_1          (0x2UL << CAN_BTR_TS1_Pos)                       /*!< 0x00020000 */
#define CAN_BTR_TS1_2          (0x4UL << CAN_BTR_TS1_Pos)                       /*!< 0x00040000 */
#define CAN_BTR_TS1_3          (0x8UL << CAN_BTR_TS1_Pos)                       /*!< 0x00080000 */
#define CAN_BTR_TS2_Pos        (20U)
#define CAN_BTR_TS2_Msk        (0x7UL << CAN_BTR_TS2_Pos)                       /*!< 0x00700000 */
#define CAN_BTR_TS2            CAN_BTR_TS2_Msk                                 /*!<Time Segment 2 */
#define CAN_BTR_TS2_0          (0x1UL << CAN_BTR_TS2_Pos)                       /*!< 0x00100000 */
#define CAN_BTR_TS2_1          (0x2UL << CAN_BTR_TS2_Pos)                       /*!< 0x00200000 */
#define CAN_BTR_TS2_2          (0x4UL << CAN_BTR_TS2_Pos)                       /*!< 0x00400000 */
#define CAN_BTR_SJW_Pos        (24U)
#define CAN_BTR_SJW_Msk        (0x3UL << CAN_BTR_SJW_Pos)                       /*!< 0x03000000 */
#define CAN_BTR_SJW            CAN_BTR_SJW_Msk                                 /*!<Resynchronization Jump Width */
#define CAN_BTR_SJW_0          (0x1UL << CAN_BTR_SJW_Pos)                       /*!< 0x01000000 */
#define CAN_BTR_SJW_1          (0x2UL << CAN_BTR_SJW_Pos)                       /*!< 0x02000000 */
#define CAN_BTR_LBKM_Pos       (30U)
#define CAN_BTR_LBKM_Msk       (0x1UL << CAN_BTR_LBKM_Pos)                      /*!< 0x40000000 */
#define CAN_BTR_LBKM           CAN_BTR_LBKM_Msk                                /*!<Loop Back Mode (Debug) */
#define CAN_BTR_SILM_Pos       (31U)
#define CAN_BTR_SILM_Msk       (0x1UL << CAN_BTR_SILM_Pos)                      /*!< 0x80000000 */
#define CAN_BTR_SILM           CAN_BTR_SILM_Msk                                /*!<Silent Mode */


/*!<Mailbox registers */
/******************  Bit definition for CAN_TI0R register  ********************/
#define CAN_TI0R_TXRQ_Pos      (0U)
#define CAN_TI0R_TXRQ_Msk      (0x1UL << CAN_TI0R_TXRQ_Pos)                     /*!< 0x00000001 */
#define CAN_TI0R_TXRQ          CAN_TI0R_TXRQ_Msk                               /*!<Transmit Mailbox Request */
#define CAN_TI0R_RTR_Pos       (1U)
#define CAN_TI0R_RTR_Msk       (0x1UL << CAN_TI0R_RTR_Pos)                      /*!< 0x00000002 */
#define CAN_TI0R_RTR           CAN_TI0R_RTR_Msk                                /*!<Remote Transmission Request */
#define CAN_TI0R_IDE_Pos       (2U)
#define CAN_TI0R_IDE_Msk       (0x1UL << CAN_TI0R_IDE_Pos)                      /*!< 0x00000004 */
#define CAN_TI0R_IDE           CAN_TI0R_IDE_Msk                                /*!<Identifier Extension */
#define CAN_TI0R_EXID_Pos      (3U)
#define CAN_TI0R_EXID_Msk      (0x3FFFFUL << CAN_TI0R_EXID_Pos)                 /*!< 0x001FFFF8 */
#define CAN_TI0R_EXID          CAN_TI0R_EXID_Msk                               /*!<Extended Identifier */
#define CAN_TI0R_STID_Pos      (21U)
#define CAN_TI0R_STID_Msk      (0x7FFUL << CAN_TI0R_STID_Pos)                   /*!< 0xFFE00000 */
#define CAN_TI0R_STID          CAN_TI0R_STID_Msk                               /*!<Standard Identifier or Extended Identifier */

/******************  Bit definition for CAN_TDT0R register  *******************/
#define CAN_TDT0R_DLC_Pos      (0U)
#define CAN_TDT0R_DLC_Msk      (0xFUL << CAN_TDT0R_DLC_Pos)                     /*!< 0x0000000F */
#define CAN_TDT0R_DLC          CAN_TDT0R_DLC_Msk                               /*!<Data Length Code */
#define CAN_TDT0R_TGT_Pos      (8U)
#define CAN_TDT0R_TGT_Msk      (0x1UL << CAN_TDT0R_TGT_Pos)                     /*!< 0x00000100 */
#define CAN_TDT0R_TGT          CAN_TDT0R_TGT_Msk                               /*!<Transmit Global Time */
#define CAN_TDT0R_TIME_Pos     (16U)
#define CAN_TDT0R_TIME_Msk     (0xFFFFUL << CAN_TDT0R_TIME_Pos)                 /*!< 0xFFFF0000 */
#define CAN_TDT0R_TIME         CAN_TDT0R_TIME_Msk                              /*!<Message Time Stamp */

/******************  Bit definition for CAN_TDL0R register  *******************/
#define CAN_TDL0R_DATA0_Pos    (0U)
#define CAN_TDL0R_DATA0_Msk    (0xFFUL << CAN_TDL0R_DATA0_Pos)                  /*!< 0x000000FF */
#define CAN_TDL0R_DATA0        CAN_TDL0R_DATA0_Msk                             /*!<Data byte 0 */
#define CAN_TDL0R_DATA1_Pos    (8U)
#define CAN_TDL0R_DATA1_Msk    (0xFFUL << CAN_TDL0R_DATA1_Pos)                  /*!< 0x0000FF00 */
#define CAN_TDL0R_DATA1        CAN_TDL0R_DATA1_Msk                             /*!<Data byte 1 */
#define CAN_TDL0R_DATA2_Pos    (16U)
#define CAN_TDL0R_DATA2_Msk    (0xFFUL << CAN_TDL0R_DATA2_Pos)                  /*!< 0x00FF0000 */
#define CAN_TDL0R_DATA2        CAN_TDL0R_DATA2_Msk                             /*!<Data byte 2 */
#define CAN_TDL0R_DATA3_Pos    (24U)
#define CAN_TDL0R_DATA3_Msk    (0xFFUL << CAN_TDL0R_DATA3_Pos)                  /*!< 0xFF000000 */
#define CAN_TDL0R_DATA3        CAN_TDL0R_DATA3_Msk                             /*!<Data byte 3 */

/******************  Bit definition for CAN_TDH0R register  *******************/
#define CAN_TDH0R_DATA4_Pos    (0U)
#define CAN_TDH0R_DATA4_Msk    (0xFFUL << CAN_TDH0R_DATA4_Pos)                  /*!< 0x000000FF */
#define CAN_TDH0R_DATA4        CAN_TDH0R_DATA4_Msk                             /*!<Data byte 4 */
#define CAN_TDH0R_DATA5_Pos    (8U)
#define CAN_TDH0R_DATA5_Msk    (0xFFUL << CAN_TDH0R_DATA5_Pos)                  /*!< 0x0000FF00 */
#define CAN_TDH0R_DATA5        CAN_TDH0R_DATA5_Msk                             /*!<Data byte 5 */
#define CAN_TDH0R_DATA6_Pos    (16U)
#define CAN_TDH0R_DATA6_Msk    (0xFFUL << CAN_TDH0R_DATA6_Pos)                  /*!< 0x00FF0000 */
#define CAN_TDH0R_DATA6        CAN_TDH0R_DATA6_Msk                             /*!<Data byte 6 */
#define CAN_TDH0R_DATA7_Pos    (24U)
#define CAN_TDH0R_DATA7_Msk    (0xFFUL << CAN_TDH0R_DATA7_Pos)                  /*!< 0xFF000000 */
#define CAN_TDH0R_DATA7        CAN_TDH0R_DATA7_Msk                             /*!<Data byte 7 */

/*******************  Bit definition for CAN_TI1R register  *******************/
#define CAN_TI1R_TXRQ_Pos      (0U)
#define CAN_TI1R_TXRQ_Msk      (0x1UL << CAN_TI1R_TXRQ_Pos)                     /*!< 0x00000001 */
#define CAN_TI1R_TXRQ          CAN_TI1R_TXRQ_Msk                               /*!<Transmit Mailbox Request */
#define CAN_TI1R_RTR_Pos       (1U)
#define CAN_TI1R_RTR_Msk       (0x1UL << CAN_TI1R_RTR_Pos)                      /*!< 0x00000002 */
#define CAN_TI1R_RTR           CAN_TI1R_RTR_Msk                                /*!<Remote Transmission Request */
#define CAN_TI1R_IDE_Pos       (2U)
#define CAN_TI1R_IDE_Msk       (0x1UL << CAN_TI1R_IDE_Pos)                      /*!< 0x00000004 */
#define CAN_TI1R_IDE           CAN_TI1R_IDE_Msk                                /*!<Identifier Extension */
#define CAN_TI1R_EXID_Pos      (3U)
#define CAN_TI1R_EXID_Msk      (0x3FFFFUL << CAN_TI1R_EXID_Pos)                 /*!< 0x001FFFF8 */
#define CAN_TI1R_EXID          CAN_TI1R_EXID_Msk                               /*!<Extended Identifier */
#define CAN_TI1R_STID_Pos      (21U)
#define CAN_TI1R_STID_Msk      (0x7FFUL << CAN_TI1R_STID_Pos)                   /*!< 0xFFE00000 */
#define CAN_TI1R_STID          CAN_TI1R_STID_Msk                               /*!<Standard Identifier or Extended Identifier */

/*******************  Bit definition for CAN_TDT1R register  ******************/
#define CAN_TDT1R_DLC_Pos      (0U)
#define CAN_TDT1R_DLC_Msk      (0xFUL << CAN_TDT1R_DLC_Pos)                     /*!< 0x0000000F */
#define CAN_TDT1R_DLC          CAN_TDT1R_DLC_Msk                               /*!<Data Length Code */
#define CAN_TDT1R_TGT_Pos      (8U)
#define CAN_TDT1R_TGT_Msk      (0x1UL << CAN_TDT1R_TGT_Pos)                     /*!< 0x00000100 */
#define CAN_TDT1R_TGT          CAN_TDT1R_TGT_Msk                               /*!<Transmit Global Time */
#define CAN_TDT1R_TIME_Pos     (16U)
#define CAN_TDT1R_TIME_Msk     (0xFFFFUL << CAN_TDT1R_TIME_Pos)                 /*!< 0xFFFF0000 */
#define CAN_TDT1R_TIME         CAN_TDT1R_TIME_Msk                              /*!<Message Time Stamp */

/*******************  Bit definition for CAN_TDL1R register  ******************/
#define CAN_TDL1R_DATA0_Pos    (0U)
#define CAN_TDL1R_DATA0_Msk    (0xFFUL << CAN_TDL1R_DATA0_Pos)                  /*!< 0x000000FF */
#define CAN_TDL1R_DATA0        CAN_TDL1R_DATA0_Msk                             /*!<Data byte 0 */
#define CAN_TDL1R_DATA1_Pos    (8U)
#define CAN_TDL1R_DATA1_Msk    (0xFFUL << CAN_TDL1R_DATA1_Pos)                  /*!< 0x0000FF00 */
#define CAN_TDL1R_DATA1        CAN_TDL1R_DATA1_Msk                             /*!<Data byte 1 */
#define CAN_TDL1R_DATA2_Pos    (16U)
#define CAN_TDL1R_DATA2_Msk    (0xFFUL << CAN_TDL1R_DATA2_Pos)                  /*!< 0x00FF0000 */
#define CAN_TDL1R_DATA2        CAN_TDL1R_DATA2_Msk                             /*!<Data byte 2 */
#define CAN_TDL1R_DATA3_Pos    (24U)
#define CAN_TDL1R_DATA3_Msk    (0xFFUL << CAN_TDL1R_DATA3_Pos)                  /*!< 0xFF000000 */
#define CAN_TDL1R_DATA3        CAN_TDL1R_DATA3_Msk                             /*!<Data byte 3 */

/*******************  Bit definition for CAN_TDH1R register  ******************/
#define CAN_TDH1R_DATA4_Pos    (0U)
#define CAN_TDH1R_DATA4_Msk    (0xFFUL << CAN_TDH1R_DATA4_Pos)                  /*!< 0x000000FF */
#define CAN_TDH1R_DATA4        CAN_TDH1R_DATA4_Msk                             /*!<Data byte 4 */
#define CAN_TDH1R_DATA5_Pos    (8U)
#define CAN_TDH1R_DATA5_Msk    (0xFFUL << CAN_TDH1R_DATA5_Pos)                  /*!< 0x0000FF00 */
#define CAN_TDH1R_DATA5        CAN_TDH1R_DATA5_Msk                             /*!<Data byte 5 */
#define CAN_TDH1R_DATA6_Pos    (16U)
#define CAN_TDH1R_DATA6_Msk    (0xFFUL << CAN_TDH1R_DATA6_Pos)                  /*!< 0x00FF0000 */
#define CAN_TDH1R_DATA6        CAN_TDH1R_DATA6_Msk                             /*!<Data byte 6 */
#define CAN_TDH1R_DATA7_Pos    (24U)
#define CAN_TDH1R_DATA7_Msk    (0xFFUL << CAN_TDH1R_DATA7_Pos)                  /*!< 0xFF000000 */
#define CAN_TDH1R_DATA7        CAN_TDH1R_DATA7_Msk                             /*!<Data byte 7 */

/*******************  Bit definition for CAN_TI2R register  *******************/
#define CAN_TI2R_TXRQ_Pos      (0U)
#define CAN_TI2R_TXRQ_Msk      (0x1UL << CAN_TI2R_TXRQ_Pos)                     /*!< 0x00000001 */
#define CAN_TI2R_TXRQ          CAN_TI2R_TXRQ_Msk                               /*!<Transmit Mailbox Request */
#define CAN_TI2R_RTR_Pos       (1U)
#define CAN_TI2R_RTR_Msk       (0x1UL << CAN_TI2R_RTR_Pos)                      /*!< 0x00000002 */
#define CAN_TI2R_RTR           CAN_TI2R_RTR_Msk                                /*!<Remote Transmission Request */
#define CAN_TI2R_IDE_Pos       (2U)
#define CAN_TI2R_IDE_Msk       (0x1UL << CAN_TI2R_IDE_Pos)                      /*!< 0x00000004 */
#define CAN_TI2R_IDE           CAN_TI2R_IDE_Msk                                /*!<Identifier Extension */
#define CAN_TI2R_EXID_Pos      (3U)
#define CAN_TI2R_EXID_Msk      (0x3FFFFUL << CAN_TI2R_EXID_Pos)                 /*!< 0x001FFFF8 */
#define CAN_TI2R_EXID          CAN_TI2R_EXID_Msk                               /*!<Extended identifier */
#define CAN_TI2R_STID_Pos      (21U)
#define CAN_TI2R_STID_Msk      (0x7FFUL << CAN_TI2R_STID_Pos)                   /*!< 0xFFE00000 */
#define CAN_TI2R_STID          CAN_TI2R_STID_Msk                               /*!<Standard Identifier or Extended Identifier */

/*******************  Bit definition for CAN_TDT2R register  ******************/
#define CAN_TDT2R_DLC_Pos      (0U)
#define CAN_TDT2R_DLC_Msk      (0xFUL << CAN_TDT2R_DLC_Pos)                     /*!< 0x0000000F */
#define CAN_TDT2R_DLC          CAN_TDT2R_DLC_Msk                               /*!<Data Length Code */
#define CAN_TDT2R_TGT_Pos      (8U)
#define CAN_TDT2R_TGT_Msk      (0x1UL << CAN_TDT2R_TGT_Pos)                     /*!< 0x00000100 */
#define CAN_TDT2R_TGT          CAN_TDT2R_TGT_Msk                               /*!<Transmit Global Time */
#define CAN_TDT2R_TIME_Pos     (16U)
#define CAN_TDT2R_TIME_Msk     (0xFFFFUL << CAN_TDT2R_TIME_Pos)                 /*!< 0xFFFF0000 */
#define CAN_TDT2R_TIME         CAN_TDT2R_TIME_Msk                              /*!<Message Time Stamp */

/*******************  Bit definition for CAN_TDL2R register  ******************/
#define CAN_TDL2R_DATA0_Pos    (0U)
#define CAN_TDL2R_DATA0_Msk    (0xFFUL << CAN_TDL2R_DATA0_Pos)                  /*!< 0x000000FF */
#define CAN_TDL2R_DATA0        CAN_TDL2R_DATA0_Msk                             /*!<Data byte 0 */
#define CAN_TDL2R_DATA1_Pos    (8U)
#define CAN_TDL2R_DATA1_Msk    (0xFFUL << CAN_TDL2R_DATA1_Pos)                  /*!< 0x0000FF00 */
#define CAN_TDL2R_DATA1        CAN_TDL2R_DATA1_Msk                             /*!<Data byte 1 */
#define CAN_TDL2R_DATA2_Pos    (16U)
#define CAN_TDL2R_DATA2_Msk    (0xFFUL << CAN_TDL2R_DATA2_Pos)                  /*!< 0x00FF0000 */
#define CAN_TDL2R_DATA2        CAN_TDL2R_DATA2_Msk                             /*!<Data byte 2 */
#define CAN_TDL2R_DATA3_Pos    (24U)
#define CAN_TDL2R_DATA3_Msk    (0xFFUL << CAN_TDL2R_DATA3_Pos)                  /*!< 0xFF000000 */
#define CAN_TDL2R_DATA3        CAN_TDL2R_DATA3_Msk                             /*!<Data byte 3 */

/*******************  Bit definition for CAN_TDH2R register  ******************/
#define CAN_TDH2R_DATA4_Pos    (0U)
#define CAN_TDH2R_DATA4_Msk    (0xFFUL << CAN_TDH2R_DATA4_Pos)                  /*!< 0x000000FF */
#define CAN_TDH2R_DATA4        CAN_TDH2R_DATA4_Msk                             /*!<Data byte 4 */
#define CAN_TDH2R_DATA5_Pos    (8U)
#define CAN_TDH2R_DATA5_Msk    (0xFFUL << CAN_TDH2R_DATA5_Pos)                  /*!< 0x0000FF00 */
#define CAN_TDH2R_DATA5        CAN_TDH2R_DATA5_Msk                             /*!<Data byte 5 */
#define CAN_TDH2R_DATA6_Pos    (16U)
#define CAN_TDH2R_DATA6_Msk    (0xFFUL << CAN_TDH2R_DATA6_Pos)                  /*!< 0x00FF0000 */
#define CAN_TDH2R_DATA6        CAN_TDH2R_DATA6_Msk                             /*!<Data byte 6 */
#define CAN_TDH2R_DATA7_Pos    (24U)
#define CAN_TDH2R_DATA7_Msk    (0xFFUL << CAN_TDH2R_DATA7_Pos)                  /*!< 0xFF000000 */
#define CAN_TDH2R_DATA7        CAN_TDH2R_DATA7_Msk                             /*!<Data byte 7 */

/*******************  Bit definition for CAN_RI0R register  *******************/
#define CAN_RI0R_RTR_Pos       (1U)
#define CAN_RI0R_RTR_Msk       (0x1UL << CAN_RI0R_RTR_Pos)                      /*!< 0x00000002 */
#define CAN_RI0R_RTR           CAN_RI0R_RTR_Msk                                /*!<Remote Transmission Request */
#define CAN_RI0R_IDE_Pos       (2U)
#define CAN_RI0R_IDE_Msk       (0x1UL << CAN_RI0R_IDE_Pos)                      /*!< 0x00000004 */
#define CAN_RI0R_IDE           CAN_RI0R_IDE_Msk                                /*!<Identifier Extension */
#define CAN_RI0R_EXID_Pos      (3U)
#define CAN_RI0R_EXID_Msk      (0x3FFFFUL << CAN_RI0R_EXID_Pos)                 /*!< 0x001FFFF8 */
#define CAN_RI0R_EXID          CAN_RI0R_EXID_Msk                               /*!<Extended Identifier */
#define CAN_RI0R_STID_Pos      (21U)
#define CAN_RI0R_STID_Msk      (0x7FFUL << CAN_RI0R_STID_Pos)                   /*!< 0xFFE00000 */
#define CAN_RI0R_STID          CAN_RI0R_STID_Msk                               /*!<Standard Identifier or Extended Identifier */

/*******************  Bit definition for CAN_RDT0R register  ******************/
#define CAN_RDT0R_DLC_Pos      (0U)
#define CAN_RDT0R_DLC_Msk      (0xFUL << CAN_RDT0R_DLC_Pos)                     /*!< 0x0000000F */
#define CAN_RDT0R_DLC          CAN_RDT0R_DLC_Msk                               /*!<Data Length Code */
#define CAN_RDT0R_FMI_Pos      (8U)
#define CAN_RDT0R_FMI_Msk      (0xFFUL << CAN_RDT0R_FMI_Pos)                    /*!< 0x0000FF00 */
#define CAN_RDT0R_FMI          CAN_RDT0R_FMI_Msk                               /*!<Filter Match Index */
#define CAN_RDT0R_TIME_Pos     (16U)
#define CAN_RDT0R_TIME_Msk     (0xFFFFUL << CAN_RDT0R_TIME_Pos)                 /*!< 0xFFFF0000 */
#define CAN_RDT0R_TIME         CAN_RDT0R_TIME_Msk                              /*!<Message Time Stamp */

/*******************  Bit definition for CAN_RDL0R register  ******************/
#define CAN_RDL0R_DATA0_Pos    (0U)
#define CAN_RDL0R_DATA0_Msk    (0xFFUL << CAN_RDL0R_DATA0_Pos)                  /*!< 0x000000FF */
#define CAN_RDL0R_DATA0        CAN_RDL0R_DATA0_Msk                             /*!<Data byte 0 */
#define CAN_RDL0R_DATA1_Pos    (8U)
#define CAN_RDL0R_DATA1_Msk    (0xFFUL << CAN_RDL0R_DATA1_Pos)                  /*!< 0x0000FF00 */
#define CAN_RDL0R_DATA1        CAN_RDL0R_DATA1_Msk                             /*!<Data byte 1 */
#define CAN_RDL0R_DATA2_Pos    (16U)
#define CAN_RDL0R_DATA2_Msk    (0xFFUL << CAN_RDL0R_DATA2_Pos)                  /*!< 0x00FF0000 */
#define CAN_RDL0R_DATA2        CAN_RDL0R_DATA2_Msk                             /*!<Data byte 2 */
#define CAN_RDL0R_DATA3_Pos    (24U)
#define CAN_RDL0R_DATA3_Msk    (0xFFUL << CAN_RDL0R_DATA3_Pos)                  /*!< 0xFF000000 */
#define CAN_RDL0R_DATA3        CAN_RDL0R_DATA3_Msk                             /*!<Data byte 3 */

/*******************  Bit definition for CAN_RDH0R register  ******************/
#define CAN_RDH0R_DATA4_Pos    (0U)
#define CAN_RDH0R_DATA4_Msk    (0xFFUL << CAN_RDH0R_DATA4_Pos)                  /*!< 0x000000FF */
#define CAN_RDH0R_DATA4        CAN_RDH0R_DATA4_Msk                             /*!<Data byte 4 */
#define CAN_RDH0R_DATA5_Pos    (8U)
#define CAN_RDH0R_DATA5_Msk    (0xFFUL << CAN_RDH0R_DATA5_Pos)                  /*!< 0x0000FF00 */
#define CAN_RDH0R_DATA5        CAN_RDH0R_DATA5_Msk                             /*!<Data byte 5 */
#define CAN_RDH0R_DATA6_Pos    (16U)
#define CAN_RDH0R_DATA6_Msk    (0xFFUL << CAN_RDH0R_DATA6_Pos)                  /*!< 0x00FF0000 */
#define CAN_RDH0R_DATA6        CAN_RDH0R_DATA6_Msk                             /*!<Data byte 6 */
#define CAN_RDH0R_DATA7_Pos    (24U)
#define CAN_RDH0R_DATA7_Msk    (0xFFUL << CAN_RDH0R_DATA7_Pos)                  /*!< 0xFF000000 */
#define CAN_RDH0R_DATA7        CAN_RDH0R_DATA7_Msk                             /*!<Data byte 7 */

/*******************  Bit definition for CAN_RI1R register  *******************/
#define CAN_RI1R_RTR_Pos       (1U)
#define CAN_RI1R_RTR_Msk       (0x1UL << CAN_RI1R_RTR_Pos)                      /*!< 0x00000002 */
#define CAN_RI1R_RTR           CAN_RI1R_RTR_Msk                                /*!<Remote Transmission Request */
#define CAN_RI1R_IDE_Pos       (2U)
#define CAN_RI1R_IDE_Msk       (0x1UL << CAN_RI1R_IDE_Pos)                      /*!< 0x00000004 */
#define CAN_RI1R_IDE           CAN_RI1R_IDE_Msk                                /*!<Identifier Extension */
#define CAN_RI1R_EXID_Pos      (3U)
#define CAN_RI1R_EXID_Msk      (0x3FFFFUL << CAN_RI1R_EXID_Pos)                 /*!< 0x001FFFF8 */
#define CAN_RI1R_EXID          CAN_RI1R_EXID_Msk                               /*!<Extended identifier */
#define CAN_RI1R_STID_Pos      (21U)
#define CAN_RI1R_STID_Msk      (0x7FFUL << CAN_RI1R_STID_Pos)                   /*!< 0xFFE00000 */
#define CAN_RI1R_STID          CAN_RI1R_STID_Msk                               /*!<Standard Identifier or Extended Identifier */

/*******************  Bit definition for CAN_RDT1R register  ******************/
#define CAN_RDT1R_DLC_Pos      (0U)
#define CAN_RDT1R_DLC_Msk      (0xFUL << CAN_RDT1R_DLC_Pos)                     /*!< 0x0000000F */
#define CAN_RDT1R_DLC          CAN_RDT1R_DLC_Msk                               /*!<Data Length Code */
#define CAN_RDT1R_FMI_Pos      (8U)
#define CAN_RDT1R_FMI_Msk      (0xFFUL << CAN_RDT1R_FMI_Pos)                    /*!< 0x0000FF00 */
#define CAN_RDT1R_FMI          CAN_RDT1R_FMI_Msk                               /*!<Filter Match Index */
#define CAN_RDT1R_TIME_Pos     (16U)
#define CAN_RDT1R_TIME_Msk     (0xFFFFUL << CAN_RDT1R_TIME_Pos)                 /*!< 0xFFFF0000 */
#define CAN_RDT1R_TIME         CAN_RDT1R_TIME_Msk                              /*!<Message Time Stamp */

/*******************  Bit definition for CAN_RDL1R register  ******************/
#define CAN_RDL1R_DATA0_Pos    (0U)
#define CAN_RDL1R_DATA0_Msk    (0xFFUL << CAN_RDL1R_DATA0_Pos)                  /*!< 0x000000FF */
#define CAN_RDL1R_DATA0        CAN_RDL1R_DATA0_Msk                             /*!<Data byte 0 */
#define CAN_RDL1R_DATA1_Pos    (8U)
#define CAN_RDL1R_DATA1_Msk    (0xFFUL << CAN_RDL1R_DATA1_Pos)                  /*!< 0x0000FF00 */
#define CAN_RDL1R_DATA1        CAN_RDL1R_DATA1_Msk                             /*!<Data byte 1 */
#define CAN_RDL1R_DATA2_Pos    (16U)
#define CAN_RDL1R_DATA2_Msk    (0xFFUL << CAN_RDL1R_DATA2_Pos)                  /*!< 0x00FF0000 */
#define CAN_RDL1R_DATA2        CAN_RDL1R_DATA2_Msk                             /*!<Data byte 2 */
#define CAN_RDL1R_DATA3_Pos    (24U)
#define CAN_RDL1R_DATA3_Msk    (0xFFUL << CAN_RDL1R_DATA3_Pos)                  /*!< 0xFF000000 */
#define CAN_RDL1R_DATA3        CAN_RDL1R_DATA3_Msk                             /*!<Data byte 3 */

/*******************  Bit definition for CAN_RDH1R register  ******************/
#define CAN_RDH1R_DATA4_Pos    (0U)
#define CAN_RDH1R_DATA4_Msk    (0xFFUL << CAN_RDH1R_DATA4_Pos)                  /*!< 0x000000FF */
#define CAN_RDH1R_DATA4        CAN_RDH1R_DATA4_Msk                             /*!<Data byte 4 */
#define CAN_RDH1R_DATA5_Pos    (8U)
#define CAN_RDH1R_DATA5_Msk    (0xFFUL << CAN_RDH1R_DATA5_Pos)                  /*!< 0x0000FF00 */
#define CAN_RDH1R_DATA5        CAN_RDH1R_DATA5_Msk                             /*!<Data byte 5 */
#define CAN_RDH1R_DATA6_Pos    (16U)
#define CAN_RDH1R_DATA6_Msk    (0xFFUL << CAN_RDH1R_DATA6_Pos)                  /*!< 0x00FF0000 */
#define CAN_RDH1R_DATA6        CAN_RDH1R_DATA6_Msk                             /*!<Data byte 6 */
#define CAN_RDH1R_DATA7_Pos    (24U)
#define CAN_RDH1R_DATA7_Msk    (0xFFUL << CAN_RDH1R_DATA7_Pos)                  /*!< 0xFF000000 */
#define CAN_RDH1R_DATA7        CAN_RDH1R_DATA7_Msk                             /*!<Data byte 7 */

/*!<CAN filter registers */
/*******************  Bit definition for CAN_FMR register  ********************/
#define CAN_FMR_FINIT_Pos      (0U)
#define CAN_FMR_FINIT_Msk      (0x1UL << CAN_FMR_FINIT_Pos)                     /*!< 0x00000001 */
#define CAN_FMR_FINIT          CAN_FMR_FINIT_Msk                               /*!<Filter Init Mode */
#define CAN_FMR_CAN2SB_Pos     (8U)
#define CAN_FMR_CAN2SB_Msk     (0x3FUL << CAN_FMR_CAN2SB_Pos)                   /*!< 0x00003F00 */
#define CAN_FMR_CAN2SB         CAN_FMR_CAN2SB_Msk                              /*!<CAN2 start bank */

/*******************  Bit definition for CAN_FM1R register  *******************/
#define CAN_FM1R_FBM_Pos       (0U)
#define CAN_FM1R_FBM_Msk       (0xFFFFFFFUL << CAN_FM1R_FBM_Pos)                /*!< 0x0FFFFFFF */
#define CAN_FM1R_FBM           CAN_FM1R_FBM_Msk                                /*!<Filter Mode */
#define CAN_FM1R_FBM0_Pos      (0U)
#define CAN_FM1R_FBM0_Msk      (0x1UL << CAN_FM1R_FBM0_Pos)                     /*!< 0x00000001 */
#define CAN_FM1R_FBM0          CAN_FM1R_FBM0_Msk                               /*!<Filter Init Mode bit 0 */
#define CAN_FM1R_FBM1_Pos      (1U)
#define CAN_FM1R_FBM1_Msk      (0x1UL << CAN_FM1R_FBM1_Pos)                     /*!< 0x00000002 */
#define CAN_FM1R_FBM1          CAN_FM1R_FBM1_Msk                               /*!<Filter Init Mode bit 1 */
#define CAN_FM1R_FBM2_Pos      (2U)
#define CAN_FM1R_FBM2_Msk      (0x1UL << CAN_FM1R_FBM2_Pos)                     /*!< 0x00000004 */
#define CAN_FM1R_FBM2          CAN_FM1R_FBM2_Msk                               /*!<Filter Init Mode bit 2 */
#define CAN_FM1R_FBM3_Pos      (3U)
#define CAN_FM1R_FBM3_Msk      (0x1UL << CAN_FM1R_FBM3_Pos)                     /*!< 0x00000008 */
#define CAN_FM1R_FBM3          CAN_FM1R_FBM3_Msk                               /*!<Filter Init Mode bit 3 */
#define CAN_FM1R_FBM4_Pos      (4U)
#define CAN_FM1R_FBM4_Msk      (0x1UL << CAN_FM1R_FBM4_Pos)                     /*!< 0x00000010 */
#define CAN_FM1R_FBM4          CAN_FM1R_FBM4_Msk                               /*!<Filter Init Mode bit 4 */
#define CAN_FM1R_FBM5_Pos      (5U)
#define CAN_FM1R_FBM5_Msk      (0x1UL << CAN_FM1R_FBM5_Pos)                     /*!< 0x00000020 */
#define CAN_FM1R_FBM5          CAN_FM1R_FBM5_Msk                               /*!<Filter Init Mode bit 5 */
#define CAN_FM1R_FBM6_Pos      (6U)
#define CAN_FM1R_FBM6_Msk      (0x1UL << CAN_FM1R_FBM6_Pos)                     /*!< 0x00000040 */
#define CAN_FM1R_FBM6          CAN_FM1R_FBM6_Msk                               /*!<Filter Init Mode bit 6 */
#define CAN_FM1R_FBM7_Pos      (7U)
#define CAN_FM1R_FBM7_Msk      (0x1UL << CAN_FM1R_FBM7_Pos)                     /*!< 0x00000080 */
#define CAN_FM1R_FBM7          CAN_FM1R_FBM7_Msk                               /*!<Filter Init Mode bit 7 */
#define CAN_FM1R_FBM8_Pos      (8U)
#define CAN_FM1R_FBM8_Msk      (0x1UL << CAN_FM1R_FBM8_Pos)                     /*!< 0x00000100 */
#define CAN_FM1R_FBM8          CAN_FM1R_FBM8_Msk                               /*!<Filter Init Mode bit 8 */
#define CAN_FM1R_FBM9_Pos      (9U)
#define CAN_FM1R_FBM9_Msk      (0x1UL << CAN_FM1R_FBM9_Pos)                     /*!< 0x00000200 */
#define CAN_FM1R_FBM9          CAN_FM1R_FBM9_Msk                               /*!<Filter Init Mode bit 9 */
#define CAN_FM1R_FBM10_Pos     (10U)
#define CAN_FM1R_FBM10_Msk     (0x1UL << CAN_FM1R_FBM10_Pos)                    /*!< 0x00000400 */
#define CAN_FM1R_FBM10         CAN_FM1R_FBM10_Msk                              /*!<Filter Init Mode bit 10 */
#define CAN_FM1R_FBM11_Pos     (11U)
#define CAN_FM1R_FBM11_Msk     (0x1UL << CAN_FM1R_FBM11_Pos)                    /*!< 0x00000800 */
#define CAN_FM1R_FBM11         CAN_FM1R_FBM11_Msk                              /*!<Filter Init Mode bit 11 */
#define CAN_FM1R_FBM12_Pos     (12U)
#define CAN_FM1R_FBM12_Msk     (0x1UL << CAN_FM1R_FBM12_Pos)                    /*!< 0x00001000 */
#define CAN_FM1R_FBM12         CAN_FM1R_FBM12_Msk                              /*!<Filter Init Mode bit 12 */
#define CAN_FM1R_FBM13_Pos     (13U)
#define CAN_FM1R_FBM13_Msk     (0x1UL << CAN_FM1R_FBM13_Pos)                    /*!< 0x00002000 */
#define CAN_FM1R_FBM13         CAN_FM1R_FBM13_Msk                              /*!<Filter Init Mode bit 13 */
#define CAN_FM1R_FBM14_Pos     (14U)
#define CAN_FM1R_FBM14_Msk     (0x1UL << CAN_FM1R_FBM14_Pos)                    /*!< 0x00004000 */
#define CAN_FM1R_FBM14         CAN_FM1R_FBM14_Msk                              /*!<Filter Init Mode bit 14 */
#define CAN_FM1R_FBM15_Pos     (15U)
#define CAN_FM1R_FBM15_Msk     (0x1UL << CAN_FM1R_FBM15_Pos)                    /*!< 0x00008000 */
#define CAN_FM1R_FBM15         CAN_FM1R_FBM15_Msk                              /*!<Filter Init Mode bit 15 */
#define CAN_FM1R_FBM16_Pos     (16U)
#define CAN_FM1R_FBM16_Msk     (0x1UL << CAN_FM1R_FBM16_Pos)                    /*!< 0x00010000 */
#define CAN_FM1R_FBM16         CAN_FM1R_FBM16_Msk                              /*!<Filter Init Mode bit 16 */
#define CAN_FM1R_FBM17_Pos     (17U)
#define CAN_FM1R_FBM17_Msk     (0x1UL << CAN_FM1R_FBM17_Pos)                    /*!< 0x00020000 */
#define CAN_FM1R_FBM17         CAN_FM1R_FBM17_Msk                              /*!<Filter Init Mode bit 17 */
#define CAN_FM1R_FBM18_Pos     (18U)
#define CAN_FM1R_FBM18_Msk     (0x1UL << CAN_FM1R_FBM18_Pos)                    /*!< 0x00040000 */
#define CAN_FM1R_FBM18         CAN_FM1R_FBM18_Msk                              /*!<Filter Init Mode bit 18 */
#define CAN_FM1R_FBM19_Pos     (19U)
#define CAN_FM1R_FBM19_Msk     (0x1UL << CAN_FM1R_FBM19_Pos)                    /*!< 0x00080000 */
#define CAN_FM1R_FBM19         CAN_FM1R_FBM19_Msk                              /*!<Filter Init Mode bit 19 */
#define CAN_FM1R_FBM20_Pos     (20U)
#define CAN_FM1R_FBM20_Msk     (0x1UL << CAN_FM1R_FBM20_Pos)                    /*!< 0x00100000 */
#define CAN_FM1R_FBM20         CAN_FM1R_FBM20_Msk                              /*!<Filter Init Mode bit 20 */
#define CAN_FM1R_FBM21_Pos     (21U)
#define CAN_FM1R_FBM21_Msk     (0x1UL << CAN_FM1R_FBM21_Pos)                    /*!< 0x00200000 */
#define CAN_FM1R_FBM21         CAN_FM1R_FBM21_Msk                              /*!<Filter Init Mode bit 21 */
#define CAN_FM1R_FBM22_Pos     (22U)
#define CAN_FM1R_FBM22_Msk     (0x1UL << CAN_FM1R_FBM22_Pos)                    /*!< 0x00400000 */
#define CAN_FM1R_FBM22         CAN_FM1R_FBM22_Msk                              /*!<Filter Init Mode bit 22 */
#define CAN_FM1R_FBM23_Pos     (23U)
#define CAN_FM1R_FBM23_Msk     (0x1UL << CAN_FM1R_FBM23_Pos)                    /*!< 0x00800000 */
#define CAN_FM1R_FBM23         CAN_FM1R_FBM23_Msk                              /*!<Filter Init Mode bit 23 */
#define CAN_FM1R_FBM24_Pos     (24U)
#define CAN_FM1R_FBM24_Msk     (0x1UL << CAN_FM1R_FBM24_Pos)                    /*!< 0x01000000 */
#define CAN_FM1R_FBM24         CAN_FM1R_FBM24_Msk                              /*!<Filter Init Mode bit 24 */
#define CAN_FM1R_FBM25_Pos     (25U)
#define CAN_FM1R_FBM25_Msk     (0x1UL << CAN_FM1R_FBM25_Pos)                    /*!< 0x02000000 */
#define CAN_FM1R_FBM25         CAN_FM1R_FBM25_Msk                              /*!<Filter Init Mode bit 25 */
#define CAN_FM1R_FBM26_Pos     (26U)
#define CAN_FM1R_FBM26_Msk     (0x1UL << CAN_FM1R_FBM26_Pos)                    /*!< 0x04000000 */
#define CAN_FM1R_FBM26         CAN_FM1R_FBM26_Msk                              /*!<Filter Init Mode bit 26 */
#define CAN_FM1R_FBM27_Pos     (27U)
#define CAN_FM1R_FBM27_Msk     (0x1UL << CAN_FM1R_FBM27_Pos)                    /*!< 0x08000000 */
#define CAN_FM1R_FBM27         CAN_FM1R_FBM27_Msk                              /*!<Filter Init Mode bit 27 */

/*******************  Bit definition for CAN_FS1R register  *******************/
#define CAN_FS1R_FSC_Pos       (0U)
#define CAN_FS1R_FSC_Msk       (0xFFFFFFFUL << CAN_FS1R_FSC_Pos)                /*!< 0x0FFFFFFF */
#define CAN_FS1R_FSC           CAN_FS1R_FSC_Msk                                /*!<Filter Scale Configuration */
#define CAN_FS1R_FSC0_Pos      (0U)
#define CAN_FS1R_FSC0_Msk      (0x1UL << CAN_FS1R_FSC0_Pos)                     /*!< 0x00000001 */
#define CAN_FS1R_FSC0          CAN_FS1R_FSC0_Msk                               /*!<Filter Scale Configuration bit 0 */
#define CAN_FS1R_FSC1_Pos      (1U)
#define CAN_FS1R_FSC1_Msk      (0x1UL << CAN_FS1R_FSC1_Pos)                     /*!< 0x00000002 */
#define CAN_FS1R_FSC1          CAN_FS1R_FSC1_Msk                               /*!<Filter Scale Configuration bit 1 */
#define CAN_FS1R_FSC2_Pos      (2U)
#define CAN_FS1R_FSC2_Msk      (0x1UL << CAN_FS1R_FSC2_Pos)                     /*!< 0x00000004 */
#define CAN_FS1R_FSC2          CAN_FS1R_FSC2_Msk                               /*!<Filter Scale Configuration bit 2 */
#define CAN_FS1R_FSC3_Pos      (3U)
#define CAN_FS1R_FSC3_Msk      (0x1UL << CAN_FS1R_FSC3_Pos)                     /*!< 0x00000008 */
#define CAN_FS1R_FSC3          CAN_FS1R_FSC3_Msk                               /*!<Filter Scale Configuration bit 3 */
#define CAN_FS1R_FSC4_Pos      (4U)
#define CAN_FS1R_FSC4_Msk      (0x1UL << CAN_FS1R_FSC4_Pos)                     /*!< 0x00000010 */
#define CAN_FS1R_FSC4          CAN_FS1R_FSC4_Msk                               /*!<Filter Scale Configuration bit 4 */
#define CAN_FS1R_FSC5_Pos      (5U)
#define CAN_FS1R_FSC5_Msk      (0x1UL << CAN_FS1R_FSC5_Pos)                     /*!< 0x00000020 */
#define CAN_FS1R_FSC5          CAN_FS1R_FSC5_Msk                               /*!<Filter Scale Configuration bit 5 */
#define CAN_FS1R_FSC6_Pos      (6U)
#define CAN_FS1R_FSC6_Msk      (0x1UL << CAN_FS1R_FSC6_Pos)                     /*!< 0x00000040 */
#define CAN_FS1R_FSC6          CAN_FS1R_FSC6_Msk                               /*!<Filter Scale Configuration bit 6 */
#define CAN_FS1R_FSC7_Pos      (7U)
#define CAN_FS1R_FSC7_Msk      (0x1UL << CAN_FS1R_FSC7_Pos)                     /*!< 0x00000080 */
#define CAN_FS1R_FSC7          CAN_FS1R_FSC7_Msk                               /*!<Filter Scale Configuration bit 7 */
#define CAN_FS1R_FSC8_Pos      (8U)
#define CAN_FS1R_FSC8_Msk      (0x1UL << CAN_FS1R_FSC8_Pos)                     /*!< 0x00000100 */
#define CAN_FS1R_FSC8          CAN_FS1R_FSC8_Msk                               /*!<Filter Scale Configuration bit 8 */
#define CAN_FS1R_FSC9_Pos      (9U)
#define CAN_FS1R_FSC9_Msk      (0x1UL << CAN_FS1R_FSC9_Pos)                     /*!< 0x00000200 */
#define CAN_FS1R_FSC9          CAN_FS1R_FSC9_Msk                               /*!<Filter Scale Configuration bit 9 */
#define CAN_FS1R_FSC10_Pos     (10U)
#define CAN_FS1R_FSC10_Msk     (0x1UL << CAN_FS1R_FSC10_Pos)                    /*!< 0x00000400 */
#define CAN_FS1R_FSC10         CAN_FS1R_FSC10_Msk                              /*!<Filter Scale Configuration bit 10 */
#define CAN_FS1R_FSC11_Pos     (11U)
#define CAN_FS1R_FSC11_Msk     (0x1UL << CAN_FS1R_FSC11_Pos)                    /*!< 0x00000800 */
#define CAN_FS1R_FSC11         CAN_FS1R_FSC11_Msk                              /*!<Filter Scale Configuration bit 11 */
#define CAN_FS1R_FSC12_Pos     (12U)
#define CAN_FS1R_FSC12_Msk     (0x1UL << CAN_FS1R_FSC12_Pos)                    /*!< 0x00001000 */
#define CAN_FS1R_FSC12         CAN_FS1R_FSC12_Msk                              /*!<Filter Scale Configuration bit 12 */
#define CAN_FS1R_FSC13_Pos     (13U)
#define CAN_FS1R_FSC13_Msk     (0x1UL << CAN_FS1R_FSC13_Pos)                    /*!< 0x00002000 */
#define CAN_FS1R_FSC13         CAN_FS1R_FSC13_Msk                              /*!<Filter Scale Configuration bit 13 */
#define CAN_FS1R_FSC14_Pos     (14U)
#define CAN_FS1R_FSC14_Msk     (0x1UL << CAN_FS1R_FSC14_Pos)                    /*!< 0x00004000 */
#define CAN_FS1R_FSC14         CAN_FS1R_FSC14_Msk                              /*!<Filter Scale Configuration bit 14 */
#define CAN_FS1R_FSC15_Pos     (15U)
#define CAN_FS1R_FSC15_Msk     (0x1UL << CAN_FS1R_FSC15_Pos)                    /*!< 0x00008000 */
#define CAN_FS1R_FSC15         CAN_FS1R_FSC15_Msk                              /*!<Filter Scale Configuration bit 15 */
#define CAN_FS1R_FSC16_Pos     (16U)
#define CAN_FS1R_FSC16_Msk     (0x1UL << CAN_FS1R_FSC16_Pos)                    /*!< 0x00010000 */
#define CAN_FS1R_FSC16         CAN_FS1R_FSC16_Msk                              /*!<Filter Scale Configuration bit 16 */
#define CAN_FS1R_FSC17_Pos     (17U)
#define CAN_FS1R_FSC17_Msk     (0x1UL << CAN_FS1R_FSC17_Pos)                    /*!< 0x00020000 */
#define CAN_FS1R_FSC17         CAN_FS1R_FSC17_Msk                              /*!<Filter Scale Configuration bit 17 */
#define CAN_FS1R_FSC18_Pos     (18U)
#define CAN_FS1R_FSC18_Msk     (0x1UL << CAN_FS1R_FSC18_Pos)                    /*!< 0x00040000 */
#define CAN_FS1R_FSC18         CAN_FS1R_FSC18_Msk                              /*!<Filter Scale Configuration bit 18 */
#define CAN_FS1R_FSC19_Pos     (19U)
#define CAN_FS1R_FSC19_Msk     (0x1UL << CAN_FS1R_FSC19_Pos)                    /*!< 0x00080000 */
#define CAN_FS1R_FSC19         CAN_FS1R_FSC19_Msk                              /*!<Filter Scale Configuration bit 19 */
#define CAN_FS1R_FSC20_Pos     (20U)
#define CAN_FS1R_FSC20_Msk     (0x1UL << CAN_FS1R_FSC20_Pos)                    /*!< 0x00100000 */
#define CAN_FS1R_FSC20         CAN_FS1R_FSC20_Msk                              /*!<Filter Scale Configuration bit 20 */
#define CAN_FS1R_FSC21_Pos     (21U)
#define CAN_FS1R_FSC21_Msk     (0x1UL << CAN_FS1R_FSC21_Pos)                    /*!< 0x00200000 */
#define CAN_FS1R_FSC21         CAN_FS1R_FSC21_Msk                              /*!<Filter Scale Configuration bit 21 */
#define CAN_FS1R_FSC22_Pos     (22U)
#define CAN_FS1R_FSC22_Msk     (0x1UL << CAN_FS1R_FSC22_Pos)                    /*!< 0x00400000 */
#define CAN_FS1R_FSC22         CAN_FS1R_FSC22_Msk                              /*!<Filter Scale Configuration bit 22 */
#define CAN_FS1R_FSC23_Pos     (23U)
#define CAN_FS1R_FSC23_Msk     (0x1UL << CAN_FS1R_FSC23_Pos)                    /*!< 0x00800000 */
#define CAN_FS1R_FSC23         CAN_FS1R_FSC23_Msk                              /*!<Filter Scale Configuration bit 23 */
#define CAN_FS1R_FSC24_Pos     (24U)
#define CAN_FS1R_FSC24_Msk     (0x1UL << CAN_FS1R_FSC24_Pos)                    /*!< 0x01000000 */
#define CAN_FS1R_FSC24         CAN_FS1R_FSC24_Msk                              /*!<Filter Scale Configuration bit 24 */
#define CAN_FS1R_FSC25_Pos     (25U)
#define CAN_FS1R_FSC25_Msk     (0x1UL << CAN_FS1R_FSC25_Pos)                    /*!< 0x02000000 */
#define CAN_FS1R_FSC25         CAN_FS1R_FSC25_Msk                              /*!<Filter Scale Configuration bit 25 */
#define CAN_FS1R_FSC26_Pos     (26U)
#define CAN_FS1R_FSC26_Msk     (0x1UL << CAN_FS1R_FSC26_Pos)                    /*!< 0x04000000 */
#define CAN_FS1R_FSC26         CAN_FS1R_FSC26_Msk                              /*!<Filter Scale Configuration bit 26 */
#define CAN_FS1R_FSC27_Pos     (27U)
#define CAN_FS1R_FSC27_Msk     (0x1UL << CAN_FS1R_FSC27_Pos)                    /*!< 0x08000000 */
#define CAN_FS1R_FSC27         CAN_FS1R_FSC27_Msk                              /*!<Filter Scale Configuration bit 27 */

/******************  Bit definition for CAN_FFA1R register  *******************/
#define CAN_FFA1R_FFA_Pos      (0U)
#define CAN_FFA1R_FFA_Msk      (0xFFFFFFFUL << CAN_FFA1R_FFA_Pos)               /*!< 0x0FFFFFFF */
#define CAN_FFA1R_FFA          CAN_FFA1R_FFA_Msk                               /*!<Filter FIFO Assignment */
#define CAN_FFA1R_FFA0_Pos     (0U)
#define CAN_FFA1R_FFA0_Msk     (0x1UL << CAN_FFA1R_FFA0_Pos)                    /*!< 0x00000001 */
#define CAN_FFA1R_FFA0         CAN_FFA1R_FFA0_Msk                              /*!<Filter FIFO Assignment bit 0 */
#define CAN_FFA1R_FFA1_Pos     (1U)
#define CAN_FFA1R_FFA1_Msk     (0x1UL << CAN_FFA1R_FFA1_Pos)                    /*!< 0x00000002 */
#define CAN_FFA1R_FFA1         CAN_FFA1R_FFA1_Msk                              /*!<Filter FIFO Assignment bit 1 */
#define CAN_FFA1R_FFA2_Pos     (2U)
#define CAN_FFA1R_FFA2_Msk     (0x1UL << CAN_FFA1R_FFA2_Pos)                    /*!< 0x00000004 */
#define CAN_FFA1R_FFA2         CAN_FFA1R_FFA2_Msk                              /*!<Filter FIFO Assignment bit 2 */
#define CAN_FFA1R_FFA3_Pos     (3U)
#define CAN_FFA1R_FFA3_Msk     (0x1UL << CAN_FFA1R_FFA3_Pos)                    /*!< 0x00000008 */
#define CAN_FFA1R_FFA3         CAN_FFA1R_FFA3_Msk                              /*!<Filter FIFO Assignment bit 3 */
#define CAN_FFA1R_FFA4_Pos     (4U)
#define CAN_FFA1R_FFA4_Msk     (0x1UL << CAN_FFA1R_FFA4_Pos)                    /*!< 0x00000010 */
#define CAN_FFA1R_FFA4         CAN_FFA1R_FFA4_Msk                              /*!<Filter FIFO Assignment bit 4 */
#define CAN_FFA1R_FFA5_Pos     (5U)
#define CAN_FFA1R_FFA5_Msk     (0x1UL << CAN_FFA1R_FFA5_Pos)                    /*!< 0x00000020 */
#define CAN_FFA1R_FFA5         CAN_FFA1R_FFA5_Msk                              /*!<Filter FIFO Assignment bit 5 */
#define CAN_FFA1R_FFA6_Pos     (6U)
#define CAN_FFA1R_FFA6_Msk     (0x1UL << CAN_FFA1R_FFA6_Pos)                    /*!< 0x00000040 */
#define CAN_FFA1R_FFA6         CAN_FFA1R_FFA6_Msk                              /*!<Filter FIFO Assignment bit 6 */
#define CAN_FFA1R_FFA7_Pos     (7U)
#define CAN_FFA1R_FFA7_Msk     (0x1UL << CAN_FFA1R_FFA7_Pos)                    /*!< 0x00000080 */
#define CAN_FFA1R_FFA7         CAN_FFA1R_FFA7_Msk                              /*!<Filter FIFO Assignment bit 7 */
#define CAN_FFA1R_FFA8_Pos     (8U)
#define CAN_FFA1R_FFA8_Msk     (0x1UL << CAN_FFA1R_FFA8_Pos)                    /*!< 0x00000100 */
#define CAN_FFA1R_FFA8         CAN_FFA1R_FFA8_Msk                              /*!<Filter FIFO Assignment bit 8 */
#define CAN_FFA1R_FFA9_Pos     (9U)
#define CAN_FFA1R_FFA9_Msk     (0x1UL << CAN_FFA1R_FFA9_Pos)                    /*!< 0x00000200 */
#define CAN_FFA1R_FFA9         CAN_FFA1R_FFA9_Msk                              /*!<Filter FIFO Assignment bit 9 */
#define CAN_FFA1R_FFA10_Pos    (10U)
#define CAN_FFA1R_FFA10_Msk    (0x1UL << CAN_FFA1R_FFA10_Pos)                   /*!< 0x00000400 */
#define CAN_FFA1R_FFA10        CAN_FFA1R_FFA10_Msk                             /*!<Filter FIFO Assignment bit 10 */
#define CAN_FFA1R_FFA11_Pos    (11U)
#define CAN_FFA1R_FFA11_Msk    (0x1UL << CAN_FFA1R_FFA11_Pos)                   /*!< 0x00000800 */
#define CAN_FFA1R_FFA11        CAN_FFA1R_FFA11_Msk                             /*!<Filter FIFO Assignment bit 11 */
#define CAN_FFA1R_FFA12_Pos    (12U)
#define CAN_FFA1R_FFA12_Msk    (0x1UL << CAN_FFA1R_FFA12_Pos)                   /*!< 0x00001000 */
#define CAN_FFA1R_FFA12        CAN_FFA1R_FFA12_Msk                             /*!<Filter FIFO Assignment bit 12 */
#define CAN_FFA1R_FFA13_Pos    (13U)
#define CAN_FFA1R_FFA13_Msk    (0x1UL << CAN_FFA1R_FFA13_Pos)                   /*!< 0x00002000 */
#define CAN_FFA1R_FFA13        CAN_FFA1R_FFA13_Msk                             /*!<Filter FIFO Assignment bit 13 */
#define CAN_FFA1R_FFA14_Pos    (14U)
#define CAN_FFA1R_FFA14_Msk    (0x1UL << CAN_FFA1R_FFA14_Pos)                   /*!< 0x00004000 */
#define CAN_FFA1R_FFA14        CAN_FFA1R_FFA14_Msk                             /*!<Filter FIFO Assignment bit 14 */
#define CAN_FFA1R_FFA15_Pos    (15U)
#define CAN_FFA1R_FFA15_Msk    (0x1UL << CAN_FFA1R_FFA15_Pos)                   /*!< 0x00008000 */
#define CAN_FFA1R_FFA15        CAN_FFA1R_FFA15_Msk                             /*!<Filter FIFO Assignment bit 15 */
#define CAN_FFA1R_FFA16_Pos    (16U)
#define CAN_FFA1R_FFA16_Msk    (0x1UL << CAN_FFA1R_FFA16_Pos)                   /*!< 0x00010000 */
#define CAN_FFA1R_FFA16        CAN_FFA1R_FFA16_Msk                             /*!<Filter FIFO Assignment bit 16 */
#define CAN_FFA1R_FFA17_Pos    (17U)
#define CAN_FFA1R_FFA17_Msk    (0x1UL << CAN_FFA1R_FFA17_Pos)                   /*!< 0x00020000 */
#define CAN_FFA1R_FFA17        CAN_FFA1R_FFA17_Msk                             /*!<Filter FIFO Assignment bit 17 */
#define CAN_FFA1R_FFA18_Pos    (18U)
#define CAN_FFA1R_FFA18_Msk    (0x1UL << CAN_FFA1R_FFA18_Pos)                   /*!< 0x00040000 */
#define CAN_FFA1R_FFA18        CAN_FFA1R_FFA18_Msk                             /*!<Filter FIFO Assignment bit 18 */
#define CAN_FFA1R_FFA19_Pos    (19U)
#define CAN_FFA1R_FFA19_Msk    (0x1UL << CAN_FFA1R_FFA19_Pos)                   /*!< 0x00080000 */
#define CAN_FFA1R_FFA19        CAN_FFA1R_FFA19_Msk                             /*!<Filter FIFO Assignment bit 19 */
#define CAN_FFA1R_FFA20_Pos    (20U)
#define CAN_FFA1R_FFA20_Msk    (0x1UL << CAN_FFA1R_FFA20_Pos)                   /*!< 0x00100000 */
#define CAN_FFA1R_FFA20        CAN_FFA1R_FFA20_Msk                             /*!<Filter FIFO Assignment bit 20 */
#define CAN_FFA1R_FFA21_Pos    (21U)
#define CAN_FFA1R_FFA21_Msk    (0x1UL << CAN_FFA1R_FFA21_Pos)                   /*!< 0x00200000 */
#define CAN_FFA1R_FFA21        CAN_FFA1R_FFA21_Msk                             /*!<Filter FIFO Assignment bit 21 */
#define CAN_FFA1R_FFA22_Pos    (22U)
#define CAN_FFA1R_FFA22_Msk    (0x1UL << CAN_FFA1R_FFA22_Pos)                   /*!< 0x00400000 */
#define CAN_FFA1R_FFA22        CAN_FFA1R_FFA22_Msk                             /*!<Filter FIFO Assignment bit 22 */
#define CAN_FFA1R_FFA23_Pos    (23U)
#define CAN_FFA1R_FFA23_Msk    (0x1UL << CAN_FFA1R_FFA23_Pos)                   /*!< 0x00800000 */
#define CAN_FFA1R_FFA23        CAN_FFA1R_FFA23_Msk                             /*!<Filter FIFO Assignment bit 23 */
#define CAN_FFA1R_FFA24_Pos    (24U)
#define CAN_FFA1R_FFA24_Msk    (0x1UL << CAN_FFA1R_FFA24_Pos)                   /*!< 0x01000000 */
#define CAN_FFA1R_FFA24        CAN_FFA1R_FFA24_Msk                             /*!<Filter FIFO Assignment bit 24 */
#define CAN_FFA1R_FFA25_Pos    (25U)
#define CAN_FFA1R_FFA25_Msk    (0x1UL << CAN_FFA1R_FFA25_Pos)                   /*!< 0x02000000 */
#define CAN_FFA1R_FFA25        CAN_FFA1R_FFA25_Msk                             /*!<Filter FIFO Assignment bit 25 */
#define CAN_FFA1R_FFA26_Pos    (26U)
#define CAN_FFA1R_FFA26_Msk    (0x1UL << CAN_FFA1R_FFA26_Pos)                   /*!< 0x04000000 */
#define CAN_FFA1R_FFA26        CAN_FFA1R_FFA26_Msk                             /*!<Filter FIFO Assignment bit 26 */
#define CAN_FFA1R_FFA27_Pos    (27U)
#define CAN_FFA1R_FFA27_Msk    (0x1UL << CAN_FFA1R_FFA27_Pos)                   /*!< 0x08000000 */
#define CAN_FFA1R_FFA27        CAN_FFA1R_FFA27_Msk                             /*!<Filter FIFO Assignment bit 27 */

/*******************  Bit definition for CAN_FA1R register  *******************/
#define CAN_FA1R_FACT_Pos      (0U)
#define CAN_FA1R_FACT_Msk      (0xFFFFFFFUL << CAN_FA1R_FACT_Pos)               /*!< 0x0FFFFFFF */
#define CAN_FA1R_FACT          CAN_FA1R_FACT_Msk                               /*!<Filter Active */
#define CAN_FA1R_FACT0_Pos     (0U)
#define CAN_FA1R_FACT0_Msk     (0x1UL << CAN_FA1R_FACT0_Pos)                    /*!< 0x00000001 */
#define CAN_FA1R_FACT0         CAN_FA1R_FACT0_Msk                              /*!<Filter Active bit 0 */
#define CAN_FA1R_FACT1_Pos     (1U)
#define CAN_FA1R_FACT1_Msk     (0x1UL << CAN_FA1R_FACT1_Pos)                    /*!< 0x00000002 */
#define CAN_FA1R_FACT1         CAN_FA1R_FACT1_Msk                              /*!<Filter Active bit 1 */
#define CAN_FA1R_FACT2_Pos     (2U)
#define CAN_FA1R_FACT2_Msk     (0x1UL << CAN_FA1R_FACT2_Pos)                    /*!< 0x00000004 */
#define CAN_FA1R_FACT2         CAN_FA1R_FACT2_Msk                              /*!<Filter Active bit 2 */
#define CAN_FA1R_FACT3_Pos     (3U)
#define CAN_FA1R_FACT3_Msk     (0x1UL << CAN_FA1R_FACT3_Pos)                    /*!< 0x00000008 */
#define CAN_FA1R_FACT3         CAN_FA1R_FACT3_Msk                              /*!<Filter Active bit 3 */
#define CAN_FA1R_FACT4_Pos     (4U)
#define CAN_FA1R_FACT4_Msk     (0x1UL << CAN_FA1R_FACT4_Pos)                    /*!< 0x00000010 */
#define CAN_FA1R_FACT4         CAN_FA1R_FACT4_Msk                              /*!<Filter Active bit 4 */
#define CAN_FA1R_FACT5_Pos     (5U)
#define CAN_FA1R_FACT5_Msk     (0x1UL << CAN_FA1R_FACT5_Pos)                    /*!< 0x00000020 */
#define CAN_FA1R_FACT5         CAN_FA1R_FACT5_Msk                              /*!<Filter Active bit 5 */
#define CAN_FA1R_FACT6_Pos     (6U)
#define CAN_FA1R_FACT6_Msk     (0x1UL << CAN_FA1R_FACT6_Pos)                    /*!< 0x00000040 */
#define CAN_FA1R_FACT6         CAN_FA1R_FACT6_Msk                              /*!<Filter Active bit 6 */
#define CAN_FA1R_FACT7_Pos     (7U)
#define CAN_FA1R_FACT7_Msk     (0x1UL << CAN_FA1R_FACT7_Pos)                    /*!< 0x00000080 */
#define CAN_FA1R_FACT7         CAN_FA1R_FACT7_Msk                              /*!<Filter Active bit 7 */
#define CAN_FA1R_FACT8_Pos     (8U)
#define CAN_FA1R_FACT8_Msk     (0x1UL << CAN_FA1R_FACT8_Pos)                    /*!< 0x00000100 */
#define CAN_FA1R_FACT8         CAN_FA1R_FACT8_Msk                              /*!<Filter Active bit 8 */
#define CAN_FA1R_FACT9_Pos     (9U)
#define CAN_FA1R_FACT9_Msk     (0x1UL << CAN_FA1R_FACT9_Pos)                    /*!< 0x00000200 */
#define CAN_FA1R_FACT9         CAN_FA1R_FACT9_Msk                              /*!<Filter Active bit 9 */
#define CAN_FA1R_FACT10_Pos    (10U)
#define CAN_FA1R_FACT10_Msk    (0x1UL << CAN_FA1R_FACT10_Pos)                   /*!< 0x00000400 */
#define CAN_FA1R_FACT10        CAN_FA1R_FACT10_Msk                             /*!<Filter Active bit 10 */
#define CAN_FA1R_FACT11_Pos    (11U)
#define CAN_FA1R_FACT11_Msk    (0x1UL << CAN_FA1R_FACT11_Pos)                   /*!< 0x00000800 */
#define CAN_FA1R_FACT11        CAN_FA1R_FACT11_Msk                             /*!<Filter Active bit 11 */
#define CAN_FA1R_FACT12_Pos    (12U)
#define CAN_FA1R_FACT12_Msk    (0x1UL << CAN_FA1R_FACT12_Pos)                   /*!< 0x00001000 */
#define CAN_FA1R_FACT12        CAN_FA1R_FACT12_Msk                             /*!<Filter Active bit 12 */
#define CAN_FA1R_FACT13_Pos    (13U)
#define CAN_FA1R_FACT13_Msk    (0x1UL << CAN_FA1R_FACT13_Pos)                   /*!< 0x00002000 */
#define CAN_FA1R_FACT13        CAN_FA1R_FACT13_Msk                             /*!<Filter Active bit 13 */
#define CAN_FA1R_FACT14_Pos    (14U)
#define CAN_FA1R_FACT14_Msk    (0x1UL << CAN_FA1R_FACT14_Pos)                   /*!< 0x00004000 */
#define CAN_FA1R_FACT14        CAN_FA1R_FACT14_Msk                             /*!<Filter Active bit 14 */
#define CAN_FA1R_FACT15_Pos    (15U)
#define CAN_FA1R_FACT15_Msk    (0x1UL << CAN_FA1R_FACT15_Pos)                   /*!< 0x00008000 */
#define CAN_FA1R_FACT15        CAN_FA1R_FACT15_Msk                             /*!<Filter Active bit 15 */
#define CAN_FA1R_FACT16_Pos    (16U)
#define CAN_FA1R_FACT16_Msk    (0x1UL << CAN_FA1R_FACT16_Pos)                   /*!< 0x00010000 */
#define CAN_FA1R_FACT16        CAN_FA1R_FACT16_Msk                             /*!<Filter Active bit 16 */
#define CAN_FA1R_FACT17_Pos    (17U)
#define CAN_FA1R_FACT17_Msk    (0x1UL << CAN_FA1R_FACT17_Pos)                   /*!< 0x00020000 */
#define CAN_FA1R_FACT17        CAN_FA1R_FACT17_Msk                             /*!<Filter Active bit 17 */
#define CAN_FA1R_FACT18_Pos    (18U)
#define CAN_FA1R_FACT18_Msk    (0x1UL << CAN_FA1R_FACT18_Pos)                   /*!< 0x00040000 */
#define CAN_FA1R_FACT18        CAN_FA1R_FACT18_Msk                             /*!<Filter Active bit 18 */
#define CAN_FA1R_FACT19_Pos    (19U)
#define CAN_FA1R_FACT19_Msk    (0x1UL << CAN_FA1R_FACT19_Pos)                   /*!< 0x00080000 */
#define CAN_FA1R_FACT19        CAN_FA1R_FACT19_Msk                             /*!<Filter Active bit 19 */
#define CAN_FA1R_FACT20_Pos    (20U)
#define CAN_FA1R_FACT20_Msk    (0x1UL << CAN_FA1R_FACT20_Pos)                   /*!< 0x00100000 */
#define CAN_FA1R_FACT20        CAN_FA1R_FACT20_Msk                             /*!<Filter Active bit 20 */
#define CAN_FA1R_FACT21_Pos    (21U)
#define CAN_FA1R_FACT21_Msk    (0x1UL << CAN_FA1R_FACT21_Pos)                   /*!< 0x00200000 */
#define CAN_FA1R_FACT21        CAN_FA1R_FACT21_Msk                             /*!<Filter Active bit 21 */
#define CAN_FA1R_FACT22_Pos    (22U)
#define CAN_FA1R_FACT22_Msk    (0x1UL << CAN_FA1R_FACT22_Pos)                   /*!< 0x00400000 */
#define CAN_FA1R_FACT22        CAN_FA1R_FACT22_Msk                             /*!<Filter Active bit 22 */
#define CAN_FA1R_FACT23_Pos    (23U)
#define CAN_FA1R_FACT23_Msk    (0x1UL << CAN_FA1R_FACT23_Pos)                   /*!< 0x00800000 */
#define CAN_FA1R_FACT23        CAN_FA1R_FACT23_Msk                             /*!<Filter Active bit 23 */
#define CAN_FA1R_FACT24_Pos    (24U)
#define CAN_FA1R_FACT24_Msk    (0x1UL << CAN_FA1R_FACT24_Pos)                   /*!< 0x01000000 */
#define CAN_FA1R_FACT24        CAN_FA1R_FACT24_Msk                             /*!<Filter Active bit 24 */
#define CAN_FA1R_FACT25_Pos    (25U)
#define CAN_FA1R_FACT25_Msk    (0x1UL << CAN_FA1R_FACT25_Pos)                   /*!< 0x02000000 */
#define CAN_FA1R_FACT25        CAN_FA1R_FACT25_Msk                             /*!<Filter Active bit 25 */
#define CAN_FA1R_FACT26_Pos    (26U)
#define CAN_FA1R_FACT26_Msk    (0x1UL << CAN_FA1R_FACT26_Pos)                   /*!< 0x04000000 */
#define CAN_FA1R_FACT26        CAN_FA1R_FACT26_Msk                             /*!<Filter Active bit 26 */
#define CAN_FA1R_FACT27_Pos    (27U)
#define CAN_FA1R_FACT27_Msk    (0x1UL << CAN_FA1R_FACT27_Pos)                   /*!< 0x08000000 */
#define CAN_FA1R_FACT27        CAN_FA1R_FACT27_Msk                             /*!<Filter Active bit 27 */


/*******************  Bit definition for CAN_F0R1 register  *******************/
#define CAN_F0R1_FB0_Pos       (0U)
#define CAN_F0R1_FB0_Msk       (0x1UL << CAN_F0R1_FB0_Pos)                      /*!< 0x00000001 */
#define CAN_F0R1_FB0           CAN_F0R1_FB0_Msk                                /*!<Filter bit 0 */
#define CAN_F0R1_FB1_Pos       (1U)
#define CAN_F0R1_FB1_Msk       (0x1UL << CAN_F0R1_FB1_Pos)                      /*!< 0x00000002 */
#define CAN_F0R1_FB1           CAN_F0R1_FB1_Msk                                /*!<Filter bit 1 */
#define CAN_F0R1_FB2_Pos       (2U)
#define CAN_F0R1_FB2_Msk       (0x1UL << CAN_F0R1_FB2_Pos)                      /*!< 0x00000004 */
#define CAN_F0R1_FB2           CAN_F0R1_FB2_Msk                                /*!<Filter bit 2 */
#define CAN_F0R1_FB3_Pos       (3U)
#define CAN_F0R1_FB3_Msk       (0x1UL << CAN_F0R1_FB3_Pos)                      /*!< 0x00000008 */
#define CAN_F0R1_FB3           CAN_F0R1_FB3_Msk                                /*!<Filter bit 3 */
#define CAN_F0R1_FB4_Pos       (4U)
#define CAN_F0R1_FB4_Msk       (0x1UL << CAN_F0R1_FB4_Pos)                      /*!< 0x00000010 */
#define CAN_F0R1_FB4           CAN_F0R1_FB4_Msk                                /*!<Filter bit 4 */
#define CAN_F0R1_FB5_Pos       (5U)
#define CAN_F0R1_FB5_Msk       (0x1UL << CAN_F0R1_FB5_Pos)                      /*!< 0x00000020 */
#define CAN_F0R1_FB5           CAN_F0R1_FB5_Msk                                /*!<Filter bit 5 */
#define CAN_F0R1_FB6_Pos       (6U)
#define CAN_F0R1_FB6_Msk       (0x1UL << CAN_F0R1_FB6_Pos)                      /*!< 0x00000040 */
#define CAN_F0R1_FB6           CAN_F0R1_FB6_Msk                                /*!<Filter bit 6 */
#define CAN_F0R1_FB7_Pos       (7U)
#define CAN_F0R1_FB7_Msk       (0x1UL << CAN_F0R1_FB7_Pos)                      /*!< 0x00000080 */
#define CAN_F0R1_FB7           CAN_F0R1_FB7_Msk                                /*!<Filter bit 7 */
#define CAN_F0R1_FB8_Pos       (8U)
#define CAN_F0R1_FB8_Msk       (0x1UL << CAN_F0R1_FB8_Pos)                      /*!< 0x00000100 */
#define CAN_F0R1_FB8           CAN_F0R1_FB8_Msk                                /*!<Filter bit 8 */
#define CAN_F0R1_FB9_Pos       (9U)
#define CAN_F0R1_FB9_Msk       (0x1UL << CAN_F0R1_FB9_Pos)                      /*!< 0x00000200 */
#define CAN_F0R1_FB9           CAN_F0R1_FB9_Msk                                /*!<Filter bit 9 */
#define CAN_F0R1_FB10_Pos      (10U)
#define CAN_F0R1_FB10_Msk      (0x1UL << CAN_F0R1_FB10_Pos)                     /*!< 0x00000400 */
#define CAN_F0R1_FB10          CAN_F0R1_FB10_Msk                               /*!<Filter bit 10 */
#define CAN_F0R1_FB11_Pos      (11U)
#define CAN_F0R1_FB11_Msk      (0x1UL << CAN_F0R1_FB11_Pos)                     /*!< 0x00000800 */
#define CAN_F0R1_FB11          CAN_F0R1_FB11_Msk                               /*!<Filter bit 11 */
#define CAN_F0R1_FB12_Pos      (12U)
#define CAN_F0R1_FB12_Msk      (0x1UL << CAN_F0R1_FB12_Pos)                     /*!< 0x00001000 */
#define CAN_F0R1_FB12          CAN_F0R1_FB12_Msk                               /*!<Filter bit 12 */
#define CAN_F0R1_FB13_Pos      (13U)
#define CAN_F0R1_FB13_Msk      (0x1UL << CAN_F0R1_FB13_Pos)                     /*!< 0x00002000 */
#define CAN_F0R1_FB13          CAN_F0R1_FB13_Msk                               /*!<Filter bit 13 */
#define CAN_F0R1_FB14_Pos      (14U)
#define CAN_F0R1_FB14_Msk      (0x1UL << CAN_F0R1_FB14_Pos)                     /*!< 0x00004000 */
#define CAN_F0R1_FB14          CAN_F0R1_FB14_Msk                               /*!<Filter bit 14 */
#define CAN_F0R1_FB15_Pos      (15U)
#define CAN_F0R1_FB15_Msk      (0x1UL << CAN_F0R1_FB15_Pos)                     /*!< 0x00008000 */
#define CAN_F0R1_FB15          CAN_F0R1_FB15_Msk                               /*!<Filter bit 15 */
#define CAN_F0R1_FB16_Pos      (16U)
#define CAN_F0R1_FB16_Msk      (0x1UL << CAN_F0R1_FB16_Pos)                     /*!< 0x00010000 */
#define CAN_F0R1_FB16          CAN_F0R1_FB16_Msk                               /*!<Filter bit 16 */
#define CAN_F0R1_FB17_Pos      (17U)
#define CAN_F0R1_FB17_Msk      (0x1UL << CAN_F0R1_FB17_Pos)                     /*!< 0x00020000 */
#define CAN_F0R1_FB17          CAN_F0R1_FB17_Msk                               /*!<Filter bit 17 */
#define CAN_F0R1_FB18_Pos      (18U)
#define CAN_F0R1_FB18_Msk      (0x1UL << CAN_F0R1_FB18_Pos)                     /*!< 0x00040000 */
#define CAN_F0R1_FB18          CAN_F0R1_FB18_Msk                               /*!<Filter bit 18 */
#define CAN_F0R1_FB19_Pos      (19U)
#define CAN_F0R1_FB19_Msk      (0x1UL << CAN_F0R1_FB19_Pos)                     /*!< 0x00080000 */
#define CAN_F0R1_FB19          CAN_F0R1_FB19_Msk                               /*!<Filter bit 19 */
#define CAN_F0R1_FB20_Pos      (20U)
#define CAN_F0R1_FB20_Msk      (0x1UL << CAN_F0R1_FB20_Pos)                     /*!< 0x00100000 */
#define CAN_F0R1_FB20          CAN_F0R1_FB20_Msk                               /*!<Filter bit 20 */
#define CAN_F0R1_FB21_Pos      (21U)
#define CAN_F0R1_FB21_Msk      (0x1UL << CAN_F0R1_FB21_Pos)                     /*!< 0x00200000 */
#define CAN_F0R1_FB21          CAN_F0R1_FB21_Msk                               /*!<Filter bit 21 */
#define CAN_F0R1_FB22_Pos      (22U)
#define CAN_F0R1_FB22_Msk      (0x1UL << CAN_F0R1_FB22_Pos)                     /*!< 0x00400000 */
#define CAN_F0R1_FB22          CAN_F0R1_FB22_Msk                               /*!<Filter bit 22 */
#define CAN_F0R1_FB23_Pos      (23U)
#define CAN_F0R1_FB23_Msk      (0x1UL << CAN_F0R1_FB23_Pos)                     /*!< 0x00800000 */
#define CAN_F0R1_FB23          CAN_F0R1_FB23_Msk                               /*!<Filter bit 23 */
#define CAN_F0R1_FB24_Pos      (24U)
#define CAN_F0R1_FB24_Msk      (0x1UL << CAN_F0R1_FB24_Pos)                     /*!< 0x01000000 */
#define CAN_F0R1_FB24          CAN_F0R1_FB24_Msk                               /*!<Filter bit 24 */
#define CAN_F0R1_FB25_Pos      (25U)
#define CAN_F0R1_FB25_Msk      (0x1UL << CAN_F0R1_FB25_Pos)                     /*!< 0x02000000 */
#define CAN_F0R1_FB25          CAN_F0R1_FB25_Msk                               /*!<Filter bit 25 */
#define CAN_F0R1_FB26_Pos      (26U)
#define CAN_F0R1_FB26_Msk      (0x1UL << CAN_F0R1_FB26_Pos)                     /*!< 0x04000000 */
#define CAN_F0R1_FB26          CAN_F0R1_FB26_Msk                               /*!<Filter bit 26 */
#define CAN_F0R1_FB27_Pos      (27U)
#define CAN_F0R1_FB27_Msk      (0x1UL << CAN_F0R1_FB27_Pos)                     /*!< 0x08000000 */
#define CAN_F0R1_FB27          CAN_F0R1_FB27_Msk                               /*!<Filter bit 27 */
#define CAN_F0R1_FB28_Pos      (28U)
#define CAN_F0R1_FB28_Msk      (0x1UL << CAN_F0R1_FB28_Pos)                     /*!< 0x10000000 */
#define CAN_F0R1_FB28          CAN_F0R1_FB28_Msk                               /*!<Filter bit 28 */
#define CAN_F0R1_FB29_Pos      (29U)
#define CAN_F0R1_FB29_Msk      (0x1UL << CAN_F0R1_FB29_Pos)                     /*!< 0x20000000 */
#define CAN_F0R1_FB29          CAN_F0R1_FB29_Msk                               /*!<Filter bit 29 */
#define CAN_F0R1_FB30_Pos      (30U)
#define CAN_F0R1_FB30_Msk      (0x1UL << CAN_F0R1_FB30_Pos)                     /*!< 0x40000000 */
#define CAN_F0R1_FB30          CAN_F0R1_FB30_Msk                               /*!<Filter bit 30 */
#define CAN_F0R1_FB31_Pos      (31U)
#define CAN_F0R1_FB31_Msk      (0x1UL << CAN_F0R1_FB31_Pos)                     /*!< 0x80000000 */
#define CAN_F0R1_FB31          CAN_F0R1_FB31_Msk                               /*!<Filter bit 31 */

/*******************  Bit definition for CAN_F1R1 register  *******************/
#define CAN_F1R1_FB0_Pos       (0U)
#define CAN_F1R1_FB0_Msk       (0x1UL << CAN_F1R1_FB0_Pos)                      /*!< 0x00000001 */
#define CAN_F1R1_FB0           CAN_F1R1_FB0_Msk                                /*!<Filter bit 0 */
#define CAN_F1R1_FB1_Pos       (1U)
#define CAN_F1R1_FB1_Msk       (0x1UL << CAN_F1R1_FB1_Pos)                      /*!< 0x00000002 */
#define CAN_F1R1_FB1           CAN_F1R1_FB1_Msk                                /*!<Filter bit 1 */
#define CAN_F1R1_FB2_Pos       (2U)
#define CAN_F1R1_FB2_Msk       (0x1UL << CAN_F1R1_FB2_Pos)                      /*!< 0x00000004 */
#define CAN_F1R1_FB2           CAN_F1R1_FB2_Msk                                /*!<Filter bit 2 */
#define CAN_F1R1_FB3_Pos       (3U)
#define CAN_F1R1_FB3_Msk       (0x1UL << CAN_F1R1_FB3_Pos)                      /*!< 0x00000008 */
#define CAN_F1R1_FB3           CAN_F1R1_FB3_Msk                                /*!<Filter bit 3 */
#define CAN_F1R1_FB4_Pos       (4U)
#define CAN_F1R1_FB4_Msk       (0x1UL << CAN_F1R1_FB4_Pos)                      /*!< 0x00000010 */
#define CAN_F1R1_FB4           CAN_F1R1_FB4_Msk                                /*!<Filter bit 4 */
#define CAN_F1R1_FB5_Pos       (5U)
#define CAN_F1R1_FB5_Msk       (0x1UL << CAN_F1R1_FB5_Pos)                      /*!< 0x00000020 */
#define CAN_F1R1_FB5           CAN_F1R1_FB5_Msk                                /*!<Filter bit 5 */
#define CAN_F1R1_FB6_Pos       (6U)
#define CAN_F1R1_FB6_Msk       (0x1UL << CAN_F1R1_FB6_Pos)                      /*!< 0x00000040 */
#define CAN_F1R1_FB6           CAN_F1R1_FB6_Msk                                /*!<Filter bit 6 */
#define CAN_F1R1_FB7_Pos       (7U)
#define CAN_F1R1_FB7_Msk       (0x1UL << CAN_F1R1_FB7_Pos)                      /*!< 0x00000080 */
#define CAN_F1R1_FB7           CAN_F1R1_FB7_Msk                                /*!<Filter bit 7 */
#define CAN_F1R1_FB8_Pos       (8U)
#define CAN_F1R1_FB8_Msk       (0x1UL << CAN_F1R1_FB8_Pos)                      /*!< 0x00000100 */
#define CAN_F1R1_FB8           CAN_F1R1_FB8_Msk                                /*!<Filter bit 8 */
#define CAN_F1R1_FB9_Pos       (9U)
#define CAN_F1R1_FB9_Msk       (0x1UL << CAN_F1R1_FB9_Pos)                      /*!< 0x00000200 */
#define CAN_F1R1_FB9           CAN_F1R1_FB9_Msk                                /*!<Filter bit 9 */
#define CAN_F1R1_FB10_Pos      (10U)
#define CAN_F1R1_FB10_Msk      (0x1UL << CAN_F1R1_FB10_Pos)                     /*!< 0x00000400 */
#define CAN_F1R1_FB10          CAN_F1R1_FB10_Msk                               /*!<Filter bit 10 */
#define CAN_F1R1_FB11_Pos      (11U)
#define CAN_F1R1_FB11_Msk      (0x1UL << CAN_F1R1_FB11_Pos)                     /*!< 0x00000800 */
#define CAN_F1R1_FB11          CAN_F1R1_FB11_Msk                               /*!<Filter bit 11 */
#define CAN_F1R1_FB12_Pos      (12U)
#define CAN_F1R1_FB12_Msk      (0x1UL << CAN_F1R1_FB12_Pos)                     /*!< 0x00001000 */
#define CAN_F1R1_FB12          CAN_F1R1_FB12_Msk                               /*!<Filter bit 12 */
#define CAN_F1R1_FB13_Pos      (13U)
#define CAN_F1R1_FB13_Msk      (0x1UL << CAN_F1R1_FB13_Pos)                     /*!< 0x00002000 */
#define CAN_F1R1_FB13          CAN_F1R1_FB13_Msk                               /*!<Filter bit 13 */
#define CAN_F1R1_FB14_Pos      (14U)
#define CAN_F1R1_FB14_Msk      (0x1UL << CAN_F1R1_FB14_Pos)                     /*!< 0x00004000 */
#define CAN_F1R1_FB14          CAN_F1R1_FB14_Msk                               /*!<Filter bit 14 */
#define CAN_F1R1_FB15_Pos      (15U)
#define CAN_F1R1_FB15_Msk      (0x1UL << CAN_F1R1_FB15_Pos)                     /*!< 0x00008000 */
#define CAN_F1R1_FB15          CAN_F1R1_FB15_Msk                               /*!<Filter bit 15 */
#define CAN_F1R1_FB16_Pos      (16U)
#define CAN_F1R1_FB16_Msk      (0x1UL << CAN_F1R1_FB16_Pos)                     /*!< 0x00010000 */
#define CAN_F1R1_FB16          CAN_F1R1_FB16_Msk                               /*!<Filter bit 16 */
#define CAN_F1R1_FB17_Pos      (17U)
#define CAN_F1R1_FB17_Msk      (0x1UL << CAN_F1R1_FB17_Pos)                     /*!< 0x00020000 */
#define CAN_F1R1_FB17          CAN_F1R1_FB17_Msk                               /*!<Filter bit 17 */
#define CAN_F1R1_FB18_Pos      (18U)
#define CAN_F1R1_FB18_Msk      (0x1UL << CAN_F1R1_FB18_Pos)                     /*!< 0x00040000 */
#define CAN_F1R1_FB18          CAN_F1R1_FB18_Msk                               /*!<Filter bit 18 */
#define CAN_F1R1_FB19_Pos      (19U)
#define CAN_F1R1_FB19_Msk      (0x1UL << CAN_F1R1_FB19_Pos)                     /*!< 0x00080000 */
#define CAN_F1R1_FB19          CAN_F1R1_FB19_Msk                               /*!<Filter bit 19 */
#define CAN_F1R1_FB20_Pos      (20U)
#define CAN_F1R1_FB20_Msk      (0x1UL << CAN_F1R1_FB20_Pos)                     /*!< 0x00100000 */
#define CAN_F1R1_FB20          CAN_F1R1_FB20_Msk                               /*!<Filter bit 20 */
#define CAN_F1R1_FB21_Pos      (21U)
#define CAN_F1R1_FB21_Msk      (0x1UL << CAN_F1R1_FB21_Pos)                     /*!< 0x00200000 */
#define CAN_F1R1_FB21          CAN_F1R1_FB21_Msk                               /*!<Filter bit 21 */
#define CAN_F1R1_FB22_Pos      (22U)
#define CAN_F1R1_FB22_Msk      (0x1UL << CAN_F1R1_FB22_Pos)                     /*!< 0x00400000 */
#define CAN_F1R1_FB22          CAN_F1R1_FB22_Msk                               /*!<Filter bit 22 */
#define CAN_F1R1_FB23_Pos      (23U)
#define CAN_F1R1_FB23_Msk      (0x1UL << CAN_F1R1_FB23_Pos)                     /*!< 0x00800000 */
#define CAN_F1R1_FB23          CAN_F1R1_FB23_Msk                               /*!<Filter bit 23 */
#define CAN_F1R1_FB24_Pos      (24U)
#define CAN_F1R1_FB24_Msk      (0x1UL << CAN_F1R1_FB24_Pos)                     /*!< 0x01000000 */
#define CAN_F1R1_FB24          CAN_F1R1_FB24_Msk                               /*!<Filter bit 24 */
#define CAN_F1R1_FB25_Pos      (25U)
#define CAN_F1R1_FB25_Msk      (0x1UL << CAN_F1R1_FB25_Pos)                     /*!< 0x02000000 */
#define CAN_F1R1_FB25          CAN_F1R1_FB25_Msk                               /*!<Filter bit 25 */
#define CAN_F1R1_FB26_Pos      (26U)
#define CAN_F1R1_FB26_Msk      (0x1UL << CAN_F1R1_FB26_Pos)                     /*!< 0x04000000 */
#define CAN_F1R1_FB26          CAN_F1R1_FB26_Msk                               /*!<Filter bit 26 */
#define CAN_F1R1_FB27_Pos      (27U)
#define CAN_F1R1_FB27_Msk      (0x1UL << CAN_F1R1_FB27_Pos)                     /*!< 0x08000000 */
#define CAN_F1R1_FB27          CAN_F1R1_FB27_Msk                               /*!<Filter bit 27 */
#define CAN_F1R1_FB28_Pos      (28U)
#define CAN_F1R1_FB28_Msk      (0x1UL << CAN_F1R1_FB28_Pos)                     /*!< 0x10000000 */
#define CAN_F1R1_FB28          CAN_F1R1_FB28_Msk                               /*!<Filter bit 28 */
#define CAN_F1R1_FB29_Pos      (29U)
#define CAN_F1R1_FB29_Msk      (0x1UL << CAN_F1R1_FB29_Pos)                     /*!< 0x20000000 */
#define CAN_F1R1_FB29          CAN_F1R1_FB29_Msk                               /*!<Filter bit 29 */
#define CAN_F1R1_FB30_Pos      (30U)
#define CAN_F1R1_FB30_Msk      (0x1UL << CAN_F1R1_FB30_Pos)                     /*!< 0x40000000 */
#define CAN_F1R1_FB30          CAN_F1R1_FB30_Msk                               /*!<Filter bit 30 */
#define CAN_F1R1_FB31_Pos      (31U)
#define CAN_F1R1_FB31_Msk      (0x1UL << CAN_F1R1_FB31_Pos)                     /*!< 0x80000000 */
#define CAN_F1R1_FB31          CAN_F1R1_FB31_Msk                               /*!<Filter bit 31 */

/*******************  Bit definition for CAN_F2R1 register  *******************/
#define CAN_F2R1_FB0_Pos       (0U)
#define CAN_F2R1_FB0_Msk       (0x1UL << CAN_F2R1_FB0_Pos)                      /*!< 0x00000001 */
#define CAN_F2R1_FB0           CAN_F2R1_FB0_Msk                                /*!<Filter bit 0 */
#define CAN_F2R1_FB1_Pos       (1U)
#define CAN_F2R1_FB1_Msk       (0x1UL << CAN_F2R1_FB1_Pos)                      /*!< 0x00000002 */
#define CAN_F2R1_FB1           CAN_F2R1_FB1_Msk                                /*!<Filter bit 1 */
#define CAN_F2R1_FB2_Pos       (2U)
#define CAN_F2R1_FB2_Msk       (0x1UL << CAN_F2R1_FB2_Pos)                      /*!< 0x00000004 */
#define CAN_F2R1_FB2           CAN_F2R1_FB2_Msk                                /*!<Filter bit 2 */
#define CAN_F2R1_FB3_Pos       (3U)
#define CAN_F2R1_FB3_Msk       (0x1UL << CAN_F2R1_FB3_Pos)                      /*!< 0x00000008 */
#define CAN_F2R1_FB3           CAN_F2R1_FB3_Msk                                /*!<Filter bit 3 */
#define CAN_F2R1_FB4_Pos       (4U)
#define CAN_F2R1_FB4_Msk       (0x1UL << CAN_F2R1_FB4_Pos)                      /*!< 0x00000010 */
#define CAN_F2R1_FB4           CAN_F2R1_FB4_Msk                                /*!<Filter bit 4 */
#define CAN_F2R1_FB5_Pos       (5U)
#define CAN_F2R1_FB5_Msk       (0x1UL << CAN_F2R1_FB5_Pos)                      /*!< 0x00000020 */
#define CAN_F2R1_FB5           CAN_F2R1_FB5_Msk                                /*!<Filter bit 5 */
#define CAN_F2R1_FB6_Pos       (6U)
#define CAN_F2R1_FB6_Msk       (0x1UL << CAN_F2R1_FB6_Pos)                      /*!< 0x00000040 */
#define CAN_F2R1_FB6           CAN_F2R1_FB6_Msk                                /*!<Filter bit 6 */
#define CAN_F2R1_FB7_Pos       (7U)
#define CAN_F2R1_FB7_Msk       (0x1UL << CAN_F2R1_FB7_Pos)                      /*!< 0x00000080 */
#define CAN_F2R1_FB7           CAN_F2R1_FB7_Msk                                /*!<Filter bit 7 */
#define CAN_F2R1_FB8_Pos       (8U)
#define CAN_F2R1_FB8_Msk       (0x1UL << CAN_F2R1_FB8_Pos)                      /*!< 0x00000100 */
#define CAN_F2R1_FB8           CAN_F2R1_FB8_Msk                                /*!<Filter bit 8 */
#define CAN_F2R1_FB9_Pos       (9U)
#define CAN_F2R1_FB9_Msk       (0x1UL << CAN_F2R1_FB9_Pos)                      /*!< 0x00000200 */
#define CAN_F2R1_FB9           CAN_F2R1_FB9_Msk                                /*!<Filter bit 9 */
#define CAN_F2R1_FB10_Pos      (10U)
#define CAN_F2R1_FB10_Msk      (0x1UL << CAN_F2R1_FB10_Pos)                     /*!< 0x00000400 */
#define CAN_F2R1_FB10          CAN_F2R1_FB10_Msk                               /*!<Filter bit 10 */
#define CAN_F2R1_FB11_Pos      (11U)
#define CAN_F2R1_FB11_Msk      (0x1UL << CAN_F2R1_FB11_Pos)                     /*!< 0x00000800 */
#define CAN_F2R1_FB11          CAN_F2R1_FB11_Msk                               /*!<Filter bit 11 */
#define CAN_F2R1_FB12_Pos      (12U)
#define CAN_F2R1_FB12_Msk      (0x1UL << CAN_F2R1_FB12_Pos)                     /*!< 0x00001000 */
#define CAN_F2R1_FB12          CAN_F2R1_FB12_Msk                               /*!<Filter bit 12 */
#define CAN_F2R1_FB13_Pos      (13U)
#define CAN_F2R1_FB13_Msk      (0x1UL << CAN_F2R1_FB13_Pos)                     /*!< 0x00002000 */
#define CAN_F2R1_FB13          CAN_F2R1_FB13_Msk                               /*!<Filter bit 13 */
#define CAN_F2R1_FB14_Pos      (14U)
#define CAN_F2R1_FB14_Msk      (0x1UL << CAN_F2R1_FB14_Pos)                     /*!< 0x00004000 */
#define CAN_F2R1_FB14          CAN_F2R1_FB14_Msk                               /*!<Filter bit 14 */
#define CAN_F2R1_FB15_Pos      (15U)
#define CAN_F2R1_FB15_Msk      (0x1UL << CAN_F2R1_FB15_Pos)                     /*!< 0x00008000 */
#define CAN_F2R1_FB15          CAN_F2R1_FB15_Msk                               /*!<Filter bit 15 */
#define CAN_F2R1_FB16_Pos      (16U)
#define CAN_F2R1_FB16_Msk      (0x1UL << CAN_F2R1_FB16_Pos)                     /*!< 0x00010000 */
#define CAN_F2R1_FB16          CAN_F2R1_FB16_Msk                               /*!<Filter bit 16 */
#define CAN_F2R1_FB17_Pos      (17U)
#define CAN_F2R1_FB17_Msk      (0x1UL << CAN_F2R1_FB17_Pos)                     /*!< 0x00020000 */
#define CAN_F2R1_FB17          CAN_F2R1_FB17_Msk                               /*!<Filter bit 17 */
#define CAN_F2R1_FB18_Pos      (18U)
#define CAN_F2R1_FB18_Msk      (0x1UL << CAN_F2R1_FB18_Pos)                     /*!< 0x00040000 */
#define CAN_F2R1_FB18          CAN_F2R1_FB18_Msk                               /*!<Filter bit 18 */
#define CAN_F2R1_FB19_Pos      (19U)
#define CAN_F2R1_FB19_Msk      (0x1UL << CAN_F2R1_FB19_Pos)                     /*!< 0x00080000 */
#define CAN_F2R1_FB19          CAN_F2R1_FB19_Msk                               /*!<Filter bit 19 */
#define CAN_F2R1_FB20_Pos      (20U)
#define CAN_F2R1_FB20_Msk      (0x1UL << CAN_F2R1_FB20_Pos)                     /*!< 0x00100000 */
#define CAN_F2R1_FB20          CAN_F2R1_FB20_Msk                               /*!<Filter bit 20 */
#define CAN_F2R1_FB21_Pos      (21U)
#define CAN_F2R1_FB21_Msk      (0x1UL << CAN_F2R1_FB21_Pos)                     /*!< 0x00200000 */
#define CAN_F2R1_FB21          CAN_F2R1_FB21_Msk                               /*!<Filter bit 21 */
#define CAN_F2R1_FB22_Pos      (22U)
#define CAN_F2R1_FB22_Msk      (0x1UL << CAN_F2R1_FB22_Pos)                     /*!< 0x00400000 */
#define CAN_F2R1_FB22          CAN_F2R1_FB22_Msk                               /*!<Filter bit 22 */
#define CAN_F2R1_FB23_Pos      (23U)
#define CAN_F2R1_FB23_Msk      (0x1UL << CAN_F2R1_FB23_Pos)                     /*!< 0x00800000 */
#define CAN_F2R1_FB23          CAN_F2R1_FB23_Msk                               /*!<Filter bit 23 */
#define CAN_F2R1_FB24_Pos      (24U)
#define CAN_F2R1_FB24_Msk      (0x1UL << CAN_F2R1_FB24_Pos)                     /*!< 0x01000000 */
#define CAN_F2R1_FB24          CAN_F2R1_FB24_Msk                               /*!<Filter bit 24 */
#define CAN_F2R1_FB25_Pos      (25U)
#define CAN_F2R1_FB25_Msk      (0x1UL << CAN_F2R1_FB25_Pos)                     /*!< 0x02000000 */
#define CAN_F2R1_FB25          CAN_F2R1_FB25_Msk                               /*!<Filter bit 25 */
#define CAN_F2R1_FB26_Pos      (26U)
#define CAN_F2R1_FB26_Msk      (0x1UL << CAN_F2R1_FB26_Pos)                     /*!< 0x04000000 */
#define CAN_F2R1_FB26          CAN_F2R1_FB26_Msk                               /*!<Filter bit 26 */
#define CAN_F2R1_FB27_Pos      (27U)
#define CAN_F2R1_FB27_Msk      (0x1UL << CAN_F2R1_FB27_Pos)                     /*!< 0x08000000 */
#define CAN_F2R1_FB27          CAN_F2R1_FB27_Msk                               /*!<Filter bit 27 */
#define CAN_F2R1_FB28_Pos      (28U)
#define CAN_F2R1_FB28_Msk      (0x1UL << CAN_F2R1_FB28_Pos)                     /*!< 0x10000000 */
#define CAN_F2R1_FB28          CAN_F2R1_FB28_Msk                               /*!<Filter bit 28 */
#define CAN_F2R1_FB29_Pos      (29U)
#define CAN_F2R1_FB29_Msk      (0x1UL << CAN_F2R1_FB29_Pos)                     /*!< 0x20000000 */
#define CAN_F2R1_FB29          CAN_F2R1_FB29_Msk                               /*!<Filter bit 29 */
#define CAN_F2R1_FB30_Pos      (30U)
#define CAN_F2R1_FB30_Msk      (0x1UL << CAN_F2R1_FB30_Pos)                     /*!< 0x40000000 */
#define CAN_F2R1_FB30          CAN_F2R1_FB30_Msk                               /*!<Filter bit 30 */
#define CAN_F2R1_FB31_Pos      (31U)
#define CAN_F2R1_FB31_Msk      (0x1UL << CAN_F2R1_FB31_Pos)                     /*!< 0x80000000 */
#define CAN_F2R1_FB31          CAN_F2R1_FB31_Msk                               /*!<Filter bit 31 */

/*******************  Bit definition for CAN_F3R1 register  *******************/
#define CAN_F3R1_FB0_Pos       (0U)
#define CAN_F3R1_FB0_Msk       (0x1UL << CAN_F3R1_FB0_Pos)                      /*!< 0x00000001 */
#define CAN_F3R1_FB0           CAN_F3R1_FB0_Msk                                /*!<Filter bit 0 */
#define CAN_F3R1_FB1_Pos       (1U)
#define CAN_F3R1_FB1_Msk       (0x1UL << CAN_F3R1_FB1_Pos)                      /*!< 0x00000002 */
#define CAN_F3R1_FB1           CAN_F3R1_FB1_Msk                                /*!<Filter bit 1 */
#define CAN_F3R1_FB2_Pos       (2U)
#define CAN_F3R1_FB2_Msk       (0x1UL << CAN_F3R1_FB2_Pos)                      /*!< 0x00000004 */
#define CAN_F3R1_FB2           CAN_F3R1_FB2_Msk                                /*!<Filter bit 2 */
#define CAN_F3R1_FB3_Pos       (3U)
#define CAN_F3R1_FB3_Msk       (0x1UL << CAN_F3R1_FB3_Pos)                      /*!< 0x00000008 */
#define CAN_F3R1_FB3           CAN_F3R1_FB3_Msk                                /*!<Filter bit 3 */
#define CAN_F3R1_FB4_Pos       (4U)
#define CAN_F3R1_FB4_Msk       (0x1UL << CAN_F3R1_FB4_Pos)                      /*!< 0x00000010 */
#define CAN_F3R1_FB4           CAN_F3R1_FB4_Msk                                /*!<Filter bit 4 */
#define CAN_F3R1_FB5_Pos       (5U)
#define CAN_F3R1_FB5_Msk       (0x1UL << CAN_F3R1_FB5_Pos)                      /*!< 0x00000020 */
#define CAN_F3R1_FB5           CAN_F3R1_FB5_Msk                                /*!<Filter bit 5 */
#define CAN_F3R1_FB6_Pos       (6U)
#define CAN_F3R1_FB6_Msk       (0x1UL << CAN_F3R1_FB6_Pos)                      /*!< 0x00000040 */
#define CAN_F3R1_FB6           CAN_F3R1_FB6_Msk                                /*!<Filter bit 6 */
#define CAN_F3R1_FB7_Pos       (7U)
#define CAN_F3R1_FB7_Msk       (0x1UL << CAN_F3R1_FB7_Pos)                      /*!< 0x00000080 */
#define CAN_F3R1_FB7           CAN_F3R1_FB7_Msk                                /*!<Filter bit 7 */
#define CAN_F3R1_FB8_Pos       (8U)
#define CAN_F3R1_FB8_Msk       (0x1UL << CAN_F3R1_FB8_Pos)                      /*!< 0x00000100 */
#define CAN_F3R1_FB8           CAN_F3R1_FB8_Msk                                /*!<Filter bit 8 */
#define CAN_F3R1_FB9_Pos       (9U)
#define CAN_F3R1_FB9_Msk       (0x1UL << CAN_F3R1_FB9_Pos)                      /*!< 0x00000200 */
#define CAN_F3R1_FB9           CAN_F3R1_FB9_Msk                                /*!<Filter bit 9 */
#define CAN_F3R1_FB10_Pos      (10U)
#define CAN_F3R1_FB10_Msk      (0x1UL << CAN_F3R1_FB10_Pos)                     /*!< 0x00000400 */
#define CAN_F3R1_FB10          CAN_F3R1_FB10_Msk                               /*!<Filter bit 10 */
#define CAN_F3R1_FB11_Pos      (11U)
#define CAN_F3R1_FB11_Msk      (0x1UL << CAN_F3R1_FB11_Pos)                     /*!< 0x00000800 */
#define CAN_F3R1_FB11          CAN_F3R1_FB11_Msk                               /*!<Filter bit 11 */
#define CAN_F3R1_FB12_Pos      (12U)
#define CAN_F3R1_FB12_Msk      (0x1UL << CAN_F3R1_FB12_Pos)                     /*!< 0x00001000 */
#define CAN_F3R1_FB12          CAN_F3R1_FB12_Msk                               /*!<Filter bit 12 */
#define CAN_F3R1_FB13_Pos      (13U)
#define CAN_F3R1_FB13_Msk      (0x1UL << CAN_F3R1_FB13_Pos)                     /*!< 0x00002000 */
#define CAN_F3R1_FB13          CAN_F3R1_FB13_Msk                               /*!<Filter bit 13 */
#define CAN_F3R1_FB14_Pos      (14U)
#define CAN_F3R1_FB14_Msk      (0x1UL << CAN_F3R1_FB14_Pos)                     /*!< 0x00004000 */
#define CAN_F3R1_FB14          CAN_F3R1_FB14_Msk                               /*!<Filter bit 14 */
#define CAN_F3R1_FB15_Pos      (15U)
#define CAN_F3R1_FB15_Msk      (0x1UL << CAN_F3R1_FB15_Pos)                     /*!< 0x00008000 */
#define CAN_F3R1_FB15          CAN_F3R1_FB15_Msk                               /*!<Filter bit 15 */
#define CAN_F3R1_FB16_Pos      (16U)
#define CAN_F3R1_FB16_Msk      (0x1UL << CAN_F3R1_FB16_Pos)                     /*!< 0x00010000 */
#define CAN_F3R1_FB16          CAN_F3R1_FB16_Msk                               /*!<Filter bit 16 */
#define CAN_F3R1_FB17_Pos      (17U)
#define CAN_F3R1_FB17_Msk      (0x1UL << CAN_F3R1_FB17_Pos)                     /*!< 0x00020000 */
#define CAN_F3R1_FB17          CAN_F3R1_FB17_Msk                               /*!<Filter bit 17 */
#define CAN_F3R1_FB18_Pos      (18U)
#define CAN_F3R1_FB18_Msk      (0x1UL << CAN_F3R1_FB18_Pos)                     /*!< 0x00040000 */
#define CAN_F3R1_FB18          CAN_F3R1_FB18_Msk                               /*!<Filter bit 18 */
#define CAN_F3R1_FB19_Pos      (19U)
#define CAN_F3R1_FB19_Msk      (0x1UL << CAN_F3R1_FB19_Pos)                     /*!< 0x00080000 */
#define CAN_F3R1_FB19          CAN_F3R1_FB19_Msk                               /*!<Filter bit 19 */
#define CAN_F3R1_FB20_Pos      (20U)
#define CAN_F3R1_FB20_Msk      (0x1UL << CAN_F3R1_FB20_Pos)                     /*!< 0x00100000 */
#define CAN_F3R1_FB20          CAN_F3R1_FB20_Msk                               /*!<Filter bit 20 */
#define CAN_F3R1_FB21_Pos      (21U)
#define CAN_F3R1_FB21_Msk      (0x1UL << CAN_F3R1_FB21_Pos)                     /*!< 0x00200000 */
#define CAN_F3R1_FB21          CAN_F3R1_FB21_Msk                               /*!<Filter bit 21 */
#define CAN_F3R1_FB22_Pos      (22U)
#define CAN_F3R1_FB22_Msk      (0x1UL << CAN_F3R1_FB22_Pos)                     /*!< 0x00400000 */
#define CAN_F3R1_FB22          CAN_F3R1_FB22_Msk                               /*!<Filter bit 22 */
#define CAN_F3R1_FB23_Pos      (23U)
#define CAN_F3R1_FB23_Msk      (0x1UL << CAN_F3R1_FB23_Pos)                     /*!< 0x00800000 */
#define CAN_F3R1_FB23          CAN_F3R1_FB23_Msk                               /*!<Filter bit 23 */
#define CAN_F3R1_FB24_Pos      (24U)
#define CAN_F3R1_FB24_Msk      (0x1UL << CAN_F3R1_FB24_Pos)                     /*!< 0x01000000 */
#define CAN_F3R1_FB24          CAN_F3R1_FB24_Msk                               /*!<Filter bit 24 */
#define CAN_F3R1_FB25_Pos      (25U)
#define CAN_F3R1_FB25_Msk      (0x1UL << CAN_F3R1_FB25_Pos)                     /*!< 0x02000000 */
#define CAN_F3R1_FB25          CAN_F3R1_FB25_Msk                               /*!<Filter bit 25 */
#define CAN_F3R1_FB26_Pos      (26U)
#define CAN_F3R1_FB26_Msk      (0x1UL << CAN_F3R1_FB26_Pos)                     /*!< 0x04000000 */
#define CAN_F3R1_FB26          CAN_F3R1_FB26_Msk                               /*!<Filter bit 26 */
#define CAN_F3R1_FB27_Pos      (27U)
#define CAN_F3R1_FB27_Msk      (0x1UL << CAN_F3R1_FB27_Pos)                     /*!< 0x08000000 */
#define CAN_F3R1_FB27          CAN_F3R1_FB27_Msk                               /*!<Filter bit 27 */
#define CAN_F3R1_FB28_Pos      (28U)
#define CAN_F3R1_FB28_Msk      (0x1UL << CAN_F3R1_FB28_Pos)                     /*!< 0x10000000 */
#define CAN_F3R1_FB28          CAN_F3R1_FB28_Msk                               /*!<Filter bit 28 */
#define CAN_F3R1_FB29_Pos      (29U)
#define CAN_F3R1_FB29_Msk      (0x1UL << CAN_F3R1_FB29_Pos)                     /*!< 0x20000000 */
#define CAN_F3R1_FB29          CAN_F3R1_FB29_Msk                               /*!<Filter bit 29 */
#define CAN_F3R1_FB30_Pos      (30U)
#define CAN_F3R1_FB30_Msk      (0x1UL << CAN_F3R1_FB30_Pos)                     /*!< 0x40000000 */
#define CAN_F3R1_FB30          CAN_F3R1_FB30_Msk                               /*!<Filter bit 30 */
#define CAN_F3R1_FB31_Pos      (31U)
#define CAN_F3R1_FB31_Msk      (0x1UL << CAN_F3R1_FB31_Pos)                     /*!< 0x80000000 */
#define CAN_F3R1_FB31          CAN_F3R1_FB31_Msk                               /*!<Filter bit 31 */

/*******************  Bit definition for CAN_F4R1 register  *******************/
#define CAN_F4R1_FB0_Pos       (0U)
#define CAN_F4R1_FB0_Msk       (0x1UL << CAN_F4R1_FB0_Pos)                      /*!< 0x00000001 */
#define CAN_F4R1_FB0           CAN_F4R1_FB0_Msk                                /*!<Filter bit 0 */
#define CAN_F4R1_FB1_Pos       (1U)
#define CAN_F4R1_FB1_Msk       (0x1UL << CAN_F4R1_FB1_Pos)                      /*!< 0x00000002 */
#define CAN_F4R1_FB1           CAN_F4R1_FB1_Msk                                /*!<Filter bit 1 */
#define CAN_F4R1_FB2_Pos       (2U)
#define CAN_F4R1_FB2_Msk       (0x1UL << CAN_F4R1_FB2_Pos)                      /*!< 0x00000004 */
#define CAN_F4R1_FB2           CAN_F4R1_FB2_Msk                                /*!<Filter bit 2 */
#define CAN_F4R1_FB3_Pos       (3U)
#define CAN_F4R1_FB3_Msk       (0x1UL << CAN_F4R1_FB3_Pos)                      /*!< 0x00000008 */
#define CAN_F4R1_FB3           CAN_F4R1_FB3_Msk                                /*!<Filter bit 3 */
#define CAN_F4R1_FB4_Pos       (4U)
#define CAN_F4R1_FB4_Msk       (0x1UL << CAN_F4R1_FB4_Pos)                      /*!< 0x00000010 */
#define CAN_F4R1_FB4           CAN_F4R1_FB4_Msk                                /*!<Filter bit 4 */
#define CAN_F4R1_FB5_Pos       (5U)
#define CAN_F4R1_FB5_Msk       (0x1UL << CAN_F4R1_FB5_Pos)                      /*!< 0x00000020 */
#define CAN_F4R1_FB5           CAN_F4R1_FB5_Msk                                /*!<Filter bit 5 */
#define CAN_F4R1_FB6_Pos       (6U)
#define CAN_F4R1_FB6_Msk       (0x1UL << CAN_F4R1_FB6_Pos)                      /*!< 0x00000040 */
#define CAN_F4R1_FB6           CAN_F4R1_FB6_Msk                                /*!<Filter bit 6 */
#define CAN_F4R1_FB7_Pos       (7U)
#define CAN_F4R1_FB7_Msk       (0x1UL << CAN_F4R1_FB7_Pos)                      /*!< 0x00000080 */
#define CAN_F4R1_FB7           CAN_F4R1_FB7_Msk                                /*!<Filter bit 7 */
#define CAN_F4R1_FB8_Pos       (8U)
#define CAN_F4R1_FB8_Msk       (0x1UL << CAN_F4R1_FB8_Pos)                      /*!< 0x00000100 */
#define CAN_F4R1_FB8           CAN_F4R1_FB8_Msk                                /*!<Filter bit 8 */
#define CAN_F4R1_FB9_Pos       (9U)
#define CAN_F4R1_FB9_Msk       (0x1UL << CAN_F4R1_FB9_Pos)                      /*!< 0x00000200 */
#define CAN_F4R1_FB9           CAN_F4R1_FB9_Msk                                /*!<Filter bit 9 */
#define CAN_F4R1_FB10_Pos      (10U)
#define CAN_F4R1_FB10_Msk      (0x1UL << CAN_F4R1_FB10_Pos)                     /*!< 0x00000400 */
#define CAN_F4R1_FB10          CAN_F4R1_FB10_Msk                               /*!<Filter bit 10 */
#define CAN_F4R1_FB11_Pos      (11U)
#define CAN_F4R1_FB11_Msk      (0x1UL << CAN_F4R1_FB11_Pos)                     /*!< 0x00000800 */
#define CAN_F4R1_FB11          CAN_F4R1_FB11_Msk                               /*!<Filter bit 11 */
#define CAN_F4R1_FB12_Pos      (12U)
#define CAN_F4R1_FB12_Msk      (0x1UL << CAN_F4R1_FB12_Pos)                     /*!< 0x00001000 */
#define CAN_F4R1_FB12          CAN_F4R1_FB12_Msk                               /*!<Filter bit 12 */
#define CAN_F4R1_FB13_Pos      (13U)
#define CAN_F4R1_FB13_Msk      (0x1UL << CAN_F4R1_FB13_Pos)                     /*!< 0x00002000 */
#define CAN_F4R1_FB13          CAN_F4R1_FB13_Msk                               /*!<Filter bit 13 */
#define CAN_F4R1_FB14_Pos      (14U)
#define CAN_F4R1_FB14_Msk      (0x1UL << CAN_F4R1_FB14_Pos)                     /*!< 0x00004000 */
#define CAN_F4R1_FB14          CAN_F4R1_FB14_Msk                               /*!<Filter bit 14 */
#define CAN_F4R1_FB15_Pos      (15U)
#define CAN_F4R1_FB15_Msk      (0x1UL << CAN_F4R1_FB15_Pos)                     /*!< 0x00008000 */
#define CAN_F4R1_FB15          CAN_F4R1_FB15_Msk                               /*!<Filter bit 15 */
#define CAN_F4R1_FB16_Pos      (16U)
#define CAN_F4R1_FB16_Msk      (0x1UL << CAN_F4R1_FB16_Pos)                     /*!< 0x00010000 */
#define CAN_F4R1_FB16          CAN_F4R1_FB16_Msk                               /*!<Filter bit 16 */
#define CAN_F4R1_FB17_Pos      (17U)
#define CAN_F4R1_FB17_Msk      (0x1UL << CAN_F4R1_FB17_Pos)                     /*!< 0x00020000 */
#define CAN_F4R1_FB17          CAN_F4R1_FB17_Msk                               /*!<Filter bit 17 */
#define CAN_F4R1_FB18_Pos      (18U)
#define CAN_F4R1_FB18_Msk      (0x1UL << CAN_F4R1_FB18_Pos)                     /*!< 0x00040000 */
#define CAN_F4R1_FB18          CAN_F4R1_FB18_Msk                               /*!<Filter bit 18 */
#define CAN_F4R1_FB19_Pos      (19U)
#define CAN_F4R1_FB19_Msk      (0x1UL << CAN_F4R1_FB19_Pos)                     /*!< 0x00080000 */
#define CAN_F4R1_FB19          CAN_F4R1_FB19_Msk                               /*!<Filter bit 19 */
#define CAN_F4R1_FB20_Pos      (20U)
#define CAN_F4R1_FB20_Msk      (0x1UL << CAN_F4R1_FB20_Pos)                     /*!< 0x00100000 */
#define CAN_F4R1_FB20          CAN_F4R1_FB20_Msk                               /*!<Filter bit 20 */
#define CAN_F4R1_FB21_Pos      (21U)
#define CAN_F4R1_FB21_Msk      (0x1UL << CAN_F4R1_FB21_Pos)                     /*!< 0x00200000 */
#define CAN_F4R1_FB21          CAN_F4R1_FB21_Msk                               /*!<Filter bit 21 */
#define CAN_F4R1_FB22_Pos      (22U)
#define CAN_F4R1_FB22_Msk      (0x1UL << CAN_F4R1_FB22_Pos)                     /*!< 0x00400000 */
#define CAN_F4R1_FB22          CAN_F4R1_FB22_Msk                               /*!<Filter bit 22 */
#define CAN_F4R1_FB23_Pos      (23U)
#define CAN_F4R1_FB23_Msk      (0x1UL << CAN_F4R1_FB23_Pos)                     /*!< 0x00800000 */
#define CAN_F4R1_FB23          CAN_F4R1_FB23_Msk                               /*!<Filter bit 23 */
#define CAN_F4R1_FB24_Pos      (24U)
#define CAN_F4R1_FB24_Msk      (0x1UL << CAN_F4R1_FB24_Pos)                     /*!< 0x01000000 */
#define CAN_F4R1_FB24          CAN_F4R1_FB24_Msk                               /*!<Filter bit 24 */
#define CAN_F4R1_FB25_Pos      (25U)
#define CAN_F4R1_FB25_Msk      (0x1UL << CAN_F4R1_FB25_Pos)                     /*!< 0x02000000 */
#define CAN_F4R1_FB25          CAN_F4R1_FB25_Msk                               /*!<Filter bit 25 */
#define CAN_F4R1_FB26_Pos      (26U)
#define CAN_F4R1_FB26_Msk      (0x1UL << CAN_F4R1_FB26_Pos)                     /*!< 0x04000000 */
#define CAN_F4R1_FB26          CAN_F4R1_FB26_Msk                               /*!<Filter bit 26 */
#define CAN_F4R1_FB27_Pos      (27U)
#define CAN_F4R1_FB27_Msk      (0x1UL << CAN_F4R1_FB27_Pos)                     /*!< 0x08000000 */
#define CAN_F4R1_FB27          CAN_F4R1_FB27_Msk                               /*!<Filter bit 27 */
#define CAN_F4R1_FB28_Pos      (28U)
#define CAN_F4R1_FB28_Msk      (0x1UL << CAN_F4R1_FB28_Pos)                     /*!< 0x10000000 */
#define CAN_F4R1_FB28          CAN_F4R1_FB28_Msk                               /*!<Filter bit 28 */
#define CAN_F4R1_FB29_Pos      (29U)
#define CAN_F4R1_FB29_Msk      (0x1UL << CAN_F4R1_FB29_Pos)                     /*!< 0x20000000 */
#define CAN_F4R1_FB29          CAN_F4R1_FB29_Msk                               /*!<Filter bit 29 */
#define CAN_F4R1_FB30_Pos      (30U)
#define CAN_F4R1_FB30_Msk      (0x1UL << CAN_F4R1_FB30_Pos)                     /*!< 0x40000000 */
#define CAN_F4R1_FB30          CAN_F4R1_FB30_Msk                               /*!<Filter bit 30 */
#define CAN_F4R1_FB31_Pos      (31U)
#define CAN_F4R1_FB31_Msk      (0x1UL << CAN_F4R1_FB31_Pos)                     /*!< 0x80000000 */
#define CAN_F4R1_FB31          CAN_F4R1_FB31_Msk                               /*!<Filter bit 31 */

/*******************  Bit definition for CAN_F5R1 register  *******************/
#define CAN_F5R1_FB0_Pos       (0U)
#define CAN_F5R1_FB0_Msk       (0x1UL << CAN_F5R1_FB0_Pos)                      /*!< 0x00000001 */
#define CAN_F5R1_FB0           CAN_F5R1_FB0_Msk                                /*!<Filter bit 0 */
#define CAN_F5R1_FB1_Pos       (1U)
#define CAN_F5R1_FB1_Msk       (0x1UL << CAN_F5R1_FB1_Pos)                      /*!< 0x00000002 */
#define CAN_F5R1_FB1           CAN_F5R1_FB1_Msk                                /*!<Filter bit 1 */
#define CAN_F5R1_FB2_Pos       (2U)
#define CAN_F5R1_FB2_Msk       (0x1UL << CAN_F5R1_FB2_Pos)                      /*!< 0x00000004 */
#define CAN_F5R1_FB2           CAN_F5R1_FB2_Msk                                /*!<Filter bit 2 */
#define CAN_F5R1_FB3_Pos       (3U)
#define CAN_F5R1_FB3_Msk       (0x1UL << CAN_F5R1_FB3_Pos)                      /*!< 0x00000008 */
#define CAN_F5R1_FB3           CAN_F5R1_FB3_Msk                                /*!<Filter bit 3 */
#define CAN_F5R1_FB4_Pos       (4U)
#define CAN_F5R1_FB4_Msk       (0x1UL << CAN_F5R1_FB4_Pos)                      /*!< 0x00000010 */
#define CAN_F5R1_FB4           CAN_F5R1_FB4_Msk                                /*!<Filter bit 4 */
#define CAN_F5R1_FB5_Pos       (5U)
#define CAN_F5R1_FB5_Msk       (0x1UL << CAN_F5R1_FB5_Pos)                      /*!< 0x00000020 */
#define CAN_F5R1_FB5           CAN_F5R1_FB5_Msk                                /*!<Filter bit 5 */
#define CAN_F5R1_FB6_Pos       (6U)
#define CAN_F5R1_FB6_Msk       (0x1UL << CAN_F5R1_FB6_Pos)                      /*!< 0x00000040 */
#define CAN_F5R1_FB6           CAN_F5R1_FB6_Msk                                /*!<Filter bit 6 */
#define CAN_F5R1_FB7_Pos       (7U)
#define CAN_F5R1_FB7_Msk       (0x1UL << CAN_F5R1_FB7_Pos)                      /*!< 0x00000080 */
#define CAN_F5R1_FB7           CAN_F5R1_FB7_Msk                                /*!<Filter bit 7 */
#define CAN_F5R1_FB8_Pos       (8U)
#define CAN_F5R1_FB8_Msk       (0x1UL << CAN_F5R1_FB8_Pos)                      /*!< 0x00000100 */
#define CAN_F5R1_FB8           CAN_F5R1_FB8_Msk                                /*!<Filter bit 8 */
#define CAN_F5R1_FB9_Pos       (9U)
#define CAN_F5R1_FB9_Msk       (0x1UL << CAN_F5R1_FB9_Pos)                      /*!< 0x00000200 */
#define CAN_F5R1_FB9           CAN_F5R1_FB9_Msk                                /*!<Filter bit 9 */
#define CAN_F5R1_FB10_Pos      (10U)
#define CAN_F5R1_FB10_Msk      (0x1UL << CAN_F5R1_FB10_Pos)                     /*!< 0x00000400 */
#define CAN_F5R1_FB10          CAN_F5R1_FB10_Msk                               /*!<Filter bit 10 */
#define CAN_F5R1_FB11_Pos      (11U)
#define CAN_F5R1_FB11_Msk      (0x1UL << CAN_F5R1_FB11_Pos)                     /*!< 0x00000800 */
#define CAN_F5R1_FB11          CAN_F5R1_FB11_Msk                               /*!<Filter bit 11 */
#define CAN_F5R1_FB12_Pos      (12U)
#define CAN_F5R1_FB12_Msk      (0x1UL << CAN_F5R1_FB12_Pos)                     /*!< 0x00001000 */
#define CAN_F5R1_FB12          CAN_F5R1_FB12_Msk                               /*!<Filter bit 12 */
#define CAN_F5R1_FB13_Pos      (13U)
#define CAN_F5R1_FB13_Msk      (0x1UL << CAN_F5R1_FB13_Pos)                     /*!< 0x00002000 */
#define CAN_F5R1_FB13          CAN_F5R1_FB13_Msk                               /*!<Filter bit 13 */
#define CAN_F5R1_FB14_Pos      (14U)
#define CAN_F5R1_FB14_Msk      (0x1UL << CAN_F5R1_FB14_Pos)                     /*!< 0x00004000 */
#define CAN_F5R1_FB14          CAN_F5R1_FB14_Msk                               /*!<Filter bit 14 */
#define CAN_F5R1_FB15_Pos      (15U)
#define CAN_F5R1_FB15_Msk      (0x1UL << CAN_F5R1_FB15_Pos)                     /*!< 0x00008000 */
#define CAN_F5R1_FB15          CAN_F5R1_FB15_Msk                               /*!<Filter bit 15 */
#define CAN_F5R1_FB16_Pos      (16U)
#define CAN_F5R1_FB16_Msk      (0x1UL << CAN_F5R1_FB16_Pos)                     /*!< 0x00010000 */
#define CAN_F5R1_FB16          CAN_F5R1_FB16_Msk                               /*!<Filter bit 16 */
#define CAN_F5R1_FB17_Pos      (17U)
#define CAN_F5R1_FB17_Msk      (0x1UL << CAN_F5R1_FB17_Pos)                     /*!< 0x00020000 */
#define CAN_F5R1_FB17          CAN_F5R1_FB17_Msk                               /*!<Filter bit 17 */
#define CAN_F5R1_FB18_Pos      (18U)
#define CAN_F5R1_FB18_Msk      (0x1UL << CAN_F5R1_FB18_Pos)                     /*!< 0x00040000 */
#define CAN_F5R1_FB18          CAN_F5R1_FB18_Msk                               /*!<Filter bit 18 */
#define CAN_F5R1_FB19_Pos      (19U)
#define CAN_F5R1_FB19_Msk      (0x1UL << CAN_F5R1_FB19_Pos)                     /*!< 0x00080000 */
#define CAN_F5R1_FB19          CAN_F5R1_FB19_Msk                               /*!<Filter bit 19 */
#define CAN_F5R1_FB20_Pos      (20U)
#define CAN_F5R1_FB20_Msk      (0x1UL << CAN_F5R1_FB20_Pos)                     /*!< 0x00100000 */
#define CAN_F5R1_FB20          CAN_F5R1_FB20_Msk                               /*!<Filter bit 20 */
#define CAN_F5R1_FB21_Pos      (21U)
#define CAN_F5R1_FB21_Msk      (0x1UL << CAN_F5R1_FB21_Pos)                     /*!< 0x00200000 */
#define CAN_F5R1_FB21          CAN_F5R1_FB21_Msk                               /*!<Filter bit 21 */
#define CAN_F5R1_FB22_Pos      (22U)
#define CAN_F5R1_FB22_Msk      (0x1UL << CAN_F5R1_FB22_Pos)                     /*!< 0x00400000 */
#define CAN_F5R1_FB22          CAN_F5R1_FB22_Msk                               /*!<Filter bit 22 */
#define CAN_F5R1_FB23_Pos      (23U)
#define CAN_F5R1_FB23_Msk      (0x1UL << CAN_F5R1_FB23_Pos)                     /*!< 0x00800000 */
#define CAN_F5R1_FB23          CAN_F5R1_FB23_Msk                               /*!<Filter bit 23 */
#define CAN_F5R1_FB24_Pos      (24U)
#define CAN_F5R1_FB24_Msk      (0x1UL << CAN_F5R1_FB24_Pos)                     /*!< 0x01000000 */
#define CAN_F5R1_FB24          CAN_F5R1_FB24_Msk                               /*!<Filter bit 24 */
#define CAN_F5R1_FB25_Pos      (25U)
#define CAN_F5R1_FB25_Msk      (0x1UL << CAN_F5R1_FB25_Pos)                     /*!< 0x02000000 */
#define CAN_F5R1_FB25          CAN_F5R1_FB25_Msk                               /*!<Filter bit 25 */
#define CAN_F5R1_FB26_Pos      (26U)
#define CAN_F5R1_FB26_Msk      (0x1UL << CAN_F5R1_FB26_Pos)                     /*!< 0x04000000 */
#define CAN_F5R1_FB26          CAN_F5R1_FB26_Msk                               /*!<Filter bit 26 */
#define CAN_F5R1_FB27_Pos      (27U)
#define CAN_F5R1_FB27_Msk      (0x1UL << CAN_F5R1_FB27_Pos)                     /*!< 0x08000000 */
#define CAN_F5R1_FB27          CAN_F5R1_FB27_Msk                               /*!<Filter bit 27 */
#define CAN_F5R1_FB28_Pos      (28U)
#define CAN_F5R1_FB28_Msk      (0x1UL << CAN_F5R1_FB28_Pos)                     /*!< 0x10000000 */
#define CAN_F5R1_FB28          CAN_F5R1_FB28_Msk                               /*!<Filter bit 28 */
#define CAN_F5R1_FB29_Pos      (29U)
#define CAN_F5R1_FB29_Msk      (0x1UL << CAN_F5R1_FB29_Pos)                     /*!< 0x20000000 */
#define CAN_F5R1_FB29          CAN_F5R1_FB29_Msk                               /*!<Filter bit 29 */
#define CAN_F5R1_FB30_Pos      (30U)
#define CAN_F5R1_FB30_Msk      (0x1UL << CAN_F5R1_FB30_Pos)                     /*!< 0x40000000 */
#define CAN_F5R1_FB30          CAN_F5R1_FB30_Msk                               /*!<Filter bit 30 */
#define CAN_F5R1_FB31_Pos      (31U)
#define CAN_F5R1_FB31_Msk      (0x1UL << CAN_F5R1_FB31_Pos)                     /*!< 0x80000000 */
#define CAN_F5R1_FB31          CAN_F5R1_FB31_Msk                               /*!<Filter bit 31 */

/*******************  Bit definition for CAN_F6R1 register  *******************/
#define CAN_F6R1_FB0_Pos       (0U)
#define CAN_F6R1_FB0_Msk       (0x1UL << CAN_F6R1_FB0_Pos)                      /*!< 0x00000001 */
#define CAN_F6R1_FB0           CAN_F6R1_FB0_Msk                                /*!<Filter bit 0 */
#define CAN_F6R1_FB1_Pos       (1U)
#define CAN_F6R1_FB1_Msk       (0x1UL << CAN_F6R1_FB1_Pos)                      /*!< 0x00000002 */
#define CAN_F6R1_FB1           CAN_F6R1_FB1_Msk                                /*!<Filter bit 1 */
#define CAN_F6R1_FB2_Pos       (2U)
#define CAN_F6R1_FB2_Msk       (0x1UL << CAN_F6R1_FB2_Pos)                      /*!< 0x00000004 */
#define CAN_F6R1_FB2           CAN_F6R1_FB2_Msk                                /*!<Filter bit 2 */
#define CAN_F6R1_FB3_Pos       (3U)
#define CAN_F6R1_FB3_Msk       (0x1UL << CAN_F6R1_FB3_Pos)                      /*!< 0x00000008 */
#define CAN_F6R1_FB3           CAN_F6R1_FB3_Msk                                /*!<Filter bit 3 */
#define CAN_F6R1_FB4_Pos       (4U)
#define CAN_F6R1_FB4_Msk       (0x1UL << CAN_F6R1_FB4_Pos)                      /*!< 0x00000010 */
#define CAN_F6R1_FB4           CAN_F6R1_FB4_Msk                                /*!<Filter bit 4 */
#define CAN_F6R1_FB5_Pos       (5U)
#define CAN_F6R1_FB5_Msk       (0x1UL << CAN_F6R1_FB5_Pos)                      /*!< 0x00000020 */
#define CAN_F6R1_FB5           CAN_F6R1_FB5_Msk                                /*!<Filter bit 5 */
#define CAN_F6R1_FB6_Pos       (6U)
#define CAN_F6R1_FB6_Msk       (0x1UL << CAN_F6R1_FB6_Pos)                      /*!< 0x00000040 */
#define CAN_F6R1_FB6           CAN_F6R1_FB6_Msk                                /*!<Filter bit 6 */
#define CAN_F6R1_FB7_Pos       (7U)
#define CAN_F6R1_FB7_Msk       (0x1UL << CAN_F6R1_FB7_Pos)                      /*!< 0x00000080 */
#define CAN_F6R1_FB7           CAN_F6R1_FB7_Msk                                /*!<Filter bit 7 */
#define CAN_F6R1_FB8_Pos       (8U)
#define CAN_F6R1_FB8_Msk       (0x1UL << CAN_F6R1_FB8_Pos)                      /*!< 0x00000100 */
#define CAN_F6R1_FB8           CAN_F6R1_FB8_Msk                                /*!<Filter bit 8 */
#define CAN_F6R1_FB9_Pos       (9U)
#define CAN_F6R1_FB9_Msk       (0x1UL << CAN_F6R1_FB9_Pos)                      /*!< 0x00000200 */
#define CAN_F6R1_FB9           CAN_F6R1_FB9_Msk                                /*!<Filter bit 9 */
#define CAN_F6R1_FB10_Pos      (10U)
#define CAN_F6R1_FB10_Msk      (0x1UL << CAN_F6R1_FB10_Pos)                     /*!< 0x00000400 */
#define CAN_F6R1_FB10          CAN_F6R1_FB10_Msk                               /*!<Filter bit 10 */
#define CAN_F6R1_FB11_Pos      (11U)
#define CAN_F6R1_FB11_Msk      (0x1UL << CAN_F6R1_FB11_Pos)                     /*!< 0x00000800 */
#define CAN_F6R1_FB11          CAN_F6R1_FB11_Msk                               /*!<Filter bit 11 */
#define CAN_F6R1_FB12_Pos      (12U)
#define CAN_F6R1_FB12_Msk      (0x1UL << CAN_F6R1_FB12_Pos)                     /*!< 0x00001000 */
#define CAN_F6R1_FB12          CAN_F6R1_FB12_Msk                               /*!<Filter bit 12 */
#define CAN_F6R1_FB13_Pos      (13U)
#define CAN_F6R1_FB13_Msk      (0x1UL << CAN_F6R1_FB13_Pos)                     /*!< 0x00002000 */
#define CAN_F6R1_FB13          CAN_F6R1_FB13_Msk                               /*!<Filter bit 13 */
#define CAN_F6R1_FB14_Pos      (14U)
#define CAN_F6R1_FB14_Msk      (0x1UL << CAN_F6R1_FB14_Pos)                     /*!< 0x00004000 */
#define CAN_F6R1_FB14          CAN_F6R1_FB14_Msk                               /*!<Filter bit 14 */
#define CAN_F6R1_FB15_Pos      (15U)
#define CAN_F6R1_FB15_Msk      (0x1UL << CAN_F6R1_FB15_Pos)                     /*!< 0x00008000 */
#define CAN_F6R1_FB15          CAN_F6R1_FB15_Msk                               /*!<Filter bit 15 */
#define CAN_F6R1_FB16_Pos      (16U)
#define CAN_F6R1_FB16_Msk      (0x1UL << CAN_F6R1_FB16_Pos)                     /*!< 0x00010000 */
#define CAN_F6R1_FB16          CAN_F6R1_FB16_Msk                               /*!<Filter bit 16 */
#define CAN_F6R1_FB17_Pos      (17U)
#define CAN_F6R1_FB17_Msk      (0x1UL << CAN_F6R1_FB17_Pos)                     /*!< 0x00020000 */
#define CAN_F6R1_FB17          CAN_F6R1_FB17_Msk                               /*!<Filter bit 17 */
#define CAN_F6R1_FB18_Pos      (18U)
#define CAN_F6R1_FB18_Msk      (0x1UL << CAN_F6R1_FB18_Pos)                     /*!< 0x00040000 */
#define CAN_F6R1_FB18          CAN_F6R1_FB18_Msk                               /*!<Filter bit 18 */
#define CAN_F6R1_FB19_Pos      (19U)
#define CAN_F6R1_FB19_Msk      (0x1UL << CAN_F6R1_FB19_Pos)                     /*!< 0x00080000 */
#define CAN_F6R1_FB19          CAN_F6R1_FB19_Msk                               /*!<Filter bit 19 */
#define CAN_F6R1_FB20_Pos      (20U)
#define CAN_F6R1_FB20_Msk      (0x1UL << CAN_F6R1_FB20_Pos)                     /*!< 0x00100000 */
#define CAN_F6R1_FB20          CAN_F6R1_FB20_Msk                               /*!<Filter bit 20 */
#define CAN_F6R1_FB21_Pos      (21U)
#define CAN_F6R1_FB21_Msk      (0x1UL << CAN_F6R1_FB21_Pos)                     /*!< 0x00200000 */
#define CAN_F6R1_FB21          CAN_F6R1_FB21_Msk                               /*!<Filter bit 21 */
#define CAN_F6R1_FB22_Pos      (22U)
#define CAN_F6R1_FB22_Msk      (0x1UL << CAN_F6R1_FB22_Pos)                     /*!< 0x00400000 */
#define CAN_F6R1_FB22          CAN_F6R1_FB22_Msk                               /*!<Filter bit 22 */
#define CAN_F6R1_FB23_Pos      (23U)
#define CAN_F6R1_FB23_Msk      (0x1UL << CAN_F6R1_FB23_Pos)                     /*!< 0x00800000 */
#define CAN_F6R1_FB23          CAN_F6R1_FB23_Msk                               /*!<Filter bit 23 */
#define CAN_F6R1_FB24_Pos      (24U)
#define CAN_F6R1_FB24_Msk      (0x1UL << CAN_F6R1_FB24_Pos)                     /*!< 0x01000000 */
#define CAN_F6R1_FB24          CAN_F6R1_FB24_Msk                               /*!<Filter bit 24 */
#define CAN_F6R1_FB25_Pos      (25U)
#define CAN_F6R1_FB25_Msk      (0x1UL << CAN_F6R1_FB25_Pos)                     /*!< 0x02000000 */
#define CAN_F6R1_FB25          CAN_F6R1_FB25_Msk                               /*!<Filter bit 25 */
#define CAN_F6R1_FB26_Pos      (26U)
#define CAN_F6R1_FB26_Msk      (0x1UL << CAN_F6R1_FB26_Pos)                     /*!< 0x04000000 */
#define CAN_F6R1_FB26          CAN_F6R1_FB26_Msk                               /*!<Filter bit 26 */
#define CAN_F6R1_FB27_Pos      (27U)
#define CAN_F6R1_FB27_Msk      (0x1UL << CAN_F6R1_FB27_Pos)                     /*!< 0x08000000 */
#define CAN_F6R1_FB27          CAN_F6R1_FB27_Msk                               /*!<Filter bit 27 */
#define CAN_F6R1_FB28_Pos      (28U)
#define CAN_F6R1_FB28_Msk      (0x1UL << CAN_F6R1_FB28_Pos)                     /*!< 0x10000000 */
#define CAN_F6R1_FB28          CAN_F6R1_FB28_Msk                               /*!<Filter bit 28 */
#define CAN_F6R1_FB29_Pos      (29U)
#define CAN_F6R1_FB29_Msk      (0x1UL << CAN_F6R1_FB29_Pos)                     /*!< 0x20000000 */
#define CAN_F6R1_FB29          CAN_F6R1_FB29_Msk                               /*!<Filter bit 29 */
#define CAN_F6R1_FB30_Pos      (30U)
#define CAN_F6R1_FB30_Msk      (0x1UL << CAN_F6R1_FB30_Pos)                     /*!< 0x40000000 */
#define CAN_F6R1_FB30          CAN_F6R1_FB30_Msk                               /*!<Filter bit 30 */
#define CAN_F6R1_FB31_Pos      (31U)
#define CAN_F6R1_FB31_Msk      (0x1UL << CAN_F6R1_FB31_Pos)                     /*!< 0x80000000 */
#define CAN_F6R1_FB31          CAN_F6R1_FB31_Msk                               /*!<Filter bit 31 */

/*******************  Bit definition for CAN_F7R1 register  *******************/
#define CAN_F7R1_FB0_Pos       (0U)
#define CAN_F7R1_FB0_Msk       (0x1UL << CAN_F7R1_FB0_Pos)                      /*!< 0x00000001 */
#define CAN_F7R1_FB0           CAN_F7R1_FB0_Msk                                /*!<Filter bit 0 */
#define CAN_F7R1_FB1_Pos       (1U)
#define CAN_F7R1_FB1_Msk       (0x1UL << CAN_F7R1_FB1_Pos)                      /*!< 0x00000002 */
#define CAN_F7R1_FB1           CAN_F7R1_FB1_Msk                                /*!<Filter bit 1 */
#define CAN_F7R1_FB2_Pos       (2U)
#define CAN_F7R1_FB2_Msk       (0x1UL << CAN_F7R1_FB2_Pos)                      /*!< 0x00000004 */
#define CAN_F7R1_FB2           CAN_F7R1_FB2_Msk                                /*!<Filter bit 2 */
#define CAN_F7R1_FB3_Pos       (3U)
#define CAN_F7R1_FB3_Msk       (0x1UL << CAN_F7R1_FB3_Pos)                      /*!< 0x00000008 */
#define CAN_F7R1_FB3           CAN_F7R1_FB3_Msk                                /*!<Filter bit 3 */
#define CAN_F7R1_FB4_Pos       (4U)
#define CAN_F7R1_FB4_Msk       (0x1UL << CAN_F7R1_FB4_Pos)                      /*!< 0x00000010 */
#define CAN_F7R1_FB4           CAN_F7R1_FB4_Msk                                /*!<Filter bit 4 */
#define CAN_F7R1_FB5_Pos       (5U)
#define CAN_F7R1_FB5_Msk       (0x1UL << CAN_F7R1_FB5_Pos)                      /*!< 0x00000020 */
#define CAN_F7R1_FB5           CAN_F7R1_FB5_Msk                                /*!<Filter bit 5 */
#define CAN_F7R1_FB6_Pos       (6U)
#define CAN_F7R1_FB6_Msk       (0x1UL << CAN_F7R1_FB6_Pos)                      /*!< 0x00000040 */
#define CAN_F7R1_FB6           CAN_F7R1_FB6_Msk                                /*!<Filter bit 6 */
#define CAN_F7R1_FB7_Pos       (7U)
#define CAN_F7R1_FB7_Msk       (0x1UL << CAN_F7R1_FB7_Pos)                      /*!< 0x00000080 */
#define CAN_F7R1_FB7           CAN_F7R1_FB7_Msk                                /*!<Filter bit 7 */
#define CAN_F7R1_FB8_Pos       (8U)
#define CAN_F7R1_FB8_Msk       (0x1UL << CAN_F7R1_FB8_Pos)                      /*!< 0x00000100 */
#define CAN_F7R1_FB8           CAN_F7R1_FB8_Msk                                /*!<Filter bit 8 */
#define CAN_F7R1_FB9_Pos       (9U)
#define CAN_F7R1_FB9_Msk       (0x1UL << CAN_F7R1_FB9_Pos)                      /*!< 0x00000200 */
#define CAN_F7R1_FB9           CAN_F7R1_FB9_Msk                                /*!<Filter bit 9 */
#define CAN_F7R1_FB10_Pos      (10U)
#define CAN_F7R1_FB10_Msk      (0x1UL << CAN_F7R1_FB10_Pos)                     /*!< 0x00000400 */
#define CAN_F7R1_FB10          CAN_F7R1_FB10_Msk                               /*!<Filter bit 10 */
#define CAN_F7R1_FB11_Pos      (11U)
#define CAN_F7R1_FB11_Msk      (0x1UL << CAN_F7R1_FB11_Pos)                     /*!< 0x00000800 */
#define CAN_F7R1_FB11          CAN_F7R1_FB11_Msk                               /*!<Filter bit 11 */
#define CAN_F7R1_FB12_Pos      (12U)
#define CAN_F7R1_FB12_Msk      (0x1UL << CAN_F7R1_FB12_Pos)                     /*!< 0x00001000 */
#define CAN_F7R1_FB12          CAN_F7R1_FB12_Msk                               /*!<Filter bit 12 */
#define CAN_F7R1_FB13_Pos      (13U)
#define CAN_F7R1_FB13_Msk      (0x1UL << CAN_F7R1_FB13_Pos)                     /*!< 0x00002000 */
#define CAN_F7R1_FB13          CAN_F7R1_FB13_Msk                               /*!<Filter bit 13 */
#define CAN_F7R1_FB14_Pos      (14U)
#define CAN_F7R1_FB14_Msk      (0x1UL << CAN_F7R1_FB14_Pos)                     /*!< 0x00004000 */
#define CAN_F7R1_FB14          CAN_F7R1_FB14_Msk                               /*!<Filter bit 14 */
#define CAN_F7R1_FB15_Pos      (15U)
#define CAN_F7R1_FB15_Msk      (0x1UL << CAN_F7R1_FB15_Pos)                     /*!< 0x00008000 */
#define CAN_F7R1_FB15          CAN_F7R1_FB15_Msk                               /*!<Filter bit 15 */
#define CAN_F7R1_FB16_Pos      (16U)
#define CAN_F7R1_FB16_Msk      (0x1UL << CAN_F7R1_FB16_Pos)                     /*!< 0x00010000 */
#define CAN_F7R1_FB16          CAN_F7R1_FB16_Msk                               /*!<Filter bit 16 */
#define CAN_F7R1_FB17_Pos      (17U)
#define CAN_F7R1_FB17_Msk      (0x1UL << CAN_F7R1_FB17_Pos)                     /*!< 0x00020000 */
#define CAN_F7R1_FB17          CAN_F7R1_FB17_Msk                               /*!<Filter bit 17 */
#define CAN_F7R1_FB18_Pos      (18U)
#define CAN_F7R1_FB18_Msk      (0x1UL << CAN_F7R1_FB18_Pos)                     /*!< 0x00040000 */
#define CAN_F7R1_FB18          CAN_F7R1_FB18_Msk                               /*!<Filter bit 18 */
#define CAN_F7R1_FB19_Pos      (19U)
#define CAN_F7R1_FB19_Msk      (0x1UL << CAN_F7R1_FB19_Pos)                     /*!< 0x00080000 */
#define CAN_F7R1_FB19          CAN_F7R1_FB19_Msk                               /*!<Filter bit 19 */
#define CAN_F7R1_FB20_Pos      (20U)
#define CAN_F7R1_FB20_Msk      (0x1UL << CAN_F7R1_FB20_Pos)                     /*!< 0x00100000 */
#define CAN_F7R1_FB20          CAN_F7R1_FB20_Msk                               /*!<Filter bit 20 */
#define CAN_F7R1_FB21_Pos      (21U)
#define CAN_F7R1_FB21_Msk      (0x1UL << CAN_F7R1_FB21_Pos)                     /*!< 0x00200000 */
#define CAN_F7R1_FB21          CAN_F7R1_FB21_Msk                               /*!<Filter bit 21 */
#define CAN_F7R1_FB22_Pos      (22U)
#define CAN_F7R1_FB22_Msk      (0x1UL << CAN_F7R1_FB22_Pos)                     /*!< 0x00400000 */
#define CAN_F7R1_FB22          CAN_F7R1_FB22_Msk                               /*!<Filter bit 22 */
#define CAN_F7R1_FB23_Pos      (23U)
#define CAN_F7R1_FB23_Msk      (0x1UL << CAN_F7R1_FB23_Pos)                     /*!< 0x00800000 */
#define CAN_F7R1_FB23          CAN_F7R1_FB23_Msk                               /*!<Filter bit 23 */
#define CAN_F7R1_FB24_Pos      (24U)
#define CAN_F7R1_FB24_Msk      (0x1UL << CAN_F7R1_FB24_Pos)                     /*!< 0x01000000 */
#define CAN_F7R1_FB24          CAN_F7R1_FB24_Msk                               /*!<Filter bit 24 */
#define CAN_F7R1_FB25_Pos      (25U)
#define CAN_F7R1_FB25_Msk      (0x1UL << CAN_F7R1_FB25_Pos)                     /*!< 0x02000000 */
#define CAN_F7R1_FB25          CAN_F7R1_FB25_Msk                               /*!<Filter bit 25 */
#define CAN_F7R1_FB26_Pos      (26U)
#define CAN_F7R1_FB26_Msk      (0x1UL << CAN_F7R1_FB26_Pos)                     /*!< 0x04000000 */
#define CAN_F7R1_FB26          CAN_F7R1_FB26_Msk                               /*!<Filter bit 26 */
#define CAN_F7R1_FB27_Pos      (27U)
#define CAN_F7R1_FB27_Msk      (0x1UL << CAN_F7R1_FB27_Pos)                     /*!< 0x08000000 */
#define CAN_F7R1_FB27          CAN_F7R1_FB27_Msk                               /*!<Filter bit 27 */
#define CAN_F7R1_FB28_Pos      (28U)
#define CAN_F7R1_FB28_Msk      (0x1UL << CAN_F7R1_FB28_Pos)                     /*!< 0x10000000 */
#define CAN_F7R1_FB28          CAN_F7R1_FB28_Msk                               /*!<Filter bit 28 */
#define CAN_F7R1_FB29_Pos      (29U)
#define CAN_F7R1_FB29_Msk      (0x1UL << CAN_F7R1_FB29_Pos)                     /*!< 0x20000000 */
#define CAN_F7R1_FB29          CAN_F7R1_FB29_Msk                               /*!<Filter bit 29 */
#define CAN_F7R1_FB30_Pos      (30U)
#define CAN_F7R1_FB30_Msk      (0x1UL << CAN_F7R1_FB30_Pos)                     /*!< 0x40000000 */
#define CAN_F7R1_FB30          CAN_F7R1_FB30_Msk                               /*!<Filter bit 30 */
#define CAN_F7R1_FB31_Pos      (31U)
#define CAN_F7R1_FB31_Msk      (0x1UL << CAN_F7R1_FB31_Pos)                     /*!< 0x80000000 */
#define CAN_F7R1_FB31          CAN_F7R1_FB31_Msk                               /*!<Filter bit 31 */

/*******************  Bit definition for CAN_F8R1 register  *******************/
#define CAN_F8R1_FB0_Pos       (0U)
#define CAN_F8R1_FB0_Msk       (0x1UL << CAN_F8R1_FB0_Pos)                      /*!< 0x00000001 */
#define CAN_F8R1_FB0           CAN_F8R1_FB0_Msk                                /*!<Filter bit 0 */
#define CAN_F8R1_FB1_Pos       (1U)
#define CAN_F8R1_FB1_Msk       (0x1UL << CAN_F8R1_FB1_Pos)                      /*!< 0x00000002 */
#define CAN_F8R1_FB1           CAN_F8R1_FB1_Msk                                /*!<Filter bit 1 */
#define CAN_F8R1_FB2_Pos       (2U)
#define CAN_F8R1_FB2_Msk       (0x1UL << CAN_F8R1_FB2_Pos)                      /*!< 0x00000004 */
#define CAN_F8R1_FB2           CAN_F8R1_FB2_Msk                                /*!<Filter bit 2 */
#define CAN_F8R1_FB3_Pos       (3U)
#define CAN_F8R1_FB3_Msk       (0x1UL << CAN_F8R1_FB3_Pos)                      /*!< 0x00000008 */
#define CAN_F8R1_FB3           CAN_F8R1_FB3_Msk                                /*!<Filter bit 3 */
#define CAN_F8R1_FB4_Pos       (4U)
#define CAN_F8R1_FB4_Msk       (0x1UL << CAN_F8R1_FB4_Pos)                      /*!< 0x00000010 */
#define CAN_F8R1_FB4           CAN_F8R1_FB4_Msk                                /*!<Filter bit 4 */
#define CAN_F8R1_FB5_Pos       (5U)
#define CAN_F8R1_FB5_Msk       (0x1UL << CAN_F8R1_FB5_Pos)                      /*!< 0x00000020 */
#define CAN_F8R1_FB5           CAN_F8R1_FB5_Msk                                /*!<Filter bit 5 */
#define CAN_F8R1_FB6_Pos       (6U)
#define CAN_F8R1_FB6_Msk       (0x1UL << CAN_F8R1_FB6_Pos)                      /*!< 0x00000040 */
#define CAN_F8R1_FB6           CAN_F8R1_FB6_Msk                                /*!<Filter bit 6 */
#define CAN_F8R1_FB7_Pos       (7U)
#define CAN_F8R1_FB7_Msk       (0x1UL << CAN_F8R1_FB7_Pos)                      /*!< 0x00000080 */
#define CAN_F8R1_FB7           CAN_F8R1_FB7_Msk                                /*!<Filter bit 7 */
#define CAN_F8R1_FB8_Pos       (8U)
#define CAN_F8R1_FB8_Msk       (0x1UL << CAN_F8R1_FB8_Pos)                      /*!< 0x00000100 */
#define CAN_F8R1_FB8           CAN_F8R1_FB8_Msk                                /*!<Filter bit 8 */
#define CAN_F8R1_FB9_Pos       (9U)
#define CAN_F8R1_FB9_Msk       (0x1UL << CAN_F8R1_FB9_Pos)                      /*!< 0x00000200 */
#define CAN_F8R1_FB9           CAN_F8R1_FB9_Msk                                /*!<Filter bit 9 */
#define CAN_F8R1_FB10_Pos      (10U)
#define CAN_F8R1_FB10_Msk      (0x1UL << CAN_F8R1_FB10_Pos)                     /*!< 0x00000400 */
#define CAN_F8R1_FB10          CAN_F8R1_FB10_Msk                               /*!<Filter bit 10 */
#define CAN_F8R1_FB11_Pos      (11U)
#define CAN_F8R1_FB11_Msk      (0x1UL << CAN_F8R1_FB11_Pos)                     /*!< 0x00000800 */
#define CAN_F8R1_FB11          CAN_F8R1_FB11_Msk                               /*!<Filter bit 11 */
#define CAN_F8R1_FB12_Pos      (12U)
#define CAN_F8R1_FB12_Msk      (0x1UL << CAN_F8R1_FB12_Pos)                     /*!< 0x00001000 */
#define CAN_F8R1_FB12          CAN_F8R1_FB12_Msk                               /*!<Filter bit 12 */
#define CAN_F8R1_FB13_Pos      (13U)
#define CAN_F8R1_FB13_Msk      (0x1UL << CAN_F8R1_FB13_Pos)                     /*!< 0x00002000 */
#define CAN_F8R1_FB13          CAN_F8R1_FB13_Msk                               /*!<Filter bit 13 */
#define CAN_F8R1_FB14_Pos      (14U)
#define CAN_F8R1_FB14_Msk      (0x1UL << CAN_F8R1_FB14_Pos)                     /*!< 0x00004000 */
#define CAN_F8R1_FB14          CAN_F8R1_FB14_Msk                               /*!<Filter bit 14 */
#define CAN_F8R1_FB15_Pos      (15U)
#define CAN_F8R1_FB15_Msk      (0x1UL << CAN_F8R1_FB15_Pos)                     /*!< 0x00008000 */
#define CAN_F8R1_FB15          CAN_F8R1_FB15_Msk                               /*!<Filter bit 15 */
#define CAN_F8R1_FB16_Pos      (16U)
#define CAN_F8R1_FB16_Msk      (0x1UL << CAN_F8R1_FB16_Pos)                     /*!< 0x00010000 */
#define CAN_F8R1_FB16          CAN_F8R1_FB16_Msk                               /*!<Filter bit 16 */
#define CAN_F8R1_FB17_Pos      (17U)
#define CAN_F8R1_FB17_Msk      (0x1UL << CAN_F8R1_FB17_Pos)                     /*!< 0x00020000 */
#define CAN_F8R1_FB17          CAN_F8R1_FB17_Msk                               /*!<Filter bit 17 */
#define CAN_F8R1_FB18_Pos      (18U)
#define CAN_F8R1_FB18_Msk      (0x1UL << CAN_F8R1_FB18_Pos)                     /*!< 0x00040000 */
#define CAN_F8R1_FB18          CAN_F8R1_FB18_Msk                               /*!<Filter bit 18 */
#define CAN_F8R1_FB19_Pos      (19U)
#define CAN_F8R1_FB19_Msk      (0x1UL << CAN_F8R1_FB19_Pos)                     /*!< 0x00080000 */
#define CAN_F8R1_FB19          CAN_F8R1_FB19_Msk                               /*!<Filter bit 19 */
#define CAN_F8R1_FB20_Pos      (20U)
#define CAN_F8R1_FB20_Msk      (0x1UL << CAN_F8R1_FB20_Pos)                     /*!< 0x00100000 */
#define CAN_F8R1_FB20          CAN_F8R1_FB20_Msk                               /*!<Filter bit 20 */
#define CAN_F8R1_FB21_Pos      (21U)
#define CAN_F8R1_FB21_Msk      (0x1UL << CAN_F8R1_FB21_Pos)                     /*!< 0x00200000 */
#define CAN_F8R1_FB21          CAN_F8R1_FB21_Msk                               /*!<Filter bit 21 */
#define CAN_F8R1_FB22_Pos      (22U)
#define CAN_F8R1_FB22_Msk      (0x1UL << CAN_F8R1_FB22_Pos)                     /*!< 0x00400000 */
#define CAN_F8R1_FB22          CAN_F8R1_FB22_Msk                               /*!<Filter bit 22 */
#define CAN_F8R1_FB23_Pos      (23U)
#define CAN_F8R1_FB23_Msk      (0x1UL << CAN_F8R1_FB23_Pos)                     /*!< 0x00800000 */
#define CAN_F8R1_FB23          CAN_F8R1_FB23_Msk                               /*!<Filter bit 23 */
#define CAN_F8R1_FB24_Pos      (24U)
#define CAN_F8R1_FB24_Msk      (0x1UL << CAN_F8R1_FB24_Pos)                     /*!< 0x01000000 */
#define CAN_F8R1_FB24          CAN_F8R1_FB24_Msk                               /*!<Filter bit 24 */
#define CAN_F8R1_FB25_Pos      (25U)
#define CAN_F8R1_FB25_Msk      (0x1UL << CAN_F8R1_FB25_Pos)                     /*!< 0x02000000 */
#define CAN_F8R1_FB25          CAN_F8R1_FB25_Msk                               /*!<Filter bit 25 */
#define CAN_F8R1_FB26_Pos      (26U)
#define CAN_F8R1_FB26_Msk      (0x1UL << CAN_F8R1_FB26_Pos)                     /*!< 0x04000000 */
#define CAN_F8R1_FB26          CAN_F8R1_FB26_Msk                               /*!<Filter bit 26 */
#define CAN_F8R1_FB27_Pos      (27U)
#define CAN_F8R1_FB27_Msk      (0x1UL << CAN_F8R1_FB27_Pos)                     /*!< 0x08000000 */
#define CAN_F8R1_FB27          CAN_F8R1_FB27_Msk                               /*!<Filter bit 27 */
#define CAN_F8R1_FB28_Pos      (28U)
#define CAN_F8R1_FB28_Msk      (0x1UL << CAN_F8R1_FB28_Pos)                     /*!< 0x10000000 */
#define CAN_F8R1_FB28          CAN_F8R1_FB28_Msk                               /*!<Filter bit 28 */
#define CAN_F8R1_FB29_Pos      (29U)
#define CAN_F8R1_FB29_Msk      (0x1UL << CAN_F8R1_FB29_Pos)                     /*!< 0x20000000 */
#define CAN_F8R1_FB29          CAN_F8R1_FB29_Msk                               /*!<Filter bit 29 */
#define CAN_F8R1_FB30_Pos      (30U)
#define CAN_F8R1_FB30_Msk      (0x1UL << CAN_F8R1_FB30_Pos)                     /*!< 0x40000000 */
#define CAN_F8R1_FB30          CAN_F8R1_FB30_Msk                               /*!<Filter bit 30 */
#define CAN_F8R1_FB31_Pos      (31U)
#define CAN_F8R1_FB31_Msk      (0x1UL << CAN_F8R1_FB31_Pos)                     /*!< 0x80000000 */
#define CAN_F8R1_FB31          CAN_F8R1_FB31_Msk                               /*!<Filter bit 31 */

/*******************  Bit definition for CAN_F9R1 register  *******************/
#define CAN_F9R1_FB0_Pos       (0U)
#define CAN_F9R1_FB0_Msk       (0x1UL << CAN_F9R1_FB0_Pos)                      /*!< 0x00000001 */
#define CAN_F9R1_FB0           CAN_F9R1_FB0_Msk                                /*!<Filter bit 0 */
#define CAN_F9R1_FB1_Pos       (1U)
#define CAN_F9R1_FB1_Msk       (0x1UL << CAN_F9R1_FB1_Pos)                      /*!< 0x00000002 */
#define CAN_F9R1_FB1           CAN_F9R1_FB1_Msk                                /*!<Filter bit 1 */
#define CAN_F9R1_FB2_Pos       (2U)
#define CAN_F9R1_FB2_Msk       (0x1UL << CAN_F9R1_FB2_Pos)                      /*!< 0x00000004 */
#define CAN_F9R1_FB2           CAN_F9R1_FB2_Msk                                /*!<Filter bit 2 */
#define CAN_F9R1_FB3_Pos       (3U)
#define CAN_F9R1_FB3_Msk       (0x1UL << CAN_F9R1_FB3_Pos)                      /*!< 0x00000008 */
#define CAN_F9R1_FB3           CAN_F9R1_FB3_Msk                                /*!<Filter bit 3 */
#define CAN_F9R1_FB4_Pos       (4U)
#define CAN_F9R1_FB4_Msk       (0x1UL << CAN_F9R1_FB4_Pos)                      /*!< 0x00000010 */
#define CAN_F9R1_FB4           CAN_F9R1_FB4_Msk                                /*!<Filter bit 4 */
#define CAN_F9R1_FB5_Pos       (5U)
#define CAN_F9R1_FB5_Msk       (0x1UL << CAN_F9R1_FB5_Pos)                      /*!< 0x00000020 */
#define CAN_F9R1_FB5           CAN_F9R1_FB5_Msk                                /*!<Filter bit 5 */
#define CAN_F9R1_FB6_Pos       (6U)
#define CAN_F9R1_FB6_Msk       (0x1UL << CAN_F9R1_FB6_Pos)                      /*!< 0x00000040 */
#define CAN_F9R1_FB6           CAN_F9R1_FB6_Msk                                /*!<Filter bit 6 */
#define CAN_F9R1_FB7_Pos       (7U)
#define CAN_F9R1_FB7_Msk       (0x1UL << CAN_F9R1_FB7_Pos)                      /*!< 0x00000080 */
#define CAN_F9R1_FB7           CAN_F9R1_FB7_Msk                                /*!<Filter bit 7 */
#define CAN_F9R1_FB8_Pos       (8U)
#define CAN_F9R1_FB8_Msk       (0x1UL << CAN_F9R1_FB8_Pos)                      /*!< 0x00000100 */
#define CAN_F9R1_FB8           CAN_F9R1_FB8_Msk                                /*!<Filter bit 8 */
#define CAN_F9R1_FB9_Pos       (9U)
#define CAN_F9R1_FB9_Msk       (0x1UL << CAN_F9R1_FB9_Pos)                      /*!< 0x00000200 */
#define CAN_F9R1_FB9           CAN_F9R1_FB9_Msk                                /*!<Filter bit 9 */
#define CAN_F9R1_FB10_Pos      (10U)
#define CAN_F9R1_FB10_Msk      (0x1UL << CAN_F9R1_FB10_Pos)                     /*!< 0x00000400 */
#define CAN_F9R1_FB10          CAN_F9R1_FB10_Msk                               /*!<Filter bit 10 */
#define CAN_F9R1_FB11_Pos      (11U)
#define CAN_F9R1_FB11_Msk      (0x1UL << CAN_F9R1_FB11_Pos)                     /*!< 0x00000800 */
#define CAN_F9R1_FB11          CAN_F9R1_FB11_Msk                               /*!<Filter bit 11 */
#define CAN_F9R1_FB12_Pos      (12U)
#define CAN_F9R1_FB12_Msk      (0x1UL << CAN_F9R1_FB12_Pos)                     /*!< 0x00001000 */
#define CAN_F9R1_FB12          CAN_F9R1_FB12_Msk                               /*!<Filter bit 12 */
#define CAN_F9R1_FB13_Pos      (13U)
#define CAN_F9R1_FB13_Msk      (0x1UL << CAN_F9R1_FB13_Pos)                     /*!< 0x00002000 */
#define CAN_F9R1_FB13          CAN_F9R1_FB13_Msk                               /*!<Filter bit 13 */
#define CAN_F9R1_FB14_Pos      (14U)
#define CAN_F9R1_FB14_Msk      (0x1UL << CAN_F9R1_FB14_Pos)                     /*!< 0x00004000 */
#define CAN_F9R1_FB14          CAN_F9R1_FB14_Msk                               /*!<Filter bit 14 */
#define CAN_F9R1_FB15_Pos      (15U)
#define CAN_F9R1_FB15_Msk      (0x1UL << CAN_F9R1_FB15_Pos)                     /*!< 0x00008000 */
#define CAN_F9R1_FB15          CAN_F9R1_FB15_Msk                               /*!<Filter bit 15 */
#define CAN_F9R1_FB16_Pos      (16U)
#define CAN_F9R1_FB16_Msk      (0x1UL << CAN_F9R1_FB16_Pos)                     /*!< 0x00010000 */
#define CAN_F9R1_FB16          CAN_F9R1_FB16_Msk                               /*!<Filter bit 16 */
#define CAN_F9R1_FB17_Pos      (17U)
#define CAN_F9R1_FB17_Msk      (0x1UL << CAN_F9R1_FB17_Pos)                     /*!< 0x00020000 */
#define CAN_F9R1_FB17          CAN_F9R1_FB17_Msk                               /*!<Filter bit 17 */
#define CAN_F9R1_FB18_Pos      (18U)
#define CAN_F9R1_FB18_Msk      (0x1UL << CAN_F9R1_FB18_Pos)                     /*!< 0x00040000 */
#define CAN_F9R1_FB18          CAN_F9R1_FB18_Msk                               /*!<Filter bit 18 */
#define CAN_F9R1_FB19_Pos      (19U)
#define CAN_F9R1_FB19_Msk      (0x1UL << CAN_F9R1_FB19_Pos)                     /*!< 0x00080000 */
#define CAN_F9R1_FB19          CAN_F9R1_FB19_Msk                               /*!<Filter bit 19 */
#define CAN_F9R1_FB20_Pos      (20U)
#define CAN_F9R1_FB20_Msk      (0x1UL << CAN_F9R1_FB20_Pos)                     /*!< 0x00100000 */
#define CAN_F9R1_FB20          CAN_F9R1_FB20_Msk                               /*!<Filter bit 20 */
#define CAN_F9R1_FB21_Pos      (21U)
#define CAN_F9R1_FB21_Msk      (0x1UL << CAN_F9R1_FB21_Pos)                     /*!< 0x00200000 */
#define CAN_F9R1_FB21          CAN_F9R1_FB21_Msk                               /*!<Filter bit 21 */
#define CAN_F9R1_FB22_Pos      (22U)
#define CAN_F9R1_FB22_Msk      (0x1UL << CAN_F9R1_FB22_Pos)                     /*!< 0x00400000 */
#define CAN_F9R1_FB22          CAN_F9R1_FB22_Msk                               /*!<Filter bit 22 */
#define CAN_F9R1_FB23_Pos      (23U)
#define CAN_F9R1_FB23_Msk      (0x1UL << CAN_F9R1_FB23_Pos)                     /*!< 0x00800000 */
#define CAN_F9R1_FB23          CAN_F9R1_FB23_Msk                               /*!<Filter bit 23 */
#define CAN_F9R1_FB24_Pos      (24U)
#define CAN_F9R1_FB24_Msk      (0x1UL << CAN_F9R1_FB24_Pos)                     /*!< 0x01000000 */
#define CAN_F9R1_FB24          CAN_F9R1_FB24_Msk                               /*!<Filter bit 24 */
#define CAN_F9R1_FB25_Pos      (25U)
#define CAN_F9R1_FB25_Msk      (0x1UL << CAN_F9R1_FB25_Pos)                     /*!< 0x02000000 */
#define CAN_F9R1_FB25          CAN_F9R1_FB25_Msk                               /*!<Filter bit 25 */
#define CAN_F9R1_FB26_Pos      (26U)
#define CAN_F9R1_FB26_Msk      (0x1UL << CAN_F9R1_FB26_Pos)                     /*!< 0x04000000 */
#define CAN_F9R1_FB26          CAN_F9R1_FB26_Msk                               /*!<Filter bit 26 */
#define CAN_F9R1_FB27_Pos      (27U)
#define CAN_F9R1_FB27_Msk      (0x1UL << CAN_F9R1_FB27_Pos)                     /*!< 0x08000000 */
#define CAN_F9R1_FB27          CAN_F9R1_FB27_Msk                               /*!<Filter bit 27 */
#define CAN_F9R1_FB28_Pos      (28U)
#define CAN_F9R1_FB28_Msk      (0x1UL << CAN_F9R1_FB28_Pos)                     /*!< 0x10000000 */
#define CAN_F9R1_FB28          CAN_F9R1_FB28_Msk                               /*!<Filter bit 28 */
#define CAN_F9R1_FB29_Pos      (29U)
#define CAN_F9R1_FB29_Msk      (0x1UL << CAN_F9R1_FB29_Pos)                     /*!< 0x20000000 */
#define CAN_F9R1_FB29          CAN_F9R1_FB29_Msk                               /*!<Filter bit 29 */
#define CAN_F9R1_FB30_Pos      (30U)
#define CAN_F9R1_FB30_Msk      (0x1UL << CAN_F9R1_FB30_Pos)                     /*!< 0x40000000 */
#define CAN_F9R1_FB30          CAN_F9R1_FB30_Msk                               /*!<Filter bit 30 */
#define CAN_F9R1_FB31_Pos      (31U)
#define CAN_F9R1_FB31_Msk      (0x1UL << CAN_F9R1_FB31_Pos)                     /*!< 0x80000000 */
#define CAN_F9R1_FB31          CAN_F9R1_FB31_Msk                               /*!<Filter bit 31 */

/*******************  Bit definition for CAN_F10R1 register  ******************/
#define CAN_F10R1_FB0_Pos      (0U)
#define CAN_F10R1_FB0_Msk      (0x1UL << CAN_F10R1_FB0_Pos)                     /*!< 0x00000001 */
#define CAN_F10R1_FB0          CAN_F10R1_FB0_Msk                               /*!<Filter bit 0 */
#define CAN_F10R1_FB1_Pos      (1U)
#define CAN_F10R1_FB1_Msk      (0x1UL << CAN_F10R1_FB1_Pos)                     /*!< 0x00000002 */
#define CAN_F10R1_FB1          CAN_F10R1_FB1_Msk                               /*!<Filter bit 1 */
#define CAN_F10R1_FB2_Pos      (2U)
#define CAN_F10R1_FB2_Msk      (0x1UL << CAN_F10R1_FB2_Pos)                     /*!< 0x00000004 */
#define CAN_F10R1_FB2          CAN_F10R1_FB2_Msk                               /*!<Filter bit 2 */
#define CAN_F10R1_FB3_Pos      (3U)
#define CAN_F10R1_FB3_Msk      (0x1UL << CAN_F10R1_FB3_Pos)                     /*!< 0x00000008 */
#define CAN_F10R1_FB3          CAN_F10R1_FB3_Msk                               /*!<Filter bit 3 */
#define CAN_F10R1_FB4_Pos      (4U)
#define CAN_F10R1_FB4_Msk      (0x1UL << CAN_F10R1_FB4_Pos)                     /*!< 0x00000010 */
#define CAN_F10R1_FB4          CAN_F10R1_FB4_Msk                               /*!<Filter bit 4 */
#define CAN_F10R1_FB5_Pos      (5U)
#define CAN_F10R1_FB5_Msk      (0x1UL << CAN_F10R1_FB5_Pos)                     /*!< 0x00000020 */
#define CAN_F10R1_FB5          CAN_F10R1_FB5_Msk                               /*!<Filter bit 5 */
#define CAN_F10R1_FB6_Pos      (6U)
#define CAN_F10R1_FB6_Msk      (0x1UL << CAN_F10R1_FB6_Pos)                     /*!< 0x00000040 */
#define CAN_F10R1_FB6          CAN_F10R1_FB6_Msk                               /*!<Filter bit 6 */
#define CAN_F10R1_FB7_Pos      (7U)
#define CAN_F10R1_FB7_Msk      (0x1UL << CAN_F10R1_FB7_Pos)                     /*!< 0x00000080 */
#define CAN_F10R1_FB7          CAN_F10R1_FB7_Msk                               /*!<Filter bit 7 */
#define CAN_F10R1_FB8_Pos      (8U)
#define CAN_F10R1_FB8_Msk      (0x1UL << CAN_F10R1_FB8_Pos)                     /*!< 0x00000100 */
#define CAN_F10R1_FB8          CAN_F10R1_FB8_Msk                               /*!<Filter bit 8 */
#define CAN_F10R1_FB9_Pos      (9U)
#define CAN_F10R1_FB9_Msk      (0x1UL << CAN_F10R1_FB9_Pos)                     /*!< 0x00000200 */
#define CAN_F10R1_FB9          CAN_F10R1_FB9_Msk                               /*!<Filter bit 9 */
#define CAN_F10R1_FB10_Pos     (10U)
#define CAN_F10R1_FB10_Msk     (0x1UL << CAN_F10R1_FB10_Pos)                    /*!< 0x00000400 */
#define CAN_F10R1_FB10         CAN_F10R1_FB10_Msk                              /*!<Filter bit 10 */
#define CAN_F10R1_FB11_Pos     (11U)
#define CAN_F10R1_FB11_Msk     (0x1UL << CAN_F10R1_FB11_Pos)                    /*!< 0x00000800 */
#define CAN_F10R1_FB11         CAN_F10R1_FB11_Msk                              /*!<Filter bit 11 */
#define CAN_F10R1_FB12_Pos     (12U)
#define CAN_F10R1_FB12_Msk     (0x1UL << CAN_F10R1_FB12_Pos)                    /*!< 0x00001000 */
#define CAN_F10R1_FB12         CAN_F10R1_FB12_Msk                              /*!<Filter bit 12 */
#define CAN_F10R1_FB13_Pos     (13U)
#define CAN_F10R1_FB13_Msk     (0x1UL << CAN_F10R1_FB13_Pos)                    /*!< 0x00002000 */
#define CAN_F10R1_FB13         CAN_F10R1_FB13_Msk                              /*!<Filter bit 13 */
#define CAN_F10R1_FB14_Pos     (14U)
#define CAN_F10R1_FB14_Msk     (0x1UL << CAN_F10R1_FB14_Pos)                    /*!< 0x00004000 */
#define CAN_F10R1_FB14         CAN_F10R1_FB14_Msk                              /*!<Filter bit 14 */
#define CAN_F10R1_FB15_Pos     (15U)
#define CAN_F10R1_FB15_Msk     (0x1UL << CAN_F10R1_FB15_Pos)                    /*!< 0x00008000 */
#define CAN_F10R1_FB15         CAN_F10R1_FB15_Msk                              /*!<Filter bit 15 */
#define CAN_F10R1_FB16_Pos     (16U)
#define CAN_F10R1_FB16_Msk     (0x1UL << CAN_F10R1_FB16_Pos)                    /*!< 0x00010000 */
#define CAN_F10R1_FB16         CAN_F10R1_FB16_Msk                              /*!<Filter bit 16 */
#define CAN_F10R1_FB17_Pos     (17U)
#define CAN_F10R1_FB17_Msk     (0x1UL << CAN_F10R1_FB17_Pos)                    /*!< 0x00020000 */
#define CAN_F10R1_FB17         CAN_F10R1_FB17_Msk                              /*!<Filter bit 17 */
#define CAN_F10R1_FB18_Pos     (18U)
#define CAN_F10R1_FB18_Msk     (0x1UL << CAN_F10R1_FB18_Pos)                    /*!< 0x00040000 */
#define CAN_F10R1_FB18         CAN_F10R1_FB18_Msk                              /*!<Filter bit 18 */
#define CAN_F10R1_FB19_Pos     (19U)
#define CAN_F10R1_FB19_Msk     (0x1UL << CAN_F10R1_FB19_Pos)                    /*!< 0x00080000 */
#define CAN_F10R1_FB19         CAN_F10R1_FB19_Msk                              /*!<Filter bit 19 */
#define CAN_F10R1_FB20_Pos     (20U)
#define CAN_F10R1_FB20_Msk     (0x1UL << CAN_F10R1_FB20_Pos)                    /*!< 0x00100000 */
#define CAN_F10R1_FB20         CAN_F10R1_FB20_Msk                              /*!<Filter bit 20 */
#define CAN_F10R1_FB21_Pos     (21U)
#define CAN_F10R1_FB21_Msk     (0x1UL << CAN_F10R1_FB21_Pos)                    /*!< 0x00200000 */
#define CAN_F10R1_FB21         CAN_F10R1_FB21_Msk                              /*!<Filter bit 21 */
#define CAN_F10R1_FB22_Pos     (22U)
#define CAN_F10R1_FB22_Msk     (0x1UL << CAN_F10R1_FB22_Pos)                    /*!< 0x00400000 */
#define CAN_F10R1_FB22         CAN_F10R1_FB22_Msk                              /*!<Filter bit 22 */
#define CAN_F10R1_FB23_Pos     (23U)
#define CAN_F10R1_FB23_Msk     (0x1UL << CAN_F10R1_FB23_Pos)                    /*!< 0x00800000 */
#define CAN_F10R1_FB23         CAN_F10R1_FB23_Msk                              /*!<Filter bit 23 */
#define CAN_F10R1_FB24_Pos     (24U)
#define CAN_F10R1_FB24_Msk     (0x1UL << CAN_F10R1_FB24_Pos)                    /*!< 0x01000000 */
#define CAN_F10R1_FB24         CAN_F10R1_FB24_Msk                              /*!<Filter bit 24 */
#define CAN_F10R1_FB25_Pos     (25U)
#define CAN_F10R1_FB25_Msk     (0x1UL << CAN_F10R1_FB25_Pos)                    /*!< 0x02000000 */
#define CAN_F10R1_FB25         CAN_F10R1_FB25_Msk                              /*!<Filter bit 25 */
#define CAN_F10R1_FB26_Pos     (26U)
#define CAN_F10R1_FB26_Msk     (0x1UL << CAN_F10R1_FB26_Pos)                    /*!< 0x04000000 */
#define CAN_F10R1_FB26         CAN_F10R1_FB26_Msk                              /*!<Filter bit 26 */
#define CAN_F10R1_FB27_Pos     (27U)
#define CAN_F10R1_FB27_Msk     (0x1UL << CAN_F10R1_FB27_Pos)                    /*!< 0x08000000 */
#define CAN_F10R1_FB27         CAN_F10R1_FB27_Msk                              /*!<Filter bit 27 */
#define CAN_F10R1_FB28_Pos     (28U)
#define CAN_F10R1_FB28_Msk     (0x1UL << CAN_F10R1_FB28_Pos)                    /*!< 0x10000000 */
#define CAN_F10R1_FB28         CAN_F10R1_FB28_Msk                              /*!<Filter bit 28 */
#define CAN_F10R1_FB29_Pos     (29U)
#define CAN_F10R1_FB29_Msk     (0x1UL << CAN_F10R1_FB29_Pos)                    /*!< 0x20000000 */
#define CAN_F10R1_FB29         CAN_F10R1_FB29_Msk                              /*!<Filter bit 29 */
#define CAN_F10R1_FB30_Pos     (30U)
#define CAN_F10R1_FB30_Msk     (0x1UL << CAN_F10R1_FB30_Pos)                    /*!< 0x40000000 */
#define CAN_F10R1_FB30         CAN_F10R1_FB30_Msk                              /*!<Filter bit 30 */
#define CAN_F10R1_FB31_Pos     (31U)
#define CAN_F10R1_FB31_Msk     (0x1UL << CAN_F10R1_FB31_Pos)                    /*!< 0x80000000 */
#define CAN_F10R1_FB31         CAN_F10R1_FB31_Msk                              /*!<Filter bit 31 */

/*******************  Bit definition for CAN_F11R1 register  ******************/
#define CAN_F11R1_FB0_Pos      (0U)
#define CAN_F11R1_FB0_Msk      (0x1UL << CAN_F11R1_FB0_Pos)                     /*!< 0x00000001 */
#define CAN_F11R1_FB0          CAN_F11R1_FB0_Msk                               /*!<Filter bit 0 */
#define CAN_F11R1_FB1_Pos      (1U)
#define CAN_F11R1_FB1_Msk      (0x1UL << CAN_F11R1_FB1_Pos)                     /*!< 0x00000002 */
#define CAN_F11R1_FB1          CAN_F11R1_FB1_Msk                               /*!<Filter bit 1 */
#define CAN_F11R1_FB2_Pos      (2U)
#define CAN_F11R1_FB2_Msk      (0x1UL << CAN_F11R1_FB2_Pos)                     /*!< 0x00000004 */
#define CAN_F11R1_FB2          CAN_F11R1_FB2_Msk                               /*!<Filter bit 2 */
#define CAN_F11R1_FB3_Pos      (3U)
#define CAN_F11R1_FB3_Msk      (0x1UL << CAN_F11R1_FB3_Pos)                     /*!< 0x00000008 */
#define CAN_F11R1_FB3          CAN_F11R1_FB3_Msk                               /*!<Filter bit 3 */
#define CAN_F11R1_FB4_Pos      (4U)
#define CAN_F11R1_FB4_Msk      (0x1UL << CAN_F11R1_FB4_Pos)                     /*!< 0x00000010 */
#define CAN_F11R1_FB4          CAN_F11R1_FB4_Msk                               /*!<Filter bit 4 */
#define CAN_F11R1_FB5_Pos      (5U)
#define CAN_F11R1_FB5_Msk      (0x1UL << CAN_F11R1_FB5_Pos)                     /*!< 0x00000020 */
#define CAN_F11R1_FB5          CAN_F11R1_FB5_Msk                               /*!<Filter bit 5 */
#define CAN_F11R1_FB6_Pos      (6U)
#define CAN_F11R1_FB6_Msk      (0x1UL << CAN_F11R1_FB6_Pos)                     /*!< 0x00000040 */
#define CAN_F11R1_FB6          CAN_F11R1_FB6_Msk                               /*!<Filter bit 6 */
#define CAN_F11R1_FB7_Pos      (7U)
#define CAN_F11R1_FB7_Msk      (0x1UL << CAN_F11R1_FB7_Pos)                     /*!< 0x00000080 */
#define CAN_F11R1_FB7          CAN_F11R1_FB7_Msk                               /*!<Filter bit 7 */
#define CAN_F11R1_FB8_Pos      (8U)
#define CAN_F11R1_FB8_Msk      (0x1UL << CAN_F11R1_FB8_Pos)                     /*!< 0x00000100 */
#define CAN_F11R1_FB8          CAN_F11R1_FB8_Msk                               /*!<Filter bit 8 */
#define CAN_F11R1_FB9_Pos      (9U)
#define CAN_F11R1_FB9_Msk      (0x1UL << CAN_F11R1_FB9_Pos)                     /*!< 0x00000200 */
#define CAN_F11R1_FB9          CAN_F11R1_FB9_Msk                               /*!<Filter bit 9 */
#define CAN_F11R1_FB10_Pos     (10U)
#define CAN_F11R1_FB10_Msk     (0x1UL << CAN_F11R1_FB10_Pos)                    /*!< 0x00000400 */
#define CAN_F11R1_FB10         CAN_F11R1_FB10_Msk                              /*!<Filter bit 10 */
#define CAN_F11R1_FB11_Pos     (11U)
#define CAN_F11R1_FB11_Msk     (0x1UL << CAN_F11R1_FB11_Pos)                    /*!< 0x00000800 */
#define CAN_F11R1_FB11         CAN_F11R1_FB11_Msk                              /*!<Filter bit 11 */
#define CAN_F11R1_FB12_Pos     (12U)
#define CAN_F11R1_FB12_Msk     (0x1UL << CAN_F11R1_FB12_Pos)                    /*!< 0x00001000 */
#define CAN_F11R1_FB12         CAN_F11R1_FB12_Msk                              /*!<Filter bit 12 */
#define CAN_F11R1_FB13_Pos     (13U)
#define CAN_F11R1_FB13_Msk     (0x1UL << CAN_F11R1_FB13_Pos)                    /*!< 0x00002000 */
#define CAN_F11R1_FB13         CAN_F11R1_FB13_Msk                              /*!<Filter bit 13 */
#define CAN_F11R1_FB14_Pos     (14U)
#define CAN_F11R1_FB14_Msk     (0x1UL << CAN_F11R1_FB14_Pos)                    /*!< 0x00004000 */
#define CAN_F11R1_FB14         CAN_F11R1_FB14_Msk                              /*!<Filter bit 14 */
#define CAN_F11R1_FB15_Pos     (15U)
#define CAN_F11R1_FB15_Msk     (0x1UL << CAN_F11R1_FB15_Pos)                    /*!< 0x00008000 */
#define CAN_F11R1_FB15         CAN_F11R1_FB15_Msk                              /*!<Filter bit 15 */
#define CAN_F11R1_FB16_Pos     (16U)
#define CAN_F11R1_FB16_Msk     (0x1UL << CAN_F11R1_FB16_Pos)                    /*!< 0x00010000 */
#define CAN_F11R1_FB16         CAN_F11R1_FB16_Msk                              /*!<Filter bit 16 */
#define CAN_F11R1_FB17_Pos     (17U)
#define CAN_F11R1_FB17_Msk     (0x1UL << CAN_F11R1_FB17_Pos)                    /*!< 0x00020000 */
#define CAN_F11R1_FB17         CAN_F11R1_FB17_Msk                              /*!<Filter bit 17 */
#define CAN_F11R1_FB18_Pos     (18U)
#define CAN_F11R1_FB18_Msk     (0x1UL << CAN_F11R1_FB18_Pos)                    /*!< 0x00040000 */
#define CAN_F11R1_FB18         CAN_F11R1_FB18_Msk                              /*!<Filter bit 18 */
#define CAN_F11R1_FB19_Pos     (19U)
#define CAN_F11R1_FB19_Msk     (0x1UL << CAN_F11R1_FB19_Pos)                    /*!< 0x00080000 */
#define CAN_F11R1_FB19         CAN_F11R1_FB19_Msk                              /*!<Filter bit 19 */
#define CAN_F11R1_FB20_Pos     (20U)
#define CAN_F11R1_FB20_Msk     (0x1UL << CAN_F11R1_FB20_Pos)                    /*!< 0x00100000 */
#define CAN_F11R1_FB20         CAN_F11R1_FB20_Msk                              /*!<Filter bit 20 */
#define CAN_F11R1_FB21_Pos     (21U)
#define CAN_F11R1_FB21_Msk     (0x1UL << CAN_F11R1_FB21_Pos)                    /*!< 0x00200000 */
#define CAN_F11R1_FB21         CAN_F11R1_FB21_Msk                              /*!<Filter bit 21 */
#define CAN_F11R1_FB22_Pos     (22U)
#define CAN_F11R1_FB22_Msk     (0x1UL << CAN_F11R1_FB22_Pos)                    /*!< 0x00400000 */
#define CAN_F11R1_FB22         CAN_F11R1_FB22_Msk                              /*!<Filter bit 22 */
#define CAN_F11R1_FB23_Pos     (23U)
#define CAN_F11R1_FB23_Msk     (0x1UL << CAN_F11R1_FB23_Pos)                    /*!< 0x00800000 */
#define CAN_F11R1_FB23         CAN_F11R1_FB23_Msk                              /*!<Filter bit 23 */
#define CAN_F11R1_FB24_Pos     (24U)
#define CAN_F11R1_FB24_Msk     (0x1UL << CAN_F11R1_FB24_Pos)                    /*!< 0x01000000 */
#define CAN_F11R1_FB24         CAN_F11R1_FB24_Msk                              /*!<Filter bit 24 */
#define CAN_F11R1_FB25_Pos     (25U)
#define CAN_F11R1_FB25_Msk     (0x1UL << CAN_F11R1_FB25_Pos)                    /*!< 0x02000000 */
#define CAN_F11R1_FB25         CAN_F11R1_FB25_Msk                              /*!<Filter bit 25 */
#define CAN_F11R1_FB26_Pos     (26U)
#define CAN_F11R1_FB26_Msk     (0x1UL << CAN_F11R1_FB26_Pos)                    /*!< 0x04000000 */
#define CAN_F11R1_FB26         CAN_F11R1_FB26_Msk                              /*!<Filter bit 26 */
#define CAN_F11R1_FB27_Pos     (27U)
#define CAN_F11R1_FB27_Msk     (0x1UL << CAN_F11R1_FB27_Pos)                    /*!< 0x08000000 */
#define CAN_F11R1_FB27         CAN_F11R1_FB27_Msk                              /*!<Filter bit 27 */
#define CAN_F11R1_FB28_Pos     (28U)
#define CAN_F11R1_FB28_Msk     (0x1UL << CAN_F11R1_FB28_Pos)                    /*!< 0x10000000 */
#define CAN_F11R1_FB28         CAN_F11R1_FB28_Msk                              /*!<Filter bit 28 */
#define CAN_F11R1_FB29_Pos     (29U)
#define CAN_F11R1_FB29_Msk     (0x1UL << CAN_F11R1_FB29_Pos)                    /*!< 0x20000000 */
#define CAN_F11R1_FB29         CAN_F11R1_FB29_Msk                              /*!<Filter bit 29 */
#define CAN_F11R1_FB30_Pos     (30U)
#define CAN_F11R1_FB30_Msk     (0x1UL << CAN_F11R1_FB30_Pos)                    /*!< 0x40000000 */
#define CAN_F11R1_FB30         CAN_F11R1_FB30_Msk                              /*!<Filter bit 30 */
#define CAN_F11R1_FB31_Pos     (31U)
#define CAN_F11R1_FB31_Msk     (0x1UL << CAN_F11R1_FB31_Pos)                    /*!< 0x80000000 */
#define CAN_F11R1_FB31         CAN_F11R1_FB31_Msk                              /*!<Filter bit 31 */

/*******************  Bit definition for CAN_F12R1 register  ******************/
#define CAN_F12R1_FB0_Pos      (0U)
#define CAN_F12R1_FB0_Msk      (0x1UL << CAN_F12R1_FB0_Pos)                     /*!< 0x00000001 */
#define CAN_F12R1_FB0          CAN_F12R1_FB0_Msk                               /*!<Filter bit 0 */
#define CAN_F12R1_FB1_Pos      (1U)
#define CAN_F12R1_FB1_Msk      (0x1UL << CAN_F12R1_FB1_Pos)                     /*!< 0x00000002 */
#define CAN_F12R1_FB1          CAN_F12R1_FB1_Msk                               /*!<Filter bit 1 */
#define CAN_F12R1_FB2_Pos      (2U)
#define CAN_F12R1_FB2_Msk      (0x1UL << CAN_F12R1_FB2_Pos)                     /*!< 0x00000004 */
#define CAN_F12R1_FB2          CAN_F12R1_FB2_Msk                               /*!<Filter bit 2 */
#define CAN_F12R1_FB3_Pos      (3U)
#define CAN_F12R1_FB3_Msk      (0x1UL << CAN_F12R1_FB3_Pos)                     /*!< 0x00000008 */
#define CAN_F12R1_FB3          CAN_F12R1_FB3_Msk                               /*!<Filter bit 3 */
#define CAN_F12R1_FB4_Pos      (4U)
#define CAN_F12R1_FB4_Msk      (0x1UL << CAN_F12R1_FB4_Pos)                     /*!< 0x00000010 */
#define CAN_F12R1_FB4          CAN_F12R1_FB4_Msk                               /*!<Filter bit 4 */
#define CAN_F12R1_FB5_Pos      (5U)
#define CAN_F12R1_FB5_Msk      (0x1UL << CAN_F12R1_FB5_Pos)                     /*!< 0x00000020 */
#define CAN_F12R1_FB5          CAN_F12R1_FB5_Msk                               /*!<Filter bit 5 */
#define CAN_F12R1_FB6_Pos      (6U)
#define CAN_F12R1_FB6_Msk      (0x1UL << CAN_F12R1_FB6_Pos)                     /*!< 0x00000040 */
#define CAN_F12R1_FB6          CAN_F12R1_FB6_Msk                               /*!<Filter bit 6 */
#define CAN_F12R1_FB7_Pos      (7U)
#define CAN_F12R1_FB7_Msk      (0x1UL << CAN_F12R1_FB7_Pos)                     /*!< 0x00000080 */
#define CAN_F12R1_FB7          CAN_F12R1_FB7_Msk                               /*!<Filter bit 7 */
#define CAN_F12R1_FB8_Pos      (8U)
#define CAN_F12R1_FB8_Msk      (0x1UL << CAN_F12R1_FB8_Pos)                     /*!< 0x00000100 */
#define CAN_F12R1_FB8          CAN_F12R1_FB8_Msk                               /*!<Filter bit 8 */
#define CAN_F12R1_FB9_Pos      (9U)
#define CAN_F12R1_FB9_Msk      (0x1UL << CAN_F12R1_FB9_Pos)                     /*!< 0x00000200 */
#define CAN_F12R1_FB9          CAN_F12R1_FB9_Msk                               /*!<Filter bit 9 */
#define CAN_F12R1_FB10_Pos     (10U)
#define CAN_F12R1_FB10_Msk     (0x1UL << CAN_F12R1_FB10_Pos)                    /*!< 0x00000400 */
#define CAN_F12R1_FB10         CAN_F12R1_FB10_Msk                              /*!<Filter bit 10 */
#define CAN_F12R1_FB11_Pos     (11U)
#define CAN_F12R1_FB11_Msk     (0x1UL << CAN_F12R1_FB11_Pos)                    /*!< 0x00000800 */
#define CAN_F12R1_FB11         CAN_F12R1_FB11_Msk                              /*!<Filter bit 11 */
#define CAN_F12R1_FB12_Pos     (12U)
#define CAN_F12R1_FB12_Msk     (0x1UL << CAN_F12R1_FB12_Pos)                    /*!< 0x00001000 */
#define CAN_F12R1_FB12         CAN_F12R1_FB12_Msk                              /*!<Filter bit 12 */
#define CAN_F12R1_FB13_Pos     (13U)
#define CAN_F12R1_FB13_Msk     (0x1UL << CAN_F12R1_FB13_Pos)                    /*!< 0x00002000 */
#define CAN_F12R1_FB13         CAN_F12R1_FB13_Msk                              /*!<Filter bit 13 */
#define CAN_F12R1_FB14_Pos     (14U)
#define CAN_F12R1_FB14_Msk     (0x1UL << CAN_F12R1_FB14_Pos)                    /*!< 0x00004000 */
#define CAN_F12R1_FB14         CAN_F12R1_FB14_Msk                              /*!<Filter bit 14 */
#define CAN_F12R1_FB15_Pos     (15U)
#define CAN_F12R1_FB15_Msk     (0x1UL << CAN_F12R1_FB15_Pos)                    /*!< 0x00008000 */
#define CAN_F12R1_FB15         CAN_F12R1_FB15_Msk                              /*!<Filter bit 15 */
#define CAN_F12R1_FB16_Pos     (16U)
#define CAN_F12R1_FB16_Msk     (0x1UL << CAN_F12R1_FB16_Pos)                    /*!< 0x00010000 */
#define CAN_F12R1_FB16         CAN_F12R1_FB16_Msk                              /*!<Filter bit 16 */
#define CAN_F12R1_FB17_Pos     (17U)
#define CAN_F12R1_FB17_Msk     (0x1UL << CAN_F12R1_FB17_Pos)                    /*!< 0x00020000 */
#define CAN_F12R1_FB17         CAN_F12R1_FB17_Msk                              /*!<Filter bit 17 */
#define CAN_F12R1_FB18_Pos     (18U)
#define CAN_F12R1_FB18_Msk     (0x1UL << CAN_F12R1_FB18_Pos)                    /*!< 0x00040000 */
#define CAN_F12R1_FB18         CAN_F12R1_FB18_Msk                              /*!<Filter bit 18 */
#define CAN_F12R1_FB19_Pos     (19U)
#define CAN_F12R1_FB19_Msk     (0x1UL << CAN_F12R1_FB19_Pos)                    /*!< 0x00080000 */
#define CAN_F12R1_FB19         CAN_F12R1_FB19_Msk                              /*!<Filter bit 19 */
#define CAN_F12R1_FB20_Pos     (20U)
#define CAN_F12R1_FB20_Msk     (0x1UL << CAN_F12R1_FB20_Pos)                    /*!< 0x00100000 */
#define CAN_F12R1_FB20         CAN_F12R1_FB20_Msk                              /*!<Filter bit 20 */
#define CAN_F12R1_FB21_Pos     (21U)
#define CAN_F12R1_FB21_Msk     (0x1UL << CAN_F12R1_FB21_Pos)                    /*!< 0x00200000 */
#define CAN_F12R1_FB21         CAN_F12R1_FB21_Msk                              /*!<Filter bit 21 */
#define CAN_F12R1_FB22_Pos     (22U)
#define CAN_F12R1_FB22_Msk     (0x1UL << CAN_F12R1_FB22_Pos)                    /*!< 0x00400000 */
#define CAN_F12R1_FB22         CAN_F12R1_FB22_Msk                              /*!<Filter bit 22 */
#define CAN_F12R1_FB23_Pos     (23U)
#define CAN_F12R1_FB23_Msk     (0x1UL << CAN_F12R1_FB23_Pos)                    /*!< 0x00800000 */
#define CAN_F12R1_FB23         CAN_F12R1_FB23_Msk                              /*!<Filter bit 23 */
#define CAN_F12R1_FB24_Pos     (24U)
#define CAN_F12R1_FB24_Msk     (0x1UL << CAN_F12R1_FB24_Pos)                    /*!< 0x01000000 */
#define CAN_F12R1_FB24         CAN_F12R1_FB24_Msk                              /*!<Filter bit 24 */
#define CAN_F12R1_FB25_Pos     (25U)
#define CAN_F12R1_FB25_Msk     (0x1UL << CAN_F12R1_FB25_Pos)                    /*!< 0x02000000 */
#define CAN_F12R1_FB25         CAN_F12R1_FB25_Msk                              /*!<Filter bit 25 */
#define CAN_F12R1_FB26_Pos     (26U)
#define CAN_F12R1_FB26_Msk     (0x1UL << CAN_F12R1_FB26_Pos)                    /*!< 0x04000000 */
#define CAN_F12R1_FB26         CAN_F12R1_FB26_Msk                              /*!<Filter bit 26 */
#define CAN_F12R1_FB27_Pos     (27U)
#define CAN_F12R1_FB27_Msk     (0x1UL << CAN_F12R1_FB27_Pos)                    /*!< 0x08000000 */
#define CAN_F12R1_FB27         CAN_F12R1_FB27_Msk                              /*!<Filter bit 27 */
#define CAN_F12R1_FB28_Pos     (28U)
#define CAN_F12R1_FB28_Msk     (0x1UL << CAN_F12R1_FB28_Pos)                    /*!< 0x10000000 */
#define CAN_F12R1_FB28         CAN_F12R1_FB28_Msk                              /*!<Filter bit 28 */
#define CAN_F12R1_FB29_Pos     (29U)
#define CAN_F12R1_FB29_Msk     (0x1UL << CAN_F12R1_FB29_Pos)                    /*!< 0x20000000 */
#define CAN_F12R1_FB29         CAN_F12R1_FB29_Msk                              /*!<Filter bit 29 */
#define CAN_F12R1_FB30_Pos     (30U)
#define CAN_F12R1_FB30_Msk     (0x1UL << CAN_F12R1_FB30_Pos)                    /*!< 0x40000000 */
#define CAN_F12R1_FB30         CAN_F12R1_FB30_Msk                              /*!<Filter bit 30 */
#define CAN_F12R1_FB31_Pos     (31U)
#define CAN_F12R1_FB31_Msk     (0x1UL << CAN_F12R1_FB31_Pos)                    /*!< 0x80000000 */
#define CAN_F12R1_FB31         CAN_F12R1_FB31_Msk                              /*!<Filter bit 31 */

/*******************  Bit definition for CAN_F13R1 register  ******************/
#define CAN_F13R1_FB0_Pos      (0U)
#define CAN_F13R1_FB0_Msk      (0x1UL << CAN_F13R1_FB0_Pos)                     /*!< 0x00000001 */
#define CAN_F13R1_FB0          CAN_F13R1_FB0_Msk                               /*!<Filter bit 0 */
#define CAN_F13R1_FB1_Pos      (1U)
#define CAN_F13R1_FB1_Msk      (0x1UL << CAN_F13R1_FB1_Pos)                     /*!< 0x00000002 */
#define CAN_F13R1_FB1          CAN_F13R1_FB1_Msk                               /*!<Filter bit 1 */
#define CAN_F13R1_FB2_Pos      (2U)
#define CAN_F13R1_FB2_Msk      (0x1UL << CAN_F13R1_FB2_Pos)                     /*!< 0x00000004 */
#define CAN_F13R1_FB2          CAN_F13R1_FB2_Msk                               /*!<Filter bit 2 */
#define CAN_F13R1_FB3_Pos      (3U)
#define CAN_F13R1_FB3_Msk      (0x1UL << CAN_F13R1_FB3_Pos)                     /*!< 0x00000008 */
#define CAN_F13R1_FB3          CAN_F13R1_FB3_Msk                               /*!<Filter bit 3 */
#define CAN_F13R1_FB4_Pos      (4U)
#define CAN_F13R1_FB4_Msk      (0x1UL << CAN_F13R1_FB4_Pos)                     /*!< 0x00000010 */
#define CAN_F13R1_FB4          CAN_F13R1_FB4_Msk                               /*!<Filter bit 4 */
#define CAN_F13R1_FB5_Pos      (5U)
#define CAN_F13R1_FB5_Msk      (0x1UL << CAN_F13R1_FB5_Pos)                     /*!< 0x00000020 */
#define CAN_F13R1_FB5          CAN_F13R1_FB5_Msk                               /*!<Filter bit 5 */
#define CAN_F13R1_FB6_Pos      (6U)
#define CAN_F13R1_FB6_Msk      (0x1UL << CAN_F13R1_FB6_Pos)                     /*!< 0x00000040 */
#define CAN_F13R1_FB6          CAN_F13R1_FB6_Msk                               /*!<Filter bit 6 */
#define CAN_F13R1_FB7_Pos      (7U)
#define CAN_F13R1_FB7_Msk      (0x1UL << CAN_F13R1_FB7_Pos)                     /*!< 0x00000080 */
#define CAN_F13R1_FB7          CAN_F13R1_FB7_Msk                               /*!<Filter bit 7 */
#define CAN_F13R1_FB8_Pos      (8U)
#define CAN_F13R1_FB8_Msk      (0x1UL << CAN_F13R1_FB8_Pos)                     /*!< 0x00000100 */
#define CAN_F13R1_FB8          CAN_F13R1_FB8_Msk                               /*!<Filter bit 8 */
#define CAN_F13R1_FB9_Pos      (9U)
#define CAN_F13R1_FB9_Msk      (0x1UL << CAN_F13R1_FB9_Pos)                     /*!< 0x00000200 */
#define CAN_F13R1_FB9          CAN_F13R1_FB9_Msk                               /*!<Filter bit 9 */
#define CAN_F13R1_FB10_Pos     (10U)
#define CAN_F13R1_FB10_Msk     (0x1UL << CAN_F13R1_FB10_Pos)                    /*!< 0x00000400 */
#define CAN_F13R1_FB10         CAN_F13R1_FB10_Msk                              /*!<Filter bit 10 */
#define CAN_F13R1_FB11_Pos     (11U)
#define CAN_F13R1_FB11_Msk     (0x1UL << CAN_F13R1_FB11_Pos)                    /*!< 0x00000800 */
#define CAN_F13R1_FB11         CAN_F13R1_FB11_Msk                              /*!<Filter bit 11 */
#define CAN_F13R1_FB12_Pos     (12U)
#define CAN_F13R1_FB12_Msk     (0x1UL << CAN_F13R1_FB12_Pos)                    /*!< 0x00001000 */
#define CAN_F13R1_FB12         CAN_F13R1_FB12_Msk                              /*!<Filter bit 12 */
#define CAN_F13R1_FB13_Pos     (13U)
#define CAN_F13R1_FB13_Msk     (0x1UL << CAN_F13R1_FB13_Pos)                    /*!< 0x00002000 */
#define CAN_F13R1_FB13         CAN_F13R1_FB13_Msk                              /*!<Filter bit 13 */
#define CAN_F13R1_FB14_Pos     (14U)
#define CAN_F13R1_FB14_Msk     (0x1UL << CAN_F13R1_FB14_Pos)                    /*!< 0x00004000 */
#define CAN_F13R1_FB14         CAN_F13R1_FB14_Msk                              /*!<Filter bit 14 */
#define CAN_F13R1_FB15_Pos     (15U)
#define CAN_F13R1_FB15_Msk     (0x1UL << CAN_F13R1_FB15_Pos)                    /*!< 0x00008000 */
#define CAN_F13R1_FB15         CAN_F13R1_FB15_Msk                              /*!<Filter bit 15 */
#define CAN_F13R1_FB16_Pos     (16U)
#define CAN_F13R1_FB16_Msk     (0x1UL << CAN_F13R1_FB16_Pos)                    /*!< 0x00010000 */
#define CAN_F13R1_FB16         CAN_F13R1_FB16_Msk                              /*!<Filter bit 16 */
#define CAN_F13R1_FB17_Pos     (17U)
#define CAN_F13R1_FB17_Msk     (0x1UL << CAN_F13R1_FB17_Pos)                    /*!< 0x00020000 */
#define CAN_F13R1_FB17         CAN_F13R1_FB17_Msk                              /*!<Filter bit 17 */
#define CAN_F13R1_FB18_Pos     (18U)
#define CAN_F13R1_FB18_Msk     (0x1UL << CAN_F13R1_FB18_Pos)                    /*!< 0x00040000 */
#define CAN_F13R1_FB18         CAN_F13R1_FB18_Msk                              /*!<Filter bit 18 */
#define CAN_F13R1_FB19_Pos     (19U)
#define CAN_F13R1_FB19_Msk     (0x1UL << CAN_F13R1_FB19_Pos)                    /*!< 0x00080000 */
#define CAN_F13R1_FB19         CAN_F13R1_FB19_Msk                              /*!<Filter bit 19 */
#define CAN_F13R1_FB20_Pos     (20U)
#define CAN_F13R1_FB20_Msk     (0x1UL << CAN_F13R1_FB20_Pos)                    /*!< 0x00100000 */
#define CAN_F13R1_FB20         CAN_F13R1_FB20_Msk                              /*!<Filter bit 20 */
#define CAN_F13R1_FB21_Pos     (21U)
#define CAN_F13R1_FB21_Msk     (0x1UL << CAN_F13R1_FB21_Pos)                    /*!< 0x00200000 */
#define CAN_F13R1_FB21         CAN_F13R1_FB21_Msk                              /*!<Filter bit 21 */
#define CAN_F13R1_FB22_Pos     (22U)
#define CAN_F13R1_FB22_Msk     (0x1UL << CAN_F13R1_FB22_Pos)                    /*!< 0x00400000 */
#define CAN_F13R1_FB22         CAN_F13R1_FB22_Msk                              /*!<Filter bit 22 */
#define CAN_F13R1_FB23_Pos     (23U)
#define CAN_F13R1_FB23_Msk     (0x1UL << CAN_F13R1_FB23_Pos)                    /*!< 0x00800000 */
#define CAN_F13R1_FB23         CAN_F13R1_FB23_Msk                              /*!<Filter bit 23 */
#define CAN_F13R1_FB24_Pos     (24U)
#define CAN_F13R1_FB24_Msk     (0x1UL << CAN_F13R1_FB24_Pos)                    /*!< 0x01000000 */
#define CAN_F13R1_FB24         CAN_F13R1_FB24_Msk                              /*!<Filter bit 24 */
#define CAN_F13R1_FB25_Pos     (25U)
#define CAN_F13R1_FB25_Msk     (0x1UL << CAN_F13R1_FB25_Pos)                    /*!< 0x02000000 */
#define CAN_F13R1_FB25         CAN_F13R1_FB25_Msk                              /*!<Filter bit 25 */
#define CAN_F13R1_FB26_Pos     (26U)
#define CAN_F13R1_FB26_Msk     (0x1UL << CAN_F13R1_FB26_Pos)                    /*!< 0x04000000 */
#define CAN_F13R1_FB26         CAN_F13R1_FB26_Msk                              /*!<Filter bit 26 */
#define CAN_F13R1_FB27_Pos     (27U)
#define CAN_F13R1_FB27_Msk     (0x1UL << CAN_F13R1_FB27_Pos)                    /*!< 0x08000000 */
#define CAN_F13R1_FB27         CAN_F13R1_FB27_Msk                              /*!<Filter bit 27 */
#define CAN_F13R1_FB28_Pos     (28U)
#define CAN_F13R1_FB28_Msk     (0x1UL << CAN_F13R1_FB28_Pos)                    /*!< 0x10000000 */
#define CAN_F13R1_FB28         CAN_F13R1_FB28_Msk                              /*!<Filter bit 28 */
#define CAN_F13R1_FB29_Pos     (29U)
#define CAN_F13R1_FB29_Msk     (0x1UL << CAN_F13R1_FB29_Pos)                    /*!< 0x20000000 */
#define CAN_F13R1_FB29         CAN_F13R1_FB29_Msk                              /*!<Filter bit 29 */
#define CAN_F13R1_FB30_Pos     (30U)
#define CAN_F13R1_FB30_Msk     (0x1UL << CAN_F13R1_FB30_Pos)                    /*!< 0x40000000 */
#define CAN_F13R1_FB30         CAN_F13R1_FB30_Msk                              /*!<Filter bit 30 */
#define CAN_F13R1_FB31_Pos     (31U)
#define CAN_F13R1_FB31_Msk     (0x1UL << CAN_F13R1_FB31_Pos)                    /*!< 0x80000000 */
#define CAN_F13R1_FB31         CAN_F13R1_FB31_Msk                              /*!<Filter bit 31 */

/*******************  Bit definition for CAN_F0R2 register  *******************/
#define CAN_F0R2_FB0_Pos       (0U)
#define CAN_F0R2_FB0_Msk       (0x1UL << CAN_F0R2_FB0_Pos)                      /*!< 0x00000001 */
#define CAN_F0R2_FB0           CAN_F0R2_FB0_Msk                                /*!<Filter bit 0 */
#define CAN_F0R2_FB1_Pos       (1U)
#define CAN_F0R2_FB1_Msk       (0x1UL << CAN_F0R2_FB1_Pos)                      /*!< 0x00000002 */
#define CAN_F0R2_FB1           CAN_F0R2_FB1_Msk                                /*!<Filter bit 1 */
#define CAN_F0R2_FB2_Pos       (2U)
#define CAN_F0R2_FB2_Msk       (0x1UL << CAN_F0R2_FB2_Pos)                      /*!< 0x00000004 */
#define CAN_F0R2_FB2           CAN_F0R2_FB2_Msk                                /*!<Filter bit 2 */
#define CAN_F0R2_FB3_Pos       (3U)
#define CAN_F0R2_FB3_Msk       (0x1UL << CAN_F0R2_FB3_Pos)                      /*!< 0x00000008 */
#define CAN_F0R2_FB3           CAN_F0R2_FB3_Msk                                /*!<Filter bit 3 */
#define CAN_F0R2_FB4_Pos       (4U)
#define CAN_F0R2_FB4_Msk       (0x1UL << CAN_F0R2_FB4_Pos)                      /*!< 0x00000010 */
#define CAN_F0R2_FB4           CAN_F0R2_FB4_Msk                                /*!<Filter bit 4 */
#define CAN_F0R2_FB5_Pos       (5U)
#define CAN_F0R2_FB5_Msk       (0x1UL << CAN_F0R2_FB5_Pos)                      /*!< 0x00000020 */
#define CAN_F0R2_FB5           CAN_F0R2_FB5_Msk                                /*!<Filter bit 5 */
#define CAN_F0R2_FB6_Pos       (6U)
#define CAN_F0R2_FB6_Msk       (0x1UL << CAN_F0R2_FB6_Pos)                      /*!< 0x00000040 */
#define CAN_F0R2_FB6           CAN_F0R2_FB6_Msk                                /*!<Filter bit 6 */
#define CAN_F0R2_FB7_Pos       (7U)
#define CAN_F0R2_FB7_Msk       (0x1UL << CAN_F0R2_FB7_Pos)                      /*!< 0x00000080 */
#define CAN_F0R2_FB7           CAN_F0R2_FB7_Msk                                /*!<Filter bit 7 */
#define CAN_F0R2_FB8_Pos       (8U)
#define CAN_F0R2_FB8_Msk       (0x1UL << CAN_F0R2_FB8_Pos)                      /*!< 0x00000100 */
#define CAN_F0R2_FB8           CAN_F0R2_FB8_Msk                                /*!<Filter bit 8 */
#define CAN_F0R2_FB9_Pos       (9U)
#define CAN_F0R2_FB9_Msk       (0x1UL << CAN_F0R2_FB9_Pos)                      /*!< 0x00000200 */
#define CAN_F0R2_FB9           CAN_F0R2_FB9_Msk                                /*!<Filter bit 9 */
#define CAN_F0R2_FB10_Pos      (10U)
#define CAN_F0R2_FB10_Msk      (0x1UL << CAN_F0R2_FB10_Pos)                     /*!< 0x00000400 */
#define CAN_F0R2_FB10          CAN_F0R2_FB10_Msk                               /*!<Filter bit 10 */
#define CAN_F0R2_FB11_Pos      (11U)
#define CAN_F0R2_FB11_Msk      (0x1UL << CAN_F0R2_FB11_Pos)                     /*!< 0x00000800 */
#define CAN_F0R2_FB11          CAN_F0R2_FB11_Msk                               /*!<Filter bit 11 */
#define CAN_F0R2_FB12_Pos      (12U)
#define CAN_F0R2_FB12_Msk      (0x1UL << CAN_F0R2_FB12_Pos)                     /*!< 0x00001000 */
#define CAN_F0R2_FB12          CAN_F0R2_FB12_Msk                               /*!<Filter bit 12 */
#define CAN_F0R2_FB13_Pos      (13U)
#define CAN_F0R2_FB13_Msk      (0x1UL << CAN_F0R2_FB13_Pos)                     /*!< 0x00002000 */
#define CAN_F0R2_FB13          CAN_F0R2_FB13_Msk                               /*!<Filter bit 13 */
#define CAN_F0R2_FB14_Pos      (14U)
#define CAN_F0R2_FB14_Msk      (0x1UL << CAN_F0R2_FB14_Pos)                     /*!< 0x00004000 */
#define CAN_F0R2_FB14          CAN_F0R2_FB14_Msk                               /*!<Filter bit 14 */
#define CAN_F0R2_FB15_Pos      (15U)
#define CAN_F0R2_FB15_Msk      (0x1UL << CAN_F0R2_FB15_Pos)                     /*!< 0x00008000 */
#define CAN_F0R2_FB15          CAN_F0R2_FB15_Msk                               /*!<Filter bit 15 */
#define CAN_F0R2_FB16_Pos      (16U)
#define CAN_F0R2_FB16_Msk      (0x1UL << CAN_F0R2_FB16_Pos)                     /*!< 0x00010000 */
#define CAN_F0R2_FB16          CAN_F0R2_FB16_Msk                               /*!<Filter bit 16 */
#define CAN_F0R2_FB17_Pos      (17U)
#define CAN_F0R2_FB17_Msk      (0x1UL << CAN_F0R2_FB17_Pos)                     /*!< 0x00020000 */
#define CAN_F0R2_FB17          CAN_F0R2_FB17_Msk                               /*!<Filter bit 17 */
#define CAN_F0R2_FB18_Pos      (18U)
#define CAN_F0R2_FB18_Msk      (0x1UL << CAN_F0R2_FB18_Pos)                     /*!< 0x00040000 */
#define CAN_F0R2_FB18          CAN_F0R2_FB18_Msk                               /*!<Filter bit 18 */
#define CAN_F0R2_FB19_Pos      (19U)
#define CAN_F0R2_FB19_Msk      (0x1UL << CAN_F0R2_FB19_Pos)                     /*!< 0x00080000 */
#define CAN_F0R2_FB19          CAN_F0R2_FB19_Msk                               /*!<Filter bit 19 */
#define CAN_F0R2_FB20_Pos      (20U)
#define CAN_F0R2_FB20_Msk      (0x1UL << CAN_F0R2_FB20_Pos)                     /*!< 0x00100000 */
#define CAN_F0R2_FB20          CAN_F0R2_FB20_Msk                               /*!<Filter bit 20 */
#define CAN_F0R2_FB21_Pos      (21U)
#define CAN_F0R2_FB21_Msk      (0x1UL << CAN_F0R2_FB21_Pos)                     /*!< 0x00200000 */
#define CAN_F0R2_FB21          CAN_F0R2_FB21_Msk                               /*!<Filter bit 21 */
#define CAN_F0R2_FB22_Pos      (22U)
#define CAN_F0R2_FB22_Msk      (0x1UL << CAN_F0R2_FB22_Pos)                     /*!< 0x00400000 */
#define CAN_F0R2_FB22          CAN_F0R2_FB22_Msk                               /*!<Filter bit 22 */
#define CAN_F0R2_FB23_Pos      (23U)
#define CAN_F0R2_FB23_Msk      (0x1UL << CAN_F0R2_FB23_Pos)                     /*!< 0x00800000 */
#define CAN_F0R2_FB23          CAN_F0R2_FB23_Msk                               /*!<Filter bit 23 */
#define CAN_F0R2_FB24_Pos      (24U)
#define CAN_F0R2_FB24_Msk      (0x1UL << CAN_F0R2_FB24_Pos)                     /*!< 0x01000000 */
#define CAN_F0R2_FB24          CAN_F0R2_FB24_Msk                               /*!<Filter bit 24 */
#define CAN_F0R2_FB25_Pos      (25U)
#define CAN_F0R2_FB25_Msk      (0x1UL << CAN_F0R2_FB25_Pos)                     /*!< 0x02000000 */
#define CAN_F0R2_FB25          CAN_F0R2_FB25_Msk                               /*!<Filter bit 25 */
#define CAN_F0R2_FB26_Pos      (26U)
#define CAN_F0R2_FB26_Msk      (0x1UL << CAN_F0R2_FB26_Pos)                     /*!< 0x04000000 */
#define CAN_F0R2_FB26          CAN_F0R2_FB26_Msk                               /*!<Filter bit 26 */
#define CAN_F0R2_FB27_Pos      (27U)
#define CAN_F0R2_FB27_Msk      (0x1UL << CAN_F0R2_FB27_Pos)                     /*!< 0x08000000 */
#define CAN_F0R2_FB27          CAN_F0R2_FB27_Msk                               /*!<Filter bit 27 */
#define CAN_F0R2_FB28_Pos      (28U)
#define CAN_F0R2_FB28_Msk      (0x1UL << CAN_F0R2_FB28_Pos)                     /*!< 0x10000000 */
#define CAN_F0R2_FB28          CAN_F0R2_FB28_Msk                               /*!<Filter bit 28 */
#define CAN_F0R2_FB29_Pos      (29U)
#define CAN_F0R2_FB29_Msk      (0x1UL << CAN_F0R2_FB29_Pos)                     /*!< 0x20000000 */
#define CAN_F0R2_FB29          CAN_F0R2_FB29_Msk                               /*!<Filter bit 29 */
#define CAN_F0R2_FB30_Pos      (30U)
#define CAN_F0R2_FB30_Msk      (0x1UL << CAN_F0R2_FB30_Pos)                     /*!< 0x40000000 */
#define CAN_F0R2_FB30          CAN_F0R2_FB30_Msk                               /*!<Filter bit 30 */
#define CAN_F0R2_FB31_Pos      (31U)
#define CAN_F0R2_FB31_Msk      (0x1UL << CAN_F0R2_FB31_Pos)                     /*!< 0x80000000 */
#define CAN_F0R2_FB31          CAN_F0R2_FB31_Msk                               /*!<Filter bit 31 */

/*******************  Bit definition for CAN_F1R2 register  *******************/
#define CAN_F1R2_FB0_Pos       (0U)
#define CAN_F1R2_FB0_Msk       (0x1UL << CAN_F1R2_FB0_Pos)                      /*!< 0x00000001 */
#define CAN_F1R2_FB0           CAN_F1R2_FB0_Msk                                /*!<Filter bit 0 */
#define CAN_F1R2_FB1_Pos       (1U)
#define CAN_F1R2_FB1_Msk       (0x1UL << CAN_F1R2_FB1_Pos)                      /*!< 0x00000002 */
#define CAN_F1R2_FB1           CAN_F1R2_FB1_Msk                                /*!<Filter bit 1 */
#define CAN_F1R2_FB2_Pos       (2U)
#define CAN_F1R2_FB2_Msk       (0x1UL << CAN_F1R2_FB2_Pos)                      /*!< 0x00000004 */
#define CAN_F1R2_FB2           CAN_F1R2_FB2_Msk                                /*!<Filter bit 2 */
#define CAN_F1R2_FB3_Pos       (3U)
#define CAN_F1R2_FB3_Msk       (0x1UL << CAN_F1R2_FB3_Pos)                      /*!< 0x00000008 */
#define CAN_F1R2_FB3           CAN_F1R2_FB3_Msk                                /*!<Filter bit 3 */
#define CAN_F1R2_FB4_Pos       (4U)
#define CAN_F1R2_FB4_Msk       (0x1UL << CAN_F1R2_FB4_Pos)                      /*!< 0x00000010 */
#define CAN_F1R2_FB4           CAN_F1R2_FB4_Msk                                /*!<Filter bit 4 */
#define CAN_F1R2_FB5_Pos       (5U)
#define CAN_F1R2_FB5_Msk       (0x1UL << CAN_F1R2_FB5_Pos)                      /*!< 0x00000020 */
#define CAN_F1R2_FB5           CAN_F1R2_FB5_Msk                                /*!<Filter bit 5 */
#define CAN_F1R2_FB6_Pos       (6U)
#define CAN_F1R2_FB6_Msk       (0x1UL << CAN_F1R2_FB6_Pos)                      /*!< 0x00000040 */
#define CAN_F1R2_FB6           CAN_F1R2_FB6_Msk                                /*!<Filter bit 6 */
#define CAN_F1R2_FB7_Pos       (7U)
#define CAN_F1R2_FB7_Msk       (0x1UL << CAN_F1R2_FB7_Pos)                      /*!< 0x00000080 */
#define CAN_F1R2_FB7           CAN_F1R2_FB7_Msk                                /*!<Filter bit 7 */
#define CAN_F1R2_FB8_Pos       (8U)
#define CAN_F1R2_FB8_Msk       (0x1UL << CAN_F1R2_FB8_Pos)                      /*!< 0x00000100 */
#define CAN_F1R2_FB8           CAN_F1R2_FB8_Msk                                /*!<Filter bit 8 */
#define CAN_F1R2_FB9_Pos       (9U)
#define CAN_F1R2_FB9_Msk       (0x1UL << CAN_F1R2_FB9_Pos)                      /*!< 0x00000200 */
#define CAN_F1R2_FB9           CAN_F1R2_FB9_Msk                                /*!<Filter bit 9 */
#define CAN_F1R2_FB10_Pos      (10U)
#define CAN_F1R2_FB10_Msk      (0x1UL << CAN_F1R2_FB10_Pos)                     /*!< 0x00000400 */
#define CAN_F1R2_FB10          CAN_F1R2_FB10_Msk                               /*!<Filter bit 10 */
#define CAN_F1R2_FB11_Pos      (11U)
#define CAN_F1R2_FB11_Msk      (0x1UL << CAN_F1R2_FB11_Pos)                     /*!< 0x00000800 */
#define CAN_F1R2_FB11          CAN_F1R2_FB11_Msk                               /*!<Filter bit 11 */
#define CAN_F1R2_FB12_Pos      (12U)
#define CAN_F1R2_FB12_Msk      (0x1UL << CAN_F1R2_FB12_Pos)                     /*!< 0x00001000 */
#define CAN_F1R2_FB12          CAN_F1R2_FB12_Msk                               /*!<Filter bit 12 */
#define CAN_F1R2_FB13_Pos      (13U)
#define CAN_F1R2_FB13_Msk      (0x1UL << CAN_F1R2_FB13_Pos)                     /*!< 0x00002000 */
#define CAN_F1R2_FB13          CAN_F1R2_FB13_Msk                               /*!<Filter bit 13 */
#define CAN_F1R2_FB14_Pos      (14U)
#define CAN_F1R2_FB14_Msk      (0x1UL << CAN_F1R2_FB14_Pos)                     /*!< 0x00004000 */
#define CAN_F1R2_FB14          CAN_F1R2_FB14_Msk                               /*!<Filter bit 14 */
#define CAN_F1R2_FB15_Pos      (15U)
#define CAN_F1R2_FB15_Msk      (0x1UL << CAN_F1R2_FB15_Pos)                     /*!< 0x00008000 */
#define CAN_F1R2_FB15          CAN_F1R2_FB15_Msk                               /*!<Filter bit 15 */
#define CAN_F1R2_FB16_Pos      (16U)
#define CAN_F1R2_FB16_Msk      (0x1UL << CAN_F1R2_FB16_Pos)                     /*!< 0x00010000 */
#define CAN_F1R2_FB16          CAN_F1R2_FB16_Msk                               /*!<Filter bit 16 */
#define CAN_F1R2_FB17_Pos      (17U)
#define CAN_F1R2_FB17_Msk      (0x1UL << CAN_F1R2_FB17_Pos)                     /*!< 0x00020000 */
#define CAN_F1R2_FB17          CAN_F1R2_FB17_Msk                               /*!<Filter bit 17 */
#define CAN_F1R2_FB18_Pos      (18U)
#define CAN_F1R2_FB18_Msk      (0x1UL << CAN_F1R2_FB18_Pos)                     /*!< 0x00040000 */
#define CAN_F1R2_FB18          CAN_F1R2_FB18_Msk                               /*!<Filter bit 18 */
#define CAN_F1R2_FB19_Pos      (19U)
#define CAN_F1R2_FB19_Msk      (0x1UL << CAN_F1R2_FB19_Pos)                     /*!< 0x00080000 */
#define CAN_F1R2_FB19          CAN_F1R2_FB19_Msk                               /*!<Filter bit 19 */
#define CAN_F1R2_FB20_Pos      (20U)
#define CAN_F1R2_FB20_Msk      (0x1UL << CAN_F1R2_FB20_Pos)                     /*!< 0x00100000 */
#define CAN_F1R2_FB20          CAN_F1R2_FB20_Msk                               /*!<Filter bit 20 */
#define CAN_F1R2_FB21_Pos      (21U)
#define CAN_F1R2_FB21_Msk      (0x1UL << CAN_F1R2_FB21_Pos)                     /*!< 0x00200000 */
#define CAN_F1R2_FB21          CAN_F1R2_FB21_Msk                               /*!<Filter bit 21 */
#define CAN_F1R2_FB22_Pos      (22U)
#define CAN_F1R2_FB22_Msk      (0x1UL << CAN_F1R2_FB22_Pos)                     /*!< 0x00400000 */
#define CAN_F1R2_FB22          CAN_F1R2_FB22_Msk                               /*!<Filter bit 22 */
#define CAN_F1R2_FB23_Pos      (23U)
#define CAN_F1R2_FB23_Msk      (0x1UL << CAN_F1R2_FB23_Pos)                     /*!< 0x00800000 */
#define CAN_F1R2_FB23          CAN_F1R2_FB23_Msk                               /*!<Filter bit 23 */
#define CAN_F1R2_FB24_Pos      (24U)
#define CAN_F1R2_FB24_Msk      (0x1UL << CAN_F1R2_FB24_Pos)                     /*!< 0x01000000 */
#define CAN_F1R2_FB24          CAN_F1R2_FB24_Msk                               /*!<Filter bit 24 */
#define CAN_F1R2_FB25_Pos      (25U)
#define CAN_F1R2_FB25_Msk      (0x1UL << CAN_F1R2_FB25_Pos)                     /*!< 0x02000000 */
#define CAN_F1R2_FB25          CAN_F1R2_FB25_Msk                               /*!<Filter bit 25 */
#define CAN_F1R2_FB26_Pos      (26U)
#define CAN_F1R2_FB26_Msk      (0x1UL << CAN_F1R2_FB26_Pos)                     /*!< 0x04000000 */
#define CAN_F1R2_FB26          CAN_F1R2_FB26_Msk                               /*!<Filter bit 26 */
#define CAN_F1R2_FB27_Pos      (27U)
#define CAN_F1R2_FB27_Msk      (0x1UL << CAN_F1R2_FB27_Pos)                     /*!< 0x08000000 */
#define CAN_F1R2_FB27          CAN_F1R2_FB27_Msk                               /*!<Filter bit 27 */
#define CAN_F1R2_FB28_Pos      (28U)
#define CAN_F1R2_FB28_Msk      (0x1UL << CAN_F1R2_FB28_Pos)                     /*!< 0x10000000 */
#define CAN_F1R2_FB28          CAN_F1R2_FB28_Msk                               /*!<Filter bit 28 */
#define CAN_F1R2_FB29_Pos      (29U)
#define CAN_F1R2_FB29_Msk      (0x1UL << CAN_F1R2_FB29_Pos)                     /*!< 0x20000000 */
#define CAN_F1R2_FB29          CAN_F1R2_FB29_Msk                               /*!<Filter bit 29 */
#define CAN_F1R2_FB30_Pos      (30U)
#define CAN_F1R2_FB30_Msk      (0x1UL << CAN_F1R2_FB30_Pos)                     /*!< 0x40000000 */
#define CAN_F1R2_FB30          CAN_F1R2_FB30_Msk                               /*!<Filter bit 30 */
#define CAN_F1R2_FB31_Pos      (31U)
#define CAN_F1R2_FB31_Msk      (0x1UL << CAN_F1R2_FB31_Pos)                     /*!< 0x80000000 */
#define CAN_F1R2_FB31          CAN_F1R2_FB31_Msk                               /*!<Filter bit 31 */

/*******************  Bit definition for CAN_F2R2 register  *******************/
#define CAN_F2R2_FB0_Pos       (0U)
#define CAN_F2R2_FB0_Msk       (0x1UL << CAN_F2R2_FB0_Pos)                      /*!< 0x00000001 */
#define CAN_F2R2_FB0           CAN_F2R2_FB0_Msk                                /*!<Filter bit 0 */
#define CAN_F2R2_FB1_Pos       (1U)
#define CAN_F2R2_FB1_Msk       (0x1UL << CAN_F2R2_FB1_Pos)                      /*!< 0x00000002 */
#define CAN_F2R2_FB1           CAN_F2R2_FB1_Msk                                /*!<Filter bit 1 */
#define CAN_F2R2_FB2_Pos       (2U)
#define CAN_F2R2_FB2_Msk       (0x1UL << CAN_F2R2_FB2_Pos)                      /*!< 0x00000004 */
#define CAN_F2R2_FB2           CAN_F2R2_FB2_Msk                                /*!<Filter bit 2 */
#define CAN_F2R2_FB3_Pos       (3U)
#define CAN_F2R2_FB3_Msk       (0x1UL << CAN_F2R2_FB3_Pos)                      /*!< 0x00000008 */
#define CAN_F2R2_FB3           CAN_F2R2_FB3_Msk                                /*!<Filter bit 3 */
#define CAN_F2R2_FB4_Pos       (4U)
#define CAN_F2R2_FB4_Msk       (0x1UL << CAN_F2R2_FB4_Pos)                      /*!< 0x00000010 */
#define CAN_F2R2_FB4           CAN_F2R2_FB4_Msk                                /*!<Filter bit 4 */
#define CAN_F2R2_FB5_Pos       (5U)
#define CAN_F2R2_FB5_Msk       (0x1UL << CAN_F2R2_FB5_Pos)                      /*!< 0x00000020 */
#define CAN_F2R2_FB5           CAN_F2R2_FB5_Msk                                /*!<Filter bit 5 */
#define CAN_F2R2_FB6_Pos       (6U)
#define CAN_F2R2_FB6_Msk       (0x1UL << CAN_F2R2_FB6_Pos)                      /*!< 0x00000040 */
#define CAN_F2R2_FB6           CAN_F2R2_FB6_Msk                                /*!<Filter bit 6 */
#define CAN_F2R2_FB7_Pos       (7U)
#define CAN_F2R2_FB7_Msk       (0x1UL << CAN_F2R2_FB7_Pos)                      /*!< 0x00000080 */
#define CAN_F2R2_FB7           CAN_F2R2_FB7_Msk                                /*!<Filter bit 7 */
#define CAN_F2R2_FB8_Pos       (8U)
#define CAN_F2R2_FB8_Msk       (0x1UL << CAN_F2R2_FB8_Pos)                      /*!< 0x00000100 */
#define CAN_F2R2_FB8           CAN_F2R2_FB8_Msk                                /*!<Filter bit 8 */
#define CAN_F2R2_FB9_Pos       (9U)
#define CAN_F2R2_FB9_Msk       (0x1UL << CAN_F2R2_FB9_Pos)                      /*!< 0x00000200 */
#define CAN_F2R2_FB9           CAN_F2R2_FB9_Msk                                /*!<Filter bit 9 */
#define CAN_F2R2_FB10_Pos      (10U)
#define CAN_F2R2_FB10_Msk      (0x1UL << CAN_F2R2_FB10_Pos)                     /*!< 0x00000400 */
#define CAN_F2R2_FB10          CAN_F2R2_FB10_Msk                               /*!<Filter bit 10 */
#define CAN_F2R2_FB11_Pos      (11U)
#define CAN_F2R2_FB11_Msk      (0x1UL << CAN_F2R2_FB11_Pos)                     /*!< 0x00000800 */
#define CAN_F2R2_FB11          CAN_F2R2_FB11_Msk                               /*!<Filter bit 11 */
#define CAN_F2R2_FB12_Pos      (12U)
#define CAN_F2R2_FB12_Msk      (0x1UL << CAN_F2R2_FB12_Pos)                     /*!< 0x00001000 */
#define CAN_F2R2_FB12          CAN_F2R2_FB12_Msk                               /*!<Filter bit 12 */
#define CAN_F2R2_FB13_Pos      (13U)
#define CAN_F2R2_FB13_Msk      (0x1UL << CAN_F2R2_FB13_Pos)                     /*!< 0x00002000 */
#define CAN_F2R2_FB13          CAN_F2R2_FB13_Msk                               /*!<Filter bit 13 */
#define CAN_F2R2_FB14_Pos      (14U)
#define CAN_F2R2_FB14_Msk      (0x1UL << CAN_F2R2_FB14_Pos)                     /*!< 0x00004000 */
#define CAN_F2R2_FB14          CAN_F2R2_FB14_Msk                               /*!<Filter bit 14 */
#define CAN_F2R2_FB15_Pos      (15U)
#define CAN_F2R2_FB15_Msk      (0x1UL << CAN_F2R2_FB15_Pos)                     /*!< 0x00008000 */
#define CAN_F2R2_FB15          CAN_F2R2_FB15_Msk                               /*!<Filter bit 15 */
#define CAN_F2R2_FB16_Pos      (16U)
#define CAN_F2R2_FB16_Msk      (0x1UL << CAN_F2R2_FB16_Pos)                     /*!< 0x00010000 */
#define CAN_F2R2_FB16          CAN_F2R2_FB16_Msk                               /*!<Filter bit 16 */
#define CAN_F2R2_FB17_Pos      (17U)
#define CAN_F2R2_FB17_Msk      (0x1UL << CAN_F2R2_FB17_Pos)                     /*!< 0x00020000 */
#define CAN_F2R2_FB17          CAN_F2R2_FB17_Msk                               /*!<Filter bit 17 */
#define CAN_F2R2_FB18_Pos      (18U)
#define CAN_F2R2_FB18_Msk      (0x1UL << CAN_F2R2_FB18_Pos)                     /*!< 0x00040000 */
#define CAN_F2R2_FB18          CAN_F2R2_FB18_Msk                               /*!<Filter bit 18 */
#define CAN_F2R2_FB19_Pos      (19U)
#define CAN_F2R2_FB19_Msk      (0x1UL << CAN_F2R2_FB19_Pos)                     /*!< 0x00080000 */
#define CAN_F2R2_FB19          CAN_F2R2_FB19_Msk                               /*!<Filter bit 19 */
#define CAN_F2R2_FB20_Pos      (20U)
#define CAN_F2R2_FB20_Msk      (0x1UL << CAN_F2R2_FB20_Pos)                     /*!< 0x00100000 */
#define CAN_F2R2_FB20          CAN_F2R2_FB20_Msk                               /*!<Filter bit 20 */
#define CAN_F2R2_FB21_Pos      (21U)
#define CAN_F2R2_FB21_Msk      (0x1UL << CAN_F2R2_FB21_Pos)                     /*!< 0x00200000 */
#define CAN_F2R2_FB21          CAN_F2R2_FB21_Msk                               /*!<Filter bit 21 */
#define CAN_F2R2_FB22_Pos      (22U)
#define CAN_F2R2_FB22_Msk      (0x1UL << CAN_F2R2_FB22_Pos)                     /*!< 0x00400000 */
#define CAN_F2R2_FB22          CAN_F2R2_FB22_Msk                               /*!<Filter bit 22 */
#define CAN_F2R2_FB23_Pos      (23U)
#define CAN_F2R2_FB23_Msk      (0x1UL << CAN_F2R2_FB23_Pos)                     /*!< 0x00800000 */
#define CAN_F2R2_FB23          CAN_F2R2_FB23_Msk                               /*!<Filter bit 23 */
#define CAN_F2R2_FB24_Pos      (24U)
#define CAN_F2R2_FB24_Msk      (0x1UL << CAN_F2R2_FB24_Pos)                     /*!< 0x01000000 */
#define CAN_F2R2_FB24          CAN_F2R2_FB24_Msk                               /*!<Filter bit 24 */
#define CAN_F2R2_FB25_Pos      (25U)
#define CAN_F2R2_FB25_Msk      (0x1UL << CAN_F2R2_FB25_Pos)                     /*!< 0x02000000 */
#define CAN_F2R2_FB25          CAN_F2R2_FB25_Msk                               /*!<Filter bit 25 */
#define CAN_F2R2_FB26_Pos      (26U)
#define CAN_F2R2_FB26_Msk      (0x1UL << CAN_F2R2_FB26_Pos)                     /*!< 0x04000000 */
#define CAN_F2R2_FB26          CAN_F2R2_FB26_Msk                               /*!<Filter bit 26 */
#define CAN_F2R2_FB27_Pos      (27U)
#define CAN_F2R2_FB27_Msk      (0x1UL << CAN_F2R2_FB27_Pos)                     /*!< 0x08000000 */
#define CAN_F2R2_FB27          CAN_F2R2_FB27_Msk                               /*!<Filter bit 27 */
#define CAN_F2R2_FB28_Pos      (28U)
#define CAN_F2R2_FB28_Msk      (0x1UL << CAN_F2R2_FB28_Pos)                     /*!< 0x10000000 */
#define CAN_F2R2_FB28          CAN_F2R2_FB28_Msk                               /*!<Filter bit 28 */
#define CAN_F2R2_FB29_Pos      (29U)
#define CAN_F2R2_FB29_Msk      (0x1UL << CAN_F2R2_FB29_Pos)                     /*!< 0x20000000 */
#define CAN_F2R2_FB29          CAN_F2R2_FB29_Msk                               /*!<Filter bit 29 */
#define CAN_F2R2_FB30_Pos      (30U)
#define CAN_F2R2_FB30_Msk      (0x1UL << CAN_F2R2_FB30_Pos)                     /*!< 0x40000000 */
#define CAN_F2R2_FB30          CAN_F2R2_FB30_Msk                               /*!<Filter bit 30 */
#define CAN_F2R2_FB31_Pos      (31U)
#define CAN_F2R2_FB31_Msk      (0x1UL << CAN_F2R2_FB31_Pos)                     /*!< 0x80000000 */
#define CAN_F2R2_FB31          CAN_F2R2_FB31_Msk                               /*!<Filter bit 31 */

/*******************  Bit definition for CAN_F3R2 register  *******************/
#define CAN_F3R2_FB0_Pos       (0U)
#define CAN_F3R2_FB0_Msk       (0x1UL << CAN_F3R2_FB0_Pos)                      /*!< 0x00000001 */
#define CAN_F3R2_FB0           CAN_F3R2_FB0_Msk                                /*!<Filter bit 0 */
#define CAN_F3R2_FB1_Pos       (1U)
#define CAN_F3R2_FB1_Msk       (0x1UL << CAN_F3R2_FB1_Pos)                      /*!< 0x00000002 */
#define CAN_F3R2_FB1           CAN_F3R2_FB1_Msk                                /*!<Filter bit 1 */
#define CAN_F3R2_FB2_Pos       (2U)
#define CAN_F3R2_FB2_Msk       (0x1UL << CAN_F3R2_FB2_Pos)                      /*!< 0x00000004 */
#define CAN_F3R2_FB2           CAN_F3R2_FB2_Msk                                /*!<Filter bit 2 */
#define CAN_F3R2_FB3_Pos       (3U)
#define CAN_F3R2_FB3_Msk       (0x1UL << CAN_F3R2_FB3_Pos)                      /*!< 0x00000008 */
#define CAN_F3R2_FB3           CAN_F3R2_FB3_Msk                                /*!<Filter bit 3 */
#define CAN_F3R2_FB4_Pos       (4U)
#define CAN_F3R2_FB4_Msk       (0x1UL << CAN_F3R2_FB4_Pos)                      /*!< 0x00000010 */
#define CAN_F3R2_FB4           CAN_F3R2_FB4_Msk                                /*!<Filter bit 4 */
#define CAN_F3R2_FB5_Pos       (5U)
#define CAN_F3R2_FB5_Msk       (0x1UL << CAN_F3R2_FB5_Pos)                      /*!< 0x00000020 */
#define CAN_F3R2_FB5           CAN_F3R2_FB5_Msk                                /*!<Filter bit 5 */
#define CAN_F3R2_FB6_Pos       (6U)
#define CAN_F3R2_FB6_Msk       (0x1UL << CAN_F3R2_FB6_Pos)                      /*!< 0x00000040 */
#define CAN_F3R2_FB6           CAN_F3R2_FB6_Msk                                /*!<Filter bit 6 */
#define CAN_F3R2_FB7_Pos       (7U)
#define CAN_F3R2_FB7_Msk       (0x1UL << CAN_F3R2_FB7_Pos)                      /*!< 0x00000080 */
#define CAN_F3R2_FB7           CAN_F3R2_FB7_Msk                                /*!<Filter bit 7 */
#define CAN_F3R2_FB8_Pos       (8U)
#define CAN_F3R2_FB8_Msk       (0x1UL << CAN_F3R2_FB8_Pos)                      /*!< 0x00000100 */
#define CAN_F3R2_FB8           CAN_F3R2_FB8_Msk                                /*!<Filter bit 8 */
#define CAN_F3R2_FB9_Pos       (9U)
#define CAN_F3R2_FB9_Msk       (0x1UL << CAN_F3R2_FB9_Pos)                      /*!< 0x00000200 */
#define CAN_F3R2_FB9           CAN_F3R2_FB9_Msk                                /*!<Filter bit 9 */
#define CAN_F3R2_FB10_Pos      (10U)
#define CAN_F3R2_FB10_Msk      (0x1UL << CAN_F3R2_FB10_Pos)                     /*!< 0x00000400 */
#define CAN_F3R2_FB10          CAN_F3R2_FB10_Msk                               /*!<Filter bit 10 */
#define CAN_F3R2_FB11_Pos      (11U)
#define CAN_F3R2_FB11_Msk      (0x1UL << CAN_F3R2_FB11_Pos)                     /*!< 0x00000800 */
#define CAN_F3R2_FB11          CAN_F3R2_FB11_Msk                               /*!<Filter bit 11 */
#define CAN_F3R2_FB12_Pos      (12U)
#define CAN_F3R2_FB12_Msk      (0x1UL << CAN_F3R2_FB12_Pos)                     /*!< 0x00001000 */
#define CAN_F3R2_FB12          CAN_F3R2_FB12_Msk                               /*!<Filter bit 12 */
#define CAN_F3R2_FB13_Pos      (13U)
#define CAN_F3R2_FB13_Msk      (0x1UL << CAN_F3R2_FB13_Pos)                     /*!< 0x00002000 */
#define CAN_F3R2_FB13          CAN_F3R2_FB13_Msk                               /*!<Filter bit 13 */
#define CAN_F3R2_FB14_Pos      (14U)
#define CAN_F3R2_FB14_Msk      (0x1UL << CAN_F3R2_FB14_Pos)                     /*!< 0x00004000 */
#define CAN_F3R2_FB14          CAN_F3R2_FB14_Msk                               /*!<Filter bit 14 */
#define CAN_F3R2_FB15_Pos      (15U)
#define CAN_F3R2_FB15_Msk      (0x1UL << CAN_F3R2_FB15_Pos)                     /*!< 0x00008000 */
#define CAN_F3R2_FB15          CAN_F3R2_FB15_Msk                               /*!<Filter bit 15 */
#define CAN_F3R2_FB16_Pos      (16U)
#define CAN_F3R2_FB16_Msk      (0x1UL << CAN_F3R2_FB16_Pos)                     /*!< 0x00010000 */
#define CAN_F3R2_FB16          CAN_F3R2_FB16_Msk                               /*!<Filter bit 16 */
#define CAN_F3R2_FB17_Pos      (17U)
#define CAN_F3R2_FB17_Msk      (0x1UL << CAN_F3R2_FB17_Pos)                     /*!< 0x00020000 */
#define CAN_F3R2_FB17          CAN_F3R2_FB17_Msk                               /*!<Filter bit 17 */
#define CAN_F3R2_FB18_Pos      (18U)
#define CAN_F3R2_FB18_Msk      (0x1UL << CAN_F3R2_FB18_Pos)                     /*!< 0x00040000 */
#define CAN_F3R2_FB18          CAN_F3R2_FB18_Msk                               /*!<Filter bit 18 */
#define CAN_F3R2_FB19_Pos      (19U)
#define CAN_F3R2_FB19_Msk      (0x1UL << CAN_F3R2_FB19_Pos)                     /*!< 0x00080000 */
#define CAN_F3R2_FB19          CAN_F3R2_FB19_Msk                               /*!<Filter bit 19 */
#define CAN_F3R2_FB20_Pos      (20U)
#define CAN_F3R2_FB20_Msk      (0x1UL << CAN_F3R2_FB20_Pos)                     /*!< 0x00100000 */
#define CAN_F3R2_FB20          CAN_F3R2_FB20_Msk                               /*!<Filter bit 20 */
#define CAN_F3R2_FB21_Pos      (21U)
#define CAN_F3R2_FB21_Msk      (0x1UL << CAN_F3R2_FB21_Pos)                     /*!< 0x00200000 */
#define CAN_F3R2_FB21          CAN_F3R2_FB21_Msk                               /*!<Filter bit 21 */
#define CAN_F3R2_FB22_Pos      (22U)
#define CAN_F3R2_FB22_Msk      (0x1UL << CAN_F3R2_FB22_Pos)                     /*!< 0x00400000 */
#define CAN_F3R2_FB22          CAN_F3R2_FB22_Msk                               /*!<Filter bit 22 */
#define CAN_F3R2_FB23_Pos      (23U)
#define CAN_F3R2_FB23_Msk      (0x1UL << CAN_F3R2_FB23_Pos)                     /*!< 0x00800000 */
#define CAN_F3R2_FB23          CAN_F3R2_FB23_Msk                               /*!<Filter bit 23 */
#define CAN_F3R2_FB24_Pos      (24U)
#define CAN_F3R2_FB24_Msk      (0x1UL << CAN_F3R2_FB24_Pos)                     /*!< 0x01000000 */
#define CAN_F3R2_FB24          CAN_F3R2_FB24_Msk                               /*!<Filter bit 24 */
#define CAN_F3R2_FB25_Pos      (25U)
#define CAN_F3R2_FB25_Msk      (0x1UL << CAN_F3R2_FB25_Pos)                     /*!< 0x02000000 */
#define CAN_F3R2_FB25          CAN_F3R2_FB25_Msk                               /*!<Filter bit 25 */
#define CAN_F3R2_FB26_Pos      (26U)
#define CAN_F3R2_FB26_Msk      (0x1UL << CAN_F3R2_FB26_Pos)                     /*!< 0x04000000 */
#define CAN_F3R2_FB26          CAN_F3R2_FB26_Msk                               /*!<Filter bit 26 */
#define CAN_F3R2_FB27_Pos      (27U)
#define CAN_F3R2_FB27_Msk      (0x1UL << CAN_F3R2_FB27_Pos)                     /*!< 0x08000000 */
#define CAN_F3R2_FB27          CAN_F3R2_FB27_Msk                               /*!<Filter bit 27 */
#define CAN_F3R2_FB28_Pos      (28U)
#define CAN_F3R2_FB28_Msk      (0x1UL << CAN_F3R2_FB28_Pos)                     /*!< 0x10000000 */
#define CAN_F3R2_FB28          CAN_F3R2_FB28_Msk                               /*!<Filter bit 28 */
#define CAN_F3R2_FB29_Pos      (29U)
#define CAN_F3R2_FB29_Msk      (0x1UL << CAN_F3R2_FB29_Pos)                     /*!< 0x20000000 */
#define CAN_F3R2_FB29          CAN_F3R2_FB29_Msk                               /*!<Filter bit 29 */
#define CAN_F3R2_FB30_Pos      (30U)
#define CAN_F3R2_FB30_Msk      (0x1UL << CAN_F3R2_FB30_Pos)                     /*!< 0x40000000 */
#define CAN_F3R2_FB30          CAN_F3R2_FB30_Msk                               /*!<Filter bit 30 */
#define CAN_F3R2_FB31_Pos      (31U)
#define CAN_F3R2_FB31_Msk      (0x1UL << CAN_F3R2_FB31_Pos)                     /*!< 0x80000000 */
#define CAN_F3R2_FB31          CAN_F3R2_FB31_Msk                               /*!<Filter bit 31 */

/*******************  Bit definition for CAN_F4R2 register  *******************/
#define CAN_F4R2_FB0_Pos       (0U)
#define CAN_F4R2_FB0_Msk       (0x1UL << CAN_F4R2_FB0_Pos)                      /*!< 0x00000001 */
#define CAN_F4R2_FB0           CAN_F4R2_FB0_Msk                                /*!<Filter bit 0 */
#define CAN_F4R2_FB1_Pos       (1U)
#define CAN_F4R2_FB1_Msk       (0x1UL << CAN_F4R2_FB1_Pos)                      /*!< 0x00000002 */
#define CAN_F4R2_FB1           CAN_F4R2_FB1_Msk                                /*!<Filter bit 1 */
#define CAN_F4R2_FB2_Pos       (2U)
#define CAN_F4R2_FB2_Msk       (0x1UL << CAN_F4R2_FB2_Pos)                      /*!< 0x00000004 */
#define CAN_F4R2_FB2           CAN_F4R2_FB2_Msk                                /*!<Filter bit 2 */
#define CAN_F4R2_FB3_Pos       (3U)
#define CAN_F4R2_FB3_Msk       (0x1UL << CAN_F4R2_FB3_Pos)                      /*!< 0x00000008 */
#define CAN_F4R2_FB3           CAN_F4R2_FB3_Msk                                /*!<Filter bit 3 */
#define CAN_F4R2_FB4_Pos       (4U)
#define CAN_F4R2_FB4_Msk       (0x1UL << CAN_F4R2_FB4_Pos)                      /*!< 0x00000010 */
#define CAN_F4R2_FB4           CAN_F4R2_FB4_Msk                                /*!<Filter bit 4 */
#define CAN_F4R2_FB5_Pos       (5U)
#define CAN_F4R2_FB5_Msk       (0x1UL << CAN_F4R2_FB5_Pos)                      /*!< 0x00000020 */
#define CAN_F4R2_FB5           CAN_F4R2_FB5_Msk                                /*!<Filter bit 5 */
#define CAN_F4R2_FB6_Pos       (6U)
#define CAN_F4R2_FB6_Msk       (0x1UL << CAN_F4R2_FB6_Pos)                      /*!< 0x00000040 */
#define CAN_F4R2_FB6           CAN_F4R2_FB6_Msk                                /*!<Filter bit 6 */
#define CAN_F4R2_FB7_Pos       (7U)
#define CAN_F4R2_FB7_Msk       (0x1UL << CAN_F4R2_FB7_Pos)                      /*!< 0x00000080 */
#define CAN_F4R2_FB7           CAN_F4R2_FB7_Msk                                /*!<Filter bit 7 */
#define CAN_F4R2_FB8_Pos       (8U)
#define CAN_F4R2_FB8_Msk       (0x1UL << CAN_F4R2_FB8_Pos)                      /*!< 0x00000100 */
#define CAN_F4R2_FB8           CAN_F4R2_FB8_Msk                                /*!<Filter bit 8 */
#define CAN_F4R2_FB9_Pos       (9U)
#define CAN_F4R2_FB9_Msk       (0x1UL << CAN_F4R2_FB9_Pos)                      /*!< 0x00000200 */
#define CAN_F4R2_FB9           CAN_F4R2_FB9_Msk                                /*!<Filter bit 9 */
#define CAN_F4R2_FB10_Pos      (10U)
#define CAN_F4R2_FB10_Msk      (0x1UL << CAN_F4R2_FB10_Pos)                     /*!< 0x00000400 */
#define CAN_F4R2_FB10          CAN_F4R2_FB10_Msk                               /*!<Filter bit 10 */
#define CAN_F4R2_FB11_Pos      (11U)
#define CAN_F4R2_FB11_Msk      (0x1UL << CAN_F4R2_FB11_Pos)                     /*!< 0x00000800 */
#define CAN_F4R2_FB11          CAN_F4R2_FB11_Msk                               /*!<Filter bit 11 */
#define CAN_F4R2_FB12_Pos      (12U)
#define CAN_F4R2_FB12_Msk      (0x1UL << CAN_F4R2_FB12_Pos)                     /*!< 0x00001000 */
#define CAN_F4R2_FB12          CAN_F4R2_FB12_Msk                               /*!<Filter bit 12 */
#define CAN_F4R2_FB13_Pos      (13U)
#define CAN_F4R2_FB13_Msk      (0x1UL << CAN_F4R2_FB13_Pos)                     /*!< 0x00002000 */
#define CAN_F4R2_FB13          CAN_F4R2_FB13_Msk                               /*!<Filter bit 13 */
#define CAN_F4R2_FB14_Pos      (14U)
#define CAN_F4R2_FB14_Msk      (0x1UL << CAN_F4R2_FB14_Pos)                     /*!< 0x00004000 */
#define CAN_F4R2_FB14          CAN_F4R2_FB14_Msk                               /*!<Filter bit 14 */
#define CAN_F4R2_FB15_Pos      (15U)
#define CAN_F4R2_FB15_Msk      (0x1UL << CAN_F4R2_FB15_Pos)                     /*!< 0x00008000 */
#define CAN_F4R2_FB15          CAN_F4R2_FB15_Msk                               /*!<Filter bit 15 */
#define CAN_F4R2_FB16_Pos      (16U)
#define CAN_F4R2_FB16_Msk      (0x1UL << CAN_F4R2_FB16_Pos)                     /*!< 0x00010000 */
#define CAN_F4R2_FB16          CAN_F4R2_FB16_Msk                               /*!<Filter bit 16 */
#define CAN_F4R2_FB17_Pos      (17U)
#define CAN_F4R2_FB17_Msk      (0x1UL << CAN_F4R2_FB17_Pos)                     /*!< 0x00020000 */
#define CAN_F4R2_FB17          CAN_F4R2_FB17_Msk                               /*!<Filter bit 17 */
#define CAN_F4R2_FB18_Pos      (18U)
#define CAN_F4R2_FB18_Msk      (0x1UL << CAN_F4R2_FB18_Pos)                     /*!< 0x00040000 */
#define CAN_F4R2_FB18          CAN_F4R2_FB18_Msk                               /*!<Filter bit 18 */
#define CAN_F4R2_FB19_Pos      (19U)
#define CAN_F4R2_FB19_Msk      (0x1UL << CAN_F4R2_FB19_Pos)                     /*!< 0x00080000 */
#define CAN_F4R2_FB19          CAN_F4R2_FB19_Msk                               /*!<Filter bit 19 */
#define CAN_F4R2_FB20_Pos      (20U)
#define CAN_F4R2_FB20_Msk      (0x1UL << CAN_F4R2_FB20_Pos)                     /*!< 0x00100000 */
#define CAN_F4R2_FB20          CAN_F4R2_FB20_Msk                               /*!<Filter bit 20 */
#define CAN_F4R2_FB21_Pos      (21U)
#define CAN_F4R2_FB21_Msk      (0x1UL << CAN_F4R2_FB21_Pos)                     /*!< 0x00200000 */
#define CAN_F4R2_FB21          CAN_F4R2_FB21_Msk                               /*!<Filter bit 21 */
#define CAN_F4R2_FB22_Pos      (22U)
#define CAN_F4R2_FB22_Msk      (0x1UL << CAN_F4R2_FB22_Pos)                     /*!< 0x00400000 */
#define CAN_F4R2_FB22          CAN_F4R2_FB22_Msk                               /*!<Filter bit 22 */
#define CAN_F4R2_FB23_Pos      (23U)
#define CAN_F4R2_FB23_Msk      (0x1UL << CAN_F4R2_FB23_Pos)                     /*!< 0x00800000 */
#define CAN_F4R2_FB23          CAN_F4R2_FB23_Msk                               /*!<Filter bit 23 */
#define CAN_F4R2_FB24_Pos      (24U)
#define CAN_F4R2_FB24_Msk      (0x1UL << CAN_F4R2_FB24_Pos)                     /*!< 0x01000000 */
#define CAN_F4R2_FB24          CAN_F4R2_FB24_Msk                               /*!<Filter bit 24 */
#define CAN_F4R2_FB25_Pos      (25U)
#define CAN_F4R2_FB25_Msk      (0x1UL << CAN_F4R2_FB25_Pos)                     /*!< 0x02000000 */
#define CAN_F4R2_FB25          CAN_F4R2_FB25_Msk                               /*!<Filter bit 25 */
#define CAN_F4R2_FB26_Pos      (26U)
#define CAN_F4R2_FB26_Msk      (0x1UL << CAN_F4R2_FB26_Pos)                     /*!< 0x04000000 */
#define CAN_F4R2_FB26          CAN_F4R2_FB26_Msk                               /*!<Filter bit 26 */
#define CAN_F4R2_FB27_Pos      (27U)
#define CAN_F4R2_FB27_Msk      (0x1UL << CAN_F4R2_FB27_Pos)                     /*!< 0x08000000 */
#define CAN_F4R2_FB27          CAN_F4R2_FB27_Msk                               /*!<Filter bit 27 */
#define CAN_F4R2_FB28_Pos      (28U)
#define CAN_F4R2_FB28_Msk      (0x1UL << CAN_F4R2_FB28_Pos)                     /*!< 0x10000000 */
#define CAN_F4R2_FB28          CAN_F4R2_FB28_Msk                               /*!<Filter bit 28 */
#define CAN_F4R2_FB29_Pos      (29U)
#define CAN_F4R2_FB29_Msk      (0x1UL << CAN_F4R2_FB29_Pos)                     /*!< 0x20000000 */
#define CAN_F4R2_FB29          CAN_F4R2_FB29_Msk                               /*!<Filter bit 29 */
#define CAN_F4R2_FB30_Pos      (30U)
#define CAN_F4R2_FB30_Msk      (0x1UL << CAN_F4R2_FB30_Pos)                     /*!< 0x40000000 */
#define CAN_F4R2_FB30          CAN_F4R2_FB30_Msk                               /*!<Filter bit 30 */
#define CAN_F4R2_FB31_Pos      (31U)
#define CAN_F4R2_FB31_Msk      (0x1UL << CAN_F4R2_FB31_Pos)                     /*!< 0x80000000 */
#define CAN_F4R2_FB31          CAN_F4R2_FB31_Msk                               /*!<Filter bit 31 */

/*******************  Bit definition for CAN_F5R2 register  *******************/
#define CAN_F5R2_FB0_Pos       (0U)
#define CAN_F5R2_FB0_Msk       (0x1UL << CAN_F5R2_FB0_Pos)                      /*!< 0x00000001 */
#define CAN_F5R2_FB0           CAN_F5R2_FB0_Msk                                /*!<Filter bit 0 */
#define CAN_F5R2_FB1_Pos       (1U)
#define CAN_F5R2_FB1_Msk       (0x1UL << CAN_F5R2_FB1_Pos)                      /*!< 0x00000002 */
#define CAN_F5R2_FB1           CAN_F5R2_FB1_Msk                                /*!<Filter bit 1 */
#define CAN_F5R2_FB2_Pos       (2U)
#define CAN_F5R2_FB2_Msk       (0x1UL << CAN_F5R2_FB2_Pos)                      /*!< 0x00000004 */
#define CAN_F5R2_FB2           CAN_F5R2_FB2_Msk                                /*!<Filter bit 2 */
#define CAN_F5R2_FB3_Pos       (3U)
#define CAN_F5R2_FB3_Msk       (0x1UL << CAN_F5R2_FB3_Pos)                      /*!< 0x00000008 */
#define CAN_F5R2_FB3           CAN_F5R2_FB3_Msk                                /*!<Filter bit 3 */
#define CAN_F5R2_FB4_Pos       (4U)
#define CAN_F5R2_FB4_Msk       (0x1UL << CAN_F5R2_FB4_Pos)                      /*!< 0x00000010 */
#define CAN_F5R2_FB4           CAN_F5R2_FB4_Msk                                /*!<Filter bit 4 */
#define CAN_F5R2_FB5_Pos       (5U)
#define CAN_F5R2_FB5_Msk       (0x1UL << CAN_F5R2_FB5_Pos)                      /*!< 0x00000020 */
#define CAN_F5R2_FB5           CAN_F5R2_FB5_Msk                                /*!<Filter bit 5 */
#define CAN_F5R2_FB6_Pos       (6U)
#define CAN_F5R2_FB6_Msk       (0x1UL << CAN_F5R2_FB6_Pos)                      /*!< 0x00000040 */
#define CAN_F5R2_FB6           CAN_F5R2_FB6_Msk                                /*!<Filter bit 6 */
#define CAN_F5R2_FB7_Pos       (7U)
#define CAN_F5R2_FB7_Msk       (0x1UL << CAN_F5R2_FB7_Pos)                      /*!< 0x00000080 */
#define CAN_F5R2_FB7           CAN_F5R2_FB7_Msk                                /*!<Filter bit 7 */
#define CAN_F5R2_FB8_Pos       (8U)
#define CAN_F5R2_FB8_Msk       (0x1UL << CAN_F5R2_FB8_Pos)                      /*!< 0x00000100 */
#define CAN_F5R2_FB8           CAN_F5R2_FB8_Msk                                /*!<Filter bit 8 */
#define CAN_F5R2_FB9_Pos       (9U)
#define CAN_F5R2_FB9_Msk       (0x1UL << CAN_F5R2_FB9_Pos)                      /*!< 0x00000200 */
#define CAN_F5R2_FB9           CAN_F5R2_FB9_Msk                                /*!<Filter bit 9 */
#define CAN_F5R2_FB10_Pos      (10U)
#define CAN_F5R2_FB10_Msk      (0x1UL << CAN_F5R2_FB10_Pos)                     /*!< 0x00000400 */
#define CAN_F5R2_FB10          CAN_F5R2_FB10_Msk                               /*!<Filter bit 10 */
#define CAN_F5R2_FB11_Pos      (11U)
#define CAN_F5R2_FB11_Msk      (0x1UL << CAN_F5R2_FB11_Pos)                     /*!< 0x00000800 */
#define CAN_F5R2_FB11          CAN_F5R2_FB11_Msk                               /*!<Filter bit 11 */
#define CAN_F5R2_FB12_Pos      (12U)
#define CAN_F5R2_FB12_Msk      (0x1UL << CAN_F5R2_FB12_Pos)                     /*!< 0x00001000 */
#define CAN_F5R2_FB12          CAN_F5R2_FB12_Msk                               /*!<Filter bit 12 */
#define CAN_F5R2_FB13_Pos      (13U)
#define CAN_F5R2_FB13_Msk      (0x1UL << CAN_F5R2_FB13_Pos)                     /*!< 0x00002000 */
#define CAN_F5R2_FB13          CAN_F5R2_FB13_Msk                               /*!<Filter bit 13 */
#define CAN_F5R2_FB14_Pos      (14U)
#define CAN_F5R2_FB14_Msk      (0x1UL << CAN_F5R2_FB14_Pos)                     /*!< 0x00004000 */
#define CAN_F5R2_FB14          CAN_F5R2_FB14_Msk                               /*!<Filter bit 14 */
#define CAN_F5R2_FB15_Pos      (15U)
#define CAN_F5R2_FB15_Msk      (0x1UL << CAN_F5R2_FB15_Pos)                     /*!< 0x00008000 */
#define CAN_F5R2_FB15          CAN_F5R2_FB15_Msk                               /*!<Filter bit 15 */
#define CAN_F5R2_FB16_Pos      (16U)
#define CAN_F5R2_FB16_Msk      (0x1UL << CAN_F5R2_FB16_Pos)                     /*!< 0x00010000 */
#define CAN_F5R2_FB16          CAN_F5R2_FB16_Msk                               /*!<Filter bit 16 */
#define CAN_F5R2_FB17_Pos      (17U)
#define CAN_F5R2_FB17_Msk      (0x1UL << CAN_F5R2_FB17_Pos)                     /*!< 0x00020000 */
#define CAN_F5R2_FB17          CAN_F5R2_FB17_Msk                               /*!<Filter bit 17 */
#define CAN_F5R2_FB18_Pos      (18U)
#define CAN_F5R2_FB18_Msk      (0x1UL << CAN_F5R2_FB18_Pos)                     /*!< 0x00040000 */
#define CAN_F5R2_FB18          CAN_F5R2_FB18_Msk                               /*!<Filter bit 18 */
#define CAN_F5R2_FB19_Pos      (19U)
#define CAN_F5R2_FB19_Msk      (0x1UL << CAN_F5R2_FB19_Pos)                     /*!< 0x00080000 */
#define CAN_F5R2_FB19          CAN_F5R2_FB19_Msk                               /*!<Filter bit 19 */
#define CAN_F5R2_FB20_Pos      (20U)
#define CAN_F5R2_FB20_Msk      (0x1UL << CAN_F5R2_FB20_Pos)                     /*!< 0x00100000 */
#define CAN_F5R2_FB20          CAN_F5R2_FB20_Msk                               /*!<Filter bit 20 */
#define CAN_F5R2_FB21_Pos      (21U)
#define CAN_F5R2_FB21_Msk      (0x1UL << CAN_F5R2_FB21_Pos)                     /*!< 0x00200000 */
#define CAN_F5R2_FB21          CAN_F5R2_FB21_Msk                               /*!<Filter bit 21 */
#define CAN_F5R2_FB22_Pos      (22U)
#define CAN_F5R2_FB22_Msk      (0x1UL << CAN_F5R2_FB22_Pos)                     /*!< 0x00400000 */
#define CAN_F5R2_FB22          CAN_F5R2_FB22_Msk                               /*!<Filter bit 22 */
#define CAN_F5R2_FB23_Pos      (23U)
#define CAN_F5R2_FB23_Msk      (0x1UL << CAN_F5R2_FB23_Pos)                     /*!< 0x00800000 */
#define CAN_F5R2_FB23          CAN_F5R2_FB23_Msk                               /*!<Filter bit 23 */
#define CAN_F5R2_FB24_Pos      (24U)
#define CAN_F5R2_FB24_Msk      (0x1UL << CAN_F5R2_FB24_Pos)                     /*!< 0x01000000 */
#define CAN_F5R2_FB24          CAN_F5R2_FB24_Msk                               /*!<Filter bit 24 */
#define CAN_F5R2_FB25_Pos      (25U)
#define CAN_F5R2_FB25_Msk      (0x1UL << CAN_F5R2_FB25_Pos)                     /*!< 0x02000000 */
#define CAN_F5R2_FB25          CAN_F5R2_FB25_Msk                               /*!<Filter bit 25 */
#define CAN_F5R2_FB26_Pos      (26U)
#define CAN_F5R2_FB26_Msk      (0x1UL << CAN_F5R2_FB26_Pos)                     /*!< 0x04000000 */
#define CAN_F5R2_FB26          CAN_F5R2_FB26_Msk                               /*!<Filter bit 26 */
#define CAN_F5R2_FB27_Pos      (27U)
#define CAN_F5R2_FB27_Msk      (0x1UL << CAN_F5R2_FB27_Pos)                     /*!< 0x08000000 */
#define CAN_F5R2_FB27          CAN_F5R2_FB27_Msk                               /*!<Filter bit 27 */
#define CAN_F5R2_FB28_Pos      (28U)
#define CAN_F5R2_FB28_Msk      (0x1UL << CAN_F5R2_FB28_Pos)                     /*!< 0x10000000 */
#define CAN_F5R2_FB28          CAN_F5R2_FB28_Msk                               /*!<Filter bit 28 */
#define CAN_F5R2_FB29_Pos      (29U)
#define CAN_F5R2_FB29_Msk      (0x1UL << CAN_F5R2_FB29_Pos)                     /*!< 0x20000000 */
#define CAN_F5R2_FB29          CAN_F5R2_FB29_Msk                               /*!<Filter bit 29 */
#define CAN_F5R2_FB30_Pos      (30U)
#define CAN_F5R2_FB30_Msk      (0x1UL << CAN_F5R2_FB30_Pos)                     /*!< 0x40000000 */
#define CAN_F5R2_FB30          CAN_F5R2_FB30_Msk                               /*!<Filter bit 30 */
#define CAN_F5R2_FB31_Pos      (31U)
#define CAN_F5R2_FB31_Msk      (0x1UL << CAN_F5R2_FB31_Pos)                     /*!< 0x80000000 */
#define CAN_F5R2_FB31          CAN_F5R2_FB31_Msk                               /*!<Filter bit 31 */

/*******************  Bit definition for CAN_F6R2 register  *******************/
#define CAN_F6R2_FB0_Pos       (0U)
#define CAN_F6R2_FB0_Msk       (0x1UL << CAN_F6R2_FB0_Pos)                      /*!< 0x00000001 */
#define CAN_F6R2_FB0           CAN_F6R2_FB0_Msk                                /*!<Filter bit 0 */
#define CAN_F6R2_FB1_Pos       (1U)
#define CAN_F6R2_FB1_Msk       (0x1UL << CAN_F6R2_FB1_Pos)                      /*!< 0x00000002 */
#define CAN_F6R2_FB1           CAN_F6R2_FB1_Msk                                /*!<Filter bit 1 */
#define CAN_F6R2_FB2_Pos       (2U)
#define CAN_F6R2_FB2_Msk       (0x1UL << CAN_F6R2_FB2_Pos)                      /*!< 0x00000004 */
#define CAN_F6R2_FB2           CAN_F6R2_FB2_Msk                                /*!<Filter bit 2 */
#define CAN_F6R2_FB3_Pos       (3U)
#define CAN_F6R2_FB3_Msk       (0x1UL << CAN_F6R2_FB3_Pos)                      /*!< 0x00000008 */
#define CAN_F6R2_FB3           CAN_F6R2_FB3_Msk                                /*!<Filter bit 3 */
#define CAN_F6R2_FB4_Pos       (4U)
#define CAN_F6R2_FB4_Msk       (0x1UL << CAN_F6R2_FB4_Pos)                      /*!< 0x00000010 */
#define CAN_F6R2_FB4           CAN_F6R2_FB4_Msk                                /*!<Filter bit 4 */
#define CAN_F6R2_FB5_Pos       (5U)
#define CAN_F6R2_FB5_Msk       (0x1UL << CAN_F6R2_FB5_Pos)                      /*!< 0x00000020 */
#define CAN_F6R2_FB5           CAN_F6R2_FB5_Msk                                /*!<Filter bit 5 */
#define CAN_F6R2_FB6_Pos       (6U)
#define CAN_F6R2_FB6_Msk       (0x1UL << CAN_F6R2_FB6_Pos)                      /*!< 0x00000040 */
#define CAN_F6R2_FB6           CAN_F6R2_FB6_Msk                                /*!<Filter bit 6 */
#define CAN_F6R2_FB7_Pos       (7U)
#define CAN_F6R2_FB7_Msk       (0x1UL << CAN_F6R2_FB7_Pos)                      /*!< 0x00000080 */
#define CAN_F6R2_FB7           CAN_F6R2_FB7_Msk                                /*!<Filter bit 7 */
#define CAN_F6R2_FB8_Pos       (8U)
#define CAN_F6R2_FB8_Msk       (0x1UL << CAN_F6R2_FB8_Pos)                      /*!< 0x00000100 */
#define CAN_F6R2_FB8           CAN_F6R2_FB8_Msk                                /*!<Filter bit 8 */
#define CAN_F6R2_FB9_Pos       (9U)
#define CAN_F6R2_FB9_Msk       (0x1UL << CAN_F6R2_FB9_Pos)                      /*!< 0x00000200 */
#define CAN_F6R2_FB9           CAN_F6R2_FB9_Msk                                /*!<Filter bit 9 */
#define CAN_F6R2_FB10_Pos      (10U)
#define CAN_F6R2_FB10_Msk      (0x1UL << CAN_F6R2_FB10_Pos)                     /*!< 0x00000400 */
#define CAN_F6R2_FB10          CAN_F6R2_FB10_Msk                               /*!<Filter bit 10 */
#define CAN_F6R2_FB11_Pos      (11U)
#define CAN_F6R2_FB11_Msk      (0x1UL << CAN_F6R2_FB11_Pos)                     /*!< 0x00000800 */
#define CAN_F6R2_FB11          CAN_F6R2_FB11_Msk                               /*!<Filter bit 11 */
#define CAN_F6R2_FB12_Pos      (12U)
#define CAN_F6R2_FB12_Msk      (0x1UL << CAN_F6R2_FB12_Pos)                     /*!< 0x00001000 */
#define CAN_F6R2_FB12          CAN_F6R2_FB12_Msk                               /*!<Filter bit 12 */
#define CAN_F6R2_FB13_Pos      (13U)
#define CAN_F6R2_FB13_Msk      (0x1UL << CAN_F6R2_FB13_Pos)                     /*!< 0x00002000 */
#define CAN_F6R2_FB13          CAN_F6R2_FB13_Msk                               /*!<Filter bit 13 */
#define CAN_F6R2_FB14_Pos      (14U)
#define CAN_F6R2_FB14_Msk      (0x1UL << CAN_F6R2_FB14_Pos)                     /*!< 0x00004000 */
#define CAN_F6R2_FB14          CAN_F6R2_FB14_Msk                               /*!<Filter bit 14 */
#define CAN_F6R2_FB15_Pos      (15U)
#define CAN_F6R2_FB15_Msk      (0x1UL << CAN_F6R2_FB15_Pos)                     /*!< 0x00008000 */
#define CAN_F6R2_FB15          CAN_F6R2_FB15_Msk                               /*!<Filter bit 15 */
#define CAN_F6R2_FB16_Pos      (16U)
#define CAN_F6R2_FB16_Msk      (0x1UL << CAN_F6R2_FB16_Pos)                     /*!< 0x00010000 */
#define CAN_F6R2_FB16          CAN_F6R2_FB16_Msk                               /*!<Filter bit 16 */
#define CAN_F6R2_FB17_Pos      (17U)
#define CAN_F6R2_FB17_Msk      (0x1UL << CAN_F6R2_FB17_Pos)                     /*!< 0x00020000 */
#define CAN_F6R2_FB17          CAN_F6R2_FB17_Msk                               /*!<Filter bit 17 */
#define CAN_F6R2_FB18_Pos      (18U)
#define CAN_F6R2_FB18_Msk      (0x1UL << CAN_F6R2_FB18_Pos)                     /*!< 0x00040000 */
#define CAN_F6R2_FB18          CAN_F6R2_FB18_Msk                               /*!<Filter bit 18 */
#define CAN_F6R2_FB19_Pos      (19U)
#define CAN_F6R2_FB19_Msk      (0x1UL << CAN_F6R2_FB19_Pos)                     /*!< 0x00080000 */
#define CAN_F6R2_FB19          CAN_F6R2_FB19_Msk                               /*!<Filter bit 19 */
#define CAN_F6R2_FB20_Pos      (20U)
#define CAN_F6R2_FB20_Msk      (0x1UL << CAN_F6R2_FB20_Pos)                     /*!< 0x00100000 */
#define CAN_F6R2_FB20          CAN_F6R2_FB20_Msk                               /*!<Filter bit 20 */
#define CAN_F6R2_FB21_Pos      (21U)
#define CAN_F6R2_FB21_Msk      (0x1UL << CAN_F6R2_FB21_Pos)                     /*!< 0x00200000 */
#define CAN_F6R2_FB21          CAN_F6R2_FB21_Msk                               /*!<Filter bit 21 */
#define CAN_F6R2_FB22_Pos      (22U)
#define CAN_F6R2_FB22_Msk      (0x1UL << CAN_F6R2_FB22_Pos)                     /*!< 0x00400000 */
#define CAN_F6R2_FB22          CAN_F6R2_FB22_Msk                               /*!<Filter bit 22 */
#define CAN_F6R2_FB23_Pos      (23U)
#define CAN_F6R2_FB23_Msk      (0x1UL << CAN_F6R2_FB23_Pos)                     /*!< 0x00800000 */
#define CAN_F6R2_FB23          CAN_F6R2_FB23_Msk                               /*!<Filter bit 23 */
#define CAN_F6R2_FB24_Pos      (24U)
#define CAN_F6R2_FB24_Msk      (0x1UL << CAN_F6R2_FB24_Pos)                     /*!< 0x01000000 */
#define CAN_F6R2_FB24          CAN_F6R2_FB24_Msk                               /*!<Filter bit 24 */
#define CAN_F6R2_FB25_Pos      (25U)
#define CAN_F6R2_FB25_Msk      (0x1UL << CAN_F6R2_FB25_Pos)                     /*!< 0x02000000 */
#define CAN_F6R2_FB25          CAN_F6R2_FB25_Msk                               /*!<Filter bit 25 */
#define CAN_F6R2_FB26_Pos      (26U)
#define CAN_F6R2_FB26_Msk      (0x1UL << CAN_F6R2_FB26_Pos)                     /*!< 0x04000000 */
#define CAN_F6R2_FB26          CAN_F6R2_FB26_Msk                               /*!<Filter bit 26 */
#define CAN_F6R2_FB27_Pos      (27U)
#define CAN_F6R2_FB27_Msk      (0x1UL << CAN_F6R2_FB27_Pos)                     /*!< 0x08000000 */
#define CAN_F6R2_FB27          CAN_F6R2_FB27_Msk                               /*!<Filter bit 27 */
#define CAN_F6R2_FB28_Pos      (28U)
#define CAN_F6R2_FB28_Msk      (0x1UL << CAN_F6R2_FB28_Pos)                     /*!< 0x10000000 */
#define CAN_F6R2_FB28          CAN_F6R2_FB28_Msk                               /*!<Filter bit 28 */
#define CAN_F6R2_FB29_Pos      (29U)
#define CAN_F6R2_FB29_Msk      (0x1UL << CAN_F6R2_FB29_Pos)                     /*!< 0x20000000 */
#define CAN_F6R2_FB29          CAN_F6R2_FB29_Msk                               /*!<Filter bit 29 */
#define CAN_F6R2_FB30_Pos      (30U)
#define CAN_F6R2_FB30_Msk      (0x1UL << CAN_F6R2_FB30_Pos)                     /*!< 0x40000000 */
#define CAN_F6R2_FB30          CAN_F6R2_FB30_Msk                               /*!<Filter bit 30 */
#define CAN_F6R2_FB31_Pos      (31U)
#define CAN_F6R2_FB31_Msk      (0x1UL << CAN_F6R2_FB31_Pos)                     /*!< 0x80000000 */
#define CAN_F6R2_FB31          CAN_F6R2_FB31_Msk                               /*!<Filter bit 31 */

/*******************  Bit definition for CAN_F7R2 register  *******************/
#define CAN_F7R2_FB0_Pos       (0U)
#define CAN_F7R2_FB0_Msk       (0x1UL << CAN_F7R2_FB0_Pos)                      /*!< 0x00000001 */
#define CAN_F7R2_FB0           CAN_F7R2_FB0_Msk                                /*!<Filter bit 0 */
#define CAN_F7R2_FB1_Pos       (1U)
#define CAN_F7R2_FB1_Msk       (0x1UL << CAN_F7R2_FB1_Pos)                      /*!< 0x00000002 */
#define CAN_F7R2_FB1           CAN_F7R2_FB1_Msk                                /*!<Filter bit 1 */
#define CAN_F7R2_FB2_Pos       (2U)
#define CAN_F7R2_FB2_Msk       (0x1UL << CAN_F7R2_FB2_Pos)                      /*!< 0x00000004 */
#define CAN_F7R2_FB2           CAN_F7R2_FB2_Msk                                /*!<Filter bit 2 */
#define CAN_F7R2_FB3_Pos       (3U)
#define CAN_F7R2_FB3_Msk       (0x1UL << CAN_F7R2_FB3_Pos)                      /*!< 0x00000008 */
#define CAN_F7R2_FB3           CAN_F7R2_FB3_Msk                                /*!<Filter bit 3 */
#define CAN_F7R2_FB4_Pos       (4U)
#define CAN_F7R2_FB4_Msk       (0x1UL << CAN_F7R2_FB4_Pos)                      /*!< 0x00000010 */
#define CAN_F7R2_FB4           CAN_F7R2_FB4_Msk                                /*!<Filter bit 4 */
#define CAN_F7R2_FB5_Pos       (5U)
#define CAN_F7R2_FB5_Msk       (0x1UL << CAN_F7R2_FB5_Pos)                      /*!< 0x00000020 */
#define CAN_F7R2_FB5           CAN_F7R2_FB5_Msk                                /*!<Filter bit 5 */
#define CAN_F7R2_FB6_Pos       (6U)
#define CAN_F7R2_FB6_Msk       (0x1UL << CAN_F7R2_FB6_Pos)                      /*!< 0x00000040 */
#define CAN_F7R2_FB6           CAN_F7R2_FB6_Msk                                /*!<Filter bit 6 */
#define CAN_F7R2_FB7_Pos       (7U)
#define CAN_F7R2_FB7_Msk       (0x1UL << CAN_F7R2_FB7_Pos)                      /*!< 0x00000080 */
#define CAN_F7R2_FB7           CAN_F7R2_FB7_Msk                                /*!<Filter bit 7 */
#define CAN_F7R2_FB8_Pos       (8U)
#define CAN_F7R2_FB8_Msk       (0x1UL << CAN_F7R2_FB8_Pos)                      /*!< 0x00000100 */
#define CAN_F7R2_FB8           CAN_F7R2_FB8_Msk                                /*!<Filter bit 8 */
#define CAN_F7R2_FB9_Pos       (9U)
#define CAN_F7R2_FB9_Msk       (0x1UL << CAN_F7R2_FB9_Pos)                      /*!< 0x00000200 */
#define CAN_F7R2_FB9           CAN_F7R2_FB9_Msk                                /*!<Filter bit 9 */
#define CAN_F7R2_FB10_Pos      (10U)
#define CAN_F7R2_FB10_Msk      (0x1UL << CAN_F7R2_FB10_Pos)                     /*!< 0x00000400 */
#define CAN_F7R2_FB10          CAN_F7R2_FB10_Msk                               /*!<Filter bit 10 */
#define CAN_F7R2_FB11_Pos      (11U)
#define CAN_F7R2_FB11_Msk      (0x1UL << CAN_F7R2_FB11_Pos)                     /*!< 0x00000800 */
#define CAN_F7R2_FB11          CAN_F7R2_FB11_Msk                               /*!<Filter bit 11 */
#define CAN_F7R2_FB12_Pos      (12U)
#define CAN_F7R2_FB12_Msk      (0x1UL << CAN_F7R2_FB12_Pos)                     /*!< 0x00001000 */
#define CAN_F7R2_FB12          CAN_F7R2_FB12_Msk                               /*!<Filter bit 12 */
#define CAN_F7R2_FB13_Pos      (13U)
#define CAN_F7R2_FB13_Msk      (0x1UL << CAN_F7R2_FB13_Pos)                     /*!< 0x00002000 */
#define CAN_F7R2_FB13          CAN_F7R2_FB13_Msk                               /*!<Filter bit 13 */
#define CAN_F7R2_FB14_Pos      (14U)
#define CAN_F7R2_FB14_Msk      (0x1UL << CAN_F7R2_FB14_Pos)                     /*!< 0x00004000 */
#define CAN_F7R2_FB14          CAN_F7R2_FB14_Msk                               /*!<Filter bit 14 */
#define CAN_F7R2_FB15_Pos      (15U)
#define CAN_F7R2_FB15_Msk      (0x1UL << CAN_F7R2_FB15_Pos)                     /*!< 0x00008000 */
#define CAN_F7R2_FB15          CAN_F7R2_FB15_Msk                               /*!<Filter bit 15 */
#define CAN_F7R2_FB16_Pos      (16U)
#define CAN_F7R2_FB16_Msk      (0x1UL << CAN_F7R2_FB16_Pos)                     /*!< 0x00010000 */
#define CAN_F7R2_FB16          CAN_F7R2_FB16_Msk                               /*!<Filter bit 16 */
#define CAN_F7R2_FB17_Pos      (17U)
#define CAN_F7R2_FB17_Msk      (0x1UL << CAN_F7R2_FB17_Pos)                     /*!< 0x00020000 */
#define CAN_F7R2_FB17          CAN_F7R2_FB17_Msk                               /*!<Filter bit 17 */
#define CAN_F7R2_FB18_Pos      (18U)
#define CAN_F7R2_FB18_Msk      (0x1UL << CAN_F7R2_FB18_Pos)                     /*!< 0x00040000 */
#define CAN_F7R2_FB18          CAN_F7R2_FB18_Msk                               /*!<Filter bit 18 */
#define CAN_F7R2_FB19_Pos      (19U)
#define CAN_F7R2_FB19_Msk      (0x1UL << CAN_F7R2_FB19_Pos)                     /*!< 0x00080000 */
#define CAN_F7R2_FB19          CAN_F7R2_FB19_Msk                               /*!<Filter bit 19 */
#define CAN_F7R2_FB20_Pos      (20U)
#define CAN_F7R2_FB20_Msk      (0x1UL << CAN_F7R2_FB20_Pos)                     /*!< 0x00100000 */
#define CAN_F7R2_FB20          CAN_F7R2_FB20_Msk                               /*!<Filter bit 20 */
#define CAN_F7R2_FB21_Pos      (21U)
#define CAN_F7R2_FB21_Msk      (0x1UL << CAN_F7R2_FB21_Pos)                     /*!< 0x00200000 */
#define CAN_F7R2_FB21          CAN_F7R2_FB21_Msk                               /*!<Filter bit 21 */
#define CAN_F7R2_FB22_Pos      (22U)
#define CAN_F7R2_FB22_Msk      (0x1UL << CAN_F7R2_FB22_Pos)                     /*!< 0x00400000 */
#define CAN_F7R2_FB22          CAN_F7R2_FB22_Msk                               /*!<Filter bit 22 */
#define CAN_F7R2_FB23_Pos      (23U)
#define CAN_F7R2_FB23_Msk      (0x1UL << CAN_F7R2_FB23_Pos)                     /*!< 0x00800000 */
#define CAN_F7R2_FB23          CAN_F7R2_FB23_Msk                               /*!<Filter bit 23 */
#define CAN_F7R2_FB24_Pos      (24U)
#define CAN_F7R2_FB24_Msk      (0x1UL << CAN_F7R2_FB24_Pos)                     /*!< 0x01000000 */
#define CAN_F7R2_FB24          CAN_F7R2_FB24_Msk                               /*!<Filter bit 24 */
#define CAN_F7R2_FB25_Pos      (25U)
#define CAN_F7R2_FB25_Msk      (0x1UL << CAN_F7R2_FB25_Pos)                     /*!< 0x02000000 */
#define CAN_F7R2_FB25          CAN_F7R2_FB25_Msk                               /*!<Filter bit 25 */
#define CAN_F7R2_FB26_Pos      (26U)
#define CAN_F7R2_FB26_Msk      (0x1UL << CAN_F7R2_FB26_Pos)                     /*!< 0x04000000 */
#define CAN_F7R2_FB26          CAN_F7R2_FB26_Msk                               /*!<Filter bit 26 */
#define CAN_F7R2_FB27_Pos      (27U)
#define CAN_F7R2_FB27_Msk      (0x1UL << CAN_F7R2_FB27_Pos)                     /*!< 0x08000000 */
#define CAN_F7R2_FB27          CAN_F7R2_FB27_Msk                               /*!<Filter bit 27 */
#define CAN_F7R2_FB28_Pos      (28U)
#define CAN_F7R2_FB28_Msk      (0x1UL << CAN_F7R2_FB28_Pos)                     /*!< 0x10000000 */
#define CAN_F7R2_FB28          CAN_F7R2_FB28_Msk                               /*!<Filter bit 28 */
#define CAN_F7R2_FB29_Pos      (29U)
#define CAN_F7R2_FB29_Msk      (0x1UL << CAN_F7R2_FB29_Pos)                     /*!< 0x20000000 */
#define CAN_F7R2_FB29          CAN_F7R2_FB29_Msk                               /*!<Filter bit 29 */
#define CAN_F7R2_FB30_Pos      (30U)
#define CAN_F7R2_FB30_Msk      (0x1UL << CAN_F7R2_FB30_Pos)                     /*!< 0x40000000 */
#define CAN_F7R2_FB30          CAN_F7R2_FB30_Msk                               /*!<Filter bit 30 */
#define CAN_F7R2_FB31_Pos      (31U)
#define CAN_F7R2_FB31_Msk      (0x1UL << CAN_F7R2_FB31_Pos)                     /*!< 0x80000000 */
#define CAN_F7R2_FB31          CAN_F7R2_FB31_Msk                               /*!<Filter bit 31 */

/*******************  Bit definition for CAN_F8R2 register  *******************/
#define CAN_F8R2_FB0_Pos       (0U)
#define CAN_F8R2_FB0_Msk       (0x1UL << CAN_F8R2_FB0_Pos)                      /*!< 0x00000001 */
#define CAN_F8R2_FB0           CAN_F8R2_FB0_Msk                                /*!<Filter bit 0 */
#define CAN_F8R2_FB1_Pos       (1U)
#define CAN_F8R2_FB1_Msk       (0x1UL << CAN_F8R2_FB1_Pos)                      /*!< 0x00000002 */
#define CAN_F8R2_FB1           CAN_F8R2_FB1_Msk                                /*!<Filter bit 1 */
#define CAN_F8R2_FB2_Pos       (2U)
#define CAN_F8R2_FB2_Msk       (0x1UL << CAN_F8R2_FB2_Pos)                      /*!< 0x00000004 */
#define CAN_F8R2_FB2           CAN_F8R2_FB2_Msk                                /*!<Filter bit 2 */
#define CAN_F8R2_FB3_Pos       (3U)
#define CAN_F8R2_FB3_Msk       (0x1UL << CAN_F8R2_FB3_Pos)                      /*!< 0x00000008 */
#define CAN_F8R2_FB3           CAN_F8R2_FB3_Msk                                /*!<Filter bit 3 */
#define CAN_F8R2_FB4_Pos       (4U)
#define CAN_F8R2_FB4_Msk       (0x1UL << CAN_F8R2_FB4_Pos)                      /*!< 0x00000010 */
#define CAN_F8R2_FB4           CAN_F8R2_FB4_Msk                                /*!<Filter bit 4 */
#define CAN_F8R2_FB5_Pos       (5U)
#define CAN_F8R2_FB5_Msk       (0x1UL << CAN_F8R2_FB5_Pos)                      /*!< 0x00000020 */
#define CAN_F8R2_FB5           CAN_F8R2_FB5_Msk                                /*!<Filter bit 5 */
#define CAN_F8R2_FB6_Pos       (6U)
#define CAN_F8R2_FB6_Msk       (0x1UL << CAN_F8R2_FB6_Pos)                      /*!< 0x00000040 */
#define CAN_F8R2_FB6           CAN_F8R2_FB6_Msk                                /*!<Filter bit 6 */
#define CAN_F8R2_FB7_Pos       (7U)
#define CAN_F8R2_FB7_Msk       (0x1UL << CAN_F8R2_FB7_Pos)                      /*!< 0x00000080 */
#define CAN_F8R2_FB7           CAN_F8R2_FB7_Msk                                /*!<Filter bit 7 */
#define CAN_F8R2_FB8_Pos       (8U)
#define CAN_F8R2_FB8_Msk       (0x1UL << CAN_F8R2_FB8_Pos)                      /*!< 0x00000100 */
#define CAN_F8R2_FB8           CAN_F8R2_FB8_Msk                                /*!<Filter bit 8 */
#define CAN_F8R2_FB9_Pos       (9U)
#define CAN_F8R2_FB9_Msk       (0x1UL << CAN_F8R2_FB9_Pos)                      /*!< 0x00000200 */
#define CAN_F8R2_FB9           CAN_F8R2_FB9_Msk                                /*!<Filter bit 9 */
#define CAN_F8R2_FB10_Pos      (10U)
#define CAN_F8R2_FB10_Msk      (0x1UL << CAN_F8R2_FB10_Pos)                     /*!< 0x00000400 */
#define CAN_F8R2_FB10          CAN_F8R2_FB10_Msk                               /*!<Filter bit 10 */
#define CAN_F8R2_FB11_Pos      (11U)
#define CAN_F8R2_FB11_Msk      (0x1UL << CAN_F8R2_FB11_Pos)                     /*!< 0x00000800 */
#define CAN_F8R2_FB11          CAN_F8R2_FB11_Msk                               /*!<Filter bit 11 */
#define CAN_F8R2_FB12_Pos      (12U)
#define CAN_F8R2_FB12_Msk      (0x1UL << CAN_F8R2_FB12_Pos)                     /*!< 0x00001000 */
#define CAN_F8R2_FB12          CAN_F8R2_FB12_Msk                               /*!<Filter bit 12 */
#define CAN_F8R2_FB13_Pos      (13U)
#define CAN_F8R2_FB13_Msk      (0x1UL << CAN_F8R2_FB13_Pos)                     /*!< 0x00002000 */
#define CAN_F8R2_FB13          CAN_F8R2_FB13_Msk                               /*!<Filter bit 13 */
#define CAN_F8R2_FB14_Pos      (14U)
#define CAN_F8R2_FB14_Msk      (0x1UL << CAN_F8R2_FB14_Pos)                     /*!< 0x00004000 */
#define CAN_F8R2_FB14          CAN_F8R2_FB14_Msk                               /*!<Filter bit 14 */
#define CAN_F8R2_FB15_Pos      (15U)
#define CAN_F8R2_FB15_Msk      (0x1UL << CAN_F8R2_FB15_Pos)                     /*!< 0x00008000 */
#define CAN_F8R2_FB15          CAN_F8R2_FB15_Msk                               /*!<Filter bit 15 */
#define CAN_F8R2_FB16_Pos      (16U)
#define CAN_F8R2_FB16_Msk      (0x1UL << CAN_F8R2_FB16_Pos)                     /*!< 0x00010000 */
#define CAN_F8R2_FB16          CAN_F8R2_FB16_Msk                               /*!<Filter bit 16 */
#define CAN_F8R2_FB17_Pos      (17U)
#define CAN_F8R2_FB17_Msk      (0x1UL << CAN_F8R2_FB17_Pos)                     /*!< 0x00020000 */
#define CAN_F8R2_FB17          CAN_F8R2_FB17_Msk                               /*!<Filter bit 17 */
#define CAN_F8R2_FB18_Pos      (18U)
#define CAN_F8R2_FB18_Msk      (0x1UL << CAN_F8R2_FB18_Pos)                     /*!< 0x00040000 */
#define CAN_F8R2_FB18          CAN_F8R2_FB18_Msk                               /*!<Filter bit 18 */
#define CAN_F8R2_FB19_Pos      (19U)
#define CAN_F8R2_FB19_Msk      (0x1UL << CAN_F8R2_FB19_Pos)                     /*!< 0x00080000 */
#define CAN_F8R2_FB19          CAN_F8R2_FB19_Msk                               /*!<Filter bit 19 */
#define CAN_F8R2_FB20_Pos      (20U)
#define CAN_F8R2_FB20_Msk      (0x1UL << CAN_F8R2_FB20_Pos)                     /*!< 0x00100000 */
#define CAN_F8R2_FB20          CAN_F8R2_FB20_Msk                               /*!<Filter bit 20 */
#define CAN_F8R2_FB21_Pos      (21U)
#define CAN_F8R2_FB21_Msk      (0x1UL << CAN_F8R2_FB21_Pos)                     /*!< 0x00200000 */
#define CAN_F8R2_FB21          CAN_F8R2_FB21_Msk                               /*!<Filter bit 21 */
#define CAN_F8R2_FB22_Pos      (22U)
#define CAN_F8R2_FB22_Msk      (0x1UL << CAN_F8R2_FB22_Pos)                     /*!< 0x00400000 */
#define CAN_F8R2_FB22          CAN_F8R2_FB22_Msk                               /*!<Filter bit 22 */
#define CAN_F8R2_FB23_Pos      (23U)
#define CAN_F8R2_FB23_Msk      (0x1UL << CAN_F8R2_FB23_Pos)                     /*!< 0x00800000 */
#define CAN_F8R2_FB23          CAN_F8R2_FB23_Msk                               /*!<Filter bit 23 */
#define CAN_F8R2_FB24_Pos      (24U)
#define CAN_F8R2_FB24_Msk      (0x1UL << CAN_F8R2_FB24_Pos)                     /*!< 0x01000000 */
#define CAN_F8R2_FB24          CAN_F8R2_FB24_Msk                               /*!<Filter bit 24 */
#define CAN_F8R2_FB25_Pos      (25U)
#define CAN_F8R2_FB25_Msk      (0x1UL << CAN_F8R2_FB25_Pos)                     /*!< 0x02000000 */
#define CAN_F8R2_FB25          CAN_F8R2_FB25_Msk                               /*!<Filter bit 25 */
#define CAN_F8R2_FB26_Pos      (26U)
#define CAN_F8R2_FB26_Msk      (0x1UL << CAN_F8R2_FB26_Pos)                     /*!< 0x04000000 */
#define CAN_F8R2_FB26          CAN_F8R2_FB26_Msk                               /*!<Filter bit 26 */
#define CAN_F8R2_FB27_Pos      (27U)
#define CAN_F8R2_FB27_Msk      (0x1UL << CAN_F8R2_FB27_Pos)                     /*!< 0x08000000 */
#define CAN_F8R2_FB27          CAN_F8R2_FB27_Msk                               /*!<Filter bit 27 */
#define CAN_F8R2_FB28_Pos      (28U)
#define CAN_F8R2_FB28_Msk      (0x1UL << CAN_F8R2_FB28_Pos)                     /*!< 0x10000000 */
#define CAN_F8R2_FB28          CAN_F8R2_FB28_Msk                               /*!<Filter bit 28 */
#define CAN_F8R2_FB29_Pos      (29U)
#define CAN_F8R2_FB29_Msk      (0x1UL << CAN_F8R2_FB29_Pos)                     /*!< 0x20000000 */
#define CAN_F8R2_FB29          CAN_F8R2_FB29_Msk                               /*!<Filter bit 29 */
#define CAN_F8R2_FB30_Pos      (30U)
#define CAN_F8R2_FB30_Msk      (0x1UL << CAN_F8R2_FB30_Pos)                     /*!< 0x40000000 */
#define CAN_F8R2_FB30          CAN_F8R2_FB30_Msk                               /*!<Filter bit 30 */
#define CAN_F8R2_FB31_Pos      (31U)
#define CAN_F8R2_FB31_Msk      (0x1UL << CAN_F8R2_FB31_Pos)                     /*!< 0x80000000 */
#define CAN_F8R2_FB31          CAN_F8R2_FB31_Msk                               /*!<Filter bit 31 */

/*******************  Bit definition for CAN_F9R2 register  *******************/
#define CAN_F9R2_FB0_Pos       (0U)
#define CAN_F9R2_FB0_Msk       (0x1UL << CAN_F9R2_FB0_Pos)                      /*!< 0x00000001 */
#define CAN_F9R2_FB0           CAN_F9R2_FB0_Msk                                /*!<Filter bit 0 */
#define CAN_F9R2_FB1_Pos       (1U)
#define CAN_F9R2_FB1_Msk       (0x1UL << CAN_F9R2_FB1_Pos)                      /*!< 0x00000002 */
#define CAN_F9R2_FB1           CAN_F9R2_FB1_Msk                                /*!<Filter bit 1 */
#define CAN_F9R2_FB2_Pos       (2U)
#define CAN_F9R2_FB2_Msk       (0x1UL << CAN_F9R2_FB2_Pos)                      /*!< 0x00000004 */
#define CAN_F9R2_FB2           CAN_F9R2_FB2_Msk                                /*!<Filter bit 2 */
#define CAN_F9R2_FB3_Pos       (3U)
#define CAN_F9R2_FB3_Msk       (0x1UL << CAN_F9R2_FB3_Pos)                      /*!< 0x00000008 */
#define CAN_F9R2_FB3           CAN_F9R2_FB3_Msk                                /*!<Filter bit 3 */
#define CAN_F9R2_FB4_Pos       (4U)
#define CAN_F9R2_FB4_Msk       (0x1UL << CAN_F9R2_FB4_Pos)                      /*!< 0x00000010 */
#define CAN_F9R2_FB4           CAN_F9R2_FB4_Msk                                /*!<Filter bit 4 */
#define CAN_F9R2_FB5_Pos       (5U)
#define CAN_F9R2_FB5_Msk       (0x1UL << CAN_F9R2_FB5_Pos)                      /*!< 0x00000020 */
#define CAN_F9R2_FB5           CAN_F9R2_FB5_Msk                                /*!<Filter bit 5 */
#define CAN_F9R2_FB6_Pos       (6U)
#define CAN_F9R2_FB6_Msk       (0x1UL << CAN_F9R2_FB6_Pos)                      /*!< 0x00000040 */
#define CAN_F9R2_FB6           CAN_F9R2_FB6_Msk                                /*!<Filter bit 6 */
#define CAN_F9R2_FB7_Pos       (7U)
#define CAN_F9R2_FB7_Msk       (0x1UL << CAN_F9R2_FB7_Pos)                      /*!< 0x00000080 */
#define CAN_F9R2_FB7           CAN_F9R2_FB7_Msk                                /*!<Filter bit 7 */
#define CAN_F9R2_FB8_Pos       (8U)
#define CAN_F9R2_FB8_Msk       (0x1UL << CAN_F9R2_FB8_Pos)                      /*!< 0x00000100 */
#define CAN_F9R2_FB8           CAN_F9R2_FB8_Msk                                /*!<Filter bit 8 */
#define CAN_F9R2_FB9_Pos       (9U)
#define CAN_F9R2_FB9_Msk       (0x1UL << CAN_F9R2_FB9_Pos)                      /*!< 0x00000200 */
#define CAN_F9R2_FB9           CAN_F9R2_FB9_Msk                                /*!<Filter bit 9 */
#define CAN_F9R2_FB10_Pos      (10U)
#define CAN_F9R2_FB10_Msk      (0x1UL << CAN_F9R2_FB10_Pos)                     /*!< 0x00000400 */
#define CAN_F9R2_FB10          CAN_F9R2_FB10_Msk                               /*!<Filter bit 10 */
#define CAN_F9R2_FB11_Pos      (11U)
#define CAN_F9R2_FB11_Msk      (0x1UL << CAN_F9R2_FB11_Pos)                     /*!< 0x00000800 */
#define CAN_F9R2_FB11          CAN_F9R2_FB11_Msk                               /*!<Filter bit 11 */
#define CAN_F9R2_FB12_Pos      (12U)
#define CAN_F9R2_FB12_Msk      (0x1UL << CAN_F9R2_FB12_Pos)                     /*!< 0x00001000 */
#define CAN_F9R2_FB12          CAN_F9R2_FB12_Msk                               /*!<Filter bit 12 */
#define CAN_F9R2_FB13_Pos      (13U)
#define CAN_F9R2_FB13_Msk      (0x1UL << CAN_F9R2_FB13_Pos)                     /*!< 0x00002000 */
#define CAN_F9R2_FB13          CAN_F9R2_FB13_Msk                               /*!<Filter bit 13 */
#define CAN_F9R2_FB14_Pos      (14U)
#define CAN_F9R2_FB14_Msk      (0x1UL << CAN_F9R2_FB14_Pos)                     /*!< 0x00004000 */
#define CAN_F9R2_FB14          CAN_F9R2_FB14_Msk                               /*!<Filter bit 14 */
#define CAN_F9R2_FB15_Pos      (15U)
#define CAN_F9R2_FB15_Msk      (0x1UL << CAN_F9R2_FB15_Pos)                     /*!< 0x00008000 */
#define CAN_F9R2_FB15          CAN_F9R2_FB15_Msk                               /*!<Filter bit 15 */
#define CAN_F9R2_FB16_Pos      (16U)
#define CAN_F9R2_FB16_Msk      (0x1UL << CAN_F9R2_FB16_Pos)                     /*!< 0x00010000 */
#define CAN_F9R2_FB16          CAN_F9R2_FB16_Msk                               /*!<Filter bit 16 */
#define CAN_F9R2_FB17_Pos      (17U)
#define CAN_F9R2_FB17_Msk      (0x1UL << CAN_F9R2_FB17_Pos)                     /*!< 0x00020000 */
#define CAN_F9R2_FB17          CAN_F9R2_FB17_Msk                               /*!<Filter bit 17 */
#define CAN_F9R2_FB18_Pos      (18U)
#define CAN_F9R2_FB18_Msk      (0x1UL << CAN_F9R2_FB18_Pos)                     /*!< 0x00040000 */
#define CAN_F9R2_FB18          CAN_F9R2_FB18_Msk                               /*!<Filter bit 18 */
#define CAN_F9R2_FB19_Pos      (19U)
#define CAN_F9R2_FB19_Msk      (0x1UL << CAN_F9R2_FB19_Pos)                     /*!< 0x00080000 */
#define CAN_F9R2_FB19          CAN_F9R2_FB19_Msk                               /*!<Filter bit 19 */
#define CAN_F9R2_FB20_Pos      (20U)
#define CAN_F9R2_FB20_Msk      (0x1UL << CAN_F9R2_FB20_Pos)                     /*!< 0x00100000 */
#define CAN_F9R2_FB20          CAN_F9R2_FB20_Msk                               /*!<Filter bit 20 */
#define CAN_F9R2_FB21_Pos      (21U)
#define CAN_F9R2_FB21_Msk      (0x1UL << CAN_F9R2_FB21_Pos)                     /*!< 0x00200000 */
#define CAN_F9R2_FB21          CAN_F9R2_FB21_Msk                               /*!<Filter bit 21 */
#define CAN_F9R2_FB22_Pos      (22U)
#define CAN_F9R2_FB22_Msk      (0x1UL << CAN_F9R2_FB22_Pos)                     /*!< 0x00400000 */
#define CAN_F9R2_FB22          CAN_F9R2_FB22_Msk                               /*!<Filter bit 22 */
#define CAN_F9R2_FB23_Pos      (23U)
#define CAN_F9R2_FB23_Msk      (0x1UL << CAN_F9R2_FB23_Pos)                     /*!< 0x00800000 */
#define CAN_F9R2_FB23          CAN_F9R2_FB23_Msk                               /*!<Filter bit 23 */
#define CAN_F9R2_FB24_Pos      (24U)
#define CAN_F9R2_FB24_Msk      (0x1UL << CAN_F9R2_FB24_Pos)                     /*!< 0x01000000 */
#define CAN_F9R2_FB24          CAN_F9R2_FB24_Msk                               /*!<Filter bit 24 */
#define CAN_F9R2_FB25_Pos      (25U)
#define CAN_F9R2_FB25_Msk      (0x1UL << CAN_F9R2_FB25_Pos)                     /*!< 0x02000000 */
#define CAN_F9R2_FB25          CAN_F9R2_FB25_Msk                               /*!<Filter bit 25 */
#define CAN_F9R2_FB26_Pos      (26U)
#define CAN_F9R2_FB26_Msk      (0x1UL << CAN_F9R2_FB26_Pos)                     /*!< 0x04000000 */
#define CAN_F9R2_FB26          CAN_F9R2_FB26_Msk                               /*!<Filter bit 26 */
#define CAN_F9R2_FB27_Pos      (27U)
#define CAN_F9R2_FB27_Msk      (0x1UL << CAN_F9R2_FB27_Pos)                     /*!< 0x08000000 */
#define CAN_F9R2_FB27          CAN_F9R2_FB27_Msk                               /*!<Filter bit 27 */
#define CAN_F9R2_FB28_Pos      (28U)
#define CAN_F9R2_FB28_Msk      (0x1UL << CAN_F9R2_FB28_Pos)                     /*!< 0x10000000 */
#define CAN_F9R2_FB28          CAN_F9R2_FB28_Msk                               /*!<Filter bit 28 */
#define CAN_F9R2_FB29_Pos      (29U)
#define CAN_F9R2_FB29_Msk      (0x1UL << CAN_F9R2_FB29_Pos)                     /*!< 0x20000000 */
#define CAN_F9R2_FB29          CAN_F9R2_FB29_Msk                               /*!<Filter bit 29 */
#define CAN_F9R2_FB30_Pos      (30U)
#define CAN_F9R2_FB30_Msk      (0x1UL << CAN_F9R2_FB30_Pos)                     /*!< 0x40000000 */
#define CAN_F9R2_FB30          CAN_F9R2_FB30_Msk                               /*!<Filter bit 30 */
#define CAN_F9R2_FB31_Pos      (31U)
#define CAN_F9R2_FB31_Msk      (0x1UL << CAN_F9R2_FB31_Pos)                     /*!< 0x80000000 */
#define CAN_F9R2_FB31          CAN_F9R2_FB31_Msk                               /*!<Filter bit 31 */

/*******************  Bit definition for CAN_F10R2 register  ******************/
#define CAN_F10R2_FB0_Pos      (0U)
#define CAN_F10R2_FB0_Msk      (0x1UL << CAN_F10R2_FB0_Pos)                     /*!< 0x00000001 */
#define CAN_F10R2_FB0          CAN_F10R2_FB0_Msk                               /*!<Filter bit 0 */
#define CAN_F10R2_FB1_Pos      (1U)
#define CAN_F10R2_FB1_Msk      (0x1UL << CAN_F10R2_FB1_Pos)                     /*!< 0x00000002 */
#define CAN_F10R2_FB1          CAN_F10R2_FB1_Msk                               /*!<Filter bit 1 */
#define CAN_F10R2_FB2_Pos      (2U)
#define CAN_F10R2_FB2_Msk      (0x1UL << CAN_F10R2_FB2_Pos)                     /*!< 0x00000004 */
#define CAN_F10R2_FB2          CAN_F10R2_FB2_Msk                               /*!<Filter bit 2 */
#define CAN_F10R2_FB3_Pos      (3U)
#define CAN_F10R2_FB3_Msk      (0x1UL << CAN_F10R2_FB3_Pos)                     /*!< 0x00000008 */
#define CAN_F10R2_FB3          CAN_F10R2_FB3_Msk                               /*!<Filter bit 3 */
#define CAN_F10R2_FB4_Pos      (4U)
#define CAN_F10R2_FB4_Msk      (0x1UL << CAN_F10R2_FB4_Pos)                     /*!< 0x00000010 */
#define CAN_F10R2_FB4          CAN_F10R2_FB4_Msk                               /*!<Filter bit 4 */
#define CAN_F10R2_FB5_Pos      (5U)
#define CAN_F10R2_FB5_Msk      (0x1UL << CAN_F10R2_FB5_Pos)                     /*!< 0x00000020 */
#define CAN_F10R2_FB5          CAN_F10R2_FB5_Msk                               /*!<Filter bit 5 */
#define CAN_F10R2_FB6_Pos      (6U)
#define CAN_F10R2_FB6_Msk      (0x1UL << CAN_F10R2_FB6_Pos)                     /*!< 0x00000040 */
#define CAN_F10R2_FB6          CAN_F10R2_FB6_Msk                               /*!<Filter bit 6 */
#define CAN_F10R2_FB7_Pos      (7U)
#define CAN_F10R2_FB7_Msk      (0x1UL << CAN_F10R2_FB7_Pos)                     /*!< 0x00000080 */
#define CAN_F10R2_FB7          CAN_F10R2_FB7_Msk                               /*!<Filter bit 7 */
#define CAN_F10R2_FB8_Pos      (8U)
#define CAN_F10R2_FB8_Msk      (0x1UL << CAN_F10R2_FB8_Pos)                     /*!< 0x00000100 */
#define CAN_F10R2_FB8          CAN_F10R2_FB8_Msk                               /*!<Filter bit 8 */
#define CAN_F10R2_FB9_Pos      (9U)
#define CAN_F10R2_FB9_Msk      (0x1UL << CAN_F10R2_FB9_Pos)                     /*!< 0x00000200 */
#define CAN_F10R2_FB9          CAN_F10R2_FB9_Msk                               /*!<Filter bit 9 */
#define CAN_F10R2_FB10_Pos     (10U)
#define CAN_F10R2_FB10_Msk     (0x1UL << CAN_F10R2_FB10_Pos)                    /*!< 0x00000400 */
#define CAN_F10R2_FB10         CAN_F10R2_FB10_Msk                              /*!<Filter bit 10 */
#define CAN_F10R2_FB11_Pos     (11U)
#define CAN_F10R2_FB11_Msk     (0x1UL << CAN_F10R2_FB11_Pos)                    /*!< 0x00000800 */
#define CAN_F10R2_FB11         CAN_F10R2_FB11_Msk                              /*!<Filter bit 11 */
#define CAN_F10R2_FB12_Pos     (12U)
#define CAN_F10R2_FB12_Msk     (0x1UL << CAN_F10R2_FB12_Pos)                    /*!< 0x00001000 */
#define CAN_F10R2_FB12         CAN_F10R2_FB12_Msk                              /*!<Filter bit 12 */
#define CAN_F10R2_FB13_Pos     (13U)
#define CAN_F10R2_FB13_Msk     (0x1UL << CAN_F10R2_FB13_Pos)                    /*!< 0x00002000 */
#define CAN_F10R2_FB13         CAN_F10R2_FB13_Msk                              /*!<Filter bit 13 */
#define CAN_F10R2_FB14_Pos     (14U)
#define CAN_F10R2_FB14_Msk     (0x1UL << CAN_F10R2_FB14_Pos)                    /*!< 0x00004000 */
#define CAN_F10R2_FB14         CAN_F10R2_FB14_Msk                              /*!<Filter bit 14 */
#define CAN_F10R2_FB15_Pos     (15U)
#define CAN_F10R2_FB15_Msk     (0x1UL << CAN_F10R2_FB15_Pos)                    /*!< 0x00008000 */
#define CAN_F10R2_FB15         CAN_F10R2_FB15_Msk                              /*!<Filter bit 15 */
#define CAN_F10R2_FB16_Pos     (16U)
#define CAN_F10R2_FB16_Msk     (0x1UL << CAN_F10R2_FB16_Pos)                    /*!< 0x00010000 */
#define CAN_F10R2_FB16         CAN_F10R2_FB16_Msk                              /*!<Filter bit 16 */
#define CAN_F10R2_FB17_Pos     (17U)
#define CAN_F10R2_FB17_Msk     (0x1UL << CAN_F10R2_FB17_Pos)                    /*!< 0x00020000 */
#define CAN_F10R2_FB17         CAN_F10R2_FB17_Msk                              /*!<Filter bit 17 */
#define CAN_F10R2_FB18_Pos     (18U)
#define CAN_F10R2_FB18_Msk     (0x1UL << CAN_F10R2_FB18_Pos)                    /*!< 0x00040000 */
#define CAN_F10R2_FB18         CAN_F10R2_FB18_Msk                              /*!<Filter bit 18 */
#define CAN_F10R2_FB19_Pos     (19U)
#define CAN_F10R2_FB19_Msk     (0x1UL << CAN_F10R2_FB19_Pos)                    /*!< 0x00080000 */
#define CAN_F10R2_FB19         CAN_F10R2_FB19_Msk                              /*!<Filter bit 19 */
#define CAN_F10R2_FB20_Pos     (20U)
#define CAN_F10R2_FB20_Msk     (0x1UL << CAN_F10R2_FB20_Pos)                    /*!< 0x00100000 */
#define CAN_F10R2_FB20         CAN_F10R2_FB20_Msk                              /*!<Filter bit 20 */
#define CAN_F10R2_FB21_Pos     (21U)
#define CAN_F10R2_FB21_Msk     (0x1UL << CAN_F10R2_FB21_Pos)                    /*!< 0x00200000 */
#define CAN_F10R2_FB21         CAN_F10R2_FB21_Msk                              /*!<Filter bit 21 */
#define CAN_F10R2_FB22_Pos     (22U)
#define CAN_F10R2_FB22_Msk     (0x1UL << CAN_F10R2_FB22_Pos)                    /*!< 0x00400000 */
#define CAN_F10R2_FB22         CAN_F10R2_FB22_Msk                              /*!<Filter bit 22 */
#define CAN_F10R2_FB23_Pos     (23U)
#define CAN_F10R2_FB23_Msk     (0x1UL << CAN_F10R2_FB23_Pos)                    /*!< 0x00800000 */
#define CAN_F10R2_FB23         CAN_F10R2_FB23_Msk                              /*!<Filter bit 23 */
#define CAN_F10R2_FB24_Pos     (24U)
#define CAN_F10R2_FB24_Msk     (0x1UL << CAN_F10R2_FB24_Pos)                    /*!< 0x01000000 */
#define CAN_F10R2_FB24         CAN_F10R2_FB24_Msk                              /*!<Filter bit 24 */
#define CAN_F10R2_FB25_Pos     (25U)
#define CAN_F10R2_FB25_Msk     (0x1UL << CAN_F10R2_FB25_Pos)                    /*!< 0x02000000 */
#define CAN_F10R2_FB25         CAN_F10R2_FB25_Msk                              /*!<Filter bit 25 */
#define CAN_F10R2_FB26_Pos     (26U)
#define CAN_F10R2_FB26_Msk     (0x1UL << CAN_F10R2_FB26_Pos)                    /*!< 0x04000000 */
#define CAN_F10R2_FB26         CAN_F10R2_FB26_Msk                              /*!<Filter bit 26 */
#define CAN_F10R2_FB27_Pos     (27U)
#define CAN_F10R2_FB27_Msk     (0x1UL << CAN_F10R2_FB27_Pos)                    /*!< 0x08000000 */
#define CAN_F10R2_FB27         CAN_F10R2_FB27_Msk                              /*!<Filter bit 27 */
#define CAN_F10R2_FB28_Pos     (28U)
#define CAN_F10R2_FB28_Msk     (0x1UL << CAN_F10R2_FB28_Pos)                    /*!< 0x10000000 */
#define CAN_F10R2_FB28         CAN_F10R2_FB28_Msk                              /*!<Filter bit 28 */
#define CAN_F10R2_FB29_Pos     (29U)
#define CAN_F10R2_FB29_Msk     (0x1UL << CAN_F10R2_FB29_Pos)                    /*!< 0x20000000 */
#define CAN_F10R2_FB29         CAN_F10R2_FB29_Msk                              /*!<Filter bit 29 */
#define CAN_F10R2_FB30_Pos     (30U)
#define CAN_F10R2_FB30_Msk     (0x1UL << CAN_F10R2_FB30_Pos)                    /*!< 0x40000000 */
#define CAN_F10R2_FB30         CAN_F10R2_FB30_Msk                              /*!<Filter bit 30 */
#define CAN_F10R2_FB31_Pos     (31U)
#define CAN_F10R2_FB31_Msk     (0x1UL << CAN_F10R2_FB31_Pos)                    /*!< 0x80000000 */
#define CAN_F10R2_FB31         CAN_F10R2_FB31_Msk                              /*!<Filter bit 31 */

/*******************  Bit definition for CAN_F11R2 register  ******************/
#define CAN_F11R2_FB0_Pos      (0U)
#define CAN_F11R2_FB0_Msk      (0x1UL << CAN_F11R2_FB0_Pos)                     /*!< 0x00000001 */
#define CAN_F11R2_FB0          CAN_F11R2_FB0_Msk                               /*!<Filter bit 0 */
#define CAN_F11R2_FB1_Pos      (1U)
#define CAN_F11R2_FB1_Msk      (0x1UL << CAN_F11R2_FB1_Pos)                     /*!< 0x00000002 */
#define CAN_F11R2_FB1          CAN_F11R2_FB1_Msk                               /*!<Filter bit 1 */
#define CAN_F11R2_FB2_Pos      (2U)
#define CAN_F11R2_FB2_Msk      (0x1UL << CAN_F11R2_FB2_Pos)                     /*!< 0x00000004 */
#define CAN_F11R2_FB2          CAN_F11R2_FB2_Msk                               /*!<Filter bit 2 */
#define CAN_F11R2_FB3_Pos      (3U)
#define CAN_F11R2_FB3_Msk      (0x1UL << CAN_F11R2_FB3_Pos)                     /*!< 0x00000008 */
#define CAN_F11R2_FB3          CAN_F11R2_FB3_Msk                               /*!<Filter bit 3 */
#define CAN_F11R2_FB4_Pos      (4U)
#define CAN_F11R2_FB4_Msk      (0x1UL << CAN_F11R2_FB4_Pos)                     /*!< 0x00000010 */
#define CAN_F11R2_FB4          CAN_F11R2_FB4_Msk                               /*!<Filter bit 4 */
#define CAN_F11R2_FB5_Pos      (5U)
#define CAN_F11R2_FB5_Msk      (0x1UL << CAN_F11R2_FB5_Pos)                     /*!< 0x00000020 */
#define CAN_F11R2_FB5          CAN_F11R2_FB5_Msk                               /*!<Filter bit 5 */
#define CAN_F11R2_FB6_Pos      (6U)
#define CAN_F11R2_FB6_Msk      (0x1UL << CAN_F11R2_FB6_Pos)                     /*!< 0x00000040 */
#define CAN_F11R2_FB6          CAN_F11R2_FB6_Msk                               /*!<Filter bit 6 */
#define CAN_F11R2_FB7_Pos      (7U)
#define CAN_F11R2_FB7_Msk      (0x1UL << CAN_F11R2_FB7_Pos)                     /*!< 0x00000080 */
#define CAN_F11R2_FB7          CAN_F11R2_FB7_Msk                               /*!<Filter bit 7 */
#define CAN_F11R2_FB8_Pos      (8U)
#define CAN_F11R2_FB8_Msk      (0x1UL << CAN_F11R2_FB8_Pos)                     /*!< 0x00000100 */
#define CAN_F11R2_FB8          CAN_F11R2_FB8_Msk                               /*!<Filter bit 8 */
#define CAN_F11R2_FB9_Pos      (9U)
#define CAN_F11R2_FB9_Msk      (0x1UL << CAN_F11R2_FB9_Pos)                     /*!< 0x00000200 */
#define CAN_F11R2_FB9          CAN_F11R2_FB9_Msk                               /*!<Filter bit 9 */
#define CAN_F11R2_FB10_Pos     (10U)
#define CAN_F11R2_FB10_Msk     (0x1UL << CAN_F11R2_FB10_Pos)                    /*!< 0x00000400 */
#define CAN_F11R2_FB10         CAN_F11R2_FB10_Msk                              /*!<Filter bit 10 */
#define CAN_F11R2_FB11_Pos     (11U)
#define CAN_F11R2_FB11_Msk     (0x1UL << CAN_F11R2_FB11_Pos)                    /*!< 0x00000800 */
#define CAN_F11R2_FB11         CAN_F11R2_FB11_Msk                              /*!<Filter bit 11 */
#define CAN_F11R2_FB12_Pos     (12U)
#define CAN_F11R2_FB12_Msk     (0x1UL << CAN_F11R2_FB12_Pos)                    /*!< 0x00001000 */
#define CAN_F11R2_FB12         CAN_F11R2_FB12_Msk                              /*!<Filter bit 12 */
#define CAN_F11R2_FB13_Pos     (13U)
#define CAN_F11R2_FB13_Msk     (0x1UL << CAN_F11R2_FB13_Pos)                    /*!< 0x00002000 */
#define CAN_F11R2_FB13         CAN_F11R2_FB13_Msk                              /*!<Filter bit 13 */
#define CAN_F11R2_FB14_Pos     (14U)
#define CAN_F11R2_FB14_Msk     (0x1UL << CAN_F11R2_FB14_Pos)                    /*!< 0x00004000 */
#define CAN_F11R2_FB14         CAN_F11R2_FB14_Msk                              /*!<Filter bit 14 */
#define CAN_F11R2_FB15_Pos     (15U)
#define CAN_F11R2_FB15_Msk     (0x1UL << CAN_F11R2_FB15_Pos)                    /*!< 0x00008000 */
#define CAN_F11R2_FB15         CAN_F11R2_FB15_Msk                              /*!<Filter bit 15 */
#define CAN_F11R2_FB16_Pos     (16U)
#define CAN_F11R2_FB16_Msk     (0x1UL << CAN_F11R2_FB16_Pos)                    /*!< 0x00010000 */
#define CAN_F11R2_FB16         CAN_F11R2_FB16_Msk                              /*!<Filter bit 16 */
#define CAN_F11R2_FB17_Pos     (17U)
#define CAN_F11R2_FB17_Msk     (0x1UL << CAN_F11R2_FB17_Pos)                    /*!< 0x00020000 */
#define CAN_F11R2_FB17         CAN_F11R2_FB17_Msk                              /*!<Filter bit 17 */
#define CAN_F11R2_FB18_Pos     (18U)
#define CAN_F11R2_FB18_Msk     (0x1UL << CAN_F11R2_FB18_Pos)                    /*!< 0x00040000 */
#define CAN_F11R2_FB18         CAN_F11R2_FB18_Msk                              /*!<Filter bit 18 */
#define CAN_F11R2_FB19_Pos     (19U)
#define CAN_F11R2_FB19_Msk     (0x1UL << CAN_F11R2_FB19_Pos)                    /*!< 0x00080000 */
#define CAN_F11R2_FB19         CAN_F11R2_FB19_Msk                              /*!<Filter bit 19 */
#define CAN_F11R2_FB20_Pos     (20U)
#define CAN_F11R2_FB20_Msk     (0x1UL << CAN_F11R2_FB20_Pos)                    /*!< 0x00100000 */
#define CAN_F11R2_FB20         CAN_F11R2_FB20_Msk                              /*!<Filter bit 20 */
#define CAN_F11R2_FB21_Pos     (21U)
#define CAN_F11R2_FB21_Msk     (0x1UL << CAN_F11R2_FB21_Pos)                    /*!< 0x00200000 */
#define CAN_F11R2_FB21         CAN_F11R2_FB21_Msk                              /*!<Filter bit 21 */
#define CAN_F11R2_FB22_Pos     (22U)
#define CAN_F11R2_FB22_Msk     (0x1UL << CAN_F11R2_FB22_Pos)                    /*!< 0x00400000 */
#define CAN_F11R2_FB22         CAN_F11R2_FB22_Msk                              /*!<Filter bit 22 */
#define CAN_F11R2_FB23_Pos     (23U)
#define CAN_F11R2_FB23_Msk     (0x1UL << CAN_F11R2_FB23_Pos)                    /*!< 0x00800000 */
#define CAN_F11R2_FB23         CAN_F11R2_FB23_Msk                              /*!<Filter bit 23 */
#define CAN_F11R2_FB24_Pos     (24U)
#define CAN_F11R2_FB24_Msk     (0x1UL << CAN_F11R2_FB24_Pos)                    /*!< 0x01000000 */
#define CAN_F11R2_FB24         CAN_F11R2_FB24_Msk                              /*!<Filter bit 24 */
#define CAN_F11R2_FB25_Pos     (25U)
#define CAN_F11R2_FB25_Msk     (0x1UL << CAN_F11R2_FB25_Pos)                    /*!< 0x02000000 */
#define CAN_F11R2_FB25         CAN_F11R2_FB25_Msk                              /*!<Filter bit 25 */
#define CAN_F11R2_FB26_Pos     (26U)
#define CAN_F11R2_FB26_Msk     (0x1UL << CAN_F11R2_FB26_Pos)                    /*!< 0x04000000 */
#define CAN_F11R2_FB26         CAN_F11R2_FB26_Msk                              /*!<Filter bit 26 */
#define CAN_F11R2_FB27_Pos     (27U)
#define CAN_F11R2_FB27_Msk     (0x1UL << CAN_F11R2_FB27_Pos)                    /*!< 0x08000000 */
#define CAN_F11R2_FB27         CAN_F11R2_FB27_Msk                              /*!<Filter bit 27 */
#define CAN_F11R2_FB28_Pos     (28U)
#define CAN_F11R2_FB28_Msk     (0x1UL << CAN_F11R2_FB28_Pos)                    /*!< 0x10000000 */
#define CAN_F11R2_FB28         CAN_F11R2_FB28_Msk                              /*!<Filter bit 28 */
#define CAN_F11R2_FB29_Pos     (29U)
#define CAN_F11R2_FB29_Msk     (0x1UL << CAN_F11R2_FB29_Pos)                    /*!< 0x20000000 */
#define CAN_F11R2_FB29         CAN_F11R2_FB29_Msk                              /*!<Filter bit 29 */
#define CAN_F11R2_FB30_Pos     (30U)
#define CAN_F11R2_FB30_Msk     (0x1UL << CAN_F11R2_FB30_Pos)                    /*!< 0x40000000 */
#define CAN_F11R2_FB30         CAN_F11R2_FB30_Msk                              /*!<Filter bit 30 */
#define CAN_F11R2_FB31_Pos     (31U)
#define CAN_F11R2_FB31_Msk     (0x1UL << CAN_F11R2_FB31_Pos)                    /*!< 0x80000000 */
#define CAN_F11R2_FB31         CAN_F11R2_FB31_Msk                              /*!<Filter bit 31 */

/*******************  Bit definition for CAN_F12R2 register  ******************/
#define CAN_F12R2_FB0_Pos      (0U)
#define CAN_F12R2_FB0_Msk      (0x1UL << CAN_F12R2_FB0_Pos)                     /*!< 0x00000001 */
#define CAN_F12R2_FB0          CAN_F12R2_FB0_Msk                               /*!<Filter bit 0 */
#define CAN_F12R2_FB1_Pos      (1U)
#define CAN_F12R2_FB1_Msk      (0x1UL << CAN_F12R2_FB1_Pos)                     /*!< 0x00000002 */
#define CAN_F12R2_FB1          CAN_F12R2_FB1_Msk                               /*!<Filter bit 1 */
#define CAN_F12R2_FB2_Pos      (2U)
#define CAN_F12R2_FB2_Msk      (0x1UL << CAN_F12R2_FB2_Pos)                     /*!< 0x00000004 */
#define CAN_F12R2_FB2          CAN_F12R2_FB2_Msk                               /*!<Filter bit 2 */
#define CAN_F12R2_FB3_Pos      (3U)
#define CAN_F12R2_FB3_Msk      (0x1UL << CAN_F12R2_FB3_Pos)                     /*!< 0x00000008 */
#define CAN_F12R2_FB3          CAN_F12R2_FB3_Msk                               /*!<Filter bit 3 */
#define CAN_F12R2_FB4_Pos      (4U)
#define CAN_F12R2_FB4_Msk      (0x1UL << CAN_F12R2_FB4_Pos)                     /*!< 0x00000010 */
#define CAN_F12R2_FB4          CAN_F12R2_FB4_Msk                               /*!<Filter bit 4 */
#define CAN_F12R2_FB5_Pos      (5U)
#define CAN_F12R2_FB5_Msk      (0x1UL << CAN_F12R2_FB5_Pos)                     /*!< 0x00000020 */
#define CAN_F12R2_FB5          CAN_F12R2_FB5_Msk                               /*!<Filter bit 5 */
#define CAN_F12R2_FB6_Pos      (6U)
#define CAN_F12R2_FB6_Msk      (0x1UL << CAN_F12R2_FB6_Pos)                     /*!< 0x00000040 */
#define CAN_F12R2_FB6          CAN_F12R2_FB6_Msk                               /*!<Filter bit 6 */
#define CAN_F12R2_FB7_Pos      (7U)
#define CAN_F12R2_FB7_Msk      (0x1UL << CAN_F12R2_FB7_Pos)                     /*!< 0x00000080 */
#define CAN_F12R2_FB7          CAN_F12R2_FB7_Msk                               /*!<Filter bit 7 */
#define CAN_F12R2_FB8_Pos      (8U)
#define CAN_F12R2_FB8_Msk      (0x1UL << CAN_F12R2_FB8_Pos)                     /*!< 0x00000100 */
#define CAN_F12R2_FB8          CAN_F12R2_FB8_Msk                               /*!<Filter bit 8 */
#define CAN_F12R2_FB9_Pos      (9U)
#define CAN_F12R2_FB9_Msk      (0x1UL << CAN_F12R2_FB9_Pos)                     /*!< 0x00000200 */
#define CAN_F12R2_FB9          CAN_F12R2_FB9_Msk                               /*!<Filter bit 9 */
#define CAN_F12R2_FB10_Pos     (10U)
#define CAN_F12R2_FB10_Msk     (0x1UL << CAN_F12R2_FB10_Pos)                    /*!< 0x00000400 */
#define CAN_F12R2_FB10         CAN_F12R2_FB10_Msk                              /*!<Filter bit 10 */
#define CAN_F12R2_FB11_Pos     (11U)
#define CAN_F12R2_FB11_Msk     (0x1UL << CAN_F12R2_FB11_Pos)                    /*!< 0x00000800 */
#define CAN_F12R2_FB11         CAN_F12R2_FB11_Msk                              /*!<Filter bit 11 */
#define CAN_F12R2_FB12_Pos     (12U)
#define CAN_F12R2_FB12_Msk     (0x1UL << CAN_F12R2_FB12_Pos)                    /*!< 0x00001000 */
#define CAN_F12R2_FB12         CAN_F12R2_FB12_Msk                              /*!<Filter bit 12 */
#define CAN_F12R2_FB13_Pos     (13U)
#define CAN_F12R2_FB13_Msk     (0x1UL << CAN_F12R2_FB13_Pos)                    /*!< 0x00002000 */
#define CAN_F12R2_FB13         CAN_F12R2_FB13_Msk                              /*!<Filter bit 13 */
#define CAN_F12R2_FB14_Pos     (14U)
#define CAN_F12R2_FB14_Msk     (0x1UL << CAN_F12R2_FB14_Pos)                    /*!< 0x00004000 */
#define CAN_F12R2_FB14         CAN_F12R2_FB14_Msk                              /*!<Filter bit 14 */
#define CAN_F12R2_FB15_Pos     (15U)
#define CAN_F12R2_FB15_Msk     (0x1UL << CAN_F12R2_FB15_Pos)                    /*!< 0x00008000 */
#define CAN_F12R2_FB15         CAN_F12R2_FB15_Msk                              /*!<Filter bit 15 */
#define CAN_F12R2_FB16_Pos     (16U)
#define CAN_F12R2_FB16_Msk     (0x1UL << CAN_F12R2_FB16_Pos)                    /*!< 0x00010000 */
#define CAN_F12R2_FB16         CAN_F12R2_FB16_Msk                              /*!<Filter bit 16 */
#define CAN_F12R2_FB17_Pos     (17U)
#define CAN_F12R2_FB17_Msk     (0x1UL << CAN_F12R2_FB17_Pos)                    /*!< 0x00020000 */
#define CAN_F12R2_FB17         CAN_F12R2_FB17_Msk                              /*!<Filter bit 17 */
#define CAN_F12R2_FB18_Pos     (18U)
#define CAN_F12R2_FB18_Msk     (0x1UL << CAN_F12R2_FB18_Pos)                    /*!< 0x00040000 */
#define CAN_F12R2_FB18         CAN_F12R2_FB18_Msk                              /*!<Filter bit 18 */
#define CAN_F12R2_FB19_Pos     (19U)
#define CAN_F12R2_FB19_Msk     (0x1UL << CAN_F12R2_FB19_Pos)                    /*!< 0x00080000 */
#define CAN_F12R2_FB19         CAN_F12R2_FB19_Msk                              /*!<Filter bit 19 */
#define CAN_F12R2_FB20_Pos     (20U)
#define CAN_F12R2_FB20_Msk     (0x1UL << CAN_F12R2_FB20_Pos)                    /*!< 0x00100000 */
#define CAN_F12R2_FB20         CAN_F12R2_FB20_Msk                              /*!<Filter bit 20 */
#define CAN_F12R2_FB21_Pos     (21U)
#define CAN_F12R2_FB21_Msk     (0x1UL << CAN_F12R2_FB21_Pos)                    /*!< 0x00200000 */
#define CAN_F12R2_FB21         CAN_F12R2_FB21_Msk                              /*!<Filter bit 21 */
#define CAN_F12R2_FB22_Pos     (22U)
#define CAN_F12R2_FB22_Msk     (0x1UL << CAN_F12R2_FB22_Pos)                    /*!< 0x00400000 */
#define CAN_F12R2_FB22         CAN_F12R2_FB22_Msk                              /*!<Filter bit 22 */
#define CAN_F12R2_FB23_Pos     (23U)
#define CAN_F12R2_FB23_Msk     (0x1UL << CAN_F12R2_FB23_Pos)                    /*!< 0x00800000 */
#define CAN_F12R2_FB23         CAN_F12R2_FB23_Msk                              /*!<Filter bit 23 */
#define CAN_F12R2_FB24_Pos     (24U)
#define CAN_F12R2_FB24_Msk     (0x1UL << CAN_F12R2_FB24_Pos)                    /*!< 0x01000000 */
#define CAN_F12R2_FB24         CAN_F12R2_FB24_Msk                              /*!<Filter bit 24 */
#define CAN_F12R2_FB25_Pos     (25U)
#define CAN_F12R2_FB25_Msk     (0x1UL << CAN_F12R2_FB25_Pos)                    /*!< 0x02000000 */
#define CAN_F12R2_FB25         CAN_F12R2_FB25_Msk                              /*!<Filter bit 25 */
#define CAN_F12R2_FB26_Pos     (26U)
#define CAN_F12R2_FB26_Msk     (0x1UL << CAN_F12R2_FB26_Pos)                    /*!< 0x04000000 */
#define CAN_F12R2_FB26         CAN_F12R2_FB26_Msk                              /*!<Filter bit 26 */
#define CAN_F12R2_FB27_Pos     (27U)
#define CAN_F12R2_FB27_Msk     (0x1UL << CAN_F12R2_FB27_Pos)                    /*!< 0x08000000 */
#define CAN_F12R2_FB27         CAN_F12R2_FB27_Msk                              /*!<Filter bit 27 */
#define CAN_F12R2_FB28_Pos     (28U)
#define CAN_F12R2_FB28_Msk     (0x1UL << CAN_F12R2_FB28_Pos)                    /*!< 0x10000000 */
#define CAN_F12R2_FB28         CAN_F12R2_FB28_Msk                              /*!<Filter bit 28 */
#define CAN_F12R2_FB29_Pos     (29U)
#define CAN_F12R2_FB29_Msk     (0x1UL << CAN_F12R2_FB29_Pos)                    /*!< 0x20000000 */
#define CAN_F12R2_FB29         CAN_F12R2_FB29_Msk                              /*!<Filter bit 29 */
#define CAN_F12R2_FB30_Pos     (30U)
#define CAN_F12R2_FB30_Msk     (0x1UL << CAN_F12R2_FB30_Pos)                    /*!< 0x40000000 */
#define CAN_F12R2_FB30         CAN_F12R2_FB30_Msk                              /*!<Filter bit 30 */
#define CAN_F12R2_FB31_Pos     (31U)
#define CAN_F12R2_FB31_Msk     (0x1UL << CAN_F12R2_FB31_Pos)                    /*!< 0x80000000 */
#define CAN_F12R2_FB31         CAN_F12R2_FB31_Msk                              /*!<Filter bit 31 */

/*******************  Bit definition for CAN_F13R2 register  ******************/
#define CAN_F13R2_FB0_Pos      (0U)
#define CAN_F13R2_FB0_Msk      (0x1UL << CAN_F13R2_FB0_Pos)                     /*!< 0x00000001 */
#define CAN_F13R2_FB0          CAN_F13R2_FB0_Msk                               /*!<Filter bit 0 */
#define CAN_F13R2_FB1_Pos      (1U)
#define CAN_F13R2_FB1_Msk      (0x1UL << CAN_F13R2_FB1_Pos)                     /*!< 0x00000002 */
#define CAN_F13R2_FB1          CAN_F13R2_FB1_Msk                               /*!<Filter bit 1 */
#define CAN_F13R2_FB2_Pos      (2U)
#define CAN_F13R2_FB2_Msk      (0x1UL << CAN_F13R2_FB2_Pos)                     /*!< 0x00000004 */
#define CAN_F13R2_FB2          CAN_F13R2_FB2_Msk                               /*!<Filter bit 2 */
#define CAN_F13R2_FB3_Pos      (3U)
#define CAN_F13R2_FB3_Msk      (0x1UL << CAN_F13R2_FB3_Pos)                     /*!< 0x00000008 */
#define CAN_F13R2_FB3          CAN_F13R2_FB3_Msk                               /*!<Filter bit 3 */
#define CAN_F13R2_FB4_Pos      (4U)
#define CAN_F13R2_FB4_Msk      (0x1UL << CAN_F13R2_FB4_Pos)                     /*!< 0x00000010 */
#define CAN_F13R2_FB4          CAN_F13R2_FB4_Msk                               /*!<Filter bit 4 */
#define CAN_F13R2_FB5_Pos      (5U)
#define CAN_F13R2_FB5_Msk      (0x1UL << CAN_F13R2_FB5_Pos)                     /*!< 0x00000020 */
#define CAN_F13R2_FB5          CAN_F13R2_FB5_Msk                               /*!<Filter bit 5 */
#define CAN_F13R2_FB6_Pos      (6U)
#define CAN_F13R2_FB6_Msk      (0x1UL << CAN_F13R2_FB6_Pos)                     /*!< 0x00000040 */
#define CAN_F13R2_FB6          CAN_F13R2_FB6_Msk                               /*!<Filter bit 6 */
#define CAN_F13R2_FB7_Pos      (7U)
#define CAN_F13R2_FB7_Msk      (0x1UL << CAN_F13R2_FB7_Pos)                     /*!< 0x00000080 */
#define CAN_F13R2_FB7          CAN_F13R2_FB7_Msk                               /*!<Filter bit 7 */
#define CAN_F13R2_FB8_Pos      (8U)
#define CAN_F13R2_FB8_Msk      (0x1UL << CAN_F13R2_FB8_Pos)                     /*!< 0x00000100 */
#define CAN_F13R2_FB8          CAN_F13R2_FB8_Msk                               /*!<Filter bit 8 */
#define CAN_F13R2_FB9_Pos      (9U)
#define CAN_F13R2_FB9_Msk      (0x1UL << CAN_F13R2_FB9_Pos)                     /*!< 0x00000200 */
#define CAN_F13R2_FB9          CAN_F13R2_FB9_Msk                               /*!<Filter bit 9 */
#define CAN_F13R2_FB10_Pos     (10U)
#define CAN_F13R2_FB10_Msk     (0x1UL << CAN_F13R2_FB10_Pos)                    /*!< 0x00000400 */
#define CAN_F13R2_FB10         CAN_F13R2_FB10_Msk                              /*!<Filter bit 10 */
#define CAN_F13R2_FB11_Pos     (11U)
#define CAN_F13R2_FB11_Msk     (0x1UL << CAN_F13R2_FB11_Pos)                    /*!< 0x00000800 */
#define CAN_F13R2_FB11         CAN_F13R2_FB11_Msk                              /*!<Filter bit 11 */
#define CAN_F13R2_FB12_Pos     (12U)
#define CAN_F13R2_FB12_Msk     (0x1UL << CAN_F13R2_FB12_Pos)                    /*!< 0x00001000 */
#define CAN_F13R2_FB12         CAN_F13R2_FB12_Msk                              /*!<Filter bit 12 */
#define CAN_F13R2_FB13_Pos     (13U)
#define CAN_F13R2_FB13_Msk     (0x1UL << CAN_F13R2_FB13_Pos)                    /*!< 0x00002000 */
#define CAN_F13R2_FB13         CAN_F13R2_FB13_Msk                              /*!<Filter bit 13 */
#define CAN_F13R2_FB14_Pos     (14U)
#define CAN_F13R2_FB14_Msk     (0x1UL << CAN_F13R2_FB14_Pos)                    /*!< 0x00004000 */
#define CAN_F13R2_FB14         CAN_F13R2_FB14_Msk                              /*!<Filter bit 14 */
#define CAN_F13R2_FB15_Pos     (15U)
#define CAN_F13R2_FB15_Msk     (0x1UL << CAN_F13R2_FB15_Pos)                    /*!< 0x00008000 */
#define CAN_F13R2_FB15         CAN_F13R2_FB15_Msk                              /*!<Filter bit 15 */
#define CAN_F13R2_FB16_Pos     (16U)
#define CAN_F13R2_FB16_Msk     (0x1UL << CAN_F13R2_FB16_Pos)                    /*!< 0x00010000 */
#define CAN_F13R2_FB16         CAN_F13R2_FB16_Msk                              /*!<Filter bit 16 */
#define CAN_F13R2_FB17_Pos     (17U)
#define CAN_F13R2_FB17_Msk     (0x1UL << CAN_F13R2_FB17_Pos)                    /*!< 0x00020000 */
#define CAN_F13R2_FB17         CAN_F13R2_FB17_Msk                              /*!<Filter bit 17 */
#define CAN_F13R2_FB18_Pos     (18U)
#define CAN_F13R2_FB18_Msk     (0x1UL << CAN_F13R2_FB18_Pos)                    /*!< 0x00040000 */
#define CAN_F13R2_FB18         CAN_F13R2_FB18_Msk                              /*!<Filter bit 18 */
#define CAN_F13R2_FB19_Pos     (19U)
#define CAN_F13R2_FB19_Msk     (0x1UL << CAN_F13R2_FB19_Pos)                    /*!< 0x00080000 */
#define CAN_F13R2_FB19         CAN_F13R2_FB19_Msk                              /*!<Filter bit 19 */
#define CAN_F13R2_FB20_Pos     (20U)
#define CAN_F13R2_FB20_Msk     (0x1UL << CAN_F13R2_FB20_Pos)                    /*!< 0x00100000 */
#define CAN_F13R2_FB20         CAN_F13R2_FB20_Msk                              /*!<Filter bit 20 */
#define CAN_F13R2_FB21_Pos     (21U)
#define CAN_F13R2_FB21_Msk     (0x1UL << CAN_F13R2_FB21_Pos)                    /*!< 0x00200000 */
#define CAN_F13R2_FB21         CAN_F13R2_FB21_Msk                              /*!<Filter bit 21 */
#define CAN_F13R2_FB22_Pos     (22U)
#define CAN_F13R2_FB22_Msk     (0x1UL << CAN_F13R2_FB22_Pos)                    /*!< 0x00400000 */
#define CAN_F13R2_FB22         CAN_F13R2_FB22_Msk                              /*!<Filter bit 22 */
#define CAN_F13R2_FB23_Pos     (23U)
#define CAN_F13R2_FB23_Msk     (0x1UL << CAN_F13R2_FB23_Pos)                    /*!< 0x00800000 */
#define CAN_F13R2_FB23         CAN_F13R2_FB23_Msk                              /*!<Filter bit 23 */
#define CAN_F13R2_FB24_Pos     (24U)
#define CAN_F13R2_FB24_Msk     (0x1UL << CAN_F13R2_FB24_Pos)                    /*!< 0x01000000 */
#define CAN_F13R2_FB24         CAN_F13R2_FB24_Msk                              /*!<Filter bit 24 */
#define CAN_F13R2_FB25_Pos     (25U)
#define CAN_F13R2_FB25_Msk     (0x1UL << CAN_F13R2_FB25_Pos)                    /*!< 0x02000000 */
#define CAN_F13R2_FB25         CAN_F13R2_FB25_Msk                              /*!<Filter bit 25 */
#define CAN_F13R2_FB26_Pos     (26U)
#define CAN_F13R2_FB26_Msk     (0x1UL << CAN_F13R2_FB26_Pos)                    /*!< 0x04000000 */
#define CAN_F13R2_FB26         CAN_F13R2_FB26_Msk                              /*!<Filter bit 26 */
#define CAN_F13R2_FB27_Pos     (27U)
#define CAN_F13R2_FB27_Msk     (0x1UL << CAN_F13R2_FB27_Pos)                    /*!< 0x08000000 */
#define CAN_F13R2_FB27         CAN_F13R2_FB27_Msk                              /*!<Filter bit 27 */
#define CAN_F13R2_FB28_Pos     (28U)
#define CAN_F13R2_FB28_Msk     (0x1UL << CAN_F13R2_FB28_Pos)                    /*!< 0x10000000 */
#define CAN_F13R2_FB28         CAN_F13R2_FB28_Msk                              /*!<Filter bit 28 */
#define CAN_F13R2_FB29_Pos     (29U)
#define CAN_F13R2_FB29_Msk     (0x1UL << CAN_F13R2_FB29_Pos)                    /*!< 0x20000000 */
#define CAN_F13R2_FB29         CAN_F13R2_FB29_Msk                              /*!<Filter bit 29 */
#define CAN_F13R2_FB30_Pos     (30U)
#define CAN_F13R2_FB30_Msk     (0x1UL << CAN_F13R2_FB30_Pos)                    /*!< 0x40000000 */
#define CAN_F13R2_FB30         CAN_F13R2_FB30_Msk                              /*!<Filter bit 30 */
#define CAN_F13R2_FB31_Pos     (31U)
#define CAN_F13R2_FB31_Msk     (0x1UL << CAN_F13R2_FB31_Pos)                    /*!< 0x80000000 */
#define CAN_F13R2_FB31         CAN_F13R2_FB31_Msk

//Simplified Definitions
#define CAN_FM1R_MaskMode              0UL//Identifier Mask Mode
#define CAN_FM1R_ListMode              1UL//Identifier List Mode

#define CAN_FS1R_D16                   0UL//Dual 16 bit scale
#define CAN_FS1R_S32                   1UL//Single 32 bit scale

#define CAN_FFA1R_FIFO0                0UL//Assigned to FIFO 0
#define CAN_FFA1R_FIFO1                1UL//Assigned to FIFO 1

#define GPIO_AFR_AFSEL_CAN             9UL

#define CAN_NORMAL                     0UL//Normal Mode operation

#define CAN_TIxR_Data                  0UL//Data Frame
#define CAN_TIxR_Remote                1UL//Remote Frame
#define CAN_RIxR_Data                  0UL//Data Frame
#define CAN_RIxR_Remote                1UL//Remote Frame

void CANx_GPIO(GPIO_TypeDef *Port_, uint8_t Pin_);
void CANx_SetMCRPred(CAN_Handler *canBus);
void CANx_Init(CAN_Handler * canBus, CAN_FilterTypeDef * fltr, CAN_DualFilterID_n_MaskTypeDef * fltr_ID2_Mask2, CAN_BitTimingTypeDef *tq, bool dual_mode, uint8_t nofltrCANslave,  uint8_t nofltrArray);
void CANx_CfgFilters(CAN_Handler * canBus, CAN_FilterTypeDef * fltr, CAN_DualFilterID_n_MaskTypeDef * fltr_ID2_Mask2, bool dual_mode, uint8_t nofltrCANslave ,uint8_t nofltrArray);
bool CANx_BitTiming(CAN_Handler * canBus, CAN_BitTimingTypeDef *tq);
void CANx_Tx(CAN_Handler * canBus, CAN_TxandRxHeader_TypeDef * TxHeader);
void CANx_TxData(CAN_Handler * canBus, CAN_TxandRxHeader_TypeDef * TxHeader);
void CANx_TxRemote(CAN_Handler * canBus, CAN_TxandRxHeader_TypeDef * TxHeader);
uint8_t CANx_RxFIFO0(CAN_Handler * canBus, CAN_TxandRxHeader_TypeDef * RxData);
uint8_t CANx_RxFIFO1(CAN_Handler * canBus, CAN_TxandRxHeader_TypeDef * RxData);
void CANx_BusOffRecovery(CAN_Handler * canBus);
void CAN1_TX_IRQHandler();
void CAN1_RX0_IRQHandler();
void CAN1_RX1_IRQHandler();
void CAN1_SCE_IRQHandler();
void CAN2_TX_IRQHandler();
void CAN2_RX0_IRQHandler();
void CAN2_RX1_IRQHandler();
void CAN2_SCE_IRQHandler();
void CANx_SetInt(CAN_Handler * canBus, uint32_t bitReg);
void CANx_ResetInt(CAN_Handler * canBus, uint32_t bitReg);
uint32_t CANx_GetError(CAN_Handler * canBus, uint32_t bitReg);
void CANx_EnTxInt(CAN_Handler * canBus);
void CANx_DisTxInt(CAN_Handler * canBus);
void CANx_EnFIFO0Ints(CAN_Handler * canBus);
void CANx_DisFIFO0Ints(CAN_Handler * canBus);
void CANx_EnFIFO1Ints(CAN_Handler * canBus);
void CANx_DisFIFO1Ints(CAN_Handler * canBus);
void CANx_EnSECInts(CAN_Handler * canBus);
void CANx_DisSECInts(CAN_Handler * canBus);
void CANx_EnWakeupInt(CAN_Handler * canBus);
void CANx_DisWakeupInt(CAN_Handler * canBus);
void CANx_EnSleepInt(CAN_Handler * canBus);
void CANx_DisSleepInt(CAN_Handler * canBus);
uint8_t CANx_GetTME(CAN_Handler * canBus, uint8_t index);
uint8_t CANx_GetLEC(CAN_Handler * canBus);
void CANx_SetLEC(CAN_Handler * canBus);
uint8_t CANx_GetREC(CAN_Handler * canBus);
uint8_t CANx_GetTEC(CAN_Handler * canBus);
bool CANx_TxSuccess(volatile uint32_t *SR, uint8_t indexMailBox);
void CANx_WaitSetFlag(volatile uint32_t *SR, uint32_t BitReg);
void CANx_WaitResetFlag(volatile uint32_t *SR, uint32_t BitReg);
void CANx_SetICPR(uint8_t x);

#endif /* DRIVERS_PERIPHERAL_INC_CANX_H_ */
