/***************************************************************************//**
* \file SpectroscopySensor.c
* \version 4.0
*
* \brief
*  This file provides the source code to the API for the SCB Component.
*
* Note:
*
*******************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "SpectroscopySensor_PVT.h"

#if (SpectroscopySensor_SCB_MODE_I2C_INC)
    #include "SpectroscopySensor_I2C_PVT.h"
#endif /* (SpectroscopySensor_SCB_MODE_I2C_INC) */

#if (SpectroscopySensor_SCB_MODE_EZI2C_INC)
    #include "SpectroscopySensor_EZI2C_PVT.h"
#endif /* (SpectroscopySensor_SCB_MODE_EZI2C_INC) */

#if (SpectroscopySensor_SCB_MODE_SPI_INC || SpectroscopySensor_SCB_MODE_UART_INC)
    #include "SpectroscopySensor_SPI_UART_PVT.h"
#endif /* (SpectroscopySensor_SCB_MODE_SPI_INC || SpectroscopySensor_SCB_MODE_UART_INC) */


/***************************************
*    Run Time Configuration Vars
***************************************/

/* Stores internal component configuration for Unconfigured mode */
#if (SpectroscopySensor_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    uint8 SpectroscopySensor_scbMode = SpectroscopySensor_SCB_MODE_UNCONFIG;
    uint8 SpectroscopySensor_scbEnableWake;
    uint8 SpectroscopySensor_scbEnableIntr;

    /* I2C configuration variables */
    uint8 SpectroscopySensor_mode;
    uint8 SpectroscopySensor_acceptAddr;

    /* SPI/UART configuration variables */
    volatile uint8 * SpectroscopySensor_rxBuffer;
    uint8  SpectroscopySensor_rxDataBits;
    uint32 SpectroscopySensor_rxBufferSize;

    volatile uint8 * SpectroscopySensor_txBuffer;
    uint8  SpectroscopySensor_txDataBits;
    uint32 SpectroscopySensor_txBufferSize;

    /* EZI2C configuration variables */
    uint8 SpectroscopySensor_numberOfAddr;
    uint8 SpectroscopySensor_subAddrSize;
#endif /* (SpectroscopySensor_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Common SCB Vars
***************************************/
/**
* \addtogroup group_general
* \{
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
uint8 SpectroscopySensor_initVar = 0u;


#if (! (SpectroscopySensor_SCB_MODE_I2C_CONST_CFG || \
        SpectroscopySensor_SCB_MODE_EZI2C_CONST_CFG))
    /** This global variable stores TX interrupt sources after 
    * SpectroscopySensor_Stop() is called. Only these TX interrupt sources 
    * will be restored on a subsequent SpectroscopySensor_Enable() call.
    */
    uint16 SpectroscopySensor_IntrTxMask = 0u;
#endif /* (! (SpectroscopySensor_SCB_MODE_I2C_CONST_CFG || \
              SpectroscopySensor_SCB_MODE_EZI2C_CONST_CFG)) */
/** \} globals */

#if (SpectroscopySensor_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_SpectroscopySensor_CUSTOM_INTR_HANDLER)
    void (*SpectroscopySensor_customIntrHandler)(void) = NULL;
#endif /* !defined (CY_REMOVE_SpectroscopySensor_CUSTOM_INTR_HANDLER) */
#endif /* (SpectroscopySensor_SCB_IRQ_INTERNAL) */


/***************************************
*    Private Function Prototypes
***************************************/

static void SpectroscopySensor_ScbEnableIntr(void);
static void SpectroscopySensor_ScbModeStop(void);
static void SpectroscopySensor_ScbModePostEnable(void);


