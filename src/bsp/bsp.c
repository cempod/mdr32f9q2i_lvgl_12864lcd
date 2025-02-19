#include "bsp.h"
#include "rcc.h"
#include "drivers/gpio/gpio.h"

void bsp_init(void)
{
	rcc_config();

	gpio_output_init(MDR_PORTB, PORT_Pin_0 | PORT_Pin_1 | PORT_Pin_2 | PORT_Pin_3);
}

