#pragma once
#include "stdafx.h"
#include "UIDebug.h"
#include "resource.h"
#include "Resource1.h"
#include <vector>
#include <algorithm>


/*
	使用C32Lib，如果需要处理事件，只需要关注C32ControlEventCallback
*/


#define GetRectWidth(rc) (rc.right -rc.left) 
#define GetRectHeigth(rc) (rc.bottom -rc.top) 

#define RtlZeroStringW(Ptr, Count) RtlZeroMemory(Ptr, Count*2)

#define C32_WC_EXPLORER L"C32Explorer"

#define C32GetLastError() m_Error = GetLastError()

#define C32GetUserData(hwnd)  (LONG_PTR)GetWindowLongPtr(hwnd, GWL_USERDATA)

#define C32EVENT_HANDEL_UNREFERENCED_PARAMETER(x, y, z) \
							{			\
								UNREFERENCED_PARAMETER(x);	\
								UNREFERENCED_PARAMETER(y);	\
								UNREFERENCED_PARAMETER(z);	\
							}

#define C32DBG_MESSAGE_BOX() MessageBox(NULL, NULL, NULL, MB_OK)

#define C32SetHandleLReslut(IsHandle, lResultValue) Handle = IsHandle, lResult = lResultValue

#define C32CommandIsMenu(wParam) (HIWORD(wParam) == 0)
#define C32CommandMenuId(wParam) LOWORD(wParam)
#define C32CommandCtrlNotifiyCode(wParam) HIWORD(wParam)
#define C32CommandCtrlId(wParam) LOWORD(wParam)

#define C32IsNull(x) (x == NULL) 
#define C32IsNonNull(x) (x != NULL) 		
			
class C32Window;
class C32ListView;
typedef VOID  (WINAPI*C32_CALLBACK_BUTTON_PUSH)(VOID);

typedef BOOL (WINAPI* C32_EVENT_ON_CALLBACK)(WPARAM wParam, LPARAM lParam, LRESULT& lResult);

typedef BOOL  (WINAPI*C32_EVENT_CALLBACK)(WPARAM wParam, LPARAM lParam, LRESULT& lResult, C32Window* This);

typedef BOOL  (WINAPI*C32_EVENT_CALLBACK_HEADER)(WPARAM wParam, LPARAM lParam, LRESULT& lResult, C32Window* This);

typedef BOOL  (WINAPI*C32_EVENT_CALLBACK_STATIC)(DWORD StaticCtrlId, LRESULT& lResult, C32Window* This);

typedef BOOL  (WINAPI*C32_EVENT_CALLBACK_COMMADN)(DWORD CtrlId, LRESULT& lResult, C32Window* This);



//typedef C32_EVENT_CALLBACK_EX  C32_EVENT_CALLBACK_HEADER;

#define C32_CALL_EVENT_CALLBACK(CallBackFunction)(CallBackFunction(wParam, lParam, lResult, this))

PVOID  C32AllocateBuffer(int Length);

VOID   C32FreeBuffer(PVOID Buffer);

LPWSTR C32AllocateString(int Length);

/*
	释放 std::Vector<C32Window*> m_List
	DeletePtr:TRUE 调用 delete m_List[i]
*/
VOID  C32FreeWindowList(std::vector<C32Window*>& List, BOOL DeletePtr = FALSE);

/*
	利用系统风格画控件
	比直接调用DrawFrameControl要美观
	文档：Visual Styles -> Parts and States

*/
class C32DrawControl
{
public:
	C32DrawControl()
	{
		Init();
	}
	~C32DrawControl()
	{
		Destroy();

	}

	BOOL Open(LPCWSTR ControlName, HWND Controlhwnd = NULL)
	{
		m_Theme = OpenThemeData(Controlhwnd, ControlName);

		return (m_Theme != NULL);
	}

	VOID Close()
	{
		if (m_Theme)
		{
			CloseThemeData(m_Theme);
			m_Theme = NULL;
		}
	}

	BOOL DrawControl(HDC hdc, int iCtrlPartId, int iCtrlStateId, RECT* Rect)
	{
		HRESULT hrst;
		hrst = DrawThemeBackground(m_Theme, hdc, iCtrlPartId, iCtrlStateId, Rect, NULL);
		if (S_OK != hrst)
		{
			ZxDebug((__FUNCTION__"():: Fail : iPartId : %d iStateId: %d\n", iCtrlPartId, iCtrlStateId));
		}
		return (S_OK == hrst);
	}

	BOOL DrawCheckBox(HDC hDc, int iStateId, RECT* Rect)
	{
		return DrawControl(hDc, BP_CHECKBOX, iStateId, Rect);
	}

	BOOL DrawCheckBoxEx(HDC hDc, int iStateId, RECT* Rect)
	{
		BOOL bDraw = FALSE;
		if(Open(WC_BUTTON))
		{
			bDraw= DrawCheckBox(hDc, iStateId, Rect);
			Close();
		}
		
		return bDraw;
	}


	VOID Init()
	{
		m_Theme = NULL;
	}

	VOID Destroy()
	{
		Close();
	}


public:
	HTHEME m_Theme;
};

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
		Assign(CharCount*2);

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

	C32String(const C32String& Right)
	{
		C32AllocateBuffer(Right.m_Length);
		if (m_Buffer)
		{
			m_Length = Right.m_Length;
			RtlCopyMemory(m_Buffer, Right.m_Buffer, m_Length);
		}
	}

	C32String& operator=(const C32String& Right)
	{
		//C32Buffer(Right);
		return *this;
	}

};

class C32RegisterClass
{



};

class C32EventCallback
{
public:
	C32EventCallback()
	{
		Init();
	}

	~C32EventCallback()
	{

	}

	VOID Init()
	{
		m_OnCommand = NULL;

		//Header 
		m_OnNotifyItemStateIconClick = NULL;
	}

public:
	VOID SetOnCommand(C32_EVENT_CALLBACK Callback)
	{
		m_OnCommand = Callback;
	}

	VOID SetOnNotifyItemStateIconClick(C32_EVENT_CALLBACK_HEADER Callback)
	{
		m_OnNotifyItemStateIconClick = Callback;
	}

public: //Window Message
	C32_EVENT_CALLBACK m_OnCommand;

	//点击 CheckBox
	C32_EVENT_CALLBACK_HEADER m_OnNotifyItemStateIconClick;

};

class C32Event
{

public:
	C32Event()
	{
		Init();
	}

	virtual ~C32Event()
	{
		
	}

public:
	virtual BOOL CALLBACK OnCommand(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		C32EVENT_HANDEL_UNREFERENCED_PARAMETER(wParam, lParam, lResult);
		return FALSE;
	}

	virtual BOOL CALLBACK OnNotify(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		C32EVENT_HANDEL_UNREFERENCED_PARAMETER(wParam, lParam, lResult);
		return FALSE;
	}

	virtual BOOL CALLBACK OnDrawItem(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		C32EVENT_HANDEL_UNREFERENCED_PARAMETER(wParam, lParam, lResult);
		lResult = FALSE;
		return FALSE;
	}


	VOID Init()
	{
		
	}


};

class C32MouseEvent
{
public:
	C32MouseEvent()
	{

	}
	
	~C32MouseEvent()
	{


	}

public: //windows message handle
	
	//WM_NCLBUTTONUP 
	virtual BOOL OnNcLButtonUP(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		C32EVENT_HANDEL_UNREFERENCED_PARAMETER(wParam, lParam, lResult);
		BOOL Handle = FALSE;
		
		return Handle;

	}
	
	//WM_NCLBUTTONDOWN
	virtual BOOL OnNcLButtonDown(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		C32EVENT_HANDEL_UNREFERENCED_PARAMETER(wParam, lParam, lResult);
		BOOL Handle = FALSE;

		return Handle;
	}
	
	 
};

class C32StaticEventCallback
{
	
public:
	C32StaticEventCallback()
	{
		Init();
	}
	~C32StaticEventCallback()
	{
		Init();
	}

	VOID Init()
	{
		m_OnClick = NULL;
		m_OnDClick = NULL;
	}

	VOID SetClickEvent(C32_EVENT_CALLBACK_STATIC Callback)
	{
		m_OnClick = Callback;
	}

	VOID SetDClickEvent(C32_EVENT_CALLBACK_STATIC Callback)
	{
		m_OnDClick = Callback;
	}


	//Static Control Event
	C32_EVENT_CALLBACK_STATIC m_OnClick; //点击
	C32_EVENT_CALLBACK_STATIC m_OnDClick;//双击
};

class C32ButtonEventCallback
{

public:
	C32ButtonEventCallback()
	{
		Init();
	}
	~C32ButtonEventCallback()
	{
		Init();
	}

	VOID Init()
	{
		m_OnClick = NULL;
		m_OnDClick = NULL;
	}

	VOID SetClickEvent(C32_EVENT_CALLBACK_STATIC Callback)
	{
		m_OnClick = Callback;
	}

	VOID SetDClickEvent(C32_EVENT_CALLBACK_STATIC Callback)
	{
		m_OnDClick = Callback;
	}


	//Static Control Event
	C32_EVENT_CALLBACK_COMMADN m_OnClick; //点击
	C32_EVENT_CALLBACK_COMMADN m_OnDClick;//双击
};


class C32Icon
{
public:
	static HINSTANCE hInstance;
public:
	C32Icon()
	{
		Init();
	}
	~C32Icon()
	{
		Destroy();
	}
public:
	operator HICON()
	{
		return m_Icon;
	}

public:
	VOID Init()
	{
		m_Icon = NULL;
	}
	VOID Destroy()
	{
		if (m_Icon)
		{
			DestroyIcon(m_Icon);
			m_Icon = NULL;
		}
	}

	BOOL Load(int ResourceId)
	{
		Destroy();

		m_Icon = LoadIcon(hInstance, MAKEINTRESOURCE(ResourceId));

		return (m_Icon != NULL);
	}


	HICON m_Icon;
};

class C32Window : public C32Event
{
public:
	C32Window()
	{
		Init();
	}

	C32Window(HWND Hwnd)
	{
		Init();
		m_Hwnd = Hwnd;
		GetClientRect(m_Hwnd, &m_ClientRect);
		GetWindowRect(m_Hwnd, &m_Rect);

	}

	~C32Window()
	{
		if (m_Hwnd && !m_Attach)
		{
			DestroyWindow(m_Hwnd);
			m_Hwnd = NULL;
		}
		
	}

	VOID Init()
	{
		InitPosSize();
		m_Error = 0;
		m_Style = 0;
		m_ExStyle = 0;

		m_Hwnd = NULL;
		m_Parent = NULL;
		m_HwndTop = NULL;

		m_Attach = FALSE;

		m_StringText.AssignStringW(256);
	}

	VOID InitPosSize()
	{
		m_Cx = 0;
		m_Cy = 0;
		RtlZeroMemory(&m_Rect, sizeof(RECT));
		m_ClientCx = 0;
		m_ClientCy = 0;

		m_MinCx = 0;
		m_MinCy = 0;

		RtlZeroMemory(&m_ClientRect, sizeof(RECT));

	}
	operator HWND () const
	{
		return m_Hwnd;
	}
	
	C32Window& operator =(HWND Hwnd)
	{
		SetHwnd(Hwnd);
		return *this;
	}
	
	VOID Attach(HWND Hwnd)
	{
		m_Hwnd = Hwnd;
		m_Attach = TRUE;
		SetUserData();
		SetPos();
	}

	VOID Detach()
	{
		m_Hwnd = NULL;
	}

public:// visual style 
	BOOL SetVisualStyle(LPCWSTR Theme)
	{
		BOOL Ret = FALSE;
		if (m_Hwnd)
		{
			Ret = ::SetWindowTheme(m_Hwnd, Theme, NULL);
			Ret = (Ret == S_OK ? TRUE : FALSE);
		}
		return Ret;
	}

	BOOL SetExplorerTheme()
	{
		return SetVisualStyle(L"Explorer");
	}


	VOID SetPos()
	{
		GetClientRect(m_Hwnd, &m_ClientRect);
		GetWindowRect(m_Hwnd, &m_Rect);

		m_ClientCx = GetRectWidth(m_ClientRect);
		m_ClientCy = GetRectHeigth(m_ClientRect);

		m_Cx =  GetRectWidth(m_Rect);
		m_Cy = GetRectHeigth(m_Rect);

		//ZxDebug((__FUNCTION__"():: {%d, %d, %d ,%d} \n", m_Rect.left, m_Rect.top, m_Rect.right, m_Rect.bottom));


	}

	//将屏幕坐标点矩形，转换成该窗口Client域为坐标的矩形
	RECT ConvertToClientRect(RECT ScreenRect)
	{
		BOOL bConvert = FALSE;
		RECT  rcRet = {};
		POINT Pt={ScreenRect.left, ScreenRect.top};
		if (m_Hwnd)
		{
			if (ScreenToClient(m_Hwnd, &Pt))
			{
				rcRet.left = Pt.x;
				rcRet.top = Pt.y;
				rcRet.right = Pt.x + GetRectWidth(ScreenRect);
				rcRet.bottom = Pt.y + GetRectHeigth(ScreenRect);
			}
		}

		return rcRet;

	}

