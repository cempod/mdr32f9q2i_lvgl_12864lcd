#include "bsp.h"
#include "rcc.h"
#include "drivers/gpio/gpio.h"

void bsp_init(void)
{
	rcc_config();

	gpio_output_init(MDR_PORTB, PORT_Pin_0 | PORT_Pin_1 | PORT_Pin_2 | PORT_Pin_3 | PORT_Pin_7 | PORT_Pin_8 | PORT_Pin_9 | PORT_Pin_10);
	gpio_output_init(MDR_PORTA, PORT_Pin_0 | PORT_Pin_1 | PORT_Pin_2 | PORT_Pin_3 | PORT_Pin_4 | PORT_Pin_5);
	gpio_output_init(MDR_PORTF, PORT_Pin_2 | PORT_Pin_3);
	gpio_output_init(MDR_PORTC, PORT_Pin_0 | PORT_Pin_1);
}

