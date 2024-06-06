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
        if (a > b) // noncompliant - doesn't work probably due to integral promotions?
        {
            a = c;
        }
        unused(a, b, c);
    }

    // mix signed 32 and unsigned 16
    {
        int32_t a = 10;
        uint16_t b = 11;
        int32_t c  = (a > b) ? a : b; // noncompliant - doesn't work probably due to integral promotions?

        unused(a, b, c);
    }

    // shift unsigned 16 using unsigned 8
    {
        uint16_t a = 0x00FF;
        uint8_t b = 8;
        // a << b will become 'int' due to integral promotions, why is it ok to assign int to uint16_t without cast?
        uint16_t c = a << b;

        unused(a, b, c);
    }

    // multiple binary or-s
    {
        uint16_t a = 0x0F;
        uint16_t b = 0xF0;
        uint16_t c = 0xFF00;
        // a | b will become 'int' due to integral promotions
        // - why is it ok to do or with c without cast
        // a | b | c will become 'int' due to integral promotions
        // - why is it ok to assign to int to uint16_t without cast?
        uint16_t d = a | b | c;

        unused(a, b, c, d);
    }
}

// Results of ~ and << operations on operands of underlying types unsigned char and unsigned short should immediately be cast to the operand's underlying type
void s853()
{
    // original example
    {
        uint8_t port = 0x5aU;
        uint8_t result_8;
        uint16_t result_16;
        uint16_t mode;
        result_8 = (~port) >> 4; // noncompliant
        result_16 = ((port << 4) & mode) >> 6; // noncompliant
    }
}

int main(int argc, char* argv[])
{
    s845();
    s853();

    return 0;
}
