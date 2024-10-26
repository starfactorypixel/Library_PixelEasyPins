#include "EasyPinD.h"

void EasyPinD::Init()
{
	HAL_GPIO_WritePin(_port, _pin.Pin, GPIO_PIN_RESET);
	HAL_GPIO_Init(_port, &_pin);
	Write(_state);

	return;
}

void EasyPinD::Mode(GPIO_InitTypeDef pin, GPIO_PinState state)
{
	_pin = pin;
	_state = state;
	Init();

	return;
}

void EasyPinD::On()
{
	HAL_GPIO_WritePin(_port, _pin.Pin, GPIO_PIN_SET);
	_state = GPIO_PIN_SET;

	return;
}

void EasyPinD::Off()
{
	HAL_GPIO_WritePin(_port, _pin.Pin, GPIO_PIN_RESET);
	_state = GPIO_PIN_RESET;

	return;
}

void EasyPinD::Toggle()
{
	HAL_GPIO_TogglePin(_port, _pin.Pin);
	_state = (_state == GPIO_PIN_RESET) ? GPIO_PIN_SET : GPIO_PIN_RESET;

	return;
}

void EasyPinD::Write(GPIO_PinState state)
{
	HAL_GPIO_WritePin(_port, _pin.Pin, state);
	_state = state;

	return;
}

GPIO_PinState EasyPinD::Read()
{
	_state = HAL_GPIO_ReadPin(_port, _pin.Pin);

	return _state;
}

GPIO_PinState EasyPinD::GetState()
{
	return _state;
}
