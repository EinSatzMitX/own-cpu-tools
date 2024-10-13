
#include "cpu.h"
#include "init.h"
#include "logging.h"
#include "typedef.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){

  if(argc < 3){
    log_output(LOG_LEVEL_FATAL, "Usage: %s <in-file> <sart-addr (in hex)>", argv[0]);
    return 1;
  }

  char* endptr;
  unsigned long start_addr = strtol(argv[2], &endptr, 16);
  if(*endptr != '\0'){
    log_output(LOG_LEVEL_FATAL, "Invalid hex value: %s", argv[2]);
    return 1;
  }
  u16 hex_start_addr = (u16) start_addr;

  initialize_logging();
  log_output(LOG_LEVEL_INFO, "Logging initialized!");

  init();

  load_program_from_file(argv[1], hex_start_addr);

  set_pc(hex_start_addr);

  printf("Status flags: 0b%08b", cpu->status_flags);

  run();

  return 0;
}
