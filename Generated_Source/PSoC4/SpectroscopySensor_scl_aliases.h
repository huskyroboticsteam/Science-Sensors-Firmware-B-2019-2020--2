/*******************************************************************************
* File Name: SpectroscopySensor_scl.h  
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

#if !defined(CY_PINS_SpectroscopySensor_scl_ALIASES_H) /* Pins SpectroscopySensor_scl_ALIASES_H */
#define CY_PINS_SpectroscopySensor_scl_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define SpectroscopySensor_scl_0			(SpectroscopySensor_scl__0__PC)
#define SpectroscopySensor_scl_0_PS		(SpectroscopySensor_scl__0__PS)
#define SpectroscopySensor_scl_0_PC		(SpectroscopySensor_scl__0__PC)
#define SpectroscopySensor_scl_0_DR		(SpectroscopySensor_scl__0__DR)
#define SpectroscopySensor_scl_0_SHIFT	(SpectroscopySensor_scl__0__SHIFT)
#define SpectroscopySensor_scl_0_INTR	((uint16)((uint16)0x0003u << (SpectroscopySensor_scl__0__SHIFT*2u)))

#define SpectroscopySensor_scl_INTR_ALL	 ((uint16)(SpectroscopySensor_scl_0_INTR))


#endif /* End Pins SpectroscopySensor_scl_ALIASES_H */


/* [] END OF FILE */
