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

#if !defined(CY_SCB_I2C_PVT_UVSensor_H)
#define CY_SCB_I2C_PVT_UVSensor_H

#include "UVSensor_I2C.h"


/***************************************
*     Private Global Vars
***************************************/

extern volatile uint8 UVSensor_state; /* Current state of I2C FSM */

#if(UVSensor_I2C_SLAVE_CONST)
    extern volatile uint8 UVSensor_slStatus;          /* Slave Status */

    /* Receive buffer variables */
    extern volatile uint8 * UVSensor_slWrBufPtr;      /* Pointer to Receive buffer  */
    extern volatile uint32  UVSensor_slWrBufSize;     /* Slave Receive buffer size  */
    extern volatile uint32  UVSensor_slWrBufIndex;    /* Slave Receive buffer Index */

    /* Transmit buffer variables */
    extern volatile uint8 * UVSensor_slRdBufPtr;      /* Pointer to Transmit buffer  */
    extern volatile uint32  UVSensor_slRdBufSize;     /* Slave Transmit buffer size  */
    extern volatile uint32  UVSensor_slRdBufIndex;    /* Slave Transmit buffer Index */
    extern volatile uint32  UVSensor_slRdBufIndexTmp; /* Slave Transmit buffer Index Tmp */
    extern volatile uint8   UVSensor_slOverFlowCount; /* Slave Transmit Overflow counter */
#endif /* (UVSensor_I2C_SLAVE_CONST) */

#if(UVSensor_I2C_MASTER_CONST)
    extern volatile uint16 UVSensor_mstrStatus;      /* Master Status byte  */
    extern volatile uint8  UVSensor_mstrControl;     /* Master Control byte */

    /* Receive buffer variables */
    extern volatile uint8 * UVSensor_mstrRdBufPtr;   /* Pointer to Master Read buffer */
    extern volatile uint32  UVSensor_mstrRdBufSize;  /* Master Read buffer size       */
    extern volatile uint32  UVSensor_mstrRdBufIndex; /* Master Read buffer Index      */

    /* Transmit buffer variables */
    extern volatile uint8 * UVSensor_mstrWrBufPtr;   /* Pointer to Master Write buffer */
    extern volatile uint32  UVSensor_mstrWrBufSize;  /* Master Write buffer size       */
    extern volatile uint32  UVSensor_mstrWrBufIndex; /* Master Write buffer Index      */
    extern volatile uint32  UVSensor_mstrWrBufIndexTmp; /* Master Write buffer Index Tmp */
#endif /* (UVSensor_I2C_MASTER_CONST) */

#if (UVSensor_I2C_CUSTOM_ADDRESS_HANDLER_CONST)
    extern uint32 (*UVSensor_customAddressHandler) (void);
#endif /* (UVSensor_I2C_CUSTOM_ADDRESS_HANDLER_CONST) */

/***************************************
*     Private Function Prototypes
***************************************/

#if(UVSensor_SCB_MODE_I2C_CONST_CFG)
    void UVSensor_I2CInit(void);
#endif /* (UVSensor_SCB_MODE_I2C_CONST_CFG) */

void UVSensor_I2CStop(void);
void UVSensor_I2CFwBlockReset(void);

void UVSensor_I2CSaveConfig(void);
void UVSensor_I2CRestoreConfig(void);

#if(UVSensor_I2C_MASTER_CONST)
    void UVSensor_I2CReStartGeneration(void);
#endif /* (UVSensor_I2C_MASTER_CONST) */

#endif /* (CY_SCB_I2C_PVT_UVSensor_H) */


/* [] END OF FILE */
