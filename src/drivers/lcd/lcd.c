#include "lcd.h"

static void send_command(struct lcd *self, uint8_t command, uint8_t part);
static void send_data(struct lcd *self, uint8_t data, uint8_t part);

void lcd_init(struct lcd *self) {
    PORT_ResetBits(self->res_port, self->res_pin);
    lcd_delay(100);
    PORT_SetBits(self->res_port, self->res_pin);
    lcd_delay(100);
    send_command(self, 0x3F, LCD_PART_LEFT);
    send_command(self, 0x3F, LCD_PART_RIGHT);
    lcd_fill(self, 1);
}

void lcd_fill(struct lcd *self, uint8_t color) {
    for (int8_t i = 0; i < 8; i++)
    {
        send_command(self, (0xB8|i), LCD_PART_LEFT);
        send_command(self, (0x40), LCD_PART_LEFT);
        for (uint8_t i = 0; i < 64; i++)
        {
            send_data(self, color ? 0xFF : 0x00, LCD_PART_LEFT);
        }
        send_command(self, (0xB8|i), LCD_PART_RIGHT);
        send_command(self, (0x40), LCD_PART_RIGHT);
        for (uint8_t i = 0; i < 64; i++)
        {
            send_data(self, color ? 0xFF : 0x00, LCD_PART_RIGHT);
        }
        
    }
    
}

__attribute__ ((weak)) int8_t lcd_delay(uint32_t ms) {    
    return -1;
}

static void send_command(struct lcd *self, uint8_t command, uint8_t part) {
    PORT_ResetBits(self->a0_port, self->a0_pin);
    PORT_ResetBits(self->rw_port, self->rw_pin);
    
    PORT_ResetBits(part ? self->e2_port : self->e1_port, part ? self->e2_pin : self->e1_pin);
    PORT_SetBits(part ? self->e1_port : self->e2_port, part ? self->e1_pin : self->e2_pin);

    for (int i = 0; i < 8; i++) {
        (command>>i & 0x01) ? PORT_SetBits(self->db_ports[i], self->db_pins[i]) : PORT_ResetBits(self->db_ports[i], self->db_pins[i]);
    }

    PORT_SetBits(self->e_port, self->e_pin);
    lcd_delay(1);
    PORT_ResetBits(self->e_port, self->e_pin);
}

static void send_data(struct lcd *self, uint8_t data, uint8_t part) {
    PORT_SetBits(self->a0_port, self->a0_pin);
    PORT_ResetBits(self->rw_port, self->rw_pin);
    
    PORT_ResetBits(part ? self->e2_port : self->e1_port, part ? self->e2_pin : self->e1_pin);
    PORT_SetBits(part ? self->e1_port : self->e2_port, part ? self->e1_pin : self->e2_pin);

    for (int i = 0; i<8; i++) {
        (data>>i & 0x01) ? PORT_SetBits(self->db_ports[i], self->db_pins[i]) : PORT_ResetBits(self->db_ports[i], self->db_pins[i]);
    }

    PORT_SetBits(self->e_port, self->e_pin);
    lcd_delay(1);
    PORT_ResetBits(self->e_port, self->e_pin);
}