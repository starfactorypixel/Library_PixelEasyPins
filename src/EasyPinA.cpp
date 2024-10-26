#include "EasyPinA.h"

void EasyPinA::Init()
{
	HAL_GPIO_WritePin(_port, _pin.Pin, GPIO_PIN_RESET);
	HAL_GPIO_Init(_port, &_pin);
	Calibration();

	return;
}

uint16_t EasyPinA::Get()
{
	HAL_ADC_ConfigChannel(_hadc, &_config);
	//HAL_ADCEx_Calibration_Start(&_hadc);
	HAL_ADC_Start(_hadc);
	HAL_ADC_PollForConversion(_hadc, 5);
	return HAL_ADC_GetValue(_hadc);
}

void EasyPinA::Calibration()
{
	HAL_ADCEx_Calibration_Start(_hadc);

	return;
}
