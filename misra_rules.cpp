#include <stdint.h>
#include "misra_rules.h"

// Integral promotion or the usual arithmetic conversions shall not change the type signedness of an operand from 'uint16_t' to 'int'
static void misracpp2023_7_0_5_a()
{
    const uint16_t a = 0xff;
    const uint16_t b = 8;
    const uint16_t c = static_cast<uint16_t>(a << b);
    //                                          ^ integral promotions of a and b happen here, result is int
    (void)c;
}

// Do not use a value of type 'int' to initialize a variable of type 'uint16_t'
static void misracpp2023_7_0_6_a()
{
    uint16_t a = 0x000f;
    uint16_t b = 0x00f0;
    uint16_t c = 0x0f00;
    uint16_t d = static_cast<uint16_t>(a | b) | c;
    //                                        ^ integral promotions of (a | b) and c happen here, result is int
    (void)d;
}

void misra_rules()
{
    misracpp2023_7_0_5_a();
    misracpp2023_7_0_6_a();
}
