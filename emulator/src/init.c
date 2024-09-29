
#include "cpu.h"
#include "init.h"
#include "logging.h"
#include "opcode.h"
#include "typedef.h"


void init(){
  CPU* cpu = get_CPU();
  cpu->memory[0x0000] = OPCODE_LOAD_REG_IMM;
  cpu->memory[0x0001] = REG0;
  cpu->memory[0x0002] = 0xFF;
  cpu->memory[0x0003] = 0x7F;

  cpu->memory[0x0004] = OPCODE_LOAD_REG_IMM;
  cpu->memory[0x0005] = REG1;
  cpu->memory[0x0006] = 0xFF;
  cpu->memory[0x0007] = 0xFF;


  cpu->memory[0x0008] = OPCODE_ADD_SIGNED_REG_IMM;
  cpu->memory[0x0009] = REG0;
  cpu->memory[0x000A] = 0x3B;
  cpu->memory[0x000B] = 0x4D;
  

}
