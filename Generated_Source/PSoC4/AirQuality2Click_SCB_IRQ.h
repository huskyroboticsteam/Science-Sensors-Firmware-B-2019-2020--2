/*******************************************************************************
* File Name: AirQuality2Click_SCB_IRQ.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_AirQuality2Click_SCB_IRQ_H)
#define CY_ISR_AirQuality2Click_SCB_IRQ_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void AirQuality2Click_SCB_IRQ_Start(void);
void AirQuality2Click_SCB_IRQ_StartEx(cyisraddress address);
void AirQuality2Click_SCB_IRQ_Stop(void);

CY_ISR_PROTO(AirQuality2Click_SCB_IRQ_Interrupt);

void AirQuality2Click_SCB_IRQ_SetVector(cyisraddress address);
cyisraddress AirQuality2Click_SCB_IRQ_GetVector(void);

void AirQuality2Click_SCB_IRQ_SetPriority(uint8 priority);
uint8 AirQuality2Click_SCB_IRQ_GetPriority(void);

void AirQuality2Click_SCB_IRQ_Enable(void);
uint8 AirQuality2Click_SCB_IRQ_GetState(void);
void AirQuality2Click_SCB_IRQ_Disable(void);

void AirQuality2Click_SCB_IRQ_SetPending(void);
void AirQuality2Click_SCB_IRQ_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the AirQuality2Click_SCB_IRQ ISR. */
#define AirQuality2Click_SCB_IRQ_INTC_VECTOR            ((reg32 *) AirQuality2Click_SCB_IRQ__INTC_VECT)

/* Address of the AirQuality2Click_SCB_IRQ ISR priority. */
#define AirQuality2Click_SCB_IRQ_INTC_PRIOR             ((reg32 *) AirQuality2Click_SCB_IRQ__INTC_PRIOR_REG)

/* Priority of the AirQuality2Click_SCB_IRQ interrupt. */
#define AirQuality2Click_SCB_IRQ_INTC_PRIOR_NUMBER      AirQuality2Click_SCB_IRQ__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable AirQuality2Click_SCB_IRQ interrupt. */
#define AirQuality2Click_SCB_IRQ_INTC_SET_EN            ((reg32 *) AirQuality2Click_SCB_IRQ__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the AirQuality2Click_SCB_IRQ interrupt. */
#define AirQuality2Click_SCB_IRQ_INTC_CLR_EN            ((reg32 *) AirQuality2Click_SCB_IRQ__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the AirQuality2Click_SCB_IRQ interrupt state to pending. */
#define AirQuality2Click_SCB_IRQ_INTC_SET_PD            ((reg32 *) AirQuality2Click_SCB_IRQ__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the AirQuality2Click_SCB_IRQ interrupt. */
#define AirQuality2Click_SCB_IRQ_INTC_CLR_PD            ((reg32 *) AirQuality2Click_SCB_IRQ__INTC_CLR_PD_REG)



#endif /* CY_ISR_AirQuality2Click_SCB_IRQ_H */


/* [] END OF FILE */
