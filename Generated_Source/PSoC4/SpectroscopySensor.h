/***************************************************************************//**
* \file SpectroscopySensor.h
* \version 4.0
*
* \brief
*  This file provides constants and parameter values for the SCB Component.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_SpectroscopySensor_H)
#define CY_SCB_SpectroscopySensor_H

#include <cydevice_trm.h>
#include <cyfitter.h>
#include <cytypes.h>
#include <CyLib.h>

/* SCB IP block v0 is available in PSoC 4100/PSoC 4200 */
#define SpectroscopySensor_CY_SCBIP_V0    (CYIPBLOCK_m0s8scb_VERSION == 0u)
/* SCB IP block v1 is available in PSoC 4000 */
#define SpectroscopySensor_CY_SCBIP_V1    (CYIPBLOCK_m0s8scb_VERSION == 1u)
/* SCB IP block v2 is available in all other devices */
#define SpectroscopySensor_CY_SCBIP_V2    (CYIPBLOCK_m0s8scb_VERSION >= 2u)

/** Component version major.minor */
#define SpectroscopySensor_COMP_VERSION_MAJOR    (4)
#define SpectroscopySensor_COMP_VERSION_MINOR    (0)
    
#define SpectroscopySensor_SCB_MODE           (1u)

/* SCB modes enum */
#define SpectroscopySensor_SCB_MODE_I2C       (0x01u)
#define SpectroscopySensor_SCB_MODE_SPI       (0x02u)
#define SpectroscopySensor_SCB_MODE_UART      (0x04u)
#define SpectroscopySensor_SCB_MODE_EZI2C     (0x08u)
#define SpectroscopySensor_SCB_MODE_UNCONFIG  (0xFFu)

/* Condition compilation depends on operation mode: Unconfigured implies apply to all modes */
#define SpectroscopySensor_SCB_MODE_I2C_CONST_CFG       (SpectroscopySensor_SCB_MODE_I2C       == SpectroscopySensor_SCB_MODE)
#define SpectroscopySensor_SCB_MODE_SPI_CONST_CFG       (SpectroscopySensor_SCB_MODE_SPI       == SpectroscopySensor_SCB_MODE)
#define SpectroscopySensor_SCB_MODE_UART_CONST_CFG      (SpectroscopySensor_SCB_MODE_UART      == SpectroscopySensor_SCB_MODE)
#define SpectroscopySensor_SCB_MODE_EZI2C_CONST_CFG     (SpectroscopySensor_SCB_MODE_EZI2C     == SpectroscopySensor_SCB_MODE)
#define SpectroscopySensor_SCB_MODE_UNCONFIG_CONST_CFG  (SpectroscopySensor_SCB_MODE_UNCONFIG  == SpectroscopySensor_SCB_MODE)

/* Condition compilation for includes */
#define SpectroscopySensor_SCB_MODE_I2C_INC      (0u !=(SpectroscopySensor_SCB_MODE_I2C   & SpectroscopySensor_SCB_MODE))
#define SpectroscopySensor_SCB_MODE_EZI2C_INC    (0u !=(SpectroscopySensor_SCB_MODE_EZI2C & SpectroscopySensor_SCB_MODE))
#if (!SpectroscopySensor_CY_SCBIP_V1)
    #define SpectroscopySensor_SCB_MODE_SPI_INC  (0u !=(SpectroscopySensor_SCB_MODE_SPI   & SpectroscopySensor_SCB_MODE))
    #define SpectroscopySensor_SCB_MODE_UART_INC (0u !=(SpectroscopySensor_SCB_MODE_UART  & SpectroscopySensor_SCB_MODE))
#else
    #define SpectroscopySensor_SCB_MODE_SPI_INC  (0u)
    #define SpectroscopySensor_SCB_MODE_UART_INC (0u)
#endif /* (!SpectroscopySensor_CY_SCBIP_V1) */

/* Interrupts remove options */
#define SpectroscopySensor_REMOVE_SCB_IRQ             (0u)
#define SpectroscopySensor_SCB_IRQ_INTERNAL           (0u == SpectroscopySensor_REMOVE_SCB_IRQ)

#define SpectroscopySensor_REMOVE_UART_RX_WAKEUP_IRQ  (1u)
#define SpectroscopySensor_UART_RX_WAKEUP_IRQ         (0u == SpectroscopySensor_REMOVE_UART_RX_WAKEUP_IRQ)

/* SCB interrupt enum */
#define SpectroscopySensor_SCB_INTR_MODE_NONE     (0u)
#define SpectroscopySensor_SCB_INTR_MODE_INTERNAL (1u)
#define SpectroscopySensor_SCB_INTR_MODE_EXTERNAL (2u)

/* Internal clock remove option */
#define SpectroscopySensor_REMOVE_SCB_CLK     (0u)
#define SpectroscopySensor_SCB_CLK_INTERNAL   (0u == SpectroscopySensor_REMOVE_SCB_CLK)


/***************************************
*       Includes
****************************************/

#include "SpectroscopySensor_PINS.h"

#if (SpectroscopySensor_SCB_CLK_INTERNAL)
    #include "SpectroscopySensor_SCBCLK.h"
#endif /* (SpectroscopySensor_SCB_CLK_INTERNAL) */


/***************************************
*       Type Definitions
***************************************/

typedef struct
{
    uint8 enableState;
} SpectroscopySensor_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

/**
* \addtogroup group_general
* @{
*/

/* Start and Stop APIs */
void SpectroscopySensor_Init(void);
void SpectroscopySensor_Enable(void);
void SpectroscopySensor_Start(void);
void SpectroscopySensor_Stop(void);

/** @} general */

/**
* \addtogroup group_power
* @{
*/
/* Sleep and Wakeup APis */
void SpectroscopySensor_Sleep(void);
void SpectroscopySensor_Wakeup(void);
/** @} power */ 

/**
* \addtogroup group_interrupt
* @{
*/
#if (SpectroscopySensor_SCB_IRQ_INTERNAL)
    /* Custom interrupt handler */
    void SpectroscopySensor_SetCustomInterruptHandler(void (*func)(void));
#endif /* (SpectroscopySensor_SCB_IRQ_INTERNAL) */
/** @} interrupt */

/* Interface to internal interrupt component */
#if (SpectroscopySensor_SCB_IRQ_INTERNAL)
    /**
    * \addtogroup group_interrupt
    * @{
    */    
    /*******************************************************************************
    * Function Name: SpectroscopySensor_EnableInt
    ****************************************************************************//**
    *
    *  When using an Internal interrupt, this enables the interrupt in the NVIC. 
    *  When using an external interrupt the API for the interrupt component must 
    *  be used to enable the interrupt.
    *
    *******************************************************************************/
    #define SpectroscopySensor_EnableInt()    CyIntEnable(SpectroscopySensor_ISR_NUMBER)
    
    
    /*******************************************************************************
    * Function Name: SpectroscopySensor_DisableInt
    ****************************************************************************//**
    *
    *  When using an Internal interrupt, this disables the interrupt in the NVIC. 
    *  When using an external interrupt the API for the interrupt component must 
    *  be used to disable the interrupt.
    *
    *******************************************************************************/    
    #define SpectroscopySensor_DisableInt()   CyIntDisable(SpectroscopySensor_ISR_NUMBER)
    /** @} interrupt */

    /*******************************************************************************
    * Function Name: SpectroscopySensor_ClearPendingInt
    ****************************************************************************//**
    *
    *  This function clears the interrupt pending status in the NVIC. 
    *
    *******************************************************************************/
    #define SpectroscopySensor_ClearPendingInt()  CyIntClearPending(SpectroscopySensor_ISR_NUMBER)
#endif /* (SpectroscopySensor_SCB_IRQ_INTERNAL) */

#if (SpectroscopySensor_UART_RX_WAKEUP_IRQ)
    /*******************************************************************************
    * Function Name: SpectroscopySensor_RxWakeEnableInt
    ****************************************************************************//**
    *
    *  This function enables the interrupt (RX_WAKE) pending status in the NVIC. 
    *
    *******************************************************************************/    
    #define SpectroscopySensor_RxWakeEnableInt()  CyIntEnable(SpectroscopySensor_RX_WAKE_ISR_NUMBER)
    

    /*******************************************************************************
    * Function Name: SpectroscopySensor_RxWakeDisableInt
    ****************************************************************************//**
    *
    *  This function disables the interrupt (RX_WAKE) pending status in the NVIC.  
    *
    *******************************************************************************/
    #define SpectroscopySensor_RxWakeDisableInt() CyIntDisable(SpectroscopySensor_RX_WAKE_ISR_NUMBER)
    
    
    /*******************************************************************************
    * Function Name: SpectroscopySensor_RxWakeClearPendingInt
    ****************************************************************************//**
    *
    *  This function clears the interrupt (RX_WAKE) pending status in the NVIC. 
    *
    *******************************************************************************/    
    #define SpectroscopySensor_RxWakeClearPendingInt()  CyIntClearPending(SpectroscopySensor_RX_WAKE_ISR_NUMBER)
#endif /* (SpectroscopySensor_UART_RX_WAKEUP_IRQ) */

/**
* \addtogroup group_interrupt
* @{
*/
/* Get interrupt cause */
/*******************************************************************************
* Function Name: SpectroscopySensor_GetInterruptCause
****************************************************************************//**
*
*  Returns a mask of bits showing the source of the current triggered interrupt. 
*  This is useful for modes of operation where an interrupt can be generated by 
*  conditions in multiple interrupt source registers.
*
*  \return
*   Mask with the OR of the following conditions that have been triggered.
*    - SpectroscopySensor_INTR_CAUSE_MASTER - Interrupt from Master
*    - SpectroscopySensor_INTR_CAUSE_SLAVE - Interrupt from Slave
*    - SpectroscopySensor_INTR_CAUSE_TX - Interrupt from TX
*    - SpectroscopySensor_INTR_CAUSE_RX - Interrupt from RX
*
*******************************************************************************/
#define SpectroscopySensor_GetInterruptCause()    (SpectroscopySensor_INTR_CAUSE_REG)


/* APIs to service INTR_RX register */
/*******************************************************************************
* Function Name: SpectroscopySensor_GetRxInterruptSource
****************************************************************************//**
*
*  Returns RX interrupt request register. This register contains current status 
*  of RX interrupt sources.
*
*  \return
*   Current status of RX interrupt sources.
*   Each constant is a bit field value. The value returned may have multiple 
*   bits set to indicate the current status.
*   - SpectroscopySensor_INTR_RX_FIFO_LEVEL - The number of data elements in the 
      RX FIFO is greater than the value of RX FIFO level.
*   - SpectroscopySensor_INTR_RX_NOT_EMPTY - Receiver FIFO is not empty.
*   - SpectroscopySensor_INTR_RX_FULL - Receiver FIFO is full.
*   - SpectroscopySensor_INTR_RX_OVERFLOW - Attempt to write to a full 
*     receiver FIFO.
*   - SpectroscopySensor_INTR_RX_UNDERFLOW - Attempt to read from an empty 
*     receiver FIFO.
*   - SpectroscopySensor_INTR_RX_FRAME_ERROR - UART framing error detected.
*   - SpectroscopySensor_INTR_RX_PARITY_ERROR - UART parity error detected.
*
*******************************************************************************/
#define SpectroscopySensor_GetRxInterruptSource() (SpectroscopySensor_INTR_RX_REG)


/*******************************************************************************
* Function Name: SpectroscopySensor_SetRxInterruptMode
****************************************************************************//**
*
*  Writes RX interrupt mask register. This register configures which bits from 
*  RX interrupt request register will trigger an interrupt event.
*
*  \param interruptMask: RX interrupt sources to be enabled (refer to 
*   SpectroscopySensor_GetRxInterruptSource() function for bit fields values).
*
*******************************************************************************/
#define SpectroscopySensor_SetRxInterruptMode(interruptMask)     SpectroscopySensor_WRITE_INTR_RX_MASK(interruptMask)


/*******************************************************************************
* Function Name: SpectroscopySensor_GetRxInterruptMode
****************************************************************************//**
*
*  Returns RX interrupt mask register This register specifies which bits from 
*  RX interrupt request register will trigger an interrupt event.
*
*  \return 
*   RX interrupt sources to be enabled (refer to 
*   SpectroscopySensor_GetRxInterruptSource() function for bit fields values).
*
*******************************************************************************/
#define SpectroscopySensor_GetRxInterruptMode()   (SpectroscopySensor_INTR_RX_MASK_REG)


/*******************************************************************************
* Function Name: SpectroscopySensor_GetRxInterruptSourceMasked
****************************************************************************//**
*
*  Returns RX interrupt masked request register. This register contains logical
*  AND of corresponding bits from RX interrupt request and mask registers.
*  This function is intended to be used in the interrupt service routine to 
*  identify which of enabled RX interrupt sources cause interrupt event.
*
*  \return 
*   Current status of enabled RX interrupt sources (refer to 
*   SpectroscopySensor_GetRxInterruptSource() function for bit fields values).
*
*******************************************************************************/
#define SpectroscopySensor_GetRxInterruptSourceMasked()   (SpectroscopySensor_INTR_RX_MASKED_REG)


/*******************************************************************************
* Function Name: SpectroscopySensor_ClearRxInterruptSource
****************************************************************************//**
*
*  Clears RX interrupt sources in the interrupt request register.
*
*  \param interruptMask: RX interrupt sources to be cleared (refer to 
*   SpectroscopySensor_GetRxInterruptSource() function for bit fields values).
*
*  \sideeffects 
*   The side effects are listed in the table below for each 
*   affected interrupt source. Refer to section RX FIFO interrupt sources for 
*   detailed description.
*   - SpectroscopySensor_INTR_RX_FIFO_LEVEL Interrupt source is not cleared when 
*     the receiver FIFO has more entries than level.
*   - SpectroscopySensor_INTR_RX_NOT_EMPTY Interrupt source is not cleared when
*     receiver FIFO is not empty.
*   - SpectroscopySensor_INTR_RX_FULL Interrupt source is not cleared when 
*      receiver FIFO is full.
*
*******************************************************************************/
#define SpectroscopySensor_ClearRxInterruptSource(interruptMask)  SpectroscopySensor_CLEAR_INTR_RX(interruptMask)


/*******************************************************************************
* Function Name: SpectroscopySensor_SetRxInterrupt
****************************************************************************//**
*
*  Sets RX interrupt sources in the interrupt request register.
*
*  \param interruptMask: RX interrupt sources to set in the RX interrupt request 
*   register (refer to SpectroscopySensor_GetRxInterruptSource() function for bit 
*   fields values).
*
*******************************************************************************/
#define SpectroscopySensor_SetRxInterrupt(interruptMask)  SpectroscopySensor_SET_INTR_RX(interruptMask)

void SpectroscopySensor_SetRxFifoLevel(uint32 level);


/* APIs to service INTR_TX register */
/*******************************************************************************
* Function Name: SpectroscopySensor_GetTxInterruptSource
****************************************************************************//**
*
*  Returns TX interrupt request register. This register contains current status 
*  of TX interrupt sources.
* 
*  \return 
*   Current status of TX interrupt sources.
*   Each constant is a bit field value. The value returned may have multiple 
*   bits set to indicate the current status.
*   - SpectroscopySensor_INTR_TX_FIFO_LEVEL - The number of data elements in the 
*     TX FIFO is less than the value of TX FIFO level.
*   - SpectroscopySensor_INTR_TX_NOT_FULL - Transmitter FIFO is not full.
*   - SpectroscopySensor_INTR_TX_EMPTY - Transmitter FIFO is empty.
*   - SpectroscopySensor_INTR_TX_OVERFLOW - Attempt to write to a full 
*     transmitter FIFO.
*   - SpectroscopySensor_INTR_TX_UNDERFLOW - Attempt to read from an empty 
*     transmitter FIFO.
*   - SpectroscopySensor_INTR_TX_UART_NACK - UART received a NACK in SmartCard 
*   mode.
*   - SpectroscopySensor_INTR_TX_UART_DONE - UART transfer is complete. 
*     All data elements from the TX FIFO are sent.
*   - SpectroscopySensor_INTR_TX_UART_ARB_LOST - Value on the TX line of the UART
*     does not match the value on the RX line.
*
*******************************************************************************/
#define SpectroscopySensor_GetTxInterruptSource() (SpectroscopySensor_INTR_TX_REG)


/*******************************************************************************
* Function Name: SpectroscopySensor_SetTxInterruptMode
****************************************************************************//**
*
*  Writes TX interrupt mask register. This register configures which bits from 
*  TX interrupt request register will trigger an interrupt event.
*
*  \param interruptMask: TX interrupt sources to be enabled (refer to 
*   SpectroscopySensor_GetTxInterruptSource() function for bit field values).
*
*******************************************************************************/
#define SpectroscopySensor_SetTxInterruptMode(interruptMask)  SpectroscopySensor_WRITE_INTR_TX_MASK(interruptMask)


/*******************************************************************************
* Function Name: SpectroscopySensor_GetTxInterruptMode
****************************************************************************//**
*
*  Returns TX interrupt mask register This register specifies which bits from 
*  TX interrupt request register will trigger an interrupt event.
*
*  \return 
*   Enabled TX interrupt sources (refer to 
*   SpectroscopySensor_GetTxInterruptSource() function for bit field values).
*   
*******************************************************************************/
#define SpectroscopySensor_GetTxInterruptMode()   (SpectroscopySensor_INTR_TX_MASK_REG)


/*******************************************************************************
* Function Name: SpectroscopySensor_GetTxInterruptSourceMasked
****************************************************************************//**
*
*  Returns TX interrupt masked request register. This register contains logical
*  AND of corresponding bits from TX interrupt request and mask registers.
*  This function is intended to be used in the interrupt service routine to identify 
*  which of enabled TX interrupt sources cause interrupt event.
*
*  \return 
*   Current status of enabled TX interrupt sources (refer to 
*   SpectroscopySensor_GetTxInterruptSource() function for bit field values).
*
*******************************************************************************/
#define SpectroscopySensor_GetTxInterruptSourceMasked()   (SpectroscopySensor_INTR_TX_MASKED_REG)


/*******************************************************************************
* Function Name: SpectroscopySensor_ClearTxInterruptSource
****************************************************************************//**
*
*  Clears TX interrupt sources in the interrupt request register.
*
*  \param interruptMask: TX interrupt sources to be cleared (refer to 
*   SpectroscopySensor_GetTxInterruptSource() function for bit field values).
*
*  \sideeffects 
*   The side effects are listed in the table below for each affected interrupt 
*   source. Refer to section TX FIFO interrupt sources for detailed description.
*   - SpectroscopySensor_INTR_TX_FIFO_LEVEL - Interrupt source is not cleared when 
*     transmitter FIFO has less entries than level.
*   - SpectroscopySensor_INTR_TX_NOT_FULL - Interrupt source is not cleared when
*     transmitter FIFO has empty entries.
*   - SpectroscopySensor_INTR_TX_EMPTY - Interrupt source is not cleared when 
*     transmitter FIFO is empty.
*   - SpectroscopySensor_INTR_TX_UNDERFLOW - Interrupt source is not cleared when 
*     transmitter FIFO is empty and I2C mode with clock stretching is selected. 
*     Put data into the transmitter FIFO before clearing it. This behavior only 
*     applicable for PSoC 4100/PSoC 4200 devices.
*
*******************************************************************************/
#define SpectroscopySensor_ClearTxInterruptSource(interruptMask)  SpectroscopySensor_CLEAR_INTR_TX(interruptMask)


