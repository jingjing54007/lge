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

#include "lge_logger.h"

#ifdef WIN32
#define snprintf _snprintf
#define vsnprintf _vsnprintf
#else
#define stricmp strcasecmp
#endif

#ifndef __max
#	define __max(a, b)         ((a) > (b)? (a) : (b))
#endif

#ifndef __min
#	define __min(a, b)         ((a) < (b)? (a) : (b))
#endif


typedef unsigned char uint8;
typedef signed char int8;
typedef unsigned short uint16;
typedef signed short int16;
typedef signed int int32;
typedef unsigned int uint32;

#ifdef __WIN32__
typedef unsigned __int64 uint64;
typedef __int64 int64;
#else
typedef unsigned long long uint64;
typedef long long int64;
#endif



inline void log_msg(const char *type,
	const char *str,
	const char *file,
	int line)
{
	char temp[256] = {0};
	snprintf(temp, sizeof(temp), "%s(%s) in %s, %d", type, str, file, line);
	LogMsg(temp);
}
#ifdef WIN32
	#define MY_ASSERT(cond) (void)((cond) || (log_msg("ASSERT", #cond, __FILE__, __LINE__), CC_ASSERT(cond), 0))
	#define MY_ASSERT_EX(cond, msg) (void)((cond) || (log_msg("ASSERT", #cond, __FILE__, __LINE__), CC_ASSERT(cond), 0))
#else
	#define MY_ASSERT(cond) (void)((cond) || (log_msg("ASSERT", #cond, __FILE__, __LINE__), 0))
	#define MY_ASSERT_EX(cond, msg) (void)((cond) || (log_msg("ASSERT", #cond, __FILE__, __LINE__), 0))
#endif

#define CHECKF(x) \
	do \
{ \
	if (!(x)) { \
	log_msg("CHECKF", #x, __FILE__, __LINE__); \
	return 0; \
	} \
} while (0)


#define SWAP16(x) static_cast(uint16, ((x << 8) | (x >> 8)));
