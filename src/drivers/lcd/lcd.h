#ifndef LCD_H_
#define LCD_H_

#include <MDR32FxQI_port.h>

enum lcd_parts {
    LCD_PART_RIGHT = 0,
    LCD_PART_LEFT
};

struct lcd {
    MDR_PORT_TypeDef *db_ports[8];
    uint32_t db_pins[8];
    MDR_PORT_TypeDef *e1_port;
    uint32_t e1_pin;
    MDR_PORT_TypeDef *e2_port;
    uint32_t e2_pin;
    MDR_PORT_TypeDef *res_port;
    uint32_t res_pin;
    MDR_PORT_TypeDef *rw_port;
    uint32_t rw_pin;
    MDR_PORT_TypeDef *a0_port;
    uint32_t a0_pin;
    MDR_PORT_TypeDef *e_port;
    uint32_t e_pin;
};

int8_t lcd_delay(uint32_t us);

void lcd_init(struct lcd *self);
void lcd_fill(struct lcd *self, uint8_t color);


#endif