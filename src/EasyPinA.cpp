#include "EasyPinA.h"

void EasyPinA::Init()
{
	HAL_GPIO_WritePin(_port, _pin.Pin, GPIO_PIN_RESET);
	HAL_GPIO_Init(_port, &_pin);
	
	HAL_ADC_Start(_hadc);
	
	return;
}

uint16_t EasyPinA::Get()
{
	HAL_ADC_ConfigChannel(_hadc, &_config);
	HAL_ADC_Start(_hadc);
	HAL_ADC_PollForConversion(_hadc, 5);
	return HAL_ADC_GetValue(_hadc);
}

void EasyPinA::Calibration()
{
	HAL_ADC_Stop(_hadc);
#if defined(STM32F1)
	HAL_ADCEx_Calibration_Start(_hadc);
#elif defined(STM32H7)
	HAL_ADCEx_Calibration_Start(_hadc, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED);
#endif
	HAL_ADC_Start(_hadc);
	
	return;
}
