#pragma once
#include <inttypes.h>
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_adc.h"

class EasyPinA
{
	public:
		
		typedef struct
		{
			GPIO_TypeDef *Port;
			uint16_t Pin;
			uint32_t Channel;
		} a_pin_t;
		
		// EasyPinA pin(&hadc1, GPIOA, GPIO_PIN_7, ADC_CHANNEL_1, ADC_SAMPLETIME_1CYCLE_5);
		EasyPinA(ADC_HandleTypeDef *hadc, GPIO_TypeDef *port, uint16_t pin, uint32_t channel, uint32_t sampling_time = ADC_SAMPLETIME_1CYCLE_5) : 
			_hadc(hadc),
			_port(port), 
			_pin{pin, GPIO_MODE_ANALOG, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW}, 
			_config{channel, ADC_REGULAR_RANK_1, sampling_time}
		{}
		
		void Init();
		uint16_t Get();
		void Calibration();
		
	private:
		
		ADC_HandleTypeDef *_hadc;
		GPIO_TypeDef *_port;
		GPIO_InitTypeDef _pin;
		ADC_ChannelConfTypeDef _config;
};
