
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f7xx_hal.h"
#include <math.h>
#include <stdlib.h>
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

SPI_HandleTypeDef hspi4;
SPI_HandleTypeDef hspi6;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
uint8_t testdata_out = 51; // 1V Amplitude as an output
uint8_t testdata_out_V2; //= 102; //2V Amplitude as an output
uint8_t testdata_out;
uint8_t DAC_A_Write = 0x1; // DAC's A output is selected 0 0 0 1
uint8_t DAC_B_Write = 0x5; // DAC's B output is selected 0 1 0 1 
//float DAC_A_Write;
/*float DAC_A_Write = 1.000f;
float DAC_B_Write = 5.000f;*/
uint16_t DACA_Buf; 
uint16_t DACB_Buf;
uint8_t current;
float volt;
int tenth;
int tenthvalue;
int ones;
float calc;
int final;

//const uint32_t data = 0x0000001;
//unsigned char bytes[4] ={ data, (data >> 8), (data >> 16), (data>>24) };

/* my edits */
int count = 0;
uint8_t buffer[10];

 
    



uint16_t Switch_Select1st = 0x0001;// I try to define that the first switch should ON. Based on datasheet, for first switch, DO should 1.
uint16_t Switch_Select2nd = 0x0000; // Rest of the 16 bit



/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI6_Init(void);
static void MX_SPI4_Init(void);
static void MX_USART2_UART_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
/*	char two[2] = "2";
	int two1 = atoi(two);*/
/*	testhelper = strtol(test, &eptr, 10);
	bandaid = testhelper * 2;
	bandaid1 = buffer[2] * 10;
	OnesHelper[0] = test[0];
	ones = atoi((char *)&OnesHelper[0]);
	tenth = ones * 2;
	//bandaid2 = atol(bandaid2buff);*/
	
  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

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
  MX_SPI6_Init();
  MX_SPI4_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
	
	/* my edits*/
