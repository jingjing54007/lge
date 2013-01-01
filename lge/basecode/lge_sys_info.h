#pragma once
// 注意发布版本要去掉这个定义(app store unsafe)
//#undef ENABLE_PROFILE_SYSINFO
#define ENABLE_PROFILE_SYSINFO 1

// 内存相关函数，单位为k
unsigned int GetTotalMemory();		// 获取设备总内存
unsigned int GetAvailableMemory();  // 获取当前的空闲内存数量
unsigned int GetProcessMemory();	// 获取当前进程的内存占用


#ifdef ENABLE_PROFILE_SYSINFO


#ifdef WIN32
#elif defined(ANDROID)
#elif defined(__APPLE__)

#else
#endif
#endif
