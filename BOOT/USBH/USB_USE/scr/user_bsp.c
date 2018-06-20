#include "usb_bsp.h"

/***********************回调函数中延时ms/us宏****************************************/
#define USE_ACCURATE_TIME
#define TIM_MSEC_DELAY                     0x01
#define TIM_USEC_DELAY                     0x02
/**************************************************************************/
//#define HOST_OVRCURR_PORT                  GPIOE
//#define HOST_OVRCURR_LINE                  GPIO_Pin_1
//#define HOST_OVRCURR_PORT_SOURCE           GPIO_PortSourceGPIOE
//#define HOST_OVRCURR_PIN_SOURCE            GPIO_PinSource1
//#define HOST_OVRCURR_PORT_RCC              RCC_APB2Periph_GPIOE
//#define HOST_OVRCURR_EXTI_LINE             EXTI_Line1
//#define HOST_OVRCURR_IRQn                  EXTI1_IRQn 

//#define HOST_POWERSW_PORT_RCC             RCC_APB2Periph_GPIOC
//#define HOST_POWERSW_PORT                 GPIOC
//#define HOST_POWERSW_VBUS                 GPIO_Pin_9

//#define HOST_SOF_OUTPUT_RCC                RCC_APB2Periph_GPIOA
//#define HOST_SOF_PORT                      GPIOA
//#define HOST_SOF_SIGNAL                    GPIO_Pin_8


/**************************************************************************/


ErrorStatus HSEStartUpStatus;
#ifdef USE_ACCURATE_TIME 
__IO uint32_t BSP_delay = 0;
#endif

#ifdef USE_ACCURATE_TIME 
static void BSP_SetTime(uint8_t Unit);
static void BSP_Delay(uint32_t nTime,uint8_t Unit);
static void USB_OTG_BSP_TimeInit ( void );
#endif


/** @defgroup USB_BSP_Private_Functions
  * @{
  */ 
/**
  * @brief  USB_OTG_BSP_TimerIRQ
  *         Time base IRQ
  * @param  None
  * @retval None
  */

void USB_OTG_BSP_TimerIRQ (void)
{
	#ifdef OS_TICKS_PER_SEC	 	//如果时钟节拍数定义了,说明要使用ucosII了.
	OSIntEnter();    
#endif
#ifdef USE_ACCURATE_TIME 
  if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)
  {
    TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
    if (BSP_delay > 0x00)
    { 
      BSP_delay--;
    }
    else
    {
      TIM_Cmd(TIM6,DISABLE);
    }
  }
#endif  
  #ifdef OS_TICKS_PER_SEC	 	//如果时钟节拍数定义了,说明要使用ucosII了.
	OSIntExit();  											 
#endif
} 
/**
  * @brief  USB_OTG_BSP_Init
  *         Initilizes BSP configurations
  * @param  None
  * @retval None
  */

void USB_OTG_BSP_Init(USB_OTG_CORE_HANDLE *pdev)
{

// EXTI_InitTypeDef EXTI_InitStructure;

//  RCC_OTGFSCLKConfig(RCC_OTGFSCLKSource_PLLVCO_Div3);
//  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_OTG_FS, ENABLE) ;

//  
//  /* Configure pin for overcurrent detection */
//  RCC_APB2PeriphClockCmd(HOST_OVRCURR_PORT_RCC, ENABLE);
//  
//  /* Configure SOF Pin */
//  GPIO_InitStructure.GPIO_Pin = HOST_OVRCURR_LINE;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
//  GPIO_Init(HOST_OVRCURR_PORT, &GPIO_InitStructure);
//  
//  /* Connect Button EXTI Line to Button GPIO Pin */
//  GPIO_EXTILineConfig(HOST_OVRCURR_PORT_SOURCE, HOST_OVRCURR_PIN_SOURCE);  
//  
//  /* Configure Button EXTI line */
//  EXTI_InitStructure.EXTI_Line = HOST_OVRCURR_EXTI_LINE;
//  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;  
//  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; 
//  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//  EXTI_Init(&EXTI_InitStructure);
   USB_OTG_BSP_TimeInit();
}
/**
  * @brief  USB_OTG_BSP_TimeInit
  *         Initializes delay unit using Timer2
  * @param  None
  * @retval None
  */
static void USB_OTG_BSP_TimeInit ( void )
{
#ifdef USE_ACCURATE_TIME   
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Set the Vector Table base address at 0x08000000 */
//  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x00);
  
  /* Configure the Priority Group to 1 bits */
//  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);  
  /* Enable the TIM6 gloabal Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  
  NVIC_Init(&NVIC_InitStructure);
  
  
#endif  
}
/**
  * @brief  USB_OTG_BSP_EnableInterrupt
  *         Configures USB Global interrupt
  * @param  None
  * @retval None
  */
void USB_OTG_BSP_EnableInterrupt(USB_OTG_CORE_HANDLE *pdev)
{
  NVIC_InitTypeDef NVIC_InitStructure; 
  
//  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
//#ifdef USE_USB_OTG_HS   
//  NVIC_InitStructure.NVIC_IRQChannel = OTG_HS_IRQn;
//#else
  NVIC_InitStructure.NVIC_IRQChannel = OTG_FS_IRQn;  
//#endif
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);  

//  
//  /* Enable the Overcurrent Interrupt */
//  NVIC_InitStructure.NVIC_IRQChannel = HOST_OVRCURR_IRQn;
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  
//  NVIC_Init(&NVIC_InitStructure);  
}

