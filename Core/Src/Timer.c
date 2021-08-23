/*
 *   Timer.c
 *
 *
 *   Author: Mario Aguilar<fernandoaguilar731010@gmail.com>
 *   Created on: Aug 17, 2021
 */
#include "Timer.h"

//Inicia el conteo del Timer
void StartTimer(void)
{
	HAL_TIM_Base_Start_IT (&htim2);
}
//Levanta la bandera cuando ocurre la interrupcion del Timer 
void HAL_TIM_PeriodElapsedCallback (TIM_HandleTypeDef * htim)
{
	timer2flag=1;
}
//Configura los parametros del Timer
void Configuracion_TIM2_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 64000;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 999;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
 
}
