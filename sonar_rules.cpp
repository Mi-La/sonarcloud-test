#include <stdint.h>
#include "sonar_rules.h"

// Signed and unsigned types should not be mixed in expressions
static void s845()
{
    // official example
    {
        int32_t a = 10;
        const uint32_t b = a; // noncompliant
        const int32_t c = (a > 0) ? a : b; // noncompliant
        if (a > b) // noncompliant
        {
            a = c;
            (void)a;
        }
    }

    // 16-bit
    {
        int16_t a = 10;
        const uint16_t b = a; // noncompliant
        const int16_t c = (a > 0) ? a : b; // noncompliant
        if (a > b) // noncompliant - doesn't work probably due to integral promotions?
        {
            a = c;
            (void)a;
        }
    }

    // mix signed 32 and unsigned 16
    {
        const int32_t a = 10;
        const uint16_t b = 11;
        const int32_t c  = (a > b) ? a : b; // noncompliant - doesn't work probably due to integral promotions?

        (void)c;
    }

    // shift unsigned 16 using unsigned 8
    {
        const uint16_t a = 0x00FF;
        const uint8_t b = 8;
        // a << b will become 'int' due to integral promotions, why is it ok to assign int to uint16_t without cast?
        const uint16_t c = a << b;

        (void)c;
    }

    // multiple binary or-s
    {
        const uint16_t a = 0x0F;
        const uint16_t b = 0xF0;
        const uint16_t c = 0xFF00;
        // a | b will become 'int' due to integral promotions
        // - why is it ok to do or with c without cast
        // a | b | c will become 'int' due to integral promotions
        // - why is it ok to assign to int to uint16_t without cast?
        const uint16_t d = a | b | c;
        const uint16_t e = static_cast<uint16_t>(a | b) | c;

        (void)d;
        (void)e;
    }
}

// Results of ~ and << operations on operands of underlying types unsigned char and unsigned short should immediately be cast to the operand's underlying type
static void s853()
{
    // original example
    {
        const uint8_t port = 0x5aU;
        uint8_t result_8;
        uint16_t result_16;
        const uint16_t mode = 0x0f;
        result_8 = (~port) >> 4; // noncompliant
        result_16 = ((port << 4) & mode) >> 6; // noncompliant

        (void)result_8;
        (void)result_16;
    }
}

static auto s874_f(int i)
{
    return 1 << i; // noncompliant
}

// Bitwise operators should not be applied to signed operands
static void s874()
{
    // original example
    {
        const uint16_t a = 0xff;
        const int16_t b = 0x0f;
        if (( a & b ) == 0x1234U) // noncompliant until C++20
        {
            // empty
        }

        if (~b == 0x1234U) // noncompliant until C++20
        {
            // empty
        }
        (void)s874_f(b);
    }
}

void sonar_rules()
{
    s845();
    s853();
    s874();
}