/*******************************************************************************
* Function Name: SpectroscopySensor_SetTxInterrupt
****************************************************************************//**
*
*  Sets RX interrupt sources in the interrupt request register.
*
*  \param interruptMask: RX interrupt sources to set in the RX interrupt request 
*   register (refer to SpectroscopySensor_GetRxInterruptSource() function for bit 
*   fields values).
*
*******************************************************************************/
#define SpectroscopySensor_SetTxInterrupt(interruptMask)  SpectroscopySensor_SET_INTR_TX(interruptMask)

void SpectroscopySensor_SetTxFifoLevel(uint32 level);


/* APIs to service INTR_MASTER register */
/*******************************************************************************
* Function Name: SpectroscopySensor_GetMasterInterruptSource
****************************************************************************//**
*
*  Returns Master interrupt request register. This register contains current 
*  status of Master interrupt sources.
*
*  \return 
*   Current status of Master interrupt sources. 
*   Each constant is a bit field value. The value returned may have multiple 
*   bits set to indicate the current status.
*   - SpectroscopySensor_INTR_MASTER_SPI_DONE - SPI master transfer is complete.
*     Refer to Interrupt sources section for detailed description.
*   - SpectroscopySensor_INTR_MASTER_I2C_ARB_LOST - I2C master lost arbitration.
*   - SpectroscopySensor_INTR_MASTER_I2C_NACK - I2C master received negative 
*    acknowledgement (NAK).
*   - SpectroscopySensor_INTR_MASTER_I2C_ACK - I2C master received acknowledgement.
*   - SpectroscopySensor_INTR_MASTER_I2C_STOP - I2C master generated STOP.
*   - SpectroscopySensor_INTR_MASTER_I2C_BUS_ERROR - I2C master bus error 
*     (detection of unexpected START or STOP condition).
*
*******************************************************************************/
#define SpectroscopySensor_GetMasterInterruptSource() (SpectroscopySensor_INTR_MASTER_REG)

/*******************************************************************************
* Function Name: SpectroscopySensor_SetMasterInterruptMode
****************************************************************************//**
*
*  Writes Master interrupt mask register. This register configures which bits 
*  from Master interrupt request register will trigger an interrupt event.
*
*  \param interruptMask: Master interrupt sources to be enabled (refer to 
*   SpectroscopySensor_GetMasterInterruptSource() function for bit field values).
*
*******************************************************************************/
#define SpectroscopySensor_SetMasterInterruptMode(interruptMask)  SpectroscopySensor_WRITE_INTR_MASTER_MASK(interruptMask)

/*******************************************************************************
* Function Name: SpectroscopySensor_GetMasterInterruptMode
****************************************************************************//**
*
*  Returns Master interrupt mask register This register specifies which bits 
*  from Master interrupt request register will trigger an interrupt event.
*
*  \return 
*   Enabled Master interrupt sources (refer to 
*   SpectroscopySensor_GetMasterInterruptSource() function for return values).
*
*******************************************************************************/
#define SpectroscopySensor_GetMasterInterruptMode()   (SpectroscopySensor_INTR_MASTER_MASK_REG)

/*******************************************************************************
* Function Name: SpectroscopySensor_GetMasterInterruptSourceMasked
****************************************************************************//**
*
*  Returns Master interrupt masked request register. This register contains 
*  logical AND of corresponding bits from Master interrupt request and mask 
*  registers.
*  This function is intended to be used in the interrupt service routine to 
*  identify which of enabled Master interrupt sources cause interrupt event.
*
*  \return 
*   Current status of enabled Master interrupt sources (refer to 
*   SpectroscopySensor_GetMasterInterruptSource() function for return values).
*
*******************************************************************************/
#define SpectroscopySensor_GetMasterInterruptSourceMasked()   (SpectroscopySensor_INTR_MASTER_MASKED_REG)

/*******************************************************************************
* Function Name: SpectroscopySensor_ClearMasterInterruptSource
****************************************************************************//**
*
*  Clears Master interrupt sources in the interrupt request register.
*
*  \param interruptMask: Master interrupt sources to be cleared (refer to 
*   SpectroscopySensor_GetMasterInterruptSource() function for bit field values).
*
*******************************************************************************/
#define SpectroscopySensor_ClearMasterInterruptSource(interruptMask)  SpectroscopySensor_CLEAR_INTR_MASTER(interruptMask)

/*******************************************************************************
* Function Name: SpectroscopySensor_SetMasterInterrupt
****************************************************************************//**
*
*  Sets Master interrupt sources in the interrupt request register.
*
*  \param interruptMask: Master interrupt sources to set in the Master interrupt
*   request register (refer to SpectroscopySensor_GetMasterInterruptSource() 
*   function for bit field values).
*
*******************************************************************************/
#define SpectroscopySensor_SetMasterInterrupt(interruptMask)  SpectroscopySensor_SET_INTR_MASTER(interruptMask)


/* APIs to service INTR_SLAVE register */
/*******************************************************************************
* Function Name: SpectroscopySensor_GetSlaveInterruptSource
****************************************************************************//**
*
*  Returns Slave interrupt request register. This register contains current 
*  status of Slave interrupt sources.
*
*  \return 
*   Current status of Slave interrupt sources.
*   Each constant is a bit field value. The value returned may have multiple 
*   bits set to indicate the current status.
*   - SpectroscopySensor_INTR_SLAVE_I2C_ARB_LOST - I2C slave lost arbitration: 
*     the value driven on the SDA line is not the same as the value observed 
*     on the SDA line.
*   - SpectroscopySensor_INTR_SLAVE_I2C_NACK - I2C slave received negative 
*     acknowledgement (NAK).
*   - SpectroscopySensor_INTR_SLAVE_I2C_ACK - I2C slave received 
*     acknowledgement (ACK).
*   - SpectroscopySensor_INTR_SLAVE_I2C_WRITE_STOP - Stop or Repeated Start 
*     event for write transfer intended for this slave (address matching 
*     is performed).
*   - SpectroscopySensor_INTR_SLAVE_I2C_STOP - Stop or Repeated Start event 
*     for (read or write) transfer intended for this slave (address matching 
*     is performed).
*   - SpectroscopySensor_INTR_SLAVE_I2C_START - I2C slave received Start 
*     condition.
*   - SpectroscopySensor_INTR_SLAVE_I2C_ADDR_MATCH - I2C slave received matching 
*     address.
*   - SpectroscopySensor_INTR_SLAVE_I2C_GENERAL - I2C Slave received general 
*     call address.
*   - SpectroscopySensor_INTR_SLAVE_I2C_BUS_ERROR - I2C slave bus error (detection 
*      of unexpected Start or Stop condition).
*   - SpectroscopySensor_INTR_SLAVE_SPI_BUS_ERROR - SPI slave select line is 
*      deselected at an expected time while the SPI transfer.
*
*******************************************************************************/
#define SpectroscopySensor_GetSlaveInterruptSource()  (SpectroscopySensor_INTR_SLAVE_REG)

/*******************************************************************************
* Function Name: SpectroscopySensor_SetSlaveInterruptMode
****************************************************************************//**
*
*  Writes Slave interrupt mask register. 
*  This register configures which bits from Slave interrupt request register 
*  will trigger an interrupt event.
*
*  \param interruptMask: Slave interrupt sources to be enabled (refer to 
*   SpectroscopySensor_GetSlaveInterruptSource() function for bit field values).
*
*******************************************************************************/
#define SpectroscopySensor_SetSlaveInterruptMode(interruptMask)   SpectroscopySensor_WRITE_INTR_SLAVE_MASK(interruptMask)

/*******************************************************************************
* Function Name: SpectroscopySensor_GetSlaveInterruptMode
****************************************************************************//**
*
*  Returns Slave interrupt mask register.
*  This register specifies which bits from Slave interrupt request register 
*  will trigger an interrupt event.
*
*  \return 
*   Enabled Slave interrupt sources(refer to 
*   SpectroscopySensor_GetSlaveInterruptSource() function for bit field values).
*
*******************************************************************************/
#define SpectroscopySensor_GetSlaveInterruptMode()    (SpectroscopySensor_INTR_SLAVE_MASK_REG)

/*******************************************************************************
* Function Name: SpectroscopySensor_GetSlaveInterruptSourceMasked
****************************************************************************//**
*
*  Returns Slave interrupt masked request register. This register contains 
*  logical AND of corresponding bits from Slave interrupt request and mask 
*  registers.
*  This function is intended to be used in the interrupt service routine to 
*  identify which of enabled Slave interrupt sources cause interrupt event.
*
*  \return 
*   Current status of enabled Slave interrupt sources (refer to 
*   SpectroscopySensor_GetSlaveInterruptSource() function for return values).
*
*******************************************************************************/
#define SpectroscopySensor_GetSlaveInterruptSourceMasked()    (SpectroscopySensor_INTR_SLAVE_MASKED_REG)

/*******************************************************************************
* Function Name: SpectroscopySensor_ClearSlaveInterruptSource
****************************************************************************//**
*
*  Clears Slave interrupt sources in the interrupt request register.
*
*  \param interruptMask: Slave interrupt sources to be cleared (refer to 
*   SpectroscopySensor_GetSlaveInterruptSource() function for return values).
*
*******************************************************************************/
#define SpectroscopySensor_ClearSlaveInterruptSource(interruptMask)   SpectroscopySensor_CLEAR_INTR_SLAVE(interruptMask)

/*******************************************************************************
* Function Name: SpectroscopySensor_SetSlaveInterrupt
****************************************************************************//**
*
*  Sets Slave interrupt sources in the interrupt request register.
*
*  \param interruptMask: Slave interrupt sources to set in the Slave interrupt 
*   request register (refer to SpectroscopySensor_GetSlaveInterruptSource() 
*   function for return values).
*
*******************************************************************************/
#define SpectroscopySensor_SetSlaveInterrupt(interruptMask)   SpectroscopySensor_SET_INTR_SLAVE(interruptMask)

/** @} interrupt */ 


/***************************************
*     Vars with External Linkage
***************************************/

/**
* \addtogroup group_globals
* @{
*/

/** SpectroscopySensor_initVar indicates whether the SpectroscopySensor 
*  component has been initialized. The variable is initialized to 0 
*  and set to 1 the first time SCB_Start() is called. This allows 
*  the component to restart without reinitialization after the first 
*  call to the SpectroscopySensor_Start() routine.
*
*  If re-initialization of the component is required, then the 
*  SpectroscopySensor_Init() function can be called before the 
*  SpectroscopySensor_Start() or SpectroscopySensor_Enable() function.
*/
extern uint8 SpectroscopySensor_initVar;
/** @} globals */

/***************************************
*              Registers
***************************************/

#define SpectroscopySensor_CTRL_REG               (*(reg32 *) SpectroscopySensor_SCB__CTRL)
#define SpectroscopySensor_CTRL_PTR               ( (reg32 *) SpectroscopySensor_SCB__CTRL)

#define SpectroscopySensor_STATUS_REG             (*(reg32 *) SpectroscopySensor_SCB__STATUS)
#define SpectroscopySensor_STATUS_PTR             ( (reg32 *) SpectroscopySensor_SCB__STATUS)

#if (!SpectroscopySensor_CY_SCBIP_V1)
    #define SpectroscopySensor_SPI_CTRL_REG           (*(reg32 *) SpectroscopySensor_SCB__SPI_CTRL)
    #define SpectroscopySensor_SPI_CTRL_PTR           ( (reg32 *) SpectroscopySensor_SCB__SPI_CTRL)

    #define SpectroscopySensor_SPI_STATUS_REG         (*(reg32 *) SpectroscopySensor_SCB__SPI_STATUS)
    #define SpectroscopySensor_SPI_STATUS_PTR         ( (reg32 *) SpectroscopySensor_SCB__SPI_STATUS)

    #define SpectroscopySensor_UART_CTRL_REG          (*(reg32 *) SpectroscopySensor_SCB__UART_CTRL)
    #define SpectroscopySensor_UART_CTRL_PTR          ( (reg32 *) SpectroscopySensor_SCB__UART_CTRL)

    #define SpectroscopySensor_UART_TX_CTRL_REG       (*(reg32 *) SpectroscopySensor_SCB__UART_TX_CTRL)
    #define SpectroscopySensor_UART_TX_CTRL_PTR       ( (reg32 *) SpectroscopySensor_SCB__UART_TX_CTRL)

    #define SpectroscopySensor_UART_RX_CTRL_REG       (*(reg32 *) SpectroscopySensor_SCB__UART_RX_CTRL)
    #define SpectroscopySensor_UART_RX_CTRL_PTR       ( (reg32 *) SpectroscopySensor_SCB__UART_RX_CTRL)

    #define SpectroscopySensor_UART_RX_STATUS_REG     (*(reg32 *) SpectroscopySensor_SCB__UART_RX_STATUS)
    #define SpectroscopySensor_UART_RX_STATUS_PTR     ( (reg32 *) SpectroscopySensor_SCB__UART_RX_STATUS)
#endif /* (!SpectroscopySensor_CY_SCBIP_V1) */

#if !(SpectroscopySensor_CY_SCBIP_V0 || SpectroscopySensor_CY_SCBIP_V1)
    #define SpectroscopySensor_UART_FLOW_CTRL_REG     (*(reg32 *) SpectroscopySensor_SCB__UART_FLOW_CTRL)
    #define SpectroscopySensor_UART_FLOW_CTRL_PTR     ( (reg32 *) SpectroscopySensor_SCB__UART_FLOW_CTRL)
#endif /* !(SpectroscopySensor_CY_SCBIP_V0 || SpectroscopySensor_CY_SCBIP_V1) */

#define SpectroscopySensor_I2C_CTRL_REG           (*(reg32 *) SpectroscopySensor_SCB__I2C_CTRL)
#define SpectroscopySensor_I2C_CTRL_PTR           ( (reg32 *) SpectroscopySensor_SCB__I2C_CTRL)

#define SpectroscopySensor_I2C_STATUS_REG         (*(reg32 *) SpectroscopySensor_SCB__I2C_STATUS)
#define SpectroscopySensor_I2C_STATUS_PTR         ( (reg32 *) SpectroscopySensor_SCB__I2C_STATUS)

#define SpectroscopySensor_I2C_MASTER_CMD_REG     (*(reg32 *) SpectroscopySensor_SCB__I2C_M_CMD)
#define SpectroscopySensor_I2C_MASTER_CMD_PTR     ( (reg32 *) SpectroscopySensor_SCB__I2C_M_CMD)

#define SpectroscopySensor_I2C_SLAVE_CMD_REG      (*(reg32 *) SpectroscopySensor_SCB__I2C_S_CMD)
#define SpectroscopySensor_I2C_SLAVE_CMD_PTR      ( (reg32 *) SpectroscopySensor_SCB__I2C_S_CMD)

#define SpectroscopySensor_I2C_CFG_REG            (*(reg32 *) SpectroscopySensor_SCB__I2C_CFG)
#define SpectroscopySensor_I2C_CFG_PTR            ( (reg32 *) SpectroscopySensor_SCB__I2C_CFG)

#define SpectroscopySensor_TX_CTRL_REG            (*(reg32 *) SpectroscopySensor_SCB__TX_CTRL)
#define SpectroscopySensor_TX_CTRL_PTR            ( (reg32 *) SpectroscopySensor_SCB__TX_CTRL)

#define SpectroscopySensor_TX_FIFO_CTRL_REG       (*(reg32 *) SpectroscopySensor_SCB__TX_FIFO_CTRL)
#define SpectroscopySensor_TX_FIFO_CTRL_PTR       ( (reg32 *) SpectroscopySensor_SCB__TX_FIFO_CTRL)

#define SpectroscopySensor_TX_FIFO_STATUS_REG     (*(reg32 *) SpectroscopySensor_SCB__TX_FIFO_STATUS)
#define SpectroscopySensor_TX_FIFO_STATUS_PTR     ( (reg32 *) SpectroscopySensor_SCB__TX_FIFO_STATUS)

#define SpectroscopySensor_TX_FIFO_WR_REG         (*(reg32 *) SpectroscopySensor_SCB__TX_FIFO_WR)
#define SpectroscopySensor_TX_FIFO_WR_PTR         ( (reg32 *) SpectroscopySensor_SCB__TX_FIFO_WR)

#define SpectroscopySensor_RX_CTRL_REG            (*(reg32 *) SpectroscopySensor_SCB__RX_CTRL)
#define SpectroscopySensor_RX_CTRL_PTR            ( (reg32 *) SpectroscopySensor_SCB__RX_CTRL)

#define SpectroscopySensor_RX_FIFO_CTRL_REG       (*(reg32 *) SpectroscopySensor_SCB__RX_FIFO_CTRL)
#define SpectroscopySensor_RX_FIFO_CTRL_PTR       ( (reg32 *) SpectroscopySensor_SCB__RX_FIFO_CTRL)

#define SpectroscopySensor_RX_FIFO_STATUS_REG     (*(reg32 *) SpectroscopySensor_SCB__RX_FIFO_STATUS)
#define SpectroscopySensor_RX_FIFO_STATUS_PTR     ( (reg32 *) SpectroscopySensor_SCB__RX_FIFO_STATUS)

#define SpectroscopySensor_RX_MATCH_REG           (*(reg32 *) SpectroscopySensor_SCB__RX_MATCH)
#define SpectroscopySensor_RX_MATCH_PTR           ( (reg32 *) SpectroscopySensor_SCB__RX_MATCH)

#define SpectroscopySensor_RX_FIFO_RD_REG         (*(reg32 *) SpectroscopySensor_SCB__RX_FIFO_RD)
#define SpectroscopySensor_RX_FIFO_RD_PTR         ( (reg32 *) SpectroscopySensor_SCB__RX_FIFO_RD)

#define SpectroscopySensor_RX_FIFO_RD_SILENT_REG  (*(reg32 *) SpectroscopySensor_SCB__RX_FIFO_RD_SILENT)
#define SpectroscopySensor_RX_FIFO_RD_SILENT_PTR  ( (reg32 *) SpectroscopySensor_SCB__RX_FIFO_RD_SILENT)

#ifdef SpectroscopySensor_SCB__EZ_DATA0
    #define SpectroscopySensor_EZBUF_DATA0_REG    (*(reg32 *) SpectroscopySensor_SCB__EZ_DATA0)
    #define SpectroscopySensor_EZBUF_DATA0_PTR    ( (reg32 *) SpectroscopySensor_SCB__EZ_DATA0)
#else
    #define SpectroscopySensor_EZBUF_DATA0_REG    (*(reg32 *) SpectroscopySensor_SCB__EZ_DATA00)
    #define SpectroscopySensor_EZBUF_DATA0_PTR    ( (reg32 *) SpectroscopySensor_SCB__EZ_DATA00)
#endif /* SpectroscopySensor_SCB__EZ_DATA00 */

#define SpectroscopySensor_INTR_CAUSE_REG         (*(reg32 *) SpectroscopySensor_SCB__INTR_CAUSE)
#define SpectroscopySensor_INTR_CAUSE_PTR         ( (reg32 *) SpectroscopySensor_SCB__INTR_CAUSE)

#define SpectroscopySensor_INTR_I2C_EC_REG        (*(reg32 *) SpectroscopySensor_SCB__INTR_I2C_EC)
#define SpectroscopySensor_INTR_I2C_EC_PTR        ( (reg32 *) SpectroscopySensor_SCB__INTR_I2C_EC)

#define SpectroscopySensor_INTR_I2C_EC_MASK_REG   (*(reg32 *) SpectroscopySensor_SCB__INTR_I2C_EC_MASK)
#define SpectroscopySensor_INTR_I2C_EC_MASK_PTR   ( (reg32 *) SpectroscopySensor_SCB__INTR_I2C_EC_MASK)

#define SpectroscopySensor_INTR_I2C_EC_MASKED_REG (*(reg32 *) SpectroscopySensor_SCB__INTR_I2C_EC_MASKED)
#define SpectroscopySensor_INTR_I2C_EC_MASKED_PTR ( (reg32 *) SpectroscopySensor_SCB__INTR_I2C_EC_MASKED)

