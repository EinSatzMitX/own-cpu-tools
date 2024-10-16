#pragma once


#include "typedef.h"
typedef enum {
    TOKEN_OPCODE,    // Represents an instruction 
    TOKEN_REGISTER,  // Represents a register
    TOKEN_IMMEDIATE,  // Represents an immediate value like #5 | NOTE: This can also be an address but the behaviour will be the same
} TokenType; 

typedef union {
    u16 value;        // The full 16-bit immediate value
    struct {
        u8 low;       // Low byte
        u8 high;      // High byte
    };
} Immediate;

typedef struct{
  TokenType type;
  
  // using unions because we want to be cool!
  union{
    u8 opcode;
    u8 reg;
    // u16 val;
    Immediate val;
  };

} Token;

u8 get_opcode(const char* str);
u8 get_register(const char* str);
u16 get_immediate(const char* str);

int is_register(const char* str);
int is_immediate(const char* str);

void tokenize_string(const char* input, Token tokens[], int* token_count);

/* Define section */
/* Opcode defines */
/* 0x00 Opcodes: Moving instructions */
#define OPCODE_LOAD_REG_IMM 0x00 // Loads a specified value onto the specified register
#define OPCODE_LOAD_REG_REG 0x01 // Loads a value from one register into another register
#define OPCODE_LOAD_REG_ZPG 0x02 // Loads a value from a memory address into the specified register

/* 0x10 Opcodes: Store instructions */
#define OPCODE_STORE_LOW_MEM 0x10 // Stores the low byte of a register into the specified memory location
#define OPCODE_STORE_HIGH_MEM 0x11 // Stores the high byte of a register into the specified memory location
#define OPCODE_STORE_REG_MEM 0x12 // Stores an entire register to memory (low byte first)

/* 0x20 Opcodes: Compare instructions */
#define OPCODE_CMP_REG_REG 0x20 // Compares the first register with the second register and sets flags accordingly
#define OPCODE_CMP_REG_MEM 0x21 // Compares the register with a value in memory and sets flags accordingly
#define OPCODE_CMP_REG_IMM 0x22 // Compares the register with an immediate value and sets flags accordingly

/* 0x30 Opcodes: Branch instructions */
#define OPCODE_BRANCH_EQUAL 0x30 // Branches if the most recent comparison was equal (Zero flag set)
#define OPCODE_BRANCH_NOT_EQUAL 0x31 // Branches if the most recent comparison was NOT equal (Zero flag not set)
#define OPCODE_BRANCH_LESS_THAN 0x32 // Branches if the most recent equation resulted in the L flag being set
#define OPCODE_BRANCH_GREATER_THEN 0x33 // Branches if the most recent equation resulted in the Zero flag AND the Less flag not being set
#define OPCODE_BRANCH_LESS_OR_EQUAL 0x34 // Branches if the most recent equation resulted in the Zero flag OR the Less flag being set
#define OPCODE_BRANCH_GREATER_OR_EQUAL 0x35 // Branches if the most recent equation resulted in the Zero flag being set AND the Less flag not being set
#define OPCODE_BRANCH_OVERFLOW_CLEAR 0x36 // Branches if the most recent equation resulted in the Overflow flag being cleared
#define OPCODE_BRANCH_OVERFLOW_SET 0x37 // Branches if the most recent equation resulted in the Overflow flag being set
#define OPCODE_BRANCH_ALWAYS 0x38 // Simply branches

/* Subroutines */
#define OPCODE_JSR  0x39
#define OPCODE_RET  0x3A


/* 0x40 Opcodes: Arithmetical instructions */
#define OPCODE_ADD_SIGNED_REG_IMM 0x40 // Adds a signed immediate value to a specified register
#define OPCODE_SUB_SIGNED_REG_IMM 0x41 // Subtracts a signed immediate value from a specified register 
#define OPCODE_ADD_SIGNED_REG_MEM 0x42 // Adds a signed value from a specified memory address to a register
#define OPCODE_SUB_SIGNED_REG_MEM 0x43 // Subtracts a signed value from a specified memory address from a register
#define OPCODE_ADD_SIGNED_REG_REG 0x44 // Adds a signed value from one register to another
#define OPCODE_SUB_SIGNED_REG_REG 0x45 // Subtracts a signed value from one register from another

/* Unsigned Variants */
#define OPCODE_ADD_UNSIGNED_REG_IMM 0x46 // Adds an unsigned immediate value to a specified register
#define OPCODE_SUB_UNSIGNED_REG_IMM 0x47 // Subtracts an unsigned immediate value from a specified register 
#define OPCODE_ADD_UNSIGNED_REG_MEM 0x48 // Adds an unsigned value from a specified memory address to a register
#define OPCODE_SUB_UNSIGNED_REG_MEM 0x49 // Subtracts an unsigned value from a specified memory address from a register
#define OPCODE_ADD_UNSIGNED_REG_REG 0x4A // Adds an unsigned value from one register to another
#define OPCODE_SUB_UNSIGNED_REG_REG 0x4B // Subtracts an unsigned value from one register from another

/* 0x50 Opcodes: Logical instructions */
#define OPCODE_XOR_REG_IMM 0x50
#define OPCODE_XOR_REG_MEM 0x51
#define OPCODE_XOR_REG_REG 0x52

#define OPCODE_AND_REG_IMM 0x53
#define OPCODE_AND_REG_MEM 0x54
#define OPCODE_AND_REG_REG 0x55

#define OPCODE_NOT_REG 0x56

#define OPCODE_OR_REG_IMM 0x57
#define OPCODE_OR_REG_MEM 0x58
#define OPCODE_OR_REG_REG 0x59

#define OPCODE_LEFT_SHIFT_REG_IMM 0x5A
#define OPCODE_LEFT_SHIFT_REG_MEM 0x5B
#define OPCODE_LEFT_SHIFT_REG_REG 0x5C

#define OPCODE_RIGHT_SHIFT_REG_IMM 0x5D
#define OPCODE_RIGHT_SHIFT_REG_MEM 0x5E
#define OPCODE_RIGHT_SHIFT_REG_REG 0x5F


/* 0x60 Opcodes: Stack instructions */
#define OPCODE_PUSH_REG 0x60
#define OPCODE_POP_REG  0x61


/* 0xF0 Opcodes: Special instructions */
#define OPCODE_HALT 0xFE
#define OPCODE_NOOP 0xFF




/* Register defines */
#define REG0 0x00
#define REG1 0x01
#define REG2 0x02
#define REG3 0x03
#define REG4 0x04
#define REG5 0x05
#define REG6 0x06
#define REG7 0x07

#define REG_SP 0x10
#define REG_PC 0x11

/* Status flag definitions */
#define STATUS_FLAG_L 0b10000000 // Less flag
#define STATUS_FLAG_Z 0b01000000 // Zero flag
#define STATUS_FLAG_C 0b00100000 // Carry flag
#define STATUS_FLAG_V 0b00010000 // Overflow flag

#define STATUS_FLAG_S 0b00001000 // Sign flag
#define STATUS_FLAG_N 0b00000100 // Negative flag