	BOOL SetPos(int X, int Y, int Cx, int Cy,  UINT Flag = SWP_NOZORDER,HWND hWndInsertAfter = NULL)
	{
		if (m_Hwnd == NULL)
			return FALSE; 
		
		BOOL bRet = SetWindowPos(m_Hwnd, hWndInsertAfter, X, Y, Cx, Cy, Flag);
		//BOOL bRet = MoveWindow(m_Hwnd,  X, Y, Cx, Cy, TRUE);
		if (bRet == FALSE)
		{
			int i = 0;
		}
		SetPos();
		return bRet;
	}
	
	BOOL SetCenterPos(HWND Parent)
	{
		m_Parent = Parent;
		RECT Rect = {};
		SetPos();
		GetWindowRect(m_Parent, &Rect);
		int X = (Rect.left + Rect.right)/2 - GetRectWidth(m_Rect)/2;
		int Y = (Rect.top + Rect.bottom)/2 - GetRectHeigth(m_Rect)/2;
		return SetPos(X, Y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
	}

	VOID SetMinCxy(int Cx, int Cy)
	{
		m_MinCx = Cx;
		m_MinCy = Cy;
	}
	//Style

	DWORD GetStyle()
	{
		DWORD Style = (DWORD)GetWindowLongPtr(m_Hwnd, GWL_STYLE);
		return Style;
	}

	DWORD SetStyle(DWORD Style)
	{
		return (DWORD)SetWindowLongPtr(m_Hwnd, GWL_STYLE, (LONG_PTR)Style);
	}
	/*
		增加Style
	*/
	BOOL SetStyleEx(DWORD Style)
	{
		DWORD Style0 = 0;
		DWORD dwStyle = GetStyle();
		dwStyle |= Style;

		SetStyle(dwStyle);
		Style0 = GetStyle();

		if (Style0&Style)
			return TRUE;
		else
			return FALSE;
	}


public:
	VOID SetText(LPCWSTR Text)
	{
		SetWindowText(m_Hwnd, Text);
	}

	LPWSTR GetText()
	{
		GetWindowText(m_Hwnd, m_StringText, 256);

		return m_StringText;
	}

public:
	BOOL Enable()
	{
		return EnableWindow(m_Hwnd, TRUE);
	}

	BOOL Disable()
	{
		return EnableWindow(m_Hwnd, FALSE);
	}

	VOID SetUserData(LPVOID UserData = NULL)
	{
		UserData = UserData ? UserData : this;
		SetWindowLongPtr(m_Hwnd, GWL_USERDATA, (LONG_PTR)UserData);
	}

	LPVOID GetUserData()
	{
		return (LPVOID)C32GetUserData(m_Hwnd);
	}

	C32Window* GetParentC32Class()
	{
		C32Window* Class = NULL;
		if (m_Parent == NULL)
			m_Parent = ::GetParent(m_Hwnd);
		

		if (m_Parent)
			Class = (C32Window*)C32GetUserData(m_Parent);

		return Class;
	}

	/*
		获取此控件所在的顶层窗口的C32Class,
		为了更方便处理同一个窗口内多个控件通信
		一般不使用。
	*/

	C32Window* GetTopC32Class()
	{
		C32Window* Class = NULL;
		
		if (m_HwndTop)
			Class = (C32Window*)C32GetUserData(m_HwndTop);

		return Class;
	}


public:
	VOID GetClientLength(__inout int & Width, __inout int& Height)
	{
		Width = GetRectWidth(m_ClientRect);
		Height = GetRectHeigth(m_ClientRect);
	}

	VOID GetLength(int & Width, int& Height)
	{
		Width = GetRectWidth(m_Rect);
		Height = GetRectHeigth(m_Rect);
	}

	VOID SetPtr(HWND Hwnd = NULL)
	{
		m_Hwnd = Hwnd;
	}

	HWND GetPtr()
	{
		return m_Hwnd;
	}

	VOID SetParentPtr(HWND hwnd)
	{
		m_Parent = hwnd;
	}

	HWND SetParentPtr()
	{
		return m_Parent;
	}
	
	VOID SetTopPtr(HWND hwnd)
	{
		m_HwndTop = hwnd;
	}

	HWND GetTopPtr()
	{
		return m_HwndTop;
	}

	HWND GetWindow()
	{
		return m_Hwnd;
	}

	VOID SetHwnd(HWND hwnd)
	{
		SetPtr(hwnd);
		SetPos();
	}

public:
	int	 m_Cy;
	int  m_Cx;
	RECT m_Rect;

	int  m_ClientCx;
	int  m_ClientCy;
	RECT m_ClientRect;

	int     m_MinCx;
	int     m_MinCy;

	HWND	m_Hwnd;
	HWND    m_Parent;
	HWND    m_HwndTop;
	DWORD   m_Error;
	DWORD	m_Style;
	DWORD   m_ExStyle;
	BOOL    m_Attach;

	C32String m_StringText;
};

class C32Menu : public C32Window
{
public:
	static HINSTANCE hInstance;
	C32Menu()
	{
		m_Wnd = NULL;
		m_Sub = NULL;
		m_Parent = NULL;
		m_ResourceId = 0;
	}

	~C32Menu()
	{
		if (m_Wnd)
		{
			DestroyMenu(m_Wnd);
			m_Wnd = NULL;
		}
		if (m_Sub)
		{
			DestroyMenu(m_Sub);
			m_Sub = NULL;
		}
	}


public:
	HMENU LoadResourceMenu(int ResourceId)
	{
		m_Wnd = LoadMenu(C32Menu::hInstance, MAKEINTRESOURCE(ResourceId));
		
		return m_Wnd;
	}

	VOID Display(int ResorceId, int nPos, int X, int Y, HWND Parent)
	{
	   if (m_Sub == NULL)
	   {
		   m_Wnd = LoadMenu(C32Menu::hInstance, MAKEINTRESOURCE(ResorceId));
		   m_Sub = GetSubMenu(m_Wnd, nPos);
		   m_Parent = Parent;
	   }
		
	  TrackPopupMenuEx(m_Sub,  TPM_LEFTALIGN, X, Y, Parent, NULL);
	}
	
	int GetSubItemCount()
	{
		return GetMenuItemCount(m_Sub);
	}


	// 打勾
	BOOL SetSelectSubItem(int CommandId, BOOL bCheck = TRUE)
	{
		DWORD Status;

		Status = CheckMenuItem(m_Wnd, CommandId, bCheck?MF_CHECKED:MF_UNCHECKED);
		return (Status == MF_UNCHECKED ? TRUE : FALSE);
	}

	BOOL SelectSubItem(int CommandId)
	{
		return SetSelectSubItem(CommandId,TRUE);
	}

	BOOL ClearSubItem(int CommandId)
	{
		return SetSelectSubItem(CommandId,FALSE);
	}

	VOID SelectSubMenuItem(int CommandId)
	{
		int Count = GetSubItemCount();
		for(int i = 0; i < Count; i++)
		{
			UINT Id = GetMenuItemID(m_Sub, i);
			if (Id == CommandId)
			{
				SelectSubItem(Id);
			}else
			{
				ClearSubItem(Id);
			}

		}

	}

	VOID SelectSubItemPos(int nPos)
	{
		CheckMenuItem(m_Sub, nPos, MF_BYPOSITION|MF_CHECKED);
	}

public:
	VOID SetParent(HWND Parent)
	{
		m_Parent = Parent;
	}
	
	VOID SetResourceId(int MakeIntId)
	{
		m_ResourceId = MakeIntId;
	}

public:
	HMENU m_Wnd;
	HMENU m_Sub;
	HWND  m_Parent;
	int   m_ResourceId;
};

class C32Group : public C32Window
{


};

class C32Button : public C32Window, public C32ButtonEventCallback
{
public:
	C32Button()
	{
		Init();
	};

	C32Button(HWND Hwnd)
	{
		Init();
		Attach(Hwnd);
	};

	~C32Button(){
		
		
	};

	
	  
public:
	int SetText(LPCWSTR Text)
	{
		Set32Text(Text);
		return (int)Button_SetText(m_Hwnd, m_Text);
	}

	int SetText()
	{
		return (int)Button_SetText(m_Hwnd, m_Text);
	}

	LPWSTR GetText()
	{
		RtlZeroStringW(m_Text, 256);
		Button_GetText(m_Hwnd, m_Text, 256);
		return m_Text;
	}

	VOID Set32Text(LPCWSTR Text)
	{
		wcscpy_s(m_Text, 255, Text);
	}

	HICON SetIcon(HICON hIcon)
	{
		return (HICON)SendMessage(m_Hwnd, BM_SETIMAGE, (WPARAM)IMAGE_ICON, (LPARAM)hIcon);
	}

	HICON GetIcon()
	{
		return (HICON)SendMessage(m_Hwnd, BM_GETIMAGE, (WPARAM)IMAGE_ICON,(LPARAM)0);
	}
	
	HICON SetIcon(int RresourceId)
	{
		HICON hIcon = NULL;

		if(m_Icon.Load(RresourceId) == TRUE)
			hIcon = SetIcon(RresourceId);
		
		return hIcon;
	}
	
public:
	VOID Disable()
	{
		Button_Enable(m_Hwnd, FALSE);
	}

	VOID Enable()
	{
		Button_Enable(m_Hwnd, TRUE);
	}

public: // Event
	
	virtual LRESULT OnCustomDraw(LPARAM lParam)
	{
		LPNMCUSTOMDRAW lpcd = (LPNMCUSTOMDRAW)lParam;

		return CDRF_DODEFAULT;

	}

	virtual BOOL CALLBACK OnCommand(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		lResult = 0;
		BOOL Handle = FALSE;
		C32SetHandleLReslut(FALSE, 0);
		DWORD NotifyCode;
		NotifyCode = HIWORD(wParam);
		switch(NotifyCode)
		{
			case BN_CLICKED:
				Handle  = OnClick(wParam, lParam, lResult);
				break;
			case BN_DOUBLECLICKED:
				Handle  = OnDClick(wParam, lParam, lResult);
				break;
			case BN_SETFOCUS:
				break;

		}

		return Handle;
	}


	virtual BOOL OnClick(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		if (m_OnClick)
			Handle = m_OnClick(C32CommandCtrlId(wParam), lResult, this);	
		return Handle;
	}

	virtual BOOL OnDClick(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		if (m_OnDClick)
			Handle = m_OnDClick(C32CommandCtrlId(wParam), lResult, this);	
		return Handle;
	}

public:
	VOID Init()
	{

	}

	WCHAR m_Text[256];
	C32Icon  m_Icon;
};

class C32Edit : public C32Window
{
public:
	C32Edit()
	{

	}
	~C32Edit()
	{

	}

	VOID Init()
	{

		m_Length = 0;
	}
	//先前状态 0:Disable !0 : Enable
	BOOL Enable()
	{
		return Edit_Enable(m_Hwnd, TRUE);
	}
	
	BOOL Disable()
	{
		return Edit_Enable(m_Hwnd, FALSE);
	}

	VOID SetRect(LPRECT Rect)
	{
		Edit_SetRect(m_Hwnd, Rect);
	}

	VOID SetRect(int X, int Y, int Cx, int Cy)
	{
		RECT Rect = {};
		Rect.left = X;
		Rect.top = Y;
		Rect.right = X + Cx;
		Rect.bottom = Y + Cy;
		Edit_SetRect(m_Hwnd, &Rect);
	}

	LPWSTR GetText()
	{
		m_String.FreeBuffer();
		LPWSTR Text = NULL;
		m_Length = Edit_GetTextLength(m_Hwnd);
		if (m_Length > 0)
		{
			m_String.Assign(m_Length);
			if (m_String.GetBuffer())
			{
				int  iCount = Edit_GetText(m_Hwnd, (LPWSTR)m_String, m_String.GetLength());
				if (iCount == 0)
				{
					m_String.FreeBuffer();
				}
			}
		}
		return m_String;
	}

	int  SetText(LPCWSTR Text)
	{
		Edit_SetText(m_Hwnd, Text);
	}

public:
	int  m_Length;
	C32String  m_String;
};

class C32Static: public C32Window , public C32StaticEventCallback
{
public:
	C32Static()
	{

	}
	
	~C32Static()
	{


	}

public:
	
	BOOL LoadIcon(int ResourceId)
	{
		m_hIcon.Load(ResourceId);
		SetIcon(m_hIcon);
	}

	BOOL SetIcon(HICON hIcon)
	{
		HICON hIco;
		hIco = Static_SetIcon(m_Hwnd, hIcon);

		return C32IsNonNull(hIco);
	}

	HICON GetIcon()
	{
		return Static_GetIcon(m_Hwnd, 0);
	}

