#pragma once
#include <inttypes.h>
#if defined(STM32F1)
	#include "stm32f1xx_hal.h"
#elif defined(STM32H7)
	#include "stm32h7xx_hal.h"
#elif defined(ESP32)
	#include "driver/gpio.h"

	#define GPIO_MODE_INPUT			GPIO_MODE_INPUT
	#define GPIO_MODE_OUTPUT_PP		GPIO_MODE_OUTPUT
	#define GPIO_MODE_OUTPUT_OD		GPIO_MODE_OUTPUT_OD
	#define GPIO_MODE_AF_PP			GPIO_MODE_OUTPUT
	#define GPIO_MODE_AF_OD			GPIO_MODE_OUTPUT_OD
	#define GPIO_MODE_AF_INPUT		GPIO_MODE_INPUT

	#define GPIO_NOPULL				0
	#define GPIO_PULLUP				1
	#define GPIO_PULLDOWN			2

	#define GPIO_SPEED_FREQ_HIGH	0
	#define GPIO_SPEED_FREQ_MEDIUM	1
	#define GPIO_SPEED_FREQ_LOW		2

	#define GPIO_PIN_RESET			0
	#define GPIO_PIN_SET			1

	#define GPIO_TypeDef			uint8_t
	#define GPIO_PinState			uint8_t
	typedef struct
	{
		gpio_num_t Pin;
		gpio_mode_t Mode;
		uint8_t Pull;
		uint8_t Speed;
	} GPIO_InitTypeDef;
	
	#define HAL_GPIO_Init(_port, _pin) \
		gpio_config_t conf = { (1ULL << (_pin)->Pin), (_pin)->Mode, GPIO_PULLUP_DISABLE, GPIO_PULLDOWN_DISABLE, GPIO_INTR_DISABLE }; \
		if((_pin)->Pull == GPIO_PULLUP) conf.pull_up_en = GPIO_PULLUP_ENABLE; \
		if((_pin)->Pull == GPIO_PULLDOWN) conf.pull_down_en = GPIO_PULLDOWN_ENABLE; \
		gpio_config(&conf);
	
	#define HAL_GPIO_WritePin(_port, _pin, _state) \
		gpio_set_level((_pin), (_state))
	
	#define HAL_GPIO_ReadPin(_port, _pin) \
		gpio_get_level((_pin))
	
	#define HAL_GPIO_TogglePin(_port, _pin) \
		gpio_set_level((_pin), 1 - gpio_get_level((_pin)))
	
#else
	#error "Unsupported STM32 series."
#endif

class EasyPinD
{
	public:
		
		typedef struct
		{
			GPIO_TypeDef *Port;
			uint16_t Pin;
		} d_pin_t;
		
		// STM32: EasyPinD pin(GPIOA, {GPIO_PIN_0, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW}, GPIO_PIN_SET);
		// ESP32: EasyPinD pin(0, {GPIO_NUM_20, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH}, GPIO_PIN_SET);
		EasyPinD(GPIO_TypeDef *port, GPIO_InitTypeDef pin, GPIO_PinState init = GPIO_PIN_RESET) : _port(port), _pin(pin), _state(init)
		{}
		
		void Init();
		void Mode(GPIO_InitTypeDef pin, GPIO_PinState state = GPIO_PIN_RESET);
		void On();
		void Off();
		void Toggle();
		void Write(GPIO_PinState state);
		GPIO_PinState Read();
		GPIO_PinState GetState();
		
	private:
		
		GPIO_TypeDef *_port;
		GPIO_InitTypeDef _pin;
		GPIO_PinState _state;
};
