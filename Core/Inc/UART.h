/*
 * UART.h
 *
 *  Author: Mario Aguilar<fernandoaguilar731010@gmail.com>
 *  Created on: Aug 17, 2021
 */

#ifndef INC_UART_H_
#define INC_UART_H_
#include <stdint.h>
#include <stdio.h>
#include "stm32f3xx_hal.h"

/*Configura el UART*/
void Configuracion_UART_Init(void);
/*Escribe un datos por el UART*/
uint8_t UART_Write(uint8_t valor);

UART_HandleTypeDef huart2;

#endif /* INC_UART_H_ */