	virtual BOOL CALLBACK OnCommand(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		C32EVENT_HANDEL_UNREFERENCED_PARAMETER(wParam, lParam, lResult);
		BOOL Handle = FALSE;
		 
		switch(C32CommandCtrlNotifiyCode(wParam))
		{
			case STN_CLICKED:
				Handle = OnClick(wParam, lParam, lResult);
				break;
			case STN_DBLCLK:
				Handle = OnDClick(wParam, lParam, lResult);
				break;

		}


		return Handle;
	}

	virtual BOOL OnClick(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		if (m_OnClick)
			Handle = m_OnClick(C32CommandCtrlId(wParam), lResult, this);	
		return Handle;
	}

	virtual BOOL OnDClick(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		if (m_OnDClick)
			Handle = m_OnDClick(C32CommandCtrlId(wParam), lResult, this);	
		return Handle;
	}

public:
	C32Icon m_hIcon;
};

class C32ComboBox : public C32Window
{
static HINSTANCE hInstance;
public:
	HWND Create(DWORD dwStyle, 
				int X, int Y, int Cx, int Cy,
				HWND Parent)
	{
		m_Hwnd = CreateWindowEx(0, WC_COMBOBOX, L"C32ComboBox",dwStyle,
								X, Y, Cx, Cy,
								Parent, (HMENU)NULL, hInstance, (LPVOID)this);
		return m_Hwnd;
	}

	BOOL SetEditText(LPCWSTR EditText)
	{
		return ComboBox_SetCueBannerText(m_Hwnd, EditText);
	}

	// 返回序号
	int  Add(LPCWSTR String)
	{
		return ComboBox_AddString(m_Hwnd, String);
	}

	//返回List的个数
	int Delete(int Index)
	{
		return ComboBox_DeleteString(m_Hwnd, Index);
	}

	// 返回序号
	int Insert(int Index, LPCWSTR String)
	{
		return ComboBox_InsertString(m_Hwnd, Index, String);
	}

	int Reset()
	{
		ComboBox_ResetContent(m_Hwnd);
	}

	int SelectItem(LPCWSTR String)
	{
		return ComboBox_SelectString(m_Hwnd, -1, String);
	}

	int SelectItem(int Index)
	{
		return ComboBox_SetCurSel(m_Hwnd, Index);
	}
	
	int GetItemHeight()
	{
		return ComboBox_GetItemHeight(m_Hwnd);
	}

	int SetItemHeight(int iHeight)
	{
		return ComboBox_SetItemHeight(m_Hwnd,-1, iHeight);
	}

	int SetSelectItemHeight(int iHeight)
	{
		return ComboBox_SetItemHeight(m_Hwnd,-1, iHeight);
	}

	BOOL ShowList()
	{
		return ComboBox_ShowDropdown(m_Hwnd, TRUE);
	}

	BOOL HideList()
	{
		return ComboBox_ShowDropdown(m_Hwnd, FALSE);

	}

	BOOL Enable()
	{
		return ComboBox_Enable(m_Hwnd, TRUE);
	}

	BOOL Disable()
	{
		return ComboBox_Enable(m_Hwnd, FALSE);
	}

};

class C32ListBox : public C32Window
{

public:
	static HINSTANCE hInstance;
	static C32Icon   m_Check;
	static C32Icon   m_UnCheck;

	static VOID Initialize()
	{
		m_Check.Load(IDI_ICON_C32CLASS_CHECKBOX_CHECK);
		m_UnCheck.Load(IDI_ICON_C32CLASS_CHECKBOX_UNCHECK);

	}

public:
	C32ListBox()
	{
		Init();
	}
	virtual ~C32ListBox()
	{

	}

	HWND  Create(DWORD dwStyle, 
		int X, int Y, int Cx, int Cy,
		HWND Parent)
	{
		
		m_Hwnd = CreateWindow( L"listbox", NULL, dwStyle, 
								X, Y, Cx, Cy,
								Parent, (HMENU)NULL, hInstance, this);
		C32GetLastError();
		
		m_Parent = Parent;

		return m_Hwnd;
	}
	//index
	int AddString(LPCWSTR String)
	{
		return (int)SendMessageW(m_Hwnd, LB_ADDSTRING, (WPARAM)NULL, (LPARAM)String);		
	}
	//Count
	int DeleteString(int Index)
	{
		return (int)SendMessage(m_Hwnd, LB_DELETESTRING, (WPARAM)Index, (LPARAM)NULL);		

	}

	int InsertString(int Index, LPCWSTR String)
	{
		return (int)SendMessage(m_Hwnd, LB_INSERTSTRING, (WPARAM)Index, (LPARAM)String);		
	}

	void Reset()
	{
		SendMessage(m_Hwnd, LB_RESETCONTENT, (WPARAM)NULL, (LPARAM)NULL);		
	}

	int GetCount()
	{
		return (int)SendMessage(m_Hwnd, LB_DELETESTRING, (WPARAM)NULL, (LPARAM)NULL);		
	}
	
	int GetString(int Index, C32String& String)
	{
		int Length = (int)SendMessageW(m_Hwnd, LB_GETTEXTLEN, (WPARAM)Index, (LPARAM)0);
		if (Length <= 0)
			return LB_ERR;
		
		String.AssignStringW(Length++);
		
		Length = (int)ListBox_GetText(m_Hwnd, Index, (LPWSTR)String.GetBuffer());
		String.m_Length = Length;
		return  String.GetStringLength();
	}

	LPWSTR GetString(int Index)
	{
		GetString(Index,m_StringText);

		return (LPWSTR)m_StringText;
	}

	int SelectString(LPCWSTR String, int Index = -1)
	{
		return (int)SendMessage(m_Hwnd, LB_SELECTSTRING, (WPARAM)Index, (LPARAM)String);		
	}

	// single-selection list box
	// Current Select Item
	int SetCurrentSelect(int Index)
	{
		return (int)SendMessage(m_Hwnd, LB_SETCURSEL, (WPARAM)Index, (LPARAM)NULL);
	}
	
	int ClearCurrentSelect()
	{
		return SetCurrentSelect(-1);
	}

	int GetCurrentSelect()
	{
		return (int)SendMessage(m_Hwnd, LB_GETCURSEL, (WPARAM)NULL, (LPARAM)NULL);
	}
	
	LPCWSTR GetCurrentSelectString()
	{
		int iIndex = GetCurrentSelect();
		if(GetString(iIndex, m_StringText))
		{
			return m_StringText.GetString();
		}

		return NULL;
	}


	//multiple-selection list box.
	// Select Item
	BOOL SetSelect(int Index)
	{
		int Ret = (int)SendMessage(m_Hwnd, LB_SETSEL, (WPARAM)TRUE, (LPARAM)Index);
		return (Ret == LB_ERR);
	}

	BOOL ClearSelect(int Index)
	{
		int Ret = (int)SendMessage(m_Hwnd, LB_SETSEL, (WPARAM)FALSE, (LPARAM)Index);
		return (Ret == LB_ERR);
	}

	BOOL SetSelectAll()
	{
		return SetSelect(-1);
	}

	BOOL ClearSelectAll()
	{
		return ClearSelect(-1);
	}

	BOOL SelectItemRange(DWORD iStart, DWORD iEnd)
	{
		LRESULT Ret = SendMessage(m_Hwnd, LB_SELITEMRANGE, (WPARAM)TRUE, (LPARAM)MAKELPARAM(iStart, iEnd));		

		return (Ret == LB_ERR);
	}

	BOOL ClearItemRance(DWORD iStart, DWORD iEnd)
	{
		LRESULT Ret = SendMessage(m_Hwnd, LB_SELITEMRANGE, (WPARAM)FALSE, (LPARAM)MAKELPARAM(iStart, iEnd));		

		return (Ret == LB_ERR);
	}

public:
	BOOL SetItemHeight(int Height, int Index = 0)
	{
	  LRESULT Ret = SendMessage(m_Hwnd, LB_SETITEMHEIGHT, (WPARAM)Index, (LPARAM)Height);		
	  return (Ret == LB_ERR);
	}
	//multiple-column list box
	VOID SetColumnWidth(int Width)
	{
		SendMessage(m_Hwnd, LB_SETITEMHEIGHT, (WPARAM)Width, (LPARAM)NULL);	
	}

public:
	 //WM_MEASUREITEM: 
	virtual BOOL OnMeasureItem(LPMEASUREITEMSTRUCT lpmis, LRESULT& lResult)
	{
		lpmis->itemHeight = m_ItemCy;
		lResult = (LRESULT)TRUE;

		return TRUE;
	}
	//WM_DRAWITEM
	virtual BOOL CALLBACK OnDrawItem(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		LPDRAWITEMSTRUCT lpdis = (LPDRAWITEMSTRUCT)lParam;
		TEXTMETRIC tm = {}; 
		C32String String;
		int y;
		LPWSTR XX;
		if (IsOwnerDraw() == FALSE)
			return FALSE;

		lResult = (LRESULT)TRUE;
		// If there are no list box items, skip this message. 
		if (lpdis->itemID == -1)
		{
			return TRUE;
		}
		
		C32DrawControl Draw;

		Draw.Open(WC_BUTTON);
		
		switch(lpdis->itemAction)
		{
			case ODA_SELECT: 
			case ODA_DRAWENTIRE: 
				  if(GetString(lpdis->itemID, String) ==LB_ERR)
					break;
				  XX = (LPWSTR)String.GetBuffer();
				  GetTextMetrics(lpdis->hDC, &tm); 

				  y = (lpdis->rcItem.bottom + lpdis->rcItem.top - 
					  tm.tmHeight) / 2;

				  TextOut(lpdis->hDC, 
					  32 + 6, 
					  y, 
					  (LPCWSTR)String.GetBuffer(), 
					  String.GetLength());  
				  RECT rcItem;
				  SetRect(&rcItem, lpdis->rcItem.left+2, lpdis->rcItem.top+2, lpdis->rcItem.left+28, lpdis->rcItem.top+28);
				  // Is the item selected? 
				if (lpdis->itemState & ODS_SELECTED) 
				{ 		
					Draw.DrawCheckBox(lpdis->hDC, CBS_CHECKEDNORMAL, &rcItem);
				}else
				{
					Draw.DrawCheckBox(lpdis->hDC, CBS_UNCHECKEDNORMAL, &rcItem);
				} 
				break;
			case ODA_FOCUS: 
				Draw.DrawCheckBox(lpdis->hDC, CBS_CHECKEDHOT, &rcItem);
				break;
		}

		return TRUE;

	}

public:
	VOID SetItemCy(int Height)
	{
		m_ItemCy = Height;
	}

public:
	BOOL IsOwnerDraw()
	{
		DWORD Style = GetWindowStyle(m_Hwnd);

		if (Style&(LBS_OWNERDRAWFIXED|LBS_OWNERDRAWVARIABLE))
			return TRUE;
		else
			return FALSE;
	}

public:
	VOID Init()
	{
		m_ItemCy = 40;
	}
public:
	int  m_ItemCy;	
};

class C32ImageList
{
public:
#define IMAGE_LIST_INITIAL_COUNT 32
#define IMAGE_LIST_GROUW_COUNT  10
	static HINSTANCE hInstance;
public:
	C32ImageList():m_List(NULL)
	{

	}
	~C32ImageList()
	{
		Destroy();
	}

	operator HIMAGELIST() const
	{
		return m_List;
	}

	HIMAGELIST Create(int Cx, int Cy, UINT Flags, int Initial = IMAGE_LIST_INITIAL_COUNT, int Grow = IMAGE_LIST_GROUW_COUNT)
	{
		HIMAGELIST List = ImageList_Create(Cx, Cy, Flags, Initial, Grow);
		m_List = List;
		return m_List; 
	}

	HIMAGELIST CreateMetrics(int MetricsIndexX, int MetricsIndexY)
	{
		DWORD Cx = GetSystemMetrics(MetricsIndexX);
		DWORD Cy = GetSystemMetrics(MetricsIndexY);
		return Create(Cx, Cy, ILC_COLOR32);
	}

	HIMAGELIST CreateSmall()
	{
		return CreateMetrics(SM_CXSMICON, SM_CYSMICON);
	}

	HIMAGELIST CreateNormal()
	{
		return CreateMetrics(SM_CXICON, SM_CYICON);
	}

	VOID Destroy()
	{
		if (m_List)
		{
			ImageList_Destroy(m_List);
			m_List = NULL;
		}
	}

	int  AddIcon(HICON hIcon)
	{
		int Index = -1;
	
		if (m_List)
			Index = ImageList_AddIcon(m_List, hIcon);
	
		return Index;
	}

	/*
		Resource 文件里的ICON id
	*/
	int AddIcon(INT ResourceId)
	{
		int Index = -1;
		LPWSTR Id = MAKEINTRESOURCE(ResourceId);
		HICON hIcon = LoadIcon(C32ImageList::hInstance, Id);

		if (hIcon)
		{
			Index = AddIcon(hIcon);
		}
		DestroyIcon(hIcon);

		return Index;
	}

