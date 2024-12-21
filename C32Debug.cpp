#include "stdafx.h"
#include <stdio.h>

#include "C32Debug.h"
#define DEBUG_FILE_NAME L"C32Debug.log"


static ULONG DebugType = DEBUG_OUTPUT_TYPE_DEBUGER; 

static PWCHAR LogFile = NULL;
static ULONG  EnableDebug = 0;

static ULONG DebugOutputCount = 0;
static ULONG EnableCount = 0;

ULONG DebugLevel = DEBUG_LEVEL_WARNING;

int DebugOutputLevelEx(int Level, char* FunctionName, int Line ,const char* formats, ...)
{
	ULONG n = 0;
	char buffer[256];

	if (EnableDebug == 0)
		return 0;

	va_list arglist = NULL;
	va_start(arglist, formats);
	if (Level == DEBUG_LEVEL_INFO)
		n = sprintf_s(buffer, 255,"INFO : %s(%d) ", FunctionName, Line);
	else if(Level == DEBUG_LEVEL_WARNING)
		n =sprintf_s(buffer, 255,"WARNING : %s(%d) ", FunctionName, Line);
	else
		n = sprintf_s(buffer, 255, "ERROR : %s(%d) ", FunctionName, Line);
		
	n += vsprintf_s(buffer+n, 255-n, formats, arglist);
	if (DebugType == DEBUG_OUTPUT_TYPE_DEBUGER)
		OutputDebugStringA(buffer);
	else
		DebugFileAppend(LogFile, buffer, n);

	/*delete buffer;
	buffer = NULL;*/

	va_end(arglist);
	return n;
}

int DebugOutputLevel(int Level, const char* formats, ...)
{
	if (EnableDebug == 0 || Level < (int)DebugLevel)
		return 0;

	ULONG n = 0;
	ULONG length = 4096;

	char* buffer = new char[length];
	if (buffer == NULL)
		return 0;
	RtlZeroMemory(buffer, length);

	va_list arglist = NULL;
	va_start(arglist, formats);
	if(EnableCount)
		n +=sprintf_s(buffer, length, "%d  :", DebugOutputCount++);
	n += vsprintf_s(buffer+n, length-n, formats, arglist);
	va_end(arglist);

	if (DebugType == DEBUG_OUTPUT_TYPE_DEBUGER)
		OutputDebugStringA(buffer);
	else
		DebugFileAppend(LogFile, buffer, n);

	delete buffer;
	buffer = NULL;
	return n;
}

int DebugOutput(const char* formats, ...)
{
	ULONG n = 0;
	ULONG length = 4096;

	if (EnableDebug == 0)
		return 0;

	char* buffer = new char[length];
	if (buffer == NULL)
		return 0;
	RtlZeroMemory(buffer, length);

	va_list arglist = NULL;
	va_start(arglist, formats);
	if(EnableCount)
		n +=sprintf_s(buffer, length, "%d  :", DebugOutputCount++);
	n += vsprintf_s(buffer+n, length-n, formats, arglist);
	va_end(arglist);
	
	if (DebugType == DEBUG_OUTPUT_TYPE_DEBUGER)
		OutputDebugStringA(buffer);
	else
		DebugFileAppend(LogFile, buffer, n);

	delete buffer;
	buffer = NULL;
	return n;
}

int DebugOutputFile(const char* formats, ...)
{
	ULONG n = 0;
	char buffer[256];

	if (EnableDebug == 0)
		return 0;
	va_list arglist = NULL;
	va_start(arglist, formats);
	n +=sprintf_s(buffer, 256, "%d  :", DebugOutputCount++);
	n += vsprintf_s(buffer+n, 255-n, formats, arglist);

	DebugFileAppend(LogFile, buffer, n);

	va_end(arglist);
	return n;
}

int DebugOutputTime(const char* formats, ...)
{
	ULONG n = 0;
	char buffer[256];

	va_list arglist = NULL;
	va_start(arglist, formats);

	SYSTEMTIME LocalTime={};

	GetLocalTime(&LocalTime);
	n = sprintf_s(buffer, 255, "%04d-%02d-%02d %02d:%02d:%02d-%03d  ", 
		LocalTime.wYear, LocalTime.wMonth, LocalTime.wDay, LocalTime.wHour, LocalTime.wMinute, LocalTime.wSecond, LocalTime.wMilliseconds);

	n += vsprintf_s(buffer+n, 255-n, formats, arglist);
	OutputDebugStringA(buffer);
	va_end(arglist);

	return n;
}

VOID DebugIncrementCount()
{
	DebugOutputCount++;
}

VOID DebugFileAppend(LPCWSTR LogPath, LPVOID Buffer, ULONG Length)
{
	FILE* file = NULL; 
	_wfopen_s(&file, (LPWSTR)LogPath, L"a+");
	if (file)
	{
		fwrite(Buffer, Length, 1, file);
		fclose(file);
	}

	
}

VOID DebugEnable()
{
	EnableDebug = 1;
}

VOID DebugDisable()
{
	EnableDebug = 0;
}

VOID DebugEnableCount()
{
	EnableCount = 1;

}

VOID DebugDisableCount()
{
	EnableCount = 0;

}

static VOID DebugSetType(ULONG Type = DEBUG_OUTPUT_TYPE_FILE)
{
	DebugType = Type;
}

VOID DebugEnableFile(LPCWSTR LogPath)
{
	LogFile = (LPWSTR)LogPath;
	DebugSetType();
}

VOID DebugEnableDebuger()
{
	DebugSetType(DEBUG_OUTPUT_TYPE_DEBUGER);
}

VOID DebugSetLevel(int Level)
{
	DebugLevel = Level;
}


BOOL DebugInitialize()
{
	DebugEnable();
	DebugEnableCount();
	DebugSetType(DEBUG_OUTPUT_TYPE_DEBUGER);

	return TRUE;
}

BOOL DebugFileInitialize(LPCWSTR FileName)
{
	DebugInitialize();
	LogFile = (FileName ? FileName : DEBUG_FILE_NAME);
	
	DebugSetType();
	return TRUE;
}



VOID DebugTest()
{
	ZxDebugInfo("InfoTest %d \n", __LINE__);
	ZxDebugWarning("WarningTest %d \n", __LINE__);
	ZxDebugError("ErrorTest %d \n", __LINE__);

	EnableDebug = 1;
	DebugInitialize();

	DebugOutputFile("Test : %d %d \n", 1 ,2);
	DebugOutputFile("Test : 1234567 \n");

	EnableDebug = 1;



}

