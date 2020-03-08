/***************************************************************************//**
* \file WeatherClick.c
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

#include "WeatherClick_PVT.h"

#if (WeatherClick_SCB_MODE_I2C_INC)
    #include "WeatherClick_I2C_PVT.h"
#endif /* (WeatherClick_SCB_MODE_I2C_INC) */

#if (WeatherClick_SCB_MODE_EZI2C_INC)
    #include "WeatherClick_EZI2C_PVT.h"
#endif /* (WeatherClick_SCB_MODE_EZI2C_INC) */

#if (WeatherClick_SCB_MODE_SPI_INC || WeatherClick_SCB_MODE_UART_INC)
    #include "WeatherClick_SPI_UART_PVT.h"
#endif /* (WeatherClick_SCB_MODE_SPI_INC || WeatherClick_SCB_MODE_UART_INC) */


/***************************************
*    Run Time Configuration Vars
***************************************/

/* Stores internal component configuration for Unconfigured mode */
#if (WeatherClick_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    uint8 WeatherClick_scbMode = WeatherClick_SCB_MODE_UNCONFIG;
    uint8 WeatherClick_scbEnableWake;
    uint8 WeatherClick_scbEnableIntr;

    /* I2C configuration variables */
    uint8 WeatherClick_mode;
    uint8 WeatherClick_acceptAddr;

    /* SPI/UART configuration variables */
    volatile uint8 * WeatherClick_rxBuffer;
    uint8  WeatherClick_rxDataBits;
    uint32 WeatherClick_rxBufferSize;

    volatile uint8 * WeatherClick_txBuffer;
    uint8  WeatherClick_txDataBits;
    uint32 WeatherClick_txBufferSize;

    /* EZI2C configuration variables */
    uint8 WeatherClick_numberOfAddr;
    uint8 WeatherClick_subAddrSize;
#endif /* (WeatherClick_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Common SCB Vars
***************************************/
/**
* \addtogroup group_general
* \{
*/

/** WeatherClick_initVar indicates whether the WeatherClick 
*  component has been initialized. The variable is initialized to 0 
*  and set to 1 the first time SCB_Start() is called. This allows 
*  the component to restart without reinitialization after the first 
*  call to the WeatherClick_Start() routine.
*
*  If re-initialization of the component is required, then the 
*  WeatherClick_Init() function can be called before the 
*  WeatherClick_Start() or WeatherClick_Enable() function.
*/
uint8 WeatherClick_initVar = 0u;


#if (! (WeatherClick_SCB_MODE_I2C_CONST_CFG || \
        WeatherClick_SCB_MODE_EZI2C_CONST_CFG))
    /** This global variable stores TX interrupt sources after 
    * WeatherClick_Stop() is called. Only these TX interrupt sources 
    * will be restored on a subsequent WeatherClick_Enable() call.
    */
    uint16 WeatherClick_IntrTxMask = 0u;
#endif /* (! (WeatherClick_SCB_MODE_I2C_CONST_CFG || \
              WeatherClick_SCB_MODE_EZI2C_CONST_CFG)) */
/** \} globals */

#if (WeatherClick_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_WeatherClick_CUSTOM_INTR_HANDLER)
    void (*WeatherClick_customIntrHandler)(void) = NULL;
#endif /* !defined (CY_REMOVE_WeatherClick_CUSTOM_INTR_HANDLER) */
#endif /* (WeatherClick_SCB_IRQ_INTERNAL) */


/***************************************
*    Private Function Prototypes
***************************************/

static void WeatherClick_ScbEnableIntr(void);
static void WeatherClick_ScbModeStop(void);
static void WeatherClick_ScbModePostEnable(void);