#if (!SpectroscopySensor_CY_SCBIP_V1)
    #define SpectroscopySensor_INTR_SPI_EC_REG        (*(reg32 *) SpectroscopySensor_SCB__INTR_SPI_EC)
    #define SpectroscopySensor_INTR_SPI_EC_PTR        ( (reg32 *) SpectroscopySensor_SCB__INTR_SPI_EC)

    #define SpectroscopySensor_INTR_SPI_EC_MASK_REG   (*(reg32 *) SpectroscopySensor_SCB__INTR_SPI_EC_MASK)
    #define SpectroscopySensor_INTR_SPI_EC_MASK_PTR   ( (reg32 *) SpectroscopySensor_SCB__INTR_SPI_EC_MASK)

    #define SpectroscopySensor_INTR_SPI_EC_MASKED_REG (*(reg32 *) SpectroscopySensor_SCB__INTR_SPI_EC_MASKED)
    #define SpectroscopySensor_INTR_SPI_EC_MASKED_PTR ( (reg32 *) SpectroscopySensor_SCB__INTR_SPI_EC_MASKED)
#endif /* (!SpectroscopySensor_CY_SCBIP_V1) */

#define SpectroscopySensor_INTR_MASTER_REG        (*(reg32 *) SpectroscopySensor_SCB__INTR_M)
#define SpectroscopySensor_INTR_MASTER_PTR        ( (reg32 *) SpectroscopySensor_SCB__INTR_M)

#define SpectroscopySensor_INTR_MASTER_SET_REG    (*(reg32 *) SpectroscopySensor_SCB__INTR_M_SET)
#define SpectroscopySensor_INTR_MASTER_SET_PTR    ( (reg32 *) SpectroscopySensor_SCB__INTR_M_SET)

#define SpectroscopySensor_INTR_MASTER_MASK_REG   (*(reg32 *) SpectroscopySensor_SCB__INTR_M_MASK)
#define SpectroscopySensor_INTR_MASTER_MASK_PTR   ( (reg32 *) SpectroscopySensor_SCB__INTR_M_MASK)

#define SpectroscopySensor_INTR_MASTER_MASKED_REG (*(reg32 *) SpectroscopySensor_SCB__INTR_M_MASKED)
#define SpectroscopySensor_INTR_MASTER_MASKED_PTR ( (reg32 *) SpectroscopySensor_SCB__INTR_M_MASKED)

#define SpectroscopySensor_INTR_SLAVE_REG         (*(reg32 *) SpectroscopySensor_SCB__INTR_S)
#define SpectroscopySensor_INTR_SLAVE_PTR         ( (reg32 *) SpectroscopySensor_SCB__INTR_S)

#define SpectroscopySensor_INTR_SLAVE_SET_REG     (*(reg32 *) SpectroscopySensor_SCB__INTR_S_SET)
#define SpectroscopySensor_INTR_SLAVE_SET_PTR     ( (reg32 *) SpectroscopySensor_SCB__INTR_S_SET)

#define SpectroscopySensor_INTR_SLAVE_MASK_REG    (*(reg32 *) SpectroscopySensor_SCB__INTR_S_MASK)
#define SpectroscopySensor_INTR_SLAVE_MASK_PTR    ( (reg32 *) SpectroscopySensor_SCB__INTR_S_MASK)

#define SpectroscopySensor_INTR_SLAVE_MASKED_REG  (*(reg32 *) SpectroscopySensor_SCB__INTR_S_MASKED)
#define SpectroscopySensor_INTR_SLAVE_MASKED_PTR  ( (reg32 *) SpectroscopySensor_SCB__INTR_S_MASKED)

#define SpectroscopySensor_INTR_TX_REG            (*(reg32 *) SpectroscopySensor_SCB__INTR_TX)
#define SpectroscopySensor_INTR_TX_PTR            ( (reg32 *) SpectroscopySensor_SCB__INTR_TX)

#define SpectroscopySensor_INTR_TX_SET_REG        (*(reg32 *) SpectroscopySensor_SCB__INTR_TX_SET)
#define SpectroscopySensor_INTR_TX_SET_PTR        ( (reg32 *) SpectroscopySensor_SCB__INTR_TX_SET)

#define SpectroscopySensor_INTR_TX_MASK_REG       (*(reg32 *) SpectroscopySensor_SCB__INTR_TX_MASK)
#define SpectroscopySensor_INTR_TX_MASK_PTR       ( (reg32 *) SpectroscopySensor_SCB__INTR_TX_MASK)

#define SpectroscopySensor_INTR_TX_MASKED_REG     (*(reg32 *) SpectroscopySensor_SCB__INTR_TX_MASKED)
#define SpectroscopySensor_INTR_TX_MASKED_PTR     ( (reg32 *) SpectroscopySensor_SCB__INTR_TX_MASKED)

#define SpectroscopySensor_INTR_RX_REG            (*(reg32 *) SpectroscopySensor_SCB__INTR_RX)
#define SpectroscopySensor_INTR_RX_PTR            ( (reg32 *) SpectroscopySensor_SCB__INTR_RX)

#define SpectroscopySensor_INTR_RX_SET_REG        (*(reg32 *) SpectroscopySensor_SCB__INTR_RX_SET)
#define SpectroscopySensor_INTR_RX_SET_PTR        ( (reg32 *) SpectroscopySensor_SCB__INTR_RX_SET)

#define SpectroscopySensor_INTR_RX_MASK_REG       (*(reg32 *) SpectroscopySensor_SCB__INTR_RX_MASK)
#define SpectroscopySensor_INTR_RX_MASK_PTR       ( (reg32 *) SpectroscopySensor_SCB__INTR_RX_MASK)

#define SpectroscopySensor_INTR_RX_MASKED_REG     (*(reg32 *) SpectroscopySensor_SCB__INTR_RX_MASKED)
#define SpectroscopySensor_INTR_RX_MASKED_PTR     ( (reg32 *) SpectroscopySensor_SCB__INTR_RX_MASKED)

/* Defines get from SCB IP parameters. */
#define SpectroscopySensor_FIFO_SIZE      (8u)  /* TX or RX FIFO size. */
#define SpectroscopySensor_EZ_DATA_NR     (32u)  /* Number of words in EZ memory. */ 
#define SpectroscopySensor_ONE_BYTE_WIDTH (8u)            /* Number of bits in one byte. */
#define SpectroscopySensor_FF_DATA_NR_LOG2_MASK       (0x0Fu)      /* Number of bits to represent a FIFO address. */
#define SpectroscopySensor_FF_DATA_NR_LOG2_PLUS1_MASK (0x1Fu) /* Number of bits to represent #bytes in FIFO. */


/***************************************
*        Registers Constants
***************************************/

#if (SpectroscopySensor_SCB_IRQ_INTERNAL)
    #define SpectroscopySensor_ISR_NUMBER     ((uint8) SpectroscopySensor_SCB_IRQ__INTC_NUMBER)
    #define SpectroscopySensor_ISR_PRIORITY   ((uint8) SpectroscopySensor_SCB_IRQ__INTC_PRIOR_NUM)
#endif /* (SpectroscopySensor_SCB_IRQ_INTERNAL) */

#if (SpectroscopySensor_UART_RX_WAKEUP_IRQ)
    #define SpectroscopySensor_RX_WAKE_ISR_NUMBER     ((uint8) SpectroscopySensor_RX_WAKEUP_IRQ__INTC_NUMBER)
    #define SpectroscopySensor_RX_WAKE_ISR_PRIORITY   ((uint8) SpectroscopySensor_RX_WAKEUP_IRQ__INTC_PRIOR_NUM)
#endif /* (SpectroscopySensor_UART_RX_WAKEUP_IRQ) */

/* SpectroscopySensor_CTRL_REG */
#define SpectroscopySensor_CTRL_OVS_POS           (0u)  /* [3:0]   Oversampling factor                 */
#define SpectroscopySensor_CTRL_EC_AM_MODE_POS    (8u)  /* [8]     Externally clocked address match    */
#define SpectroscopySensor_CTRL_EC_OP_MODE_POS    (9u)  /* [9]     Externally clocked operation mode   */
#define SpectroscopySensor_CTRL_EZBUF_MODE_POS    (10u) /* [10]    EZ buffer is enabled                */
#if !(SpectroscopySensor_CY_SCBIP_V0 || SpectroscopySensor_CY_SCBIP_V1)
    #define SpectroscopySensor_CTRL_BYTE_MODE_POS (11u) /* [11]    Determines the number of bits per FIFO data element */
#endif /* !(SpectroscopySensor_CY_SCBIP_V0 || SpectroscopySensor_CY_SCBIP_V1) */
#define SpectroscopySensor_CTRL_ADDR_ACCEPT_POS   (16u) /* [16]    Put matched address in RX FIFO       */
#define SpectroscopySensor_CTRL_BLOCK_POS         (17u) /* [17]    Ext and Int logic to resolve collide */
#define SpectroscopySensor_CTRL_MODE_POS          (24u) /* [25:24] Operation mode                       */
#define SpectroscopySensor_CTRL_ENABLED_POS       (31u) /* [31]    Enable SCB block                     */
#define SpectroscopySensor_CTRL_OVS_MASK          ((uint32) 0x0Fu)
#define SpectroscopySensor_CTRL_EC_AM_MODE        ((uint32) 0x01u << SpectroscopySensor_CTRL_EC_AM_MODE_POS)
#define SpectroscopySensor_CTRL_EC_OP_MODE        ((uint32) 0x01u << SpectroscopySensor_CTRL_EC_OP_MODE_POS)
#define SpectroscopySensor_CTRL_EZBUF_MODE        ((uint32) 0x01u << SpectroscopySensor_CTRL_EZBUF_MODE_POS)
#if !(SpectroscopySensor_CY_SCBIP_V0 || SpectroscopySensor_CY_SCBIP_V1)
    #define SpectroscopySensor_CTRL_BYTE_MODE ((uint32) 0x01u << SpectroscopySensor_CTRL_BYTE_MODE_POS)
#endif /* !(SpectroscopySensor_CY_SCBIP_V0 || SpectroscopySensor_CY_SCBIP_V1) */
#define SpectroscopySensor_CTRL_ADDR_ACCEPT       ((uint32) 0x01u << SpectroscopySensor_CTRL_ADDR_ACCEPT_POS)
#define SpectroscopySensor_CTRL_BLOCK             ((uint32) 0x01u << SpectroscopySensor_CTRL_BLOCK_POS)
#define SpectroscopySensor_CTRL_MODE_MASK         ((uint32) 0x03u << SpectroscopySensor_CTRL_MODE_POS)
#define SpectroscopySensor_CTRL_MODE_I2C          ((uint32) 0x00u)
#define SpectroscopySensor_CTRL_MODE_SPI          ((uint32) 0x01u << SpectroscopySensor_CTRL_MODE_POS)
#define SpectroscopySensor_CTRL_MODE_UART         ((uint32) 0x02u << SpectroscopySensor_CTRL_MODE_POS)
#define SpectroscopySensor_CTRL_ENABLED           ((uint32) 0x01u << SpectroscopySensor_CTRL_ENABLED_POS)

/* SpectroscopySensor_STATUS_REG */
#define SpectroscopySensor_STATUS_EC_BUSY_POS     (0u)  /* [0] Bus busy. Externally clocked logic access to EZ memory */
#define SpectroscopySensor_STATUS_EC_BUSY         ((uint32) 0x0Fu)

/* SpectroscopySensor_SPI_CTRL_REG  */
#define SpectroscopySensor_SPI_CTRL_CONTINUOUS_POS        (0u)  /* [0]     Continuous or Separated SPI data transfers */
#define SpectroscopySensor_SPI_CTRL_SELECT_PRECEDE_POS    (1u)  /* [1]     Precedes or coincides start of data frame  */
#define SpectroscopySensor_SPI_CTRL_CPHA_POS              (2u)  /* [2]     SCLK phase                                 */
#define SpectroscopySensor_SPI_CTRL_CPOL_POS              (3u)  /* [3]     SCLK polarity                              */
#define SpectroscopySensor_SPI_CTRL_LATE_MISO_SAMPLE_POS  (4u)  /* [4]     Late MISO sample enabled                   */
#if !(SpectroscopySensor_CY_SCBIP_V0 || SpectroscopySensor_CY_SCBIP_V1)
    #define SpectroscopySensor_SPI_CTRL_SCLK_CONTINUOUS_POS   (5u)  /* [5]     Enable continuous SCLK generation */
    #define SpectroscopySensor_SPI_CTRL_SSEL0_POLARITY_POS    (8u)  /* [8]     SS0 polarity                      */
    #define SpectroscopySensor_SPI_CTRL_SSEL1_POLARITY_POS    (9u)  /* [9]     SS1 polarity                      */
    #define SpectroscopySensor_SPI_CTRL_SSEL2_POLARITY_POS    (10u) /* [10]    SS2 polarity                      */
    #define SpectroscopySensor_SPI_CTRL_SSEL3_POLARITY_POS    (11u) /* [11]    SS3 polarity                      */
#endif /* !(SpectroscopySensor_CY_SCBIP_V0 || SpectroscopySensor_CY_SCBIP_V1) */
#define SpectroscopySensor_SPI_CTRL_LOOPBACK_POS          (16u) /* [16]    Local loop-back control enabled            */
#define SpectroscopySensor_SPI_CTRL_MODE_POS              (24u) /* [25:24] Submode of SPI operation                   */
#define SpectroscopySensor_SPI_CTRL_SLAVE_SELECT_POS      (26u) /* [27:26] Selects SPI SS signal                      */
#define SpectroscopySensor_SPI_CTRL_MASTER_MODE_POS       (31u) /* [31]    Master mode enabled                        */
#define SpectroscopySensor_SPI_CTRL_CONTINUOUS            ((uint32) 0x01u)
#define SpectroscopySensor_SPI_CTRL_SELECT_PRECEDE        ((uint32) 0x01u << SpectroscopySensor_SPI_CTRL_SELECT_PRECEDE_POS)
#define SpectroscopySensor_SPI_CTRL_SCLK_MODE_MASK        ((uint32) 0x03u << SpectroscopySensor_SPI_CTRL_CPHA_POS)
#define SpectroscopySensor_SPI_CTRL_CPHA                  ((uint32) 0x01u << SpectroscopySensor_SPI_CTRL_CPHA_POS)
#define SpectroscopySensor_SPI_CTRL_CPOL                  ((uint32) 0x01u << SpectroscopySensor_SPI_CTRL_CPOL_POS)
#define SpectroscopySensor_SPI_CTRL_LATE_MISO_SAMPLE      ((uint32) 0x01u << \
                                                                    SpectroscopySensor_SPI_CTRL_LATE_MISO_SAMPLE_POS)
#if !(SpectroscopySensor_CY_SCBIP_V0 || SpectroscopySensor_CY_SCBIP_V1)
    #define SpectroscopySensor_SPI_CTRL_SCLK_CONTINUOUS  ((uint32) 0x01u << SpectroscopySensor_SPI_CTRL_SCLK_CONTINUOUS_POS)
    #define SpectroscopySensor_SPI_CTRL_SSEL0_POLARITY   ((uint32) 0x01u << SpectroscopySensor_SPI_CTRL_SSEL0_POLARITY_POS)
    #define SpectroscopySensor_SPI_CTRL_SSEL1_POLARITY   ((uint32) 0x01u << SpectroscopySensor_SPI_CTRL_SSEL1_POLARITY_POS)
    #define SpectroscopySensor_SPI_CTRL_SSEL2_POLARITY   ((uint32) 0x01u << SpectroscopySensor_SPI_CTRL_SSEL2_POLARITY_POS)
    #define SpectroscopySensor_SPI_CTRL_SSEL3_POLARITY   ((uint32) 0x01u << SpectroscopySensor_SPI_CTRL_SSEL3_POLARITY_POS)
    #define SpectroscopySensor_SPI_CTRL_SSEL_POLARITY_MASK ((uint32)0x0Fu << SpectroscopySensor_SPI_CTRL_SSEL0_POLARITY_POS)
#endif /* !(SpectroscopySensor_CY_SCBIP_V0 || SpectroscopySensor_CY_SCBIP_V1) */

#define SpectroscopySensor_SPI_CTRL_LOOPBACK              ((uint32) 0x01u << SpectroscopySensor_SPI_CTRL_LOOPBACK_POS)
#define SpectroscopySensor_SPI_CTRL_MODE_MASK             ((uint32) 0x03u << SpectroscopySensor_SPI_CTRL_MODE_POS)
#define SpectroscopySensor_SPI_CTRL_MODE_MOTOROLA         ((uint32) 0x00u)
#define SpectroscopySensor_SPI_CTRL_MODE_TI               ((uint32) 0x01u << SpectroscopySensor_CTRL_MODE_POS)
#define SpectroscopySensor_SPI_CTRL_MODE_NS               ((uint32) 0x02u << SpectroscopySensor_CTRL_MODE_POS)
#define SpectroscopySensor_SPI_CTRL_SLAVE_SELECT_MASK     ((uint32) 0x03u << SpectroscopySensor_SPI_CTRL_SLAVE_SELECT_POS)
#define SpectroscopySensor_SPI_CTRL_SLAVE_SELECT0         ((uint32) 0x00u)
#define SpectroscopySensor_SPI_CTRL_SLAVE_SELECT1         ((uint32) 0x01u << SpectroscopySensor_SPI_CTRL_SLAVE_SELECT_POS)
#define SpectroscopySensor_SPI_CTRL_SLAVE_SELECT2         ((uint32) 0x02u << SpectroscopySensor_SPI_CTRL_SLAVE_SELECT_POS)
#define SpectroscopySensor_SPI_CTRL_SLAVE_SELECT3         ((uint32) 0x03u << SpectroscopySensor_SPI_CTRL_SLAVE_SELECT_POS)
#define SpectroscopySensor_SPI_CTRL_MASTER                ((uint32) 0x01u << SpectroscopySensor_SPI_CTRL_MASTER_MODE_POS)
#define SpectroscopySensor_SPI_CTRL_SLAVE                 ((uint32) 0x00u)

/* SpectroscopySensor_SPI_STATUS_REG  */
#define SpectroscopySensor_SPI_STATUS_BUS_BUSY_POS    (0u)  /* [0]    Bus busy - slave selected */
#define SpectroscopySensor_SPI_STATUS_EZBUF_ADDR_POS  (8u)  /* [15:8] EzAddress                 */
#define SpectroscopySensor_SPI_STATUS_BUS_BUSY        ((uint32) 0x01u)
#define SpectroscopySensor_SPI_STATUS_EZBUF_ADDR_MASK ((uint32) 0xFFu << SpectroscopySensor_I2C_STATUS_EZBUF_ADDR_POS)

/* SpectroscopySensor_UART_CTRL */
#define SpectroscopySensor_UART_CTRL_LOOPBACK_POS         (16u) /* [16] Loop-back    */
#define SpectroscopySensor_UART_CTRL_MODE_POS             (24u) /* [24] UART subMode */
#define SpectroscopySensor_UART_CTRL_LOOPBACK             ((uint32) 0x01u << SpectroscopySensor_UART_CTRL_LOOPBACK_POS)
#define SpectroscopySensor_UART_CTRL_MODE_UART_STD        ((uint32) 0x00u)
#define SpectroscopySensor_UART_CTRL_MODE_UART_SMARTCARD  ((uint32) 0x01u << SpectroscopySensor_UART_CTRL_MODE_POS)
#define SpectroscopySensor_UART_CTRL_MODE_UART_IRDA       ((uint32) 0x02u << SpectroscopySensor_UART_CTRL_MODE_POS)
#define SpectroscopySensor_UART_CTRL_MODE_MASK            ((uint32) 0x03u << SpectroscopySensor_UART_CTRL_MODE_POS)

