
#include "cpu.h"
#include "init.h"
#include "logging.h"


int main(int argc, char** argv){
  initialize_logging();
  log_output(LOG_LEVEL_INFO, "Logging initialized!");

  log_output(LOG_LEVEL_TRACE, "executing init()...");
  init();

  run();

  log_output(LOG_LEVEL_DEBUG, "value of r0: %i", get_CPU()->r[0]);
  log_output(LOG_LEVEL_DEBUG, "value of r1: %i", get_CPU()->r[1]);

  log_output(LOG_LEVEL_DEBUG, "value at address 0x01F0: 0x%02x", cpu->memory[0x01F0]);
  log_output(LOG_LEVEL_DEBUG, "value at address 0x01F1: 0x%02x", cpu->memory[0x01F1]);

  log_output(LOG_LEVEL_DEBUG, "Status flags: 0x%02x", get_status_flags());

  return 0;
}
