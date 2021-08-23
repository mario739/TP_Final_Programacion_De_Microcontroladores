/*
 *   Timer.h
 *
 *
 *   Author: Mario Aguilar<fernandoaguilar731010@gmail.com>
 *   Created on: Aug 17, 2021
 */
#ifndef INC_TIMER_H_
#define INC_TIMER_H_
#include "stm32f3xx_hal.h"
#include "main.h"

/*Inicializa el TIMER*/
void StartTimer(void);

/*Configuracion del TIMER*/
void Configuracion_TIM2_Init(void);

/*Funcion ISR del TIMER*:Recibe como parametro una variable tipo TIM_HandleTypeDef */
void HAL_TIM_PeriodElapsedCallback (TIM_HandleTypeDef * htim);

//Variable de tipo Timer
TIM_HandleTypeDef htim2;

/*bandera de la interrupcion */
volatile uint8_t timer2flag;

#endif /* INC_TIMER_H_ */
