#include <stdint.h>
#include <memory>
#include <string>
#include "misra_rules.h"

// The value returned by a function shall be used
static void misracpp2023_0_1_2()
{
    auto func = [](){ return 0; };
    func(); // return value not used here
}

static void misracpp2023_6_4_1_func(const std::allocator<uint8_t>& allocator)
{
    class Test
    {
    public:
        explicit Test(const std::allocator<uint8_t>& allocator) :
        //                                           ^ hides 'allocator' parameter to the func
                m_allocator(allocator)
        {

        };

        const std::allocator<uint8_t>& allocator() const
        //                             ^ hides 'allocator'parameter to the func
        {
            return m_allocator;
        }

        std::allocator<uint8_t> m_allocator;
    };

    Test t = Test(allocator);
    (void)t.allocator();
    (void)t;
}

// A variable declared in an inner scope shall not hide a variable declared in an outer scope
static void misracpp2023_6_4_1()
{
    std::allocator<uint8_t> allocator;
    misracpp2023_6_4_1_func(allocator);
}

static const std::string MISRACPP2023_6_7_2 = "MISRA C++ 2024 6.7.2 - Global variables shall not be used";

// Integral promotion or the usual arithmetic conversions shall not change the type signedness of an operand from 'uint16_t' to 'int'
static void misracpp2023_7_0_5()
{
    const uint16_t a = 0xff;
    const uint16_t b = 8;
    const uint16_t c = static_cast<uint16_t>(a << b);
    //                                         ^ integral promotions of a and b happen here, result is int
    (void)c;
}

// Assignment between numeric types shall be appropriate
static void misracpp2023_7_0_6()
{
    uint16_t a = 0x000f;
    uint16_t b = 0x00f0;
    uint16_t c = 0x0f00;
    uint16_t d = static_cast<uint16_t>(a | b) | c;
    //                                        ^ integral promotions of (a | b) and c happen here, result is int
    (void)d;
}

// C-style casts and functional casts shall not be used.
static void misracpp2023_8_2_2()
{
    const uint16_t value = 0xffff;
    const int16_t signed_value = (uint16_t)value;
    //                            ^ c-style cast used here
    const int16_t other_signed_value = uint16_t(value);
    //                            ^ functional cast used here
    (void)signed_value;
    (void)other_signed_value;
}

// Conversion operators and constructors that are callable with a single argument shall be explicit
static void misracpp2023_15_1_3()
{
    class NoExplicitCtor
    {
    public:
        NoExplicitCtor(uint32_t value) : // not explicit constructor here
                m_value(value)
        {}

        operator uint32_t() const // not explicit conversion operator here
        {
            return m_value;
        }

    private:
        uint32_t m_value;
    };

    auto func = [](const NoExplicitCtor& arg)
    {
        auto otherFunc = [](uint32_t value)
        {
            return value;
        };

        return otherFunc(arg);
    };

    constexpr uint32_t value = 4;
    (void)func(value);
}

// The body of an iteration-statement or a selection-statement shall be a compound-statement
static void misracpp2023_9_3_1()
{
    const bool cond = true;
    if (cond)
        return; // not a compound statement here

    for (uint32_t i = 0; i < 10; ++i)
        continue; // not a compound statement here
}

// reinterpret_cast shall not be used
static void misracpp2023_8_5_2()
{
    const uint32_t value = 0xff00ff00;
    const uint8_t* u8 = reinterpret_cast<const uint8_t*>(&value);
    (void)u8;
}

void misra_rules()
{
    misracpp2023_0_1_2();
    misracpp2023_6_4_1();
    (void)MISRACPP2023_6_7_2;
    misracpp2023_7_0_5();
    misracpp2023_7_0_6();
    misracpp2023_8_2_2();
    misracpp2023_9_3_1();
    misracpp2023_15_1_3();
}