/*******************************************************************************
* Function Name: SpectroscopySensor_Init
****************************************************************************//**
*
*  Initializes the SpectroscopySensor component to operate in one of the selected
*  configurations: I2C, SPI, UART or EZI2C.
*  When the configuration is set to "Unconfigured SCB", this function does
*  not do any initialization. Use mode-specific initialization APIs instead:
*  SpectroscopySensor_I2CInit, SpectroscopySensor_SpiInit, 
*  SpectroscopySensor_UartInit or SpectroscopySensor_EzI2CInit.
*
*******************************************************************************/
void SpectroscopySensor_Init(void)
{
#if (SpectroscopySensor_SCB_MODE_UNCONFIG_CONST_CFG)
    if (SpectroscopySensor_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        SpectroscopySensor_initVar = 0u;
    }
    else
    {
        /* Initialization was done before this function call */
    }

#elif (SpectroscopySensor_SCB_MODE_I2C_CONST_CFG)
    SpectroscopySensor_I2CInit();

#elif (SpectroscopySensor_SCB_MODE_SPI_CONST_CFG)
    SpectroscopySensor_SpiInit();

#elif (SpectroscopySensor_SCB_MODE_UART_CONST_CFG)
    SpectroscopySensor_UartInit();

#elif (SpectroscopySensor_SCB_MODE_EZI2C_CONST_CFG)
    SpectroscopySensor_EzI2CInit();

#endif /* (SpectroscopySensor_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: SpectroscopySensor_Enable
****************************************************************************//**
*
*  Enables SpectroscopySensor component operation: activates the hardware and 
*  internal interrupt. It also restores TX interrupt sources disabled after the 
*  SpectroscopySensor_Stop() function was called (note that level-triggered TX 
*  interrupt sources remain disabled to not cause code lock-up).
*  For I2C and EZI2C modes the interrupt is internal and mandatory for 
*  operation. For SPI and UART modes the interrupt can be configured as none, 
*  internal or external.
*  The SpectroscopySensor configuration should be not changed when the component
*  is enabled. Any configuration changes should be made after disabling the 
*  component.
*  When configuration is set to “Unconfigured SpectroscopySensor”, the component 
*  must first be initialized to operate in one of the following configurations: 
*  I2C, SPI, UART or EZ I2C, using the mode-specific initialization API. 
*  Otherwise this function does not enable the component.
*
*******************************************************************************/
void SpectroscopySensor_Enable(void)
{
#if (SpectroscopySensor_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Enable SCB block, only if it is already configured */
    if (!SpectroscopySensor_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        SpectroscopySensor_CTRL_REG |= SpectroscopySensor_CTRL_ENABLED;

        SpectroscopySensor_ScbEnableIntr();

        /* Call PostEnable function specific to current operation mode */
        SpectroscopySensor_ScbModePostEnable();
    }
#else
    SpectroscopySensor_CTRL_REG |= SpectroscopySensor_CTRL_ENABLED;

    SpectroscopySensor_ScbEnableIntr();

    /* Call PostEnable function specific to current operation mode */
    SpectroscopySensor_ScbModePostEnable();
#endif /* (SpectroscopySensor_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: SpectroscopySensor_Start
****************************************************************************//**
*
*  Invokes SpectroscopySensor_Init() and SpectroscopySensor_Enable().
*  After this function call, the component is enabled and ready for operation.
*  When configuration is set to "Unconfigured SCB", the component must first be
*  initialized to operate in one of the following configurations: I2C, SPI, UART
*  or EZI2C. Otherwise this function does not enable the component.
*
* \globalvars
*  SpectroscopySensor_initVar - used to check initial configuration, modified
*  on first function call.
*
*******************************************************************************/
void SpectroscopySensor_Start(void)
{
    if (0u == SpectroscopySensor_initVar)
    {
        SpectroscopySensor_Init();
        SpectroscopySensor_initVar = 1u; /* Component was initialized */
    }

    SpectroscopySensor_Enable();
}


/*******************************************************************************
* Function Name: SpectroscopySensor_Stop
****************************************************************************//**
*
*  Disables the SpectroscopySensor component: disable the hardware and internal 
*  interrupt. It also disables all TX interrupt sources so as not to cause an 
*  unexpected interrupt trigger because after the component is enabled, the 
*  TX FIFO is empty.
*  Refer to the function SpectroscopySensor_Enable() for the interrupt 
*  configuration details.
*  This function disables the SCB component without checking to see if 
*  communication is in progress. Before calling this function it may be 
*  necessary to check the status of communication to make sure communication 
*  is complete. If this is not done then communication could be stopped mid 
*  byte and corrupted data could result.
*
*******************************************************************************/
void SpectroscopySensor_Stop(void)
{
#if (SpectroscopySensor_SCB_IRQ_INTERNAL)
    SpectroscopySensor_DisableInt();
#endif /* (SpectroscopySensor_SCB_IRQ_INTERNAL) */

    /* Call Stop function specific to current operation mode */
    SpectroscopySensor_ScbModeStop();

    /* Disable SCB IP */
    SpectroscopySensor_CTRL_REG &= (uint32) ~SpectroscopySensor_CTRL_ENABLED;

    /* Disable all TX interrupt sources so as not to cause an unexpected
    * interrupt trigger after the component will be enabled because the 
    * TX FIFO is empty.
    * For SCB IP v0, it is critical as it does not mask-out interrupt
    * sources when it is disabled. This can cause a code lock-up in the
    * interrupt handler because TX FIFO cannot be loaded after the block
    * is disabled.
    */
    SpectroscopySensor_SetTxInterruptMode(SpectroscopySensor_NO_INTR_SOURCES);

#if (SpectroscopySensor_SCB_IRQ_INTERNAL)
    SpectroscopySensor_ClearPendingInt();
#endif /* (SpectroscopySensor_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: SpectroscopySensor_SetRxFifoLevel
****************************************************************************//**
*
*  Sets level in the RX FIFO to generate a RX level interrupt.
*  When the RX FIFO has more entries than the RX FIFO level an RX level
*  interrupt request is generated.
*
*  \param level: Level in the RX FIFO to generate RX level interrupt.
*   The range of valid level values is between 0 and RX FIFO depth - 1.
*
*******************************************************************************/
void SpectroscopySensor_SetRxFifoLevel(uint32 level)
{
    uint32 rxFifoCtrl;

    rxFifoCtrl = SpectroscopySensor_RX_FIFO_CTRL_REG;

    rxFifoCtrl &= ((uint32) ~SpectroscopySensor_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    rxFifoCtrl |= ((uint32) (SpectroscopySensor_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    SpectroscopySensor_RX_FIFO_CTRL_REG = rxFifoCtrl;
}


/*******************************************************************************
* Function Name: SpectroscopySensor_SetTxFifoLevel
****************************************************************************//**
*
*  Sets level in the TX FIFO to generate a TX level interrupt.
*  When the TX FIFO has less entries than the TX FIFO level an TX level
*  interrupt request is generated.
*
*  \param level: Level in the TX FIFO to generate TX level interrupt.
*   The range of valid level values is between 0 and TX FIFO depth - 1.
*
*******************************************************************************/
void SpectroscopySensor_SetTxFifoLevel(uint32 level)
{
    uint32 txFifoCtrl;

    txFifoCtrl = SpectroscopySensor_TX_FIFO_CTRL_REG;

    txFifoCtrl &= ((uint32) ~SpectroscopySensor_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    txFifoCtrl |= ((uint32) (SpectroscopySensor_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    SpectroscopySensor_TX_FIFO_CTRL_REG = txFifoCtrl;
}


#if (SpectroscopySensor_SCB_IRQ_INTERNAL)
    /*******************************************************************************
    * Function Name: SpectroscopySensor_SetCustomInterruptHandler
    ****************************************************************************//**
    *
    *  Registers a function to be called by the internal interrupt handler.
    *  First the function that is registered is called, then the internal interrupt
    *  handler performs any operation such as software buffer management functions
    *  before the interrupt returns.  It is the user's responsibility not to break
    *  the software buffer operations. Only one custom handler is supported, which
    *  is the function provided by the most recent call.
    *  At the initialization time no custom handler is registered.
    *
    *  \param func: Pointer to the function to register.
    *        The value NULL indicates to remove the current custom interrupt
    *        handler.
    *
    *******************************************************************************/
    void SpectroscopySensor_SetCustomInterruptHandler(void (*func)(void))
    {
    #if !defined (CY_REMOVE_SpectroscopySensor_CUSTOM_INTR_HANDLER)
        SpectroscopySensor_customIntrHandler = func; /* Register interrupt handler */
    #else
        if (NULL != func)
        {
            /* Suppress compiler warning */
        }
    #endif /* !defined (CY_REMOVE_SpectroscopySensor_CUSTOM_INTR_HANDLER) */
    }
#endif /* (SpectroscopySensor_SCB_IRQ_INTERNAL) */


/*******************************************************************************
* Function Name: SpectroscopySensor_ScbModeEnableIntr
****************************************************************************//**
*
*  Enables an interrupt for a specific mode.
*
*******************************************************************************/
static void SpectroscopySensor_ScbEnableIntr(void)
{
#if (SpectroscopySensor_SCB_IRQ_INTERNAL)
    /* Enable interrupt in NVIC */
    #if (SpectroscopySensor_SCB_MODE_UNCONFIG_CONST_CFG)
        if (0u != SpectroscopySensor_scbEnableIntr)
        {
            SpectroscopySensor_EnableInt();
        }

    #else
        SpectroscopySensor_EnableInt();

    #endif /* (SpectroscopySensor_SCB_MODE_UNCONFIG_CONST_CFG) */
#endif /* (SpectroscopySensor_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: SpectroscopySensor_ScbModePostEnable
****************************************************************************//**
*
*  Calls the PostEnable function for a specific operation mode.
*
*******************************************************************************/
static void SpectroscopySensor_ScbModePostEnable(void)
{
#if (SpectroscopySensor_SCB_MODE_UNCONFIG_CONST_CFG)
#if (!SpectroscopySensor_CY_SCBIP_V1)
    if (SpectroscopySensor_SCB_MODE_SPI_RUNTM_CFG)
    {
        SpectroscopySensor_SpiPostEnable();
    }
    else if (SpectroscopySensor_SCB_MODE_UART_RUNTM_CFG)
    {
        SpectroscopySensor_UartPostEnable();
    }
    else
    {
        /* Unknown mode: do nothing */
    }
#endif /* (!SpectroscopySensor_CY_SCBIP_V1) */

#elif (SpectroscopySensor_SCB_MODE_SPI_CONST_CFG)
    SpectroscopySensor_SpiPostEnable();

#elif (SpectroscopySensor_SCB_MODE_UART_CONST_CFG)
    SpectroscopySensor_UartPostEnable();

#else
    /* Unknown mode: do nothing */
#endif /* (SpectroscopySensor_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: SpectroscopySensor_ScbModeStop
****************************************************************************//**
*
*  Calls the Stop function for a specific operation mode.
*
*******************************************************************************/
static void SpectroscopySensor_ScbModeStop(void)
{
#if (SpectroscopySensor_SCB_MODE_UNCONFIG_CONST_CFG)
    if (SpectroscopySensor_SCB_MODE_I2C_RUNTM_CFG)
    {
        SpectroscopySensor_I2CStop();
    }
    else if (SpectroscopySensor_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        SpectroscopySensor_EzI2CStop();
    }
#if (!SpectroscopySensor_CY_SCBIP_V1)
    else if (SpectroscopySensor_SCB_MODE_SPI_RUNTM_CFG)
    {
        SpectroscopySensor_SpiStop();
    }
    else if (SpectroscopySensor_SCB_MODE_UART_RUNTM_CFG)
    {
        SpectroscopySensor_UartStop();
    }
#endif /* (!SpectroscopySensor_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
#elif (SpectroscopySensor_SCB_MODE_I2C_CONST_CFG)
    SpectroscopySensor_I2CStop();

#elif (SpectroscopySensor_SCB_MODE_EZI2C_CONST_CFG)
    SpectroscopySensor_EzI2CStop();

#elif (SpectroscopySensor_SCB_MODE_SPI_CONST_CFG)
    SpectroscopySensor_SpiStop();

#elif (SpectroscopySensor_SCB_MODE_UART_CONST_CFG)
    SpectroscopySensor_UartStop();

#else
    /* Unknown mode: do nothing */
#endif /* (SpectroscopySensor_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if (SpectroscopySensor_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: SpectroscopySensor_SetPins
    ****************************************************************************//**
    *
    *  Sets the pins settings accordingly to the selected operation mode.
    *  Only available in the Unconfigured operation mode. The mode specific
    *  initialization function calls it.
    *  Pins configuration is set by PSoC Creator when a specific mode of operation
    *  is selected in design time.
    *
    *  \param mode:      Mode of SCB operation.
    *  \param subMode:   Sub-mode of SCB operation. It is only required for SPI and UART
    *             modes.
    *  \param uartEnableMask: enables TX or RX direction and RTS and CTS signals.
    *
    *******************************************************************************/
    void SpectroscopySensor_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask)
    {
        uint32 pinsDm[SpectroscopySensor_SCB_PINS_NUMBER];
        uint32 i;
        
    #if (!SpectroscopySensor_CY_SCBIP_V1)
        uint32 pinsInBuf = 0u;
    #endif /* (!SpectroscopySensor_CY_SCBIP_V1) */
        
        uint32 hsiomSel[SpectroscopySensor_SCB_PINS_NUMBER] = 
        {
            SpectroscopySensor_RX_SCL_MOSI_HSIOM_SEL_GPIO,
            SpectroscopySensor_TX_SDA_MISO_HSIOM_SEL_GPIO,
            0u,
            0u,
            0u,
            0u,
            0u,
        };

    #if (SpectroscopySensor_CY_SCBIP_V1)
        /* Supress compiler warning. */
        if ((0u == subMode) || (0u == uartEnableMask))
        {
        }
    #endif /* (SpectroscopySensor_CY_SCBIP_V1) */

        /* Set default HSIOM to GPIO and Drive Mode to Analog Hi-Z */
        for (i = 0u; i < SpectroscopySensor_SCB_PINS_NUMBER; i++)
        {
            pinsDm[i] = SpectroscopySensor_PIN_DM_ALG_HIZ;
        }

        if ((SpectroscopySensor_SCB_MODE_I2C   == mode) ||
            (SpectroscopySensor_SCB_MODE_EZI2C == mode))
        {
        #if (SpectroscopySensor_RX_SCL_MOSI_PIN)
            hsiomSel[SpectroscopySensor_RX_SCL_MOSI_PIN_INDEX] = SpectroscopySensor_RX_SCL_MOSI_HSIOM_SEL_I2C;
            pinsDm  [SpectroscopySensor_RX_SCL_MOSI_PIN_INDEX] = SpectroscopySensor_PIN_DM_OD_LO;
        #elif (SpectroscopySensor_RX_WAKE_SCL_MOSI_PIN)
            hsiomSel[SpectroscopySensor_RX_WAKE_SCL_MOSI_PIN_INDEX] = SpectroscopySensor_RX_WAKE_SCL_MOSI_HSIOM_SEL_I2C;
            pinsDm  [SpectroscopySensor_RX_WAKE_SCL_MOSI_PIN_INDEX] = SpectroscopySensor_PIN_DM_OD_LO;
        #else
        #endif /* (SpectroscopySensor_RX_SCL_MOSI_PIN) */
        
        #if (SpectroscopySensor_TX_SDA_MISO_PIN)
            hsiomSel[SpectroscopySensor_TX_SDA_MISO_PIN_INDEX] = SpectroscopySensor_TX_SDA_MISO_HSIOM_SEL_I2C;
            pinsDm  [SpectroscopySensor_TX_SDA_MISO_PIN_INDEX] = SpectroscopySensor_PIN_DM_OD_LO;
        #endif /* (SpectroscopySensor_TX_SDA_MISO_PIN) */
        }
    #if (!SpectroscopySensor_CY_SCBIP_V1)
        else if (SpectroscopySensor_SCB_MODE_SPI == mode)
        {
        #if (SpectroscopySensor_RX_SCL_MOSI_PIN)
            hsiomSel[SpectroscopySensor_RX_SCL_MOSI_PIN_INDEX] = SpectroscopySensor_RX_SCL_MOSI_HSIOM_SEL_SPI;
        #elif (SpectroscopySensor_RX_WAKE_SCL_MOSI_PIN)
            hsiomSel[SpectroscopySensor_RX_WAKE_SCL_MOSI_PIN_INDEX] = SpectroscopySensor_RX_WAKE_SCL_MOSI_HSIOM_SEL_SPI;
        #else
        #endif /* (SpectroscopySensor_RX_SCL_MOSI_PIN) */
        
        #if (SpectroscopySensor_TX_SDA_MISO_PIN)
            hsiomSel[SpectroscopySensor_TX_SDA_MISO_PIN_INDEX] = SpectroscopySensor_TX_SDA_MISO_HSIOM_SEL_SPI;
        #endif /* (SpectroscopySensor_TX_SDA_MISO_PIN) */
        
        #if (SpectroscopySensor_CTS_SCLK_PIN)
            hsiomSel[SpectroscopySensor_CTS_SCLK_PIN_INDEX] = SpectroscopySensor_CTS_SCLK_HSIOM_SEL_SPI;
        #endif /* (SpectroscopySensor_CTS_SCLK_PIN) */

            if (SpectroscopySensor_SPI_SLAVE == subMode)
            {
                /* Slave */
                pinsDm[SpectroscopySensor_RX_SCL_MOSI_PIN_INDEX] = SpectroscopySensor_PIN_DM_DIG_HIZ;
                pinsDm[SpectroscopySensor_TX_SDA_MISO_PIN_INDEX] = SpectroscopySensor_PIN_DM_STRONG;
                pinsDm[SpectroscopySensor_CTS_SCLK_PIN_INDEX] = SpectroscopySensor_PIN_DM_DIG_HIZ;

            #if (SpectroscopySensor_RTS_SS0_PIN)
                /* Only SS0 is valid choice for Slave */
                hsiomSel[SpectroscopySensor_RTS_SS0_PIN_INDEX] = SpectroscopySensor_RTS_SS0_HSIOM_SEL_SPI;
                pinsDm  [SpectroscopySensor_RTS_SS0_PIN_INDEX] = SpectroscopySensor_PIN_DM_DIG_HIZ;
            #endif /* (SpectroscopySensor_RTS_SS0_PIN) */

            #if (SpectroscopySensor_TX_SDA_MISO_PIN)
                /* Disable input buffer */
                 pinsInBuf |= SpectroscopySensor_TX_SDA_MISO_PIN_MASK;
            #endif /* (SpectroscopySensor_TX_SDA_MISO_PIN) */
            }
            else 
            {
                /* (Master) */
                pinsDm[SpectroscopySensor_RX_SCL_MOSI_PIN_INDEX] = SpectroscopySensor_PIN_DM_STRONG;
                pinsDm[SpectroscopySensor_TX_SDA_MISO_PIN_INDEX] = SpectroscopySensor_PIN_DM_DIG_HIZ;
                pinsDm[SpectroscopySensor_CTS_SCLK_PIN_INDEX] = SpectroscopySensor_PIN_DM_STRONG;

            #if (SpectroscopySensor_RTS_SS0_PIN)
                hsiomSel [SpectroscopySensor_RTS_SS0_PIN_INDEX] = SpectroscopySensor_RTS_SS0_HSIOM_SEL_SPI;
                pinsDm   [SpectroscopySensor_RTS_SS0_PIN_INDEX] = SpectroscopySensor_PIN_DM_STRONG;
                pinsInBuf |= SpectroscopySensor_RTS_SS0_PIN_MASK;
            #endif /* (SpectroscopySensor_RTS_SS0_PIN) */

            #if (SpectroscopySensor_SS1_PIN)
                hsiomSel [SpectroscopySensor_SS1_PIN_INDEX] = SpectroscopySensor_SS1_HSIOM_SEL_SPI;
                pinsDm   [SpectroscopySensor_SS1_PIN_INDEX] = SpectroscopySensor_PIN_DM_STRONG;
                pinsInBuf |= SpectroscopySensor_SS1_PIN_MASK;
            #endif /* (SpectroscopySensor_SS1_PIN) */

            #if (SpectroscopySensor_SS2_PIN)
                hsiomSel [SpectroscopySensor_SS2_PIN_INDEX] = SpectroscopySensor_SS2_HSIOM_SEL_SPI;
                pinsDm   [SpectroscopySensor_SS2_PIN_INDEX] = SpectroscopySensor_PIN_DM_STRONG;
                pinsInBuf |= SpectroscopySensor_SS2_PIN_MASK;
            #endif /* (SpectroscopySensor_SS2_PIN) */

            #if (SpectroscopySensor_SS3_PIN)
                hsiomSel [SpectroscopySensor_SS3_PIN_INDEX] = SpectroscopySensor_SS3_HSIOM_SEL_SPI;
                pinsDm   [SpectroscopySensor_SS3_PIN_INDEX] = SpectroscopySensor_PIN_DM_STRONG;
                pinsInBuf |= SpectroscopySensor_SS3_PIN_MASK;
            #endif /* (SpectroscopySensor_SS3_PIN) */

                /* Disable input buffers */
            #if (SpectroscopySensor_RX_SCL_MOSI_PIN)
                pinsInBuf |= SpectroscopySensor_RX_SCL_MOSI_PIN_MASK;
            #elif (SpectroscopySensor_RX_WAKE_SCL_MOSI_PIN)
                pinsInBuf |= SpectroscopySensor_RX_WAKE_SCL_MOSI_PIN_MASK;
            #else
            #endif /* (SpectroscopySensor_RX_SCL_MOSI_PIN) */

            #if (SpectroscopySensor_CTS_SCLK_PIN)
                pinsInBuf |= SpectroscopySensor_CTS_SCLK_PIN_MASK;
            #endif /* (SpectroscopySensor_CTS_SCLK_PIN) */
            }
        }
        else /* UART */
        {
            if (SpectroscopySensor_UART_MODE_SMARTCARD == subMode)
            {
                /* SmartCard */
            #if (SpectroscopySensor_TX_SDA_MISO_PIN)
                hsiomSel[SpectroscopySensor_TX_SDA_MISO_PIN_INDEX] = SpectroscopySensor_TX_SDA_MISO_HSIOM_SEL_UART;
                pinsDm  [SpectroscopySensor_TX_SDA_MISO_PIN_INDEX] = SpectroscopySensor_PIN_DM_OD_LO;
            #endif /* (SpectroscopySensor_TX_SDA_MISO_PIN) */
            }
            else /* Standard or IrDA */
            {
                if (0u != (SpectroscopySensor_UART_RX_PIN_ENABLE & uartEnableMask))
                {
                #if (SpectroscopySensor_RX_SCL_MOSI_PIN)
                    hsiomSel[SpectroscopySensor_RX_SCL_MOSI_PIN_INDEX] = SpectroscopySensor_RX_SCL_MOSI_HSIOM_SEL_UART;
                    pinsDm  [SpectroscopySensor_RX_SCL_MOSI_PIN_INDEX] = SpectroscopySensor_PIN_DM_DIG_HIZ;
                #elif (SpectroscopySensor_RX_WAKE_SCL_MOSI_PIN)
                    hsiomSel[SpectroscopySensor_RX_WAKE_SCL_MOSI_PIN_INDEX] = SpectroscopySensor_RX_WAKE_SCL_MOSI_HSIOM_SEL_UART;
                    pinsDm  [SpectroscopySensor_RX_WAKE_SCL_MOSI_PIN_INDEX] = SpectroscopySensor_PIN_DM_DIG_HIZ;
                #else
                #endif /* (SpectroscopySensor_RX_SCL_MOSI_PIN) */
                }

                if (0u != (SpectroscopySensor_UART_TX_PIN_ENABLE & uartEnableMask))
                {
                #if (SpectroscopySensor_TX_SDA_MISO_PIN)
                    hsiomSel[SpectroscopySensor_TX_SDA_MISO_PIN_INDEX] = SpectroscopySensor_TX_SDA_MISO_HSIOM_SEL_UART;
                    pinsDm  [SpectroscopySensor_TX_SDA_MISO_PIN_INDEX] = SpectroscopySensor_PIN_DM_STRONG;
                    
                    /* Disable input buffer */
                    pinsInBuf |= SpectroscopySensor_TX_SDA_MISO_PIN_MASK;
                #endif /* (SpectroscopySensor_TX_SDA_MISO_PIN) */
                }

            #if !(SpectroscopySensor_CY_SCBIP_V0 || SpectroscopySensor_CY_SCBIP_V1)
                if (SpectroscopySensor_UART_MODE_STD == subMode)
                {
                    if (0u != (SpectroscopySensor_UART_CTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* CTS input is multiplexed with SCLK */
                    #if (SpectroscopySensor_CTS_SCLK_PIN)
                        hsiomSel[SpectroscopySensor_CTS_SCLK_PIN_INDEX] = SpectroscopySensor_CTS_SCLK_HSIOM_SEL_UART;
                        pinsDm  [SpectroscopySensor_CTS_SCLK_PIN_INDEX] = SpectroscopySensor_PIN_DM_DIG_HIZ;
                    #endif /* (SpectroscopySensor_CTS_SCLK_PIN) */
                    }

                    if (0u != (SpectroscopySensor_UART_RTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* RTS output is multiplexed with SS0 */
                    #if (SpectroscopySensor_RTS_SS0_PIN)
                        hsiomSel[SpectroscopySensor_RTS_SS0_PIN_INDEX] = SpectroscopySensor_RTS_SS0_HSIOM_SEL_UART;
                        pinsDm  [SpectroscopySensor_RTS_SS0_PIN_INDEX] = SpectroscopySensor_PIN_DM_STRONG;
                        
                        /* Disable input buffer */
                        pinsInBuf |= SpectroscopySensor_RTS_SS0_PIN_MASK;
                    #endif /* (SpectroscopySensor_RTS_SS0_PIN) */
                    }
                }
            #endif /* !(SpectroscopySensor_CY_SCBIP_V0 || SpectroscopySensor_CY_SCBIP_V1) */
            }
        }
    #endif /* (!SpectroscopySensor_CY_SCBIP_V1) */

    /* Configure pins: set HSIOM, DM and InputBufEnable */
    /* Note: the DR register settings do not effect the pin output if HSIOM is other than GPIO */

    #if (SpectroscopySensor_RX_SCL_MOSI_PIN)
        SpectroscopySensor_SET_HSIOM_SEL(SpectroscopySensor_RX_SCL_MOSI_HSIOM_REG,
                                       SpectroscopySensor_RX_SCL_MOSI_HSIOM_MASK,
                                       SpectroscopySensor_RX_SCL_MOSI_HSIOM_POS,
                                        hsiomSel[SpectroscopySensor_RX_SCL_MOSI_PIN_INDEX]);

        SpectroscopySensor_uart_rx_i2c_scl_spi_mosi_SetDriveMode((uint8) pinsDm[SpectroscopySensor_RX_SCL_MOSI_PIN_INDEX]);

        #if (!SpectroscopySensor_CY_SCBIP_V1)
            SpectroscopySensor_SET_INP_DIS(SpectroscopySensor_uart_rx_i2c_scl_spi_mosi_INP_DIS,
                                         SpectroscopySensor_uart_rx_i2c_scl_spi_mosi_MASK,
                                         (0u != (pinsInBuf & SpectroscopySensor_RX_SCL_MOSI_PIN_MASK)));
        #endif /* (!SpectroscopySensor_CY_SCBIP_V1) */
    
    #elif (SpectroscopySensor_RX_WAKE_SCL_MOSI_PIN)
        SpectroscopySensor_SET_HSIOM_SEL(SpectroscopySensor_RX_WAKE_SCL_MOSI_HSIOM_REG,
                                       SpectroscopySensor_RX_WAKE_SCL_MOSI_HSIOM_MASK,
                                       SpectroscopySensor_RX_WAKE_SCL_MOSI_HSIOM_POS,
                                       hsiomSel[SpectroscopySensor_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        SpectroscopySensor_uart_rx_wake_i2c_scl_spi_mosi_SetDriveMode((uint8)
                                                               pinsDm[SpectroscopySensor_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        SpectroscopySensor_SET_INP_DIS(SpectroscopySensor_uart_rx_wake_i2c_scl_spi_mosi_INP_DIS,
                                     SpectroscopySensor_uart_rx_wake_i2c_scl_spi_mosi_MASK,
                                     (0u != (pinsInBuf & SpectroscopySensor_RX_WAKE_SCL_MOSI_PIN_MASK)));

         /* Set interrupt on falling edge */
        SpectroscopySensor_SET_INCFG_TYPE(SpectroscopySensor_RX_WAKE_SCL_MOSI_INTCFG_REG,
                                        SpectroscopySensor_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK,
                                        SpectroscopySensor_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS,
                                        SpectroscopySensor_INTCFG_TYPE_FALLING_EDGE);
    #else
    #endif /* (SpectroscopySensor_RX_WAKE_SCL_MOSI_PIN) */

    #if (SpectroscopySensor_TX_SDA_MISO_PIN)
        SpectroscopySensor_SET_HSIOM_SEL(SpectroscopySensor_TX_SDA_MISO_HSIOM_REG,
                                       SpectroscopySensor_TX_SDA_MISO_HSIOM_MASK,
                                       SpectroscopySensor_TX_SDA_MISO_HSIOM_POS,
                                        hsiomSel[SpectroscopySensor_TX_SDA_MISO_PIN_INDEX]);

        SpectroscopySensor_uart_tx_i2c_sda_spi_miso_SetDriveMode((uint8) pinsDm[SpectroscopySensor_TX_SDA_MISO_PIN_INDEX]);

    #if (!SpectroscopySensor_CY_SCBIP_V1)
        SpectroscopySensor_SET_INP_DIS(SpectroscopySensor_uart_tx_i2c_sda_spi_miso_INP_DIS,
                                     SpectroscopySensor_uart_tx_i2c_sda_spi_miso_MASK,
                                    (0u != (pinsInBuf & SpectroscopySensor_TX_SDA_MISO_PIN_MASK)));
    #endif /* (!SpectroscopySensor_CY_SCBIP_V1) */
    #endif /* (SpectroscopySensor_RX_SCL_MOSI_PIN) */

    #if (SpectroscopySensor_CTS_SCLK_PIN)
        SpectroscopySensor_SET_HSIOM_SEL(SpectroscopySensor_CTS_SCLK_HSIOM_REG,
                                       SpectroscopySensor_CTS_SCLK_HSIOM_MASK,
                                       SpectroscopySensor_CTS_SCLK_HSIOM_POS,
                                       hsiomSel[SpectroscopySensor_CTS_SCLK_PIN_INDEX]);

        SpectroscopySensor_uart_cts_spi_sclk_SetDriveMode((uint8) pinsDm[SpectroscopySensor_CTS_SCLK_PIN_INDEX]);

        SpectroscopySensor_SET_INP_DIS(SpectroscopySensor_uart_cts_spi_sclk_INP_DIS,
                                     SpectroscopySensor_uart_cts_spi_sclk_MASK,
                                     (0u != (pinsInBuf & SpectroscopySensor_CTS_SCLK_PIN_MASK)));
    #endif /* (SpectroscopySensor_CTS_SCLK_PIN) */

    #if (SpectroscopySensor_RTS_SS0_PIN)
        SpectroscopySensor_SET_HSIOM_SEL(SpectroscopySensor_RTS_SS0_HSIOM_REG,
                                       SpectroscopySensor_RTS_SS0_HSIOM_MASK,
                                       SpectroscopySensor_RTS_SS0_HSIOM_POS,
                                       hsiomSel[SpectroscopySensor_RTS_SS0_PIN_INDEX]);

        SpectroscopySensor_uart_rts_spi_ss0_SetDriveMode((uint8) pinsDm[SpectroscopySensor_RTS_SS0_PIN_INDEX]);

        SpectroscopySensor_SET_INP_DIS(SpectroscopySensor_uart_rts_spi_ss0_INP_DIS,
                                     SpectroscopySensor_uart_rts_spi_ss0_MASK,
                                     (0u != (pinsInBuf & SpectroscopySensor_RTS_SS0_PIN_MASK)));
    #endif /* (SpectroscopySensor_RTS_SS0_PIN) */

    #if (SpectroscopySensor_SS1_PIN)
        SpectroscopySensor_SET_HSIOM_SEL(SpectroscopySensor_SS1_HSIOM_REG,
                                       SpectroscopySensor_SS1_HSIOM_MASK,
                                       SpectroscopySensor_SS1_HSIOM_POS,
                                       hsiomSel[SpectroscopySensor_SS1_PIN_INDEX]);

        SpectroscopySensor_spi_ss1_SetDriveMode((uint8) pinsDm[SpectroscopySensor_SS1_PIN_INDEX]);

        SpectroscopySensor_SET_INP_DIS(SpectroscopySensor_spi_ss1_INP_DIS,
                                     SpectroscopySensor_spi_ss1_MASK,
                                     (0u != (pinsInBuf & SpectroscopySensor_SS1_PIN_MASK)));
    #endif /* (SpectroscopySensor_SS1_PIN) */

    #if (SpectroscopySensor_SS2_PIN)
        SpectroscopySensor_SET_HSIOM_SEL(SpectroscopySensor_SS2_HSIOM_REG,
                                       SpectroscopySensor_SS2_HSIOM_MASK,
                                       SpectroscopySensor_SS2_HSIOM_POS,
                                       hsiomSel[SpectroscopySensor_SS2_PIN_INDEX]);

        SpectroscopySensor_spi_ss2_SetDriveMode((uint8) pinsDm[SpectroscopySensor_SS2_PIN_INDEX]);

        SpectroscopySensor_SET_INP_DIS(SpectroscopySensor_spi_ss2_INP_DIS,
                                     SpectroscopySensor_spi_ss2_MASK,
                                     (0u != (pinsInBuf & SpectroscopySensor_SS2_PIN_MASK)));
    #endif /* (SpectroscopySensor_SS2_PIN) */

    #if (SpectroscopySensor_SS3_PIN)
        SpectroscopySensor_SET_HSIOM_SEL(SpectroscopySensor_SS3_HSIOM_REG,
                                       SpectroscopySensor_SS3_HSIOM_MASK,
                                       SpectroscopySensor_SS3_HSIOM_POS,
                                       hsiomSel[SpectroscopySensor_SS3_PIN_INDEX]);

        SpectroscopySensor_spi_ss3_SetDriveMode((uint8) pinsDm[SpectroscopySensor_SS3_PIN_INDEX]);

        SpectroscopySensor_SET_INP_DIS(SpectroscopySensor_spi_ss3_INP_DIS,
                                     SpectroscopySensor_spi_ss3_MASK,
                                     (0u != (pinsInBuf & SpectroscopySensor_SS3_PIN_MASK)));
    #endif /* (SpectroscopySensor_SS3_PIN) */
    }

#endif /* (SpectroscopySensor_SCB_MODE_UNCONFIG_CONST_CFG) */


#if (SpectroscopySensor_CY_SCBIP_V0 || SpectroscopySensor_CY_SCBIP_V1)
    /*******************************************************************************
    * Function Name: SpectroscopySensor_I2CSlaveNackGeneration
    ****************************************************************************//**
    *
    *  Sets command to generate NACK to the address or data.
    *
    *******************************************************************************/
    void SpectroscopySensor_I2CSlaveNackGeneration(void)
    {
        /* Check for EC_AM toggle condition: EC_AM and clock stretching for address are enabled */
        if ((0u != (SpectroscopySensor_CTRL_REG & SpectroscopySensor_CTRL_EC_AM_MODE)) &&
            (0u == (SpectroscopySensor_I2C_CTRL_REG & SpectroscopySensor_I2C_CTRL_S_NOT_READY_ADDR_NACK)))
        {
            /* Toggle EC_AM before NACK generation */
            SpectroscopySensor_CTRL_REG &= ~SpectroscopySensor_CTRL_EC_AM_MODE;
            SpectroscopySensor_CTRL_REG |=  SpectroscopySensor_CTRL_EC_AM_MODE;
        }

        SpectroscopySensor_I2C_SLAVE_CMD_REG = SpectroscopySensor_I2C_SLAVE_CMD_S_NACK;
    }
#endif /* (SpectroscopySensor_CY_SCBIP_V0 || SpectroscopySensor_CY_SCBIP_V1) */


/* [] END OF FILE */
