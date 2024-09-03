#ifndef MS_UART_H
#define MS_UART_H

#include <avr/io.h>
#include <util/delay.h>

#define BAUD 9600                       // Prędkość transmisji
#define BIT_DELAY_US (1000000UL / BAUD) // Czas trwania jednego bitu w mikrosekundach

class MsUart
{
private:
    uint8_t txPin;
    volatile uint8_t *txPort;
    volatile uint8_t *txDdr;

    void init();
    void transmitBit(uint8_t bit);
    void transmit(uint8_t data);

public:
    MsUart(volatile uint8_t *ddr, volatile uint8_t *port, uint8_t pin);

    void print(const char *str);
    void print(char ch);
    void printNumber(uint16_t num);
};

#endif // MS_UART_H