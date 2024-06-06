#include <iostream>
#include <stdint.h>

template <typename... T>
void unused(T...)
{}

// Signed and unsigned types should not be mixed in expressions
void s845()
{
    // official example
    {
        int32_t a = 10;
        uint32_t b = a; // noncompliant
        int32_t c = (a > 0) ? a : b; // noncompliant
        if (a > b) // noncompliant
        {
            a = c;
        }
        unused(a, b, c);
    }

    // 16-bit
    {
        int16_t a = 10;
        uint16_t b = a; // noncompliant
        int16_t c = (a > 0) ? a : b; // noncompliant
        if (a > b) // non-compliant - doesn't work probably due to integral promotions?
        {
            a = c;
        }
        unused(a, b, c);
    }

    // mix signed 32 and unsigned 16
    {
        int32_t a = 10;
        uint16_t b = 11;
        int32_t c  = (a > b) ? a : b; // non-compliant - doesn't work probably due to integral promotions?

        unused(a, b, c);
    }

    // shift unsigned 16 using unsigned 8
    {
        uint16_t a = 0x00FF;
        uint8_t b = 8;
        uint16_t c = a << b;

        unused(a, b, c);
    }

    // multiple binary or-s
    {
        uint16_t a = 0x0F;
        uint16_t b = 0xF0;
        uint16_t c = 0xFF00;
        uint16_t d = a | b | c;

        unused(a, b, c, d);
    }
}

// Results of ~ and << operations on operands of underlying types unsigned char and unsigned short should immediately be cast to the operand's underlying type
void s853()
{
    // TBD
}

int main(int argc, char* argv[])
{
    s845();
    s853();

    return 0;
}
