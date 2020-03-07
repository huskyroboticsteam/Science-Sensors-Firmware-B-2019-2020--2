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

#if !defined(CY_SCB_I2C_PVT_SpectroscopySensor_H)
#define CY_SCB_I2C_PVT_SpectroscopySensor_H

#include "SpectroscopySensor_I2C.h"


/***************************************
*     Private Global Vars
***************************************/

extern volatile uint8 SpectroscopySensor_state; /* Current state of I2C FSM */

#if(SpectroscopySensor_I2C_SLAVE_CONST)
    extern volatile uint8 SpectroscopySensor_slStatus;          /* Slave Status */

    /* Receive buffer variables */
    extern volatile uint8 * SpectroscopySensor_slWrBufPtr;      /* Pointer to Receive buffer  */
    extern volatile uint32  SpectroscopySensor_slWrBufSize;     /* Slave Receive buffer size  */
    extern volatile uint32  SpectroscopySensor_slWrBufIndex;    /* Slave Receive buffer Index */

    /* Transmit buffer variables */
    extern volatile uint8 * SpectroscopySensor_slRdBufPtr;      /* Pointer to Transmit buffer  */
    extern volatile uint32  SpectroscopySensor_slRdBufSize;     /* Slave Transmit buffer size  */
    extern volatile uint32  SpectroscopySensor_slRdBufIndex;    /* Slave Transmit buffer Index */
    extern volatile uint32  SpectroscopySensor_slRdBufIndexTmp; /* Slave Transmit buffer Index Tmp */
    extern volatile uint8   SpectroscopySensor_slOverFlowCount; /* Slave Transmit Overflow counter */
#endif /* (SpectroscopySensor_I2C_SLAVE_CONST) */

#if(SpectroscopySensor_I2C_MASTER_CONST)
    extern volatile uint16 SpectroscopySensor_mstrStatus;      /* Master Status byte  */
    extern volatile uint8  SpectroscopySensor_mstrControl;     /* Master Control byte */

    /* Receive buffer variables */
    extern volatile uint8 * SpectroscopySensor_mstrRdBufPtr;   /* Pointer to Master Read buffer */
    extern volatile uint32  SpectroscopySensor_mstrRdBufSize;  /* Master Read buffer size       */
    extern volatile uint32  SpectroscopySensor_mstrRdBufIndex; /* Master Read buffer Index      */

    /* Transmit buffer variables */
    extern volatile uint8 * SpectroscopySensor_mstrWrBufPtr;   /* Pointer to Master Write buffer */
    extern volatile uint32  SpectroscopySensor_mstrWrBufSize;  /* Master Write buffer size       */
    extern volatile uint32  SpectroscopySensor_mstrWrBufIndex; /* Master Write buffer Index      */
    extern volatile uint32  SpectroscopySensor_mstrWrBufIndexTmp; /* Master Write buffer Index Tmp */
#endif /* (SpectroscopySensor_I2C_MASTER_CONST) */

#if (SpectroscopySensor_I2C_CUSTOM_ADDRESS_HANDLER_CONST)
    extern uint32 (*SpectroscopySensor_customAddressHandler) (void);
#endif /* (SpectroscopySensor_I2C_CUSTOM_ADDRESS_HANDLER_CONST) */

/***************************************
*     Private Function Prototypes
***************************************/

#if(SpectroscopySensor_SCB_MODE_I2C_CONST_CFG)
    void SpectroscopySensor_I2CInit(void);
#endif /* (SpectroscopySensor_SCB_MODE_I2C_CONST_CFG) */

void SpectroscopySensor_I2CStop(void);
void SpectroscopySensor_I2CFwBlockReset(void);

void SpectroscopySensor_I2CSaveConfig(void);
void SpectroscopySensor_I2CRestoreConfig(void);

#if(SpectroscopySensor_I2C_MASTER_CONST)
    void SpectroscopySensor_I2CReStartGeneration(void);
#endif /* (SpectroscopySensor_I2C_MASTER_CONST) */

#endif /* (CY_SCB_I2C_PVT_SpectroscopySensor_H) */


/* [] END OF FILE */
