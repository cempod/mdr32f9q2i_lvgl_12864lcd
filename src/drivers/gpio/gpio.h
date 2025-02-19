#ifndef GPIO_H_
#define GPIO_H_

#include <MDR32FxQI_port.h>

#include <stdint.h>

int8_t gpio_output_init(MDR_PORT_TypeDef *port, uint32_t pin_number);

#endif
