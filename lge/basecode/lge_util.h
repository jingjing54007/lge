#pragma once

void lge_debug_log(const char * pszFormat, ...);



void MyCreateDirectory(const char* pszDirectory);						// 创建目录。
void MyDeleteFile(const char* pszDirectory);							// 删除文件
FILE* MyFileOpen(const char* pszFile, const char* pszMode);				// 打开文件。用此函数代替fopen
void LogMsgError(const char* pszErrorType, const char* pszCallStacks, const char* pszExtractInfo = NULL);
void SendErrorLogToHttp(const char* pszLog);
const char* GetDocumentPath();
const char* GetApplicationPath();
unsigned int TimeGet(void);
int IsFileExist(const char* lpcszPathFilename);


void SendEventToAdx(const char* event, const char* data);