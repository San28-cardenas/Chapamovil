
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stddef.h>
#include "ssd1306.h"
#include "font5x7.h"

#define FOSC 80000000UL
#define FCY  (FOSC/2)
#include <libpic30.h>

int main(void) {
    // Inicialización del OLED
    ssd1306_init();
    ssd1306_clear();

    // Mostrar texto en la pantalla
    ssd1306_drawString(0, 0, "Hola Mundo!", SSD1306_WHITE);
    ssd1306_update();

    while (1) {
        // Aquí puedes agregar lógica adicional
        __delay_ms(1000);
    }

    return 0;
}
