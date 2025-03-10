/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

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
TIM_HandleTypeDef htim21;

/* USER CODE BEGIN PV */
uint8_t count 	  = 0,
		countDeca = 0,
		atualDisp = 0;

char numbers[10][7] = { {1, 1, 1, 1, 1, 1, 0},  // count = 0
						{0, 1, 1, 0, 0, 0, 0},  // count = 1
						{1, 1, 0, 1, 1, 0, 1},  // count = 2
						{1, 1, 1, 1, 0, 0, 1},  // count = 3
						{0, 1, 1, 0, 0, 1, 1},  // count = 4
						{1, 0, 1, 1, 0, 1, 1},  // count = 5
						{1, 0, 1, 1, 1, 1, 1},  // count = 6
						{1, 1, 1, 0, 0, 0, 0},  // count = 7
						{1, 1, 1, 1, 1, 1, 1},  // count = 8
						{1, 1, 1, 1, 0, 1, 1}}; // count = 9
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM21_Init(void);
/* USER CODE BEGIN PFP */

void verifyDisp(void);
void counterConfig(void);
void showDisp(uint8_t atualCount);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
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
  MX_TIM21_Init();
  /* USER CODE BEGIN 2 */

  HAL_TIM_Base_Start_IT(&htim21);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  counterConfig();

    /* USER CODE END WHILE */

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

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_3;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM21 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM21_Init(void)
{

  /* USER CODE BEGIN TIM21_Init 0 */

  /* USER CODE END TIM21_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM21_Init 1 */

  /* USER CODE END TIM21_Init 1 */
  htim21.Instance = TIM21;
  htim21.Init.Prescaler = 12000;
  htim21.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim21.Init.Period = 500;
  htim21.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim21.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim21) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim21, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim21, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM21_Init 2 */

  /* USER CODE END TIM21_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, PORT_A_Pin|PORT_B_Pin|PORT_F_Pin|PORT_E_Pin
                          |CLOCK_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, PORT_G_Pin|PORT_C_Pin|SECOND_DISP_Pin|FIRST_DISP_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(PORT_D_GPIO_Port, PORT_D_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PORT_A_Pin PORT_B_Pin PORT_F_Pin PORT_E_Pin
                           CLOCK_Pin */
  GPIO_InitStruct.Pin = PORT_A_Pin|PORT_B_Pin|PORT_F_Pin|PORT_E_Pin
                          |CLOCK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PORT_G_Pin PORT_C_Pin SECOND_DISP_Pin FIRST_DISP_Pin */
  GPIO_InitStruct.Pin = PORT_G_Pin|PORT_C_Pin|SECOND_DISP_Pin|FIRST_DISP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PORT_D_Pin */
  GPIO_InitStruct.Pin = PORT_D_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(PORT_D_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

void showDisp(uint8_t atualCount){
	HAL_GPIO_WritePin(PORT_A_GPIO_Port, PORT_A_Pin, numbers[atualCount][0]);
	HAL_GPIO_WritePin(PORT_B_GPIO_Port, PORT_B_Pin, numbers[atualCount][1]);
	HAL_GPIO_WritePin(PORT_C_GPIO_Port, PORT_C_Pin, numbers[atualCount][2]);
	HAL_GPIO_WritePin(PORT_D_GPIO_Port, PORT_D_Pin, numbers[atualCount][3]);
	HAL_GPIO_WritePin(PORT_E_GPIO_Port, PORT_E_Pin, numbers[atualCount][4]);
	HAL_GPIO_WritePin(PORT_F_GPIO_Port, PORT_F_Pin, numbers[atualCount][5]);
	HAL_GPIO_WritePin(PORT_G_GPIO_Port, PORT_G_Pin, numbers[atualCount][6]);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	count++;
}

void verifyDisp(void){
	switch(atualDisp){
		case 0:
			HAL_GPIO_WritePin(FIRST_DISP_GPIO_Port, FIRST_DISP_Pin, 1);
			HAL_GPIO_WritePin(SECOND_DISP_GPIO_Port, SECOND_DISP_Pin, 0);
			break;
		case 1:
			HAL_GPIO_WritePin(FIRST_DISP_GPIO_Port, FIRST_DISP_Pin, 0);
			HAL_GPIO_WritePin(SECOND_DISP_GPIO_Port, SECOND_DISP_Pin, 1);
			break;
	}
	// Time for stable mode
	HAL_Delay(1);
}

void counterConfig(void){
	switch(atualDisp){
		case 0:
			showDisp(countDeca);
			verifyDisp();
			atualDisp = 1;
			break;

		case 1:
			showDisp(count);
			verifyDisp();
			atualDisp = 0;
			break;
	}

	if (count >= 10){
		count = 0;
		countDeca++;
		if (countDeca >= 10){
			countDeca = 0;
		}
	}
}


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
