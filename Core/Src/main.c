/*
 * main.c
 *
 *
 *   Author: Mario Aguilar<fernandoaguilar731010@gmail.com>
 *   Created on: Aug 17, 2021
 */

#include "main.h"

/*Crea los prototipos de las funciones y variables del modulo*/
static void SystemClock_Config(void);

//static void Configuracion_GPIO_Init(void);
static uint8_t sensor;
static uint16_t lectura ;

/*Enumerador que contiene los estados de la maquina principal*/
typedef enum
{
	INICIAL,
	ESPERA,
	LECTURA,
	CONVERSION,
	ENVIO

}Sensor_Estados;



/*MAIN----------*/
int main(void)
{

	Sensor_Estados Sensor_Humedad_Estados=INICIAL;

/*Bucle infinito */
while(1)
{

	  switch (Sensor_Humedad_Estados) {

	  /*Estado Inicial :Configuracion de los perifericos*/
		case INICIAL:

			  // Configura el  system clock
			  SystemClock_Config();
			  // Configura todos los perifericos

			  Configuracion_UART_Init();
			  Configuracion_ADC1_Init();
			  Configuracion_TIM2_Init();

			  /* Inicializa el TIMER*/
			  StartTimer();
			  /*Cambio de Estado*/
			  Sensor_Humedad_Estados=ESPERA;
			break;

		case ESPERA:
			/*Estado ESPERA :Espera por la interrupcion del TIMER*/
			if(timer2flag==OK){
				Sensor_Humedad_Estados=LECTURA;
				}
				break;

		case LECTURA:
			/*Estado LECTURA :Lee el puerto del ADC*/
			lectura =ADC_Read();

			if(lectura>=0 &&  lectura<=4095)
			{
				Sensor_Humedad_Estados=CONVERSION;
			}
			else
			{
				Sensor_Humedad_Estados=ESPERA;
			}
					break;
		case CONVERSION:
			/*Estado CONVERSION:Convierte el valor de la señal analogica a un valor representativo de la humedad*/

			sensor =ADC_Converter(lectura);
			if(sensor>=0 && sensor <=100  )
			{
				Sensor_Humedad_Estados=ENVIO;
			}
			else
			{
			Sensor_Humedad_Estados=LECTURA;
			}
					break;
		case ENVIO:
			/*Estado ENVIO:Envia los datos por el puerto serial */

			if(UART_Write(sensor)==OK)
			{
				Sensor_Humedad_Estados=ESPERA;

			}
			else
			{
				Sensor_Humedad_Estados=LECTURA;
			}

			timer2flag=ERROR;
					break;
		default:
			break;
	}
  }
}
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV8;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV8;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC12;
  PeriphClkInit.Adc12ClockSelection = RCC_ADC12PLLCLK_DIV4;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

