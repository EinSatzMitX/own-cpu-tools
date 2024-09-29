#include <stdlib.h>
#include <string.h>

#include "cpu.h"
#include "logging.h"
#include "opcode.h"
#include "typedef.h"

CPU *cpu = NULL;

CPU* get_CPU(){
  if (cpu == NULL){
    cpu = (CPU*)malloc(sizeof(cpu));
    memset(cpu->r, 0, sizeof(cpu->r)); 
    cpu->sp = 0x0000;
    cpu->pc = 0x0000;
    cpu->status_flags = 0x00;
    cpu->clock_cycles = 0x0000;
    memset(cpu->memory, 0xFF, sizeof(cpu->memory));
  }

  return cpu;
}
u8 get_status_flags(){
  return cpu->status_flags;
}
u16 get_r0(){
  return cpu->r[0];
}
u16 get_r1(){
  return cpu->r[1];
}
u16 get_r2(){
  return cpu->r[2];
}
u16 get_r3(){
  return cpu->r[3];
}
u16 get_r4(){
  return cpu->r[4];
}
u16 get_r5(){
  return cpu->r[5];
}
u16 get_r6(){
  return cpu->r[6];
}
u16 get_r7(){
  return cpu->r[7];
}
u16 get_pc(){
  return cpu->pc;
}
u16 get_sp(){
  return cpu->sp;
}

u8 fetch(){
  u8 opcode = cpu->memory[cpu->pc];
  if (cpu->pc == 0xFFFF){
    cpu->pc = 0;
  }else {
    cpu->pc += 1;
  }
  return opcode;
}

