/*******************************************************************************
* File Name: WeatherClick_scl.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_WeatherClick_scl_ALIASES_H) /* Pins WeatherClick_scl_ALIASES_H */
#define CY_PINS_WeatherClick_scl_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define WeatherClick_scl_0			(WeatherClick_scl__0__PC)
#define WeatherClick_scl_0_PS		(WeatherClick_scl__0__PS)
#define WeatherClick_scl_0_PC		(WeatherClick_scl__0__PC)
#define WeatherClick_scl_0_DR		(WeatherClick_scl__0__DR)
#define WeatherClick_scl_0_SHIFT	(WeatherClick_scl__0__SHIFT)
#define WeatherClick_scl_0_INTR	((uint16)((uint16)0x0003u << (WeatherClick_scl__0__SHIFT*2u)))

#define WeatherClick_scl_INTR_ALL	 ((uint16)(WeatherClick_scl_0_INTR))


#endif /* End Pins WeatherClick_scl_ALIASES_H */


/* [] END OF FILE */
