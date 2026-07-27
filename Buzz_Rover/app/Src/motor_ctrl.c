#include "motor_ctrl.h"

void Motor_EnableDriver(GPIO_RegMap_t *pSTBYPort, uint8_t STBYPin)
{
	GPIO_WriteToOutputPin(pSTBYPort, STBYPin, 1);
}


void Motor_DisableDriver(GPIO_RegMap_t *pSTBYPort, uint8_t STBYPin)
{
	GPIO_WriteToOutputPin(pSTBYPort, STBYPin, 0);
}

void Motor_SetDirection(Motor_Handle_t *pMotorHandle, Motor_Direction_t direction)
{
	switch(direction)
	{
	case MOTOR_DIR_FORWARD:
		GPIO_WriteToOutputPin(pMotorHandle->pIN1_Port, pMotorHandle->IN1_Pin, 1);
		GPIO_WriteToOutputPin(pMotorHandle->pIN2_Port, pMotorHandle->IN2_Pin, 0);
		break;
	case MOTOR_DIR_REVERSE:
		GPIO_WriteToOutputPin(pMotorHandle->pIN1_Port, pMotorHandle->IN1_Pin, 0);
		GPIO_WriteToOutputPin(pMotorHandle->pIN2_Port, pMotorHandle->IN2_Pin, 1);
		break;
	case MOTOR_DIR_BRAKE:
		GPIO_WriteToOutputPin(pMotorHandle->pIN1_Port, pMotorHandle->IN1_Pin, 1);
		GPIO_WriteToOutputPin(pMotorHandle->pIN2_Port, pMotorHandle->IN2_Pin, 1);
		break;
	case MOTOR_DIR_COAST:
		GPIO_WriteToOutputPin(pMotorHandle->pIN1_Port, pMotorHandle->IN1_Pin, 0);
		GPIO_WriteToOutputPin(pMotorHandle->pIN2_Port, pMotorHandle->IN2_Pin, 0);
		break;
	}
}

void Motor_SetSpeed(Motor_Handle_t *pMotorHandle, uint8_t duty_percent)
{
	TIM_SetDutyCycle(pMotorHandle->pPWM_Handle, duty_percent);
}

