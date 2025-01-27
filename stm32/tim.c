/**
  ******************************************************************************
  * File Name          : TIM.c
  * Description        : This file provides code for the configuration
  *                      of the TIM instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "tim.h"

/**
 * @brief MX_TIM1_Init 1Khz
 */
void MX_TIM_Init(void)
{
	{
  LL_TIM_InitTypeDef TIM_InitStruct = {0};
  LL_TIM_OC_InitTypeDef TIM_OC_InitStruct = {0};
  LL_TIM_BDTR_InitTypeDef TIM_BDTRInitStruct = {0};

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* Peripheral clock enable */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM1);

  TIM_InitStruct.Prescaler = 71;
  TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
  TIM_InitStruct.Autoreload = 1000-1;
  TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
  TIM_InitStruct.RepetitionCounter = 0;
  LL_TIM_Init(TIM1, &TIM_InitStruct);
  LL_TIM_DisableARRPreload(TIM1);
  LL_TIM_OC_EnablePreload(TIM1, LL_TIM_CHANNEL_CH1);
  TIM_OC_InitStruct.OCMode = LL_TIM_OCMODE_PWM1;
  TIM_OC_InitStruct.OCState = LL_TIM_OCSTATE_DISABLE;
  TIM_OC_InitStruct.OCNState = LL_TIM_OCSTATE_DISABLE;
  TIM_OC_InitStruct.CompareValue = 0;
  TIM_OC_InitStruct.OCPolarity = LL_TIM_OCPOLARITY_HIGH;
  TIM_OC_InitStruct.OCNPolarity = LL_TIM_OCPOLARITY_HIGH;
  TIM_OC_InitStruct.OCIdleState = LL_TIM_OCIDLESTATE_LOW;
  TIM_OC_InitStruct.OCNIdleState = LL_TIM_OCIDLESTATE_LOW;
  LL_TIM_OC_Init(TIM1, LL_TIM_CHANNEL_CH1, &TIM_OC_InitStruct);
  LL_TIM_OC_DisableFast(TIM1, LL_TIM_CHANNEL_CH1);
  LL_TIM_SetTriggerOutput(TIM1, LL_TIM_TRGO_RESET);
  LL_TIM_DisableMasterSlaveMode(TIM1);
  TIM_BDTRInitStruct.OSSRState = LL_TIM_OSSR_DISABLE;
  TIM_BDTRInitStruct.OSSIState = LL_TIM_OSSI_DISABLE;
  TIM_BDTRInitStruct.LockLevel = LL_TIM_LOCKLEVEL_OFF;
  TIM_BDTRInitStruct.DeadTime = 0;
  TIM_BDTRInitStruct.BreakState = LL_TIM_BREAK_DISABLE;
  TIM_BDTRInitStruct.BreakPolarity = LL_TIM_BREAK_POLARITY_HIGH;
  TIM_BDTRInitStruct.AutomaticOutput = LL_TIM_AUTOMATICOUTPUT_DISABLE;
  LL_TIM_BDTR_Init(TIM1, &TIM_BDTRInitStruct);
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
    /**TIM1 GPIO Configuration
    PA8     ------> TIM1_CH1
    */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_8;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

  {
      NVIC_SetPriority(TIM2_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),STEP_SET_TIMER_PR, 0));
      LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);	//TIM3时钟使能
	  TIM2->ARR=0;
	  TIM2->PSC=0;
	  TIM2->DIER|=1<<0;   //允许更新中断
	  TIM2->CR1|=0x01;    //使能定时器3
//    LL_TIM_InitTypeDef TIM_InitStruct = {0};
//
//    /* Peripheral clock enable */
//    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);
//
//    /* TIM2 interrupt Init */
//    NVIC_SetPriority(TIM2_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),STEP_SET_TIMER_PR, 0));
//    NVIC_EnableIRQ(TIM2_IRQn);
//
//    TIM_InitStruct.Prescaler = 0;
//    TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
//    TIM_InitStruct.Autoreload = 0;
//    TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
//    LL_TIM_Init(TIM2, &TIM_InitStruct);
//    LL_TIM_DisableARRPreload(TIM2);
//    LL_TIM_SetClockSource(TIM2, LL_TIM_CLOCKSOURCE_INTERNAL);
//    LL_TIM_SetTriggerOutput(TIM2, LL_TIM_TRGO_RESET);
//    LL_TIM_DisableMasterSlaveMode(TIM2);
   }

    {
//      LL_TIM_InitTypeDef TIM_InitStruct = {0};

      /* Peripheral clock enable */
//      LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);

      /* TIM3 interrupt Init */
      NVIC_SetPriority(TIM3_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),STEP_RESET_TIMER_PR, 0));
      RCC->APB1ENR|=1<<1;	//TIM3时钟使能
	  TIM3->ARR=0;
	  TIM3->PSC=0;
	  TIM3->DIER|=1<<0;   //允许更新中断
	  TIM3->CR1|=0x01;    //使能定时器3
//      NVIC_EnableIRQ(TIM3_IRQn);

//      TIM_InitStruct.Prescaler = 0;
//      TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
//      TIM_InitStruct.Autoreload = 0;
//      TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
//      LL_TIM_Init(TIM3, &TIM_InitStruct);
//      LL_TIM_DisableARRPreload(TIM3);
//      LL_TIM_SetClockSource(TIM3, LL_TIM_CLOCKSOURCE_INTERNAL);
//      LL_TIM_SetTriggerOutput(TIM3, LL_TIM_TRGO_RESET);
//      LL_TIM_DisableMasterSlaveMode(TIM3);
    }
}
