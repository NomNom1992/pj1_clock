/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "lcd_16x2.h"
//#include "string.h"
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
RTC_HandleTypeDef hrtc;

/* USER CODE BEGIN PV */
RTC_HandleTypeDef hrtc;

RTC_TimeTypeDef sTime;
RTC_DateTypeDef sDate;
RTC_AlarmTypeDef sAlarm;


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_RTC_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
	uint8_t alarm_en = 0;
	uint8_t alarm_hour = 12;
	uint8_t alarm_minute = 0;

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	sTime.Hours = 9;
	sTime.Minutes = 30;
	sTime.Seconds = 0;

	sDate.Date = 19;
	sDate.Month = 3;
	sDate.Year = 23;


	uint8_t mode = 0;
	uint8_t sb;
	uint8_t CurrYear = 20;



  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
	Lcd_Init();
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_RTC_Init();
  /* USER CODE BEGIN 2 */
	HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);






  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	uint8_t MODE = 0;
	uint8_t UP = 0;
	uint8_t DOWN = 0;
	uint8_t OK = 0;
  while (1)
  {
		MODE = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7);
		UP = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6);
		DOWN = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5);
		OK = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4);
		//kiem tra trang thai chan MODE

		if (MODE == 1 && sb==0){ //chon che do
			if (mode == 9){
				mode = 0;
			}
			else {
				mode++;
			}
			sb = 1; //bao co phim nhan
			Lcd_clear_display();
	}
		//che do hien thi thong tin de tai
		if(mode == 0){

			Lcd_gotoxy(0,0);
			Lcd_write_string("HE THONG NHUNG");
			Lcd_gotoxy(4,1);
			Lcd_write_string("LE THANH NAM");
			HAL_Delay(1000);
			sb = 0;
			Lcd_clear_display();
			mode = 1;
		}
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

		if(mode==1){
			if(alarm_en == 1) Lcd_write_string("*");
			Lcd_gotoxy(4,0);
			HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
			Lcd_write_int(sTime.Hours);
			Lcd_write_string(":");
			Lcd_write_int(sTime.Minutes);
			Lcd_write_string(":");
			Lcd_write_int(sTime.Seconds);
			Lcd_write_string(" ");

			Lcd_gotoxy(0,1);
			switch(sDate.WeekDay){
				case 1: Lcd_write_string("MON");
								break;
				case 2: Lcd_write_string("TUE");
								break;
				case 3: Lcd_write_string("WEN");
								break;
				case 4: Lcd_write_string("THU");
								break;
				case 5: Lcd_write_string("FRI");
								break;
				case 6: Lcd_write_string("SAT");
								break;
				case 0: Lcd_write_string("SUN");
								break;
				}

			Lcd_gotoxy(6,1);
			if(sDate.Date >9) Lcd_write_int(sDate.Date);
			else{
				Lcd_write_int(0);
				Lcd_write_int(sDate.Date);
			}
			Lcd_write_string("-");
			if(sDate.Month >9) Lcd_write_int(sDate.Month);
			else{
				Lcd_write_int(0);
				Lcd_write_int(sDate.Month);
			}
			Lcd_write_string("-");
			Lcd_write_int(CurrYear);
			Lcd_write_int(sDate.Year);
			Lcd_write_string(" ");

			HAL_Delay(100);
			sb = 0;
		}

		//che do chinh gio trong hen gio
		if(mode == 2){
			Lcd_gotoxy(0,0);
			Lcd_write_string("Alarm Hour: ");
			if(alarm_hour < 10){
				Lcd_write_int(0);
				Lcd_write_int(alarm_hour);
			}
			else Lcd_write_int(alarm_hour);
			HAL_Delay(200);
			if (UP == 1 && sb == 0){
				if (alarm_hour == 23) alarm_hour = 0;
				else alarm_hour++;
				sb = 1;
			}
			if (DOWN == 1 && sb == 0){
				if (alarm_hour == 0) alarm_hour = 23;
				else alarm_hour--;
				sb = 1;
			}

			else if(OK == 1 && sb == 0){
				Lcd_clear_display();
				sb = 1;
			}
		}

		//che do chinh phut trong hen gio
		if(mode == 3){
			Lcd_gotoxy(0,0);
			Lcd_write_string("Alarm Minute: ");
			if(alarm_minute < 10){
				Lcd_write_int(0);
				Lcd_write_int(alarm_minute);
			}
			else Lcd_write_int(alarm_minute);
			HAL_Delay(200);
			if (UP == 1 && sb == 0){
				if (alarm_minute == 59) alarm_minute = 0;
				else alarm_minute++;
				sb = 1;
			}
			if (DOWN == 1 && sb == 0){
				if (alarm_minute == 0) alarm_minute = 59;
				else alarm_minute--;
			sb = 1;
			}

			if(OK == 1){
				if(alarm_en == 1) alarm_en = 0;
				else alarm_en = 1;
				Lcd_clear_display();
				mode = 1;
				sb = 1;
			}

		}

		//kiem tra gio bao thuc
		if(alarm_en == 1){
			if(alarm_hour == sTime.Hours && alarm_minute == sTime.Minutes){
			Lcd_clear_display();
			Lcd_gotoxy(3,0);
			Lcd_write_string("WARNING!!!");
			for(uint8_t i = 30; i > 0; i--){
				HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_12);
				HAL_Delay(40);
				HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_12);
				HAL_Delay(20);
				HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_12);
				HAL_Delay(40);
				HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_12);
				HAL_Delay(300);
				if(OK == 1){
					alarm_en = 0;
					Lcd_clear_display();
					sb = 0;
					break;
				}
			}
		}
	}
		if(mode == 4){
			Lcd_gotoxy(0,0);
			Lcd_write_string("Set Hour: ");
			if(sTime.Hours < 10){
				Lcd_write_int(0);
				Lcd_write_int(sTime.Hours);
			}
			else Lcd_write_int(sTime.Hours);
			sb = 0;
			HAL_Delay(100);


			if (UP == 1 && sb == 0){ //Phim UP duoc nhan
				if (sTime.Hours == 23) sTime.Hours = 0;
				else sTime.Hours++;
				HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
				sb = 1;
			}

			if (DOWN == 1 && sb == 0){ //Phim DOWN duoc nhan
				if (sTime.Hours == 0) sTime.Hours = 23;
				else sTime.Hours--;
				HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
				sb = 1;
			}
			if(OK == 1 && sb == 0){
				Lcd_clear_display();
				mode = 1;
			}
		}
		//che do chinh phut
		if(mode == 5){
			Lcd_gotoxy(0,0);
			Lcd_write_string("Set Minutes: ");
			if(sTime.Minutes < 10){
				Lcd_write_int(0);
				Lcd_write_int(sTime.Minutes);
			}
			else Lcd_write_int(sTime.Minutes);
			sb = 0;
			HAL_Delay(200);
			//status_button(MODE, UP, DOWN, OK, sb);

			if (UP == 1 && sb == 0){ //Phim UP duoc nhan
				if (sTime.Minutes == 59) sTime.Minutes = 0;
				else sTime.Minutes++;
				HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
				sb = 1;
			}

			if (DOWN == 1 && sb == 0){ //Phim DOWN duoc nhan
				if (sTime.Minutes == 0) sTime.Minutes = 59;
				else sTime.Minutes--;
				HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
				sb = 1;
			}
			if(OK == 1 && sb == 0){
				Lcd_clear_display();
				mode = 1;
			}
		}
		//che do chinh ngay
		if(mode == 6){
			Lcd_gotoxy(0,0);
			Lcd_write_string("Set Date: ");
			if(sDate.Date < 10){
				Lcd_write_int(0);
				Lcd_write_int(sDate.Date);
			}
			else Lcd_write_int(sDate.Date);
			Lcd_write_string("   ");
			sb = 0;
			HAL_Delay(200);
			//status_button(MODE, UP, DOWN, OK, sb);

			if (UP == 1 && sb == 0){ //Phim UP duoc nhan
				if (sDate.Date == 32) sDate.Date = 1;
				else sDate.Date++;
				HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
				sb = 1;
			}

			if (DOWN == 1 && sb == 0){ //Phim DOWN duoc nhan
				if (sDate.Date == 0) sDate.Date = 31;
				else sDate.Date--;
				HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
				sb = 1;
			}
			if(OK == 1 && sb == 0){
				Lcd_clear_display();
				mode = 1;
			}
		}

		//che do chinh thang
		if(mode == 7){
			Lcd_gotoxy(0,0);
			Lcd_write_string("Set Month: ");
			if(sDate.Month < 10){
				Lcd_write_int(0);
				Lcd_write_int(sDate.Month);
			}
			else Lcd_write_int(sDate.Month);
			sb = 0;
			HAL_Delay(200);
			//status_button(MODE, UP, DOWN, OK, sb);

			if (UP == 1 && sb == 0){ //Phim UP duoc nhan
				if (sDate.Month == 12) sDate.Month = 1;
				else sDate.Month++;
				HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
				sb = 1;
			}

			if (DOWN == 1 && sb == 0){ //Phim DOWN duoc nhan
				if (sDate.Month == 1) sDate.Month = 12;
				else sDate.Month--;
				HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
				sb = 1;
			}
			if(OK == 1 && sb == 0){
				Lcd_clear_display();
				mode = 1;
			}
		}

		//CHE DO CHINH NAM
		if(mode == 8){
			Lcd_gotoxy(0,0);
			Lcd_write_string("Set Year: ");
			Lcd_write_int(sDate.Year);
			sb = 0;
			HAL_Delay(200);
			//status_button(MODE, UP, DOWN, OK, sb);

			if (UP == 1 && sb == 0){ //Phim UP duoc nhan
				if (sDate.Year == 99){
					sDate.Year = 0;
					CurrYear++;
				}
				else sDate.Year++;
				HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
				sb = 1;
			}

			if (DOWN == 1 && sb == 0){ //Phim DOWN duoc nhan
				if (sDate.Year == 0){
					sDate.Year = 99;
					CurrYear--;
				}
				else sDate.Year--;
				HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
				sb = 1;
			}
			if(OK == 1 && sb == 0){
				Lcd_clear_display();
				mode = 1;
			}
		}
		sb = 0;
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
			  HAL_Delay(250);
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_OFF;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL2;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef DateToUpdate = {0};

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */

  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.AsynchPrediv = RTC_AUTO_1_SECOND;
  hrtc.Init.OutPut = RTC_OUTPUTSOURCE_ALARM;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */

  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date
  */
  sTime.Hours = 0x9;
  sTime.Minutes = 0x0;
  sTime.Seconds = 0x0;

  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  DateToUpdate.WeekDay = RTC_WEEKDAY_MONDAY;
  DateToUpdate.Month = RTC_MONTH_OCTOBER;
  DateToUpdate.Date = 0x1;
  DateToUpdate.Year = 0x23;

  if (HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
                          |GPIO_PIN_8, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA4 PA5 PA6 PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB12 PB5 PB6 PB7
                           PB8 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
                          |GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PA9 PA10 PA11 */
  GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
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
