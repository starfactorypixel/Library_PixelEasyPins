#pragma once
#include <inttypes.h>
#if defined(STM32F1)
	#include "stm32f1xx_hal.h"
#elif defined(STM32H7)
	#include "stm32h7xx_hal.h"
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
		
		// EasyPinD pin(GPIOA, {GPIO_PIN_0, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW}, GPIO_PIN_SET);
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
