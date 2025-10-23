#ifndef UTILS
#define UTILS

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>


extern struct ins
{
    uint8_t opcode;
    uint8_t rd;
    uint8_t rs1;
    uint8_t rs2;
    uint8_t funct3;
    uint8_t funct7;
} *ins;



#endif