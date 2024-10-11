#pragma once
#include "stm32f1xx_hal.h"
#include <inttypes.h>

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
		{

		}

		void Init()
		{
			Off();
			HAL_GPIO_Init(_port, &_pin);
			Write(_state);
			
			return;
		}
		
		void Mode(GPIO_InitTypeDef pin, GPIO_PinState init = GPIO_PIN_RESET)
		{
			_pin = pin;
			_state = init;
			Init();
			
			return;
		}
		
		void On()
		{
			HAL_GPIO_WritePin(_port, _pin.Pin, GPIO_PIN_SET);
			_state = GPIO_PIN_SET;
			
			return;
		}
		
		void Off()
		{
			HAL_GPIO_WritePin(_port, _pin.Pin, GPIO_PIN_RESET);
			_state = GPIO_PIN_RESET;
			
			return;
		}
		
		void Toggle()
		{
			HAL_GPIO_TogglePin(_port, _pin.Pin);
			_state = (_state == GPIO_PIN_RESET) ? GPIO_PIN_SET : GPIO_PIN_RESET;
			
			return;
		}
		
		void Write(GPIO_PinState state)
		{
			HAL_GPIO_WritePin(_port, _pin.Pin, state);
			_state = state;
			
			return;
		}
		
		GPIO_PinState Read()
		{
			_state = HAL_GPIO_ReadPin(_port, _pin.Pin);
			
			return _state;
		}
		
		GPIO_PinState GetState()
		{
			return _state;
		}
		
	private:
		
		GPIO_TypeDef *_port;
		GPIO_InitTypeDef _pin;
		GPIO_PinState _state;
};