/* SpectroscopySensor_UART_TX_CTRL */
#define SpectroscopySensor_UART_TX_CTRL_STOP_BITS_POS         (0u)  /* [2:0] Stop bits: (Stop bits + 1) * 0.5 period */
#define SpectroscopySensor_UART_TX_CTRL_PARITY_POS            (4u)  /* [4]   Parity bit                              */
#define SpectroscopySensor_UART_TX_CTRL_PARITY_ENABLED_POS    (5u)  /* [5]   Parity enable                           */
#define SpectroscopySensor_UART_TX_CTRL_RETRY_ON_NACK_POS     (8u)  /* [8]   Smart Card: re-send frame on NACK       */
#define SpectroscopySensor_UART_TX_CTRL_ONE_STOP_BIT          ((uint32) 0x01u)
#define SpectroscopySensor_UART_TX_CTRL_ONE_HALF_STOP_BITS    ((uint32) 0x02u)
#define SpectroscopySensor_UART_TX_CTRL_TWO_STOP_BITS         ((uint32) 0x03u)
#define SpectroscopySensor_UART_TX_CTRL_STOP_BITS_MASK        ((uint32) 0x07u)
#define SpectroscopySensor_UART_TX_CTRL_PARITY                ((uint32) 0x01u << \
                                                                    SpectroscopySensor_UART_TX_CTRL_PARITY_POS)
#define SpectroscopySensor_UART_TX_CTRL_PARITY_ENABLED        ((uint32) 0x01u << \
                                                                    SpectroscopySensor_UART_TX_CTRL_PARITY_ENABLED_POS)
#define SpectroscopySensor_UART_TX_CTRL_RETRY_ON_NACK         ((uint32) 0x01u << \
                                                                    SpectroscopySensor_UART_TX_CTRL_RETRY_ON_NACK_POS)

/* SpectroscopySensor_UART_RX_CTRL */
#define SpectroscopySensor_UART_RX_CTRL_STOP_BITS_POS             (0u)  /* [2:0] Stop bits: (Stop bits + 1) * 0.5 period*/
#define SpectroscopySensor_UART_RX_CTRL_PARITY_POS                (4u)  /* [4]   Parity bit                             */
#define SpectroscopySensor_UART_RX_CTRL_PARITY_ENABLED_POS        (5u)  /* [5]   Parity enable                          */
#define SpectroscopySensor_UART_RX_CTRL_POLARITY_POS              (6u)  /* [6]   IrDA: inverts polarity of RX signal    */
#define SpectroscopySensor_UART_RX_CTRL_DROP_ON_PARITY_ERR_POS    (8u)  /* [8]   Drop and lost RX FIFO on parity error  */
#define SpectroscopySensor_UART_RX_CTRL_DROP_ON_FRAME_ERR_POS     (9u)  /* [9]   Drop and lost RX FIFO on frame error   */
#define SpectroscopySensor_UART_RX_CTRL_MP_MODE_POS               (10u) /* [10]  Multi-processor mode                   */
#define SpectroscopySensor_UART_RX_CTRL_LIN_MODE_POS              (12u) /* [12]  Lin mode: applicable for UART Standard */
#define SpectroscopySensor_UART_RX_CTRL_SKIP_START_POS            (13u) /* [13]  Skip start not: only for UART Standard */
#define SpectroscopySensor_UART_RX_CTRL_BREAK_WIDTH_POS           (16u) /* [19:16]  Break width: (Break width + 1)      */
#define SpectroscopySensor_UART_TX_CTRL_ONE_STOP_BIT              ((uint32) 0x01u)
#define SpectroscopySensor_UART_TX_CTRL_ONE_HALF_STOP_BITS        ((uint32) 0x02u)
#define SpectroscopySensor_UART_TX_CTRL_TWO_STOP_BITS             ((uint32) 0x03u)
#define SpectroscopySensor_UART_RX_CTRL_STOP_BITS_MASK            ((uint32) 0x07u)
#define SpectroscopySensor_UART_RX_CTRL_PARITY                    ((uint32) 0x01u << \
                                                                    SpectroscopySensor_UART_RX_CTRL_PARITY_POS)
#define SpectroscopySensor_UART_RX_CTRL_PARITY_ENABLED            ((uint32) 0x01u << \
                                                                    SpectroscopySensor_UART_RX_CTRL_PARITY_ENABLED_POS)
#define SpectroscopySensor_UART_RX_CTRL_POLARITY                  ((uint32) 0x01u << \
                                                                    SpectroscopySensor_UART_RX_CTRL_POLARITY_POS)
#define SpectroscopySensor_UART_RX_CTRL_DROP_ON_PARITY_ERR        ((uint32) 0x01u << \
                                                                   SpectroscopySensor_UART_RX_CTRL_DROP_ON_PARITY_ERR_POS)
#define SpectroscopySensor_UART_RX_CTRL_DROP_ON_FRAME_ERR         ((uint32) 0x01u << \
                                                                    SpectroscopySensor_UART_RX_CTRL_DROP_ON_FRAME_ERR_POS)
#define SpectroscopySensor_UART_RX_CTRL_MP_MODE                   ((uint32) 0x01u << \
                                                                    SpectroscopySensor_UART_RX_CTRL_MP_MODE_POS)
#define SpectroscopySensor_UART_RX_CTRL_LIN_MODE                  ((uint32) 0x01u << \
                                                                    SpectroscopySensor_UART_RX_CTRL_LIN_MODE_POS)
#define SpectroscopySensor_UART_RX_CTRL_SKIP_START                ((uint32) 0x01u << \
                                                                    SpectroscopySensor_UART_RX_CTRL_SKIP_START_POS)
#define SpectroscopySensor_UART_RX_CTRL_BREAK_WIDTH_MASK          ((uint32) 0x0Fu << \
                                                                    SpectroscopySensor_UART_RX_CTRL_BREAK_WIDTH_POS)
/* SpectroscopySensor_UART_RX_STATUS_REG */
#define SpectroscopySensor_UART_RX_STATUS_BR_COUNTER_POS     (0u)  /* [11:0] Baud Rate counter */
#define SpectroscopySensor_UART_RX_STATUS_BR_COUNTER_MASK    ((uint32) 0xFFFu)

#if !(SpectroscopySensor_CY_SCBIP_V0 || SpectroscopySensor_CY_SCBIP_V1)
    /* SpectroscopySensor_UART_FLOW_CTRL_REG */
    #define SpectroscopySensor_UART_FLOW_CTRL_TRIGGER_LEVEL_POS    (0u)  /* [7:0] RTS RX FIFO trigger level         */
    #define SpectroscopySensor_UART_FLOW_CTRL_RTS_POLARITY_POS     (16u) /* [16]  Polarity of the RTS output signal */
    #define SpectroscopySensor_UART_FLOW_CTRL_CTS_POLARITY_POS     (24u) /* [24]  Polarity of the CTS input signal  */
    #define SpectroscopySensor_UART_FLOW_CTRL_CTS_ENABLED_POS      (25u) /* [25]  Enable CTS signal                 */
    #define SpectroscopySensor_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK   ((uint32) SpectroscopySensor_FF_DATA_NR_LOG2_MASK)
    #define SpectroscopySensor_UART_FLOW_CTRL_RTS_POLARITY         ((uint32) 0x01u << \
                                                                       SpectroscopySensor_UART_FLOW_CTRL_RTS_POLARITY_POS)
    #define SpectroscopySensor_UART_FLOW_CTRL_CTS_POLARITY         ((uint32) 0x01u << \
                                                                       SpectroscopySensor_UART_FLOW_CTRL_CTS_POLARITY_POS)
    #define SpectroscopySensor_UART_FLOW_CTRL_CTS_ENABLE           ((uint32) 0x01u << \
                                                                       SpectroscopySensor_UART_FLOW_CTRL_CTS_ENABLED_POS)
#endif /* !(SpectroscopySensor_CY_SCBIP_V0 || SpectroscopySensor_CY_SCBIP_V1) */

/* SpectroscopySensor_I2C_CTRL */
#define SpectroscopySensor_I2C_CTRL_HIGH_PHASE_OVS_POS           (0u)   /* [3:0] Oversampling factor high: master only */
#define SpectroscopySensor_I2C_CTRL_LOW_PHASE_OVS_POS            (4u)   /* [7:4] Oversampling factor low:  master only */
#define SpectroscopySensor_I2C_CTRL_M_READY_DATA_ACK_POS         (8u)   /* [8]   Master ACKs data while RX FIFO != FULL*/
#define SpectroscopySensor_I2C_CTRL_M_NOT_READY_DATA_NACK_POS    (9u)   /* [9]   Master NACKs data if RX FIFO ==  FULL */
#define SpectroscopySensor_I2C_CTRL_S_GENERAL_IGNORE_POS         (11u)  /* [11]  Slave ignores General call            */
#define SpectroscopySensor_I2C_CTRL_S_READY_ADDR_ACK_POS         (12u)  /* [12]  Slave ACKs Address if RX FIFO != FULL */
#define SpectroscopySensor_I2C_CTRL_S_READY_DATA_ACK_POS         (13u)  /* [13]  Slave ACKs data while RX FIFO == FULL */
#define SpectroscopySensor_I2C_CTRL_S_NOT_READY_ADDR_NACK_POS    (14u)  /* [14]  Slave NACKs address if RX FIFO == FULL*/
#define SpectroscopySensor_I2C_CTRL_S_NOT_READY_DATA_NACK_POS    (15u)  /* [15]  Slave NACKs data if RX FIFO is  FULL  */
#define SpectroscopySensor_I2C_CTRL_LOOPBACK_POS                 (16u)  /* [16]  Loop-back                             */
#define SpectroscopySensor_I2C_CTRL_SLAVE_MODE_POS               (30u)  /* [30]  Slave mode enabled                    */
#define SpectroscopySensor_I2C_CTRL_MASTER_MODE_POS              (31u)  /* [31]  Master mode enabled                   */
#define SpectroscopySensor_I2C_CTRL_HIGH_PHASE_OVS_MASK  ((uint32) 0x0Fu)
#define SpectroscopySensor_I2C_CTRL_LOW_PHASE_OVS_MASK   ((uint32) 0x0Fu << \
                                                                SpectroscopySensor_I2C_CTRL_LOW_PHASE_OVS_POS)
#define SpectroscopySensor_I2C_CTRL_M_READY_DATA_ACK      ((uint32) 0x01u << \
                                                                SpectroscopySensor_I2C_CTRL_M_READY_DATA_ACK_POS)
#define SpectroscopySensor_I2C_CTRL_M_NOT_READY_DATA_NACK ((uint32) 0x01u << \
                                                                SpectroscopySensor_I2C_CTRL_M_NOT_READY_DATA_NACK_POS)
#define SpectroscopySensor_I2C_CTRL_S_GENERAL_IGNORE      ((uint32) 0x01u << \
                                                                SpectroscopySensor_I2C_CTRL_S_GENERAL_IGNORE_POS)
#define SpectroscopySensor_I2C_CTRL_S_READY_ADDR_ACK      ((uint32) 0x01u << \
                                                                SpectroscopySensor_I2C_CTRL_S_READY_ADDR_ACK_POS)
#define SpectroscopySensor_I2C_CTRL_S_READY_DATA_ACK      ((uint32) 0x01u << \
                                                                SpectroscopySensor_I2C_CTRL_S_READY_DATA_ACK_POS)
#define SpectroscopySensor_I2C_CTRL_S_NOT_READY_ADDR_NACK ((uint32) 0x01u << \
                                                                SpectroscopySensor_I2C_CTRL_S_NOT_READY_ADDR_NACK_POS)
#define SpectroscopySensor_I2C_CTRL_S_NOT_READY_DATA_NACK ((uint32) 0x01u << \
                                                                SpectroscopySensor_I2C_CTRL_S_NOT_READY_DATA_NACK_POS)
#define SpectroscopySensor_I2C_CTRL_LOOPBACK              ((uint32) 0x01u << \
                                                                SpectroscopySensor_I2C_CTRL_LOOPBACK_POS)
#define SpectroscopySensor_I2C_CTRL_SLAVE_MODE            ((uint32) 0x01u << \
                                                                SpectroscopySensor_I2C_CTRL_SLAVE_MODE_POS)
#define SpectroscopySensor_I2C_CTRL_MASTER_MODE           ((uint32) 0x01u << \
                                                                SpectroscopySensor_I2C_CTRL_MASTER_MODE_POS)
#define SpectroscopySensor_I2C_CTRL_SLAVE_MASTER_MODE_MASK    ((uint32) 0x03u << \
                                                                SpectroscopySensor_I2C_CTRL_SLAVE_MODE_POS)

/* SpectroscopySensor_I2C_STATUS_REG  */
#define SpectroscopySensor_I2C_STATUS_BUS_BUSY_POS    (0u)  /* [0]    Bus busy: internally clocked */
#define SpectroscopySensor_I2C_STATUS_S_READ_POS      (4u)  /* [4]    Slave is read by master      */
#define SpectroscopySensor_I2C_STATUS_M_READ_POS      (5u)  /* [5]    Master reads Slave           */
#define SpectroscopySensor_I2C_STATUS_EZBUF_ADDR_POS  (8u)  /* [15:8] EZAddress                    */
#define SpectroscopySensor_I2C_STATUS_BUS_BUSY        ((uint32) 0x01u)
#define SpectroscopySensor_I2C_STATUS_S_READ          ((uint32) 0x01u << SpectroscopySensor_I2C_STATUS_S_READ_POS)
#define SpectroscopySensor_I2C_STATUS_M_READ          ((uint32) 0x01u << SpectroscopySensor_I2C_STATUS_M_READ_POS)
#define SpectroscopySensor_I2C_STATUS_EZBUF_ADDR_MASK ((uint32) 0xFFu << SpectroscopySensor_I2C_STATUS_EZBUF_ADDR_POS)

/* SpectroscopySensor_I2C_MASTER_CMD_REG */
#define SpectroscopySensor_I2C_MASTER_CMD_M_START_POS             (0u)  /* [0] Master generate Start                */
#define SpectroscopySensor_I2C_MASTER_CMD_M_START_ON_IDLE_POS     (1u)  /* [1] Master generate Start if bus is free */
#define SpectroscopySensor_I2C_MASTER_CMD_M_ACK_POS               (2u)  /* [2] Master generate ACK                  */
#define SpectroscopySensor_I2C_MASTER_CMD_M_NACK_POS              (3u)  /* [3] Master generate NACK                 */
#define SpectroscopySensor_I2C_MASTER_CMD_M_STOP_POS              (4u)  /* [4] Master generate Stop                 */
#define SpectroscopySensor_I2C_MASTER_CMD_M_START         ((uint32) 0x01u)
#define SpectroscopySensor_I2C_MASTER_CMD_M_START_ON_IDLE ((uint32) 0x01u << \
                                                                   SpectroscopySensor_I2C_MASTER_CMD_M_START_ON_IDLE_POS)
#define SpectroscopySensor_I2C_MASTER_CMD_M_ACK           ((uint32) 0x01u << \
                                                                   SpectroscopySensor_I2C_MASTER_CMD_M_ACK_POS)
#define SpectroscopySensor_I2C_MASTER_CMD_M_NACK          ((uint32) 0x01u << \
                                                                    SpectroscopySensor_I2C_MASTER_CMD_M_NACK_POS)
#define SpectroscopySensor_I2C_MASTER_CMD_M_STOP          ((uint32) 0x01u << \
                                                                    SpectroscopySensor_I2C_MASTER_CMD_M_STOP_POS)

/* SpectroscopySensor_I2C_SLAVE_CMD_REG  */
#define SpectroscopySensor_I2C_SLAVE_CMD_S_ACK_POS    (0u)  /* [0] Slave generate ACK  */
#define SpectroscopySensor_I2C_SLAVE_CMD_S_NACK_POS   (1u)  /* [1] Slave generate NACK */
#define SpectroscopySensor_I2C_SLAVE_CMD_S_ACK        ((uint32) 0x01u)
#define SpectroscopySensor_I2C_SLAVE_CMD_S_NACK       ((uint32) 0x01u << SpectroscopySensor_I2C_SLAVE_CMD_S_NACK_POS)

#define SpectroscopySensor_I2C_SLAVE_CMD_S_ACK_POS    (0u)  /* [0] Slave generate ACK  */
#define SpectroscopySensor_I2C_SLAVE_CMD_S_NACK_POS   (1u)  /* [1] Slave generate NACK */
#define SpectroscopySensor_I2C_SLAVE_CMD_S_ACK        ((uint32) 0x01u)
#define SpectroscopySensor_I2C_SLAVE_CMD_S_NACK       ((uint32) 0x01u << SpectroscopySensor_I2C_SLAVE_CMD_S_NACK_POS)

/* SpectroscopySensor_I2C_CFG_REG */
#if (SpectroscopySensor_CY_SCBIP_V0)
#define SpectroscopySensor_I2C_CFG_SDA_FILT_HYS_POS           (0u)  /* [1:0]   Trim bits for the I2C SDA filter         */
#define SpectroscopySensor_I2C_CFG_SDA_FILT_TRIM_POS          (2u)  /* [3:2]   Trim bits for the I2C SDA filter         */
#define SpectroscopySensor_I2C_CFG_SCL_FILT_HYS_POS           (4u)  /* [5:4]   Trim bits for the I2C SCL filter         */
#define SpectroscopySensor_I2C_CFG_SCL_FILT_TRIM_POS          (6u)  /* [7:6]   Trim bits for the I2C SCL filter         */
#define SpectroscopySensor_I2C_CFG_SDA_FILT_OUT_HYS_POS       (8u)  /* [9:8]   Trim bits for I2C SDA filter output path */
#define SpectroscopySensor_I2C_CFG_SDA_FILT_OUT_TRIM_POS      (10u) /* [11:10] Trim bits for I2C SDA filter output path */
#define SpectroscopySensor_I2C_CFG_SDA_FILT_HS_POS            (16u) /* [16]    '0': 50 ns filter, '1': 10 ns filter     */
#define SpectroscopySensor_I2C_CFG_SDA_FILT_ENABLED_POS       (17u) /* [17]    I2C SDA filter enabled                   */
#define SpectroscopySensor_I2C_CFG_SCL_FILT_HS_POS            (24u) /* [24]    '0': 50 ns filter, '1': 10 ns filter     */
#define SpectroscopySensor_I2C_CFG_SCL_FILT_ENABLED_POS       (25u) /* [25]    I2C SCL filter enabled                   */
#define SpectroscopySensor_I2C_CFG_SDA_FILT_OUT_HS_POS        (26u) /* [26]    '0': 50 ns filter, '1': 10 ns filter     */
#define SpectroscopySensor_I2C_CFG_SDA_FILT_OUT_ENABLED_POS   (27u) /* [27]    I2C SDA output delay filter enabled      */
#define SpectroscopySensor_I2C_CFG_SDA_FILT_HYS_MASK          ((uint32) 0x03u)
#define SpectroscopySensor_I2C_CFG_SDA_FILT_TRIM_MASK         ((uint32) 0x03u << \
                                                                SpectroscopySensor_I2C_CFG_SDA_FILT_TRIM_POS)
#define SpectroscopySensor_I2C_CFG_SCL_FILT_HYS_MASK          ((uint32) 0x03u << \
                                                                SpectroscopySensor_I2C_CFG_SCL_FILT_HYS_POS)
#define SpectroscopySensor_I2C_CFG_SCL_FILT_TRIM_MASK         ((uint32) 0x03u << \
                                                                SpectroscopySensor_I2C_CFG_SCL_FILT_TRIM_POS)
