#include "MsUart.h"

MsUart::MsUart(volatile uint8_t *ddr, volatile uint8_t *port, uint8_t pin)
{
    this->txPort = port;
    this->txDdr = ddr;
    this->txPin = pin;

    init();
}

void MsUart::init()
{
    *txDdr |= (1 << txPin);
    *txPort |= (1 << txPin);
}

void MsUart::transmitBit(uint8_t bit)
{
    if (bit)
    {
        *txPort |= (1 << txPin);
    }
    else
    {
        *txPort &= ~(1 << txPin);
    }
    _delay_us(BIT_DELAY_US);
}

void MsUart::transmit(uint8_t data)
{
    transmitBit(0);

    for (uint8_t i = 0; i < 8; i++)
    {
        transmitBit(data & 0x01);
        data >>= 1;
    }

    transmitBit(1);
}

void MsUart::print(const char *str)
{
    while (*str)
    {
        transmit(*str++);
    }
}

void MsUart::print(char ch)
{
    transmit(ch);
}

void MsUart::printNumber(uint16_t num)
{
    char buffer[6]; // 5 cyfr dla wartości od 0 do 1023 + 1 dla null terminatora
    int i = 5;
    buffer[i] = '\0'; // Null-terminator na końcu stringa

    do
    {
        buffer[--i] = (num % 10) + '0'; // Zapisz cyfrę jako znak
        num /= 10;
    } while (num > 0);

    print(&buffer[i]); // Wyślij string od pierwszej znaczącej cyfry
}