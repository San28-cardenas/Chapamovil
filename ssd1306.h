#ifndef SSD1306_H
#define SSD1306_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#define SSD1306_WIDTH   128
#define SSD1306_HEIGHT   32
#define SSD1306_I2C_ADDR 0x3C   // 7-bit (0x3C o 0x3D según tu módulo)

typedef enum { SSD1306_BLACK = 0, SSD1306_WHITE = 1 } ssd1306_color_t;

void ssd1306_init(void);
void ssd1306_powerOn(void);
void ssd1306_powerOff(void);
void ssd1306_setContrast(uint8_t val);
void ssd1306_invert(bool enable);

void ssd1306_clear(void);
void ssd1306_update(void);                    // Envía todo el buffer (4 páginas x 128 bytes)
void ssd1306_drawPixel(uint8_t x, uint8_t y, ssd1306_color_t c);

// Helpers de dibujo y texto
void ssd1306_drawFastHLine(uint8_t x, uint8_t y, uint8_t w, ssd1306_color_t c);
void ssd1306_drawFastVLine(uint8_t x, uint8_t y, uint8_t h, ssd1306_color_t c);
void ssd1306_drawChar(uint8_t x, uint8_t y, char ch, ssd1306_color_t c);
void ssd1306_drawString(uint8_t x, uint8_t y, const char *s, ssd1306_color_t c);

// Acceso al framebuffer por si quieres dibujar fuera del driver
uint8_t* ssd1306_getBuffer(void);

#endif // SSD1306_H