#pragma once

#define C32A2W(String) (LPCSTR)String ? CA2W(String, CP_ACP) : L""
#define C32W2A(String) (LPCWSTR)String ? CW2A(String, CP_ACP) : ""


PVOID  C32AllocateBuffer(int Length);

VOID   C32FreeBuffer(PVOID Buffer);

LPWSTR C32AllocateString(int Length);


class C32Buffer
{
public:
	C32Buffer()
	{
		Init();
		
	}

	C32Buffer(int Length)
	{
		Init();
		Assign(Length);
	}

	~C32Buffer()
	{
		if (!m_Attach)
		{
			C32FreeBuffer(m_Buffer);
		}
	}

public:
	operator LPVOID()
	{
		return m_Buffer;
	}

	

	BOOL Assign(int Length)
	{
		FreeBuffer();
		m_Buffer = C32AllocateBuffer(Length);
		m_Length = Length;

		return (m_Buffer ? TRUE : FALSE);
	}

	VOID Attach(PVOID Buffer, int Length)
	{
		
		m_Buffer = Buffer;
		m_Length = Length;
		m_Attach = TRUE;

	}

	VOID Detach()
	{
		m_Buffer = NULL;
		m_Length = NULL;
	}

	VOID FreeBuffer()
	{
		if (m_Attach  == FALSE && m_Buffer)
		{
			C32FreeBuffer(m_Buffer);
			m_Buffer = NULL;
			m_Length = 0;
		}
	}

	VOID Init()
	{
		m_Length = 0;
		m_Buffer = NULL;
		m_Attach = FALSE;
	}

	int GetLength()
	{
		return m_Length;
	}

	

	PVOID GetBuffer()
	{
		return m_Buffer;
	}

	BOOL IsEmptry()
	{
		return (m_Buffer ? FALSE : TRUE);
	}

	C32Buffer(const C32Buffer& Right)
	{
		C32AllocateBuffer(Right.m_Length);
		if (m_Buffer)
		{
			m_Length = Right.m_Length;
			RtlCopyMemory(m_Buffer, Right.m_Buffer, m_Length);
		}
	}

	C32Buffer& operator=(const C32Buffer& Right)
	{
		//C32Buffer(Right);
		return *this;
	}

	
	

	PVOID m_Buffer;
	int   m_Length;
	BOOL  m_Attach;
};

class C32String : public C32Buffer
{

public:
	C32String()
	{
		Init();
	}

	~C32String()
	{

	}

	operator LPWSTR() const
	{
		return (LPWSTR)m_Buffer;
	}
	operator LPCWSTR() const
	{
		return (LPCWSTR)m_Buffer;
	}
	/*
		String 操作

	*/
	BOOL AssignStringW(int CharCount)
	{
		//多分配1个字符
		CharCount++;

		if(Assign(CharCount*2) == TRUE)
		{
			m_TotalCount = CharCount;
		}else
		{
			m_TotalCount = 0;
		}
		m_DbgString = (LPWSTR)m_Buffer;
		return (m_Buffer ? TRUE : FALSE);
	}

	/*
		默认是WCHAR
	*/
	LPWSTR GetString()
	{
		return GetStringW();
	}

	int GetStringLength()
	{
		return GetStringLengthW();
	}

	LPWSTR GetStringW()
	{
		return (LPWSTR)m_Buffer;
	}

	LPSTR GetStringA()
	{
		return (LPSTR)m_Buffer;
	}

	int GetStringLengthW()
	{
		int Count = 0;
		if (m_Buffer)
		{
			Count = (int)wcslen((const wchar_t*)m_Buffer);
		}
		return Count;
	}

	int GetStringLengthA()
	{
		int Count = 0;
		if (m_Buffer)
		{
			Count = (int)strlen((const char*)m_Buffer);
		}
		return Count;
	}

	int GetTotalCount()
	{
		int TotalSize = GetLength();

		return (TotalSize? TotalSize/2 -1 : 0) ;
	}

	int GetCount()
	{
		return m_Count;
	}

	int GetByte()
	{
		return m_Count*2;
	}


