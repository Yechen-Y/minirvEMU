#include "utils.h"
#define MemorySize 256
#define I 1

uint32_t PC = 0;
uint32_t R[32];
uint32_t M[MemorySize] = {
    0x01400513u,
    0x010000e7u,
    0x00c000e7u,
    0x00c00067u,
    0x00a50513u,
    0x00008067u
};
uint8_t Flag;

void inst_cycle() {
    decode_Ins(fetch_Ins());
    execute();
}

uint32_t fetch_Ins() 
{
    return M[PC >> 2]; // 别忘记除4
}

void decode_Ins(uint32_t instruction)
{
    ins->opcode = instruction & 0x7fu; // 6 ~ 0
    ins->rd = (instruction >> 7) & 0x1fu; // 11 ~ 7
    ins->funct3 = (instruction >> 12) & 0x7u; // 14 ~ 12
    ins->rs1 = (instruction >> 15) & 0x1fu; // 19 ~ 15
    ins->rs2 = (instruction >> 20) & 0x1fu; // 24 ~ 20
    ins->funct7 = (instruction >> 25) & 0x7fu; // 31 ~ 25
}

void execute()
{
    switch (ins->opcode)
    {
    case 0x13u: // I-type addi
        if (ins->funct3 == 0) {
            Flag = I;
            if (ins->rd != 0) {
                R[ins->rd] = R[ins->rs1] + imm_Gen(Flag);
            }         
            PC += 4;
        } 
        break;
    case 0x67u: // I-type jalr
        if (ins->funct3 == 0) {
            Flag = I;
            if (ins->rd != 0) {
                R[ins->rd] = PC + 4;
            }          
            PC = R[ins->rs1] + imm_Gen(Flag);
        }
        break;
    default:
        break;
    }

}

int32_t imm_Gen(uint8_t flag) // 根据指令产生立即数
{
    int16_t rs2 = ins->rs2; // rs2实际只有低五位有值，所以这里的高位都为0
    int16_t funct7 = (int8_t)(ins->funct7 << 1 | (ins->funct7 & 1));
    switch (flag)
    {
    case I:
        return (int32_t)(funct7 << 5 | rs2);
        break;
    
    default:
        break;
    }
}
