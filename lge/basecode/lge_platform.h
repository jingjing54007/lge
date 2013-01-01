#pragma once

#if defined(linux) || defined(__linux) || defined(__linux__)
#define __LINUX__	1
#endif

#if defined(ANDROID)
#define __ANDROID__ 1
#endif

#if defined(__APPLE__)
/* lets us know what version of Mac OS X we're compiling on */
#include "AvailabilityMacros.h"
#include "TargetConditionals.h"
#if TARGET_OS_IPHONE
#define __IPHONEOS__ 1
#else
#define __MACOSX__	1
#endif
#endif

#if defined(WIN32) || defined(_WIN32)
#define __WIN32__	1
#endif

#ifdef __WIN32__
#include <windows.h>
#endif

#include <stdio.h>
#include <stdlib.h>