	BOOL Remove(int Index)
	{
		return ImageList_Remove(m_List, Index);
	}

	COLORREF SetBkColor(__in COLORREF color)
	{
		return ImageList_SetBkColor(m_List, color);
	}

	HIMAGELIST GetList()
	{
		return m_List;
	}

public:
	HIMAGELIST m_List;

};

class C32TreeView : public C32Window, public C32EventCallback
{
#define TV_MASK_NO_BIT -1
public:

	static HINSTANCE  hInstance; //
	static  LRESULT  CALLBACK TreeSubclassProc (HWND hWnd, UINT uMsg, WPARAM wParam,
		LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);

public:
	C32TreeView(){};
	~C32TreeView(){};

	HWND Create(DWORD  dwExStyle, DWORD dwStyle,int X, int Y, int Width, int Height, HWND Parent);

	VOID DestroyView();

	// 控件样式
	VOID SetExplorerTheme(){if(m_Hwnd)SetWindowTheme(m_Hwnd, L"Explorer", NULL);};

	VOID SetExtendedStyles(DWORD dwExStyle);

	VOID AddExtendedStyles(DWORD dwExStyle);

	DWORD GetExtendedStyles();

	BOOL SetSubclass();

	BOOL RemovSubClass()
	{
		RemoveWindowSubclass(m_Hwnd, C32TreeView::TreeSubclassProc, (ULONG_PTR)this);
	}
public: //成员函数设置
	//设置.rc里右键显示菜单的资源ID
	VOID SetMenuId(int ResourceId)
	{
		m_Menu.m_ResourceId = ResourceId;
	}

	VOID SetImageList(int ImageType = TVSIL_NORMAL|TVSIL_STATE)
	{
		if (ImageType & TVSIL_NORMAL)
			TreeView_SetImageList(m_Hwnd, m_ImageListNormal, TVSIL_NORMAL);

		if (ImageType & TVSIL_STATE)
			TreeView_SetImageList(m_Hwnd, m_ImageListNormal, TVSIL_NORMAL);


	}

	VOID AddSilNormalIcon(int ResourceId)
	{
		m_ImageListNormal.AddIcon(ResourceId);
	}

	VOID AddSilStateIcon(int ResourceId)
	{
		m_ImageListState.AddIcon(ResourceId);
	}

	// 插入节点
	HTREEITEM InsertItem(HTREEITEM Parent, HTREEITEM InsertAfter, LPWSTR Text, int iImage, int iSelectedImage, int cChildren, LPARAM lParam);

	HTREEITEM InsertItem(HTREEITEM Parent, HTREEITEM InsertAfter, LPWSTR Text, int cChildren = 1, int iImage = TV_MASK_NO_BIT,  LPARAM lParam = NULL)
	{
		HTREEITEM hItem = InsertItem(Parent, InsertAfter, Text, iImage, TV_MASK_NO_BIT, cChildren, lParam);

		return hItem;

	}

	HTREEITEM InsertRootItem(HTREEITEM InsertAfter, LPWSTR Text, int iImage, int iSelectedImage , int cChildren , LPARAM lParam);

	HTREEITEM InsertRootItem(HTREEITEM InsertAfter, LPWSTR Text, int cChildren = 1, int iImage =TV_MASK_NO_BIT, LPARAM lParam = NULL)
	{
		HTREEITEM hItem = InsertRootItem(InsertAfter, Text, iImage, TV_MASK_NO_BIT, cChildren, lParam);
		return hItem;
	}


	HTREEITEM InsertItemAsyn(HTREEITEM Parent, HTREEITEM InsertAfter, LPWSTR Text, int iImage, int iSelectedImage, int cChildren, LPARAM lParam);
	//WM_CONTEXMENU
	virtual BOOL OnContextMenu(HWND hwnd, int xCursor, int yCursor)
	{
		m_Menu.Display(m_Menu.m_ResourceId, 0,xCursor, yCursor, m_Hwnd);
		return TRUE;
	}

	// WM_COMMAND
	//virtual BOOL CALLBACK OnCommand()
	BOOL CALLBACK OnCommand(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		HWND HwndCtrl;
		DWORD MenuId;
		HwndCtrl= (HWND)lParam;
		MenuId = LOWORD(wParam);
		
		m_Menu.SelectSubMenuItem(MenuId);

		if (m_OnCommand)
			Handle = m_OnCommand(wParam, lParam, lResult, this);

		ZxDebug((__FUNCTION__"():: Hwnd: %p %d \n", HwndCtrl, MenuId));

		return TRUE;	
	}
	// WM_NOTIFY
	virtual BOOL CALLBACK OnNotify(WPARAM wParam, LPARAM lParam, LRESULT& lResult);


	//Returns FALSE to accept the change, or TRUE to prevent the change
	virtual BOOL CALLBACK OnNotifySelChanged(LPNMTREEVIEW NMTreeView)
	{
		(NMTreeView);
		m_Result = FALSE ;
		return FALSE;
	}
	//Returns TRUE to prevent the selection from changing.
	virtual BOOL CALLBACK OnNotifySelChanging(LPNMTREEVIEW NMTreeView)
	{
		(NMTreeView);
		m_Result = FALSE ;		
		return TRUE;
	}

	//Returns FALSE to accept the change, or TRUE to prevent the change.
	virtual BOOL CALLBACK OnNotifyItemChanging(NMTVITEMCHANGE*   NMItemChange)
	{
		(NMItemChange);
		m_Result = FALSE ;
		return TRUE;
	}

	virtual BOOL CALLBACK OnNotifyItemChanged(NMTVITEMCHANGE*   NMItemChange)
	{
		(NMItemChange);
		m_Result = FALSE ;
		return TRUE;
	}

	virtual BOOL CALLBACK OnNotifyCustomDraw(LPNMCUSTOMDRAW  NMCustomDraw)
	{
		(NMCustomDraw);		
		return FALSE;
	}

	virtual BOOL CALLBACK OnNotifyGetDispInfo(LPNMTVDISPINFO NMTvDispInfo);


	virtual LPWSTR CALLBACK AsynGetText(TVITEM& Tvi)
	{
		return L"AsynGetText";
	}

	virtual int    CALLBACK AsynGetSelectedImage(TVITEM& Tvi)
	{
		return 0;
	}

	virtual int    CALLBACK AsynGetImage(TVITEM& Tvi)
	{
		return 0;
	}

	virtual int    CALLBACK AsynGetChildren(TVITEM& Tvi)
	{
		return 0;
	}

public:
	VOID Init()
	{

		m_Cx = 0;
		m_Cy = 0;
	}
public:


public:
	LRESULT		 m_Result;
	C32ImageList m_ImageListNormal;
	C32ImageList m_ImageListState;
	C32Menu		 m_Menu;



};

class C32Header : public C32Window, public C32EventCallback
{
#define HEADER_COUNT_MAX  20

public:
	C32Header()
	{
		Init();
	};
	~C32Header(){};

public:
	
	VOID SetHeader(HWND Header, C32ListView* List = NULL)
	{
		  m_List = List;
		  Attach(Header);
	}

	BOOL GetItem(int iItem, HDITEM& hdi)
	{
		return Header_GetItem((HWND)m_Hwnd, iItem, &hdi);
	}

	BOOL SetItem(int iItem, HDITEM& hdi)
	{
		return Header_SetItem((HWND)m_Hwnd, iItem, &hdi);
	}

	int GetFormat(int iItem)
	{
		HDITEM hdi = {};
		hdi.mask = HDI_FORMAT;
		GetItem(iItem, hdi);

		return hdi.fmt;
	}

	int GetSort(int iItem)
	{
		int fmt = GetFormat(iItem);
		
		fmt &= HDF_SORTUP|HDF_SORTDOWN;

		return(fmt);
	}

	void SetFormat(int iItem, int Format)
	{
		HDITEM hdi = {};
		hdi.mask = HDI_FORMAT;
		hdi.fmt =Format;
		SetItem(iItem, hdi);
	}

	void AddFormat(int iItem, int Format)
	{
		int fmt = 0;
		fmt = GetFormat(iItem);

		if ((fmt& Format) == Format)
			return;

		fmt|= Format;
		SetFormat(iItem, fmt);
	}

	VOID ResetSort(int iItem)
	{
		HDITEM  hi = {};
		hi.mask = HDI_FORMAT;
		if(GetItem(iItem, hi))
		{
			int sfmt = (HDF_SORTDOWN | HDF_SORTUP);
			if (hi.fmt & sfmt)
			{
				hi.fmt &=(~sfmt);
				SetItem(iItem, hi);
			}
			
		}
	}

	VOID SetSort(int iItem, BOOL bDown = TRUE)
	{
		int fmt;
		fmt = GetFormat(iItem);
		
		int sfmt = (HDF_SORTDOWN | HDF_SORTUP);
		fmt &=(~sfmt);
		fmt |= (bDown ? HDF_SORTDOWN : HDF_SORTUP);
				
		SetFormat(iItem, fmt);
	}

	/*
		只有一列显示排序图标
	*/
	VOID SetHeaderSort(int iItem, BOOL bDown = TRUE)
	{
		int Count = GetCount();
		for(int i = 0; i < Count; i++)
		{
			if (iItem != i)
				ResetSort(i);
			else
				SetSort(i, bDown);
		}
	}

	VOID SetHeaderSortUp(int iItem)
	{
		SetHeaderSort(iItem, FALSE);
	}

	VOID SetHeaderSortDown(int iItem)
	{
		SetHeaderSort(iItem, TRUE);
	}

	int  GetCount()
	{
		m_Count = Header_GetItemCount((HWND)m_Hwnd);
		return m_Count;
	}

	//Check Box
	VOID SetCheckboxStyle(int iItem = 0)
	{
		SetStyleEx(HDS_CHECKBOXES);

		int fmt = GetFormat(iItem);
		fmt |= HDF_CHECKBOX;
		SetFormat(iItem, fmt);
	}

	BOOL IsCheckState(int iItem)
	{
		int Fmt = GetFormat(iItem);

		return !!(Fmt&HDF_CHECKED);
	}

public:
	virtual BOOL CALLBACK OnNotify(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		LPNMHDR lphdr = (LPNMHDR)lParam;
		
		UIDebugOutputHeaderNotify(lphdr->code);

		switch(lphdr->code)
		{
			case HDN_ITEMSTATEICONCLICK:
				Handle= OnNotifyItemStateIconClick(wParam, lParam, lResult);
				break;
			
		}

		return Handle;
	}

	virtual BOOL OnNotifyItemStateIconClick(WPARAM wParam, LPARAM lParam, LRESULT& lResult);

public:
	VOID Init()
	{
		m_List = NULL;
	}
public:
	int m_Count; //Item 总数
public:
	C32ImageList m_ImageList;
	C32ListView* m_List; //Header 关联的List
};

class C32ListView : public C32Window, public C32EventCallback
{
#define LV_MASK_NO_BIT -1
	static HINSTANCE  hInstance;
	static LRESULT CALLBACK ListSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam,
		LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
	{
		LRESULT lResult = 0;
		C32ListView* This = (C32ListView*)dwRefData;
		switch(uMsg)
		{
			case WM_COMMAND:
				This->OnCommand(wParam, lParam, lResult);
				break;
				
		}
		return DefSubclassProc(hWnd, uMsg, wParam, lParam);
	}

public:
	C32ListView(){}
	~C32ListView(){}	

public:
	HWND Create( DWORD dwExStyle, DWORD dwStyle, 
		int X, int Y, int Width, int Height,HWND Parent);

public:
	operator HWND ()
	{
		return m_Wnd.GetPtr();
	}
	
	HWND GetWindow()
	{
		return m_Wnd;
	}

	VOID SetExtendedStyle(DWORD dwExStyle)
	{
		ListView_SetExtendedListViewStyle(m_Wnd, dwExStyle);
	}

	VOID AddExtendedStyle(DWORD dwExStyle)
	{
		DWORD Ex = ListView_GetExtendedListViewStyle(m_Wnd);
		Ex |= dwExStyle;
		ListView_SetExtendedListViewStyle(m_Wnd, Ex);
	}

	DWORD GetExtendedStyle()
	{
		DWORD dwExStyle = ListView_GetExtendedListViewStyle(m_Wnd);
		return dwExStyle;
	}

	VOID SetCheckBoxStyle()
	{
		AddExtendedStyle(LVS_EX_CHECKBOXES);
	}
	/*
		此函数要在 列插入完成之后调用
	*/
	VOID SetHeaderCheckBox()
	{
		m_Header.SetCheckboxStyle(0);
	}

	VOID SetExplorerTheme()
	{
		SetWindowTheme(m_Wnd, L"Explorer", NULL);
	}

	VOID SetSubclass()
	{
		SetWindowSubclass(m_Wnd, C32ListView::ListSubclassProc, (UINT_PTR)this, (DWORD_PTR)this);
	}

