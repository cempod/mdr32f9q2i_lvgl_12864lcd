#include "gpio.h"

#include <MDR32FxQI_rst_clk.h>

#include <stddef.h>

static int8_t gpio_port_clock_enable(MDR_PORT_TypeDef *port);

int8_t gpio_output_init(MDR_PORT_TypeDef *port, uint32_t pin_number)
{
    if (port == NULL)
        return -1;

    if (gpio_port_clock_enable(port) != 0)
        return -2;

    PORT_InitTypeDef port_init;
    PORT_StructInit(&port_init);
    port_init.PORT_Pin   = pin_number;
    port_init.PORT_OE    = PORT_OE_OUT;
    port_init.PORT_FUNC  = PORT_FUNC_PORT;
    port_init.PORT_MODE  = PORT_MODE_DIGITAL;
    port_init.PORT_SPEED = PORT_SPEED_SLOW;
    PORT_Init(port, &port_init);

    return 0;
}

static int8_t gpio_port_clock_enable(MDR_PORT_TypeDef *port)
{
    switch ((intptr_t)port) {
        case (intptr_t)MDR_PORTA:
            RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTA, ENABLE);
            break;

        case (intptr_t)MDR_PORTB:
            RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTB, ENABLE);
            break;

        case (intptr_t)MDR_PORTC:
            RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTC, ENABLE);
            break;

        case (intptr_t)MDR_PORTD:
            RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTD, ENABLE);
            break;

        case (intptr_t)MDR_PORTE:
            RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTE, ENABLE);
            break;

        default:
            return -2;
            break;
    }
    
    return 0;
}
