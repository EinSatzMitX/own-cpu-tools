#pragma once

// Properly define static assertions.
#if defined(__clang__) || defined(__gcc__)
#define STATIC_ASSERT _Static_assert
#else
#define STATIC_ASSERT static_assert
#endif

// Platform detection
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) 
#define RPLATFORM_WINDOWS 1
#ifndef _WIN64
#error "64-bit is required on Windows!"
#endif
#elif defined(__linux__) || defined(__gnu_linux__)
// Linux OS
#define RPLATFORM_LINUX 1
#if defined(__ANDROID__)
#define RPLATFORM_ANDROID 1
#endif
#elif defined(__unix__)
// Catch anything not caught by the above.
#define RPLATFORM_UNIX 1
#elif defined(_POSIX_VERSION)
// Posix
#define RPLATFORM_POSIX 1
#elif __APPLE__
// Apple platforms
#define RPLATFORM_APPLE 1
#include <TargetConditionals.h>
#if TARGET_IPHONE_SIMULATOR
// iOS Simulator
#define RPLATFORM_IOS 1
#define RPLATFORM_IOS_SIMULATOR 1
#elif TARGET_OS_IPHONE
#define RPLATFORM_IOS 1
// iOS device
#elif TARGET_OS_MAC
// Other kinds of Mac OS
#else
#error "Unknown Apple platform"
#endif
#else
#error "Unknown platform!"
#endif

#ifdef REXPORT
// Exports
#ifdef _MSC_VER
#define RAPI __declspec(dllexport)
#else
#define RAPI __attribute__((visibility("default")))
#endif
#else
// Imports
#ifdef _MSC_VER
#define RAPI __declspec(dllimport)
#else
#define RAPI
#endif
#endif
