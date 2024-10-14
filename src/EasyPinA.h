#pragma once
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_adc.h"
#include <inttypes.h>

class EasyPinA
{
	public:
		
		typedef struct
		{
			GPIO_TypeDef *Port;
			uint16_t Pin;
			uint32_t Channel;
		} a_pin_t;
		
		// EasyPinA pin(&hadc1, GPIOA, GPIO_PIN_7, ADC_CHANNEL_1);
		EasyPinA(ADC_HandleTypeDef *hadc, GPIO_TypeDef *port, uint16_t pin, uint32_t channel) : 
			_hadc(hadc),
			_port(port), 
			_pin{pin, GPIO_MODE_ANALOG, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW}, 
			_config{channel, ADC_REGULAR_RANK_1, ADC_SAMPLETIME_1CYCLE_5}
		{

		}

		void Init()
		{
			HAL_GPIO_WritePin(_port, _pin.Pin, GPIO_PIN_RESET);
			HAL_GPIO_Init(_port, &_pin);
			Calibration();
			
			return;
		}
		
		uint16_t Get()
		{
			HAL_ADC_ConfigChannel(_hadc, &_config);
			//HAL_ADCEx_Calibration_Start(&_hadc);
			HAL_ADC_Start(_hadc);
			HAL_ADC_PollForConversion(_hadc, 5);
			return HAL_ADC_GetValue(_hadc);
		}
		
		void Calibration()
		{
			HAL_ADCEx_Calibration_Start(_hadc);
			
			return;
		}
		
	private:
		
		ADC_HandleTypeDef *_hadc;
		GPIO_TypeDef *_port;
		GPIO_InitTypeDef _pin;
		ADC_ChannelConfTypeDef _config;
};