/**
  * @brief  BSP_Drive_VBUS
  *         Drives the Vbus signal through IO
  * @param  state : VBUS states
  * @retval None
  */

void USB_OTG_BSP_DriveVBUS(USB_OTG_CORE_HANDLE *pdev, uint8_t state)
{
  /*
  On-chip 5 V VBUS generation is not supported. For this reason, a charge pump 
  or, if 5 V are available on the application board, a basic power switch, must 
  be added externally to drive the 5 V VBUS line. The external charge pump can 
  be driven by any GPIO output. When the application decides to power on VBUS 
  using the chosen GPIO, it must also set the port power bit in the host port 
  control and status register (PPWR bit in OTG_FS_HPRT).
  
  Bit 12 PPWR: Port power
  The application uses this field to control power to this port, and the core 
  clears this bit on an overcurrent condition.
  */
//#ifndef USE_USB_OTG_HS   
//  if (0 == state)
//  { 
//    /* DISABLE is needed on output of the Power Switch */
//    GPIO_SetBits(HOST_POWERSW_PORT, HOST_POWERSW_VBUS);
//  }
//  else
//  {
//    /*ENABLE the Power Switch by driving the Enable LOW */
//    GPIO_ResetBits(HOST_POWERSW_PORT, HOST_POWERSW_VBUS);
//  }
//#endif  
}

/**
  * @brief  USB_OTG_BSP_ConfigVBUS
  *         Configures the IO for the Vbus and OverCurrent
  * @param  None
  * @retval None
  */

void  USB_OTG_BSP_ConfigVBUS(USB_OTG_CORE_HANDLE *pdev)
{
//#ifdef USE_USB_OTG_FS   
//  GPIO_InitTypeDef GPIO_InitStructure; 
//  
//  RCC_APB2PeriphClockCmd(HOST_POWERSW_PORT_RCC, ENABLE);
//  
//  
//  /* Configure Power Switch Vbus Pin */
//  GPIO_InitStructure.GPIO_Pin = HOST_POWERSW_VBUS;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//  GPIO_Init(HOST_POWERSW_PORT, &GPIO_InitStructure);

//  /* By Default, DISABLE is needed on output of the Power Switch */
//  GPIO_SetBits(HOST_POWERSW_PORT, HOST_POWERSW_VBUS);
  
//  USB_OTG_BSP_mDelay(200);  
	/* Delay is need for stabilising the Vbus Low 
  in Reset Condition, when Vbus=1 and Reset-button is pressed by user */
//#endif  
}

#ifdef USE_ACCURATE_TIME 

/**
  * @brief  BSP_SetTime
  *         Configures TIM2 for delay routine based on TIM2
  * @param  unit : msec /usec
  * @retval None
  */
static void BSP_SetTime(uint8_t unit)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  
  TIM_Cmd(TIM6,DISABLE);
  TIM_ITConfig(TIM6, TIM_IT_Update, DISABLE); 
  
  
  if(unit == TIM_USEC_DELAY)
  {  
    TIM_TimeBaseStructure.TIM_Period = 11;
  }
  else if(unit == TIM_MSEC_DELAY)
  {
    TIM_TimeBaseStructure.TIM_Period = 11999;
  }
  TIM_TimeBaseStructure.TIM_Prescaler = 5;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  
  TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);
  TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
  
  TIM_ARRPreloadConfig(TIM6, ENABLE);
  
  /* TIM IT enable */
  TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);
  
  /* TIM2 enable counter */ 
  TIM_Cmd(TIM6, ENABLE);  
} 

/**
  * @brief  BSP_Delay
  *         Delay routine based on TIM2
  * @param  nTime : Delay Time 
  * @param  unit : Delay Time unit : mili sec / micro sec
  * @retval None
  */
static void BSP_Delay(uint32_t nTime, uint8_t unit)
{
  
  BSP_delay = nTime;
  BSP_SetTime(unit);  
  while(BSP_delay != 0);
  TIM_Cmd(TIM6,DISABLE);
}

#endif

/**
  * @brief  USB_OTG_BSP_mDelay
  *          This function provides delay time in milli sec
  * @param  msec : Value of delay required in milli sec
  * @retval None
  */
void USB_OTG_BSP_mDelay (const uint32_t msec)
{ 
#ifdef USE_ACCURATE_TIME  
    BSP_Delay(msec,TIM_MSEC_DELAY);   
#else
    USB_OTG_BSP_uDelay(msec * 1000);   
#endif    

}

/**
  * @brief  USB_OTG_BSP_uDelay
  *         This function provides delay time in micro sec
  * @param  usec : Value of delay required in micro sec
  * @retval None
  */
void USB_OTG_BSP_uDelay (const uint32_t usec)
{
//  
//#ifdef USE_ACCURATE_TIME    
  BSP_Delay(usec,TIM_USEC_DELAY); 
//#else
//  __IO uint32_t count = 0;
//  const uint32_t utime = (120 * usec / 7);
//  do
//  {
//    if ( ++count > utime )
//    {
//      return ;
//    }
//  }
//  while (1);
//#endif   
  
}

void TIM6_IRQHandler()
{
	USB_OTG_BSP_TimerIRQ();	
}