#define SpectroscopySensor_I2C_CFG_SDA_FILT_OUT_HYS_MASK      ((uint32) 0x03u << \
                                                                SpectroscopySensor_I2C_CFG_SDA_FILT_OUT_HYS_POS)
#define SpectroscopySensor_I2C_CFG_SDA_FILT_OUT_TRIM_MASK     ((uint32) 0x03u << \
                                                                SpectroscopySensor_I2C_CFG_SDA_FILT_OUT_TRIM_POS)
#define SpectroscopySensor_I2C_CFG_SDA_FILT_HS                ((uint32) 0x01u << \
                                                                SpectroscopySensor_I2C_CFG_SDA_FILT_HS_POS)
#define SpectroscopySensor_I2C_CFG_SDA_FILT_ENABLED           ((uint32) 0x01u << \
                                                                SpectroscopySensor_I2C_CFG_SDA_FILT_ENABLED_POS)
#define SpectroscopySensor_I2C_CFG_SCL_FILT_HS                ((uint32) 0x01u << \
                                                                SpectroscopySensor_I2C_CFG_SCL_FILT_HS_POS)
#define SpectroscopySensor_I2C_CFG_SCL_FILT_ENABLED           ((uint32) 0x01u << \
                                                                SpectroscopySensor_I2C_CFG_SCL_FILT_ENABLED_POS)
#define SpectroscopySensor_I2C_CFG_SDA_FILT_OUT_HS            ((uint32) 0x01u << \
                                                                SpectroscopySensor_I2C_CFG_SDA_FILT_OUT_HS_POS)
#define SpectroscopySensor_I2C_CFG_SDA_FILT_OUT_ENABLED       ((uint32) 0x01u << \
                                                                SpectroscopySensor_I2C_CFG_SDA_FILT_OUT_ENABLED_POS)
#else
#define SpectroscopySensor_I2C_CFG_SDA_IN_FILT_TRIM_POS   (0u)  /* [1:0] Trim bits for "i2c_sda_in" 50 ns filter */
#define SpectroscopySensor_I2C_CFG_SDA_IN_FILT_SEL_POS    (4u)  /* [4]   "i2c_sda_in" filter delay: 0 ns and 50 ns */
#define SpectroscopySensor_I2C_CFG_SCL_IN_FILT_TRIM_POS   (8u)  /* [9:8] Trim bits for "i2c_scl_in" 50 ns filter */
#define SpectroscopySensor_I2C_CFG_SCL_IN_FILT_SEL_POS    (12u) /* [12]  "i2c_scl_in" filter delay: 0 ns and 50 ns */
#define SpectroscopySensor_I2C_CFG_SDA_OUT_FILT0_TRIM_POS (16u) /* [17:16] Trim bits for "i2c_sda_out" 50 ns filter 0 */
#define SpectroscopySensor_I2C_CFG_SDA_OUT_FILT1_TRIM_POS (18u) /* [19:18] Trim bits for "i2c_sda_out" 50 ns filter 1 */
#define SpectroscopySensor_I2C_CFG_SDA_OUT_FILT2_TRIM_POS (20u) /* [21:20] Trim bits for "i2c_sda_out" 50 ns filter 2 */
#define SpectroscopySensor_I2C_CFG_SDA_OUT_FILT_SEL_POS   (28u) /* [29:28] Cumulative "i2c_sda_out" filter delay: */

#define SpectroscopySensor_I2C_CFG_SDA_IN_FILT_TRIM_MASK  ((uint32) 0x03u)
#define SpectroscopySensor_I2C_CFG_SDA_IN_FILT_SEL        ((uint32) 0x01u << SpectroscopySensor_I2C_CFG_SDA_IN_FILT_SEL_POS)
#define SpectroscopySensor_I2C_CFG_SCL_IN_FILT_TRIM_MASK  ((uint32) 0x03u << \
                                                            SpectroscopySensor_I2C_CFG_SCL_IN_FILT_TRIM_POS)
#define SpectroscopySensor_I2C_CFG_SCL_IN_FILT_SEL        ((uint32) 0x01u << SpectroscopySensor_I2C_CFG_SCL_IN_FILT_SEL_POS)
#define SpectroscopySensor_I2C_CFG_SDA_OUT_FILT0_TRIM_MASK ((uint32) 0x03u << \
                                                            SpectroscopySensor_I2C_CFG_SDA_OUT_FILT0_TRIM_POS)
#define SpectroscopySensor_I2C_CFG_SDA_OUT_FILT1_TRIM_MASK ((uint32) 0x03u << \
                                                            SpectroscopySensor_I2C_CFG_SDA_OUT_FILT1_TRIM_POS)
#define SpectroscopySensor_I2C_CFG_SDA_OUT_FILT2_TRIM_MASK ((uint32) 0x03u << \
                                                            SpectroscopySensor_I2C_CFG_SDA_OUT_FILT2_TRIM_POS)
#define SpectroscopySensor_I2C_CFG_SDA_OUT_FILT_SEL_MASK   ((uint32) 0x03u << \
                                                            SpectroscopySensor_I2C_CFG_SDA_OUT_FILT_SEL_POS)
#endif /* (SpectroscopySensor_CY_SCBIP_V0) */


/* SpectroscopySensor_TX_CTRL_REG */
#define SpectroscopySensor_TX_CTRL_DATA_WIDTH_POS     (0u)  /* [3:0] Data frame width: (Data width - 1) */
#define SpectroscopySensor_TX_CTRL_MSB_FIRST_POS      (8u)  /* [8]   MSB first shifter-out             */
#define SpectroscopySensor_TX_CTRL_ENABLED_POS        (31u) /* [31]  Transmitter enabled               */
#define SpectroscopySensor_TX_CTRL_DATA_WIDTH_MASK    ((uint32) 0x0Fu)
#define SpectroscopySensor_TX_CTRL_MSB_FIRST          ((uint32) 0x01u << SpectroscopySensor_TX_CTRL_MSB_FIRST_POS)
#define SpectroscopySensor_TX_CTRL_LSB_FIRST          ((uint32) 0x00u)
#define SpectroscopySensor_TX_CTRL_ENABLED            ((uint32) 0x01u << SpectroscopySensor_TX_CTRL_ENABLED_POS)

/* SpectroscopySensor_TX_CTRL_FIFO_REG */
#define SpectroscopySensor_TX_FIFO_CTRL_TRIGGER_LEVEL_POS     (0u)  /* [2:0] Trigger level                              */
#define SpectroscopySensor_TX_FIFO_CTRL_CLEAR_POS             (16u) /* [16]  Clear TX FIFO: cleared after set           */
#define SpectroscopySensor_TX_FIFO_CTRL_FREEZE_POS            (17u) /* [17]  Freeze TX FIFO: HW do not inc read pointer */
#define SpectroscopySensor_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK    ((uint32) SpectroscopySensor_FF_DATA_NR_LOG2_MASK)
#define SpectroscopySensor_TX_FIFO_CTRL_CLEAR                 ((uint32) 0x01u << SpectroscopySensor_TX_FIFO_CTRL_CLEAR_POS)
#define SpectroscopySensor_TX_FIFO_CTRL_FREEZE                ((uint32) 0x01u << SpectroscopySensor_TX_FIFO_CTRL_FREEZE_POS)

/* SpectroscopySensor_TX_FIFO_STATUS_REG */
#define SpectroscopySensor_TX_FIFO_STATUS_USED_POS    (0u)  /* [3:0]   Amount of entries in TX FIFO */
#define SpectroscopySensor_TX_FIFO_SR_VALID_POS       (15u) /* [15]    Shifter status of TX FIFO    */
#define SpectroscopySensor_TX_FIFO_STATUS_RD_PTR_POS  (16u) /* [18:16] TX FIFO read pointer         */
#define SpectroscopySensor_TX_FIFO_STATUS_WR_PTR_POS  (24u) /* [26:24] TX FIFO write pointer        */
#define SpectroscopySensor_TX_FIFO_STATUS_USED_MASK   ((uint32) SpectroscopySensor_FF_DATA_NR_LOG2_PLUS1_MASK)
#define SpectroscopySensor_TX_FIFO_SR_VALID           ((uint32) 0x01u << SpectroscopySensor_TX_FIFO_SR_VALID_POS)
#define SpectroscopySensor_TX_FIFO_STATUS_RD_PTR_MASK ((uint32) SpectroscopySensor_FF_DATA_NR_LOG2_MASK << \
                                                                    SpectroscopySensor_TX_FIFO_STATUS_RD_PTR_POS)
#define SpectroscopySensor_TX_FIFO_STATUS_WR_PTR_MASK ((uint32) SpectroscopySensor_FF_DATA_NR_LOG2_MASK << \
                                                                    SpectroscopySensor_TX_FIFO_STATUS_WR_PTR_POS)

/* SpectroscopySensor_TX_FIFO_WR_REG */
#define SpectroscopySensor_TX_FIFO_WR_POS    (0u)  /* [15:0] Data written into TX FIFO */
#define SpectroscopySensor_TX_FIFO_WR_MASK   ((uint32) 0xFFu)

/* SpectroscopySensor_RX_CTRL_REG */
#define SpectroscopySensor_RX_CTRL_DATA_WIDTH_POS     (0u)  /* [3:0] Data frame width: (Data width - 1) */
#define SpectroscopySensor_RX_CTRL_MSB_FIRST_POS      (8u)  /* [8]   MSB first shifter-out             */
#define SpectroscopySensor_RX_CTRL_MEDIAN_POS         (9u)  /* [9]   Median filter                     */
#define SpectroscopySensor_RX_CTRL_ENABLED_POS        (31u) /* [31]  Receiver enabled                  */
#define SpectroscopySensor_RX_CTRL_DATA_WIDTH_MASK    ((uint32) 0x0Fu)
#define SpectroscopySensor_RX_CTRL_MSB_FIRST          ((uint32) 0x01u << SpectroscopySensor_RX_CTRL_MSB_FIRST_POS)
#define SpectroscopySensor_RX_CTRL_LSB_FIRST          ((uint32) 0x00u)
#define SpectroscopySensor_RX_CTRL_MEDIAN             ((uint32) 0x01u << SpectroscopySensor_RX_CTRL_MEDIAN_POS)
#define SpectroscopySensor_RX_CTRL_ENABLED            ((uint32) 0x01u << SpectroscopySensor_RX_CTRL_ENABLED_POS)


/* SpectroscopySensor_RX_FIFO_CTRL_REG */
#define SpectroscopySensor_RX_FIFO_CTRL_TRIGGER_LEVEL_POS     (0u)   /* [2:0] Trigger level                            */
#define SpectroscopySensor_RX_FIFO_CTRL_CLEAR_POS             (16u)  /* [16]  Clear RX FIFO: clear after set           */
#define SpectroscopySensor_RX_FIFO_CTRL_FREEZE_POS            (17u)  /* [17]  Freeze RX FIFO: HW writes has not effect */
#define SpectroscopySensor_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK    ((uint32) SpectroscopySensor_FF_DATA_NR_LOG2_MASK)
#define SpectroscopySensor_RX_FIFO_CTRL_CLEAR                 ((uint32) 0x01u << SpectroscopySensor_RX_FIFO_CTRL_CLEAR_POS)
#define SpectroscopySensor_RX_FIFO_CTRL_FREEZE                ((uint32) 0x01u << SpectroscopySensor_RX_FIFO_CTRL_FREEZE_POS)

/* SpectroscopySensor_RX_FIFO_STATUS_REG */
#define SpectroscopySensor_RX_FIFO_STATUS_USED_POS    (0u)   /* [3:0]   Amount of entries in RX FIFO */
#define SpectroscopySensor_RX_FIFO_SR_VALID_POS       (15u)  /* [15]    Shifter status of RX FIFO    */
#define SpectroscopySensor_RX_FIFO_STATUS_RD_PTR_POS  (16u)  /* [18:16] RX FIFO read pointer         */
#define SpectroscopySensor_RX_FIFO_STATUS_WR_PTR_POS  (24u)  /* [26:24] RX FIFO write pointer        */
#define SpectroscopySensor_RX_FIFO_STATUS_USED_MASK   ((uint32) SpectroscopySensor_FF_DATA_NR_LOG2_PLUS1_MASK)
#define SpectroscopySensor_RX_FIFO_SR_VALID           ((uint32) 0x01u << SpectroscopySensor_RX_FIFO_SR_VALID_POS)
#define SpectroscopySensor_RX_FIFO_STATUS_RD_PTR_MASK ((uint32) SpectroscopySensor_FF_DATA_NR_LOG2_MASK << \
                                                                    SpectroscopySensor_RX_FIFO_STATUS_RD_PTR_POS)
#define SpectroscopySensor_RX_FIFO_STATUS_WR_PTR_MASK ((uint32) SpectroscopySensor_FF_DATA_NR_LOG2_MASK << \
                                                                    SpectroscopySensor_RX_FIFO_STATUS_WR_PTR_POS)

/* SpectroscopySensor_RX_MATCH_REG */
#define SpectroscopySensor_RX_MATCH_ADDR_POS     (0u)  /* [7:0]   Slave address                        */
#define SpectroscopySensor_RX_MATCH_MASK_POS     (16u) /* [23:16] Slave address mask: 0 - doesn't care */
#define SpectroscopySensor_RX_MATCH_ADDR_MASK    ((uint32) 0xFFu)
#define SpectroscopySensor_RX_MATCH_MASK_MASK    ((uint32) 0xFFu << SpectroscopySensor_RX_MATCH_MASK_POS)

/* SpectroscopySensor_RX_FIFO_WR_REG */
#define SpectroscopySensor_RX_FIFO_RD_POS    (0u)  /* [15:0] Data read from RX FIFO */
#define SpectroscopySensor_RX_FIFO_RD_MASK   ((uint32) 0xFFu)

/* SpectroscopySensor_RX_FIFO_RD_SILENT_REG */
#define SpectroscopySensor_RX_FIFO_RD_SILENT_POS     (0u)  /* [15:0] Data read from RX FIFO: not remove data from FIFO */
#define SpectroscopySensor_RX_FIFO_RD_SILENT_MASK    ((uint32) 0xFFu)

/* SpectroscopySensor_RX_FIFO_RD_SILENT_REG */
#define SpectroscopySensor_RX_FIFO_RD_SILENT_POS     (0u)  /* [15:0] Data read from RX FIFO: not remove data from FIFO */
#define SpectroscopySensor_RX_FIFO_RD_SILENT_MASK    ((uint32) 0xFFu)

/* SpectroscopySensor_EZBUF_DATA_REG */
#define SpectroscopySensor_EZBUF_DATA_POS   (0u)  /* [7:0] Data from EZ Memory */
#define SpectroscopySensor_EZBUF_DATA_MASK  ((uint32) 0xFFu)

/*  SpectroscopySensor_INTR_CAUSE_REG */
#define SpectroscopySensor_INTR_CAUSE_MASTER_POS  (0u)  /* [0] Master interrupt active                 */
#define SpectroscopySensor_INTR_CAUSE_SLAVE_POS   (1u)  /* [1] Slave interrupt active                  */
#define SpectroscopySensor_INTR_CAUSE_TX_POS      (2u)  /* [2] Transmitter interrupt active            */
#define SpectroscopySensor_INTR_CAUSE_RX_POS      (3u)  /* [3] Receiver interrupt active               */
#define SpectroscopySensor_INTR_CAUSE_I2C_EC_POS  (4u)  /* [4] Externally clock I2C interrupt active   */
#define SpectroscopySensor_INTR_CAUSE_SPI_EC_POS  (5u)  /* [5] Externally clocked SPI interrupt active */
#define SpectroscopySensor_INTR_CAUSE_MASTER      ((uint32) 0x01u)
#define SpectroscopySensor_INTR_CAUSE_SLAVE       ((uint32) 0x01u << SpectroscopySensor_INTR_CAUSE_SLAVE_POS)
#define SpectroscopySensor_INTR_CAUSE_TX          ((uint32) 0x01u << SpectroscopySensor_INTR_CAUSE_TX_POS)
#define SpectroscopySensor_INTR_CAUSE_RX          ((uint32) 0x01u << SpectroscopySensor_INTR_CAUSE_RX_POS)
#define SpectroscopySensor_INTR_CAUSE_I2C_EC      ((uint32) 0x01u << SpectroscopySensor_INTR_CAUSE_I2C_EC_POS)
#define SpectroscopySensor_INTR_CAUSE_SPI_EC      ((uint32) 0x01u << SpectroscopySensor_INTR_CAUSE_SPI_EC_POS)

/* SpectroscopySensor_INTR_SPI_EC_REG, SpectroscopySensor_INTR_SPI_EC_MASK_REG, SpectroscopySensor_INTR_SPI_EC_MASKED_REG */
#define SpectroscopySensor_INTR_SPI_EC_WAKE_UP_POS          (0u)  /* [0] Address match: triggers wakeup of chip */
#define SpectroscopySensor_INTR_SPI_EC_EZBUF_STOP_POS       (1u)  /* [1] Externally clocked Stop detected       */
#define SpectroscopySensor_INTR_SPI_EC_EZBUF_WRITE_STOP_POS (2u)  /* [2] Externally clocked Write Stop detected */
#define SpectroscopySensor_INTR_SPI_EC_WAKE_UP              ((uint32) 0x01u)
#define SpectroscopySensor_INTR_SPI_EC_EZBUF_STOP           ((uint32) 0x01u << \
                                                                    SpectroscopySensor_INTR_SPI_EC_EZBUF_STOP_POS)
#define SpectroscopySensor_INTR_SPI_EC_EZBUF_WRITE_STOP     ((uint32) 0x01u << \
                                                                    SpectroscopySensor_INTR_SPI_EC_EZBUF_WRITE_STOP_POS)

/* SpectroscopySensor_INTR_I2C_EC, SpectroscopySensor_INTR_I2C_EC_MASK, SpectroscopySensor_INTR_I2C_EC_MASKED */
#define SpectroscopySensor_INTR_I2C_EC_WAKE_UP_POS          (0u)  /* [0] Address match: triggers wakeup of chip */
#define SpectroscopySensor_INTR_I2C_EC_EZBUF_STOP_POS       (1u)  /* [1] Externally clocked Stop detected       */
#define SpectroscopySensor_INTR_I2C_EC_EZBUF_WRITE_STOP_POS (2u)  /* [2] Externally clocked Write Stop detected */
#define SpectroscopySensor_INTR_I2C_EC_WAKE_UP              ((uint32) 0x01u)
#define SpectroscopySensor_INTR_I2C_EC_EZBUF_STOP           ((uint32) 0x01u << \
                                                                    SpectroscopySensor_INTR_I2C_EC_EZBUF_STOP_POS)
#define SpectroscopySensor_INTR_I2C_EC_EZBUF_WRITE_STOP     ((uint32) 0x01u << \
                                                                    SpectroscopySensor_INTR_I2C_EC_EZBUF_WRITE_STOP_POS)

/* SpectroscopySensor_INTR_MASTER, SpectroscopySensor_INTR_MASTER_SET,
   SpectroscopySensor_INTR_MASTER_MASK, SpectroscopySensor_INTR_MASTER_MASKED */
