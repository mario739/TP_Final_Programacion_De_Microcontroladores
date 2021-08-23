/*
 *   ADC.c
 *
 *
 *   Author: Mario Aguilar<fernandoaguilar731010@gmail.com>
 *   Created on: Aug 17, 2021
 */

#include "ADC.h"
//Se crean variables 
static uint16_t valor;
static uint8_t humedad;

//Realiza la configuracion del ADC
void Configuracion_ADC1_Init(void)
{
  ADC_MultiModeTypeDef multimode = {0};
  ADC_ChannelConfTypeDef sConfig = {0};
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc1.Init.LowPowerAutoWait = DISABLE;
  hadc1.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
  multimode.Mode = ADC_MODE_INDEPENDENT;

  sConfig.Channel =  ADC_CHANNEL_1;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
}

//Realiza la lectura del ADC
uint16_t ADC_Read()
{
	HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1,100);
    valor=HAL_ADC_GetValue(&hadc1);
    return valor;
}
//Convierte la señal en un valor porcentual
uint8_t ADC_Converter(uint16_t sensor)
{
	humedad=(((sensor*100)/4095));
	return humedad;
}
