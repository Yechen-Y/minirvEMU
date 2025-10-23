#include "utils.h"
#define MemorySize 256

uint32_t PC = 0;
uint32_t R[32];
uint32_t M[MemorySize];

void inst_cycle() {
    decode_Ins(fetch_Ins());
    execute();
}

uint32_t fetch_Ins() 
{
    return M[PC];
}

void decode_Ins(uint32_t instruction)
{
    ins->opcode = instruction & 0b1111111; // 6 ~ 0
    ins->rd = (instruction >> 7) & 0b11111; // 11 ~ 7
    ins->funct3 = (instruction >> 12) & 0b111; // 14 ~ 12
    ins->rs1 = (instruction >> 15) & 0b11111; // 19 ~ 15
    ins->rs2 = (instruction >> 20) & 0b11111; // 24 ~ 20
    ins->funct7 = (instruction >> 25) & 0b1111111; // 31 ~ 25
}

void execute()
{
    switch (ins->opcode)
    {
    case 0b0010011: // I-type addi
        
        break;
    case 0b1100111: // I-type jalr

        break;
    default:
        break;
    }

}
