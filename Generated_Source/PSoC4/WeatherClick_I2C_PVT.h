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

#if !defined(CY_SCB_I2C_PVT_WeatherClick_H)
#define CY_SCB_I2C_PVT_WeatherClick_H

#include "WeatherClick_I2C.h"


/***************************************
*     Private Global Vars
***************************************/

extern volatile uint8 WeatherClick_state; /* Current state of I2C FSM */

#if(WeatherClick_I2C_SLAVE_CONST)
    extern volatile uint8 WeatherClick_slStatus;          /* Slave Status */

    /* Receive buffer variables */
    extern volatile uint8 * WeatherClick_slWrBufPtr;      /* Pointer to Receive buffer  */
    extern volatile uint32  WeatherClick_slWrBufSize;     /* Slave Receive buffer size  */
    extern volatile uint32  WeatherClick_slWrBufIndex;    /* Slave Receive buffer Index */

    /* Transmit buffer variables */
    extern volatile uint8 * WeatherClick_slRdBufPtr;      /* Pointer to Transmit buffer  */
    extern volatile uint32  WeatherClick_slRdBufSize;     /* Slave Transmit buffer size  */
    extern volatile uint32  WeatherClick_slRdBufIndex;    /* Slave Transmit buffer Index */
    extern volatile uint32  WeatherClick_slRdBufIndexTmp; /* Slave Transmit buffer Index Tmp */
    extern volatile uint8   WeatherClick_slOverFlowCount; /* Slave Transmit Overflow counter */
#endif /* (WeatherClick_I2C_SLAVE_CONST) */

#if(WeatherClick_I2C_MASTER_CONST)
    extern volatile uint16 WeatherClick_mstrStatus;      /* Master Status byte  */
    extern volatile uint8  WeatherClick_mstrControl;     /* Master Control byte */

    /* Receive buffer variables */
    extern volatile uint8 * WeatherClick_mstrRdBufPtr;   /* Pointer to Master Read buffer */
    extern volatile uint32  WeatherClick_mstrRdBufSize;  /* Master Read buffer size       */
    extern volatile uint32  WeatherClick_mstrRdBufIndex; /* Master Read buffer Index      */

    /* Transmit buffer variables */
    extern volatile uint8 * WeatherClick_mstrWrBufPtr;   /* Pointer to Master Write buffer */
    extern volatile uint32  WeatherClick_mstrWrBufSize;  /* Master Write buffer size       */
    extern volatile uint32  WeatherClick_mstrWrBufIndex; /* Master Write buffer Index      */
    extern volatile uint32  WeatherClick_mstrWrBufIndexTmp; /* Master Write buffer Index Tmp */
#endif /* (WeatherClick_I2C_MASTER_CONST) */

#if (WeatherClick_I2C_CUSTOM_ADDRESS_HANDLER_CONST)
    extern uint32 (*WeatherClick_customAddressHandler) (void);
#endif /* (WeatherClick_I2C_CUSTOM_ADDRESS_HANDLER_CONST) */

/***************************************
*     Private Function Prototypes
***************************************/

#if(WeatherClick_SCB_MODE_I2C_CONST_CFG)
    void WeatherClick_I2CInit(void);
#endif /* (WeatherClick_SCB_MODE_I2C_CONST_CFG) */

void WeatherClick_I2CStop(void);
void WeatherClick_I2CFwBlockReset(void);

void WeatherClick_I2CSaveConfig(void);
void WeatherClick_I2CRestoreConfig(void);

#if(WeatherClick_I2C_MASTER_CONST)
    void WeatherClick_I2CReStartGeneration(void);
#endif /* (WeatherClick_I2C_MASTER_CONST) */

#endif /* (CY_SCB_I2C_PVT_WeatherClick_H) */


/* [] END OF FILE */
