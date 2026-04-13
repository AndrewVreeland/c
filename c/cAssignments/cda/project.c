#include "spimcore.h"


/* ALU */
/* 10 Points */
void ALU(unsigned A, unsigned B, char ALUControl, unsigned *ALUresult, char *Zero)
{
    switch (ALUControl)
    {
        case 0: /* Z = A + B */
            *ALUresult = A + B;
            break;
        case 1: /* Z = A - B */
            *ALUresult = A - B;
            break;
        case 2: /* Z = 1 if A < B (signed), else 0 */
            *ALUresult = ((int)A < (int)B) ? 1 : 0;
            break;
        case 3: /* Z = 1 if A < B (unsigned), else 0 */
            *ALUresult = (A < B) ? 1 : 0;
            break;
        case 4: /* Z = A AND B */
            *ALUresult = A & B;
            break;
        case 5: /* Z = A OR B */
            *ALUresult = A | B;
            break;
        case 6: /* Z = B shifted left by 16 bits */
            *ALUresult = B << 16;
            break;
        case 7: /* Z = NOT A */
            *ALUresult = ~A;
            break;
        default:
            *ALUresult = 0;
            break;
    }
    *Zero = (*ALUresult == 0) ? 1 : 0;
}

/* instruction fetch */
/* 10 Points */
int instruction_fetch(unsigned PC, unsigned *Mem, unsigned *instruction)
{
    /* Check word alignment */
    if (PC % 4 != 0)
        return 1; /* halt */

    /* Check memory bounds (64kB = 0x0000 to 0xFFFF) */
    if (PC >= 65536)
        return 1; /* halt */

    /* Fetch instruction: PC >> 2 gives the word index */
    *instruction = Mem[PC >> 2];
    return 0;
}


/* instruction partition */
/* 10 Points */
void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,
                           unsigned *r2, unsigned *r3, unsigned *funct,
                           unsigned *offset, unsigned *jsec)
{
    *op     = (instruction >> 26) & 0x3F; /* bits [31-26] */
    *r1     = (instruction >> 21) & 0x1F; /* bits [25-21] */
    *r2     = (instruction >> 16) & 0x1F; /* bits [20-16] */
    *r3     = (instruction >> 11) & 0x1F; /* bits [15-11] */
    *funct  = instruction & 0x3F;         /* bits [5-0]   */
    *offset = instruction & 0xFFFF;       /* bits [15-0]  */
    *jsec   = instruction & 0x3FFFFFF;    /* bits [25-0]  */
}



/* instruction decode */
/* 15 Points */
int instruction_decode(unsigned op, struct_controls *controls)
{
    /* Initialize all signals to don't care (2) */
    controls->RegDst   = 2;
    controls->Jump     = 2;
    controls->Branch   = 2;
    controls->MemRead  = 2;
    controls->MemtoReg = 2;
    controls->ALUOp    = 0;
    controls->MemWrite = 2;
    controls->ALUSrc   = 2;
    controls->RegWrite = 2;

    switch (op)
    {
        case 0x00: /* R-type: add, sub, and, or, slt, sltu */
            controls->RegDst   = 1;
            controls->Jump     = 0;
            controls->Branch   = 0;
            controls->MemRead  = 0;
            controls->MemtoReg = 0;
            controls->ALUOp    = 7; /* R-type: look at funct field */
            controls->MemWrite = 0;
            controls->ALUSrc   = 0;
            controls->RegWrite = 1;
            break;

        case 0x08: /* addi */
            controls->RegDst   = 0;
            controls->Jump     = 0;
            controls->Branch   = 0;
            controls->MemRead  = 0;
            controls->MemtoReg = 0;
            controls->ALUOp    = 0; /* addition */
            controls->MemWrite = 0;
            controls->ALUSrc   = 1;
            controls->RegWrite = 1;
            break;

        case 0x23: /* lw */
            controls->RegDst   = 0;
            controls->Jump     = 0;
            controls->Branch   = 0;
            controls->MemRead  = 1;
            controls->MemtoReg = 1;
            controls->ALUOp    = 0; /* addition for address */
            controls->MemWrite = 0;
            controls->ALUSrc   = 1;
            controls->RegWrite = 1;
            break;

        case 0x2B: /* sw */
            controls->RegDst   = 2; /* don't care */
            controls->Jump     = 0;
            controls->Branch   = 0;
            controls->MemRead  = 0;
            controls->MemtoReg = 2; /* don't care */
            controls->ALUOp    = 0; /* addition for address */
            controls->MemWrite = 1;
            controls->ALUSrc   = 1;
            controls->RegWrite = 0;
            break;

        case 0x04: /* beq */
            controls->RegDst   = 2; /* don't care */
            controls->Jump     = 0;
            controls->Branch   = 1;
            controls->MemRead  = 0;
            controls->MemtoReg = 2; /* don't care */
            controls->ALUOp    = 1; /* subtraction to compare */
            controls->MemWrite = 0;
            controls->ALUSrc   = 0;
            controls->RegWrite = 0;
            break;

        case 0x0A: /* slti */
            controls->RegDst   = 0;
            controls->Jump     = 0;
            controls->Branch   = 0;
            controls->MemRead  = 0;
            controls->MemtoReg = 0;
            controls->ALUOp    = 2; /* set less than signed */
            controls->MemWrite = 0;
            controls->ALUSrc   = 1;
            controls->RegWrite = 1;
            break;

        case 0x0B: /* sltiu */
            controls->RegDst   = 0;
            controls->Jump     = 0;
            controls->Branch   = 0;
            controls->MemRead  = 0;
            controls->MemtoReg = 0;
            controls->ALUOp    = 3; /* set less than unsigned */
            controls->MemWrite = 0;
            controls->ALUSrc   = 1;
            controls->RegWrite = 1;
            break;

        case 0x0F: /* lui */
            controls->RegDst   = 0;
            controls->Jump     = 0;
            controls->Branch   = 0;
            controls->MemRead  = 0;
            controls->MemtoReg = 0;
            controls->ALUOp    = 6; /* shift left by 16 */
            controls->MemWrite = 0;
            controls->ALUSrc   = 1;
            controls->RegWrite = 1;
            break;

        case 0x02: /* j (jump) */
            controls->RegDst   = 2; /* don't care */
            controls->Jump     = 1;
            controls->Branch   = 0;
            controls->MemRead  = 0;
            controls->MemtoReg = 2; /* don't care */
            controls->ALUOp    = 0; /* don't care */
            controls->MemWrite = 0;
            controls->ALUSrc   = 2; /* don't care */
            controls->RegWrite = 0;
            break;

        default:
            return 1; /* illegal instruction: halt */
    }
    return 0;
}

