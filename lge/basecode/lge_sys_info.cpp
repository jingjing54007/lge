#include "SysInfo.h"
#ifndef ENABLE_PROFILE_SYSINFO
unsigned int GetTotalMemory()
{
	return 0;
}

unsigned int GetAvailableMemory()
{
	return 0;
}

unsigned int GetProcessMemory()
{
	return 0;
}
#endif

#ifdef ENABLE_PROFILE_SYSINFO
#include <ctime>
#include <cmath>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <cstddef>
#include <cassert>

#include <set>
#include <map>
#include <list>
#include <vector>

#include <memory>
#include <string>
#include <limits>
#include <utility>
#include <numeric>
#include <algorithm>
#include <functional>

#include <iomanip>
#include <iostream>

#include <typeinfo>
#include <stdexcept>

#include "LogManager.h"


#ifdef WIN32
unsigned int GetTotalMemory()
{
	return 0;
}

unsigned int GetAvailableMemory()
{
	return 0;
}

unsigned int GetProcessMemory()
{
	return 0;
}
#elif defined(ANDROID)
#elif defined(__APPLE__)
#include <sys/sysctl.h>
#include <pwd.h>
#include <mach/host_priv.h>
#include <mach/mach_host.h>
#include <mach/mach_error.h>
#include <mach/mach_port.h>
#include <mach/vm_map.h>
#include <mach/processor_set.h>
#include <mach/task.h>

#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <mach/task.h>
#include <vector>
#include "MySingleton.h"

class SysInfo : public MySingleton<SysInfo>
{
public:
	SysInfo();
	virtual ~SysInfo();
	
	class ProcessInfo {
	public:
		int prevTime;
		int curTime;
		int runTime;
		int pid;
		char pName[10];
		char userName[10];
		int rSize;
		int vSize;
		bool isDel;
		bool isSys;
		
		bool operator==(const ProcessInfo &user) const {
			return pid == user.pid;
		}
		
		ProcessInfo()
		: prevTime(0)
		, curTime(0)
		, runTime(0)
		, pid(0)
		, rSize(0)
		, vSize(0)
		, isDel(0)
		, isSys(0)
		{
		};
	};
    
	typedef std::vector<ProcessInfo> Process_VEC;
	typedef Process_VEC::iterator Process_VEC_ITER;
    
public:
	bool GetAllProcess();
	bool GetProcessInfo(task_t a_task);
	Process_VEC& GetAllProcessInfo(void);
	int GetMemoryInfo(int* wired, int* active, int* inactive, int* free);
	int GetCurrentProcessMemoryInfo();
	void Draw();
private:
	int m_nResidentMem;
	int m_nVirMem;
	int m_nTotalTime;
    
	Process_VEC m_pInfoList;
};

SysInfo::SysInfo()
{
}

SysInfo::~SysInfo()
{
}