//	__HAL_UART_ENABLE_IT(&huart3, UART_IT_RXNE);
		
		
		 	//HAL_GPIO_WritePin(AnalogSWIC_LE_GPIO_Port, AnalogSWIC_LE_Pin, GPIO_PIN_RESET); // LE Pin set as low
			//HAL_GPIO_WritePin(AnalogSWIC_CLR_GPIO_Port, AnalogSWIC_CLR_Pin, GPIO_PIN_RESET); // CLR pin set as low
		  //HAL_SPI_Transmit(&hspi4,(uint8_t*)&Switch_Select1st,2,100);
			//HAL_Delay(1);
			//HAL_SPI_Transmit(&hspi4,(uint8_t*)&Switch_Select2nd,2,100);
			//HAL_GPIO_WritePin(AnalogSWIC_LE_GPIO_Port, AnalogSWIC_LE_Pin, GPIO_PIN_SET); // LE pins set as high
			//HAL_GPIO_WritePin(AnalogSWIC_CLR_GPIO_Port, AnalogSWIC_CLR_Pin, GPIO_PIN_SET); // CLR pin set as high
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
		//mult = (int)two * (int)five;
		HAL_UART_Receive(&huart2, buffer, 10, 1);
		//bandaid2buff = (char) buffer;
		//HAL_Delay(5);
		HAL_GPIO_WritePin(DAC_SYNC_Pin_GPIO_Port, DAC_SYNC_Pin_Pin, GPIO_PIN_RESET);
		DACA_Buf = DAC_A_Write<<12 | testdata_out<<4;
	//	DACA_Buf = DAC_A_Write<12.00f | testdata_out<<4;
		HAL_SPI_Transmit(&hspi6,(uint8_t*)&DACA_Buf,16,100);
		HAL_Delay(1);
		HAL_GPIO_WritePin(DAC_SYNC_Pin_GPIO_Port, DAC_SYNC_Pin_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(DAC_SYNC_Pin_GPIO_Port, DAC_SYNC_Pin_Pin, GPIO_PIN_RESET);
		DACB_Buf =  DAC_B_Write<<12 | testdata_out <<4;
		HAL_SPI_Transmit(&hspi6,(uint8_t*)&DACB_Buf,16,100);
		HAL_Delay(1);
		HAL_GPIO_WritePin(DAC_SYNC_Pin_GPIO_Port, DAC_SYNC_Pin_Pin, GPIO_PIN_SET);
     		
		// Analog Switch (PS323ESA) Input 1 and Input 2. 
		HAL_GPIO_TogglePin(Input_1st_AnalogSW_Pin_GPIO_Port, Input_1st_AnalogSW_Pin_Pin);
		HAL_Delay(1);
		HAL_GPIO_TogglePin(Input_2nd_AnalogSW_Pin_GPIO_Port, Input_2nd_AnalogSW_Pin_Pin);
		HAL_Delay(1);
		
		HAL_GPIO_WritePin(SW_1_GPIO_Port, SW_1_Pin, GPIO_PIN_RESET);
						HAL_Delay(1);
						HAL_GPIO_WritePin(SW_2_GPIO_Port, SW_2_Pin, GPIO_PIN_SET);
						HAL_Delay(1);
						HAL_GPIO_WritePin(SW_3_GPIO_Port, SW_3_Pin, GPIO_PIN_RESET);
						HAL_Delay(1);
						HAL_GPIO_WritePin(SW_4_GPIO_Port, SW_4_Pin, GPIO_PIN_RESET);
						HAL_Delay(1);
						HAL_GPIO_WritePin(SW_5_GPIO_Port, SW_5_Pin, GPIO_PIN_RESET);
						HAL_Delay(1);
						HAL_GPIO_WritePin(SW_6_GPIO_Port, SW_6_Pin, GPIO_PIN_RESET);
						HAL_Delay(1);
						HAL_GPIO_WritePin(SW_7_GPIO_Port, SW_7_Pin, GPIO_PIN_RESET);
						HAL_Delay(1);
						HAL_GPIO_WritePin(SW_8_GPIO_Port, SW_8_Pin, GPIO_PIN_RESET);
						HAL_Delay(1);
						HAL_GPIO_WritePin(SW_9_GPIO_Port, SW_9_Pin, GPIO_PIN_RESET);
						HAL_Delay(1);
		HAL_GPIO_WritePin(SW_10_GPIO_Port, SW_10_Pin, GPIO_PIN_RESET);
						HAL_Delay(1);
						HAL_GPIO_WritePin(SW_11_GPIO_Port, SW_11_Pin, GPIO_PIN_RESET);
						HAL_Delay(1);
						HAL_GPIO_WritePin(SW_12_GPIO_Port, SW_12_Pin, GPIO_PIN_RESET);
						HAL_Delay(1);
						HAL_GPIO_WritePin(SW_13_GPIO_Port, SW_13_Pin, GPIO_PIN_RESET);
						HAL_Delay(1);
						HAL_GPIO_WritePin(SW_14_GPIO_Port, SW_14_Pin, GPIO_PIN_RESET);
						HAL_Delay(1);
						HAL_GPIO_WritePin(SW_15_GPIO_Port, SW_15_Pin, GPIO_PIN_RESET);
						HAL_Delay(1);
		HAL_GPIO_WritePin(SW_16_GPIO_Port, SW_16_Pin, GPIO_PIN_RESET);
				/*
				// 16:1 Multiplexer control
				// Channel NO1 is enabled. Based on the circuit design, it is Channel 8 voltage monitoring.
				HAL_GPIO_WritePin(MUX_EN_GPIO_Port,MUX_EN_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(MUX_A0_GPIO_Port,MUX_A0_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(MUX_A1_GPIO_Port,MUX_A1_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(MUX_A2_GPIO_Port,MUX_A2_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(MUX_A3_GPIO_Port,MUX_A3_Pin,GPIO_PIN_RESET);	
				
				// Channel NO2 is enabled. Based on the circuit design, it is Channel 7 voltage monitoring.
				HAL_GPIO_WritePin(MUX_EN_GPIO_Port,MUX_EN_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(MUX_A0_GPIO_Port,MUX_A0_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(MUX_A1_GPIO_Port,MUX_A1_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(MUX_A2_GPIO_Port,MUX_A2_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(MUX_A3_GPIO_Port,MUX_A3_Pin,GPIO_PIN_RESET);
				
					
				// Channel NO3 is enabled. Based on the circuit design, it is Channel 6 voltage monitoring.
				HAL_GPIO_WritePin(MUX_EN_GPIO_Port,MUX_EN_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(MUX_A0_GPIO_Port,MUX_A0_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(MUX_A1_GPIO_Port,MUX_A1_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(MUX_A2_GPIO_Port,MUX_A2_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(MUX_A3_GPIO_Port,MUX_A3_Pin,GPIO_PIN_RESET);
				
				// Channel NO4 is enabled. Based on the circuit design, it is Channel 5 voltage monitoring.
				HAL_GPIO_WritePin(MUX_EN_GPIO_Port,MUX_EN_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(MUX_A0_GPIO_Port,MUX_A0_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(MUX_A1_GPIO_Port,MUX_A1_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(MUX_A2_GPIO_Port,MUX_A2_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(MUX_A3_GPIO_Port,MUX_A3_Pin,GPIO_PIN_RESET);
			
				// Channel NO5 is enabled. Based on the circuit design, it is Channel 4 voltage monitoring.
				HAL_GPIO_WritePin(MUX_EN_GPIO_Port,MUX_EN_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(MUX_A0_GPIO_Port,MUX_A0_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(MUX_A1_GPIO_Port,MUX_A1_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(MUX_A2_GPIO_Port,MUX_A2_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(MUX_A3_GPIO_Port,MUX_A3_Pin,GPIO_PIN_RESET);
				
				// Channel NO6 is enabled. Based on the circuit design, it is Channel 3 voltage monitoring.
				HAL_GPIO_WritePin(MUX_EN_GPIO_Port,MUX_EN_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(MUX_A0_GPIO_Port,MUX_A0_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(MUX_A1_GPIO_Port,MUX_A1_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(MUX_A2_GPIO_Port,MUX_A2_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(MUX_A3_GPIO_Port,MUX_A3_Pin,GPIO_PIN_RESET);
				
				// Channel NO7 is enabled. Based on the circuit design, it is Channel 2 voltage monitoring.
				HAL_GPIO_WritePin(MUX_EN_GPIO_Port,MUX_EN_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(MUX_A0_GPIO_Port,MUX_A0_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(MUX_A1_GPIO_Port,MUX_A1_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(MUX_A2_GPIO_Port,MUX_A2_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(MUX_A3_GPIO_Port,MUX_A3_Pin,GPIO_PIN_RESET);
			
				// Channel NO8 is enabled. Based on the circuit design, it is Channel 1 voltage monitoring.
				HAL_GPIO_WritePin(MUX_EN_GPIO_Port,MUX_EN_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(MUX_A0_GPIO_Port,MUX_A0_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(MUX_A1_GPIO_Port,MUX_A1_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(MUX_A2_GPIO_Port,MUX_A2_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(MUX_A3_GPIO_Port,MUX_A3_Pin,GPIO_PIN_RESET);
	
				// Channel NO9 is enabled. Based on the circuit design, it is Channel 9 voltage monitoring.
				HAL_GPIO_WritePin(MUX_EN_GPIO_Port,MUX_EN_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(MUX_A0_GPIO_Port,MUX_A0_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(MUX_A1_GPIO_Port,MUX_A1_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(MUX_A2_GPIO_Port,MUX_A2_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(MUX_A3_GPIO_Port,MUX_A3_Pin,GPIO_PIN_SET);
				
				// Channel NO10 is enabled. Based on the circuit design, it is Channel 10 voltage monitoring.
				HAL_GPIO_WritePin(MUX_EN_GPIO_Port,MUX_EN_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(MUX_A0_GPIO_Port,MUX_A0_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(MUX_A1_GPIO_Port,MUX_A1_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(MUX_A2_GPIO_Port,MUX_A2_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(MUX_A3_GPIO_Port,MUX_A3_Pin,GPIO_PIN_SET);
				
				// Channel NO11 is enabled. Based on the circuit design, it is Channel 11 voltage monitoring.
				HAL_GPIO_WritePin(MUX_EN_GPIO_Port,MUX_EN_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(MUX_A0_GPIO_Port,MUX_A0_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(MUX_A1_GPIO_Port,MUX_A1_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(MUX_A2_GPIO_Port,MUX_A2_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(MUX_A3_GPIO_Port,MUX_A3_Pin,GPIO_PIN_SET);
				
				// Channel NO12 is enabled. Based on the circuit design, it is Channel 12 voltage monitoring.
				HAL_GPIO_WritePin(MUX_EN_GPIO_Port,MUX_EN_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(MUX_A0_GPIO_Port,MUX_A0_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(MUX_A1_GPIO_Port,MUX_A1_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(MUX_A2_GPIO_Port,MUX_A2_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(MUX_A3_GPIO_Port,MUX_A3_Pin,GPIO_PIN_SET);
				
				// Channel NO13 is enabled. Based on the circuit design, it is Channel 13 voltage monitoring.
				HAL_GPIO_WritePin(MUX_EN_GPIO_Port,MUX_EN_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(MUX_A0_GPIO_Port,MUX_A0_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(MUX_A1_GPIO_Port,MUX_A1_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(MUX_A2_GPIO_Port,MUX_A2_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(MUX_A3_GPIO_Port,MUX_A3_Pin,GPIO_PIN_SET);
				
				// Channel NO14 is enabled. Based on the circuit design, it is Channel 14 voltage monitoring.
				HAL_GPIO_WritePin(MUX_EN_GPIO_Port,MUX_EN_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(MUX_A0_GPIO_Port,MUX_A0_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(MUX_A1_GPIO_Port,MUX_A1_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(MUX_A2_GPIO_Port,MUX_A2_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(MUX_A3_GPIO_Port,MUX_A3_Pin,GPIO_PIN_SET);
				
				// Channel NO15 is enabled. Based on the circuit design, it is Channel 15 voltage monitoring.
				HAL_GPIO_WritePin(MUX_EN_GPIO_Port,MUX_EN_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(MUX_A0_GPIO_Port,MUX_A0_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(MUX_A1_GPIO_Port,MUX_A1_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(MUX_A2_GPIO_Port,MUX_A2_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(MUX_A3_GPIO_Port,MUX_A3_Pin,GPIO_PIN_SET);
				
				// Channel NO16 is enabled. Based on the circuit design, it is Channel 16 voltage monitoring.
				HAL_GPIO_WritePin(MUX_EN_GPIO_Port,MUX_EN_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(MUX_A0_GPIO_Port,MUX_A0_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(MUX_A1_GPIO_Port,MUX_A1_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(MUX_A2_GPIO_Port,MUX_A2_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(MUX_A3_GPIO_Port,MUX_A3_Pin,GPIO_PIN_SET);*/
				
			//HAL_UART_Transmit(&huart2, (uint8_t *)"hello world\r\n", 13, 1000);
		if(buffer[2] == 0x31 ) //this checks if the electrode is on
		{
			if(buffer[3] == 0x31) //this checks for the value of the amplitude at A2
				//A2 is the hundredth place
				//if A2 is equal to 1, then the only possible value for the amplitude is 100
			{
				current = 100;
			}
			else if(buffer[3] != 0x31) //if the value of the amplitude at A2 is not equal to 1, 
				//then it must be in the range from 0 to 99
			{
				if(buffer[4] == 0x30) //this checks the value of the amplitude at A1
				//A1 is the tenth place
				//if the value of the amplitude at A1 is equal to 0, then the value must be in between 0 to 9
				//0x30 == 0(radix 10)
				{
					//OnesHelper[0] = buffer[5];
					ones = atoi((char *)&buffer[5]);
					current = ones;
				}
				else if(buffer[4] != 0x30) //the value of the amplitude at the tenth place is not equal to 0
				//the value of the amplitude is in the range of 10 to 99
				{
					ones = atoi((char *)&buffer[5]);
					tenthvalue = atoi((char *)&buffer[4]);
					tenth = tenthvalue * 10;
					current = tenth + ones;
				}
			}
			volt = current * (32.4) ;
			calc = (float)volt * 256.0 / 5.0;
			final = round(calc);
			testdata_out_V2 = final;
			HAL_Delay(100);
			if(buffer[0] == 0x30) //this block turns on the LED for ch 1-9
			{
				HAL_GPIO_WritePin(SW_10_GPIO_Port, SW_10_Pin, GPIO_PIN_RESET);
				HAL_Delay(1);
				HAL_GPIO_WritePin(SW_11_GPIO_Port, SW_11_Pin, GPIO_PIN_RESET);
				HAL_Delay(1);
				HAL_GPIO_WritePin(SW_12_GPIO_Port, SW_12_Pin, GPIO_PIN_RESET);
				HAL_Delay(1);
				HAL_GPIO_WritePin(SW_13_GPIO_Port, SW_13_Pin, GPIO_PIN_RESET);
				HAL_Delay(1);
				HAL_GPIO_WritePin(SW_14_GPIO_Port, SW_14_Pin, GPIO_PIN_RESET);
				HAL_Delay(1);
				HAL_GPIO_WritePin(SW_15_GPIO_Port, SW_15_Pin, GPIO_PIN_RESET);
				HAL_Delay(1);
				HAL_GPIO_WritePin(SW_16_GPIO_Port, SW_16_Pin, GPIO_PIN_RESET);
				HAL_Delay(1);
				if(buffer[1] == 0x31) //ch 1 is selected
				{
					HAL_GPIO_WritePin(SW_1_GPIO_Port, SW_1_Pin, GPIO_PIN_SET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_2_GPIO_Port, SW_2_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_3_GPIO_Port, SW_3_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_4_GPIO_Port, SW_4_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_5_GPIO_Port, SW_5_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_6_GPIO_Port, SW_6_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_7_GPIO_Port, SW_7_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_8_GPIO_Port, SW_8_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_9_GPIO_Port, SW_9_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					
					// Channel NO8 is enabled. Based on the circuit design, it is Channel 1 voltage monitoring.
					HAL_GPIO_WritePin(MUX_EN_GPIO_Port,MUX_EN_Pin,GPIO_PIN_SET);
					HAL_GPIO_WritePin(MUX_A0_GPIO_Port,MUX_A0_Pin,GPIO_PIN_SET);
					HAL_GPIO_WritePin(MUX_A1_GPIO_Port,MUX_A1_Pin,GPIO_PIN_SET);
					HAL_GPIO_WritePin(MUX_A2_GPIO_Port,MUX_A2_Pin,GPIO_PIN_SET);
					HAL_GPIO_WritePin(MUX_A3_GPIO_Port,MUX_A3_Pin,GPIO_PIN_RESET);
				}
				else if(buffer[1] == 0x32) //ch 2 is selected
				{
					HAL_GPIO_WritePin(SW_1_GPIO_Port, SW_1_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_2_GPIO_Port, SW_2_Pin, GPIO_PIN_SET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_3_GPIO_Port, SW_3_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_4_GPIO_Port, SW_4_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_5_GPIO_Port, SW_5_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_6_GPIO_Port, SW_6_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_7_GPIO_Port, SW_7_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_8_GPIO_Port, SW_8_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_9_GPIO_Port, SW_9_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					
					// Channel NO7 is enabled. Based on the circuit design, it is Channel 2 voltage monitoring.
					HAL_GPIO_WritePin(MUX_EN_GPIO_Port,MUX_EN_Pin,GPIO_PIN_SET);
					HAL_GPIO_WritePin(MUX_A0_GPIO_Port,MUX_A0_Pin,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(MUX_A1_GPIO_Port,MUX_A1_Pin,GPIO_PIN_SET);
					HAL_GPIO_WritePin(MUX_A2_GPIO_Port,MUX_A2_Pin,GPIO_PIN_SET);
					HAL_GPIO_WritePin(MUX_A3_GPIO_Port,MUX_A3_Pin,GPIO_PIN_RESET);
				}
				else if(buffer[1] == 0x33) //ch 3 is selected
				{
					HAL_GPIO_WritePin(SW_1_GPIO_Port, SW_1_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_2_GPIO_Port, SW_2_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_3_GPIO_Port, SW_3_Pin, GPIO_PIN_SET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_4_GPIO_Port, SW_4_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_5_GPIO_Port, SW_5_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_6_GPIO_Port, SW_6_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_7_GPIO_Port, SW_7_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_8_GPIO_Port, SW_8_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_9_GPIO_Port, SW_9_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					
					// Channel NO6 is enabled. Based on the circuit design, it is Channel 3 voltage monitoring.
					HAL_GPIO_WritePin(MUX_EN_GPIO_Port,MUX_EN_Pin,GPIO_PIN_SET);
					HAL_GPIO_WritePin(MUX_A0_GPIO_Port,MUX_A0_Pin,GPIO_PIN_SET);
					HAL_GPIO_WritePin(MUX_A1_GPIO_Port,MUX_A1_Pin,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(MUX_A2_GPIO_Port,MUX_A2_Pin,GPIO_PIN_SET);
					HAL_GPIO_WritePin(MUX_A3_GPIO_Port,MUX_A3_Pin,GPIO_PIN_RESET);
				
				}
				else if(buffer[1] == 0x34) //ch 4 is selected
				{
					HAL_GPIO_WritePin(SW_1_GPIO_Port, SW_1_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_2_GPIO_Port, SW_2_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_3_GPIO_Port, SW_3_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_4_GPIO_Port, SW_4_Pin, GPIO_PIN_SET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_5_GPIO_Port, SW_5_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_6_GPIO_Port, SW_6_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_7_GPIO_Port, SW_7_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_8_GPIO_Port, SW_8_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_9_GPIO_Port, SW_9_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					
					// Channel NO5 is enabled. Based on the circuit design, it is Channel 4 voltage monitoring.
					HAL_GPIO_WritePin(MUX_EN_GPIO_Port,MUX_EN_Pin,GPIO_PIN_SET);
					HAL_GPIO_WritePin(MUX_A0_GPIO_Port,MUX_A0_Pin,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(MUX_A1_GPIO_Port,MUX_A1_Pin,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(MUX_A2_GPIO_Port,MUX_A2_Pin,GPIO_PIN_SET);
					HAL_GPIO_WritePin(MUX_A3_GPIO_Port,MUX_A3_Pin,GPIO_PIN_RESET);
				}
				else if(buffer[1] == 0x35) //ch 5 is selected
				{
					HAL_GPIO_WritePin(SW_1_GPIO_Port, SW_1_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_2_GPIO_Port, SW_2_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_3_GPIO_Port, SW_3_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_4_GPIO_Port, SW_4_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_5_GPIO_Port, SW_5_Pin, GPIO_PIN_SET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_6_GPIO_Port, SW_6_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_7_GPIO_Port, SW_7_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_8_GPIO_Port, SW_8_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_9_GPIO_Port, SW_9_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					
					// Channel NO4 is enabled. Based on the circuit design, it is Channel 5 voltage monitoring.
					HAL_GPIO_WritePin(MUX_EN_GPIO_Port,MUX_EN_Pin,GPIO_PIN_SET);
					HAL_GPIO_WritePin(MUX_A0_GPIO_Port,MUX_A0_Pin,GPIO_PIN_SET);
					HAL_GPIO_WritePin(MUX_A1_GPIO_Port,MUX_A1_Pin,GPIO_PIN_SET);
					HAL_GPIO_WritePin(MUX_A2_GPIO_Port,MUX_A2_Pin,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(MUX_A3_GPIO_Port,MUX_A3_Pin,GPIO_PIN_RESET);
				}
				else if(buffer[1] == 0x36) //ch 6 is selected
				{
					HAL_GPIO_WritePin(SW_1_GPIO_Port, SW_1_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_2_GPIO_Port, SW_2_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_3_GPIO_Port, SW_3_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_4_GPIO_Port, SW_4_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_5_GPIO_Port, SW_5_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_6_GPIO_Port, SW_6_Pin, GPIO_PIN_SET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_7_GPIO_Port, SW_7_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_8_GPIO_Port, SW_8_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_9_GPIO_Port, SW_9_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					
					
					// Channel NO3 is enabled. Based on the circuit design, it is Channel 6 voltage monitoring.
					HAL_GPIO_WritePin(MUX_EN_GPIO_Port,MUX_EN_Pin,GPIO_PIN_SET);
					HAL_GPIO_WritePin(MUX_A0_GPIO_Port,MUX_A0_Pin,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(MUX_A1_GPIO_Port,MUX_A1_Pin,GPIO_PIN_SET);
					HAL_GPIO_WritePin(MUX_A2_GPIO_Port,MUX_A2_Pin,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(MUX_A3_GPIO_Port,MUX_A3_Pin,GPIO_PIN_RESET);
				}
				else if(buffer[1] == 0x37) //ch 7 is selected
				{
					HAL_GPIO_WritePin(SW_1_GPIO_Port, SW_1_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_2_GPIO_Port, SW_2_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_3_GPIO_Port, SW_3_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_4_GPIO_Port, SW_4_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_5_GPIO_Port, SW_5_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_6_GPIO_Port, SW_6_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_7_GPIO_Port, SW_7_Pin, GPIO_PIN_SET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_8_GPIO_Port, SW_8_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_9_GPIO_Port, SW_9_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					
					
					// Channel NO2 is enabled. Based on the circuit design, it is Channel 7 voltage monitoring.
					HAL_GPIO_WritePin(MUX_EN_GPIO_Port,MUX_EN_Pin,GPIO_PIN_SET);
					HAL_GPIO_WritePin(MUX_A0_GPIO_Port,MUX_A0_Pin,GPIO_PIN_SET);
					HAL_GPIO_WritePin(MUX_A1_GPIO_Port,MUX_A1_Pin,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(MUX_A2_GPIO_Port,MUX_A2_Pin,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(MUX_A3_GPIO_Port,MUX_A3_Pin,GPIO_PIN_RESET);
				}
				else if(buffer[1] == 0x38) //ch 8 is selected
				{
					HAL_GPIO_WritePin(SW_1_GPIO_Port, SW_1_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_2_GPIO_Port, SW_2_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_3_GPIO_Port, SW_3_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_4_GPIO_Port, SW_4_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_5_GPIO_Port, SW_5_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_6_GPIO_Port, SW_6_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_7_GPIO_Port, SW_7_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_8_GPIO_Port, SW_8_Pin, GPIO_PIN_SET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_9_GPIO_Port, SW_9_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					
					// Channel NO1 is enabled. Based on the circuit design, it is Channel 8 voltage monitoring.
					HAL_GPIO_WritePin(MUX_EN_GPIO_Port,MUX_EN_Pin,GPIO_PIN_SET);
					HAL_GPIO_WritePin(MUX_A0_GPIO_Port,MUX_A0_Pin,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(MUX_A1_GPIO_Port,MUX_A1_Pin,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(MUX_A2_GPIO_Port,MUX_A2_Pin,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(MUX_A3_GPIO_Port,MUX_A3_Pin,GPIO_PIN_RESET);	
				}
				else if(buffer[1] == 0x39) //ch 9 is selected
				{
					HAL_GPIO_WritePin(SW_1_GPIO_Port, SW_1_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_2_GPIO_Port, SW_2_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_3_GPIO_Port, SW_3_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_4_GPIO_Port, SW_4_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_5_GPIO_Port, SW_5_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_6_GPIO_Port, SW_6_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_7_GPIO_Port, SW_7_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_8_GPIO_Port, SW_8_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_9_GPIO_Port, SW_9_Pin, GPIO_PIN_SET);
					HAL_Delay(1);
					
					// Channel NO9 is enabled. Based on the circuit design, it is Channel 9 voltage monitoring.
					HAL_GPIO_WritePin(MUX_EN_GPIO_Port,MUX_EN_Pin,GPIO_PIN_SET);
					HAL_GPIO_WritePin(MUX_A0_GPIO_Port,MUX_A0_Pin,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(MUX_A1_GPIO_Port,MUX_A1_Pin,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(MUX_A2_GPIO_Port,MUX_A2_Pin,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(MUX_A3_GPIO_Port,MUX_A3_Pin,GPIO_PIN_SET);
				}
			}
			else if(buffer[0] == 0x31) //this block of code turns on chs 10-16
			{
				HAL_GPIO_WritePin(SW_1_GPIO_Port, SW_1_Pin, GPIO_PIN_RESET);
				HAL_Delay(1);
				HAL_GPIO_WritePin(SW_2_GPIO_Port, SW_2_Pin, GPIO_PIN_RESET);
				HAL_Delay(1);
				HAL_GPIO_WritePin(SW_3_GPIO_Port, SW_3_Pin, GPIO_PIN_RESET);
				HAL_Delay(1);
				HAL_GPIO_WritePin(SW_4_GPIO_Port, SW_4_Pin, GPIO_PIN_RESET);
				HAL_Delay(1);
				HAL_GPIO_WritePin(SW_5_GPIO_Port, SW_5_Pin, GPIO_PIN_RESET);
				HAL_Delay(1);
				HAL_GPIO_WritePin(SW_6_GPIO_Port, SW_6_Pin, GPIO_PIN_RESET);
				HAL_Delay(1);
				HAL_GPIO_WritePin(SW_7_GPIO_Port, SW_7_Pin, GPIO_PIN_RESET);
				HAL_Delay(1);
				HAL_GPIO_WritePin(SW_8_GPIO_Port, SW_8_Pin, GPIO_PIN_RESET);
				HAL_Delay(1);
				HAL_GPIO_WritePin(SW_9_GPIO_Port, SW_9_Pin, GPIO_PIN_RESET);
				HAL_Delay(1);
				if(buffer[1] == 0x30) //ch 10 is selected
				{
					HAL_GPIO_WritePin(SW_10_GPIO_Port, SW_10_Pin, GPIO_PIN_SET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_11_GPIO_Port, SW_11_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_12_GPIO_Port, SW_12_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_13_GPIO_Port, SW_13_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_14_GPIO_Port, SW_14_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_15_GPIO_Port, SW_15_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_16_GPIO_Port, SW_16_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					
					// Channel NO10 is enabled. Based on the circuit design, it is Channel 10 voltage monitoring.
					HAL_GPIO_WritePin(MUX_EN_GPIO_Port,MUX_EN_Pin,GPIO_PIN_SET);
					HAL_GPIO_WritePin(MUX_A0_GPIO_Port,MUX_A0_Pin,GPIO_PIN_SET);
					HAL_GPIO_WritePin(MUX_A1_GPIO_Port,MUX_A1_Pin,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(MUX_A2_GPIO_Port,MUX_A2_Pin,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(MUX_A3_GPIO_Port,MUX_A3_Pin,GPIO_PIN_SET);
				}
				else if(buffer[1] == 0x31) //ch 11 is selected
				{
					HAL_GPIO_WritePin(SW_10_GPIO_Port, SW_10_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_11_GPIO_Port, SW_11_Pin, GPIO_PIN_SET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_12_GPIO_Port, SW_12_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_13_GPIO_Port, SW_13_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_14_GPIO_Port, SW_14_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_15_GPIO_Port, SW_15_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_16_GPIO_Port, SW_16_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					
					// Channel NO11 is enabled. Based on the circuit design, it is Channel 11 voltage monitoring.
					HAL_GPIO_WritePin(MUX_EN_GPIO_Port,MUX_EN_Pin,GPIO_PIN_SET);
					HAL_GPIO_WritePin(MUX_A0_GPIO_Port,MUX_A0_Pin,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(MUX_A1_GPIO_Port,MUX_A1_Pin,GPIO_PIN_SET);
					HAL_GPIO_WritePin(MUX_A2_GPIO_Port,MUX_A2_Pin,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(MUX_A3_GPIO_Port,MUX_A3_Pin,GPIO_PIN_SET);
				
				}
				else if(buffer[1] == 0x32) //ch 12 is selected
				{
					HAL_GPIO_WritePin(SW_10_GPIO_Port, SW_10_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_11_GPIO_Port, SW_11_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_12_GPIO_Port, SW_12_Pin, GPIO_PIN_SET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_13_GPIO_Port, SW_13_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_14_GPIO_Port, SW_14_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_15_GPIO_Port, SW_15_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_16_GPIO_Port, SW_16_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					
						// Channel NO12 is enabled. Based on the circuit design, it is Channel 12 voltage monitoring.
					HAL_GPIO_WritePin(MUX_EN_GPIO_Port,MUX_EN_Pin,GPIO_PIN_SET);
					HAL_GPIO_WritePin(MUX_A0_GPIO_Port,MUX_A0_Pin,GPIO_PIN_SET);
					HAL_GPIO_WritePin(MUX_A1_GPIO_Port,MUX_A1_Pin,GPIO_PIN_SET);
					HAL_GPIO_WritePin(MUX_A2_GPIO_Port,MUX_A2_Pin,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(MUX_A3_GPIO_Port,MUX_A3_Pin,GPIO_PIN_SET);
				}
				else if(buffer[1] == 0x33) //ch 13 is selected
				{
					HAL_GPIO_WritePin(SW_10_GPIO_Port, SW_10_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_11_GPIO_Port, SW_11_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_12_GPIO_Port, SW_12_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_13_GPIO_Port, SW_13_Pin, GPIO_PIN_SET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_14_GPIO_Port, SW_14_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_15_GPIO_Port, SW_15_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_16_GPIO_Port, SW_16_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					
					// Channel NO13 is enabled. Based on the circuit design, it is Channel 13 voltage monitoring.
					HAL_GPIO_WritePin(MUX_EN_GPIO_Port,MUX_EN_Pin,GPIO_PIN_SET);
					HAL_GPIO_WritePin(MUX_A0_GPIO_Port,MUX_A0_Pin,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(MUX_A1_GPIO_Port,MUX_A1_Pin,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(MUX_A2_GPIO_Port,MUX_A2_Pin,GPIO_PIN_SET);
					HAL_GPIO_WritePin(MUX_A3_GPIO_Port,MUX_A3_Pin,GPIO_PIN_SET);
				}
				else if(buffer[1] == 0x34) //ch 14 is selected
				{
					HAL_GPIO_WritePin(SW_10_GPIO_Port, SW_10_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_11_GPIO_Port, SW_11_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_12_GPIO_Port, SW_12_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_13_GPIO_Port, SW_13_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_14_GPIO_Port, SW_14_Pin, GPIO_PIN_SET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_15_GPIO_Port, SW_15_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_16_GPIO_Port, SW_16_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					
					// Channel NO14 is enabled. Based on the circuit design, it is Channel 14 voltage monitoring.
					HAL_GPIO_WritePin(MUX_EN_GPIO_Port,MUX_EN_Pin,GPIO_PIN_SET);
					HAL_GPIO_WritePin(MUX_A0_GPIO_Port,MUX_A0_Pin,GPIO_PIN_SET);
					HAL_GPIO_WritePin(MUX_A1_GPIO_Port,MUX_A1_Pin,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(MUX_A2_GPIO_Port,MUX_A2_Pin,GPIO_PIN_SET);
					HAL_GPIO_WritePin(MUX_A3_GPIO_Port,MUX_A3_Pin,GPIO_PIN_SET);
				}
				else if(buffer[1] == 0x35) //ch 15 is selected
				{
					HAL_GPIO_WritePin(SW_10_GPIO_Port, SW_10_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_11_GPIO_Port, SW_11_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_12_GPIO_Port, SW_12_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_13_GPIO_Port, SW_13_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_14_GPIO_Port, SW_14_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_15_GPIO_Port, SW_15_Pin, GPIO_PIN_SET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_16_GPIO_Port, SW_16_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					
					// Channel NO15 is enabled. Based on the circuit design, it is Channel 15 voltage monitoring.
					HAL_GPIO_WritePin(MUX_EN_GPIO_Port,MUX_EN_Pin,GPIO_PIN_SET);
					HAL_GPIO_WritePin(MUX_A0_GPIO_Port,MUX_A0_Pin,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(MUX_A1_GPIO_Port,MUX_A1_Pin,GPIO_PIN_SET);
					HAL_GPIO_WritePin(MUX_A2_GPIO_Port,MUX_A2_Pin,GPIO_PIN_SET);
					HAL_GPIO_WritePin(MUX_A3_GPIO_Port,MUX_A3_Pin,GPIO_PIN_SET);
				}
				else if(buffer[1] == 0x36) //ch 16 is selected
				{
					HAL_GPIO_WritePin(SW_10_GPIO_Port, SW_10_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_11_GPIO_Port, SW_11_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_12_GPIO_Port, SW_12_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_13_GPIO_Port, SW_13_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_14_GPIO_Port, SW_14_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_15_GPIO_Port, SW_15_Pin, GPIO_PIN_RESET);
					HAL_Delay(1);
					HAL_GPIO_WritePin(SW_16_GPIO_Port, SW_16_Pin, GPIO_PIN_SET);
					HAL_Delay(1);
					
					// Channel NO16 is enabled. Based on the circuit design, it is Channel 16 voltage monitoring.
					HAL_GPIO_WritePin(MUX_EN_GPIO_Port,MUX_EN_Pin,GPIO_PIN_SET);
					HAL_GPIO_WritePin(MUX_A0_GPIO_Port,MUX_A0_Pin,GPIO_PIN_SET);
					HAL_GPIO_WritePin(MUX_A1_GPIO_Port,MUX_A1_Pin,GPIO_PIN_SET);
					HAL_GPIO_WritePin(MUX_A2_GPIO_Port,MUX_A2_Pin,GPIO_PIN_SET);
					HAL_GPIO_WritePin(MUX_A3_GPIO_Port,MUX_A3_Pin,GPIO_PIN_SET);
				}
			}
		}
		else if(buffer[2] == 0x30) //this indicates for the selected channel to turn it off
		{
			HAL_GPIO_WritePin(SW_1_GPIO_Port, SW_1_Pin, GPIO_PIN_RESET);
			HAL_Delay(1);
			HAL_GPIO_WritePin(SW_2_GPIO_Port, SW_2_Pin, GPIO_PIN_RESET);
			HAL_Delay(1);
			HAL_GPIO_WritePin(SW_3_GPIO_Port, SW_3_Pin, GPIO_PIN_RESET);
			HAL_Delay(1);
			HAL_GPIO_WritePin(SW_4_GPIO_Port, SW_4_Pin, GPIO_PIN_RESET);
			HAL_Delay(1);
			HAL_GPIO_WritePin(SW_5_GPIO_Port, SW_5_Pin, GPIO_PIN_RESET);
			HAL_Delay(1);
			HAL_GPIO_WritePin(SW_6_GPIO_Port, SW_6_Pin, GPIO_PIN_RESET);
			HAL_Delay(1);
			HAL_GPIO_WritePin(SW_7_GPIO_Port, SW_7_Pin, GPIO_PIN_RESET);
			HAL_Delay(1);
			HAL_GPIO_WritePin(SW_8_GPIO_Port, SW_8_Pin, GPIO_PIN_RESET);
			HAL_Delay(1);
			HAL_GPIO_WritePin(SW_9_GPIO_Port, SW_9_Pin, GPIO_PIN_RESET);
			HAL_Delay(1);
			HAL_GPIO_WritePin(SW_10_GPIO_Port, SW_10_Pin, GPIO_PIN_RESET);
			HAL_Delay(1);
			HAL_GPIO_WritePin(SW_11_GPIO_Port, SW_11_Pin, GPIO_PIN_RESET);
			HAL_Delay(1);
			HAL_GPIO_WritePin(SW_12_GPIO_Port, SW_12_Pin, GPIO_PIN_RESET);
			HAL_Delay(1);
			HAL_GPIO_WritePin(SW_13_GPIO_Port, SW_13_Pin, GPIO_PIN_RESET);
			HAL_Delay(1);
			HAL_GPIO_WritePin(SW_14_GPIO_Port, SW_14_Pin, GPIO_PIN_RESET);
			HAL_Delay(1);
			HAL_GPIO_WritePin(SW_15_GPIO_Port, SW_15_Pin, GPIO_PIN_RESET);
			HAL_Delay(1);
			HAL_GPIO_WritePin(SW_16_GPIO_Port, SW_16_Pin, GPIO_PIN_RESET);
			HAL_Delay(1);
		}
				
  }
  /* USER CODE END 3 */

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 216;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Activate the Over-Drive mode 
    */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART2;
  PeriphClkInitStruct.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* SPI4 init function */
static void MX_SPI4_Init(void)
{

  /* SPI4 parameter configuration*/
  hspi4.Instance = SPI4;
  hspi4.Init.Mode = SPI_MODE_MASTER;
  hspi4.Init.Direction = SPI_DIRECTION_2LINES;
  hspi4.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi4.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi4.Init.CLKPhase = SPI_PHASE_2EDGE;
  hspi4.Init.NSS = SPI_NSS_SOFT;
  hspi4.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi4.Init.FirstBit = SPI_FIRSTBIT_LSB;
  hspi4.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi4.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi4.Init.CRCPolynomial = 7;
  hspi4.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi4.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
  if (HAL_SPI_Init(&hspi4) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* SPI6 init function */
static void MX_SPI6_Init(void)
{

  /* SPI6 parameter configuration*/
  hspi6.Instance = SPI6;
  hspi6.Init.Mode = SPI_MODE_MASTER;
  hspi6.Init.Direction = SPI_DIRECTION_2LINES;
  hspi6.Init.DataSize = SPI_DATASIZE_16BIT;
  hspi6.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi6.Init.CLKPhase = SPI_PHASE_2EDGE;
  hspi6.Init.NSS = SPI_NSS_SOFT;
  hspi6.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi6.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi6.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi6.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi6.Init.CRCPolynomial = 7;
  hspi6.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi6.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
  if (HAL_SPI_Init(&hspi6) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* USART2 init function */
static void MX_USART2_UART_Init(void)
{

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
    _Error_Handler(__FILE__, __LINE__);
  }

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, LED_2_Pin|AnalogSWIC_LE_Pin|SW_2_Pin|SW_1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, AnalogSWIC_CLR_Pin|MUX_A3_Pin|SW_7_Pin|SW_6_Pin 
                          |SW_5_Pin|SW_4_Pin|SW_3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, MUX_A2_Pin|MUX_A1_Pin|MUX_A0_Pin|MUX_EN_Pin 
                          |SW_16_Pin|SW_15_Pin|SW_14_Pin|SW_13_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOG, DAC_SYNC_Pin_Pin|SW_12_Pin|SW_11_Pin|SW_10_Pin 
                          |SW_9_Pin|SW_8_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, Input_2nd_AnalogSW_Pin_Pin|Test_Pin_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(Input_1st_AnalogSW_Pin_GPIO_Port, Input_1st_AnalogSW_Pin_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LED_2_Pin AnalogSWIC_LE_Pin SW_2_Pin SW_1_Pin */
  GPIO_InitStruct.Pin = LED_2_Pin|AnalogSWIC_LE_Pin|SW_2_Pin|SW_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : AnalogSWIC_CLR_Pin MUX_A3_Pin SW_7_Pin SW_6_Pin 
                           SW_5_Pin SW_4_Pin SW_3_Pin */
  GPIO_InitStruct.Pin = AnalogSWIC_CLR_Pin|MUX_A3_Pin|SW_7_Pin|SW_6_Pin 
                          |SW_5_Pin|SW_4_Pin|SW_3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : MUX_A2_Pin MUX_A1_Pin MUX_A0_Pin MUX_EN_Pin 
                           SW_16_Pin SW_15_Pin SW_14_Pin SW_13_Pin */
  GPIO_InitStruct.Pin = MUX_A2_Pin|MUX_A1_Pin|MUX_A0_Pin|MUX_EN_Pin 
                          |SW_16_Pin|SW_15_Pin|SW_14_Pin|SW_13_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : DAC_SYNC_Pin_Pin SW_12_Pin SW_11_Pin SW_10_Pin 
                           SW_9_Pin SW_8_Pin */
  GPIO_InitStruct.Pin = DAC_SYNC_Pin_Pin|SW_12_Pin|SW_11_Pin|SW_10_Pin 
                          |SW_9_Pin|SW_8_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : Input_2nd_AnalogSW_Pin_Pin Test_Pin_Pin */
  GPIO_InitStruct.Pin = Input_2nd_AnalogSW_Pin_Pin|Test_Pin_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : Input_1st_AnalogSW_Pin_Pin */
  GPIO_InitStruct.Pin = Input_1st_AnalogSW_Pin_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(Input_1st_AnalogSW_Pin_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
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
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