/* Read Register */
/* 5 Points */
void read_register(unsigned r1, unsigned r2, unsigned *Reg,
                   unsigned *data1, unsigned *data2)
{
    *data1 = Reg[r1];
    *data2 = Reg[r2];
}


/* Sign Extend */
/* 10 Points */
void sign_extend(unsigned offset, unsigned *extended_value)
{
    /* offset is 16 bits; sign-extend to 32 bits */
    if (offset & 0x8000) /* if bit 15 is set, it's negative */
        *extended_value = offset | 0xFFFF0000;
    else
        *extended_value = offset & 0x0000FFFF;
}

/* ALU operations */
/* 10 Points */
int ALU_operations(unsigned data1, unsigned data2, unsigned extended_value,
                   unsigned funct, char ALUOp, char ALUSrc,
                   unsigned *ALUresult, char *Zero)
{
    unsigned B;
    char ALUControl;

    /* Select second ALU input based on ALUSrc */
    B = (ALUSrc == 1) ? extended_value : data2;

    /* Determine ALUControl based on ALUOp */
    if (ALUOp == 7) /* R-type: decode funct field */
    {
        switch (funct)
        {
            case 0x20: ALUControl = 0; break; /* add  */
            case 0x22: ALUControl = 1; break; /* sub  */
            case 0x24: ALUControl = 4; break; /* and  */
            case 0x25: ALUControl = 5; break; /* or   */ 
            case 0x2A: ALUControl = 2; break; /* slt  */
            case 0x2B: ALUControl = 3; break; /* sltu */
            default:   return 1;              /* illegal funct: halt */
        }
    }
    else
    {
        ALUControl = ALUOp;
    }

    ALU(data1, B, ALUControl, ALUresult, Zero);
    return 0;
}

/* Read / Write Memory */
/* 10 Points */
int rw_memory(unsigned ALUresult, unsigned data2, char MemWrite, char MemRead,
              unsigned *memdata, unsigned *Mem)
{
    if (MemRead == 1 || MemWrite == 1)
    {
        /* Check word alignment */
        if (ALUresult % 4 != 0)
            return 1; /* halt */

        /* Check memory bounds */
        if (ALUresult >= 65536)
            return 1; /* halt */
    }

    if (MemRead == 1)
        *memdata = Mem[ALUresult >> 2];

    if (MemWrite == 1)
        Mem[ALUresult >> 2] = data2;

    return 0;
}


/* Write Register */
/* 10 Points */
void write_register(unsigned r2, unsigned r3, unsigned memdata,
                    unsigned ALUresult, char RegWrite, char RegDst,
                    char MemtoReg, unsigned *Reg)
{
    if (RegWrite == 1)
    {
        /* Select destination register */
        unsigned dest = (RegDst == 1) ? r3 : r2;

        /* Select data to write */
        unsigned data = (MemtoReg == 1) ? memdata : ALUresult;

        /* Never write to $zero (register 0) */
        if (dest != 0)
            Reg[dest] = data;
    }
}

/* PC update */
/* 10 Points */
void PC_update(unsigned jsec, unsigned extended_value, char Branch,
               char Jump, char Zero, unsigned *PC)
{
    /* Default: advance to next instruction */
    *PC = *PC + 4;

    /* Branch: if Branch signal and Zero flag both set, take the branch */
    if (Branch == 1 && Zero == 1)
        *PC = *PC + (extended_value << 2);

    /* Jump: replace PC with jump target address */
    if (Jump == 1)
        *PC = ((*PC) & 0xF0000000) | (jsec << 2);
}