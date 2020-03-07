/*******************************************************************************
* File Name: SpectroscopySensor_SCBCLK.h
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

#if !defined(CY_CLOCK_SpectroscopySensor_SCBCLK_H)
#define CY_CLOCK_SpectroscopySensor_SCBCLK_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void SpectroscopySensor_SCBCLK_StartEx(uint32 alignClkDiv);
#define SpectroscopySensor_SCBCLK_Start() \
    SpectroscopySensor_SCBCLK_StartEx(SpectroscopySensor_SCBCLK__PA_DIV_ID)

#else

void SpectroscopySensor_SCBCLK_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void SpectroscopySensor_SCBCLK_Stop(void);

void SpectroscopySensor_SCBCLK_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 SpectroscopySensor_SCBCLK_GetDividerRegister(void);
uint8  SpectroscopySensor_SCBCLK_GetFractionalDividerRegister(void);

#define SpectroscopySensor_SCBCLK_Enable()                         SpectroscopySensor_SCBCLK_Start()
#define SpectroscopySensor_SCBCLK_Disable()                        SpectroscopySensor_SCBCLK_Stop()
#define SpectroscopySensor_SCBCLK_SetDividerRegister(clkDivider, reset)  \
    SpectroscopySensor_SCBCLK_SetFractionalDividerRegister((clkDivider), 0u)
#define SpectroscopySensor_SCBCLK_SetDivider(clkDivider)           SpectroscopySensor_SCBCLK_SetDividerRegister((clkDivider), 1u)
#define SpectroscopySensor_SCBCLK_SetDividerValue(clkDivider)      SpectroscopySensor_SCBCLK_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define SpectroscopySensor_SCBCLK_DIV_ID     SpectroscopySensor_SCBCLK__DIV_ID

#define SpectroscopySensor_SCBCLK_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define SpectroscopySensor_SCBCLK_CTRL_REG   (*(reg32 *)SpectroscopySensor_SCBCLK__CTRL_REGISTER)
#define SpectroscopySensor_SCBCLK_DIV_REG    (*(reg32 *)SpectroscopySensor_SCBCLK__DIV_REGISTER)

#define SpectroscopySensor_SCBCLK_CMD_DIV_SHIFT          (0u)
#define SpectroscopySensor_SCBCLK_CMD_PA_DIV_SHIFT       (8u)
#define SpectroscopySensor_SCBCLK_CMD_DISABLE_SHIFT      (30u)
#define SpectroscopySensor_SCBCLK_CMD_ENABLE_SHIFT       (31u)

#define SpectroscopySensor_SCBCLK_CMD_DISABLE_MASK       ((uint32)((uint32)1u << SpectroscopySensor_SCBCLK_CMD_DISABLE_SHIFT))
#define SpectroscopySensor_SCBCLK_CMD_ENABLE_MASK        ((uint32)((uint32)1u << SpectroscopySensor_SCBCLK_CMD_ENABLE_SHIFT))

#define SpectroscopySensor_SCBCLK_DIV_FRAC_MASK  (0x000000F8u)
#define SpectroscopySensor_SCBCLK_DIV_FRAC_SHIFT (3u)
#define SpectroscopySensor_SCBCLK_DIV_INT_MASK   (0xFFFFFF00u)
#define SpectroscopySensor_SCBCLK_DIV_INT_SHIFT  (8u)

#else 

#define SpectroscopySensor_SCBCLK_DIV_REG        (*(reg32 *)SpectroscopySensor_SCBCLK__REGISTER)
#define SpectroscopySensor_SCBCLK_ENABLE_REG     SpectroscopySensor_SCBCLK_DIV_REG
#define SpectroscopySensor_SCBCLK_DIV_FRAC_MASK  SpectroscopySensor_SCBCLK__FRAC_MASK
#define SpectroscopySensor_SCBCLK_DIV_FRAC_SHIFT (16u)
#define SpectroscopySensor_SCBCLK_DIV_INT_MASK   SpectroscopySensor_SCBCLK__DIVIDER_MASK
#define SpectroscopySensor_SCBCLK_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_SpectroscopySensor_SCBCLK_H) */

/* [] END OF FILE */
