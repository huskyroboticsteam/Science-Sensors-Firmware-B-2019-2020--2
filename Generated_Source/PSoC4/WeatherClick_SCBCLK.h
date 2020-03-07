/*******************************************************************************
* File Name: WeatherClick_SCBCLK.h
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

#if !defined(CY_CLOCK_WeatherClick_SCBCLK_H)
#define CY_CLOCK_WeatherClick_SCBCLK_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void WeatherClick_SCBCLK_StartEx(uint32 alignClkDiv);
#define WeatherClick_SCBCLK_Start() \
    WeatherClick_SCBCLK_StartEx(WeatherClick_SCBCLK__PA_DIV_ID)

#else

void WeatherClick_SCBCLK_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void WeatherClick_SCBCLK_Stop(void);

void WeatherClick_SCBCLK_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 WeatherClick_SCBCLK_GetDividerRegister(void);
uint8  WeatherClick_SCBCLK_GetFractionalDividerRegister(void);

#define WeatherClick_SCBCLK_Enable()                         WeatherClick_SCBCLK_Start()
#define WeatherClick_SCBCLK_Disable()                        WeatherClick_SCBCLK_Stop()
#define WeatherClick_SCBCLK_SetDividerRegister(clkDivider, reset)  \
    WeatherClick_SCBCLK_SetFractionalDividerRegister((clkDivider), 0u)
#define WeatherClick_SCBCLK_SetDivider(clkDivider)           WeatherClick_SCBCLK_SetDividerRegister((clkDivider), 1u)
#define WeatherClick_SCBCLK_SetDividerValue(clkDivider)      WeatherClick_SCBCLK_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define WeatherClick_SCBCLK_DIV_ID     WeatherClick_SCBCLK__DIV_ID

#define WeatherClick_SCBCLK_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define WeatherClick_SCBCLK_CTRL_REG   (*(reg32 *)WeatherClick_SCBCLK__CTRL_REGISTER)
#define WeatherClick_SCBCLK_DIV_REG    (*(reg32 *)WeatherClick_SCBCLK__DIV_REGISTER)

#define WeatherClick_SCBCLK_CMD_DIV_SHIFT          (0u)
#define WeatherClick_SCBCLK_CMD_PA_DIV_SHIFT       (8u)
#define WeatherClick_SCBCLK_CMD_DISABLE_SHIFT      (30u)
#define WeatherClick_SCBCLK_CMD_ENABLE_SHIFT       (31u)

#define WeatherClick_SCBCLK_CMD_DISABLE_MASK       ((uint32)((uint32)1u << WeatherClick_SCBCLK_CMD_DISABLE_SHIFT))
#define WeatherClick_SCBCLK_CMD_ENABLE_MASK        ((uint32)((uint32)1u << WeatherClick_SCBCLK_CMD_ENABLE_SHIFT))

#define WeatherClick_SCBCLK_DIV_FRAC_MASK  (0x000000F8u)
#define WeatherClick_SCBCLK_DIV_FRAC_SHIFT (3u)
#define WeatherClick_SCBCLK_DIV_INT_MASK   (0xFFFFFF00u)
#define WeatherClick_SCBCLK_DIV_INT_SHIFT  (8u)

#else 

#define WeatherClick_SCBCLK_DIV_REG        (*(reg32 *)WeatherClick_SCBCLK__REGISTER)
#define WeatherClick_SCBCLK_ENABLE_REG     WeatherClick_SCBCLK_DIV_REG
#define WeatherClick_SCBCLK_DIV_FRAC_MASK  WeatherClick_SCBCLK__FRAC_MASK
#define WeatherClick_SCBCLK_DIV_FRAC_SHIFT (16u)
#define WeatherClick_SCBCLK_DIV_INT_MASK   WeatherClick_SCBCLK__DIVIDER_MASK
#define WeatherClick_SCBCLK_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_WeatherClick_SCBCLK_H) */

/* [] END OF FILE */
