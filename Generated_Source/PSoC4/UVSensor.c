/***************************************************************************//**
* \file UVSensor.c
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

#include "UVSensor_PVT.h"

#if (UVSensor_SCB_MODE_I2C_INC)
    #include "UVSensor_I2C_PVT.h"
#endif /* (UVSensor_SCB_MODE_I2C_INC) */

#if (UVSensor_SCB_MODE_EZI2C_INC)
    #include "UVSensor_EZI2C_PVT.h"
#endif /* (UVSensor_SCB_MODE_EZI2C_INC) */

#if (UVSensor_SCB_MODE_SPI_INC || UVSensor_SCB_MODE_UART_INC)
    #include "UVSensor_SPI_UART_PVT.h"
#endif /* (UVSensor_SCB_MODE_SPI_INC || UVSensor_SCB_MODE_UART_INC) */


/***************************************
*    Run Time Configuration Vars
***************************************/

/* Stores internal component configuration for Unconfigured mode */
#if (UVSensor_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    uint8 UVSensor_scbMode = UVSensor_SCB_MODE_UNCONFIG;
    uint8 UVSensor_scbEnableWake;
    uint8 UVSensor_scbEnableIntr;

    /* I2C configuration variables */
    uint8 UVSensor_mode;
    uint8 UVSensor_acceptAddr;

    /* SPI/UART configuration variables */
    volatile uint8 * UVSensor_rxBuffer;
    uint8  UVSensor_rxDataBits;
    uint32 UVSensor_rxBufferSize;

    volatile uint8 * UVSensor_txBuffer;
    uint8  UVSensor_txDataBits;
    uint32 UVSensor_txBufferSize;

    /* EZI2C configuration variables */
    uint8 UVSensor_numberOfAddr;
    uint8 UVSensor_subAddrSize;
#endif /* (UVSensor_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Common SCB Vars
***************************************/
/**
* \addtogroup group_general
* \{
*/

/** UVSensor_initVar indicates whether the UVSensor 
*  component has been initialized. The variable is initialized to 0 
*  and set to 1 the first time SCB_Start() is called. This allows 
*  the component to restart without reinitialization after the first 
*  call to the UVSensor_Start() routine.
*
*  If re-initialization of the component is required, then the 
*  UVSensor_Init() function can be called before the 
*  UVSensor_Start() or UVSensor_Enable() function.
*/
uint8 UVSensor_initVar = 0u;


#if (! (UVSensor_SCB_MODE_I2C_CONST_CFG || \
        UVSensor_SCB_MODE_EZI2C_CONST_CFG))
    /** This global variable stores TX interrupt sources after 
    * UVSensor_Stop() is called. Only these TX interrupt sources 
    * will be restored on a subsequent UVSensor_Enable() call.
    */
    uint16 UVSensor_IntrTxMask = 0u;
#endif /* (! (UVSensor_SCB_MODE_I2C_CONST_CFG || \
              UVSensor_SCB_MODE_EZI2C_CONST_CFG)) */
/** \} globals */

#if (UVSensor_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_UVSensor_CUSTOM_INTR_HANDLER)
    void (*UVSensor_customIntrHandler)(void) = NULL;
#endif /* !defined (CY_REMOVE_UVSensor_CUSTOM_INTR_HANDLER) */
#endif /* (UVSensor_SCB_IRQ_INTERNAL) */


/***************************************
*    Private Function Prototypes
***************************************/

static void UVSensor_ScbEnableIntr(void);
static void UVSensor_ScbModeStop(void);
static void UVSensor_ScbModePostEnable(void);