#define SpectroscopySensor_INTR_MASTER_I2C_ARB_LOST_POS   (0u)  /* [0] Master lost arbitration                          */
#define SpectroscopySensor_INTR_MASTER_I2C_NACK_POS       (1u)  /* [1] Master receives NACK: address or write to slave  */
#define SpectroscopySensor_INTR_MASTER_I2C_ACK_POS        (2u)  /* [2] Master receives NACK: address or write to slave  */
#define SpectroscopySensor_INTR_MASTER_I2C_STOP_POS       (4u)  /* [4] Master detects the Stop: only self generated Stop*/
#define SpectroscopySensor_INTR_MASTER_I2C_BUS_ERROR_POS  (8u)  /* [8] Master detects bus error: misplaced Start or Stop*/
#define SpectroscopySensor_INTR_MASTER_SPI_DONE_POS       (9u)  /* [9] Master complete transfer: Only for SPI           */
#define SpectroscopySensor_INTR_MASTER_I2C_ARB_LOST       ((uint32) 0x01u)
#define SpectroscopySensor_INTR_MASTER_I2C_NACK           ((uint32) 0x01u << SpectroscopySensor_INTR_MASTER_I2C_NACK_POS)
#define SpectroscopySensor_INTR_MASTER_I2C_ACK            ((uint32) 0x01u << SpectroscopySensor_INTR_MASTER_I2C_ACK_POS)
#define SpectroscopySensor_INTR_MASTER_I2C_STOP           ((uint32) 0x01u << SpectroscopySensor_INTR_MASTER_I2C_STOP_POS)
#define SpectroscopySensor_INTR_MASTER_I2C_BUS_ERROR      ((uint32) 0x01u << \
                                                                    SpectroscopySensor_INTR_MASTER_I2C_BUS_ERROR_POS)
#define SpectroscopySensor_INTR_MASTER_SPI_DONE           ((uint32) 0x01u << SpectroscopySensor_INTR_MASTER_SPI_DONE_POS)

/*
* SpectroscopySensor_INTR_SLAVE, SpectroscopySensor_INTR_SLAVE_SET,
* SpectroscopySensor_INTR_SLAVE_MASK, SpectroscopySensor_INTR_SLAVE_MASKED
*/
#define SpectroscopySensor_INTR_SLAVE_I2C_ARB_LOST_POS         (0u)  /* [0]  Slave lost arbitration                   */
#define SpectroscopySensor_INTR_SLAVE_I2C_NACK_POS             (1u)  /* [1]  Slave receives NACK: master reads data   */
#define SpectroscopySensor_INTR_SLAVE_I2C_ACK_POS              (2u)  /* [2]  Slave receives ACK: master reads data    */
#define SpectroscopySensor_INTR_SLAVE_I2C_WRITE_STOP_POS       (3u)  /* [3]  Slave detects end of write transaction   */
#define SpectroscopySensor_INTR_SLAVE_I2C_STOP_POS             (4u)  /* [4]  Slave detects end of transaction intended */
#define SpectroscopySensor_INTR_SLAVE_I2C_START_POS            (5u)  /* [5]  Slave detects Start                      */
#define SpectroscopySensor_INTR_SLAVE_I2C_ADDR_MATCH_POS       (6u)  /* [6]  Slave address matches                    */
#define SpectroscopySensor_INTR_SLAVE_I2C_GENERAL_POS          (7u)  /* [7]  General call received                    */
#define SpectroscopySensor_INTR_SLAVE_I2C_BUS_ERROR_POS        (8u)  /* [8]  Slave detects bus error                  */
#define SpectroscopySensor_INTR_SLAVE_SPI_EZBUF_WRITE_STOP_POS (9u)  /* [9]  Slave write complete: Only for SPI       */
#define SpectroscopySensor_INTR_SLAVE_SPI_EZBUF_STOP_POS       (10u) /* [10] Slave end of transaction: Only for SPI   */
#define SpectroscopySensor_INTR_SLAVE_SPI_BUS_ERROR_POS        (11u) /* [11] Slave detects bus error: Only for SPI    */
#define SpectroscopySensor_INTR_SLAVE_I2C_ARB_LOST             ((uint32) 0x01u)
#define SpectroscopySensor_INTR_SLAVE_I2C_NACK                 ((uint32) 0x01u << \
                                                                    SpectroscopySensor_INTR_SLAVE_I2C_NACK_POS)
#define SpectroscopySensor_INTR_SLAVE_I2C_ACK                  ((uint32) 0x01u << \
                                                                    SpectroscopySensor_INTR_SLAVE_I2C_ACK_POS)
#define SpectroscopySensor_INTR_SLAVE_I2C_WRITE_STOP           ((uint32) 0x01u << \
                                                                    SpectroscopySensor_INTR_SLAVE_I2C_WRITE_STOP_POS)
#define SpectroscopySensor_INTR_SLAVE_I2C_STOP                 ((uint32) 0x01u << \
                                                                    SpectroscopySensor_INTR_SLAVE_I2C_STOP_POS)
#define SpectroscopySensor_INTR_SLAVE_I2C_START                ((uint32) 0x01u << \
                                                                    SpectroscopySensor_INTR_SLAVE_I2C_START_POS)
#define SpectroscopySensor_INTR_SLAVE_I2C_ADDR_MATCH           ((uint32) 0x01u << \
                                                                    SpectroscopySensor_INTR_SLAVE_I2C_ADDR_MATCH_POS)
#define SpectroscopySensor_INTR_SLAVE_I2C_GENERAL              ((uint32) 0x01u << \
                                                                    SpectroscopySensor_INTR_SLAVE_I2C_GENERAL_POS)
#define SpectroscopySensor_INTR_SLAVE_I2C_BUS_ERROR            ((uint32) 0x01u << \
                                                                    SpectroscopySensor_INTR_SLAVE_I2C_BUS_ERROR_POS)
#define SpectroscopySensor_INTR_SLAVE_SPI_EZBUF_WRITE_STOP     ((uint32) 0x01u << \
                                                                   SpectroscopySensor_INTR_SLAVE_SPI_EZBUF_WRITE_STOP_POS)
#define SpectroscopySensor_INTR_SLAVE_SPI_EZBUF_STOP           ((uint32) 0x01u << \
                                                                    SpectroscopySensor_INTR_SLAVE_SPI_EZBUF_STOP_POS)
#define SpectroscopySensor_INTR_SLAVE_SPI_BUS_ERROR           ((uint32) 0x01u << \
                                                                    SpectroscopySensor_INTR_SLAVE_SPI_BUS_ERROR_POS)

/*
* SpectroscopySensor_INTR_TX, SpectroscopySensor_INTR_TX_SET,
* SpectroscopySensor_INTR_TX_MASK, SpectroscopySensor_INTR_TX_MASKED
*/
#define SpectroscopySensor_INTR_TX_TRIGGER_POS        (0u)  /* [0]  Trigger on TX FIFO entires                       */
#define SpectroscopySensor_INTR_TX_NOT_FULL_POS       (1u)  /* [1]  TX FIFO is not full                              */
#define SpectroscopySensor_INTR_TX_EMPTY_POS          (4u)  /* [4]  TX FIFO is empty                                 */
#define SpectroscopySensor_INTR_TX_OVERFLOW_POS       (5u)  /* [5]  Attempt to write to a full TX FIFO               */
#define SpectroscopySensor_INTR_TX_UNDERFLOW_POS      (6u)  /* [6]  Attempt to read from an empty TX FIFO            */
#define SpectroscopySensor_INTR_TX_BLOCKED_POS        (7u)  /* [7]  No access to the EZ memory                       */
#define SpectroscopySensor_INTR_TX_UART_NACK_POS      (8u)  /* [8]  UART transmitter received a NACK: SmartCard mode */
#define SpectroscopySensor_INTR_TX_UART_DONE_POS      (9u)  /* [9]  UART transmitter done even                       */
#define SpectroscopySensor_INTR_TX_UART_ARB_LOST_POS  (10u) /* [10] UART lost arbitration: LIN or SmartCard          */
#define SpectroscopySensor_INTR_TX_TRIGGER            ((uint32) 0x01u)
#define SpectroscopySensor_INTR_TX_FIFO_LEVEL         (SpectroscopySensor_INTR_TX_TRIGGER)
#define SpectroscopySensor_INTR_TX_NOT_FULL           ((uint32) 0x01u << SpectroscopySensor_INTR_TX_NOT_FULL_POS)
#define SpectroscopySensor_INTR_TX_EMPTY              ((uint32) 0x01u << SpectroscopySensor_INTR_TX_EMPTY_POS)
#define SpectroscopySensor_INTR_TX_OVERFLOW           ((uint32) 0x01u << SpectroscopySensor_INTR_TX_OVERFLOW_POS)
#define SpectroscopySensor_INTR_TX_UNDERFLOW          ((uint32) 0x01u << SpectroscopySensor_INTR_TX_UNDERFLOW_POS)
#define SpectroscopySensor_INTR_TX_BLOCKED            ((uint32) 0x01u << SpectroscopySensor_INTR_TX_BLOCKED_POS)
#define SpectroscopySensor_INTR_TX_UART_NACK          ((uint32) 0x01u << SpectroscopySensor_INTR_TX_UART_NACK_POS)
#define SpectroscopySensor_INTR_TX_UART_DONE          ((uint32) 0x01u << SpectroscopySensor_INTR_TX_UART_DONE_POS)
#define SpectroscopySensor_INTR_TX_UART_ARB_LOST      ((uint32) 0x01u << SpectroscopySensor_INTR_TX_UART_ARB_LOST_POS)

/*
* SpectroscopySensor_INTR_RX, SpectroscopySensor_INTR_RX_SET,
* SpectroscopySensor_INTR_RX_MASK, SpectroscopySensor_INTR_RX_MASKED
*/
#define SpectroscopySensor_INTR_RX_TRIGGER_POS        (0u)   /* [0]  Trigger on RX FIFO entires            */
#define SpectroscopySensor_INTR_RX_NOT_EMPTY_POS      (2u)   /* [2]  RX FIFO is not empty                  */
#define SpectroscopySensor_INTR_RX_FULL_POS           (3u)   /* [3]  RX FIFO is full                       */
#define SpectroscopySensor_INTR_RX_OVERFLOW_POS       (5u)   /* [5]  Attempt to write to a full RX FIFO    */
#define SpectroscopySensor_INTR_RX_UNDERFLOW_POS      (6u)   /* [6]  Attempt to read from an empty RX FIFO */
#define SpectroscopySensor_INTR_RX_BLOCKED_POS        (7u)   /* [7]  No access to the EZ memory            */
#define SpectroscopySensor_INTR_RX_FRAME_ERROR_POS    (8u)   /* [8]  Frame error in received data frame    */
#define SpectroscopySensor_INTR_RX_PARITY_ERROR_POS   (9u)   /* [9]  Parity error in received data frame   */
#define SpectroscopySensor_INTR_RX_BAUD_DETECT_POS    (10u)  /* [10] LIN baud rate detection is completed   */
#define SpectroscopySensor_INTR_RX_BREAK_DETECT_POS   (11u)  /* [11] Break detection is successful         */
#define SpectroscopySensor_INTR_RX_TRIGGER            ((uint32) 0x01u)
#define SpectroscopySensor_INTR_RX_FIFO_LEVEL         (SpectroscopySensor_INTR_RX_TRIGGER)
#define SpectroscopySensor_INTR_RX_NOT_EMPTY          ((uint32) 0x01u << SpectroscopySensor_INTR_RX_NOT_EMPTY_POS)
#define SpectroscopySensor_INTR_RX_FULL               ((uint32) 0x01u << SpectroscopySensor_INTR_RX_FULL_POS)
#define SpectroscopySensor_INTR_RX_OVERFLOW           ((uint32) 0x01u << SpectroscopySensor_INTR_RX_OVERFLOW_POS)
#define SpectroscopySensor_INTR_RX_UNDERFLOW          ((uint32) 0x01u << SpectroscopySensor_INTR_RX_UNDERFLOW_POS)
#define SpectroscopySensor_INTR_RX_BLOCKED            ((uint32) 0x01u << SpectroscopySensor_INTR_RX_BLOCKED_POS)
#define SpectroscopySensor_INTR_RX_FRAME_ERROR        ((uint32) 0x01u << SpectroscopySensor_INTR_RX_FRAME_ERROR_POS)
#define SpectroscopySensor_INTR_RX_PARITY_ERROR       ((uint32) 0x01u << SpectroscopySensor_INTR_RX_PARITY_ERROR_POS)
#define SpectroscopySensor_INTR_RX_BAUD_DETECT        ((uint32) 0x01u << SpectroscopySensor_INTR_RX_BAUD_DETECT_POS)
#define SpectroscopySensor_INTR_RX_BREAK_DETECT       ((uint32) 0x01u << SpectroscopySensor_INTR_RX_BREAK_DETECT_POS)

/* Define all interrupt sources */
#define SpectroscopySensor_INTR_I2C_EC_ALL    (SpectroscopySensor_INTR_I2C_EC_WAKE_UP    | \
                                             SpectroscopySensor_INTR_I2C_EC_EZBUF_STOP | \
                                             SpectroscopySensor_INTR_I2C_EC_EZBUF_WRITE_STOP)

#define SpectroscopySensor_INTR_SPI_EC_ALL    (SpectroscopySensor_INTR_SPI_EC_WAKE_UP    | \
                                             SpectroscopySensor_INTR_SPI_EC_EZBUF_STOP | \
                                             SpectroscopySensor_INTR_SPI_EC_EZBUF_WRITE_STOP)

#define SpectroscopySensor_INTR_MASTER_ALL    (SpectroscopySensor_INTR_MASTER_I2C_ARB_LOST  | \
                                             SpectroscopySensor_INTR_MASTER_I2C_NACK      | \
                                             SpectroscopySensor_INTR_MASTER_I2C_ACK       | \
                                             SpectroscopySensor_INTR_MASTER_I2C_STOP      | \
                                             SpectroscopySensor_INTR_MASTER_I2C_BUS_ERROR | \
                                             SpectroscopySensor_INTR_MASTER_SPI_DONE)

#define SpectroscopySensor_INTR_SLAVE_ALL     (SpectroscopySensor_INTR_SLAVE_I2C_ARB_LOST      | \
                                             SpectroscopySensor_INTR_SLAVE_I2C_NACK          | \
                                             SpectroscopySensor_INTR_SLAVE_I2C_ACK           | \
                                             SpectroscopySensor_INTR_SLAVE_I2C_WRITE_STOP    | \
                                             SpectroscopySensor_INTR_SLAVE_I2C_STOP          | \
                                             SpectroscopySensor_INTR_SLAVE_I2C_START         | \
                                             SpectroscopySensor_INTR_SLAVE_I2C_ADDR_MATCH    | \
                                             SpectroscopySensor_INTR_SLAVE_I2C_GENERAL       | \
                                             SpectroscopySensor_INTR_SLAVE_I2C_BUS_ERROR     | \
                                             SpectroscopySensor_INTR_SLAVE_SPI_EZBUF_WRITE_STOP | \
                                             SpectroscopySensor_INTR_SLAVE_SPI_EZBUF_STOP       | \
                                             SpectroscopySensor_INTR_SLAVE_SPI_BUS_ERROR)

#define SpectroscopySensor_INTR_TX_ALL        (SpectroscopySensor_INTR_TX_TRIGGER   | \
                                             SpectroscopySensor_INTR_TX_NOT_FULL  | \
                                             SpectroscopySensor_INTR_TX_EMPTY     | \
                                             SpectroscopySensor_INTR_TX_OVERFLOW  | \
                                             SpectroscopySensor_INTR_TX_UNDERFLOW | \
                                             SpectroscopySensor_INTR_TX_BLOCKED   | \
                                             SpectroscopySensor_INTR_TX_UART_NACK | \
                                             SpectroscopySensor_INTR_TX_UART_DONE | \
                                             SpectroscopySensor_INTR_TX_UART_ARB_LOST)

#define SpectroscopySensor_INTR_RX_ALL        (SpectroscopySensor_INTR_RX_TRIGGER      | \
                                             SpectroscopySensor_INTR_RX_NOT_EMPTY    | \
                                             SpectroscopySensor_INTR_RX_FULL         | \
                                             SpectroscopySensor_INTR_RX_OVERFLOW     | \
                                             SpectroscopySensor_INTR_RX_UNDERFLOW    | \
                                             SpectroscopySensor_INTR_RX_BLOCKED      | \
                                             SpectroscopySensor_INTR_RX_FRAME_ERROR  | \
                                             SpectroscopySensor_INTR_RX_PARITY_ERROR | \
                                             SpectroscopySensor_INTR_RX_BAUD_DETECT  | \
                                             SpectroscopySensor_INTR_RX_BREAK_DETECT)

/* I2C and EZI2C slave address defines */
#define SpectroscopySensor_I2C_SLAVE_ADDR_POS    (0x01u)    /* 7-bit address shift */
#define SpectroscopySensor_I2C_SLAVE_ADDR_MASK   (0xFEu)    /* 8-bit address mask */

/* OVS constants for IrDA Low Power operation */
#define SpectroscopySensor_CTRL_OVS_IRDA_LP_OVS16     (0x00u)
#define SpectroscopySensor_CTRL_OVS_IRDA_LP_OVS32     (0x01u)
#define SpectroscopySensor_CTRL_OVS_IRDA_LP_OVS48     (0x02u)
#define SpectroscopySensor_CTRL_OVS_IRDA_LP_OVS96     (0x03u)
#define SpectroscopySensor_CTRL_OVS_IRDA_LP_OVS192    (0x04u)
#define SpectroscopySensor_CTRL_OVS_IRDA_LP_OVS768    (0x05u)
#define SpectroscopySensor_CTRL_OVS_IRDA_LP_OVS1536   (0x06u)

/* OVS constant for IrDA */
#define SpectroscopySensor_CTRL_OVS_IRDA_OVS16        (SpectroscopySensor_UART_IRDA_LP_OVS16)


/***************************************
*    Common Macro Definitions
***************************************/

/* Re-enables the SCB IP. A clear enable bit has a different effect
* on the scb IP depending on the version:
*  CY_SCBIP_V0: resets state, status, TX and RX FIFOs.
*  CY_SCBIP_V1 or later: resets state, status, TX and RX FIFOs and interrupt sources.
* Clear I2C command registers are because they are not impacted by re-enable.
*/
#define SpectroscopySensor_SCB_SW_RESET   SpectroscopySensor_I2CFwBlockReset()

/* TX FIFO macro */
#define SpectroscopySensor_CLEAR_TX_FIFO \
                            do{        \
                                SpectroscopySensor_TX_FIFO_CTRL_REG |= ((uint32)  SpectroscopySensor_TX_FIFO_CTRL_CLEAR); \
                                SpectroscopySensor_TX_FIFO_CTRL_REG &= ((uint32) ~SpectroscopySensor_TX_FIFO_CTRL_CLEAR); \
                            }while(0)

#define SpectroscopySensor_GET_TX_FIFO_ENTRIES    (SpectroscopySensor_TX_FIFO_STATUS_REG & \
                                                 SpectroscopySensor_TX_FIFO_STATUS_USED_MASK)

#define SpectroscopySensor_GET_TX_FIFO_SR_VALID   ((0u != (SpectroscopySensor_TX_FIFO_STATUS_REG & \
                                                         SpectroscopySensor_TX_FIFO_SR_VALID)) ? (1u) : (0u))

/* RX FIFO macro */
#define SpectroscopySensor_CLEAR_RX_FIFO \
                            do{        \
                                SpectroscopySensor_RX_FIFO_CTRL_REG |= ((uint32)  SpectroscopySensor_RX_FIFO_CTRL_CLEAR); \
                                SpectroscopySensor_RX_FIFO_CTRL_REG &= ((uint32) ~SpectroscopySensor_RX_FIFO_CTRL_CLEAR); \
                            }while(0)

#define SpectroscopySensor_GET_RX_FIFO_ENTRIES    (SpectroscopySensor_RX_FIFO_STATUS_REG & \
                                                    SpectroscopySensor_RX_FIFO_STATUS_USED_MASK)

#define SpectroscopySensor_GET_RX_FIFO_SR_VALID   ((0u != (SpectroscopySensor_RX_FIFO_STATUS_REG & \
                                                         SpectroscopySensor_RX_FIFO_SR_VALID)) ? (1u) : (0u))

