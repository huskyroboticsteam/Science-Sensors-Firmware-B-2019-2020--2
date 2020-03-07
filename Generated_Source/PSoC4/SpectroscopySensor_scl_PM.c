/*******************************************************************************
* File Name: SpectroscopySensor_scl.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "SpectroscopySensor_scl.h"

static SpectroscopySensor_scl_BACKUP_STRUCT  SpectroscopySensor_scl_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: SpectroscopySensor_scl_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function applies only to SIO and USBIO pins.
*  It should not be called for GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet SpectroscopySensor_scl_SUT.c usage_SpectroscopySensor_scl_Sleep_Wakeup
*******************************************************************************/
void SpectroscopySensor_scl_Sleep(void)
{
    #if defined(SpectroscopySensor_scl__PC)
        SpectroscopySensor_scl_backup.pcState = SpectroscopySensor_scl_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            SpectroscopySensor_scl_backup.usbState = SpectroscopySensor_scl_CR1_REG;
            SpectroscopySensor_scl_USB_POWER_REG |= SpectroscopySensor_scl_USBIO_ENTER_SLEEP;
            SpectroscopySensor_scl_CR1_REG &= SpectroscopySensor_scl_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(SpectroscopySensor_scl__SIO)
        SpectroscopySensor_scl_backup.sioState = SpectroscopySensor_scl_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        SpectroscopySensor_scl_SIO_REG &= (uint32)(~SpectroscopySensor_scl_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: SpectroscopySensor_scl_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep(). This 
* function applies only to SIO and USBIO pins. It should not be called for
* GPIO or GPIO_OVT pins.
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to SpectroscopySensor_scl_Sleep() for an example usage.
*******************************************************************************/
void SpectroscopySensor_scl_Wakeup(void)
{
    #if defined(SpectroscopySensor_scl__PC)
        SpectroscopySensor_scl_PC = SpectroscopySensor_scl_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            SpectroscopySensor_scl_USB_POWER_REG &= SpectroscopySensor_scl_USBIO_EXIT_SLEEP_PH1;
            SpectroscopySensor_scl_CR1_REG = SpectroscopySensor_scl_backup.usbState;
            SpectroscopySensor_scl_USB_POWER_REG &= SpectroscopySensor_scl_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(SpectroscopySensor_scl__SIO)
        SpectroscopySensor_scl_SIO_REG = SpectroscopySensor_scl_backup.sioState;
    #endif
}


/* [] END OF FILE */