	VOID SetCount()
	{
		if (m_Buffer)
		{
			m_Count = (int)wcslen((LPCWSTR)m_Buffer);
		}
	}

	VOID SetCount(int Count)
	{
		m_Count = Count;
	}

	int GetFormatLength(__in __format_string LPCWSTR Format, va_list argList)
	{
		wchar_t Buffer[2048]={};

		return wvsprintfW(Buffer, Format, argList);
	}

	C32String& FormatString(__in __format_string LPCWSTR Format, ...)
	{
		int Count = 0;
		va_list argList;
		va_start(argList, Format);

		m_Count = GetFormatLength(Format, argList);

		if (m_Count)
		{
			AssignStringW(m_Count);
			m_Count = wvsprintfW(GetString(), Format, argList);
		}
		va_end( argList );

		return *this;
	}

	C32String& AppendString(LPCWSTR Str)
	{
		if (Str== NULL)
			return *this;

		int AppendCount = (int)wcslen(Str);
		if (m_Count+ AppendCount >= m_TotalCount )
		{
			LPWSTR OldString = (LPWSTR)m_Buffer;
			Detach();
			if(AssignStringW(m_Count+ AppendCount))
			{
				CopyString(OldString, m_Count);
				delete OldString;
				
			}else
			{
				//分配内存失败
				m_Buffer = OldString;
				m_Length = m_Count*2;

				return *this;
			}
			
		}

		wcscpy_s((LPWSTR)m_Buffer + m_Count, m_TotalCount -m_Count, Str);
		m_Count += (int)wcslen(Str);
		

		return *this;

	}

	C32String& CopyString(LPWSTR Str)
	{
		if (Str== NULL)
			return *this;

		int Count = (int)wcslen(Str);
		if (Count == 0)
			return *this;

		if(AssignStringW(Count))
		{
			CopyString(Str, Count);
		}

		return *this;

	}

	C32String& CopyString(LPCWSTR Str)
	{
		CopyString((LPWSTR)Str);

		return *this;
	}

	C32String& AppendString(LPWSTR Str)
	{
		AppendString((LPCWSTR)Str);
		return *this;
	}

	BOOL CopyString(LPWSTR Str, int Count)
	{
		if (Str)
		{
			wcscpy_s((LPWSTR)m_Buffer, m_TotalCount,Str);
			m_Count = Count;
		}
		return TRUE;
	}


	VOID Init()
	{
		m_Count = 0;
		m_TotalCount = 0;

		m_DbgString = NULL;
	}

public:
	int m_Count;
	int m_TotalCount;
	LPWSTR m_DbgString;

	const C32String& operator = (LPWSTR Str)
	{
		*this = (LPCWSTR)Str;

		return *this;
	}

	const C32String& operator = (LPCWSTR Str)
	{
		CopyString(Str);

		return *this;
	}

	const C32String& operator += (LPCWSTR Str)
	{
		AppendString(Str);

		return *this;
	}

	const C32String& operator += (LPWSTR Str)
	{
		*this +=(LPCWSTR)Str;

		return *this;
	}
	
	const C32String& operator += (const C32String& Str)
	{
		*this +=(LPCWSTR)Str;

		return *this;
	}


	C32String(LPCWSTR Str)
	{
		*this = Str;
	}

	C32String(LPWSTR Str)
	{
		operator= (Str);
	}

	C32String(const C32String& Right)
	{
		*this = Right;
	}

	C32String& operator=(const C32String& Right)
	{
		//C32Buffer(Right);
		AssignStringW(Right.m_Length);
		if (m_Buffer)
		{
			m_Count = Right.m_Count;
			m_Length = Right.m_Length;
			m_TotalCount = Right.m_TotalCount;
			RtlCopyMemory(m_Buffer, Right.m_Buffer, m_Count*2);
			
		}
		return *this;
	}

};

/*
    线程同步
*/

class C32SynThread
{
public:
    C32SynThread (){
		m_Parameter = NULL;
        m_Handle = NULL;
        m_bTerminate = FALSE;
        m_ThreadId = 0;
    }

