/*******************************************************************************
* File Name: AirQuality2Click_SCBCLK.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_AirQuality2Click_SCBCLK_H)
#define CY_CLOCK_AirQuality2Click_SCBCLK_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void AirQuality2Click_SCBCLK_StartEx(uint32 alignClkDiv);
#define AirQuality2Click_SCBCLK_Start() \
    AirQuality2Click_SCBCLK_StartEx(AirQuality2Click_SCBCLK__PA_DIV_ID)

#else

void AirQuality2Click_SCBCLK_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void AirQuality2Click_SCBCLK_Stop(void);

void AirQuality2Click_SCBCLK_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 AirQuality2Click_SCBCLK_GetDividerRegister(void);
uint8  AirQuality2Click_SCBCLK_GetFractionalDividerRegister(void);

#define AirQuality2Click_SCBCLK_Enable()                         AirQuality2Click_SCBCLK_Start()
#define AirQuality2Click_SCBCLK_Disable()                        AirQuality2Click_SCBCLK_Stop()
#define AirQuality2Click_SCBCLK_SetDividerRegister(clkDivider, reset)  \
    AirQuality2Click_SCBCLK_SetFractionalDividerRegister((clkDivider), 0u)
#define AirQuality2Click_SCBCLK_SetDivider(clkDivider)           AirQuality2Click_SCBCLK_SetDividerRegister((clkDivider), 1u)
#define AirQuality2Click_SCBCLK_SetDividerValue(clkDivider)      AirQuality2Click_SCBCLK_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define AirQuality2Click_SCBCLK_DIV_ID     AirQuality2Click_SCBCLK__DIV_ID

#define AirQuality2Click_SCBCLK_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define AirQuality2Click_SCBCLK_CTRL_REG   (*(reg32 *)AirQuality2Click_SCBCLK__CTRL_REGISTER)
#define AirQuality2Click_SCBCLK_DIV_REG    (*(reg32 *)AirQuality2Click_SCBCLK__DIV_REGISTER)

#define AirQuality2Click_SCBCLK_CMD_DIV_SHIFT          (0u)
#define AirQuality2Click_SCBCLK_CMD_PA_DIV_SHIFT       (8u)
#define AirQuality2Click_SCBCLK_CMD_DISABLE_SHIFT      (30u)
#define AirQuality2Click_SCBCLK_CMD_ENABLE_SHIFT       (31u)

#define AirQuality2Click_SCBCLK_CMD_DISABLE_MASK       ((uint32)((uint32)1u << AirQuality2Click_SCBCLK_CMD_DISABLE_SHIFT))
#define AirQuality2Click_SCBCLK_CMD_ENABLE_MASK        ((uint32)((uint32)1u << AirQuality2Click_SCBCLK_CMD_ENABLE_SHIFT))

#define AirQuality2Click_SCBCLK_DIV_FRAC_MASK  (0x000000F8u)
#define AirQuality2Click_SCBCLK_DIV_FRAC_SHIFT (3u)
#define AirQuality2Click_SCBCLK_DIV_INT_MASK   (0xFFFFFF00u)
#define AirQuality2Click_SCBCLK_DIV_INT_SHIFT  (8u)

#else 

#define AirQuality2Click_SCBCLK_DIV_REG        (*(reg32 *)AirQuality2Click_SCBCLK__REGISTER)
#define AirQuality2Click_SCBCLK_ENABLE_REG     AirQuality2Click_SCBCLK_DIV_REG
#define AirQuality2Click_SCBCLK_DIV_FRAC_MASK  AirQuality2Click_SCBCLK__FRAC_MASK
#define AirQuality2Click_SCBCLK_DIV_FRAC_SHIFT (16u)
#define AirQuality2Click_SCBCLK_DIV_INT_MASK   AirQuality2Click_SCBCLK__DIVIDER_MASK
#define AirQuality2Click_SCBCLK_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_AirQuality2Click_SCBCLK_H) */

/* [] END OF FILE */
