#include <iostream>
#include <stdint.h>

int main(int argc, char* argv[])
{
    uint16_t value = 10;

    uint16_t result = value | value;

    std::cout << uint32_t(result) << std::endl;

    return 0;
}
