 /********************************************************************************
  * @file    main.c
  * @author  Supreeth
  * @version V1.0
  * @date    07-May-2020
  *
  * @brief   Interfacing push button with stm32f446re
  *
  * Overview
  * --------
  * This application toggle the User LED(LD2, Green), if there is a key press
  * event from the user otherwise the LED remains in OFF state.
  *
  * User LED(LD2, Green) is connected to PA5.
  * User Button(B1, Blue in Color) is connected to PC13
  *
  * Runs on stm32f446re
  *
  *******************************************************************************/


#include "stm32f4xx.h"
#include "stm32f4xx_nucleo.h"

void LED_Init(void);
void Button_Init(void);

int main(void)
{
	HAL_Init();
	LED_Init();
	Button_Init();

	for(;;) {
		if (HAL_GPIO_ReadPin(USER_BUTTON_GPIO_PORT, USER_BUTTON_PIN) == GPIO_PIN_RESET) {
			HAL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);
			HAL_Delay(100);
		} else {
			HAL_GPIO_WritePin(LED2_GPIO_PORT, LED2_PIN, GPIO_PIN_RESET);
		}

	}
}

/**********************************************************************
 *
 * @brief PortA Initialization for User LED(LD2, Green)
 *
 * User LED(LD2, Green) is connected to PA5.
 *
 * @param  None
 *
 * @return None
 *
 *********************************************************************/
void LED_Init(void)
{
	GPIO_InitTypeDef ledGPIO;

	/* Enable Clock for GPIOA Port */
	__HAL_RCC_GPIOA_CLK_ENABLE();

	ledGPIO.Mode  = GPIO_MODE_OUTPUT_PP;
	ledGPIO.Pin   = LED2_PIN;
	ledGPIO.Speed = GPIO_SPEED_FREQ_LOW;

	HAL_GPIO_Init(LED2_GPIO_PORT, &ledGPIO);
}


/**********************************************************************
 *
 * @brief PortC Initialization for User Button(B1, Blue)
 *
 * User Button(B1, Blue in Color) is connected to PC13.
 *
 * @param  None
 *
 * @return None
 *
 * @note Button has a built-in Pull Up Resistor. On pressing the button,
 * 		 the pin goes from a HIGH to LOW state.
 *
 *********************************************************************/
void Button_Init(void)
{
	GPIO_InitTypeDef btnGPIO;

	/* Enable Clock for GPIOC Port */
	__HAL_RCC_GPIOC_CLK_ENABLE();

	btnGPIO.Mode  = GPIO_MODE_INPUT;
	btnGPIO.Pin   = GPIO_PIN_13;
	btnGPIO.Pull  = GPIO_NOPULL;
	btnGPIO.Speed = GPIO_SPEED_FREQ_LOW;

	HAL_GPIO_Init(USER_BUTTON_GPIO_PORT, &btnGPIO);
}
