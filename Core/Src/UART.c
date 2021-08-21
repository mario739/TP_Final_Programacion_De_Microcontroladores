/*
 * UART.c
 *
 *
 *   Author: Mario Aguilar<fernandoaguilar731010@gmail.com>
 *   Created on: Aug 17, 2021
 */


#include "UART.h"


static uint8_t txbufferADC[30];
static uint16_t num;



void Configuracion_UART_Init(void)
{
	/* Configuracion del UART */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
    {
      Error_Handler();
    }
}
/* Configuracion del UART */

uint8_t UART_Write(uint8_t valor)
{
	num=sprintf(txbufferADC,"valor adc:%u\n",valor);
	HAL_UART_Transmit(&huart2,txbufferADC,num,100);
	return 1;
}
