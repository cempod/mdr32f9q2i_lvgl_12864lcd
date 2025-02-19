#include "led.h"

void led_toggle(struct led *self)
{
    if (PORT_ReadInputDataBit(self->port, self->pin))
        led_off(self);
    else
        led_on(self);
    
}

void led_on(struct led *self)
{
    PORT_SetBits(self->port, self->pin);
}

void led_off(struct led *self)
{
    PORT_ResetBits(self->port, self->pin);
}

