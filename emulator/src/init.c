
#include "cpu.h"
#include "init.h"
#include "logging.h"
#include "opcode.h"
#include "typedef.h"


void init(){
  CPU* cpu = get_CPU();
  cpu->pc = 0x0000;
  cpu->memory[0x10] = OPCODE_HALT;
}
