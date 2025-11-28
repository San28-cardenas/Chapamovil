#include "ssd1306.h"
#include "font5x7.h"
#include "i2c.h"

static uint8_t buffer[SSD1306_WIDTH * SSD1306_HEIGHT / 8];

static void ssd1306_command(uint8_t cmd) {
    i2c_start();
    i2c_write(SSD1306_I2C_ADDR << 1); // Dirección + Write
    i2c_write(0x00); // Control byte: Co=0, D/C#=0 (comando)
    i2c_write(cmd);
    i2c_stop();
}

void ssd1306_init(void) {
    i2c_init();

    ssd1306_command(0xAE); // Display OFF
    ssd1306_command(0xA8); ssd1306_command(0x1F); // Multiplex ratio (altura 32)
    ssd1306_command(0xD3); ssd1306_command(0x00); // Display offset
    ssd1306_command(0x40); // Start line
    ssd1306_command(0xA1); // Segment remap
    ssd1306_command(0xC8); // COM scan direction
    ssd1306_command(0xDA); ssd1306_command(0x02); // COM pins config
    ssd1306_command(0x81); ssd1306_command(0x7F); // Contraste
    ssd1306_command(0xA4); // Seguir RAM
    ssd1306_command(0xA6); // Normal display
    ssd1306_command(0xAF); // Display ON
}

void ssd1306_clear(void) {
    for (int i = 0; i < sizeof(buffer); i++) {
        buffer[i] = 0x00;
    }
}

void ssd1306_update(void) {
    for (uint8_t page = 0; page < 4; page++) {
        ssd1306_command(0xB0 + page); // Set page
        ssd1306_command(0x00);        // Low column
        ssd1306_command(0x10);        // High column

        i2c_start();
        i2c_write(SSD1306_I2C_ADDR << 1);
        i2c_write(0x40); // Control byte: Co=0, D/C#=1 (datos)
        for (uint8_t col = 0; col < SSD1306_WIDTH; col++) {
            i2c_write(buffer[page * SSD1306_WIDTH + col]);
        }
        i2c_stop();
    }
}

void ssd1306_drawPixel(uint8_t x, uint8_t y, ssd1306_color_t c) {
    if (x >= SSD1306_WIDTH || y >= SSD1306_HEIGHT) return;
    uint16_t index = x + (y / 8) * SSD1306_WIDTH;
    if (c == SSD1306_WHITE)
        buffer[index] |= (1 << (y & 7));
    else
        buffer[index] &= ~(1 << (y & 7));
}

void ssd1306_drawChar(uint8_t x, uint8_t y, char ch, ssd1306_color_t c) {
    if (ch < 32 || ch > 127) return;
    const uint8_t *glyph = Font5x7[ch - 32];
    for (uint8_t i = 0; i < 5; i++) {
        uint8_t line = glyph[i];
        for (uint8_t j = 0; j < 7; j++) {
            if (line & (1 << j)) {
                ssd1306_drawPixel(x + i, y + j, c);
            }
        }
    }
}

void ssd1306_drawString(uint8_t x, uint8_t y, const char *s, ssd1306_color_t c) {
    while (*s) {
        ssd1306_drawChar(x, y, *s++, c);
        x += 6; // 5 columnas + 1 espacio
    }
}