bool SysInfo::GetProcessInfo(task_t a_task)
{
	boolean_t		retval = FALSE;
	kern_return_t		error;
	struct kinfo_proc	kinfo;
	size_t			kinfosize;
	int			pid, mib[4];
	mach_msg_type_number_t	count;
	struct task_basic_info_64	ti;
	unsigned int vsize;
	
	mach_vm_address_t	address;
	mach_port_t		object_name;
	vm_region_top_info_data_t info;
	mach_vm_size_t		size;
	boolean_t split;
	char userName[9];
	std::vector<ProcessInfo>::iterator pInfoItem;

	error = pid_for_task(a_task, &pid);
	if (error != KERN_SUCCESS) return FALSE;
	
	kinfosize = sizeof(struct kinfo_proc);
	mib[0] = CTL_KERN;
	mib[1] = KERN_PROC;
	mib[2] = KERN_PROC_PID;
	mib[3] = pid;
	
	if (sysctl(mib, 4, &kinfo, &kinfosize, NULL, 0) == -1) {
		printf("%s(): Error in sysctl()", __FUNCTION__);
		retval = TRUE;
		goto RETURN;
	}
	
	if (kinfo.kp_proc.p_stat == 0) {
		retval = FALSE;
		goto RETURN;
	}
	
	count = TASK_BASIC_INFO_64_COUNT;
	error = task_info(a_task, TASK_BASIC_INFO_64, (task_info_t)&ti, &count);
	if (error != KERN_SUCCESS) {
		return FALSE;
	}
	
	vsize = ti.virtual_size;
	
	{
		struct passwd *pwd;
		
		setpwent();
		pwd = getpwuid(kinfo.kp_eproc.e_ucred.cr_uid);
		memset(userName, 0, 9);
		if (pwd != NULL) 
			snprintf(userName, 9, "%s", pwd->pw_name);
		endpwent();
	}

	{
		ProcessInfo temp;
		temp.pid = kinfo.kp_proc.p_pid;
		pInfoItem=std::find(m_pInfoList.begin(), m_pInfoList.end(), temp); 
		if(pInfoItem != m_pInfoList.end())
		{
			pInfoItem->prevTime = pInfoItem->curTime;
			pInfoItem->curTime += ti.user_time.seconds*1000+ti.user_time.microseconds;
			pInfoItem->curTime += ti.system_time.seconds*1000+ti.system_time.microseconds;
			pInfoItem->runTime = pInfoItem->curTime - pInfoItem->prevTime;
			m_nTotalTime += pInfoItem->runTime;
			pInfoItem->rSize = ti.resident_size;
			pInfoItem->vSize = vsize;
			pInfoItem->isDel = false;
		}
		else
		{
			ProcessInfo procInfo;
			procInfo.prevTime = 0;
			procInfo.curTime += ti.user_time.seconds*1000+ti.user_time.microseconds;
			procInfo.curTime += ti.system_time.seconds*1000+ti.system_time.microseconds;
			procInfo.runTime = procInfo.curTime;
			m_nTotalTime += procInfo.runTime;
			procInfo.pid = kinfo.kp_proc.p_pid;
			snprintf(procInfo.pName, 9, "%s", kinfo.kp_proc.p_comm);
			snprintf(procInfo.userName, 9, "%s", userName);
			procInfo.rSize = ti.resident_size;
			procInfo.vSize = vsize;
			procInfo.isDel = false;
			procInfo.isSys = false;
			m_pInfoList.push_back(procInfo);
		}
	}
	
RETURN:
	return retval;
}

bool SysInfo::GetAllProcess()
{
	kern_return_t	error;
	processor_set_t	*psets, pset;
	task_t		*tasks;
	unsigned	i, j, pcnt, tcnt;
	
	m_nTotalTime = 0;
	host_priv_t libtop_port = mach_host_self();

	// 必须获得系统root权限才能访问所有process list，下面这段代码不能获得，暂用pxl制作包来解决权限问题
	host_t myhost = mach_host_self();
	processor_set_name_t p_default_set;
	processor_set_t p_default_set_control;
	/* get the default processor set */
	error = processor_set_default(myhost, &p_default_set);
	if (KERN_SUCCESS != error)
	{
		printf("Error in processor_set_default(): %s \n",mach_error_string(error));

		char szInfo[256] = { 0 };
		snprintf(szInfo, sizeof(szInfo) - 1, "processor_set_default error");
		LogMsg(szInfo);
	}
	/* get the control port for this processor set */
	error = host_processor_set_priv(myhost, p_default_set, &p_default_set_control);
	if (KERN_SUCCESS != error)
	{
	}

	error = host_processor_sets(libtop_port, &psets, &pcnt);
	if (error != KERN_SUCCESS) {
		GetProcessInfo(mach_task_self());
		return TRUE;
	}
	
	m_pInfoList.clear();

	for (i = 0; i < pcnt; i++) {
		error = host_processor_set_priv(libtop_port, psets[i], &pset);
		if (error != KERN_SUCCESS) {
			printf("Error in host_processor_set_priv(): %s \n",mach_error_string(error));
			
			char szInfo[256] = { 0 };
			snprintf(szInfo, sizeof(szInfo) - 1, "host_processor_set_priv error");
			LogMsg(szInfo);

			return true;
		}
		
		error = processor_set_tasks(pset, &tasks, &tcnt);
		if (error != KERN_SUCCESS) {
			printf("Error in processor_set_tasks(): %s \n",mach_error_string(error));
			
			char szInfo[256] = { 0 };
			snprintf(szInfo, sizeof(szInfo) - 1, "processor_set_tasks error");
			LogMsg(szInfo);

			return true;
		}
		
		for (j = 0; j < tcnt; j++) {
			if (GetProcessInfo(tasks[j])) 
			{
				return true;
			}
			mach_port_deallocate(mach_task_self(),tasks[j]);
		}
		error = vm_deallocate((vm_map_t)mach_task_self(),(vm_address_t)tasks, tcnt * sizeof(task_t));
		if (error != KERN_SUCCESS) {
			printf("Error in vm_deallocate(): %s \n",mach_error_string(error));
			return true;
		}
		if ((error = mach_port_deallocate(mach_task_self(),pset)) != KERN_SUCCESS
		    || (error = mach_port_deallocate(mach_task_self(),psets[i])) != KERN_SUCCESS) 
		{
			printf("Error in mach_port_deallocate(): %s \n",mach_error_string(error));
			return true;
		}
	}
	
	error = vm_deallocate((vm_map_t)mach_task_self(),(vm_address_t)psets, pcnt * sizeof(processor_set_t));
	if (error != KERN_SUCCESS) {
		printf("Error in vm_deallocate(): %s \n",mach_error_string(error));
		return true;
	}
	
	return false;
}

