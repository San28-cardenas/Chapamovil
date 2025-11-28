#include "i2c.h"

void i2c_init(void) {
    I2C1BRG = 157; // Configuración para ~100kHz con Fcy=40MHz
    I2C1CONbits.I2CEN = 1; // Habilitar módulo I2C1
}

void i2c_start(void) {
    I2C1CONbits.SEN = 1;
    while (I2C1CONbits.SEN);
}

void i2c_stop(void) {
    I2C1CONbits.PEN = 1;
    while (I2C1CONbits.PEN);
}

void i2c_write(uint8_t data) {
    I2C1TRN = data;
    while (I2C1STATbits.TBF);   // Esperar que se vacíe el buffer
    while (I2C1STATbits.TRSTAT); // Esperar fin de transmisión
}