/* Write interrupt source: set sourceMask bits in SpectroscopySensor_INTR_X_MASK_REG */
#define SpectroscopySensor_WRITE_INTR_I2C_EC_MASK(sourceMask) \
                                                do{         \
                                                    SpectroscopySensor_INTR_I2C_EC_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

#if (!SpectroscopySensor_CY_SCBIP_V1)
    #define SpectroscopySensor_WRITE_INTR_SPI_EC_MASK(sourceMask) \
                                                do{         \
                                                    SpectroscopySensor_INTR_SPI_EC_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)
#endif /* (!SpectroscopySensor_CY_SCBIP_V1) */

#define SpectroscopySensor_WRITE_INTR_MASTER_MASK(sourceMask) \
                                                do{         \
                                                    SpectroscopySensor_INTR_MASTER_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

#define SpectroscopySensor_WRITE_INTR_SLAVE_MASK(sourceMask)  \
                                                do{         \
                                                    SpectroscopySensor_INTR_SLAVE_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

#define SpectroscopySensor_WRITE_INTR_TX_MASK(sourceMask)     \
                                                do{         \
                                                    SpectroscopySensor_INTR_TX_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

#define SpectroscopySensor_WRITE_INTR_RX_MASK(sourceMask)     \
                                                do{         \
                                                    SpectroscopySensor_INTR_RX_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

/* Enable interrupt source: set sourceMask bits in SpectroscopySensor_INTR_X_MASK_REG */
#define SpectroscopySensor_ENABLE_INTR_I2C_EC(sourceMask) \
                                                do{     \
                                                    SpectroscopySensor_INTR_I2C_EC_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)
#if (!SpectroscopySensor_CY_SCBIP_V1)
    #define SpectroscopySensor_ENABLE_INTR_SPI_EC(sourceMask) \
                                                do{     \
                                                    SpectroscopySensor_INTR_SPI_EC_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)
#endif /* (!SpectroscopySensor_CY_SCBIP_V1) */

#define SpectroscopySensor_ENABLE_INTR_MASTER(sourceMask) \
                                                do{     \
                                                    SpectroscopySensor_INTR_MASTER_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)

#define SpectroscopySensor_ENABLE_INTR_SLAVE(sourceMask)  \
                                                do{     \
                                                    SpectroscopySensor_INTR_SLAVE_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)

#define SpectroscopySensor_ENABLE_INTR_TX(sourceMask)     \
                                                do{     \
                                                    SpectroscopySensor_INTR_TX_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)

#define SpectroscopySensor_ENABLE_INTR_RX(sourceMask)     \
                                                do{     \
                                                    SpectroscopySensor_INTR_RX_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)

/* Disable interrupt source: clear sourceMask bits in SpectroscopySensor_INTR_X_MASK_REG */
#define SpectroscopySensor_DISABLE_INTR_I2C_EC(sourceMask) \
                                do{                      \
                                    SpectroscopySensor_INTR_I2C_EC_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                }while(0)

#if (!SpectroscopySensor_CY_SCBIP_V1)
    #define SpectroscopySensor_DISABLE_INTR_SPI_EC(sourceMask) \
                                do{                      \
                                    SpectroscopySensor_INTR_SPI_EC_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                 }while(0)
#endif /* (!SpectroscopySensor_CY_SCBIP_V1) */

#define SpectroscopySensor_DISABLE_INTR_MASTER(sourceMask) \
                                do{                      \
                                SpectroscopySensor_INTR_MASTER_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                }while(0)

#define SpectroscopySensor_DISABLE_INTR_SLAVE(sourceMask) \
                                do{                     \
                                    SpectroscopySensor_INTR_SLAVE_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                }while(0)

#define SpectroscopySensor_DISABLE_INTR_TX(sourceMask)    \
                                do{                     \
                                    SpectroscopySensor_INTR_TX_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                 }while(0)

#define SpectroscopySensor_DISABLE_INTR_RX(sourceMask)    \
                                do{                     \
                                    SpectroscopySensor_INTR_RX_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                }while(0)

/* Set interrupt sources: write sourceMask bits in SpectroscopySensor_INTR_X_SET_REG */
#define SpectroscopySensor_SET_INTR_MASTER(sourceMask)    \
                                                do{     \
                                                    SpectroscopySensor_INTR_MASTER_SET_REG = (uint32) (sourceMask); \
                                                }while(0)

#define SpectroscopySensor_SET_INTR_SLAVE(sourceMask) \
                                                do{ \
                                                    SpectroscopySensor_INTR_SLAVE_SET_REG = (uint32) (sourceMask); \
                                                }while(0)

#define SpectroscopySensor_SET_INTR_TX(sourceMask)    \
                                                do{ \
                                                    SpectroscopySensor_INTR_TX_SET_REG = (uint32) (sourceMask); \
                                                }while(0)

#define SpectroscopySensor_SET_INTR_RX(sourceMask)    \
                                                do{ \
                                                    SpectroscopySensor_INTR_RX_SET_REG = (uint32) (sourceMask); \
                                                }while(0)

/* Clear interrupt sources: write sourceMask bits in SpectroscopySensor_INTR_X_REG */
#define SpectroscopySensor_CLEAR_INTR_I2C_EC(sourceMask)  \
                                                do{     \
                                                    SpectroscopySensor_INTR_I2C_EC_REG = (uint32) (sourceMask); \
                                                }while(0)

#if (!SpectroscopySensor_CY_SCBIP_V1)
    #define SpectroscopySensor_CLEAR_INTR_SPI_EC(sourceMask)  \
                                                do{     \
                                                    SpectroscopySensor_INTR_SPI_EC_REG = (uint32) (sourceMask); \
                                                }while(0)
#endif /* (!SpectroscopySensor_CY_SCBIP_V1) */

#define SpectroscopySensor_CLEAR_INTR_MASTER(sourceMask)  \
                                                do{     \
                                                    SpectroscopySensor_INTR_MASTER_REG = (uint32) (sourceMask); \
                                                }while(0)

#define SpectroscopySensor_CLEAR_INTR_SLAVE(sourceMask)   \
                                                do{     \
                                                    SpectroscopySensor_INTR_SLAVE_REG  = (uint32) (sourceMask); \
                                                }while(0)

#define SpectroscopySensor_CLEAR_INTR_TX(sourceMask)      \
                                                do{     \
                                                    SpectroscopySensor_INTR_TX_REG     = (uint32) (sourceMask); \
                                                }while(0)

#define SpectroscopySensor_CLEAR_INTR_RX(sourceMask)      \
                                                do{     \
                                                    SpectroscopySensor_INTR_RX_REG     = (uint32) (sourceMask); \
                                                }while(0)

/* Return true if sourceMask is set in SpectroscopySensor_INTR_CAUSE_REG */
#define SpectroscopySensor_CHECK_CAUSE_INTR(sourceMask)    (0u != (SpectroscopySensor_INTR_CAUSE_REG & (sourceMask)))

/* Return true if sourceMask is set in INTR_X_MASKED_REG */
#define SpectroscopySensor_CHECK_INTR_I2C_EC(sourceMask)  (0u != (SpectroscopySensor_INTR_I2C_EC_REG & (sourceMask)))
#if (!SpectroscopySensor_CY_SCBIP_V1)
    #define SpectroscopySensor_CHECK_INTR_SPI_EC(sourceMask)  (0u != (SpectroscopySensor_INTR_SPI_EC_REG & (sourceMask)))
#endif /* (!SpectroscopySensor_CY_SCBIP_V1) */
#define SpectroscopySensor_CHECK_INTR_MASTER(sourceMask)  (0u != (SpectroscopySensor_INTR_MASTER_REG & (sourceMask)))
#define SpectroscopySensor_CHECK_INTR_SLAVE(sourceMask)   (0u != (SpectroscopySensor_INTR_SLAVE_REG  & (sourceMask)))
#define SpectroscopySensor_CHECK_INTR_TX(sourceMask)      (0u != (SpectroscopySensor_INTR_TX_REG     & (sourceMask)))
#define SpectroscopySensor_CHECK_INTR_RX(sourceMask)      (0u != (SpectroscopySensor_INTR_RX_REG     & (sourceMask)))

/* Return true if sourceMask is set in SpectroscopySensor_INTR_X_MASKED_REG */
#define SpectroscopySensor_CHECK_INTR_I2C_EC_MASKED(sourceMask)   (0u != (SpectroscopySensor_INTR_I2C_EC_MASKED_REG & \
                                                                       (sourceMask)))
#if (!SpectroscopySensor_CY_SCBIP_V1)
    #define SpectroscopySensor_CHECK_INTR_SPI_EC_MASKED(sourceMask)   (0u != (SpectroscopySensor_INTR_SPI_EC_MASKED_REG & \
                                                                       (sourceMask)))
#endif /* (!SpectroscopySensor_CY_SCBIP_V1) */
#define SpectroscopySensor_CHECK_INTR_MASTER_MASKED(sourceMask)   (0u != (SpectroscopySensor_INTR_MASTER_MASKED_REG & \
                                                                       (sourceMask)))
#define SpectroscopySensor_CHECK_INTR_SLAVE_MASKED(sourceMask)    (0u != (SpectroscopySensor_INTR_SLAVE_MASKED_REG  & \
                                                                       (sourceMask)))
#define SpectroscopySensor_CHECK_INTR_TX_MASKED(sourceMask)       (0u != (SpectroscopySensor_INTR_TX_MASKED_REG     & \
                                                                       (sourceMask)))
#define SpectroscopySensor_CHECK_INTR_RX_MASKED(sourceMask)       (0u != (SpectroscopySensor_INTR_RX_MASKED_REG     & \
                                                                       (sourceMask)))

/* Return true if sourceMask is set in SpectroscopySensor_CTRL_REG: generally is used to check enable bit */
#define SpectroscopySensor_GET_CTRL_ENABLED    (0u != (SpectroscopySensor_CTRL_REG & SpectroscopySensor_CTRL_ENABLED))

#define SpectroscopySensor_CHECK_SLAVE_AUTO_ADDR_NACK     (0u != (SpectroscopySensor_I2C_CTRL_REG & \
                                                                SpectroscopySensor_I2C_CTRL_S_NOT_READY_DATA_NACK))


/***************************************
*      I2C Macro Definitions
***************************************/

/* Enable auto ACK/NACK */
#define SpectroscopySensor_ENABLE_SLAVE_AUTO_ADDR_NACK \
                            do{                      \
                                SpectroscopySensor_I2C_CTRL_REG |= SpectroscopySensor_I2C_CTRL_S_NOT_READY_DATA_NACK; \
                            }while(0)

#define SpectroscopySensor_ENABLE_SLAVE_AUTO_DATA_ACK \
                            do{                     \
                                SpectroscopySensor_I2C_CTRL_REG |= SpectroscopySensor_I2C_CTRL_S_READY_DATA_ACK; \
                            }while(0)

#define SpectroscopySensor_ENABLE_SLAVE_AUTO_DATA_NACK \
                            do{                      \
                                SpectroscopySensor_I2C_CTRL_REG |= SpectroscopySensor_I2C_CTRL_S_NOT_READY_DATA_NACK; \
                            }while(0)

#define SpectroscopySensor_ENABLE_MASTER_AUTO_DATA_ACK \
                            do{                      \
                                SpectroscopySensor_I2C_CTRL_REG |= SpectroscopySensor_I2C_CTRL_M_READY_DATA_ACK; \
                            }while(0)

#define SpectroscopySensor_ENABLE_MASTER_AUTO_DATA_NACK \
                            do{                       \
                                SpectroscopySensor_I2C_CTRL_REG |= SpectroscopySensor_I2C_CTRL_M_NOT_READY_DATA_NACK; \
                            }while(0)

/* Disable auto ACK/NACK */
#define SpectroscopySensor_DISABLE_SLAVE_AUTO_ADDR_NACK \
                            do{                       \
                                SpectroscopySensor_I2C_CTRL_REG &= ~SpectroscopySensor_I2C_CTRL_S_NOT_READY_DATA_NACK; \
                            }while(0)

#define SpectroscopySensor_DISABLE_SLAVE_AUTO_DATA_ACK \
                            do{                      \
                                SpectroscopySensor_I2C_CTRL_REG &= ~SpectroscopySensor_I2C_CTRL_S_READY_DATA_ACK; \
                            }while(0)

#define SpectroscopySensor_DISABLE_SLAVE_AUTO_DATA_NACK \
                            do{                       \
                                SpectroscopySensor_I2C_CTRL_REG &= ~SpectroscopySensor_I2C_CTRL_S_NOT_READY_DATA_NACK; \
                            }while(0)

#define SpectroscopySensor_DISABLE_MASTER_AUTO_DATA_ACK \
                            do{                       \
                                SpectroscopySensor_I2C_CTRL_REG &= ~SpectroscopySensor_I2C_CTRL_M_READY_DATA_ACK; \
                            }while(0)

#define SpectroscopySensor_DISABLE_MASTER_AUTO_DATA_NACK \
                            do{                        \
                                SpectroscopySensor_I2C_CTRL_REG &= ~SpectroscopySensor_I2C_CTRL_M_NOT_READY_DATA_NACK; \
                            }while(0)

/* Enable Slave autoACK/NACK Data */
#define SpectroscopySensor_ENABLE_SLAVE_AUTO_DATA \
                            do{                 \
                                SpectroscopySensor_I2C_CTRL_REG |= (SpectroscopySensor_I2C_CTRL_S_READY_DATA_ACK |      \
                                                                  SpectroscopySensor_I2C_CTRL_S_NOT_READY_DATA_NACK); \
                            }while(0)

/* Disable Slave autoACK/NACK Data */
#define SpectroscopySensor_DISABLE_SLAVE_AUTO_DATA \
                            do{                  \
                                SpectroscopySensor_I2C_CTRL_REG &= ((uint32) \
                                                                  ~(SpectroscopySensor_I2C_CTRL_S_READY_DATA_ACK |       \
                                                                    SpectroscopySensor_I2C_CTRL_S_NOT_READY_DATA_NACK)); \
                            }while(0)

/* Disable Master autoACK/NACK Data */
#define SpectroscopySensor_DISABLE_MASTER_AUTO_DATA \
                            do{                   \
                                SpectroscopySensor_I2C_CTRL_REG &= ((uint32) \
                                                                  ~(SpectroscopySensor_I2C_CTRL_M_READY_DATA_ACK |       \
                                                                    SpectroscopySensor_I2C_CTRL_M_NOT_READY_DATA_NACK)); \
                            }while(0)
/* Disables auto data ACK/NACK bits */
#define SpectroscopySensor_DISABLE_AUTO_DATA \
                do{                        \
                    SpectroscopySensor_I2C_CTRL_REG &= ((uint32) ~(SpectroscopySensor_I2C_CTRL_M_READY_DATA_ACK      |  \
                                                                 SpectroscopySensor_I2C_CTRL_M_NOT_READY_DATA_NACK |  \
                                                                 SpectroscopySensor_I2C_CTRL_S_READY_DATA_ACK      |  \
                                                                 SpectroscopySensor_I2C_CTRL_S_NOT_READY_DATA_NACK)); \
                }while(0)

/* Master commands */
#define SpectroscopySensor_I2C_MASTER_GENERATE_START \
                            do{                    \
                                SpectroscopySensor_I2C_MASTER_CMD_REG = SpectroscopySensor_I2C_MASTER_CMD_M_START_ON_IDLE; \
                            }while(0)

#define SpectroscopySensor_I2C_MASTER_CLEAR_START \
                            do{                 \
                                SpectroscopySensor_I2C_MASTER_CMD_REG =  ((uint32) 0u); \
                            }while(0)

#define SpectroscopySensor_I2C_MASTER_GENERATE_RESTART SpectroscopySensor_I2CReStartGeneration()

#define SpectroscopySensor_I2C_MASTER_GENERATE_STOP \
                            do{                   \
                                SpectroscopySensor_I2C_MASTER_CMD_REG =                                            \
                                    (SpectroscopySensor_I2C_MASTER_CMD_M_STOP |                                    \
                                        (SpectroscopySensor_CHECK_I2C_STATUS(SpectroscopySensor_I2C_STATUS_M_READ) ? \
                                            (SpectroscopySensor_I2C_MASTER_CMD_M_NACK) : (0u)));                   \
                            }while(0)

#define SpectroscopySensor_I2C_MASTER_GENERATE_ACK \
                            do{                  \
                                SpectroscopySensor_I2C_MASTER_CMD_REG = SpectroscopySensor_I2C_MASTER_CMD_M_ACK; \
                            }while(0)

#define SpectroscopySensor_I2C_MASTER_GENERATE_NACK \
                            do{                   \
                                SpectroscopySensor_I2C_MASTER_CMD_REG = SpectroscopySensor_I2C_MASTER_CMD_M_NACK; \
                            }while(0)

/* Slave commands */
#define SpectroscopySensor_I2C_SLAVE_GENERATE_ACK \
                            do{                 \
                                SpectroscopySensor_I2C_SLAVE_CMD_REG = SpectroscopySensor_I2C_SLAVE_CMD_S_ACK; \
                            }while(0)

#if (SpectroscopySensor_CY_SCBIP_V0 || SpectroscopySensor_CY_SCBIP_V1)
    /* Slave NACK generation for EC_AM logic on address phase. Ticket ID #183902 */
    void SpectroscopySensor_I2CSlaveNackGeneration(void);
    #define SpectroscopySensor_I2C_SLAVE_GENERATE_NACK SpectroscopySensor_I2CSlaveNackGeneration()

#else
    #define SpectroscopySensor_I2C_SLAVE_GENERATE_NACK \
                            do{                      \
                                SpectroscopySensor_I2C_SLAVE_CMD_REG = SpectroscopySensor_I2C_SLAVE_CMD_S_NACK; \
                            }while(0)
#endif /* (SpectroscopySensor_CY_SCBIP_V0 || SpectroscopySensor_CY_SCBIP_V1) */

#define SpectroscopySensor_I2C_SLAVE_CLEAR_NACK \
                            do{               \
                                SpectroscopySensor_I2C_SLAVE_CMD_REG = 0u; \
                            }while(0)

/* Return 8-bit address. The input address should be 7-bits */
#define SpectroscopySensor_GET_I2C_8BIT_ADDRESS(addr) (((uint32) ((uint32) (addr) << \
                                                                    SpectroscopySensor_I2C_SLAVE_ADDR_POS)) & \
                                                                        SpectroscopySensor_I2C_SLAVE_ADDR_MASK)

#define SpectroscopySensor_GET_I2C_7BIT_ADDRESS(addr) ((uint32) (addr) >> SpectroscopySensor_I2C_SLAVE_ADDR_POS)

/* Adjust SDA filter Trim settings */
#define SpectroscopySensor_DEFAULT_I2C_CFG_SDA_FILT_TRIM  (0x02u)
#define SpectroscopySensor_EC_AM_I2C_CFG_SDA_FILT_TRIM    (0x03u)

#if (SpectroscopySensor_CY_SCBIP_V0)
    #define SpectroscopySensor_SET_I2C_CFG_SDA_FILT_TRIM(sdaTrim) \
        do{                                                 \
            SpectroscopySensor_I2C_CFG_REG =                  \
                            ((SpectroscopySensor_I2C_CFG_REG & (uint32) ~SpectroscopySensor_I2C_CFG_SDA_FILT_TRIM_MASK) | \
                             ((uint32) ((uint32) (sdaTrim) <<SpectroscopySensor_I2C_CFG_SDA_FILT_TRIM_POS)));           \
        }while(0)
#endif /* (SpectroscopySensor_CY_SCBIP_V0) */