	BOOL RemovSubClass()
	{
		RemoveWindowSubclass(m_Wnd, C32ListView::ListSubclassProc, (ULONG_PTR)this);
	}

	HWND GetListHeader()
	{
		HWND Header = ListView_GetHeader(m_Wnd);

		m_Header.SetHeader(Header, this);

		return Header;
	}

	VOID SetMenuId(int ResourceId)
	{
		m_Menu.SetResourceId(ResourceId);
	}

	VOID SetImageList(BOOL Normal = TRUE, BOOL Small = TRUE, BOOL State = TRUE)
	{
		if (Normal)
			ListView_SetImageList(m_Wnd, m_ImageListNormal, LVSIL_NORMAL);

		if (Small)
			ListView_SetImageList(m_Wnd, m_ImageListSmall, LVSIL_SMALL);

		if (State)
			ListView_SetImageList(m_Wnd, m_ImageListStatus, LVSIL_STATE);

	}

	int InsertColumn(int iCol, int iSubItem, LPWSTR Text,int Format, int Cx, int iImage = -1, int CxMin = 32);

	int InsertItem(int iItem, LPWSTR Text, int iImage = -1, LPARAM lParam = 0);

	int InsertSubItem(int iItem, int iSubItem, LPWSTR Text, int Image = -1);

	int InsertItemAsyn(int iItem, LPWSTR Text, int iImage = -1, LPARAM lParam = 0);

	int InsertSubItemAsyn(int iItem, int iSubItem, LPWSTR Text, int Image = -1);

	int GetItemCount()
	{
		return ListView_GetItemCount(m_Wnd.GetWindow());
	}

	int GetSelectedColumn()
	{
		return ListView_GetSelectedColumn(m_Wnd);
	}

	static int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
	{
		C32ListView* List = (C32ListView*)lParamSort;
		ZxDebug(("iItem1 : %d iItem2: %d  %x\n", lParam1, lParam2,(LOWORD(List->m_Parameter)& HDF_SORTDOWN)));
		WCHAR T1[260]={}, T2[260]={};
		ListView_GetItemText(List->m_Wnd,  lParam1, HIWORD(List->m_Parameter), T1, 260);
		ListView_GetItemText(List->m_Wnd,  lParam2, HIWORD(List->m_Parameter), T2, 260);

		if (LOWORD(List->m_Parameter)&HDF_SORTDOWN)
		{
			return wcscmp(T1, T2);
		}else
		{
			return wcscmp(T2, T1);			
		}
	}

	virtual LPWSTR GetDispInfoText(int iItem, int iSubItem)
	{
		return L"C32ListView";
	}

	virtual int GetDispInfoImage(int iItem, int iSubItem)
	{
		return 0;
	}

	BOOL OnNotifyGetDispInfo(NMLVDISPINFO* Disp)
	{
		LVITEM& lvi = Disp->item;
		if (lvi.mask & LVIF_TEXT)
		{
			lvi.pszText = GetDispInfoText(lvi.iItem, lvi.iSubItem);
		}
		if (lvi.mask & LVIF_IMAGE)
		{
			lvi.iImage = GetDispInfoImage(lvi.iItem, lvi.iSubItem);
		}

		return TRUE;
	} 

public:
	// WM_NOTIFY
	virtual BOOL CALLBACK OnNotify(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		lResult = 0;
		LPNMHDR lphdr = (LPNMHDR)lParam;

		int NotifyCode = 0;
		NotifyCode = lphdr->code;
		UIDebugOutputListViewNotify(NotifyCode);
		switch(NotifyCode)
		{
			case LVN_COLUMNCLICK:
				OnNotifyColumnClick((LPNMLISTVIEW)lphdr);
				break;
			case LVN_GETDISPINFO:
				OnNotifyGetDispInfo((NMLVDISPINFO*)lphdr);
				break;
			case LVN_ITEMCHANGING:
				Handle = OnNotifyItemChanging(wParam, lParam, lResult);
				break;
			case LVN_ITEMCHANGED:
				Handle =OnNotifyItemChanged(wParam, lParam,lResult);
				break;

		}
		return Handle;
	};

	virtual BOOL  OnNotifyColumnClick(LPNMLISTVIEW NMLv)
	{
		int iSubItem = NMLv->iSubItem;

		int fmt = m_Header.GetSort(iSubItem);
		/*
		if (fmt& HDF_SORTDOWN)
		{
			
		}else if(fmt& HDF_SORTUP)
		{

		}else
		{

		}*/
		ZxDebug((__FUNCTION__"():: Click : %d  %s\n", iSubItem, (fmt == HDF_SORTDOWN ? "down-arrow" :"up-arrow")));
		
		m_Parameter = MAKELONG(fmt, iSubItem);
		ListView_SortItemsEx(m_Wnd, CompareFunc, this);

		m_Header.SetHeaderSort(NMLv->iSubItem, (fmt == HDF_SORTDOWN ? FALSE :TRUE));

		return TRUE;
	}

	virtual BOOL OnContextMenu(HWND hwnd, int xCursor, int yCursor)
	{
		m_Menu.Display(m_Menu.m_ResourceId, 0,xCursor, yCursor, m_Wnd);
		return TRUE;
	}


	BOOL CALLBACK OnCommand(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		HWND HwndCtrl;
		DWORD MenuId;
		HwndCtrl= (HWND)lParam;
		MenuId = LOWORD(wParam);

		m_Menu.SelectSubMenuItem(MenuId);

		if (m_OnCommand)
			Handle = m_OnCommand(wParam, lParam, lResult, this);

		ZxDebug((__FUNCTION__"():: Hwnd: %p %d \n", HwndCtrl, MenuId));

		return TRUE;	
	}

	virtual BOOL  OnNotifyItemChanged(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		/*LPNMLISTVIEW lplv = (LPNMLISTVIEW)lParam;
		int iSubItem = lplv->iSubItem;
		if (IsCheckBox())
		{
			if (!(lplv->uOldState&LVIS_SELECTED) && lplv->uNewState&LVIS_SELECTED)
			{
				SetCheck(lplv->iItem);
			}
			if ((lplv->uOldState&LVIS_SELECTED) && !(lplv->uNewState&LVIS_SELECTED))
			{
				ResetCheck(lplv->iItem);
			}
			
		}
	
		UIDebugOutputNmListView(lplv);*/
		return FALSE;
	}

	virtual BOOL  OnNotifyItemChanging(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		lResult = FALSE;
		LPNMLISTVIEW lplv = (LPNMLISTVIEW)lParam;
		int iSubItem = lplv->iSubItem;
		
		/*lplv->uNewState &= ~LVIS_FOCUSED;
		lplv->uOldState &= ~LVIS_FOCUSED;*/
		//UIDebugOutputNmListView(lplv);
		return TRUE;
	}

	//LVS_EX_CHECKBOXES
	VOID SetCheck(int iItem)
	{
		ListView_SetCheckState((HWND)m_Wnd, iItem, TRUE);
	}

	VOID ResetCheck(int iItem)
	{
		ListView_SetCheckState((HWND)m_Wnd, iItem, FALSE);
	}

	VOID SetCheckList()
	{
		int Count = GetItemCount();

		for(int i = 0; i < Count; i++)
		{
			SetCheck(i);
		}
	}

	VOID ResetCheckList()
	{
		int Count = GetItemCount();

		for(int i = 0; i < Count; i++)
		{
			ResetCheck(i);
		}
	}


	BOOL  IsCheckBoxStyle()
	{
		return TRUE;
	}

public:
	

	DWORD m_ExStyle;
	DWORD m_Style;

public:
	C32ImageList m_ImageListStatus;
	C32ImageList m_ImageListNormal;
	C32ImageList m_ImageListSmall;

public:
	C32Header m_Header;
	C32Menu       m_Menu;
	HWND		  m_Parent;
	C32Window	  m_Wnd;

public:
	
	LPARAM m_Parameter;

public:
};

class C32StatusBar : public C32Window
{
#define STATUS_PART_MAX_COUNT 20

public:
	static HINSTANCE hInstance;
public:
	HWND CreateStatus(DWORD ExStyle, DWORD Style, HWND Parent)
	{
		HWND hwnd = CreateWindowEx(ExStyle, STATUSCLASSNAME, L"C32StatusBar", Style,
								   0, 0, 0, 0, Parent, (HMENU)this, C32StatusBar::hInstance, (LPVOID)this);

		m_Hwnd = hwnd;
		
		return m_Hwnd;
	}

	VOID DestroyStatus()
	{
		
		DestroyWindow(m_Hwnd);
			
	}
	
	BOOL SetPart(int Count, int Part[])
	{
		m_Count = Count;
		RtlCopyMemory(m_Part, Part, Count* sizeof(int));

		return SendMessage(m_Hwnd, SB_SETPARTS, (WPARAM)Count,(LPARAM)m_Part);
	}

	BOOL SetText(int iPartType, LPWSTR Text)
	{
		return SendMessage(m_Hwnd, SB_SETTEXT, (WPARAM)(iPartType), (LPARAM)Text);
	}

	BOOL SetIcon(int iPart, HICON hIcon)
	{
		return SendMessage(m_Hwnd, SB_SETICON, (WPARAM)iPart, (LPARAM)hIcon);
	}


public:
	int  m_Count; //分割总数
	int  m_Part[STATUS_PART_MAX_COUNT];
	
};

/*
	容器类
	如果一个窗口包含多个控件可以将该窗口作为容器来管理控件.
*/
#define C32ContainerCallOnXyz(hwndCtl, OnXyz)\
		for(size_t i = 0; i < m_List.size(); i++)\
		{										\
			if (m_List[i]->GetPtr() == hwndCtl)\
			{\
				Handle = m_List[i]->OnXyz(wParam, lParam, lResult);\
				break;\
			}\
		}


class C32Container : public C32Window, public C32MouseEvent
{
public:
	C32Container()
	{
		Init();
	}

	~C32Container()
	{
		Destroy();
	}

public:
	
	VOID AddC32Window(C32Window* Window)
	{
		m_List.push_back(Window);
	}
	

public:
	virtual BOOL CALLBACK OnDrawItem(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		LPDRAWITEMSTRUCT lpdis = (LPDRAWITEMSTRUCT)lParam;
		C32ContainerCallOnXyz(lpdis->hwndItem, OnDrawItem);

		return Handle;
	}

public:	
	VOID Init()
	{
		m_bDeleteList = FALSE;
	}

	VOID Destroy()
	{
		C32FreeWindowList(m_List, m_bDeleteList);
	}

public:
	std::vector<C32Window*> m_List;
	BOOL					m_bDeleteList;
};



class C32Dialog : public C32Container
{
	
public:
	static INT_PTR CALLBACK C32DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		//ZxDebug((__FUNCTION__"():: uMsg:%s  (%d) wParam: %d lParam: %08d(%d:%d)\n", UiDebugGetWindowMessageString(uMsg),uMsg, wParam,lParam,LOWORD(lParam), HIWORD(lParam)));
		UiDebugOutWinowsMesageFilter(uMsg, wParam, lParam, __FUNCTION__);
		C32Dialog * This = (uMsg == WM_INITDIALOG ? (C32Dialog*)lParam : (C32Dialog*)GetWindowLongPtr(hwndDlg, GWL_USERDATA));
		BOOL Handle = FALSE;
		LRESULT lResult = FALSE;
		switch(uMsg)
		{
			case WM_INITDIALOG:
				Handle = This->OnInitDialog(hwndDlg, uMsg, wParam, lParam,lResult);
				break;
			case WM_COMMAND:
				Handle = This->OnCommand(wParam, lParam, lResult);
				break;
			case WM_NOTIFY:
				if (This)
					Handle = This->OnNotify(wParam, lParam, lResult);
				break;
			case WM_DESTROY:
				This->Destroy();
				break;
			/*case WM_NCCALCSIZE:
				Handle = This->OnNcCalcSize(wParam, lParam, lResult);
				return Handle;
			
			case WM_WINDOWPOSCHANGED:
				Handle = This->OnWindowPosChanged(wParam, lParam, lResult);
				break;
			case WM_MOVE:
				Handle = This->OnMove(wParam, lParam, lResult);
				break;*/
			case WM_SIZE:
				Handle = This->OnSize(wParam, lParam, lResult);
				break;
			case WM_DRAWITEM:
				Handle = This->OnDrawItem(wParam, lParam, lResult);
				break;
			
				
		}
		return (INT_PTR)Handle;
	}
	static HINSTANCE hInstance;
public:

	C32Dialog()
	{

	}

	~C32Dialog()
	{


	}

public:
	BOOL Create(int ResourceId, HWND hwndParent)
	{
		INT_PTR Ret = DialogBoxParam(C32Dialog::hInstance,
							MAKEINTRESOURCE(ResourceId), 
							hwndParent, C32Dialog::C32DialogProc, (LPARAM)this);
		
		ZxDebug((__FUNCTION__"():: m_Hwnd : %p Error %d \n", Ret, GetLastError()));

		return (Ret != NULL);
	}

public:
	VOID SetReturnValue(LRESULT lResult)
	{
		 SetWindowLongPtr(m_Hwnd, DWL_MSGRESULT, lResult);
	}

