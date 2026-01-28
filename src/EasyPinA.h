#pragma once
#include <inttypes.h>
#if defined(STM32F1)
	#include "stm32f1xx_hal.h"
	#include "stm32f1xx_hal_adc.h"
#elif defined(STM32H7)
	#include "stm32h7xx_hal.h"
	#include "stm32h7xx_hal_adc.h"
#elif defined(ESP32)

	#define HAL_GPIO_WritePin(_port, _pin, GPIO_PIN_RESET)
	#define HAL_GPIO_Init(_port, _pin)
	#define HAL_ADC_Start(_hadc)
	#define HAL_ADC_ConfigChannel(_hadc, _config)
	#define HAL_ADC_PollForConversion(_hadc, time)
	#define HAL_ADC_GetValue(_hadc) 0
	#define HAL_ADC_Stop(_hadc)

	#define GPIO_TypeDef uint32_t
	#define ADC_HandleTypeDef uint32_t
	#define ADC_SAMPLETIME_1CYCLE_5 15UL
	
	typedef struct
	{
		uint32_t Pin;
		uint32_t Mode;
		uint32_t Pull; 
		uint32_t Speed;
	} GPIO_InitTypeDef;
	
	typedef struct 
	{
		uint32_t Channel;
		uint32_t Rank;
		uint32_t SamplingTime;
		}ADC_ChannelConfTypeDef;

	#define GPIO_MODE_ANALOG 0
	#define GPIO_NOPULL 0
	#define GPIO_SPEED_FREQ_LOW 0
	#define ADC_REGULAR_RANK_1 0

#else
	#error "Unsupported STM32 series."
#endif

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