    ~C32SynThread(){

        Close();
    }

public:
    BOOL Create(LPTHREAD_START_ROUTINE StartRoutine, LPVOID Parameter = NULL)
    {
        if (StartRoutine == NULL)
            return FALSE;
        LPVOID lpParameter = (Parameter ? Parameter : (PVOID)this);

        HANDLE Handle = CreateThread(NULL, 0, StartRoutine, lpParameter, 0, &m_ThreadId);

        m_Handle = Handle;

        return (Handle ? TRUE :FALSE);
    }

    BOOL Wait(DWORD dwMilliseconds = INFINITE)
    {
        BOOL bWait = FALSE;
        DWORD Ret;

        if (m_Handle)
        {
            Ret = WaitForSingleObject(m_Handle, dwMilliseconds);
            if (Ret >= 0)
                bWait = TRUE;
        }


        return bWait;
    }
    // Thread Stop Running
    VOID SetTerminate(BOOL Terminate = TRUE)
    {
        m_bTerminate = Terminate;
    }

    BOOL IsTerminate()
    {
        return m_bTerminate;
    }

    BOOL Suspend()
    {
        BOOL bSuspend = FALSE;
        if (m_Handle)
        {
            DWORD Count;
            Count = SuspendThread(m_Handle);

            bSuspend = (Count == -1 ? FALSE : TRUE);
        }

        return bSuspend;
    }

    BOOL Resume()
    {
        BOOL bResume = FALSE;
        if (m_Handle)
        {
            DWORD Count;
            Count = ResumeThread(m_Handle);

            bResume = (Count == -1 ? FALSE : TRUE);
        }

        return bResume;

    }

    BOOL Close()
    {
        BOOL bClose = FALSE;
        if (m_Handle)
        {
            bClose = CloseHandle(m_Handle);
            m_Handle = NULL;
        }

        return !!bClose;
    }

public:
	VOID SetParameter(LPVOID lpParameter)
	{
		m_Parameter = lpParameter;
	}
	PVOID GetParameter()
	{
		return m_Parameter ;
	}

	PVOID  m_Parameter;
    BOOL   m_bTerminate;
    HANDLE m_Handle;
    DWORD  m_ThreadId;
};

class C32SynEvent
{
public:
    C32SynEvent()
    {
        m_Event = NULL;
    }
    ~C32SynEvent()
    {


    }

public:

    BOOL Create(BOOL  SignalStatie = TRUE, LPCWSTR EventName = NULL)
    {
        m_Event = CreateEvent(NULL, TRUE, SignalStatie, EventName);
        return (m_Event ? TRUE : FALSE);
    }

    VOID Close()
    {
        if (m_Event)
        {
            CloseHandle(m_Event);
            m_Event = NULL;
        }
    }

    BOOL Set()
    {
        BOOL bSet = FALSE;
        if (m_Event)
            bSet = SetEvent(m_Event);

        return bSet;
    }

    BOOL Reset()
    {
        BOOL bSet = FALSE;
        if (m_Event)
            bSet = ResetEvent(m_Event);

        return bSet;
    }

    DWORD WaitFor(DWORD  dwMilliseconds = INFINITE)
    {
        DWORD Ret = WAIT_FAILED;
		if (m_Event)
			Ret = WaitForSingleObject(m_Event, dwMilliseconds);
        

        return Ret;
    }

private:
    HANDLE m_Event;
};

/*
	封装CreateFile 相关的API
	std 看不懂所以少用
*/
class C32File
{
public:
	C32File()
	{
		m_ErrorCode = 0;
		m_hFile = NULL;
	}

	~C32File()
	{
		m_ErrorCode = 0;
		Close();
	}

public:
	HANDLE Create(LPCWSTR FilePath, DWORD dwCreateDisposition = OPEN_ALWAYS)
	{
		DWORD  dwDesiredAccess = FILE_GENERIC_READ | FILE_GENERIC_WRITE;
		DWORD  dwShareMode = FILE_SHARE_READ;
		//DWORD  dwCreateDisposition = OPEN_ALWAYS;
		DWORD  dwAttribute = FILE_ATTRIBUTE_NORMAL;
		HANDLE hFile = CreateFile(FilePath, dwDesiredAccess, dwShareMode, NULL, dwCreateDisposition,dwAttribute, NULL);
		m_hFile = hFile;
		m_ErrorCode = GetLastError();

		return (hFile ==  INVALID_HANDLE_VALUE ? NULL : hFile);
	}
	
