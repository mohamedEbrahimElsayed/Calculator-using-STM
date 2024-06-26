/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "arith_func.h"
#include "conversion.h"
#include "Error_handling.h"
#include "keypad.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void uart_string (char *str)
	{         //dispal string on screen
		int i;
		for(i=0;str[i]!=0;i++){   //send each character of the string till the null
			HAL_UART_Transmit(&huart1,&str[i], 1, 100);
			DELAY(4);
		}
	}
void clear()
{
	uint8_t clear='c';
	HAL_UART_Transmit(&huart1,&clear, 1, 100);
}


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
	/* USER CODE BEGIN 1 */
			uint8_t operand1_hex[3]={0,0,0};
			uint8_t operand2_hex[3]={0,0,0};
			uint8_t opration_sign=0;
			uint8_t count,equal_sgin,Error_flag[4];
		    int operand1_dec,operand2_dec,result_dec,result_float=0;
		    uint8_t result_hex[3]={0,0,0};
		    uint8_t result_hex_float[3]={0,0,0};
		    uint8_t size,flag=0;
		    uint8_t da='o';



	  /* USER CODE END 1 */

	  /* MCU Configuration--------------------------------------------------------*/

	  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	  HAL_Init();

	  /* USER CODE BEGIN Init */

	  /* USER CODE END Init */

	  /* Configure the system clock */
	  SystemClock_Config();

	  /* USER CODE BEGIN SysInit */

	  /* USER CODE END SysInit */

	  /* Initialize all configured peripherals */
	  MX_GPIO_Init();
	  MX_USART1_UART_Init();
	  /* USER CODE BEGIN 2 */

	  /* USER CODE END 2 */

	  /* Infinite loop */
	  /* USER CODE BEGIN WHILE */
	  while (1)
	  {
		  while(1)
		  {
	    /* USER CODE END WHILE */
		  for ( count = 0; count < 3; count++)
		     {
		     operand1_hex[count]=Keypad_GetVal();
		     if (operand1_hex[count]=='c')
		     {
		    	 flag=1;
		         break;

		     }
		     else
		     {
		    	 HAL_UART_Transmit(&huart1,&operand1_hex[count], 1, 100);
		    	 flag=0;
		     }
		     }

			if(flag!=0)
			{
			clear();
			break;
			}

		  opration_sign=Keypad_GetVal();
		  if(opration_sign=='c')
		  {
			  clear();
			  break;
		  }
		  else
		  {
			  HAL_UART_Transmit(&huart1,&opration_sign,1, 100);
		  }


		  for ( count = 0; count < 3; count++)
		  	     {
		  	     operand2_hex[count]=Keypad_GetVal();
		  	     if (operand2_hex[count]=='c')
		  	     {
		  	         flag=1;
		  	         break;

		  	     }
		  	     else
		  	     {
		  	    	 HAL_UART_Transmit(&huart1,&operand2_hex[count], 1, 100);
		  	    	 flag = 0;
		  	     }

		  	     }

			if(flag!=0)
			{
			clear();
			break;
			}

		    equal_sgin=Keypad_GetVal();
		    if (equal_sgin !='=')
		    {
		    	clear();
		       uart_string("Error\0");
		       break;
		    }
		    else
		    {
		    	HAL_UART_Transmit(&huart1,&equal_sgin, 1, 100);
		        DELAY(6);
		    }


		    Error_flag[0]=invldOpr(operand1_hex[0],operand1_hex[1],operand1_hex[2]);
		    Error_flag[1]=invldOpr(operand2_hex[0],operand2_hex[1],operand2_hex[2]);
		    Error_flag[2]=invldOpration(opration_sign);


		 	 if(Error_flag[0]==10 || Error_flag[1]==10 || Error_flag[2]==10 )
		 	    {
		 	        clear();
		 	        uart_string("INVALD\0");
		 	        break;
		 	    }

		    operand1_dec=hex_to_dec(operand1_hex[0],operand1_hex[1],operand1_hex[2]);
		    operand2_dec=hex_to_dec(operand2_hex[0],operand2_hex[1],operand2_hex[2]);
		    Error_flag[3]=divByZeroError(operand2_dec,opration_sign);

		            if(Error_flag[3]==10)
		        {
		            clear();
		            uart_string("INVALD\0");
		            break;
		        }
		            ArithFunc(operand1_dec,opration_sign,operand2_dec,&result_dec,&result_float);

		            if (operand1_dec<operand2_dec && opration_sign == '-')
		            {
		                uart_string("-\0");
		                result_dec = ~result_dec+1;
		            }
		            dec_to_hex_dec(result_dec, result_hex, &size);

		      	  for ( count = 0; count <=size; count++)
		      	  	     {
		      		HAL_UART_Transmit(&huart1, &result_hex[count], 1, 100);
		      			DELAY(5);
		      	  	     }
		      	  if(size==0)
		      	  {
		      		  	 uart_string("0\0");
		      	  }

				if(opration_sign=='/' && result_float!=0)
				{
				dec_to_hex(result_float,result_hex_float);
					uart_string(".\0");
					HAL_UART_Transmit(&huart1, &result_hex_float[0], 1, 100);
				if(result_hex_float[1] !='0' && result_hex_float[2] != '0')
				   HAL_UART_Transmit(&huart1, &result_hex_float[1], 1, 100);
				   if(result_hex_float[2]!='0')
					   HAL_UART_Transmit(&huart1, &result_hex_float[2], 1, 100);
				}



				Keypad_GetVal();
				clear();
		  }
		  Keypad_GetVal();
		  clear();

	    /* USER CODE BEGIN 3 */
	  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_12, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA0 PA1 PA2 PA3
                           PA12 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PA4 PA5 PA6 PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
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

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