	VOID Close()
	{
		EndDialog(m_Hwnd, 0);
	}

	virtual VOID Destroy()
	{
		//C32FreeWindowPtrList(m_List);
	}


public: // Windows Message
	virtual BOOL CALLBACK OnInitDialog(HWND hwndDlg, UINT uMsg, WPARAM  DefautFocusHwnd, LPARAM InitParam, LRESULT& lResult)
	{
		(hwndDlg),(uMsg),(DefautFocusHwnd),(InitParam);
		lResult = TRUE;
		this->SetUserData();
		Attach(hwndDlg);
		return TRUE;
	}

	virtual BOOL CALLBACK OnCommand(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;

		if (wParam == 0ULL)
		{
			Handle = OnCommandMenu(wParam, lParam, lResult);
		}else if (wParam == 1ULL )
		{
			Handle = OnCommandAccelerator(wParam, lParam, lResult);
		}else //Control Command
		{
			if (LOWORD(wParam) == IDCANCEL)
			{
				Close();
				Handle = TRUE;
			}
			HWND HwndControl = (HWND)lParam;
			/*for(size_t i = 0; i < m_List.size(); i++)
			{
				if (m_List[i]->GetPtr() == HwndControl)
				{
					 Handle = m_List[i]->OnCommand(wParam, lParam, lResult);
					 break;
				}
			}*/

			C32ContainerCallOnXyz(HwndControl, OnCommand);

		}
		return Handle;
	}
	
	virtual BOOL OnCommandMenu(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		lResult = 0;
		return FALSE;
	}

	virtual BOOL OnCommandAccelerator(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		lResult = 0;
		return FALSE;
	}

	virtual BOOL OnCommandControl(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		lResult = 0;
		return FALSE;
	}

	virtual BOOL CALLBACK OnNotify(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		HWND HwndControl = (HWND)lParam;
		for(size_t i = 0; i < m_List.size(); i++)
		{
			if (m_List[i]->GetPtr() == HwndControl)
			{
				Handle = m_List[i]->OnNotify(wParam, lParam, lResult);
				break;
			}
		}

		return Handle;
	}

	virtual BOOL CALLBACK OnSize(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		
		return FALSE;
	}

	virtual BOOL CALLBACK OnMove(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;

		return FALSE;
	}

	virtual BOOL CALLBACK OnWindowPosChanged(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		lResult = 1;
		SetReturnValue(0);
		LPWINDOWPOS lpwpos = (LPWINDOWPOS)lParam;
		ZxDebug((__FUNCTION__"():: LPWINDOWPOS {%d %d %d %d} 0x%08x (hwnd:%p : after:%p)\n", lpwpos->x, lpwpos->y, lpwpos->cx, lpwpos->cy, lpwpos->flags, lpwpos->hwnd, lpwpos->hwndInsertAfter));
		
		return FALSE;
	}

	virtual BOOL CALLBACK OnNcCalcSize(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		LPNCCALCSIZE_PARAMS lpncp = NULL;
		BOOL Handle = FALSE;
		lResult = 1;
		
		if (wParam == TRUE)
		{
			
			lpncp = (LPNCCALCSIZE_PARAMS)lParam;
		}


		return Handle;
	}
	
	virtual BOOL CALLBACK OnNcPaint(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		lResult = 1;
		SetReturnValue(0);
		
		return FALSE;
	}

};

//class C32Explorer
//{
//public:
//
//	static HINSTANCE hInstance;
//
//	static LRESULT CALLBACK C32WindowsProcessExporer(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
//	{
//		C32Explorer* This = GetThisClass(hWnd);
//		LRESULT lResult = 0;
//		BOOL    Handle = FALSE;
//		char* sMsg = UiDebugGetWindowMessageString(uMsg);
//		//ZxDebug(("ProcessExporers Msg: %s (%04X) \n", sMsg, uMsg));
//		switch (uMsg)
//		{
//		case WM_CREATE:
//			Handle = C32Explorer::OnCreate(hWnd, lParam, lResult);
//			break;
//		case WM_DESTROY:
//			PostQuitMessage(0);
//			return 0;
//		case WM_SIZE:
//			Handle = This->OnSize(wParam, lParam, lResult);
//			break;
//
//		case WM_PAINT:
//			{
//				PAINTSTRUCT ps;
//				HDC hdc = BeginPaint(hWnd, &ps);
//				EndPaint(hWnd, &ps);
//			}
//			break;
//		
//		case WM_CONTEXTMENU:
//			Handle = This->OnContextMenu(wParam, lParam, lResult);
//			break;
//		case WM_COMMAND:
//			 Handle = This->OnCommand(wParam, lParam, lResult);
//			 break;
//		case WM_NOTIFY:
//			Handle = This->OnNotify(wParam, lParam, lResult);
//			break;
//		case WM_LBUTTONDOWN: //Client Area 
//			SetCapture(hWnd);
//			break;
//		case WM_LBUTTONUP:   //Client Area
//			This->OnLButtonUP(wParam, lParam, lResult);
//			
//			break;
//		
//		}
//
//		if(Handle == FALSE)
//			lResult = DefWindowProc(hWnd, uMsg, wParam, lParam);
//
//		return lResult;
//	}
//
//	static DWORD RegisterClass()
//	{
//		WNDCLASSEX wcex = {};
//
//		wcex.cbSize = sizeof(WNDCLASSEX);
//
//		wcex.style			= CS_HREDRAW | CS_VREDRAW;
//		wcex.lpfnWndProc	= C32Explorer::C32WindowsProcessExporer;
//		wcex.cbClsExtra		= 0;
//		wcex.cbWndExtra		= 0;
//		wcex.hInstance		= C32Explorer::hInstance;
//		wcex.hIcon			= NULL;
//		//wcex.hbrBackground	= (HBRUSH)(COLOR_DESKTOP);
//		wcex.hbrBackground	= (HBRUSH)(GetStockBrush(LTGRAY_BRUSH));
//		wcex.hCursor		= (HCURSOR)LoadImage(NULL, MAKEINTRESOURCE(OCR_SIZEWE), IMAGE_CURSOR, 0 , 0, LR_SHARED);
//		wcex.lpszMenuName	= NULL;
//		wcex.lpszClassName	= C32_WC_EXPLORER;
//		wcex.hIconSm		= NULL;
//
//		ATOM Atom = RegisterClassEx(&wcex);
//		return Atom;
//	}
//
//	static C32Explorer* GetThisClass(HWND Hwnd)
//	{
//		C32Explorer* Explorer = (C32Explorer*)GetWindowLongPtr(Hwnd, GWL_USERDATA);
//
//		return Explorer;
//	}
//
//	static BOOL OnCreate(HWND hWnd, LPARAM lParam, LRESULT& lResult)
//	{
//		BOOL Handle = TRUE;
//		C32SetHandleLReslut(TRUE, 0);
//
//		LPCREATESTRUCT Cs = (LPCREATESTRUCT)lParam;
//
//		C32Explorer* This = (C32Explorer*)Cs->lpCreateParams;
//		Handle = This->OnCreate(Cs, hWnd);
//
//		return Handle;
//	}
//
//	static VOID Initialize()
//	{
//		//注册C32Explore类
//		RegisterClass();
//
//	}
//
//public:
//	C32Explorer(){}
//	~C32Explorer(){};
//
//	
//public:
//	virtual BOOL CreateExplorer(RECT& TreeRt, RECT& ListRt)
//	{
//		
//		CreateTreeCtl(TreeRt);
//		CreateListCtl(ListRt);
//		CreateStatusCtl();
//		return NULL;
//	}
//
//	virtual BOOL CreateTreeCtl(RECT& TreeRt)
//	{
//		DWORD Style = WS_CHILD | WS_VISIBLE;
//		Style |= TVS_LINESATROOT  | TVS_HASBUTTONS | TVS_FULLROWSELECT|TVS_DISABLEDRAGDROP;
//		Style |= TVS_TRACKSELECT ;
//		m_Tree.Create(0, Style,
//			TreeRt.left, TreeRt.top, GetRectWidth(TreeRt), GetRectHeigth(TreeRt), 
//			(HWND)m_Wnd);
//
//		m_Tree.SetSubclass();
//		m_Tree.SetExplorerTheme();
//		m_Tree.m_ImageListNormal.CreateNormal();
//		m_Tree.m_ImageListState.CreateNormal();
//
//		return TRUE;
//	}
//
//	virtual BOOL CreateListCtl(RECT& Rt)
//	{
//		DWORD Style = WS_CHILD | WS_VISIBLE;
//		 Style |=   LVS_REPORT ;
//		m_List.Create(0, Style,
//			Rt.left, Rt.top, GetRectWidth(Rt), GetRectHeigth(Rt), 
//			(HWND)m_Wnd);
//		m_List.GetListHeader();
//		m_List.SetSubclass();
//		m_List.SetExplorerTheme();
//
//		//m_Tree.SetExtendedStyles();
//		return TRUE;
//	}
//
//	virtual BOOL CreateStatusCtl()
//	{
//		DWORD Style3 = WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP | SBARS_TOOLTIPS ;
//		m_Status.CreateStatus(0, Style3, (HWND)m_Wnd);
//		m_Status.m_Wnd.SetPos();
//		return TRUE;
//	}
//	
//	virtual HWND CreateExplorer(HWND Parent, int X, int Y, int Cx, int Cy)
//	{
//		m_Parent = Parent;
//		
//		DWORD ExStyle = 0;
//		DWORD Style =  WS_CHILD | WS_VISIBLE;
//		HWND hwnd = CreateWindowEx(ExStyle, C32_WC_EXPLORER, L"C32Explorer", Style,
//						X, Y, Cx, Cy,
//						Parent, (HMENU)NULL, hInstance, (LPVOID)this);
//
//		SetWindowLongPtr(m_Wnd, GWL_USERDATA, (LONG_PTR)this);
//		DWORD Error = GetLastError();
//		m_Wnd = hwnd;
//		return hwnd;
//	}
//
//public:
//	virtual LONG_PTR SetWindowContext()
//	{
//		return SetWindowLongPtr(m_Wnd.GetPtr(), GWL_USERDATA, (LONG_PTR)this);
//	}
//	
//public:
//	virtual BOOL OnCreate(LPCREATESTRUCT Cs, HWND hWnd)
//	{
//		m_Wnd = hWnd;
//		RECT RcTree = {0, 0, m_Tree.m_Cx, Cs->cy};
//		RECT RcList = {m_Tree.m_Cx, 0, Cs->cx - m_Tree.m_Cx, Cs->cy};
//		SetWindowContext();
//
//		CreateTreeCtl(RcTree);
//		CreateListCtl(RcList);
//		CreateStatusCtl();
//
//		
//		return TRUE;
//		
//	}
//
//	virtual BOOL OnSize(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
//	{
//		BOOL Handle;
//		C32SetHandleLReslut(TRUE, 0);
//
//		if(IsIconic(m_Wnd)) // 最小化
//			return Handle;
//
//		DWORD Type = (DWORD)wParam;
//		int Cx = GET_X_LPARAM(lParam);
//		int Cy = GET_Y_LPARAM(lParam);
//		// m_Wnd.SetPos(0, 0, Cx, Cy);
//		//// 树和列表分割先10
//		// m_Tree.m_Wnd.SetPos(0,0,m_Tree.m_Wnd.m_Cx, Cy - m_Status.m_Wnd.m_Cy);
//		// m_Tree.m_Wnd.SetPos();
//
//		// m_List.m_Wnd.SetPos(m_Tree.m_Wnd.m_Cx+10,0,Cx - m_Tree.m_Wnd.m_Cx-10, Cy - m_Status.m_Wnd.m_Cy);
//		// m_List.m_Wnd.SetPos();
//		// 
//		// m_Status.m_Wnd.SetPos(0,m_Tree.m_Wnd.m_Cy, Cx, m_Status.m_Wnd.m_Cy);
//		// m_Status.m_Wnd.SetPos();
//		
//		//InvalidateRect(m_Wnd,NULL, TRUE);
//		//RedrawWindow(m_Wnd, )
//		HDWP hdwp = BeginDeferWindowPos(3);
//		 m_Wnd.SetPos(0, 0, Cx, Cy);
//		 
//		 DeferWindowPos(hdwp, m_Tree.m_Hwnd, NULL,0,0,m_Tree.m_Cx, Cy - m_Status.m_Wnd.m_Cy, SWP_NOZORDER);
//		 DeferWindowPos(hdwp, m_List.m_Wnd, NULL,m_Tree.m_Cx+10,0,Cx - m_Tree.m_Cx-10, Cy - m_Status.m_Wnd.m_Cy, SWP_NOZORDER);
//		 DeferWindowPos(hdwp, m_Status.m_Wnd, NULL,0,Cy-m_Status.m_Wnd.m_Cy, Cx, m_Status.m_Wnd.m_Cy, SWP_NOZORDER);
//		 EndDeferWindowPos(hdwp);
//		  m_List.m_Wnd.SetPos();
//		  m_Status.m_Wnd.SetPos();
//
//		  m_Wnd.SetPos();
//		  m_Tree.SetPos();
//
//		  return Handle;
//	}
//
//	virtual BOOL OnLButtonUP(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
//	{
//		BOOL Handle;
//		C32SetHandleLReslut(TRUE, 0);
//
//		DWORD Type = (DWORD)wParam;
//		int xCursor = GET_X_LPARAM(lParam);
//		int yCursor = GET_Y_LPARAM(lParam);
//		m_Tree.m_Cx = xCursor;
//		
//		SendMessage((HWND)m_Wnd, WM_SIZE, (WPARAM)-1, (LPARAM)MAKELPARAM(m_Wnd.m_ClientCx, m_Wnd.m_ClientCy));
//		ReleaseCapture();
//
//		return Handle;
//	}
//
//	virtual BOOL CALLBACK OnContextMenu(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
//	{
//		BOOL Handle;
//		C32SetHandleLReslut(TRUE, 0);
//
//		HWND hwnd = (HWND)wParam;
//		if(hwnd == (HWND)m_List)
//		{
//			m_List.OnContextMenu((HWND)wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
//		
//		}else if(hwnd== (HWND)m_Tree)
//		{
//			m_Tree.OnContextMenu((HWND)wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
//		}
//
//		return Handle;
//	}
//
//	virtual BOOL CALLBACK OnCommand(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
//	{
//		BOOL Handle;
//		C32SetHandleLReslut(TRUE, 0);
//		HWND Hwnd = (HWND)lParam;
//		if (m_Wnd == m_List.GetWindow())
//		{
//			m_List.OnCommand(wParam, lParam,lResult);
//		}else
//		{
//			m_Tree.OnCommand(wParam, lParam,lResult);
//		}
//
//		return Handle;
//	}
//
//	virtual BOOL CALLBACK OnNotify(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
//	{
//		BOOL Handle = FALSE;
//		C32SetHandleLReslut(TRUE, 0);
//
//		LPNMHDR NmHdr = (LPNMHDR)lParam;
//
//		
//
//		if(NmHdr->hwndFrom == (HWND)m_List)
//		{
//			m_List.OnNotify(wParam, lParam, lResult);	
//		}else if((NmHdr->hwndFrom == (HWND)m_Tree))
//		{
//			m_Tree.OnNotify(wParam, lParam, lResult);
//			
//		}else if(NmHdr->hwndFrom == (HWND)m_List.m_Header)
//		{
//			
//			m_List.m_Header.OnNotify(wParam, lParam, lResult);
//			
//		}
//
//
//
//		return Handle;
//	}
//	
//
//
//public:
//	int m_CxMin; 
//
//public:
//	C32TreeView m_Tree;
//	C32ListView m_List;
//	C32StatusBar m_Status;
//	HWND m_Parent;
//	C32Window m_Wnd;
//};


