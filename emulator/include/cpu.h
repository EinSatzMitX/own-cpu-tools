#pragma once

#include <stdio.h>

#include "typedef.h"

typedef struct{
  // General Purpose Registers
  // u16 r0;
  // u16 r1;
  // u16 r2;
  // u16 r3;
  // u16 r4;
  // u16 r5;
  // u16 r6;
  // u16 r7;
  u16 r[8];

  // Program Counter
  u16 pc;

  //Stack Pointer
  u8 sp;

  // Status Flags
  // LAYOUT: 0b0 0 0 0  0 0 0 0
  //           L Z C V  S N  
  //           L: Less
  //           Z: Zero
  //           C: Carry
  //           V: Overflow
  //           S: Signed
  //           N: Negative
  u8 status_flags;

  u8 memory[0x10000];

  u64 clock_cycles;

} CPU;

extern CPU *cpu;

CPU* get_CPU();
u8 get_status_flags();
u16 get_r0();
u16 get_r1();
u16 get_r2();
u16 get_r3();
u16 get_r4();
u16 get_r5();
u16 get_r6();
u16 get_r7();
u16 get_pc();
u16 get_sp();

u8 fetch();
u16 fetch_word();

void execute(u8 opcode);
void run();

int is_flag_set(u8 flag);
void set_flag(u8 flag);
void clear_flag(u8 flag);

void set_pc(u16 val);
void set_sp(u8 val);

void push(u8 val);
u8 pop();

void push16(u16 val);
u16 pop16();


void load_program(u8* program, size_t program_size, u16 start_addr);
void load_program_from_file(const char* filename, u16 start_addr);
