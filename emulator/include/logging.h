#pragma once

#include "defines.h"


#define LOG_WARN_ENABLED 1
#define LOG_INFO_ENABLED 1
#define LOG_DEBUG_ENABLED 1
#define LOG_TRACE_ENABLED 1

#if RIFT_RELEASE == 1
#define LOG_TRACE_ENABLED 0 
#define LOG_DEBUG_ENABLED 0
#endif

typedef enum log_level{
  LOG_LEVEL_FATAL = 0,
  LOG_LEVEL_ERROR = 1,
  LOG_LEVEL_WARN = 2,
  LOG_LEVEL_INFO = 3,
  LOG_LEVEL_DEBUG = 4,
  LOG_LEVEL_TRACE = 5,
} log_level;


int initialize_logging();
void shutdown_logging();

RAPI void log_output(log_level level, const char* message, ...);

// Logs a fatal-level message.
#define RFATAL(message, ...) log_output(LOG_LEVEL_FATAL, message, ##__VA_ARGS__);

#ifndef RERROR
// Logs an error-level message.
#define RERROR(message, ...) log_output(LOG_LEVEL_ERROR, message, ##__VA_ARGS__);
#endif

#if LOG_WARN_ENABLED == 1
// Logs a warning-level message.
#define RWARN(message, ...) log_output(LOG_LEVEL_WARN, message, ##__VA_ARGS__);
#else
// Does nothing when LOG_WARN_ENABLED != 1
#define RWARN(message, ...)
#endif

#if LOG_INFO_ENABLED == 1
// Logs a info-level message.
#define RINFO(message, ...) log_output(LOG_LEVEL_INFO, message, ##__VA_ARGS__);
#else
// Does nothing when LOG_INFO_ENABLED != 1
#define RINFO(message, ...)
#endif

#if LOG_DEBUG_ENABLED == 1
// Logs a debug-level message.
#define RDEBUG(message, ...) log_output(LOG_LEVEL_DEBUG, message, ##__VA_ARGS__);
#else
// Does nothing when LOG_DEBUG_ENABLED != 1
#define RDEBUG(message, ...)
#endif

#if LOG_TRACE_ENABLED == 1
// Logs a trace-level message.
#define RTRACE(message, ...) log_output(LOG_LEVEL_TRACE, message, ##__VA_ARGS__);
#else
// Does nothing when LOG_TRACE_ENABLED != 1
#define RTRACE(message, ...)
#endif
