#include <stdint.h>
#include <memory>
#include "misra_rules.h"

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

static const std::string MISRACPP2024_6_7_3 = "MISRA C++ 2024 6.4.2 - Global variables shall not be used";

// Integral promotion or the usual arithmetic conversions shall not change the type signedness of an operand from 'uint16_t' to 'int'
static void misracpp2023_7_0_5()
{
    const uint16_t a = 0xff;
    const uint16_t b = 8;
    const uint16_t c = static_cast<uint16_t>(a << b);
    //                                         ^ integral promotions of a and b happen here, result is int
    (void)c;
}

// Do not use a value of type 'int' to initialize a variable of type 'uint16_t'
static void misracpp2023_7_0_6()
{
    uint16_t a = 0x000f;
    uint16_t b = 0x00f0;
    uint16_t c = 0x0f00;
    uint16_t d = static_cast<uint16_t>(a | b) | c;
    //                                        ^ integral promotions of (a | b) and c happen here, result is int
    (void)d;
}

static void misracpp2023_15_1_3()
{
    class NoExplicitCtor
    {
    public:
        NoExplicitCtor(uint32_t value) :
                m_value(value)
        {}

        uint32_t get() const
        {
            return m_value;
        }

    private:
        uint32_t m_value;
    };


    auto func = [](const NoExplicitCtor& arg)
    {
        return arg.get();
    };

    constexpr uint32_t value = 4;
    (void)func(value);
}

void misra_rules()
{
    misracpp2023_6_4_1();
    (void)MISRACPP2024_6_7_3;
    misracpp2023_7_0_5();
    misracpp2023_7_0_6();
    misracpp2023_15_1_3();
}
