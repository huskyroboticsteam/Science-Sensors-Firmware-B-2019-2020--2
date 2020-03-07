/***************************************************************************//**
* \file .h
* \version 4.0
*
* \brief
*  This private file provides constants and parameter values for the
*  SCB Component in I2C mode.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_I2C_PVT_AirQuality2Click_H)
#define CY_SCB_I2C_PVT_AirQuality2Click_H

#include "AirQuality2Click_I2C.h"


/***************************************
*     Private Global Vars
***************************************/

extern volatile uint8 AirQuality2Click_state; /* Current state of I2C FSM */

#if(AirQuality2Click_I2C_SLAVE_CONST)
    extern volatile uint8 AirQuality2Click_slStatus;          /* Slave Status */

    /* Receive buffer variables */
    extern volatile uint8 * AirQuality2Click_slWrBufPtr;      /* Pointer to Receive buffer  */
    extern volatile uint32  AirQuality2Click_slWrBufSize;     /* Slave Receive buffer size  */
    extern volatile uint32  AirQuality2Click_slWrBufIndex;    /* Slave Receive buffer Index */

    /* Transmit buffer variables */
    extern volatile uint8 * AirQuality2Click_slRdBufPtr;      /* Pointer to Transmit buffer  */
    extern volatile uint32  AirQuality2Click_slRdBufSize;     /* Slave Transmit buffer size  */
    extern volatile uint32  AirQuality2Click_slRdBufIndex;    /* Slave Transmit buffer Index */
    extern volatile uint32  AirQuality2Click_slRdBufIndexTmp; /* Slave Transmit buffer Index Tmp */
    extern volatile uint8   AirQuality2Click_slOverFlowCount; /* Slave Transmit Overflow counter */
#endif /* (AirQuality2Click_I2C_SLAVE_CONST) */

#if(AirQuality2Click_I2C_MASTER_CONST)
    extern volatile uint16 AirQuality2Click_mstrStatus;      /* Master Status byte  */
    extern volatile uint8  AirQuality2Click_mstrControl;     /* Master Control byte */

    /* Receive buffer variables */
    extern volatile uint8 * AirQuality2Click_mstrRdBufPtr;   /* Pointer to Master Read buffer */
    extern volatile uint32  AirQuality2Click_mstrRdBufSize;  /* Master Read buffer size       */
    extern volatile uint32  AirQuality2Click_mstrRdBufIndex; /* Master Read buffer Index      */

    /* Transmit buffer variables */
    extern volatile uint8 * AirQuality2Click_mstrWrBufPtr;   /* Pointer to Master Write buffer */
    extern volatile uint32  AirQuality2Click_mstrWrBufSize;  /* Master Write buffer size       */
    extern volatile uint32  AirQuality2Click_mstrWrBufIndex; /* Master Write buffer Index      */
    extern volatile uint32  AirQuality2Click_mstrWrBufIndexTmp; /* Master Write buffer Index Tmp */
#endif /* (AirQuality2Click_I2C_MASTER_CONST) */

#if (AirQuality2Click_I2C_CUSTOM_ADDRESS_HANDLER_CONST)
    extern uint32 (*AirQuality2Click_customAddressHandler) (void);
#endif /* (AirQuality2Click_I2C_CUSTOM_ADDRESS_HANDLER_CONST) */

/***************************************
*     Private Function Prototypes
***************************************/

#if(AirQuality2Click_SCB_MODE_I2C_CONST_CFG)
    void AirQuality2Click_I2CInit(void);
#endif /* (AirQuality2Click_SCB_MODE_I2C_CONST_CFG) */

void AirQuality2Click_I2CStop(void);
void AirQuality2Click_I2CFwBlockReset(void);

void AirQuality2Click_I2CSaveConfig(void);
void AirQuality2Click_I2CRestoreConfig(void);

#if(AirQuality2Click_I2C_MASTER_CONST)
    void AirQuality2Click_I2CReStartGeneration(void);
#endif /* (AirQuality2Click_I2C_MASTER_CONST) */

#endif /* (CY_SCB_I2C_PVT_AirQuality2Click_H) */


/* [] END OF FILE */