class C32Explorer : public C32Window
{
public:

	static HINSTANCE hInstance;

	static LRESULT CALLBACK C32WindowsProcessExporer(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		C32Explorer* This = GetThisClass(hWnd);
		LRESULT lResult = 0;
		BOOL    Handle = FALSE;
		char* sMsg = UiDebugGetWindowMessageString(uMsg);
		//ZxDebug(("ProcessExporers Msg: %s (%04X) \n", sMsg, uMsg));
		switch (uMsg)
		{
		case WM_CREATE:
			Handle = C32Explorer::OnCreate(hWnd, lParam, lResult);
			break;
		case WM_DESTROY:
			Handle = This->OnDestroy();
			return 0;
		case WM_SIZE:
			Handle = This->OnSize(wParam, lParam, lResult);
			break;

		case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hWnd, &ps);
				EndPaint(hWnd, &ps);
			}
			break;

		case WM_CONTEXTMENU:
			Handle = This->OnContextMenu(wParam, lParam, lResult);
			break;
		case WM_COMMAND:
			Handle = This->OnCommand(wParam, lParam, lResult);
			break;
		case WM_NOTIFY:
			Handle = This->OnNotify(wParam, lParam, lResult);
			break;
		case WM_LBUTTONDOWN: //Client Area 
			SetCapture(hWnd);
			break;
		case WM_LBUTTONUP:   //Client Area
			This->OnLButtonUP(wParam, lParam, lResult);

			break;

		}

		if(Handle == FALSE)
			lResult = DefWindowProc(hWnd, uMsg, wParam, lParam);

		return lResult;
	}

	static DWORD RegisterClass()
	{
		WNDCLASSEX wcex = {};

		wcex.cbSize = sizeof(WNDCLASSEX);

		wcex.style			= CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc	= C32Explorer::C32WindowsProcessExporer;
		wcex.cbClsExtra		= 0;
		wcex.cbWndExtra		= 0;
		wcex.hInstance		= C32Explorer::hInstance;
		wcex.hIcon			= NULL;
		//wcex.hbrBackground	= (HBRUSH)(COLOR_DESKTOP);
		wcex.hbrBackground	= (HBRUSH)(GetStockBrush(LTGRAY_BRUSH));
		wcex.hCursor		= (HCURSOR)LoadImage(NULL, MAKEINTRESOURCE(OCR_SIZEWE), IMAGE_CURSOR, 0 , 0, LR_SHARED);
		wcex.lpszMenuName	= NULL;
		wcex.lpszClassName	= C32_WC_EXPLORER;
		wcex.hIconSm		= NULL;

		ATOM Atom = RegisterClassEx(&wcex);
		return Atom;
	}

	static C32Explorer* GetThisClass(HWND Hwnd)
	{
		C32Explorer* Explorer = (C32Explorer*)GetWindowLongPtr(Hwnd, GWL_USERDATA);

		return Explorer;
	}

	static BOOL OnCreate(HWND hWnd, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = TRUE;
		C32SetHandleLReslut(TRUE, 0);

		LPCREATESTRUCT Cs = (LPCREATESTRUCT)lParam;

		C32Explorer* This = (C32Explorer*)Cs->lpCreateParams;
		Handle = This->OnCreate(Cs, hWnd);

		return Handle;
	}

	static VOID Initialize()
	{
		//注册C32Explore类
		RegisterClass();

	}

public:
	C32Explorer(){}
	~C32Explorer(){};


public:
	virtual BOOL CreateExplorer(RECT& TreeRt, RECT& ListRt)
	{

		CreateTreeCtl(TreeRt);
		CreateListCtl(ListRt);
		CreateStatusCtl();
		return NULL;
	}

	virtual BOOL CreateTreeCtl(RECT& TreeRt)
	{
		DWORD Style = WS_CHILD | WS_VISIBLE;
		Style |= TVS_LINESATROOT  | TVS_HASBUTTONS | TVS_FULLROWSELECT|TVS_DISABLEDRAGDROP;
		Style |= TVS_TRACKSELECT ;
		m_Tree.Create(0, Style,
			TreeRt.left, TreeRt.top, GetRectWidth(TreeRt), GetRectHeigth(TreeRt), 
			(HWND)m_Hwnd);

		m_Tree.SetSubclass();
		m_Tree.SetExplorerTheme();
		m_Tree.m_ImageListNormal.CreateNormal();
		m_Tree.m_ImageListState.CreateNormal();

		return TRUE;
	}

	virtual BOOL CreateListCtl(RECT& Rt)
	{
		DWORD Style = WS_CHILD | WS_VISIBLE;
		Style |=   LVS_REPORT ;
		m_List.Create(0, Style,
			Rt.left, Rt.top, GetRectWidth(Rt), GetRectHeigth(Rt), 
			(HWND)m_Hwnd);
		m_List.GetListHeader();
		m_List.SetSubclass();
		m_List.SetExplorerTheme();

		//m_Tree.SetExtendedStyles();
		return TRUE;
	}

	virtual BOOL CreateStatusCtl()
	{
		DWORD Style3 = WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP | SBARS_TOOLTIPS ;
		m_Status.CreateStatus(0, Style3, (HWND)m_Hwnd);
		m_Status.SetPos();
		return TRUE;
	}

	virtual HWND CreateExplorer(HWND Parent, int X, int Y, int Cx, int Cy)
	{
		m_Parent = Parent;

		DWORD ExStyle = 0;
		DWORD Style =  WS_CHILD | WS_VISIBLE;
		HWND hwnd = CreateWindowEx(ExStyle, C32_WC_EXPLORER, L"C32Explorer", Style,
			X, Y, Cx, Cy,
			Parent, (HMENU)NULL, hInstance, (LPVOID)this);

		DWORD Error = GetLastError();
		m_Hwnd = hwnd;
		SetWindowLongPtr(m_Hwnd, GWL_USERDATA, (LONG_PTR)this);
		return hwnd;
	}

public:
	virtual LONG_PTR SetWindowContext()
	{
		return SetWindowLongPtr(m_Hwnd, GWL_USERDATA, (LONG_PTR)this);
	}

public:
	virtual BOOL OnCreate(LPCREATESTRUCT Cs, HWND hWnd)
	{
		m_Hwnd = hWnd;
		RECT RcTree = {0, 0, m_Tree.m_Cx, Cs->cy};
		RECT RcList = {m_Tree.m_Cx, 0, Cs->cx - m_Tree.m_Cx, Cs->cy};
		SetWindowContext();

		CreateTreeCtl(RcTree);
		CreateListCtl(RcList);
		CreateStatusCtl();


		return TRUE;

	}

	virtual BOOL OnDestroy()
	{
		
		
		return TRUE;
	}


	virtual BOOL OnSize(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle;
		C32SetHandleLReslut(TRUE, 0);

		if(IsIconic(m_Hwnd)) // 最小化
			return Handle;

		DWORD Type = (DWORD)wParam;
		int Cx = GET_X_LPARAM(lParam);
		int Cy = GET_Y_LPARAM(lParam);
		// m_Hwnd.SetPos(0, 0, Cx, Cy);
		//// 树和列表分割先10
		// m_Tree.m_Hwnd.SetPos(0,0,m_Tree.m_Hwnd.m_Cx, Cy - m_Status.m_Hwnd.m_Cy);
		// m_Tree.m_Hwnd.SetPos();

		// m_List.m_Hwnd.SetPos(m_Tree.m_Hwnd.m_Cx+10,0,Cx - m_Tree.m_Hwnd.m_Cx-10, Cy - m_Status.m_Hwnd.m_Cy);
		// m_List.m_Hwnd.SetPos();
		// 
		// m_Status.m_Hwnd.SetPos(0,m_Tree.m_Hwnd.m_Cy, Cx, m_Status.m_Hwnd.m_Cy);
		// m_Status.m_Hwnd.SetPos();

		//InvalidateRect(m_Hwnd,NULL, TRUE);
		//RedrawWindow(m_Hwnd, )
		HDWP hdwp = BeginDeferWindowPos(3);
		SetPos(0, 0, Cx, Cy);

		DeferWindowPos(hdwp, m_Tree, NULL,0,0,m_Tree.m_Cx, Cy - m_Status.m_Cy, SWP_NOZORDER);
		DeferWindowPos(hdwp, m_List, NULL,m_Tree.m_Cx+10,0,Cx - m_Tree.m_Cx-10, Cy - m_Status.m_Cy, SWP_NOZORDER);
		DeferWindowPos(hdwp, m_Status, NULL,0,Cy-m_Status.m_Cy, Cx, m_Status.m_Cy, SWP_NOZORDER);
		EndDeferWindowPos(hdwp);
		m_List.m_Wnd.SetPos();
		m_Status.SetPos();

		SetPos();
		m_Tree.SetPos();

		return Handle;
	}

	virtual BOOL OnLButtonUP(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle;
		C32SetHandleLReslut(TRUE, 0);

		DWORD Type = (DWORD)wParam;
		int xCursor = GET_X_LPARAM(lParam);
		int yCursor = GET_Y_LPARAM(lParam);
		m_Tree.m_Cx = xCursor;

		SendMessage((HWND)m_Hwnd, WM_SIZE, (WPARAM)-1, (LPARAM)MAKELPARAM(m_ClientCx, m_ClientCy));
		ReleaseCapture();

		return Handle;
	}

	virtual BOOL CALLBACK OnContextMenu(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle;
		C32SetHandleLReslut(TRUE, 0);

		HWND hwnd = (HWND)wParam;
		if(hwnd == (HWND)m_List)
		{
			m_List.OnContextMenu((HWND)wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));

		}else if(hwnd== (HWND)m_Tree)
		{
			m_Tree.OnContextMenu((HWND)wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		}

		return Handle;
	}

	virtual BOOL CALLBACK OnCommand(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle;
		C32SetHandleLReslut(TRUE, 0);
		HWND Hwnd = (HWND)lParam;
		if (Hwnd == m_List.GetWindow())
		{
			m_List.OnCommand(wParam, lParam,lResult);
		}else
		{
			m_Tree.OnCommand(wParam, lParam,lResult);
		}

		return Handle;
	}

	virtual BOOL CALLBACK OnNotify(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		C32SetHandleLReslut(TRUE, 0);

		LPNMHDR NmHdr = (LPNMHDR)lParam;



		if(NmHdr->hwndFrom == (HWND)m_List)
		{
			m_List.OnNotify(wParam, lParam, lResult);	
		}else if((NmHdr->hwndFrom == (HWND)m_Tree))
		{
			m_Tree.OnNotify(wParam, lParam, lResult);

		}else if(NmHdr->hwndFrom == (HWND)m_List.m_Header)
		{

			m_List.m_Header.OnNotify(wParam, lParam, lResult);

		}



		return Handle;
	}