void execute(u8 opcode){
  u64 cycles = 0;

  switch (opcode) {
    case OPCODE_LOAD_REG_IMM:{ // LVR Loads an immediate value into a register
      u8 reg = fetch();
      u8 val_low = fetch();
      u8 val_high = fetch();
       
      if (reg < 8) {
        cpu->r[reg] = (val_high << 8) | val_low;
      } else {
        log_output(LOG_LEVEL_ERROR, "Invalid register: r%d", reg);
      }
      break;
    }
    case OPCODE_LOAD_REG_REG: {// LRR Loads data from one register into another
      u8 dest_reg = fetch();
      u8 src_reg = fetch();

      if (src_reg < 8 && dest_reg < 8){
        cpu->r[dest_reg] = cpu->r[src_reg];
      } else {
        log_output(LOG_LEVEL_ERROR, "Invalid source or destination register: r%d", src_reg, dest_reg);
      }
      break;
    }
    case OPCODE_LOAD_REG_ZPG: {// LMR Loads data from a specified memory address into the specifiedregister
      u8 reg = fetch();
      u8 addr_low = fetch();
      u8 addr_high = fetch();

      if (reg < 8){
        cpu->r[reg] = (cpu->memory[addr_high] << 8) | (cpu->memory[addr_low]);
      } else {
        log_output(LOG_LEVEL_ERROR, "Invalid register: r%d", reg);
      } 
      break;
    }
    case OPCODE_STORE_REG_MEM: {
      u8 reg = fetch();
      u8 addr_low = fetch();
      u8 addr_high = fetch();

      u16 addr = (addr_high << 8) | (addr_low);

      if (reg < 8){
        cpu->memory[addr] = (cpu->r[reg] & 0x00FF); 
        cpu->memory[addr + 1] = ((cpu->r[reg] >> 8) & 0x00FF);
      }else {
        log_output(LOG_LEVEL_ERROR, "Invalid register: r%d", reg);
      }
      break;
    }
    case OPCODE_STORE_LOW_MEM: {
      u8 reg = fetch();
      u8 addr_low = fetch();
      u8 addr_high = fetch();

      u16 addr = (addr_high << 8) | (addr_low);

      if (reg < 8){
        cpu->memory[addr] = (cpu->r[reg] & 0x00FF); 
      }else {
        log_output(LOG_LEVEL_ERROR, "Invalid register: r%d", reg);
      }
      break;
    }
    case OPCODE_STORE_HIGH_MEM: {
      u8 reg = fetch();
      u8 addr_low = fetch();
      u8 addr_high = fetch();

      u16 addr = (addr_high << 8) | (addr_low);

      if (reg < 8){
        cpu->memory[addr + 1] = ((cpu->r[reg] >> 8) & 0xFF00);
      }
      else{
        log_output(LOG_LEVEL_ERROR, "Invalid register: r%d", reg);
      }
      break;
    }
    case OPCODE_CMP_REG_REG: {
      u8 reg_a = fetch();
      u8 reg_b = fetch();

      if (reg_a < 8 && reg_b < 8){
        // Read the values inthe registers
        u16 value_a = cpu->r[reg_a]; 
        u16 value_b = cpu->r[reg_b];

        i16 signed_value_a = (i16)value_a;
        i16 signed_value_b = (i16)value_b;

        // Clear all relevant flags so nothing gets messed up here
        clear_flag(STATUS_FLAG_Z);
        clear_flag(STATUS_FLAG_L);
        clear_flag(STATUS_FLAG_C);
        clear_flag(STATUS_FLAG_V);

        // Now compare
        if (signed_value_a == signed_value_b){
          set_flag(STATUS_FLAG_Z);
        }
        else if (signed_value_a < signed_value_b){
          set_flag(STATUS_FLAG_L);
          set_flag(STATUS_FLAG_C);
        } else {
          clear_flag(STATUS_FLAG_C);
          clear_flag(STATUS_FLAG_L);
        }

        // Check for signed overflow
        if (((value_a ^ value_b) & (value_a ^(value_a - value_b))) & 0x8000){
          set_flag(STATUS_FLAG_V);
        }

      } else {
        log_output(LOG_LEVEL_ERROR, "Invalid register: r%d, r%d", reg_a, reg_b);
      }
      break;
    }
    case OPCODE_CMP_REG_MEM:{
      u8 reg = fetch();
      u8 addr_low = fetch();
      u8 addr_high = fetch();

      u16 addr = (addr_high << 8) | addr_low;

      if (reg < 8){
        // Read the values inthe registers
        u16 value_a = cpu->r[reg]; 
        u16 value_b = cpu->memory[addr];

        i16 signed_value_a = (i16)value_a;
        i16 signed_value_b = (i16)value_b;

        // Clear all relevant flags so nothing gets messed up here
        clear_flag(STATUS_FLAG_Z);
        clear_flag(STATUS_FLAG_L);
        clear_flag(STATUS_FLAG_C);
        clear_flag(STATUS_FLAG_V);

        // Now compare
        if (signed_value_a == signed_value_b){
          set_flag(STATUS_FLAG_Z);
        }
        else if (signed_value_a < signed_value_b){
          set_flag(STATUS_FLAG_L);
          set_flag(STATUS_FLAG_C);
        } else {
          clear_flag(STATUS_FLAG_C);
          clear_flag(STATUS_FLAG_L);
        }

        // Check for signed overflow
        if (((value_a ^ value_b) & (value_a ^(value_a - value_b))) & 0x8000){
          set_flag(STATUS_FLAG_V);
        }

      } else {
        log_output(LOG_LEVEL_ERROR, "Invalid register: r%d", reg);
      }
      break;
    }
    case OPCODE_CMP_REG_IMM:{
      u8 reg = fetch();
      u8 val_low = fetch();
      u8 val_high = fetch();

      u16 value = (val_high << 8) | val_low;

      if (reg < 8){
        // Read the values inthe registers
        u16 value_a = cpu->r[reg]; 
        u16 value_b = value;

        i16 signed_value_a = (i16)value_a;
        i16 signed_value_b = (i16)value_b;

        // Clear all relevant flags so nothing gets messed up here
        clear_flag(STATUS_FLAG_Z);
        clear_flag(STATUS_FLAG_L);
        clear_flag(STATUS_FLAG_C);
        clear_flag(STATUS_FLAG_V);

        // Now compare
        if (signed_value_a == signed_value_b){
          set_flag(STATUS_FLAG_Z);
        }
        else if (signed_value_a < signed_value_b){
          set_flag(STATUS_FLAG_L);
          set_flag(STATUS_FLAG_C);
        } else {
          clear_flag(STATUS_FLAG_C);
          clear_flag(STATUS_FLAG_L);
        }

        // Check for signed overflow
        if (((value_a ^ value_b) & (value_a ^(value_a - value_b))) & 0x8000){
          set_flag(STATUS_FLAG_V);
        }

      } else {
        log_output(LOG_LEVEL_ERROR, "Invalid register: r%d", reg);
      }
      break;
    }


    default:
      log_output(LOG_LEVEL_ERROR, "Unknown opcode: 0x%02x", opcode);
      break;
  }
}

void run(){
  while (cpu->pc < 0x000B){
    log_output(LOG_LEVEL_INFO, "Fetching instruction...");
    u8 opcode = fetch();
    log_output(LOG_LEVEL_INFO, "Now executing opcode: 0x%08x", opcode);
    execute(opcode);
    log_output(LOG_LEVEL_INFO, "Current Program counter: 0x%04x", cpu->pc);


  }
}

void set_flag(u8 flag){
  cpu->status_flags |= flag;
}
void clear_flag(u8 flag){
  cpu->status_flags &= ~flag;
}