/* Enable/Disable analog and digital filter */
#define SpectroscopySensor_DIGITAL_FILTER_DISABLE    (0u)
#define SpectroscopySensor_DIGITAL_FILTER_ENABLE     (1u)
#define SpectroscopySensor_I2C_DATA_RATE_FS_MODE_MAX (400u)
#if (SpectroscopySensor_CY_SCBIP_V0)
    /* SpectroscopySensor_I2C_CFG_SDA_FILT_OUT_ENABLED is disabled by default */
    #define SpectroscopySensor_I2C_CFG_FILT_MASK  (SpectroscopySensor_I2C_CFG_SDA_FILT_ENABLED | \
                                                 SpectroscopySensor_I2C_CFG_SCL_FILT_ENABLED)
#else
    /* SpectroscopySensor_I2C_CFG_SDA_OUT_FILT_SEL_MASK is disabled by default */
    #define SpectroscopySensor_I2C_CFG_FILT_MASK  (SpectroscopySensor_I2C_CFG_SDA_IN_FILT_SEL | \
                                                 SpectroscopySensor_I2C_CFG_SCL_IN_FILT_SEL)
#endif /* (SpectroscopySensor_CY_SCBIP_V0) */

#define SpectroscopySensor_I2C_CFG_ANALOG_FITER_DISABLE \
        do{                                           \
            SpectroscopySensor_I2C_CFG_REG &= (uint32) ~SpectroscopySensor_I2C_CFG_FILT_MASK; \
        }while(0)

#define SpectroscopySensor_I2C_CFG_ANALOG_FITER_ENABLE \
        do{                                          \
            SpectroscopySensor_I2C_CFG_REG |= (uint32)  SpectroscopySensor_I2C_CFG_FILT_MASK; \
        }while(0)

/* Return slave select number from SPI_CTRL register */
#define SpectroscopySensor_GET_SPI_CTRL_SS(activeSelect) (((uint32) ((uint32) (activeSelect) << \
                                                                    SpectroscopySensor_SPI_CTRL_SLAVE_SELECT_POS)) & \
                                                                        SpectroscopySensor_SPI_CTRL_SLAVE_SELECT_MASK)

/* Return true if bit is set in SpectroscopySensor_I2C_STATUS_REG */
#define SpectroscopySensor_CHECK_I2C_STATUS(sourceMask)   (0u != (SpectroscopySensor_I2C_STATUS_REG & (sourceMask)))

/* Return true if bit is set in SpectroscopySensor_SPI_STATUS_REG */
#define SpectroscopySensor_CHECK_SPI_STATUS(sourceMask)   (0u != (SpectroscopySensor_SPI_STATUS_REG & (sourceMask)))

/* Return FIFO size depends on SpectroscopySensor_CTRL_BYTE_MODE bit */
#define SpectroscopySensor_GET_FIFO_SIZE(condition) ((0u != (condition)) ? \
                                                    (2u * SpectroscopySensor_FIFO_SIZE) : (SpectroscopySensor_FIFO_SIZE))


/***************************************
*       Get Macros Definitions
***************************************/

/* SpectroscopySensor_CTRL */
#define SpectroscopySensor_GET_CTRL_OVS(oversample)       (((uint32) (oversample) - 1u) & SpectroscopySensor_CTRL_OVS_MASK)

#define SpectroscopySensor_GET_CTRL_EC_OP_MODE(opMode)        ((0u != (opMode)) ? \
                                                                (SpectroscopySensor_CTRL_EC_OP_MODE)  : (0u))

#define SpectroscopySensor_GET_CTRL_EC_AM_MODE(amMode)        ((0u != (amMode)) ? \
                                                                (SpectroscopySensor_CTRL_EC_AM_MODE)  : (0u))

#define SpectroscopySensor_GET_CTRL_BLOCK(block)              ((0u != (block))  ? \
                                                                (SpectroscopySensor_CTRL_BLOCK)       : (0u))

#define SpectroscopySensor_GET_CTRL_ADDR_ACCEPT(acceptAddr)   ((0u != (acceptAddr)) ? \
                                                                (SpectroscopySensor_CTRL_ADDR_ACCEPT) : (0u))

#if (SpectroscopySensor_CY_SCBIP_V0 || SpectroscopySensor_CY_SCBIP_V1)
    #define SpectroscopySensor_GET_CTRL_BYTE_MODE(mode)   (0u)
#else
    #define SpectroscopySensor_GET_CTRL_BYTE_MODE(mode)   ((0u != (mode)) ? \
                                                            (SpectroscopySensor_CTRL_BYTE_MODE) : (0u))
#endif /* (SpectroscopySensor_CY_SCBIP_V0 || SpectroscopySensor_CY_SCBIP_V1) */

/* SpectroscopySensor_I2C_CTRL */
#define SpectroscopySensor_GET_I2C_CTRL_HIGH_PHASE_OVS(oversampleHigh) (((uint32) (oversampleHigh) - 1u) & \
                                                                        SpectroscopySensor_I2C_CTRL_HIGH_PHASE_OVS_MASK)

#define SpectroscopySensor_GET_I2C_CTRL_LOW_PHASE_OVS(oversampleLow)  ((((uint32) (oversampleLow) - 1u) << \
                                                                    SpectroscopySensor_I2C_CTRL_LOW_PHASE_OVS_POS) &  \
                                                                    SpectroscopySensor_I2C_CTRL_LOW_PHASE_OVS_MASK)

#define SpectroscopySensor_GET_I2C_CTRL_S_NOT_READY_ADDR_NACK(wakeNack) ((0u != (wakeNack)) ? \
                                                            (SpectroscopySensor_I2C_CTRL_S_NOT_READY_ADDR_NACK) : (0u))

#define SpectroscopySensor_GET_I2C_CTRL_S_GENERAL_IGNORE(genCall) ((0u != (genCall)) ? \
                                                                    (SpectroscopySensor_I2C_CTRL_S_GENERAL_IGNORE) : (0u))

#define SpectroscopySensor_GET_I2C_CTRL_SL_MSTR_MODE(mode)    ((uint32)(mode) << SpectroscopySensor_I2C_CTRL_SLAVE_MODE_POS)

/* SpectroscopySensor_SPI_CTRL */
#define SpectroscopySensor_GET_SPI_CTRL_CONTINUOUS(separate)  ((0u != (separate)) ? \
                                                                (SpectroscopySensor_SPI_CTRL_CONTINUOUS) : (0u))

#define SpectroscopySensor_GET_SPI_CTRL_SELECT_PRECEDE(mode)  ((0u != (mode)) ? \
                                                                      (SpectroscopySensor_SPI_CTRL_SELECT_PRECEDE) : (0u))

#define SpectroscopySensor_GET_SPI_CTRL_SCLK_MODE(mode)       (((uint32) (mode) << \
                                                                        SpectroscopySensor_SPI_CTRL_CPHA_POS) & \
                                                                        SpectroscopySensor_SPI_CTRL_SCLK_MODE_MASK)

#define SpectroscopySensor_GET_SPI_CTRL_LATE_MISO_SAMPLE(lateMiso) ((0u != (lateMiso)) ? \
                                                                    (SpectroscopySensor_SPI_CTRL_LATE_MISO_SAMPLE) : (0u))

#if (SpectroscopySensor_CY_SCBIP_V0 || SpectroscopySensor_CY_SCBIP_V1)
    #define SpectroscopySensor_GET_SPI_CTRL_SCLK_CONTINUOUS(sclkType) (0u)
    #define SpectroscopySensor_GET_SPI_CTRL_SSEL_POLARITY(polarity)   (0u)
#else
    #define SpectroscopySensor_GET_SPI_CTRL_SCLK_CONTINUOUS(sclkType) ((0u != (sclkType)) ? \
                                                                    (SpectroscopySensor_SPI_CTRL_SCLK_CONTINUOUS) : (0u))

    #define SpectroscopySensor_GET_SPI_CTRL_SSEL_POLARITY(polarity)   (((uint32) (polarity) << \
                                                                     SpectroscopySensor_SPI_CTRL_SSEL0_POLARITY_POS) & \
                                                                     SpectroscopySensor_SPI_CTRL_SSEL_POLARITY_MASK)
#endif /* ((SpectroscopySensor_CY_SCBIP_V0 || SpectroscopySensor_CY_SCBIP_V1) */

#define SpectroscopySensor_GET_SPI_CTRL_SUB_MODE(mode)        (((uint32) (mode) << SpectroscopySensor_SPI_CTRL_MODE_POS) & \
                                                                                 SpectroscopySensor_SPI_CTRL_MODE_MASK)

#define SpectroscopySensor_GET_SPI_CTRL_SLAVE_SELECT(select)  (((uint32) (select) << \
                                                                      SpectroscopySensor_SPI_CTRL_SLAVE_SELECT_POS) & \
                                                                      SpectroscopySensor_SPI_CTRL_SLAVE_SELECT_MASK)

#define SpectroscopySensor_GET_SPI_CTRL_MASTER_MODE(mode)     ((0u != (mode)) ? \
                                                                (SpectroscopySensor_SPI_CTRL_MASTER) : (0u))

/* SpectroscopySensor_UART_CTRL */
#define SpectroscopySensor_GET_UART_CTRL_MODE(mode)           (((uint32) (mode) << \
                                                                            SpectroscopySensor_UART_CTRL_MODE_POS) & \
                                                                            SpectroscopySensor_UART_CTRL_MODE_MASK)

/* SpectroscopySensor_UART_RX_CTRL */
#define SpectroscopySensor_GET_UART_RX_CTRL_MODE(stopBits)    (((uint32) (stopBits) - 1u) & \
                                                                        SpectroscopySensor_UART_RX_CTRL_STOP_BITS_MASK)

#define SpectroscopySensor_GET_UART_RX_CTRL_PARITY(parity)    ((0u != (parity)) ? \
                                                                    (SpectroscopySensor_UART_RX_CTRL_PARITY) : (0u))

#define SpectroscopySensor_GET_UART_RX_CTRL_POLARITY(polarity)    ((0u != (polarity)) ? \
                                                                    (SpectroscopySensor_UART_RX_CTRL_POLARITY) : (0u))

#define SpectroscopySensor_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(dropErr) ((0u != (dropErr)) ? \
                                                        (SpectroscopySensor_UART_RX_CTRL_DROP_ON_PARITY_ERR) : (0u))

#define SpectroscopySensor_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(dropErr) ((0u != (dropErr)) ? \
                                                        (SpectroscopySensor_UART_RX_CTRL_DROP_ON_FRAME_ERR) : (0u))

#define SpectroscopySensor_GET_UART_RX_CTRL_MP_MODE(mpMode)   ((0u != (mpMode)) ? \
                                                        (SpectroscopySensor_UART_RX_CTRL_MP_MODE) : (0u))

#define SpectroscopySensor_GET_UART_RX_CTRL_BREAK_WIDTH(width)    (((uint32) ((uint32) (width) - 1u) << \
                                                                    SpectroscopySensor_UART_RX_CTRL_BREAK_WIDTH_POS) & \
                                                                    SpectroscopySensor_UART_RX_CTRL_BREAK_WIDTH_MASK)

/* SpectroscopySensor_UART_TX_CTRL */
#define SpectroscopySensor_GET_UART_TX_CTRL_MODE(stopBits)    (((uint32) (stopBits) - 1u) & \
                                                                SpectroscopySensor_UART_RX_CTRL_STOP_BITS_MASK)

#define SpectroscopySensor_GET_UART_TX_CTRL_PARITY(parity)    ((0u != (parity)) ? \
                                                               (SpectroscopySensor_UART_TX_CTRL_PARITY) : (0u))

#define SpectroscopySensor_GET_UART_TX_CTRL_RETRY_NACK(nack)  ((0u != (nack)) ? \
                                                               (SpectroscopySensor_UART_TX_CTRL_RETRY_ON_NACK) : (0u))

/* SpectroscopySensor_UART_FLOW_CTRL */
#if !(SpectroscopySensor_CY_SCBIP_V0 || SpectroscopySensor_CY_SCBIP_V1)
    #define SpectroscopySensor_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(level)   ( (uint32) (level) & \
                                                                 SpectroscopySensor_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK)

    #define SpectroscopySensor_GET_UART_FLOW_CTRL_RTS_POLARITY(polarity) ((0u != (polarity)) ? \
                                                                (SpectroscopySensor_UART_FLOW_CTRL_RTS_POLARITY) : (0u))

    #define SpectroscopySensor_GET_UART_FLOW_CTRL_CTS_POLARITY(polarity) ((0u != (polarity)) ? \
                                                                (SpectroscopySensor_UART_FLOW_CTRL_CTS_POLARITY) : (0u))

    #define SpectroscopySensor_GET_UART_FLOW_CTRL_CTS_ENABLE(ctsEn)      ((0u != (ctsEn)) ? \
                                                                (SpectroscopySensor_UART_FLOW_CTRL_CTS_ENABLE) : (0u))
#endif /* !(SpectroscopySensor_CY_SCBIP_V0 || SpectroscopySensor_CY_SCBIP_V1) */

/* SpectroscopySensor_RX_CTRL */
#define SpectroscopySensor_GET_RX_CTRL_DATA_WIDTH(dataWidth)  (((uint32) (dataWidth) - 1u) & \
                                                                SpectroscopySensor_RX_CTRL_DATA_WIDTH_MASK)

#define SpectroscopySensor_GET_RX_CTRL_BIT_ORDER(bitOrder)    ((0u != (bitOrder)) ? \
                                                                (SpectroscopySensor_RX_CTRL_MSB_FIRST) : (0u))

#define SpectroscopySensor_GET_RX_CTRL_MEDIAN(filterEn)       ((0u != (filterEn)) ? \
                                                                (SpectroscopySensor_RX_CTRL_MEDIAN) : (0u))

/* SpectroscopySensor_RX_MATCH */
#define SpectroscopySensor_GET_RX_MATCH_ADDR(addr)    ((uint32) (addr) & SpectroscopySensor_RX_MATCH_ADDR_MASK)
#define SpectroscopySensor_GET_RX_MATCH_MASK(mask)    (((uint32) (mask) << \
                                                            SpectroscopySensor_RX_MATCH_MASK_POS) & \
                                                            SpectroscopySensor_RX_MATCH_MASK_MASK)

/* SpectroscopySensor_RX_FIFO_CTRL */
#define SpectroscopySensor_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(level)  ((uint32) (level) & \
                                                                    SpectroscopySensor_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK)

/* SpectroscopySensor_TX_CTRL */
#define SpectroscopySensor_GET_TX_CTRL_DATA_WIDTH(dataWidth)  (((uint32) (dataWidth) - 1u) & \
                                                                SpectroscopySensor_TX_CTRL_DATA_WIDTH_MASK)

#define SpectroscopySensor_GET_TX_CTRL_BIT_ORDER(bitOrder)    ((0u != (bitOrder)) ? \
                                                                (SpectroscopySensor_TX_CTRL_MSB_FIRST) : (0u))

/* SpectroscopySensor_TX_FIFO_CTRL */
#define SpectroscopySensor_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(level)  ((uint32) (level) & \
                                                                    SpectroscopySensor_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK)

/* SpectroscopySensor_INTR_SLAVE_I2C_GENERAL */
#define SpectroscopySensor_GET_INTR_SLAVE_I2C_GENERAL(genCall)  ((0u != (genCall)) ? \
                                                                (SpectroscopySensor_INTR_SLAVE_I2C_GENERAL) : (0u))

/* Return true if master mode is enabled SpectroscopySensor_SPI_CTRL_REG */
#define SpectroscopySensor_CHECK_SPI_MASTER   (0u != (SpectroscopySensor_SPI_CTRL_REG & SpectroscopySensor_SPI_CTRL_MASTER))

/* Return inactive state of SPI SCLK line depends on CPOL */
#define SpectroscopySensor_GET_SPI_SCLK_INACTIVE \
            ((0u == (SpectroscopySensor_SPI_CTRL_REG & SpectroscopySensor_SPI_CTRL_CPOL)) ? (0u) : (1u))

/* Get output pin inactive state */
#if (SpectroscopySensor_CY_SCBIP_V0 || SpectroscopySensor_CY_SCBIP_V1)
#define SpectroscopySensor_GET_SPI_SS0_INACTIVE       (1u)
#define SpectroscopySensor_GET_SPI_SS1_INACTIVE       (1u)
#define SpectroscopySensor_GET_SPI_SS2_INACTIVE       (1u)
#define SpectroscopySensor_GET_SPI_SS3_INACTIVE       (1u)
#define SpectroscopySensor_GET_UART_RTS_INACTIVE      (1u)

#else
#define SpectroscopySensor_GET_SPI_SS0_INACTIVE  \
        ((0u != (SpectroscopySensor_SPI_CTRL_REG & SpectroscopySensor_SPI_CTRL_SSEL0_POLARITY)) ? (0u) : (1u))

#define SpectroscopySensor_GET_SPI_SS1_INACTIVE  \
        ((0u != (SpectroscopySensor_SPI_CTRL_REG & SpectroscopySensor_SPI_CTRL_SSEL1_POLARITY)) ? (0u) : (1u))

#define SpectroscopySensor_GET_SPI_SS2_INACTIVE  \
        ((0u != (SpectroscopySensor_SPI_CTRL_REG & SpectroscopySensor_SPI_CTRL_SSEL2_POLARITY)) ? (0u) : (1u))

#define SpectroscopySensor_GET_SPI_SS3_INACTIVE  \
        ((0u != (SpectroscopySensor_SPI_CTRL_REG & SpectroscopySensor_SPI_CTRL_SSEL3_POLARITY)) ? (0u) : (1u))

#define SpectroscopySensor_GET_UART_RTS_INACTIVE \
        ((0u == (SpectroscopySensor_UART_FLOW_CTRL_REG & SpectroscopySensor_UART_FLOW_CTRL_RTS_POLARITY)) ? (0u) : (1u))

#endif /*(SpectroscopySensor_CY_SCBIP_V0 || SpectroscopySensor_CY_SCBIP_V1) */

/* Clear register constants for configuration and interrupt mask */
#define SpectroscopySensor_CLEAR_REG          ((uint32) (0u))
#define SpectroscopySensor_NO_INTR_SOURCES    ((uint32) (0u))
#define SpectroscopySensor_DUMMY_PARAM        ((uint32) (0u))
#define SpectroscopySensor_SUBMODE_SPI_SLAVE  ((uint32) (0u))

/* Return in case of I2C read error */
#define SpectroscopySensor_I2C_INVALID_BYTE   ((uint32) 0xFFFFFFFFu)
#define SpectroscopySensor_CHECK_VALID_BYTE   ((uint32) 0x80000000u)


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

#define SpectroscopySensor_CHECK_INTR_EC_I2C(sourceMask)  SpectroscopySensor_CHECK_INTR_I2C_EC(sourceMask)
#if (!SpectroscopySensor_CY_SCBIP_V1)
    #define SpectroscopySensor_CHECK_INTR_EC_SPI(sourceMask)  SpectroscopySensor_CHECK_INTR_SPI_EC(sourceMask)
#endif /* (!SpectroscopySensor_CY_SCBIP_V1) */

#define SpectroscopySensor_CY_SCBIP_V1_I2C_ONLY   (SpectroscopySensor_CY_SCBIP_V1)
#define SpectroscopySensor_EZBUFFER_SIZE          (SpectroscopySensor_EZ_DATA_NR)

#define SpectroscopySensor_EZBUF_DATA00_REG   SpectroscopySensor_EZBUF_DATA0_REG
#define SpectroscopySensor_EZBUF_DATA00_PTR   SpectroscopySensor_EZBUF_DATA0_PTR

#endif /* (CY_SCB_SpectroscopySensor_H) */


/* [] END OF FILE */
