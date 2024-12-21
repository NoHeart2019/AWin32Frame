#pragma once
/*
	OutputDebugString �����Ϣ��������
	�����������
			1.�����Visual Studio ����̨����DbgView.exe��Windbg.exe
			2.������ļ�

	DebugEnable() �������
	DebugDisable() �ر����
	DebugEnableCount() ������ű��
	DebugDisableCount() �ر���ű��
	DebugEnableFile()    ������ļ�
	DebugEnableDebuger() ���������̨
*/

#define DEBUG_OUTPUT_TYPE_DEBUGER 0
#define DEBUG_OUTPUT_TYPE_FILE 1

#define DEBUG_LEVEL_INFO	   0
#define DEBUG_LEVEL_WARNING    1
#define DEBUG_LEVEL_ERROR	   2

extern ULONG DebugLevel;

int DebugOutputLevelEx(int Level, char* FunctionName, int Line ,const char* formats, ...);

int DebugOutputLevel(int Level, const char* formats, ...);

int DebugOutput(const char* formats, ...);

int DebugOutputFile(const char* formats, ...);

 
#define ZxDebug(x)   if(DebugLevel >  DEBUG_LEVEL_WARNING) DebugOutput x
#define ZxDebugEx(x) if(DebugLevel >  DEBUG_LEVEL_INFO)  DebugOutput x
 
#define ZxDebugError(formats, ...)\
		DebugOutputLevelEx(DEBUG_LEVEL_ERROR, __FUNCTION__, __LINE__,formats, __VA_ARGS__)

#define ZxDebugWarning(formats, ...)\
	DebugOutputLevelEx(DEBUG_LEVEL_WARNING, __FUNCTION__,__LINE__, formats, __VA_ARGS__)

#define ZxDebugInfo(formats, ...)\
	DebugOutputLevelEx(DEBUG_LEVEL_INFO, __FUNCTION__, __LINE__, formats, __VA_ARGS__)

VOID DebugFileAppend(LPCWSTR LogPath, LPVOID Buffer, ULONG Length);


BOOL DebugInitialize();

BOOL DebugFileInitialize(LPCWSTR FileName = NULL);


VOID DebugIncrementCount();

VOID DebugEnable();

VOID DebugDisable();

VOID DebugEnableCount();

VOID DebugDisableCount();

VOID DebugEnableFile(LPCWSTR LogPath);

VOID DebugEnableDebuger();

VOID DebugSetLevel(int Level);


VOID DebugTest();

VOID DebugCpuid();
