#include "stdafx.h"
#include "C32Helper.h"

PVOID  C32AllocateBuffer(int Length)
{
	PVOID p= NULL;
	int n = ((Length + 8)&-8);
	p = (PVOID)new UCHAR[n];
	if (p)
	{
		RtlZeroMemory(p, n);
	}
	return p;
}

VOID   C32FreeBuffer(PVOID Buffer)
{
	delete Buffer;
}

LPWSTR C32AllocateString(int Length)
{
	return (LPWSTR)C32AllocateBuffer(Length);
}


C32String C32zFormatSystemTimeString(ULONGLONG SystemTime)
{
	int Count = 0;
	_SYSTEMTIME st ={};
	C32String Time;
	Time.AssignStringW(64);

	FileTimeToSystemTime((FILETIME*)&SystemTime, &st);
	SystemTimeToTzSpecificLocalTime(NULL, &st, &st);
	Time.m_Count = swprintf_s(Time, 64,L"%4d-%02d-%02d %02d:%02d:%02d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

	return Time;   
}

C32String C32zGetSystemTimeString()
{
	C32String Time;
	_SYSTEMTIME St ={};
	GetSystemTime(&St);
	SystemTimeToTzSpecificLocalTime(NULL, &St, &St);

	Time.FormatString(L"%4d-%02d-%02d %02d:%02d:%02d",St.wYear, St.wMonth, St.wDay,  St.wHour, St.wMinute, St.wSecond);

	return Time;   
}
