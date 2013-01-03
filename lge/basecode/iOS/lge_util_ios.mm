
#include <sys/stat.h>
#include <sys/sysctl.h>
#include <sys/types.h>
#include <mach/mach_host.h>
#include <mach/mach_init.h>
#include <mach/task.h>

#include <string>

#include "lge_platform.h"
#include "lge_string_format.h"
#include "lge_util.h"

extern char g_document_path[1024];

// =====================================================================================================================
// =======================================================================================================================
const char* GetApplicationPath()
{
	return [[[NSBundle mainBundle] bundlePath] UTF8String];
}

const char* GetDocumentPath()
{
	if (g_document_path[0] == 0)
	{
        NSArray* array = NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES);
        NSString* documentPath = [array objectAtIndex:0];
        strlcpy(g_document_path, [documentPath UTF8String], sizeof(g_document_path));
	}
    
	return g_document_path;
}

// =====================================================================================================================
// =======================================================================================================================
FILE* MyFileOpen(const char *pszFile, const char *pszMode)
{
	if (!pszFile || !pszMode || pszFile[0] == 0 || pszMode[0] == 0) {
		return NULL;
	}

	std::string strTemp = pszFile;
	std::transform(strTemp.begin(), strTemp.end(), strTemp.begin(), tolower);
	std::replace(strTemp.begin(), strTemp.end(), '\\', '/');

	std::string filePath = FORMAT("%s/%s") << GetDocumentPath() << strTemp.c_str();
	
	// 优先读取documents目录下的文件
	FILE* file = fopen(filePath.c_str(), pszMode);
	if (file) {
		return file;
	}

	// 读取app目录下的文件
	filePath = FORMAT("%s/%s") << GetApplicationPath() << strTemp.c_str();
	file = fopen(filePath.c_str(),pszMode);
	if (file) {
		return file;
	}
    
    // 文件没有找到，试试原始名字
    strTemp = pszFile;
	std::replace(strTemp.begin(), strTemp.end(), '\\', '/');
	filePath = FORMAT("%s/%s") << GetDocumentPath() << strTemp.c_str();
	
	// 优先读取documents目录下的文件
	file = fopen(filePath.c_str(), pszMode);
	if (file) {
		return file;
	}
    
	// 读取app目录下的文件
	filePath = FORMAT("%s/%s") << GetApplicationPath() << strTemp.c_str();
	file = fopen(filePath.c_str(),pszMode);
	if (file) {
		return file;
	}

	return NULL;
}

// =====================================================================================================================
// =======================================================================================================================
void MyCopyFile(const char* src, const char* dest)
{
    if (!src || !dest || src[0] == 0 || dest[0] == 0) {
        return;
    }
    
    NSFileManager* fm = [NSFileManager defaultManager];
    NSString* destPath = [NSString stringWithUTF8String:dest];
    
    for (int i = destPath.length - 1; i > 0; --i) {
        if ([destPath characterAtIndex:i] == '/') {
            destPath = [destPath substringToIndex:i];
            break;
        }
    }

    NSLog(@"%@", destPath);

    [fm createDirectoryAtPath:destPath withIntermediateDirectories:YES attributes:nil error:nil];
    [fm copyItemAtPath:[NSString stringWithUTF8String:src] toPath:destPath error:nil];
}
