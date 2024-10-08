
#include "cpu.h"
#include "init.h"
#include "logging.h"


int main(int argc, char** argv){
  initialize_logging();
  log_output(LOG_LEVEL_INFO, "Logging initialized!");

  init();

  load_program_from_file(argv[1], 0x0000);


  run();

  log_output(LOG_LEVEL_DEBUG, "value of r0: 0x%04x", get_CPU()->r[0]);
  log_output(LOG_LEVEL_DEBUG, "value of r1: 0x%04x", get_CPU()->r[1]);

  log_output(LOG_LEVEL_DEBUG, "Status flags: 0b%08b", get_status_flags());

  return 0;
}
