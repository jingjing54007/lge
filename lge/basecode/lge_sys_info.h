#pragma once
// ע�ⷢ���汾Ҫȥ���������(app store unsafe)
//#undef ENABLE_PROFILE_SYSINFO
#define ENABLE_PROFILE_SYSINFO 1

// �ڴ���غ�������λΪk
unsigned int GetTotalMemory();		// ��ȡ�豸���ڴ�
unsigned int GetAvailableMemory();  // ��ȡ��ǰ�Ŀ����ڴ�����
unsigned int GetProcessMemory();	// ��ȡ��ǰ���̵��ڴ�ռ��


#ifdef ENABLE_PROFILE_SYSINFO


#ifdef WIN32
#elif defined(ANDROID)
#elif defined(__APPLE__)

#else
#endif
#endif