/*******************************************************************************
* Function Name: UVSensor_Init
****************************************************************************//**
*
*  Initializes the UVSensor component to operate in one of the selected
*  configurations: I2C, SPI, UART or EZI2C.
*  When the configuration is set to "Unconfigured SCB", this function does
*  not do any initialization. Use mode-specific initialization APIs instead:
*  UVSensor_I2CInit, UVSensor_SpiInit, 
*  UVSensor_UartInit or UVSensor_EzI2CInit.
*
*******************************************************************************/
void UVSensor_Init(void)
{
#if (UVSensor_SCB_MODE_UNCONFIG_CONST_CFG)
    if (UVSensor_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        UVSensor_initVar = 0u;
    }
    else
    {
        /* Initialization was done before this function call */
    }

#elif (UVSensor_SCB_MODE_I2C_CONST_CFG)
    UVSensor_I2CInit();

#elif (UVSensor_SCB_MODE_SPI_CONST_CFG)
    UVSensor_SpiInit();

#elif (UVSensor_SCB_MODE_UART_CONST_CFG)
    UVSensor_UartInit();

#elif (UVSensor_SCB_MODE_EZI2C_CONST_CFG)
    UVSensor_EzI2CInit();

#endif /* (UVSensor_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: UVSensor_Enable
****************************************************************************//**
*
*  Enables UVSensor component operation: activates the hardware and 
*  internal interrupt. It also restores TX interrupt sources disabled after the 
*  UVSensor_Stop() function was called (note that level-triggered TX 
*  interrupt sources remain disabled to not cause code lock-up).
*  For I2C and EZI2C modes the interrupt is internal and mandatory for 
*  operation. For SPI and UART modes the interrupt can be configured as none, 
*  internal or external.
*  The UVSensor configuration should be not changed when the component
*  is enabled. Any configuration changes should be made after disabling the 
*  component.
*  When configuration is set to “Unconfigured UVSensor”, the component 
*  must first be initialized to operate in one of the following configurations: 
*  I2C, SPI, UART or EZ I2C, using the mode-specific initialization API. 
*  Otherwise this function does not enable the component.
*
*******************************************************************************/
void UVSensor_Enable(void)
{
#if (UVSensor_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Enable SCB block, only if it is already configured */
    if (!UVSensor_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        UVSensor_CTRL_REG |= UVSensor_CTRL_ENABLED;

        UVSensor_ScbEnableIntr();

        /* Call PostEnable function specific to current operation mode */
        UVSensor_ScbModePostEnable();
    }
#else
    UVSensor_CTRL_REG |= UVSensor_CTRL_ENABLED;

    UVSensor_ScbEnableIntr();

    /* Call PostEnable function specific to current operation mode */
    UVSensor_ScbModePostEnable();
#endif /* (UVSensor_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: UVSensor_Start
****************************************************************************//**
*
*  Invokes UVSensor_Init() and UVSensor_Enable().
*  After this function call, the component is enabled and ready for operation.
*  When configuration is set to "Unconfigured SCB", the component must first be
*  initialized to operate in one of the following configurations: I2C, SPI, UART
*  or EZI2C. Otherwise this function does not enable the component.
*
* \globalvars
*  UVSensor_initVar - used to check initial configuration, modified
*  on first function call.
*
*******************************************************************************/
void UVSensor_Start(void)
{
    if (0u == UVSensor_initVar)
    {
        UVSensor_Init();
        UVSensor_initVar = 1u; /* Component was initialized */
    }

    UVSensor_Enable();
}


/*******************************************************************************
* Function Name: UVSensor_Stop
****************************************************************************//**
*
*  Disables the UVSensor component: disable the hardware and internal 
*  interrupt. It also disables all TX interrupt sources so as not to cause an 
*  unexpected interrupt trigger because after the component is enabled, the 
*  TX FIFO is empty.
*  Refer to the function UVSensor_Enable() for the interrupt 
*  configuration details.
*  This function disables the SCB component without checking to see if 
*  communication is in progress. Before calling this function it may be 
*  necessary to check the status of communication to make sure communication 
*  is complete. If this is not done then communication could be stopped mid 
*  byte and corrupted data could result.
*
*******************************************************************************/
void UVSensor_Stop(void)
{
#if (UVSensor_SCB_IRQ_INTERNAL)
    UVSensor_DisableInt();
#endif /* (UVSensor_SCB_IRQ_INTERNAL) */

    /* Call Stop function specific to current operation mode */
    UVSensor_ScbModeStop();

    /* Disable SCB IP */
    UVSensor_CTRL_REG &= (uint32) ~UVSensor_CTRL_ENABLED;

    /* Disable all TX interrupt sources so as not to cause an unexpected
    * interrupt trigger after the component will be enabled because the 
    * TX FIFO is empty.
    * For SCB IP v0, it is critical as it does not mask-out interrupt
    * sources when it is disabled. This can cause a code lock-up in the
    * interrupt handler because TX FIFO cannot be loaded after the block
    * is disabled.
    */
    UVSensor_SetTxInterruptMode(UVSensor_NO_INTR_SOURCES);

#if (UVSensor_SCB_IRQ_INTERNAL)
    UVSensor_ClearPendingInt();
#endif /* (UVSensor_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: UVSensor_SetRxFifoLevel
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
void UVSensor_SetRxFifoLevel(uint32 level)
{
    uint32 rxFifoCtrl;

    rxFifoCtrl = UVSensor_RX_FIFO_CTRL_REG;

    rxFifoCtrl &= ((uint32) ~UVSensor_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    rxFifoCtrl |= ((uint32) (UVSensor_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    UVSensor_RX_FIFO_CTRL_REG = rxFifoCtrl;
}


/*******************************************************************************
* Function Name: UVSensor_SetTxFifoLevel
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
void UVSensor_SetTxFifoLevel(uint32 level)
{
    uint32 txFifoCtrl;

    txFifoCtrl = UVSensor_TX_FIFO_CTRL_REG;

    txFifoCtrl &= ((uint32) ~UVSensor_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    txFifoCtrl |= ((uint32) (UVSensor_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    UVSensor_TX_FIFO_CTRL_REG = txFifoCtrl;
}


#if (UVSensor_SCB_IRQ_INTERNAL)
    /*******************************************************************************
    * Function Name: UVSensor_SetCustomInterruptHandler
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
    void UVSensor_SetCustomInterruptHandler(void (*func)(void))
    {
    #if !defined (CY_REMOVE_UVSensor_CUSTOM_INTR_HANDLER)
        UVSensor_customIntrHandler = func; /* Register interrupt handler */
    #else
        if (NULL != func)
        {
            /* Suppress compiler warning */
        }
    #endif /* !defined (CY_REMOVE_UVSensor_CUSTOM_INTR_HANDLER) */
    }
#endif /* (UVSensor_SCB_IRQ_INTERNAL) */


/*******************************************************************************
* Function Name: UVSensor_ScbModeEnableIntr
****************************************************************************//**
*
*  Enables an interrupt for a specific mode.
*
*******************************************************************************/
static void UVSensor_ScbEnableIntr(void)
{
#if (UVSensor_SCB_IRQ_INTERNAL)
    /* Enable interrupt in NVIC */
    #if (UVSensor_SCB_MODE_UNCONFIG_CONST_CFG)
        if (0u != UVSensor_scbEnableIntr)
        {
            UVSensor_EnableInt();
        }

    #else
        UVSensor_EnableInt();

    #endif /* (UVSensor_SCB_MODE_UNCONFIG_CONST_CFG) */
#endif /* (UVSensor_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: UVSensor_ScbModePostEnable
****************************************************************************//**
*
*  Calls the PostEnable function for a specific operation mode.
*
*******************************************************************************/
static void UVSensor_ScbModePostEnable(void)
{
#if (UVSensor_SCB_MODE_UNCONFIG_CONST_CFG)
#if (!UVSensor_CY_SCBIP_V1)
    if (UVSensor_SCB_MODE_SPI_RUNTM_CFG)
    {
        UVSensor_SpiPostEnable();
    }
    else if (UVSensor_SCB_MODE_UART_RUNTM_CFG)
    {
        UVSensor_UartPostEnable();
    }
    else
    {
        /* Unknown mode: do nothing */
    }
#endif /* (!UVSensor_CY_SCBIP_V1) */

#elif (UVSensor_SCB_MODE_SPI_CONST_CFG)
    UVSensor_SpiPostEnable();

#elif (UVSensor_SCB_MODE_UART_CONST_CFG)
    UVSensor_UartPostEnable();

#else
    /* Unknown mode: do nothing */
#endif /* (UVSensor_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: UVSensor_ScbModeStop
****************************************************************************//**
*
*  Calls the Stop function for a specific operation mode.
*
*******************************************************************************/
static void UVSensor_ScbModeStop(void)
{
#if (UVSensor_SCB_MODE_UNCONFIG_CONST_CFG)
    if (UVSensor_SCB_MODE_I2C_RUNTM_CFG)
    {
        UVSensor_I2CStop();
    }
    else if (UVSensor_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        UVSensor_EzI2CStop();
    }
#if (!UVSensor_CY_SCBIP_V1)
    else if (UVSensor_SCB_MODE_SPI_RUNTM_CFG)
    {
        UVSensor_SpiStop();
    }
    else if (UVSensor_SCB_MODE_UART_RUNTM_CFG)
    {
        UVSensor_UartStop();
    }
#endif /* (!UVSensor_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
#elif (UVSensor_SCB_MODE_I2C_CONST_CFG)
    UVSensor_I2CStop();

#elif (UVSensor_SCB_MODE_EZI2C_CONST_CFG)
    UVSensor_EzI2CStop();

#elif (UVSensor_SCB_MODE_SPI_CONST_CFG)
    UVSensor_SpiStop();

#elif (UVSensor_SCB_MODE_UART_CONST_CFG)
    UVSensor_UartStop();

#else
    /* Unknown mode: do nothing */
#endif /* (UVSensor_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if (UVSensor_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: UVSensor_SetPins
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
    void UVSensor_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask)
    {
        uint32 pinsDm[UVSensor_SCB_PINS_NUMBER];
        uint32 i;
        
    #if (!UVSensor_CY_SCBIP_V1)
        uint32 pinsInBuf = 0u;
    #endif /* (!UVSensor_CY_SCBIP_V1) */
        
        uint32 hsiomSel[UVSensor_SCB_PINS_NUMBER] = 
        {
            UVSensor_RX_SCL_MOSI_HSIOM_SEL_GPIO,
            UVSensor_TX_SDA_MISO_HSIOM_SEL_GPIO,
            0u,
            0u,
            0u,
            0u,
            0u,
        };

    #if (UVSensor_CY_SCBIP_V1)
        /* Supress compiler warning. */
        if ((0u == subMode) || (0u == uartEnableMask))
        {
        }
    #endif /* (UVSensor_CY_SCBIP_V1) */

        /* Set default HSIOM to GPIO and Drive Mode to Analog Hi-Z */
        for (i = 0u; i < UVSensor_SCB_PINS_NUMBER; i++)
        {
            pinsDm[i] = UVSensor_PIN_DM_ALG_HIZ;
        }

        if ((UVSensor_SCB_MODE_I2C   == mode) ||
            (UVSensor_SCB_MODE_EZI2C == mode))
        {
        #if (UVSensor_RX_SCL_MOSI_PIN)
            hsiomSel[UVSensor_RX_SCL_MOSI_PIN_INDEX] = UVSensor_RX_SCL_MOSI_HSIOM_SEL_I2C;
            pinsDm  [UVSensor_RX_SCL_MOSI_PIN_INDEX] = UVSensor_PIN_DM_OD_LO;
        #elif (UVSensor_RX_WAKE_SCL_MOSI_PIN)
            hsiomSel[UVSensor_RX_WAKE_SCL_MOSI_PIN_INDEX] = UVSensor_RX_WAKE_SCL_MOSI_HSIOM_SEL_I2C;
            pinsDm  [UVSensor_RX_WAKE_SCL_MOSI_PIN_INDEX] = UVSensor_PIN_DM_OD_LO;
        #else
        #endif /* (UVSensor_RX_SCL_MOSI_PIN) */
        
        #if (UVSensor_TX_SDA_MISO_PIN)
            hsiomSel[UVSensor_TX_SDA_MISO_PIN_INDEX] = UVSensor_TX_SDA_MISO_HSIOM_SEL_I2C;
            pinsDm  [UVSensor_TX_SDA_MISO_PIN_INDEX] = UVSensor_PIN_DM_OD_LO;
        #endif /* (UVSensor_TX_SDA_MISO_PIN) */
        }
    #if (!UVSensor_CY_SCBIP_V1)
        else if (UVSensor_SCB_MODE_SPI == mode)
        {
        #if (UVSensor_RX_SCL_MOSI_PIN)
            hsiomSel[UVSensor_RX_SCL_MOSI_PIN_INDEX] = UVSensor_RX_SCL_MOSI_HSIOM_SEL_SPI;
        #elif (UVSensor_RX_WAKE_SCL_MOSI_PIN)
            hsiomSel[UVSensor_RX_WAKE_SCL_MOSI_PIN_INDEX] = UVSensor_RX_WAKE_SCL_MOSI_HSIOM_SEL_SPI;
        #else
        #endif /* (UVSensor_RX_SCL_MOSI_PIN) */
        
        #if (UVSensor_TX_SDA_MISO_PIN)
            hsiomSel[UVSensor_TX_SDA_MISO_PIN_INDEX] = UVSensor_TX_SDA_MISO_HSIOM_SEL_SPI;
        #endif /* (UVSensor_TX_SDA_MISO_PIN) */
        
        #if (UVSensor_CTS_SCLK_PIN)
            hsiomSel[UVSensor_CTS_SCLK_PIN_INDEX] = UVSensor_CTS_SCLK_HSIOM_SEL_SPI;
        #endif /* (UVSensor_CTS_SCLK_PIN) */

            if (UVSensor_SPI_SLAVE == subMode)
            {
                /* Slave */
                pinsDm[UVSensor_RX_SCL_MOSI_PIN_INDEX] = UVSensor_PIN_DM_DIG_HIZ;
                pinsDm[UVSensor_TX_SDA_MISO_PIN_INDEX] = UVSensor_PIN_DM_STRONG;
                pinsDm[UVSensor_CTS_SCLK_PIN_INDEX] = UVSensor_PIN_DM_DIG_HIZ;

            #if (UVSensor_RTS_SS0_PIN)
                /* Only SS0 is valid choice for Slave */
                hsiomSel[UVSensor_RTS_SS0_PIN_INDEX] = UVSensor_RTS_SS0_HSIOM_SEL_SPI;
                pinsDm  [UVSensor_RTS_SS0_PIN_INDEX] = UVSensor_PIN_DM_DIG_HIZ;
            #endif /* (UVSensor_RTS_SS0_PIN) */

            #if (UVSensor_TX_SDA_MISO_PIN)
                /* Disable input buffer */
                 pinsInBuf |= UVSensor_TX_SDA_MISO_PIN_MASK;
            #endif /* (UVSensor_TX_SDA_MISO_PIN) */
            }
            else 
            {
                /* (Master) */
                pinsDm[UVSensor_RX_SCL_MOSI_PIN_INDEX] = UVSensor_PIN_DM_STRONG;
                pinsDm[UVSensor_TX_SDA_MISO_PIN_INDEX] = UVSensor_PIN_DM_DIG_HIZ;
                pinsDm[UVSensor_CTS_SCLK_PIN_INDEX] = UVSensor_PIN_DM_STRONG;

            #if (UVSensor_RTS_SS0_PIN)
                hsiomSel [UVSensor_RTS_SS0_PIN_INDEX] = UVSensor_RTS_SS0_HSIOM_SEL_SPI;
                pinsDm   [UVSensor_RTS_SS0_PIN_INDEX] = UVSensor_PIN_DM_STRONG;
                pinsInBuf |= UVSensor_RTS_SS0_PIN_MASK;
            #endif /* (UVSensor_RTS_SS0_PIN) */

            #if (UVSensor_SS1_PIN)
                hsiomSel [UVSensor_SS1_PIN_INDEX] = UVSensor_SS1_HSIOM_SEL_SPI;
                pinsDm   [UVSensor_SS1_PIN_INDEX] = UVSensor_PIN_DM_STRONG;
                pinsInBuf |= UVSensor_SS1_PIN_MASK;
            #endif /* (UVSensor_SS1_PIN) */

            #if (UVSensor_SS2_PIN)
                hsiomSel [UVSensor_SS2_PIN_INDEX] = UVSensor_SS2_HSIOM_SEL_SPI;
                pinsDm   [UVSensor_SS2_PIN_INDEX] = UVSensor_PIN_DM_STRONG;
                pinsInBuf |= UVSensor_SS2_PIN_MASK;
            #endif /* (UVSensor_SS2_PIN) */

            #if (UVSensor_SS3_PIN)
                hsiomSel [UVSensor_SS3_PIN_INDEX] = UVSensor_SS3_HSIOM_SEL_SPI;
                pinsDm   [UVSensor_SS3_PIN_INDEX] = UVSensor_PIN_DM_STRONG;
                pinsInBuf |= UVSensor_SS3_PIN_MASK;
            #endif /* (UVSensor_SS3_PIN) */

                /* Disable input buffers */
            #if (UVSensor_RX_SCL_MOSI_PIN)
                pinsInBuf |= UVSensor_RX_SCL_MOSI_PIN_MASK;
            #elif (UVSensor_RX_WAKE_SCL_MOSI_PIN)
                pinsInBuf |= UVSensor_RX_WAKE_SCL_MOSI_PIN_MASK;
            #else
            #endif /* (UVSensor_RX_SCL_MOSI_PIN) */

            #if (UVSensor_CTS_SCLK_PIN)
                pinsInBuf |= UVSensor_CTS_SCLK_PIN_MASK;
            #endif /* (UVSensor_CTS_SCLK_PIN) */
            }
        }
        else /* UART */
        {
            if (UVSensor_UART_MODE_SMARTCARD == subMode)
            {
                /* SmartCard */
            #if (UVSensor_TX_SDA_MISO_PIN)
                hsiomSel[UVSensor_TX_SDA_MISO_PIN_INDEX] = UVSensor_TX_SDA_MISO_HSIOM_SEL_UART;
                pinsDm  [UVSensor_TX_SDA_MISO_PIN_INDEX] = UVSensor_PIN_DM_OD_LO;
            #endif /* (UVSensor_TX_SDA_MISO_PIN) */
            }
            else /* Standard or IrDA */
            {
                if (0u != (UVSensor_UART_RX_PIN_ENABLE & uartEnableMask))
                {
                #if (UVSensor_RX_SCL_MOSI_PIN)
                    hsiomSel[UVSensor_RX_SCL_MOSI_PIN_INDEX] = UVSensor_RX_SCL_MOSI_HSIOM_SEL_UART;
                    pinsDm  [UVSensor_RX_SCL_MOSI_PIN_INDEX] = UVSensor_PIN_DM_DIG_HIZ;
                #elif (UVSensor_RX_WAKE_SCL_MOSI_PIN)
                    hsiomSel[UVSensor_RX_WAKE_SCL_MOSI_PIN_INDEX] = UVSensor_RX_WAKE_SCL_MOSI_HSIOM_SEL_UART;
                    pinsDm  [UVSensor_RX_WAKE_SCL_MOSI_PIN_INDEX] = UVSensor_PIN_DM_DIG_HIZ;
                #else
                #endif /* (UVSensor_RX_SCL_MOSI_PIN) */
                }

                if (0u != (UVSensor_UART_TX_PIN_ENABLE & uartEnableMask))
                {
                #if (UVSensor_TX_SDA_MISO_PIN)
                    hsiomSel[UVSensor_TX_SDA_MISO_PIN_INDEX] = UVSensor_TX_SDA_MISO_HSIOM_SEL_UART;
                    pinsDm  [UVSensor_TX_SDA_MISO_PIN_INDEX] = UVSensor_PIN_DM_STRONG;
                    
                    /* Disable input buffer */
                    pinsInBuf |= UVSensor_TX_SDA_MISO_PIN_MASK;
                #endif /* (UVSensor_TX_SDA_MISO_PIN) */
                }

            #if !(UVSensor_CY_SCBIP_V0 || UVSensor_CY_SCBIP_V1)
                if (UVSensor_UART_MODE_STD == subMode)
                {
                    if (0u != (UVSensor_UART_CTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* CTS input is multiplexed with SCLK */
                    #if (UVSensor_CTS_SCLK_PIN)
                        hsiomSel[UVSensor_CTS_SCLK_PIN_INDEX] = UVSensor_CTS_SCLK_HSIOM_SEL_UART;
                        pinsDm  [UVSensor_CTS_SCLK_PIN_INDEX] = UVSensor_PIN_DM_DIG_HIZ;
                    #endif /* (UVSensor_CTS_SCLK_PIN) */
                    }

                    if (0u != (UVSensor_UART_RTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* RTS output is multiplexed with SS0 */
                    #if (UVSensor_RTS_SS0_PIN)
                        hsiomSel[UVSensor_RTS_SS0_PIN_INDEX] = UVSensor_RTS_SS0_HSIOM_SEL_UART;
                        pinsDm  [UVSensor_RTS_SS0_PIN_INDEX] = UVSensor_PIN_DM_STRONG;
                        
                        /* Disable input buffer */
                        pinsInBuf |= UVSensor_RTS_SS0_PIN_MASK;
                    #endif /* (UVSensor_RTS_SS0_PIN) */
                    }
                }
            #endif /* !(UVSensor_CY_SCBIP_V0 || UVSensor_CY_SCBIP_V1) */
            }
        }
    #endif /* (!UVSensor_CY_SCBIP_V1) */

    /* Configure pins: set HSIOM, DM and InputBufEnable */
    /* Note: the DR register settings do not effect the pin output if HSIOM is other than GPIO */

    #if (UVSensor_RX_SCL_MOSI_PIN)
        UVSensor_SET_HSIOM_SEL(UVSensor_RX_SCL_MOSI_HSIOM_REG,
                                       UVSensor_RX_SCL_MOSI_HSIOM_MASK,
                                       UVSensor_RX_SCL_MOSI_HSIOM_POS,
                                        hsiomSel[UVSensor_RX_SCL_MOSI_PIN_INDEX]);

        UVSensor_uart_rx_i2c_scl_spi_mosi_SetDriveMode((uint8) pinsDm[UVSensor_RX_SCL_MOSI_PIN_INDEX]);

        #if (!UVSensor_CY_SCBIP_V1)
            UVSensor_SET_INP_DIS(UVSensor_uart_rx_i2c_scl_spi_mosi_INP_DIS,
                                         UVSensor_uart_rx_i2c_scl_spi_mosi_MASK,
                                         (0u != (pinsInBuf & UVSensor_RX_SCL_MOSI_PIN_MASK)));
        #endif /* (!UVSensor_CY_SCBIP_V1) */
    
    #elif (UVSensor_RX_WAKE_SCL_MOSI_PIN)
        UVSensor_SET_HSIOM_SEL(UVSensor_RX_WAKE_SCL_MOSI_HSIOM_REG,
                                       UVSensor_RX_WAKE_SCL_MOSI_HSIOM_MASK,
                                       UVSensor_RX_WAKE_SCL_MOSI_HSIOM_POS,
                                       hsiomSel[UVSensor_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        UVSensor_uart_rx_wake_i2c_scl_spi_mosi_SetDriveMode((uint8)
                                                               pinsDm[UVSensor_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        UVSensor_SET_INP_DIS(UVSensor_uart_rx_wake_i2c_scl_spi_mosi_INP_DIS,
                                     UVSensor_uart_rx_wake_i2c_scl_spi_mosi_MASK,
                                     (0u != (pinsInBuf & UVSensor_RX_WAKE_SCL_MOSI_PIN_MASK)));

         /* Set interrupt on falling edge */
        UVSensor_SET_INCFG_TYPE(UVSensor_RX_WAKE_SCL_MOSI_INTCFG_REG,
                                        UVSensor_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK,
                                        UVSensor_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS,
                                        UVSensor_INTCFG_TYPE_FALLING_EDGE);
    #else
    #endif /* (UVSensor_RX_WAKE_SCL_MOSI_PIN) */

    #if (UVSensor_TX_SDA_MISO_PIN)
        UVSensor_SET_HSIOM_SEL(UVSensor_TX_SDA_MISO_HSIOM_REG,
                                       UVSensor_TX_SDA_MISO_HSIOM_MASK,
                                       UVSensor_TX_SDA_MISO_HSIOM_POS,
                                        hsiomSel[UVSensor_TX_SDA_MISO_PIN_INDEX]);

        UVSensor_uart_tx_i2c_sda_spi_miso_SetDriveMode((uint8) pinsDm[UVSensor_TX_SDA_MISO_PIN_INDEX]);

    #if (!UVSensor_CY_SCBIP_V1)
        UVSensor_SET_INP_DIS(UVSensor_uart_tx_i2c_sda_spi_miso_INP_DIS,
                                     UVSensor_uart_tx_i2c_sda_spi_miso_MASK,
                                    (0u != (pinsInBuf & UVSensor_TX_SDA_MISO_PIN_MASK)));
    #endif /* (!UVSensor_CY_SCBIP_V1) */
    #endif /* (UVSensor_RX_SCL_MOSI_PIN) */

    #if (UVSensor_CTS_SCLK_PIN)
        UVSensor_SET_HSIOM_SEL(UVSensor_CTS_SCLK_HSIOM_REG,
                                       UVSensor_CTS_SCLK_HSIOM_MASK,
                                       UVSensor_CTS_SCLK_HSIOM_POS,
                                       hsiomSel[UVSensor_CTS_SCLK_PIN_INDEX]);

        UVSensor_uart_cts_spi_sclk_SetDriveMode((uint8) pinsDm[UVSensor_CTS_SCLK_PIN_INDEX]);

        UVSensor_SET_INP_DIS(UVSensor_uart_cts_spi_sclk_INP_DIS,
                                     UVSensor_uart_cts_spi_sclk_MASK,
                                     (0u != (pinsInBuf & UVSensor_CTS_SCLK_PIN_MASK)));
    #endif /* (UVSensor_CTS_SCLK_PIN) */

    #if (UVSensor_RTS_SS0_PIN)
        UVSensor_SET_HSIOM_SEL(UVSensor_RTS_SS0_HSIOM_REG,
                                       UVSensor_RTS_SS0_HSIOM_MASK,
                                       UVSensor_RTS_SS0_HSIOM_POS,
                                       hsiomSel[UVSensor_RTS_SS0_PIN_INDEX]);

        UVSensor_uart_rts_spi_ss0_SetDriveMode((uint8) pinsDm[UVSensor_RTS_SS0_PIN_INDEX]);

        UVSensor_SET_INP_DIS(UVSensor_uart_rts_spi_ss0_INP_DIS,
                                     UVSensor_uart_rts_spi_ss0_MASK,
                                     (0u != (pinsInBuf & UVSensor_RTS_SS0_PIN_MASK)));
    #endif /* (UVSensor_RTS_SS0_PIN) */

    #if (UVSensor_SS1_PIN)
        UVSensor_SET_HSIOM_SEL(UVSensor_SS1_HSIOM_REG,
                                       UVSensor_SS1_HSIOM_MASK,
                                       UVSensor_SS1_HSIOM_POS,
                                       hsiomSel[UVSensor_SS1_PIN_INDEX]);

        UVSensor_spi_ss1_SetDriveMode((uint8) pinsDm[UVSensor_SS1_PIN_INDEX]);

        UVSensor_SET_INP_DIS(UVSensor_spi_ss1_INP_DIS,
                                     UVSensor_spi_ss1_MASK,
                                     (0u != (pinsInBuf & UVSensor_SS1_PIN_MASK)));
    #endif /* (UVSensor_SS1_PIN) */

    #if (UVSensor_SS2_PIN)
        UVSensor_SET_HSIOM_SEL(UVSensor_SS2_HSIOM_REG,
                                       UVSensor_SS2_HSIOM_MASK,
                                       UVSensor_SS2_HSIOM_POS,
                                       hsiomSel[UVSensor_SS2_PIN_INDEX]);

        UVSensor_spi_ss2_SetDriveMode((uint8) pinsDm[UVSensor_SS2_PIN_INDEX]);

        UVSensor_SET_INP_DIS(UVSensor_spi_ss2_INP_DIS,
                                     UVSensor_spi_ss2_MASK,
                                     (0u != (pinsInBuf & UVSensor_SS2_PIN_MASK)));
    #endif /* (UVSensor_SS2_PIN) */

    #if (UVSensor_SS3_PIN)
        UVSensor_SET_HSIOM_SEL(UVSensor_SS3_HSIOM_REG,
                                       UVSensor_SS3_HSIOM_MASK,
                                       UVSensor_SS3_HSIOM_POS,
                                       hsiomSel[UVSensor_SS3_PIN_INDEX]);

        UVSensor_spi_ss3_SetDriveMode((uint8) pinsDm[UVSensor_SS3_PIN_INDEX]);

        UVSensor_SET_INP_DIS(UVSensor_spi_ss3_INP_DIS,
                                     UVSensor_spi_ss3_MASK,
                                     (0u != (pinsInBuf & UVSensor_SS3_PIN_MASK)));
    #endif /* (UVSensor_SS3_PIN) */
    }

#endif /* (UVSensor_SCB_MODE_UNCONFIG_CONST_CFG) */


#if (UVSensor_CY_SCBIP_V0 || UVSensor_CY_SCBIP_V1)
    /*******************************************************************************
    * Function Name: UVSensor_I2CSlaveNackGeneration
    ****************************************************************************//**
    *
    *  Sets command to generate NACK to the address or data.
    *
    *******************************************************************************/
    void UVSensor_I2CSlaveNackGeneration(void)
    {
        /* Check for EC_AM toggle condition: EC_AM and clock stretching for address are enabled */
        if ((0u != (UVSensor_CTRL_REG & UVSensor_CTRL_EC_AM_MODE)) &&
            (0u == (UVSensor_I2C_CTRL_REG & UVSensor_I2C_CTRL_S_NOT_READY_ADDR_NACK)))
        {
            /* Toggle EC_AM before NACK generation */
            UVSensor_CTRL_REG &= ~UVSensor_CTRL_EC_AM_MODE;
            UVSensor_CTRL_REG |=  UVSensor_CTRL_EC_AM_MODE;
        }

        UVSensor_I2C_SLAVE_CMD_REG = UVSensor_I2C_SLAVE_CMD_S_NACK;
    }
#endif /* (UVSensor_CY_SCBIP_V0 || UVSensor_CY_SCBIP_V1) */


/* [] END OF FILE */