SysInfo::Process_VEC& SysInfo::GetAllProcessInfo(void)
{
	return m_pInfoList;
}

int SysInfo::GetMemoryInfo(int* wired, int* active, int* inactive, int* free)
{
	int poll = 0;
    kern_return_t ke = KERN_SUCCESS;
    mach_port_t host;
    vm_size_t hps;
    vm_statistics_data_t hs;
    mach_msg_type_number_t vmsz;
	
    host = mach_host_self();
    vmsz = sizeof(hs) / sizeof(integer_t);
	
    while (1) {
        if ((ke = host_page_size(host, &hps)) != KERN_SUCCESS) {
            return EXIT_FAILURE;
        }
		
        ke = host_statistics(host, HOST_VM_INFO, (host_info_t) &hs, &vmsz);
        if (ke != KERN_SUCCESS) {
            return EXIT_FAILURE;
        }

        int used = ((hs.active_count + hs.inactive_count + hs.wire_count)* hps);
        *free = (hs.free_count * hps);
        *active = (hs.active_count * hps);
        *inactive = (hs.inactive_count * hps);
        *wired = (hs.wire_count * hps);
		
        if (poll != 0) {
            sleep(poll);
            printf("\n");
        } else {
            break;
        }
    }
	
    return EXIT_SUCCESS;
}

int SysInfo::GetCurrentProcessMemoryInfo()
{
	GetAllProcess();
	Process_VEC::iterator itr = m_pInfoList.begin();
	if (itr != m_pInfoList.end()) {
		return (*itr).rSize;
	}

	return 0;
}

void SysInfo::Draw()
{
	int wired, active, inactive, free;
	static int total = GetTotalMemory();
	this->GetMemoryInfo(&wired, &active, &inactive, &free);
	int ress = this->GetCurrentProcessMemoryInfo();
	char szMsg[256] = {0};
	snprintf(szMsg, sizeof(szMsg) - 1, "Memory info: Total:%dmb  Wired:%dmb  Active:%dmb             Inactive:%dmb  Free:%dmb        Self:%dmb",
			  total, wired / 1024 / 1024, active / 1024 / 1024,
              inactive / 1024 / 1024,  free / 1024 / 1024, ress / 1024 / 1024);
	szMsg[sizeof(szMsg) - 1] = 0;
}

unsigned int GetTotalMemory()
{
    kern_return_t ke = KERN_SUCCESS;
    mach_port_t host;
    struct host_basic_info hbi;
    mach_msg_type_number_t memsz;
	
    host = mach_host_self();
    memsz = sizeof(hbi) / sizeof(integer_t);
	
    ke = host_info(host, HOST_BASIC_INFO, (host_info_t) &hbi, &memsz);
    if (ke != KERN_SUCCESS) {
        return 0;
    }
	
	return hbi.max_mem >> 20;
}

unsigned int GetAvailableMemory()
{
	// wired是系统内存，active是当前占用的内存，inactive是非活跃进程内存，可以被使用，free是完全没有被使用的内存
	int wired, active, inactive, free;
	SysInfo::GetSingleton().GetMemoryInfo(&wired, &active, &inactive, &free);
	return (free + inactive) / 1024;
}

unsigned int GetProcessMemory()
{
	return SysInfo::GetSingleton().GetCurrentProcessMemoryInfo() / 1024;
}
#else
unsigned int GetTotalMemory()
{
	return 0;
}

unsigned int GetAvailableMemory()
{
	return 0;
}

unsigned int GetProcessMemory()
{
	return 0;
}
#endif
#endif