/*******************************************************************************
* Function Name: WeatherClick_Init
****************************************************************************//**
*
*  Initializes the WeatherClick component to operate in one of the selected
*  configurations: I2C, SPI, UART or EZI2C.
*  When the configuration is set to "Unconfigured SCB", this function does
*  not do any initialization. Use mode-specific initialization APIs instead:
*  WeatherClick_I2CInit, WeatherClick_SpiInit, 
*  WeatherClick_UartInit or WeatherClick_EzI2CInit.
*
*******************************************************************************/
void WeatherClick_Init(void)
{
#if (WeatherClick_SCB_MODE_UNCONFIG_CONST_CFG)
    if (WeatherClick_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        WeatherClick_initVar = 0u;
    }
    else
    {
        /* Initialization was done before this function call */
    }

#elif (WeatherClick_SCB_MODE_I2C_CONST_CFG)
    WeatherClick_I2CInit();

#elif (WeatherClick_SCB_MODE_SPI_CONST_CFG)
    WeatherClick_SpiInit();

#elif (WeatherClick_SCB_MODE_UART_CONST_CFG)
    WeatherClick_UartInit();

#elif (WeatherClick_SCB_MODE_EZI2C_CONST_CFG)
    WeatherClick_EzI2CInit();

#endif /* (WeatherClick_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: WeatherClick_Enable
****************************************************************************//**
*
*  Enables WeatherClick component operation: activates the hardware and 
*  internal interrupt. It also restores TX interrupt sources disabled after the 
*  WeatherClick_Stop() function was called (note that level-triggered TX 
*  interrupt sources remain disabled to not cause code lock-up).
*  For I2C and EZI2C modes the interrupt is internal and mandatory for 
*  operation. For SPI and UART modes the interrupt can be configured as none, 
*  internal or external.
*  The WeatherClick configuration should be not changed when the component
*  is enabled. Any configuration changes should be made after disabling the 
*  component.
*  When configuration is set to “Unconfigured WeatherClick”, the component 
*  must first be initialized to operate in one of the following configurations: 
*  I2C, SPI, UART or EZ I2C, using the mode-specific initialization API. 
*  Otherwise this function does not enable the component.
*
*******************************************************************************/
void WeatherClick_Enable(void)
{
#if (WeatherClick_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Enable SCB block, only if it is already configured */
    if (!WeatherClick_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        WeatherClick_CTRL_REG |= WeatherClick_CTRL_ENABLED;

        WeatherClick_ScbEnableIntr();

        /* Call PostEnable function specific to current operation mode */
        WeatherClick_ScbModePostEnable();
    }
#else
    WeatherClick_CTRL_REG |= WeatherClick_CTRL_ENABLED;

    WeatherClick_ScbEnableIntr();

    /* Call PostEnable function specific to current operation mode */
    WeatherClick_ScbModePostEnable();
#endif /* (WeatherClick_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: WeatherClick_Start
****************************************************************************//**
*
*  Invokes WeatherClick_Init() and WeatherClick_Enable().
*  After this function call, the component is enabled and ready for operation.
*  When configuration is set to "Unconfigured SCB", the component must first be
*  initialized to operate in one of the following configurations: I2C, SPI, UART
*  or EZI2C. Otherwise this function does not enable the component.
*
* \globalvars
*  WeatherClick_initVar - used to check initial configuration, modified
*  on first function call.
*
*******************************************************************************/
void WeatherClick_Start(void)
{
    if (0u == WeatherClick_initVar)
    {
        WeatherClick_Init();
        WeatherClick_initVar = 1u; /* Component was initialized */
    }

    WeatherClick_Enable();
}


/*******************************************************************************
* Function Name: WeatherClick_Stop
****************************************************************************//**
*
*  Disables the WeatherClick component: disable the hardware and internal 
*  interrupt. It also disables all TX interrupt sources so as not to cause an 
*  unexpected interrupt trigger because after the component is enabled, the 
*  TX FIFO is empty.
*  Refer to the function WeatherClick_Enable() for the interrupt 
*  configuration details.
*  This function disables the SCB component without checking to see if 
*  communication is in progress. Before calling this function it may be 
*  necessary to check the status of communication to make sure communication 
*  is complete. If this is not done then communication could be stopped mid 
*  byte and corrupted data could result.
*
*******************************************************************************/
void WeatherClick_Stop(void)
{
#if (WeatherClick_SCB_IRQ_INTERNAL)
    WeatherClick_DisableInt();
#endif /* (WeatherClick_SCB_IRQ_INTERNAL) */

    /* Call Stop function specific to current operation mode */
    WeatherClick_ScbModeStop();

    /* Disable SCB IP */
    WeatherClick_CTRL_REG &= (uint32) ~WeatherClick_CTRL_ENABLED;

    /* Disable all TX interrupt sources so as not to cause an unexpected
    * interrupt trigger after the component will be enabled because the 
    * TX FIFO is empty.
    * For SCB IP v0, it is critical as it does not mask-out interrupt
    * sources when it is disabled. This can cause a code lock-up in the
    * interrupt handler because TX FIFO cannot be loaded after the block
    * is disabled.
    */
    WeatherClick_SetTxInterruptMode(WeatherClick_NO_INTR_SOURCES);

#if (WeatherClick_SCB_IRQ_INTERNAL)
    WeatherClick_ClearPendingInt();
#endif /* (WeatherClick_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: WeatherClick_SetRxFifoLevel
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
void WeatherClick_SetRxFifoLevel(uint32 level)
{
    uint32 rxFifoCtrl;

    rxFifoCtrl = WeatherClick_RX_FIFO_CTRL_REG;

    rxFifoCtrl &= ((uint32) ~WeatherClick_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    rxFifoCtrl |= ((uint32) (WeatherClick_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    WeatherClick_RX_FIFO_CTRL_REG = rxFifoCtrl;
}


/*******************************************************************************
* Function Name: WeatherClick_SetTxFifoLevel
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
void WeatherClick_SetTxFifoLevel(uint32 level)
{
    uint32 txFifoCtrl;

    txFifoCtrl = WeatherClick_TX_FIFO_CTRL_REG;

    txFifoCtrl &= ((uint32) ~WeatherClick_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    txFifoCtrl |= ((uint32) (WeatherClick_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    WeatherClick_TX_FIFO_CTRL_REG = txFifoCtrl;
}


#if (WeatherClick_SCB_IRQ_INTERNAL)
    /*******************************************************************************
    * Function Name: WeatherClick_SetCustomInterruptHandler
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
    void WeatherClick_SetCustomInterruptHandler(void (*func)(void))
    {
    #if !defined (CY_REMOVE_WeatherClick_CUSTOM_INTR_HANDLER)
        WeatherClick_customIntrHandler = func; /* Register interrupt handler */
    #else
        if (NULL != func)
        {
            /* Suppress compiler warning */
        }
    #endif /* !defined (CY_REMOVE_WeatherClick_CUSTOM_INTR_HANDLER) */
    }
#endif /* (WeatherClick_SCB_IRQ_INTERNAL) */


/*******************************************************************************
* Function Name: WeatherClick_ScbModeEnableIntr
****************************************************************************//**
*
*  Enables an interrupt for a specific mode.
*
*******************************************************************************/
static void WeatherClick_ScbEnableIntr(void)
{
#if (WeatherClick_SCB_IRQ_INTERNAL)
    /* Enable interrupt in NVIC */
    #if (WeatherClick_SCB_MODE_UNCONFIG_CONST_CFG)
        if (0u != WeatherClick_scbEnableIntr)
        {
            WeatherClick_EnableInt();
        }

    #else
        WeatherClick_EnableInt();

    #endif /* (WeatherClick_SCB_MODE_UNCONFIG_CONST_CFG) */
#endif /* (WeatherClick_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: WeatherClick_ScbModePostEnable
****************************************************************************//**
*
*  Calls the PostEnable function for a specific operation mode.
*
*******************************************************************************/
static void WeatherClick_ScbModePostEnable(void)
{
#if (WeatherClick_SCB_MODE_UNCONFIG_CONST_CFG)
#if (!WeatherClick_CY_SCBIP_V1)
    if (WeatherClick_SCB_MODE_SPI_RUNTM_CFG)
    {
        WeatherClick_SpiPostEnable();
    }
    else if (WeatherClick_SCB_MODE_UART_RUNTM_CFG)
    {
        WeatherClick_UartPostEnable();
    }
    else
    {
        /* Unknown mode: do nothing */
    }
#endif /* (!WeatherClick_CY_SCBIP_V1) */

#elif (WeatherClick_SCB_MODE_SPI_CONST_CFG)
    WeatherClick_SpiPostEnable();

#elif (WeatherClick_SCB_MODE_UART_CONST_CFG)
    WeatherClick_UartPostEnable();

#else
    /* Unknown mode: do nothing */
#endif /* (WeatherClick_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: WeatherClick_ScbModeStop
****************************************************************************//**
*
*  Calls the Stop function for a specific operation mode.
*
*******************************************************************************/
static void WeatherClick_ScbModeStop(void)
{
#if (WeatherClick_SCB_MODE_UNCONFIG_CONST_CFG)
    if (WeatherClick_SCB_MODE_I2C_RUNTM_CFG)
    {
        WeatherClick_I2CStop();
    }
    else if (WeatherClick_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        WeatherClick_EzI2CStop();
    }
#if (!WeatherClick_CY_SCBIP_V1)
    else if (WeatherClick_SCB_MODE_SPI_RUNTM_CFG)
    {
        WeatherClick_SpiStop();
    }
    else if (WeatherClick_SCB_MODE_UART_RUNTM_CFG)
    {
        WeatherClick_UartStop();
    }
#endif /* (!WeatherClick_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
#elif (WeatherClick_SCB_MODE_I2C_CONST_CFG)
    WeatherClick_I2CStop();

#elif (WeatherClick_SCB_MODE_EZI2C_CONST_CFG)
    WeatherClick_EzI2CStop();

#elif (WeatherClick_SCB_MODE_SPI_CONST_CFG)
    WeatherClick_SpiStop();

#elif (WeatherClick_SCB_MODE_UART_CONST_CFG)
    WeatherClick_UartStop();

#else
    /* Unknown mode: do nothing */
#endif /* (WeatherClick_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if (WeatherClick_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: WeatherClick_SetPins
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
    void WeatherClick_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask)
    {
        uint32 pinsDm[WeatherClick_SCB_PINS_NUMBER];
        uint32 i;
        
    #if (!WeatherClick_CY_SCBIP_V1)
        uint32 pinsInBuf = 0u;
    #endif /* (!WeatherClick_CY_SCBIP_V1) */
        
        uint32 hsiomSel[WeatherClick_SCB_PINS_NUMBER] = 
        {
            WeatherClick_RX_SCL_MOSI_HSIOM_SEL_GPIO,
            WeatherClick_TX_SDA_MISO_HSIOM_SEL_GPIO,
            0u,
            0u,
            0u,
            0u,
            0u,
        };

    #if (WeatherClick_CY_SCBIP_V1)
        /* Supress compiler warning. */
        if ((0u == subMode) || (0u == uartEnableMask))
        {
        }
    #endif /* (WeatherClick_CY_SCBIP_V1) */

        /* Set default HSIOM to GPIO and Drive Mode to Analog Hi-Z */
        for (i = 0u; i < WeatherClick_SCB_PINS_NUMBER; i++)
        {
            pinsDm[i] = WeatherClick_PIN_DM_ALG_HIZ;
        }

        if ((WeatherClick_SCB_MODE_I2C   == mode) ||
            (WeatherClick_SCB_MODE_EZI2C == mode))
        {
        #if (WeatherClick_RX_SCL_MOSI_PIN)
            hsiomSel[WeatherClick_RX_SCL_MOSI_PIN_INDEX] = WeatherClick_RX_SCL_MOSI_HSIOM_SEL_I2C;
            pinsDm  [WeatherClick_RX_SCL_MOSI_PIN_INDEX] = WeatherClick_PIN_DM_OD_LO;
        #elif (WeatherClick_RX_WAKE_SCL_MOSI_PIN)
            hsiomSel[WeatherClick_RX_WAKE_SCL_MOSI_PIN_INDEX] = WeatherClick_RX_WAKE_SCL_MOSI_HSIOM_SEL_I2C;
            pinsDm  [WeatherClick_RX_WAKE_SCL_MOSI_PIN_INDEX] = WeatherClick_PIN_DM_OD_LO;
        #else
        #endif /* (WeatherClick_RX_SCL_MOSI_PIN) */
        
        #if (WeatherClick_TX_SDA_MISO_PIN)
            hsiomSel[WeatherClick_TX_SDA_MISO_PIN_INDEX] = WeatherClick_TX_SDA_MISO_HSIOM_SEL_I2C;
            pinsDm  [WeatherClick_TX_SDA_MISO_PIN_INDEX] = WeatherClick_PIN_DM_OD_LO;
        #endif /* (WeatherClick_TX_SDA_MISO_PIN) */
        }
    #if (!WeatherClick_CY_SCBIP_V1)
        else if (WeatherClick_SCB_MODE_SPI == mode)
        {
        #if (WeatherClick_RX_SCL_MOSI_PIN)
            hsiomSel[WeatherClick_RX_SCL_MOSI_PIN_INDEX] = WeatherClick_RX_SCL_MOSI_HSIOM_SEL_SPI;
        #elif (WeatherClick_RX_WAKE_SCL_MOSI_PIN)
            hsiomSel[WeatherClick_RX_WAKE_SCL_MOSI_PIN_INDEX] = WeatherClick_RX_WAKE_SCL_MOSI_HSIOM_SEL_SPI;
        #else
        #endif /* (WeatherClick_RX_SCL_MOSI_PIN) */
        
        #if (WeatherClick_TX_SDA_MISO_PIN)
            hsiomSel[WeatherClick_TX_SDA_MISO_PIN_INDEX] = WeatherClick_TX_SDA_MISO_HSIOM_SEL_SPI;
        #endif /* (WeatherClick_TX_SDA_MISO_PIN) */
        
        #if (WeatherClick_CTS_SCLK_PIN)
            hsiomSel[WeatherClick_CTS_SCLK_PIN_INDEX] = WeatherClick_CTS_SCLK_HSIOM_SEL_SPI;
        #endif /* (WeatherClick_CTS_SCLK_PIN) */

            if (WeatherClick_SPI_SLAVE == subMode)
            {
                /* Slave */
                pinsDm[WeatherClick_RX_SCL_MOSI_PIN_INDEX] = WeatherClick_PIN_DM_DIG_HIZ;
                pinsDm[WeatherClick_TX_SDA_MISO_PIN_INDEX] = WeatherClick_PIN_DM_STRONG;
                pinsDm[WeatherClick_CTS_SCLK_PIN_INDEX] = WeatherClick_PIN_DM_DIG_HIZ;

            #if (WeatherClick_RTS_SS0_PIN)
                /* Only SS0 is valid choice for Slave */
                hsiomSel[WeatherClick_RTS_SS0_PIN_INDEX] = WeatherClick_RTS_SS0_HSIOM_SEL_SPI;
                pinsDm  [WeatherClick_RTS_SS0_PIN_INDEX] = WeatherClick_PIN_DM_DIG_HIZ;
            #endif /* (WeatherClick_RTS_SS0_PIN) */

            #if (WeatherClick_TX_SDA_MISO_PIN)
                /* Disable input buffer */
                 pinsInBuf |= WeatherClick_TX_SDA_MISO_PIN_MASK;
            #endif /* (WeatherClick_TX_SDA_MISO_PIN) */
            }
            else 
            {
                /* (Master) */
                pinsDm[WeatherClick_RX_SCL_MOSI_PIN_INDEX] = WeatherClick_PIN_DM_STRONG;
                pinsDm[WeatherClick_TX_SDA_MISO_PIN_INDEX] = WeatherClick_PIN_DM_DIG_HIZ;
                pinsDm[WeatherClick_CTS_SCLK_PIN_INDEX] = WeatherClick_PIN_DM_STRONG;

            #if (WeatherClick_RTS_SS0_PIN)
                hsiomSel [WeatherClick_RTS_SS0_PIN_INDEX] = WeatherClick_RTS_SS0_HSIOM_SEL_SPI;
                pinsDm   [WeatherClick_RTS_SS0_PIN_INDEX] = WeatherClick_PIN_DM_STRONG;
                pinsInBuf |= WeatherClick_RTS_SS0_PIN_MASK;
            #endif /* (WeatherClick_RTS_SS0_PIN) */

            #if (WeatherClick_SS1_PIN)
                hsiomSel [WeatherClick_SS1_PIN_INDEX] = WeatherClick_SS1_HSIOM_SEL_SPI;
                pinsDm   [WeatherClick_SS1_PIN_INDEX] = WeatherClick_PIN_DM_STRONG;
                pinsInBuf |= WeatherClick_SS1_PIN_MASK;
            #endif /* (WeatherClick_SS1_PIN) */

            #if (WeatherClick_SS2_PIN)
                hsiomSel [WeatherClick_SS2_PIN_INDEX] = WeatherClick_SS2_HSIOM_SEL_SPI;
                pinsDm   [WeatherClick_SS2_PIN_INDEX] = WeatherClick_PIN_DM_STRONG;
                pinsInBuf |= WeatherClick_SS2_PIN_MASK;
            #endif /* (WeatherClick_SS2_PIN) */

            #if (WeatherClick_SS3_PIN)
                hsiomSel [WeatherClick_SS3_PIN_INDEX] = WeatherClick_SS3_HSIOM_SEL_SPI;
                pinsDm   [WeatherClick_SS3_PIN_INDEX] = WeatherClick_PIN_DM_STRONG;
                pinsInBuf |= WeatherClick_SS3_PIN_MASK;
            #endif /* (WeatherClick_SS3_PIN) */

                /* Disable input buffers */
            #if (WeatherClick_RX_SCL_MOSI_PIN)
                pinsInBuf |= WeatherClick_RX_SCL_MOSI_PIN_MASK;
            #elif (WeatherClick_RX_WAKE_SCL_MOSI_PIN)
                pinsInBuf |= WeatherClick_RX_WAKE_SCL_MOSI_PIN_MASK;
            #else
            #endif /* (WeatherClick_RX_SCL_MOSI_PIN) */

            #if (WeatherClick_CTS_SCLK_PIN)
                pinsInBuf |= WeatherClick_CTS_SCLK_PIN_MASK;
            #endif /* (WeatherClick_CTS_SCLK_PIN) */
            }
        }
        else /* UART */
        {
            if (WeatherClick_UART_MODE_SMARTCARD == subMode)
            {
                /* SmartCard */
            #if (WeatherClick_TX_SDA_MISO_PIN)
                hsiomSel[WeatherClick_TX_SDA_MISO_PIN_INDEX] = WeatherClick_TX_SDA_MISO_HSIOM_SEL_UART;
                pinsDm  [WeatherClick_TX_SDA_MISO_PIN_INDEX] = WeatherClick_PIN_DM_OD_LO;
            #endif /* (WeatherClick_TX_SDA_MISO_PIN) */
            }
            else /* Standard or IrDA */
            {
                if (0u != (WeatherClick_UART_RX_PIN_ENABLE & uartEnableMask))
                {
                #if (WeatherClick_RX_SCL_MOSI_PIN)
                    hsiomSel[WeatherClick_RX_SCL_MOSI_PIN_INDEX] = WeatherClick_RX_SCL_MOSI_HSIOM_SEL_UART;
                    pinsDm  [WeatherClick_RX_SCL_MOSI_PIN_INDEX] = WeatherClick_PIN_DM_DIG_HIZ;
                #elif (WeatherClick_RX_WAKE_SCL_MOSI_PIN)
                    hsiomSel[WeatherClick_RX_WAKE_SCL_MOSI_PIN_INDEX] = WeatherClick_RX_WAKE_SCL_MOSI_HSIOM_SEL_UART;
                    pinsDm  [WeatherClick_RX_WAKE_SCL_MOSI_PIN_INDEX] = WeatherClick_PIN_DM_DIG_HIZ;
                #else
                #endif /* (WeatherClick_RX_SCL_MOSI_PIN) */
                }

                if (0u != (WeatherClick_UART_TX_PIN_ENABLE & uartEnableMask))
                {
                #if (WeatherClick_TX_SDA_MISO_PIN)
                    hsiomSel[WeatherClick_TX_SDA_MISO_PIN_INDEX] = WeatherClick_TX_SDA_MISO_HSIOM_SEL_UART;
                    pinsDm  [WeatherClick_TX_SDA_MISO_PIN_INDEX] = WeatherClick_PIN_DM_STRONG;
                    
                    /* Disable input buffer */
                    pinsInBuf |= WeatherClick_TX_SDA_MISO_PIN_MASK;
                #endif /* (WeatherClick_TX_SDA_MISO_PIN) */
                }

            #if !(WeatherClick_CY_SCBIP_V0 || WeatherClick_CY_SCBIP_V1)
                if (WeatherClick_UART_MODE_STD == subMode)
                {
                    if (0u != (WeatherClick_UART_CTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* CTS input is multiplexed with SCLK */
                    #if (WeatherClick_CTS_SCLK_PIN)
                        hsiomSel[WeatherClick_CTS_SCLK_PIN_INDEX] = WeatherClick_CTS_SCLK_HSIOM_SEL_UART;
                        pinsDm  [WeatherClick_CTS_SCLK_PIN_INDEX] = WeatherClick_PIN_DM_DIG_HIZ;
                    #endif /* (WeatherClick_CTS_SCLK_PIN) */
                    }

                    if (0u != (WeatherClick_UART_RTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* RTS output is multiplexed with SS0 */
                    #if (WeatherClick_RTS_SS0_PIN)
                        hsiomSel[WeatherClick_RTS_SS0_PIN_INDEX] = WeatherClick_RTS_SS0_HSIOM_SEL_UART;
                        pinsDm  [WeatherClick_RTS_SS0_PIN_INDEX] = WeatherClick_PIN_DM_STRONG;
                        
                        /* Disable input buffer */
                        pinsInBuf |= WeatherClick_RTS_SS0_PIN_MASK;
                    #endif /* (WeatherClick_RTS_SS0_PIN) */
                    }
                }
            #endif /* !(WeatherClick_CY_SCBIP_V0 || WeatherClick_CY_SCBIP_V1) */
            }
        }
    #endif /* (!WeatherClick_CY_SCBIP_V1) */

    /* Configure pins: set HSIOM, DM and InputBufEnable */
    /* Note: the DR register settings do not effect the pin output if HSIOM is other than GPIO */

    #if (WeatherClick_RX_SCL_MOSI_PIN)
        WeatherClick_SET_HSIOM_SEL(WeatherClick_RX_SCL_MOSI_HSIOM_REG,
                                       WeatherClick_RX_SCL_MOSI_HSIOM_MASK,
                                       WeatherClick_RX_SCL_MOSI_HSIOM_POS,
                                        hsiomSel[WeatherClick_RX_SCL_MOSI_PIN_INDEX]);

        WeatherClick_uart_rx_i2c_scl_spi_mosi_SetDriveMode((uint8) pinsDm[WeatherClick_RX_SCL_MOSI_PIN_INDEX]);

        #if (!WeatherClick_CY_SCBIP_V1)
            WeatherClick_SET_INP_DIS(WeatherClick_uart_rx_i2c_scl_spi_mosi_INP_DIS,
                                         WeatherClick_uart_rx_i2c_scl_spi_mosi_MASK,
                                         (0u != (pinsInBuf & WeatherClick_RX_SCL_MOSI_PIN_MASK)));
        #endif /* (!WeatherClick_CY_SCBIP_V1) */
    
    #elif (WeatherClick_RX_WAKE_SCL_MOSI_PIN)
        WeatherClick_SET_HSIOM_SEL(WeatherClick_RX_WAKE_SCL_MOSI_HSIOM_REG,
                                       WeatherClick_RX_WAKE_SCL_MOSI_HSIOM_MASK,
                                       WeatherClick_RX_WAKE_SCL_MOSI_HSIOM_POS,
                                       hsiomSel[WeatherClick_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        WeatherClick_uart_rx_wake_i2c_scl_spi_mosi_SetDriveMode((uint8)
                                                               pinsDm[WeatherClick_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        WeatherClick_SET_INP_DIS(WeatherClick_uart_rx_wake_i2c_scl_spi_mosi_INP_DIS,
                                     WeatherClick_uart_rx_wake_i2c_scl_spi_mosi_MASK,
                                     (0u != (pinsInBuf & WeatherClick_RX_WAKE_SCL_MOSI_PIN_MASK)));

         /* Set interrupt on falling edge */
        WeatherClick_SET_INCFG_TYPE(WeatherClick_RX_WAKE_SCL_MOSI_INTCFG_REG,
                                        WeatherClick_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK,
                                        WeatherClick_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS,
                                        WeatherClick_INTCFG_TYPE_FALLING_EDGE);
    #else
    #endif /* (WeatherClick_RX_WAKE_SCL_MOSI_PIN) */

    #if (WeatherClick_TX_SDA_MISO_PIN)
        WeatherClick_SET_HSIOM_SEL(WeatherClick_TX_SDA_MISO_HSIOM_REG,
                                       WeatherClick_TX_SDA_MISO_HSIOM_MASK,
                                       WeatherClick_TX_SDA_MISO_HSIOM_POS,
                                        hsiomSel[WeatherClick_TX_SDA_MISO_PIN_INDEX]);

        WeatherClick_uart_tx_i2c_sda_spi_miso_SetDriveMode((uint8) pinsDm[WeatherClick_TX_SDA_MISO_PIN_INDEX]);

    #if (!WeatherClick_CY_SCBIP_V1)
        WeatherClick_SET_INP_DIS(WeatherClick_uart_tx_i2c_sda_spi_miso_INP_DIS,
                                     WeatherClick_uart_tx_i2c_sda_spi_miso_MASK,
                                    (0u != (pinsInBuf & WeatherClick_TX_SDA_MISO_PIN_MASK)));
    #endif /* (!WeatherClick_CY_SCBIP_V1) */
    #endif /* (WeatherClick_RX_SCL_MOSI_PIN) */

    #if (WeatherClick_CTS_SCLK_PIN)
        WeatherClick_SET_HSIOM_SEL(WeatherClick_CTS_SCLK_HSIOM_REG,
                                       WeatherClick_CTS_SCLK_HSIOM_MASK,
                                       WeatherClick_CTS_SCLK_HSIOM_POS,
                                       hsiomSel[WeatherClick_CTS_SCLK_PIN_INDEX]);

        WeatherClick_uart_cts_spi_sclk_SetDriveMode((uint8) pinsDm[WeatherClick_CTS_SCLK_PIN_INDEX]);

        WeatherClick_SET_INP_DIS(WeatherClick_uart_cts_spi_sclk_INP_DIS,
                                     WeatherClick_uart_cts_spi_sclk_MASK,
                                     (0u != (pinsInBuf & WeatherClick_CTS_SCLK_PIN_MASK)));
    #endif /* (WeatherClick_CTS_SCLK_PIN) */

    #if (WeatherClick_RTS_SS0_PIN)
        WeatherClick_SET_HSIOM_SEL(WeatherClick_RTS_SS0_HSIOM_REG,
                                       WeatherClick_RTS_SS0_HSIOM_MASK,
                                       WeatherClick_RTS_SS0_HSIOM_POS,
                                       hsiomSel[WeatherClick_RTS_SS0_PIN_INDEX]);

        WeatherClick_uart_rts_spi_ss0_SetDriveMode((uint8) pinsDm[WeatherClick_RTS_SS0_PIN_INDEX]);

        WeatherClick_SET_INP_DIS(WeatherClick_uart_rts_spi_ss0_INP_DIS,
                                     WeatherClick_uart_rts_spi_ss0_MASK,
                                     (0u != (pinsInBuf & WeatherClick_RTS_SS0_PIN_MASK)));
    #endif /* (WeatherClick_RTS_SS0_PIN) */

    #if (WeatherClick_SS1_PIN)
        WeatherClick_SET_HSIOM_SEL(WeatherClick_SS1_HSIOM_REG,
                                       WeatherClick_SS1_HSIOM_MASK,
                                       WeatherClick_SS1_HSIOM_POS,
                                       hsiomSel[WeatherClick_SS1_PIN_INDEX]);

        WeatherClick_spi_ss1_SetDriveMode((uint8) pinsDm[WeatherClick_SS1_PIN_INDEX]);

        WeatherClick_SET_INP_DIS(WeatherClick_spi_ss1_INP_DIS,
                                     WeatherClick_spi_ss1_MASK,
                                     (0u != (pinsInBuf & WeatherClick_SS1_PIN_MASK)));
    #endif /* (WeatherClick_SS1_PIN) */

    #if (WeatherClick_SS2_PIN)
        WeatherClick_SET_HSIOM_SEL(WeatherClick_SS2_HSIOM_REG,
                                       WeatherClick_SS2_HSIOM_MASK,
                                       WeatherClick_SS2_HSIOM_POS,
                                       hsiomSel[WeatherClick_SS2_PIN_INDEX]);

        WeatherClick_spi_ss2_SetDriveMode((uint8) pinsDm[WeatherClick_SS2_PIN_INDEX]);

        WeatherClick_SET_INP_DIS(WeatherClick_spi_ss2_INP_DIS,
                                     WeatherClick_spi_ss2_MASK,
                                     (0u != (pinsInBuf & WeatherClick_SS2_PIN_MASK)));
    #endif /* (WeatherClick_SS2_PIN) */

    #if (WeatherClick_SS3_PIN)
        WeatherClick_SET_HSIOM_SEL(WeatherClick_SS3_HSIOM_REG,
                                       WeatherClick_SS3_HSIOM_MASK,
                                       WeatherClick_SS3_HSIOM_POS,
                                       hsiomSel[WeatherClick_SS3_PIN_INDEX]);

        WeatherClick_spi_ss3_SetDriveMode((uint8) pinsDm[WeatherClick_SS3_PIN_INDEX]);

        WeatherClick_SET_INP_DIS(WeatherClick_spi_ss3_INP_DIS,
                                     WeatherClick_spi_ss3_MASK,
                                     (0u != (pinsInBuf & WeatherClick_SS3_PIN_MASK)));
    #endif /* (WeatherClick_SS3_PIN) */
    }

#endif /* (WeatherClick_SCB_MODE_UNCONFIG_CONST_CFG) */


#if (WeatherClick_CY_SCBIP_V0 || WeatherClick_CY_SCBIP_V1)
    /*******************************************************************************
    * Function Name: WeatherClick_I2CSlaveNackGeneration
    ****************************************************************************//**
    *
    *  Sets command to generate NACK to the address or data.
    *
    *******************************************************************************/
    void WeatherClick_I2CSlaveNackGeneration(void)
    {
        /* Check for EC_AM toggle condition: EC_AM and clock stretching for address are enabled */
        if ((0u != (WeatherClick_CTRL_REG & WeatherClick_CTRL_EC_AM_MODE)) &&
            (0u == (WeatherClick_I2C_CTRL_REG & WeatherClick_I2C_CTRL_S_NOT_READY_ADDR_NACK)))
        {
            /* Toggle EC_AM before NACK generation */
            WeatherClick_CTRL_REG &= ~WeatherClick_CTRL_EC_AM_MODE;
            WeatherClick_CTRL_REG |=  WeatherClick_CTRL_EC_AM_MODE;
        }

        WeatherClick_I2C_SLAVE_CMD_REG = WeatherClick_I2C_SLAVE_CMD_S_NACK;
    }
#endif /* (WeatherClick_CY_SCBIP_V0 || WeatherClick_CY_SCBIP_V1) */


/* [] END OF FILE */
