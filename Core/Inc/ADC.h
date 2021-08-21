/*
 *   ADC.h
 *
 *
 *   Author: Mario Aguilar<fernandoaguilar731010@gmail.com>
 *   Created on: Aug 17, 2021
 */
#ifndef INC_ADC_H_
#define INC_ADC_H_
#include "stm32f3xx_hal.h"


/*Configura el ADC1*/
void Configuracion_ADC1_Init(void);

/*Realiza la seguencia para la lectura del ADC*/
uint16_t ADC_Read();
/*Convierte la señal en un valor represetativo de la humedad*/
uint8_t ADC_Converter(uint16_t sensor);

uint8_t Enviar_Datos_Convertidos(uint8_t temperatura);


ADC_HandleTypeDef hadc1;


#endif /* INC_ADC_H_ */