public:
	int m_CxMin; 

public:
	C32TreeView m_Tree;
	C32ListView m_List;
	C32StatusBar m_Status;
	HWND m_Parent;

};



class C32Progress : public C32Window
{
static HINSTANCE hInstance;
public:
	C32Progress()
	{
		m_Range.iLow = 0;
		m_Range.iHigh = 100;
		m_Step = 1;
	}
	HWND Create(HWND Parent, 
				int X, int Y, int Cx, int Cy,
				DWORD dwStyle = PBS_MARQUEE)
	{
		dwStyle |= WS_CHILDWINDOW | WS_VISIBLE;

		HWND Hwnd = CreateWindowEx(0, PROGRESS_CLASS, L"C32ProgressBar", dwStyle, 
						X, Y, Cx, Cy,
						Parent,
						(HMENU)NULL,
						hInstance, this);
		m_Hwnd = Hwnd;
		C32GetLastError();
		return Hwnd;
	}


	

	int SetStatus(int iStatus)
	{
		return (int)SendMessage(m_Hwnd,PBM_SETSTATE,(WPARAM)iStatus,0);
	}

	int SetRange(int iLow, int iHigh)
	{
		m_Range.iLow = iLow;
		m_Range.iHigh = iHigh;

		return (int)SendMessage(m_Hwnd, PBM_SETRANGE, 0, MAKELPARAM(iLow, iHigh));
	}

	int SetPos(int iPos)
	{
		if (iPos < m_Range.iLow)
			iPos = m_Range.iHigh;
		else if(iPos > m_Range.iHigh)
			iPos = m_Range.iHigh;

		m_Pos = iPos;

	 return (int)SendMessage(m_Hwnd, PBM_SETPOS, (WPARAM)iPos, NULL);
	}

	int SetStep(int iStep)
	{
		m_Step = iStep;
		
		return (int)SendMessage(m_Hwnd, PBM_SETSTEP, (WPARAM)iStep, 0);
	}

	int NextStep()
	{
		return (int)SendMessage(m_Hwnd, PBM_STEPIT, 0, 0);
	}
	
	DWORD SetStyle(DWORD Style = PBS_SMOOTH)
	{
		//Style = ;
		return (DWORD)SetWindowLong(m_Hwnd, GWL_STYLE, Style);
	}

	VOID SetMarqueem()
	{
		SendMessage(m_Hwnd, PBM_SETMARQUEE, TRUE, 30);
	}

public:
	int      m_Pos;
	int	     m_Step;
	PBRANGE  m_Range;
	

	
};

class C32DialogProgress : public C32Window
{
public:
	static HINSTANCE hInstance;
	static INT_PTR WINAPI C32DialogProgressProc(HWND hDialog, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		INT_PTR Ret = 0;
		C32DialogProgress* This = (C32DialogProgress*)GetWindowLongPtr(hDialog, GWLP_USERDATA);
		if (This == NULL)
			This = (C32DialogProgress*)lParam;
		switch(uMsg)
		{
		case WM_INITDIALOG:
			SetWindowLongPtr(hDialog, GWLP_USERDATA, (LONG_PTR)lParam);
			This->Init(hDialog);
			break;
		case WM_COMMAND:
			 switch(LOWORD(wParam))
			 {
				case IDOK:
					This->OnClickOk();
					break;
				case IDCANCEL:
					This->OnClickCancel();
					EndDialog(hDialog, 0);
					break;
			 }
			 break;

		case WM_DESTROY:
			{
				SetWindowLongPtr(hDialog, GWLP_USERDATA, (LONG_PTR)NULL);
				EndDialog(hDialog, 0);
			}
			break;
		default:
			Ret = DefWindowProc(hDialog, uMsg, wParam, lParam);
			break;
		}

		return Ret;
	}

	C32DialogProgress()
	{
		InitText();
	}

	C32DialogProgress(DWORD dwProgressStyle)
	{
		//SetCtrlText();
		InitText();
	}

	C32DialogProgress(LPCWSTR DialogText, 
						LPCWSTR OKText = L"暂停", 
						LPCWSTR CancelText = L"停止")
	{
		InitText();
		SetCtrlText(DialogText, OKText, CancelText);
	}

	~C32DialogProgress()
	{

	}
public:
	
	VOID Create(HWND Parent)
	{
		m_Parent = Parent;
		DialogBoxParam(hInstance, 
			MAKEINTRESOURCE(IDD_DIALOG_C32CLASS_PROGRESS), 
			Parent,
			C32DialogProgress::C32DialogProgressProc, 
			(LPARAM)this);
	}

	virtual VOID Init(HWND hDialog)
	{
		m_Hwnd = hDialog;

		HWND Ok = GetDlgItem(hDialog, IDOK);
		HWND Cancel = GetDlgItem(hDialog, IDCANCEL);
		HWND Progress = GetDlgItem(hDialog, IDC_PROGRESS);

		m_ProBar.SetHwnd(Progress);
		m_ProBar.SetStyle(PBS_MARQUEE| WS_CHILD|WS_VISIBLE);
		m_ProBar.SetMarqueem();
		m_Ok.SetHwnd(Ok);
		m_Cancel.SetHwnd(Cancel);
		if (m_OkText)
			m_Ok.SetText(m_OkText);
		if (m_CancelText)
			m_Cancel.SetText(m_CancelText);

		SetCenterPos(this->m_Parent);
	}
	
	VOID SetCtrlText(LPCWSTR DialogText = L"进度展示", 
		LPCWSTR OKText = L"暂停", 
		LPCWSTR CancelText = L"停止")
	{
		m_Title = DialogText;
		m_OkText = OKText;
		m_CancelText = CancelText;

	}

	VOID InitText()
	{
		m_OkText = NULL;
		m_CancelText = NULL;
		m_Title = NULL;
	}

public:
	virtual BOOL OnClickOk()
	{
		ZxDebug((__FUNCTION__"():: \n"));
		return TRUE;
	}

	virtual BOOL OnClickCancel()
	{
		return TRUE;
	}

	C32Progress m_ProBar;
	C32Button m_Ok;
	C32Button m_Cancel;

	LPCWSTR   m_OkText;
	LPCWSTR   m_CancelText;

	LPCWSTR   m_Title;

};

class C32DialogSearch : public C32Dialog
{

public:
	C32DialogSearch()
	{
		m_DbgOnSizeCount = 0;
	}
	~C32DialogSearch()
	{

	}

public:
	
	 virtual BOOL CALLBACK OnInitDialog(HWND hwndDlg, UINT uMsg, WPARAM  FocusHwnd, LPARAM InitParam, LRESULT& lResult)
	{
		//C32Dialog::OnInitDialog(hwndDlg, uMsg, DefautFocusHwnd,InitParam, lResult);
		SetWindowLongPtr(hwndDlg, GWL_USERDATA, (LONG_PTR)InitParam);
		Attach(hwndDlg);
		HWND hwndCombo = GetDlgItem(hwndDlg, IDC_DIALOG_SEARCH_COMBO);
		HWND hwndEdit = GetDlgItem(hwndDlg, IDC_DIALOG_SEARCH_EDIT);
		HWND hwndButton = GetDlgItem(hwndDlg, IDC_DIALOG_SEARCH_BUTTON);
		HWND hwndGroup = GetDlgItem(hwndDlg, IDC_DIALOG_SEARCH_GROUP);

		HWND hwndList = GetDlgItem(hwndDlg, IDC_DIALOG_SEARCH_LIST);
		
		m_ComboBox.Attach(hwndCombo);
		m_Edit.Attach(hwndEdit);
		m_Button.Attach(hwndButton);
		m_Group.Attach(hwndGroup);
		m_LV.Attach(hwndList);


		m_ComboBox.SetItemHeight(38);
		m_Button.SetClickEvent(OnSearchClick);
		
		m_List.push_back(&m_ComboBox);
		m_List.push_back(&m_Edit);
		m_List.push_back(&m_Button);
		m_List.push_back(&m_LV);

		SetText(L"C32查找对话框");
		SetPos();
		SetMinCxy(m_ClientCx, m_ClientCy);
		InitComboBox();
		SetCenterPos(GetParent(m_Hwnd));
		return TRUE;
	}
	 
	 virtual BOOL InitComboBox()
	 {
		m_ComboBox.Add(L"123");
		m_ComboBox.Add(L"456");	
		m_ComboBox.Add(L"789");	
		
		m_ComboBox.SelectItem(0);

		return TRUE;
	 } 

public: // WindowsMessage

	static BOOL WINAPI OnSearchClick(DWORD CtrlId, LRESULT& lResult, C32Window* This)
	{
		ZxDebug((__FUNCTION__"():: \n"));
		return TRUE;
	}
	
	virtual BOOL CALLBACK OnSize(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
	
		int Cx = GET_X_LPARAM(lParam);
		int Cy = GET_Y_LPARAM(lParam);
		if (Cx <= m_MinCx && Cy <= m_MinCy)
			return FALSE;
		m_ComboBox.SetPos();
		m_Group.SetPos();
		
		m_Button.SetPos();
		m_Edit.SetPos();
		m_LV.SetPos();
		SetPos();
		
		RECT GroupRc = ConvertToClientRect(m_Group.m_Rect);
		m_Group.SetPos(0, 0, Cx - GroupRc.left*2 , m_Group.m_Cy, SWP_NOZORDER | SWP_NOMOVE);
		 GroupRc = ConvertToClientRect(m_Group.m_Rect);
		// combo box 不变
		m_ComboBox.SetPos(0, 0, 0,0, SWP_NOZORDER | SWP_NOMOVE| SWP_NOSIZE);
		RECT CommboRc = ConvertToClientRect(m_ComboBox.m_Rect);

		RECT ButtonRc = ConvertToClientRect(m_Button.m_Rect);
		
		int BtnX = m_ClientRect.right - GetRectWidth(ButtonRc) -  GroupRc.left - 10;

		m_Button.SetPos(BtnX, ButtonRc.top, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		ButtonRc = ConvertToClientRect(m_Button.m_Rect);

		RECT EditRc = ConvertToClientRect(m_Edit.m_Rect);
		int EditCx = BtnX - EditRc.left -20 ;
		m_Edit.SetPos(0, 0,  EditCx, m_Edit.m_Cy, SWP_NOZORDER | SWP_NOMOVE);

		RECT LvRc = ConvertToClientRect(m_LV.m_Rect);
		
		m_LV.SetPos(0, 0,  m_Group.m_Cx, Cy - LvRc.top-80, SWP_NOZORDER | SWP_NOMOVE);


		return TRUE;
	}

	virtual BOOL CALLBACK OnMove(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		int xPos = GET_X_LPARAM(lParam);
		int yPos = GET_Y_LPARAM(lParam);
		/*if (Cx <= m_MinCx && Cy <= m_MinCy)
			return TRUE;*/
		m_ComboBox.SetPos();
		

		return TRUE;
	}

	virtual BOOL CALLBACK OnNcCalcSize(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		LPNCCALCSIZE_PARAMS lpncp = NULL;
		BOOL Handle = FALSE;
		lResult = 1;
		SetReturnValue(0);
		if (wParam == TRUE)
		{
			lpncp = (LPNCCALCSIZE_PARAMS)lParam;
			SetReturnValue(WVR_VALIDRECTS);
			
		}
		
		
		return FALSE;
	}


public:
	C32ComboBox m_ComboBox;
	C32Edit		m_Edit;
	C32Button   m_Button;
	C32ListView m_LV;
	C32Group    m_Group;

	int         m_DbgOnSizeCount;

};

VOID C32DrawControlTest(HWND hwnd, HDC hDc);


VOID C32ListBoxTest(HWND Parent);

VOID C32DialogSearchTest();

VOID C32ExplorerTest(HWND hWnd, C32Explorer* Explorer = NULL);


VOID C32DialogProgressTest(HWND hWnd, HINSTANCE hInstance);


VOID InitializeC32Control(HINSTANCE hInstance);

extern HINSTANCE C32Hinstance;
extern HWND      C32Hwnd;