	HANDLE Open(LPCWSTR FilePath, DWORD dwCreateDisposition = OPEN_EXISTING)
	{
		return Create(FilePath, dwCreateDisposition);
	}

	VOID   Close()
	{
		if (m_hFile)
		{
			CloseHandle(m_hFile);
			m_hFile = NULL;
		}
	}

	ULONGLONG Seek(ULONG Method, LONGLONG Distance)
	{
		LARGE_INTEGER li;

		li.QuadPart = Distance;
		if (m_hFile == INVALID_HANDLE_VALUE)
			return -1;

		li.LowPart = ::SetFilePointer(m_hFile, li.LowPart, &li.HighPart, Method);
		if (li.LowPart == INVALID_SET_FILE_POINTER)
			return -1;

		return li.QuadPart;
	}



	ULONG  Write(PVOID Buffer, ULONG Length)
	{
		if (m_hFile == NULL || Buffer == NULL || Length == 0)
			return 0;
		
		DWORD Count = 0;
		BOOL bWrite = WriteFile(m_hFile, Buffer, Length, &Count, NULL);
		m_ErrorCode = GetLastError();
		if (bWrite == 0)
			return 0;

		return Count;
	}

	ULONG  Read(PVOID Buffer, ULONG Length)
	{
		if (m_hFile == NULL || Buffer == NULL || Length == 0)
			return 0;

		DWORD Count = 0;
		BOOL bRet = ReadFile(m_hFile, Buffer, Length, &Count, NULL);
		m_ErrorCode = GetLastError();
		if (bRet == 0)
			return 0;

		return Count;
	}

	ULONG   SetFileOffset(ULONG Offset, DWORD MoveMethod = FILE_BEGIN)
	{
		if (m_hFile == NULL)
			return 0;

		return SetFilePointer(m_hFile, MoveMethod, NULL, MoveMethod);
	}

	ULONGLONG GetSize()
	{
		ULONGLONG FileSize = 0;
		if (m_hFile)
		{
			DWORD FileLow = 0, High = 0;

			FileLow = GetFileSize(m_hFile, &High);
			
			FileSize = (((ULONGLONG)High << 32) | FileLow);
		}

		return FileSize;
	}

public:
	DWORD m_ErrorCode;
	HANDLE m_hFile;

};

class C32ResorceFile
{
public:
	C32ResorceFile()
	{
		Init();
	}
	~C32ResorceFile()
	{

	}
	
	LPVOID LoadResource(int RsrcId, LPWSTR Type)
	{
		m_hRsrc = FindResource(NULL, MAKEINTRESOURCE(RsrcId), Type);
		if (m_hRsrc)
		{
			m_Size = SizeofResource(NULL,m_hRsrc);
			m_hGlobal = ::LoadResource(NULL, m_hRsrc);
			if (m_hGlobal)
			{
				m_Address = LockResource(m_hGlobal);
			}
		
		}

		return m_Address;
	}

	//将资源释放到磁盘.
	DWORD   FreeResourceDisk(int RsrcId, LPCWSTR Type, LPCWSTR FilePath)
	{
		DWORD Size = 0;
		if(LoadResource(RsrcId, (LPWSTR)Type))
		{
			C32File File;
			File.Create(FilePath);
			Size = File.Write(m_Address, m_Size);
		}

		return Size;
	}

public:
	VOID Init()
	{
		m_Address = NULL;
		m_Size = 0;
		m_hGlobal = NULL;
		m_hRsrc = NULL;
	}
	LPVOID  m_Address;
	DWORD   m_Size;
	HGLOBAL m_hGlobal;
	HRSRC  m_hRsrc;
};

//以下是逻辑处理帮助函数
C32String C32zFormatSystemTimeString(ULONGLONG SystemTime);

C32String C32zGetSystemTimeString();
