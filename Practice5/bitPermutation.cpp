#include "../functions.hpp"
using namespace std;

int main()
{
    // 1 Exercise 
    unsigned char data = 'K';

    printf("1) Initial value\n");
    printf("Character: %c\n", data);
    printf("Hexadecimal: 0x%X\n", data);
    printf("Integer: %u\n\n", data);

    // 2 Exercise LSHIFT
    printf("2) Left shift\n");
    for (int i = 0; i < 8; i++)
    {
        data = data << 1;
        printf("Shift %d\n", i + 1);
        printf("Character: %c\n", data);
        printf("Hexadecimal: 0x%X\n", data);
        printf("Integer: %u\n\n", data);
    }

    // 3 Exercise RSHIFT
    data = 'A';
    printf("3) Right shift\n");
    for (int i = 0; i < 8; i++)
    {
        data = data >> 1;
        printf("Shift %d\n", i + 1);
        printf("Character: %c\n", data);
        printf("Hexadecimal: 0x%X\n", data);
        printf("Integer: %u\n\n", data);
    }

    // 4 Exercise - bitwise AND, OR, XOR
    unsigned char v1 = 'D'; // 0x44 = 68
    unsigned char v2 = 'M'; // 0x4D = 77

    unsigned char result_and = v1 & v2;
    unsigned char result_or  = v1 | v2;
    unsigned char result_xor = v1 ^ v2;

    printf("4) Bitwise operations\n");
    printf("v1 = %c -> 0x%X -> %u\n", v1, v1, v1);
    printf("v2 = %c -> 0x%X -> %u\n\n", v2, v2, v2);

    printf("AND: 0x%X -> %u\n", result_and, result_and);
    printf("OR : 0x%X -> %u\n", result_or, result_or);
    printf("XOR: 0x%X -> %u\n\n", result_xor, result_xor);

    // 5 Exercise - obtain most significant bit
    unsigned char data2 = 'R';   // 0x52 = 01010010
    unsigned char mask = 0x80;   // 10000000
    unsigned char result = data2 & mask;

    printf("5) Most significant bit\n");
    printf("data2 = %c -> 0x%X -> %u\n", data2, data2, data2);
    printf("Mask  = 0x%X\n", mask);
    printf("Result: 0x%X -> %u\n\n", result, result);

    // 6 Exercise - obtain 4 least significant bits
    data2 = 'V';                 // 0x56 = 01010110
    mask = 0x0F;                 // 00001111
    result = data2 & mask;

    printf("6) Four least significant bits\n");
    printf("data2 = %c -> 0x%X -> %u\n", data2, data2, data2);
    printf("Mask  = 0x%X\n", mask);
    printf("Result: 0x%X -> %u\n", result, result);

    return 0;
}