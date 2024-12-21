#pragma once
#include "stdafx.h"
#include "C32DebugMsg.h"
#include "C32Helper.h"
#include "resource.h"
#include "Resource1.h"
#include <vector>
#include <algorithm>
#include <atlstr.h>
#include <atlconv.h>
#include<assert.h>

/*
	使用C32Lib，如果需要处理事件，只需要关注C32ControlEventCallback
*/


#define C32GetRectWidth(rc) (rc.right -rc.left) 
#define C32GetRectHeight(rc) (rc.bottom -rc.top) 

#define RtlZeroStringW(Ptr, Count) RtlZeroMemory(Ptr, Count*2)

#define C32_WC_EXPLORER L"C32Explorer"
#define C32_WC_CONTAINTER L"C32Container"

#define C32MessageBox(Title, Caption) MessageBox(NULL,Caption, Title, MB_OK)

#define C32MessageBoxTip(Caption) MessageBox(NULL,Caption, L"提示", MB_OK)


#define C32MessageBoxSuccess(x) x ? MessageBox(NULL,  L"操作成功", L"提示", MB_OK) : MessageBox(NULL,  L"操作失败", L"提示", MB_OK)


#define C32GetLastError() m_Error = GetLastError()
#define C32GetUserData(hwnd)  (LONG_PTR)GetWindowLongPtr(hwnd, GWLP_USERDATA)
#define C32GetUserClass(hwnd)  (C32Window*)C32GetUserData(hwnd)

#define C32BoolToString(x) (x  ? "Yes" : "No")

							
#define C32EVENT_UNREFERENCED_PARAMETER()\
							{			\
								UNREFERENCED_PARAMETER(wParam);	\
								UNREFERENCED_PARAMETER(lParam);	\
								UNREFERENCED_PARAMETER(lResult);	\
							}

#define C32DBG_MESSAGE_BOX() MessageBox(NULL, NULL, NULL, MB_OK)

#define C32SetHandleLReslut(IsHandle, lResultValue) Handle = IsHandle, lResult = lResultValue

#define C32CommandIsMenu(wParam) (HIWORD(wParam) == 0)
#define C32CommandIsCtrl(wParam) (HIWORD(wParam) > 1)

#define C32CommandMenuId(wParam) LOWORD(wParam)
#define C32CommandCtrlNotifiyCode(wParam) HIWORD(wParam)
#define C32CommandCtrlId(wParam) LOWORD(wParam)

#define C32IsNull(x) (x == NULL) 
#define C32IsNonNull(x) (x != NULL) 		

#define C32CtrlDebug(x) ZxDebug(x)

			
#define C32SelectFontDefault(hdc) SelectFont(hdc,GetStockObject(DEFAULT_GUI_FONT));
 
class C32Window;
class C32ListView;
class C32TreeView;
class C32StatusBar;
class C32Button;
class C32Dialog;
class C32DialogSearch;
class C32Header;
class C32TabCtrl;
class C32ToolTip;
class C32Container;

typedef Gdiplus::Status  C32GdiStatus;
typedef Gdiplus::Pen  C32GdiPen;
typedef Gdiplus::Brush  C32GdiBrush;
typedef Gdiplus::Graphics  C32Graphics;

typedef Gdiplus::ImageAttributes C32ImageAttributes;
typedef Gdiplus::Matrix          C32Matrix;         
typedef Gdiplus::Brush           C32Brush;          
typedef Gdiplus::Pen             C32Pen;            
typedef Gdiplus::StringFormat    C32StringFormat;   
typedef Gdiplus::PathData        C32PathData;           
typedef Gdiplus::Graphics        C32Graphics;       
typedef Gdiplus::Metafile        C32Metafile;       
typedef Gdiplus::CachedBitmap    C32CachedBitmap;   
typedef Gdiplus::Region          C32Region;         
typedef Gdiplus::FontCollection  C32FontCollection; 
typedef Gdiplus::FontFamily      C32FontFamily;     
typedef Gdiplus::Font            C32Font;           
typedef Gdiplus::Bitmap          C32Bitmap; 
typedef Gdiplus::Color           C32Color;         


typedef BOOL (WINAPI* C32_ON_EVENT_CALLBACK)(WPARAM wParam, LPARAM lParam, LRESULT& lResult);
typedef BOOL  (WINAPI*C32_EVENT_CALLBACK)(WPARAM wParam, LPARAM lParam, LRESULT& lResult, C32Window* This);
typedef BOOL  (WINAPI*C32_EVENT_CALLBACK_COMMADN)(DWORD CtrlId, LRESULT& lResult, C32Window* This);

typedef BOOL  (WINAPI*C32_EVENT_CALLBACK_CONTEXTMENU)(HWND hwndClicked, int xPos, int yPos, LRESULT& lResult, C32Window* This);

typedef BOOL  (WINAPI*C32_EVENT_CALLBACK_COMMAND_MENU)(DWORD CtrlId, LRESULT& lResult, C32Window* This);

typedef BOOL  (WINAPI*C32_EVENT_CALLBACK_ONSIZE)(DWORD ResizeType, int Cx, int Cy, LRESULT& lResult, C32Window* This);


//Static Event
typedef BOOL  (WINAPI*C32_EVENT_CALLBACK_STATIC_CLICK)(DWORD CtrlId, C32Window* This);
typedef C32_EVENT_CALLBACK_STATIC_CLICK C32_EVENT_CALLBACK_STATIC_DCLICK;


typedef BOOL  (WINAPI*C32_EVENT_CALLBACK_BUTTON_CLICK)(DWORD CtrlId, C32Button* This);


// Button Event
typedef C32_EVENT_CALLBACK_BUTTON_CLICK C32_EVENT_CALLBACK_BUTTON_DCLICK;


//Header
typedef BOOL  (WINAPI*C32_EVENT_CALLBACK_HEADER)(WPARAM wParam, LPARAM lParam, LRESULT& lResult, C32Window* This);

typedef BOOL  (WINAPI*C32_EVENT_CALLBACK_HEADER_NOTIFY)(LPNMHEADER lpnmhdr, LRESULT& lResult, C32Header* This);


typedef BOOL  (WINAPI*C32_EVENT_CALLBACK_DIALOG_INIT)(C32Dialog* This);


//Tab Control
typedef BOOL  (WINAPI*C32_EVENT_CALLBACK_TAB_CTRL_NOTIFY_SELCHANGE)(int iSelectItem, LRESULT& lResult, C32TabCtrl* This);

//ToolTip Control
typedef BOOL (WINAPI*C32_EVENT_CALLBACK_TOOLTIP_CTRL_NOTIFY_GETDISPINFO)(ULONG_PTR idFrom, BOOL IsHwnd, __inout LPWSTR* lpszText, __out BOOL* isRetain,LRESULT& lResult, C32ToolTip* This);


//typedef C32_EVENT_CALLBACK_EX  C32_EVENT_CALLBACK_HEADER;


#define C32OnXyz(OnXyz)\
	virtual BOOL CALLBACK OnXyz(WPARAM wParam, LPARAM lParam, LRESULT& lResult)\
	{\
		C32EVENT_UNREFERENCED_PARAMETER();\
		return FALSE;\
	}

	//virtual BOOL CALLBACK OnNcDestroy(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	//{
	//	C32EVENT_UNREFERENCED_PARAMETER();
	//	//delete this;
	//	return FALSE;
	//}



#define C32_CALL_EVENT_CALLBACK(CallBackFunction)(CallBackFunction(wParam, lParam, lResult, this))


extern HINSTANCE C32Hinstance;
extern HWND      C32Hwnd;
extern C32Container* C32MainFrame;


/*
	释放 std::Vector<C32Window*> m_List
	DeletePtr:TRUE 调用 delete m_List[i]
*/
VOID  C32FreeWindowList(std::vector<C32Window*>& List, BOOL DeletePtr = FALSE);
 
/*
	创建默认的控件
	Windows Explorer Tree
	Windows Explorer List
*/
VOID C32CreateTree(C32TreeView& Tree, HWND hwndParent, int xPos = 0, int yPos = 0, int Cx = 0, int Cy = 0);

VOID C32CreateList(C32ListView& List, HWND hwndParent, int xPos = 0, int yPos = 0, int Cx = 0, int Cy = 0);

VOID C32CreateStatus(C32StatusBar& Status, HWND hwndParent);

class C32DrawText
{
public:
	C32DrawText()
	{

	}

	~C32DrawText()
	{

	}

	/*
		上下居中写写文字
	*/
	BOOL TextOutExt(__in HDC hdc,  __in UINT Options, RECT * Rect,  LPCWSTR String, int Count)
	{
		BOOL bRet = FALSE;
		TEXTMETRIC tm = {};
		int xPos; 
		int yPos;
		GetTextMetrics(hdc, &tm);
		xPos = Rect->left;
		yPos = (Rect->top + Rect->bottom - tm.tmHeight)/2;

		bRet = ExtTextOut(hdc, xPos, yPos, Options, Rect, String, Count, NULL);

		return !!bRet;
	}

};

/*
	利用系统风格画控件
	比直接调用DrawFrameControl
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
		Close();
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

	BOOL DrawControlSystemStyle(HDC hdc, int iCtrlPartId, int iCtrlStateId, RECT* Rect)
	{
		SIZE Size = {26,26};
		if (!GetPartSize(hdc, iCtrlPartId, iCtrlStateId, Size))
			return FALSE;

		RECT rcSysTyle = *Rect;
		rcSysTyle.left = Rect->left;
		rcSysTyle.right = rcSysTyle.left + Size.cx;
		rcSysTyle.top = (Rect->bottom + Rect->top - Size.cy)/2;
		rcSysTyle.bottom = rcSysTyle.top+Size.cy;
		
		if(DrawControl(hdc, iCtrlPartId, iCtrlStateId, &rcSysTyle) == FALSE)
			return FALSE;
		*Rect = rcSysTyle;
		return TRUE;
	}

	BOOL DrawCheckBoxImage(HDC hdc, int iStateId, RECT Rect)
	{
		HRESULT hrst;
		SIZE Size = {};

		hrst = GetThemePartSize(m_Theme, hdc, BP_CHECKBOX, iStateId, NULL,TS_DRAW, &Size);

		Rect.top += (C32GetRectHeight(Rect)/2 - Size.cy/2);
		Rect.right = Rect.left + Size.cx;
		Rect.bottom = Rect.top + Size.cy;

		return DrawControl(hdc, BP_CHECKBOX, iStateId, &Rect);
	}

	
	BOOL GetPartSize(HDC hdc, int iPartId, int iStateId, SIZE& Size)
	{
		Size.cx = Size.cy = 0;
		HRESULT hrst;
		hrst = GetThemePartSize(m_Theme, hdc, iPartId, iStateId, NULL,TS_TRUE, &Size);
		if (hrst == S_OK )
			return TRUE;

		return FALSE;
	}

	BOOL DrawCheckBox(HDC hdc, int iStateId, RECT Rect,LPCWSTR String)
	{
		BOOL  bRet = FALSE;

		SIZE Size = {26,26};
		if (!GetPartSize(hdc, BP_CHECKBOX, iStateId, Size))
			return FALSE;
	
		// 先写文字在画图片 why?
		if (String)
		{
			Rect.left += Size.cx + 5;
			C32DrawText Text;
			bRet = Text.TextOutExt(hdc, ETO_OPAQUE, &Rect, String, (int)wcslen(String));
			Rect.left -= (Size.cx + 5);
		}

		Rect.top += (C32GetRectHeight(Rect)/2 - Size.cy/2);
		Rect.right = Rect.left + Size.cx;
		Rect.bottom = Rect.top + Size.cy;
		if(DrawControl(hdc, BP_CHECKBOX, iStateId, &Rect) == FALSE)
			return FALSE;

		return bRet;
	}

#if 0
	BOOL DrawCheckBoxEx(HDC hDc, int iStateId, RECT Rect)
	{
		BOOL bDraw = FALSE;
		if(Open(WC_BUTTON))
		{
			bDraw= DrawCheckBox(hDc, iStateId, Rect);
			Close();
		}

		return bDraw;
	}

#endif
	
	BOOL DrawThemeText(HDC hdc, int iPartId, int iStateId, LPCWSTR pszText, int cchText, DWORD dwTextFlags, DWORD dwTextFlags2, LPCRECT pRect)
	{
		HRESULT hrst;
		hrst = ::DrawThemeText(m_Theme, hdc, iPartId, iStateId, pszText, cchText,dwTextFlags, dwTextFlags2, pRect);

		return (hrst == S_OK);
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


class C32GdiObject
{
public:
	static HFONT  m_SysGuiFont; //DEFAULT_GUI_FONT 
	static HFONT  m_SysFont;    //SYSTEM_FONT

public:
	static VOID Initialize()
	{
		m_SysGuiFont = GetStockFont(DEFAULT_GUI_FONT);
		m_SysFont = GetStockFont(SYSTEM_FONT);
	}

	VOID Uninitialize()
	{
		if (m_SysGuiFont)
		{
			DeleteObject(m_SysGuiFont);
			m_SysGuiFont = NULL;
		}

		if (m_SysFont)
		{
			DeleteObject(m_SysFont);
			m_SysFont = NULL;
		}
	}


public:
	C32GdiObject()
	{

	}

	~C32GdiObject()
	{

	}

	
};

/*
	封装 hdc .
*/
class C32DeviceContext
{
	
public:
	C32DeviceContext()
	{
		Init();
	}

	~C32DeviceContext()
	{
		if (m_Font)
		{
			SelectFont(m_Hdc, m_Font);
			m_Font = NULL;
		}

		if (m_OriginPen)
		{
			SelectPen(m_Hdc, m_OriginPen);
			m_OriginPen = NULL;
		}

		if (m_Brush)
		{
			SelectBrush(m_Hdc, m_Brush);
			m_Brush = NULL;
		}

		

	}

	C32DeviceContext(HDC hdc)
	{
		Init();
		m_Hdc = hdc;
	}

public:
	VOID SetHdc(HDC hdc)
	{
		m_Hdc = hdc;
	}

	// 选择Font 默认是 : DEFAULT_GUI_FONT
	VOID SelectFont32(HFONT hFont = NULL)
	{
		if (hFont == NULL)
		{
			m_Font = GetStockFont(DEFAULT_GUI_FONT);
			m_OriginFont = SelectFont(m_Hdc, m_Font);
		}else
		{
			m_OriginFont = SelectFont(m_Hdc, hFont);
		}
	}

	// 选择Font 默认是 : DEFAULT_GUI_FONT
	VOID SelectBrush32(HBRUSH hBrush)
	{
		m_OriginBrush = SelectBrush(m_Hdc, hBrush);	
	}



	VOID Init()
	{
		m_Pen	= NULL;
		m_Font	= NULL;
		m_Brush	= NULL;
		m_Pen	= NULL;
		m_Rng	= NULL; 
		m_Hdc   = NULL;
		m_OriginPen	= NULL;
		m_OriginFont= NULL;
		m_OriginBrush= NULL;
		m_OriginPen= NULL;
		m_OriginRng= NULL; 

	}

public:
	 operator HDC() const
	 {
		return m_Hdc;
	 }
public:
	HPEN	m_Pen;
	HFONT	m_Font;
	HBRUSH	m_Brush;
	HRGN	m_Rng; 
	HDC     m_Hdc;


	HPEN	m_OriginPen;
	HFONT	m_OriginFont;
	HBRUSH	m_OriginBrush;
	HRGN	m_OriginRng; 

};

/*
	对GDI+ 函数进行简单的封装.
*/


class C32GdiPlus 
{
public:
	static ULONG_PTR m_GdiToken;
	static Gdiplus::GdiplusStartupInput m_GdiInput;
	static Gdiplus::GdiplusStartupOutput m_GdiOutput;
	
public:
	static BOOL Initialize()
	{
		
		C32GdiStatus Status = Gdiplus::GdiplusStartup(&C32GdiPlus::m_GdiToken, &C32GdiPlus::m_GdiInput, &C32GdiPlus::m_GdiOutput);
		(Status);
		return (Status == Gdiplus::Ok);

	}
	            
	static VOID Uninitialize()
	{
		Gdiplus::GdiplusShutdown(m_GdiToken);
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
		m_OnSize = NULL;
		m_OnContextMenu = NULL;
	}

public:
	VOID SetOnCommand(C32_EVENT_CALLBACK Callback)
	{
		m_OnCommand = Callback;
	}

	VOID SetOnSize(C32_EVENT_CALLBACK_ONSIZE Callback)
	{
		m_OnSize = Callback;
	}

	VOID SetOnContextMenu(C32_EVENT_CALLBACK_CONTEXTMENU Callback)
	{
		m_OnContextMenu = Callback;
	}


public: //Window Message
	C32_EVENT_CALLBACK m_OnCommand;
	C32_EVENT_CALLBACK_ONSIZE m_OnSize;
	C32_EVENT_CALLBACK_CONTEXTMENU m_OnContextMenu;
};

/*
	事件(Msg)处理函数
	事件和处理函数的对应关系
	WM_XYZ : OnXyz
	事件处理函数定义格式：
	BOOL  OnXyz(WPARAM wParam, LPARAM lParam, LRESULT& lResult);
		例外： WM_CREATE, WM_INITDIALOG
	
*/
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
	//通过宏定义事件函数

	C32OnXyz(OnCreate)
	
	C32OnXyz(OnSize)

	C32OnXyz(OnCommand)
	
	C32OnXyz(OnNotify)

	C32OnXyz(OnDrawItem)

	C32OnXyz(OnPaint)

	C32OnXyz(OnNcDestroy)

	C32OnXyz(OnContextMenu)
	
	C32OnXyz(OnDestroy)

	C32OnXyz(OnLButtonDown);

	C32OnXyz(OnLButtonUp);

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
		C32EVENT_UNREFERENCED_PARAMETER();
		BOOL Handle = FALSE;
		
		return Handle;

	}
	
	//WM_NCLBUTTONDOWN
	virtual BOOL OnNcLButtonDown(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		C32EVENT_UNREFERENCED_PARAMETER();
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

	VOID SetEventClick(C32_EVENT_CALLBACK_STATIC_CLICK Callback)
	{
		m_OnClick = Callback;
	}

	VOID SetEventDClick(C32_EVENT_CALLBACK_STATIC_CLICK Callback)
	{
		m_OnDClick = Callback;
	}


	//Static Control Event
	C32_EVENT_CALLBACK_STATIC_CLICK m_OnClick; //点击
	C32_EVENT_CALLBACK_STATIC_DCLICK m_OnDClick;//双击
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

	VOID SetEventClick(C32_EVENT_CALLBACK_BUTTON_CLICK Callback)
	{
		m_OnClick = Callback;
	}

	VOID SetEventDClick(C32_EVENT_CALLBACK_BUTTON_DCLICK Callback)
	{
		m_OnDClick = Callback;
	}

	//Button Control Event
	C32_EVENT_CALLBACK_BUTTON_CLICK m_OnClick; //点击
	C32_EVENT_CALLBACK_BUTTON_DCLICK m_OnDClick;//双击
};




class C32DialogEventCallback
{

public:
	C32DialogEventCallback()
	{
		Init();
	}
	~C32DialogEventCallback()
	{
		Init();
	}

	VOID Init()
	{
		m_OnInitDialog = NULL;
	}
	
	VOID SetEventDialogInit(C32_EVENT_CALLBACK_DIALOG_INIT Callback)
	{
		m_OnInitDialog = Callback;
	}
	//Dialog Event Callback
	C32_EVENT_CALLBACK_DIALOG_INIT  m_OnInitDialog; //WM_INIT_DIALOG
	
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

/*
	@breif: 窗口放大缩小时，控件改变大小或位置。
	记住是 或，因为位置和大小同时变化时，太复杂了，放弃。
	m_SwpFlag : 记录变化类型
	m_SwpPos;  //位置不变时，边缘不变设置
	m_SwpSize; //大小不变时，边缘不变设置
	m_Margin;  //记录控件在窗口左边缘，上边缘，右边缘下边缘距离初始值，以此做参考.

	顺序： 以从上到下，从左到右为先后顺序标记
	大小不变的控件一般为
		Button ComboBox
			左上边距不变：之前没有可变大小的控件
			右下边距不变：之前有可变大小的控件
	位置不变的控件一般为
		ListView TreeView Edit ...
			左上边距不变： 因为位置已经不变。左上边距已经失去了意义
			右下边距不变：

*/
class C32PosSize
{
public:
	C32PosSize()
	{
		Init();
	}

	~C32PosSize()
	{

	}

public:
	VOID Init()
	{
		SetRectEmpty(&m_SwpPos);
		SetRectEmpty(&m_SwpSize);
		SetRectEmpty(&m_Margin);
		SetRectEmpty(&m_Content);
		RtlZeroMemory(&m_SizeWindow,sizeof(SIZE));
		RtlZeroMemory(&m_SwpSizeFlag,sizeof(SIZE));
		
		m_SwpFlag = 0;  
	}

	VOID CalPosSize(POINT& Pt, SIZE& Size)
	{
		
			if (m_SwpFlag& SWP_NOSIZE) //大小不变，位置变
			{
				if (m_SwpSize.left)  //左边距不变
				{
					Pt.x = m_Margin.left;
				}
				if (m_SwpSize.top) //上边距不变
				{
					Pt.y = m_Margin.top;
				}
				if (m_SwpSize.right) //右边距不变
				{
					Pt.x = m_SizeWindow.cx - m_Margin.right -C32GetRectWidth(m_Content);
				} 
				if (m_SwpSize.bottom) //下边距不变
				{
					Pt.y = m_SizeWindow.cy -m_Margin.bottom - C32GetRectHeight(m_Content);
				}
			}

			if (m_SwpFlag& SWP_NOMOVE)
			{
				//位置不变，大小变
				
				if (m_SwpSizeFlag.cx == 1) //长度不变
				{
					Size.cx = C32GetRectWidth(m_Content);
				}else                   //长度变
				{
					if (m_SwpPos.right)
					{
						Size.cx = m_SizeWindow.cx - m_Margin.right - m_Content.left;
					}
				}
				if (m_SwpSizeFlag.cy == 1) //高度不变
				{
					Size.cy = C32GetRectHeight(m_Content);
				}else
				{
					if (m_SwpPos.bottom)
					{
						Size.cy = m_SizeWindow.cy - m_Margin.bottom - m_Content.top;
					}
				}
				
			}
		
	}

	/*
		大小不变时,边缘不变设置
	*/
	VOID SetNoSizeLeftTop()
	{
		m_SwpFlag |= SWP_NOSIZE;		
		m_SwpSize.left = 1;
		m_SwpSize.top  = 1;

		m_SwpSize.right = 0;
		m_SwpSize.bottom = 0;
	}

	VOID SetNoSizeLeftBottom()
	{
		m_SwpFlag |= SWP_NOSIZE;		
		m_SwpSize.left = 1;
		m_SwpSize.top  = 0;

		m_SwpSize.right = 0;
		m_SwpSize.bottom = 1;
	}


	VOID SetNoSizeRightBotton()
	{
		m_SwpFlag |= SWP_NOSIZE;		
		m_SwpSize.left = 0;
		m_SwpSize.top  = 0;

		m_SwpSize.right = 1;
		m_SwpSize.bottom = 1;
	}

	VOID SetNoSizeRightTop()
	{
		m_SwpFlag |= SWP_NOSIZE;
		
		m_SwpSize.left = 0;
		m_SwpSize.top  = 1;

		m_SwpSize.right = 1;
		m_SwpSize.bottom = 0;
	}

	VOID SetNoHeigthRight()
	{
		m_SwpSizeFlag.cy = 1;
		m_SwpFlag |= SWP_NOMOVE;

		m_SwpPos.right = 1;
		m_SwpPos.bottom = 0;
	}

	VOID SetNoWidthBottom()
	{
		m_SwpSizeFlag.cx = 1;
		m_SwpFlag |= SWP_NOMOVE;

		m_SwpPos.right = 0;
		m_SwpPos.bottom = 1;
	}

	VOID SetNoMoveRightBottom()
	{
		m_SwpFlag |= SWP_NOMOVE;

		m_SwpPos.right = 1;
		m_SwpPos.bottom = 1;
	}



	


public:
	RECT  m_SwpPos;  //位置不变时，边缘不变设置
	RECT  m_SwpSize; //大小不变时，边缘不变设置
	SIZE m_SwpSizeFlag; // 控制高度和宽度是否变化
	DWORD m_SwpFlag;
	RECT  m_Margin;  //记录控件在窗口左边缘，上边缘，右边缘下边缘距离
	RECT  m_Content; //控件在窗口Client域中的位置
	SIZE  m_SizeWindow; //窗口Client域大小

};

class C32Window : public C32Event ,public C32PosSize, public C32EventCallback
{
public: 
	static LRESULT CALLBACK C32WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		BOOL    Handle = FALSE;
		LRESULT lResult = 0;
		C32Window* This =  (C32Window*)C32GetUserData(hwnd);
		LPCWSTR Title;
		char* sMsg = C32DbgGetWindowMsgString(uMsg);
		Title = (This ? This->m_StringText.GetString(): L"NULL");
		if (sMsg != NULL)
			ZxDebug(("Title %ws sMsg: %s :hwnd: %p :C32Window: %p wParam:%p lParam: %p \n",Title, sMsg, hwnd, This, wParam, lParam));
		switch(uMsg)
		{ 
			case WM_CREATE:
				 {
					LPCREATESTRUCT lpcs = (LPCREATESTRUCT)lParam;
					This = (C32Window*)lpcs->lpCreateParams;
					This->Attach(hwnd) ;
					Handle = This->OnCreate(wParam, lParam, lResult);
					This->SetUserData();
				 }
				 break; 
				 
			case WM_SIZE:
				Handle = This->OnSize(wParam, lParam, lResult);
				break;
			case WM_PAINT:
				Handle = This->OnPaint(wParam, lParam, lResult);
				break;
			case WM_NOTIFY:
				Handle = This->OnNotify(wParam, lParam, lResult);
				break;
			case WM_DRAWITEM:
				Handle = This->OnDrawItem(wParam, lParam, lResult);
				break;
			case WM_COMMAND:
				Handle = This->OnCommand(wParam, lParam, lResult);
				break;
			
			case WM_NCDESTROY:
				Handle = This->OnNcDestroy(wParam, lParam, lResult);
				delete This;
				break;
			case WM_CONTEXTMENU:
				Handle = This->OnContextMenu(wParam, lParam, lResult);
				break; 
			case WM_DESTROY:
				Handle = This->OnDestroy(wParam, lParam, lResult);
				break;
			case WM_LBUTTONDOWN: 
				Handle = This->OnLButtonDown(wParam, lParam, lResult);
				break;
			case WM_LBUTTONUP:
				Handle = This->OnLButtonUp(wParam, lParam, lResult);
				break;

			default:
				break;
		}

		if (Handle == FALSE)
		{
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}

		return lResult;

	}
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

	virtual ~C32Window()
	{
		if (m_Hwnd && !m_Attach)
		{
			m_Hwnd = NULL;
		}
		
	}

	static DWORD RegisterClassEx32(LPCWSTR lpszClassName, 
							WNDPROC lpfnWndProc = NULL, 
							HCURSOR hCursor = NULL,
							HBRUSH hBackGround = NULL, 
							int MenuResorseId = 0,
							int IconId = NULL,
							int IconSmId = NULL)
	{
		WNDCLASSEX wcex = {};

		wcex.cbSize = sizeof(WNDCLASSEX);

		wcex.style			= CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc	= lpfnWndProc ? lpfnWndProc : C32Window::C32WndProc;
		wcex.cbClsExtra		= 0;
		wcex.cbWndExtra		= 0;
		wcex.hInstance		= C32Hinstance;
		wcex.hIcon			= (IconId?LoadIcon(C32Hinstance, MAKEINTRESOURCE(IconId)):NULL);
		wcex.hbrBackground	= hBackGround ? hBackGround :(HBRUSH)(COLOR_WINDOW+1);
		wcex.hCursor		= hCursor ? hCursor : LoadCursor(NULL, IDC_ARROW);
		wcex.lpszMenuName	= MenuResorseId == 0 ? NULL : MAKEINTRESOURCE(MenuResorseId);
		wcex.lpszClassName	= lpszClassName;
		wcex.hIconSm		= (IconSmId?LoadIcon(C32Hinstance, MAKEINTRESOURCE(IconSmId)):NULL);

		ATOM Atom = RegisterClassEx(&wcex);
		return Atom;
	}

	HWND Create(DWORD ExStyle, LPCWSTR lpwszClassName,LPCWSTR lpwszWindowName,DWORD Style, int xPos, int yPos, int Cx, int Cy, HWND hwnd)
	{
		m_Hwnd = CreateWindowEx(ExStyle,lpwszClassName, lpwszWindowName, Style, xPos,yPos, Cx, Cy, hwnd, NULL, C32Hinstance,this);
		
		ZxDebugEx((__FUNCTION__"()::%ws m_Hwnd : %p This : %p Parent:%p Code: %d\n", lpwszClassName,m_Hwnd, this, hwnd, GetLastError()));
		return m_Hwnd;
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
		GetPos();
		SetMargin();
		GetWindowText32();
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

	VOID GetPos()
	{
		GetClientRect(m_Hwnd, &m_ClientRect);
		GetWindowRect(m_Hwnd, &m_Rect);

		m_ClientCx = C32GetRectWidth(m_ClientRect);
		m_ClientCy = C32GetRectHeight(m_ClientRect);

		m_Cx =  C32GetRectWidth(m_Rect);
		m_Cy = C32GetRectHeight(m_Rect);
	}

	BOOL GetCursorPos32(POINT& Pt)
	{
		BOOL bRet = FALSE;
		RtlZeroMemory(&Pt, sizeof(POINT));
	
		if (GetCursorPos(&Pt))
		{
			if (ScreenToClient(m_Hwnd, &Pt))
				bRet = TRUE;
		}

		ZxDebug((__FUNCTION__"():: {%d, %d} \n", Pt.x, Pt.y));
		return bRet;
	}

	VOID SetMargin()
	{
		GetContentRect();

		m_Margin.left = m_Content.left;
		m_Margin.top = m_Content.top;
		RECT rc = GetParentClient();
		m_Margin.right = C32GetRectWidth(rc) - m_Content.right;
		m_Margin.bottom = C32GetRectHeight(rc)  - m_Content.bottom;
	
	}

	RECT GetParentClient()
	{
		RECT rc = {};
		m_Parent = m_Parent? m_Parent : GetParent(m_Hwnd);

		if (m_Parent)
		{
			GetClientRect(m_Parent, &rc);
		}

		return rc;
	}

	//将屏幕坐标点矩形，转换成该窗口Client域为坐标的矩形
	RECT GetContentRect()
	{
		BOOL bConvert = FALSE;
		RECT  rcRet = {};
		GetPos();
		POINT Pt={m_Rect.left, m_Rect.top};
		if (m_Hwnd)
		{
			HWND Parent = m_Parent ? m_Parent :GetParent(m_Hwnd);	
			if (ScreenToClient(Parent, &Pt))
			{
				rcRet.left = Pt.x;
				rcRet.top = Pt.y;
				rcRet.right = Pt.x + C32GetRectWidth(m_Rect);
				rcRet.bottom = Pt.y + C32GetRectHeight(m_Rect);
			}
			m_Parent = Parent;
		}
		m_Content = rcRet;
		
		return rcRet;

	}

	BOOL ScreenToClient32(PPOINT Point)
	{
		BOOL bRet = ScreenToClient(m_Hwnd, Point);

		return (bRet ? TRUE : FALSE);
	}

	BOOL ScreenToClient32(int xPos, int yPos, PPOINT Point)
	{
		Point->x = xPos;
		Point->y = yPos;
		BOOL bRet = ScreenToClient(m_Hwnd, Point);
		
		return (bRet ? TRUE : FALSE);
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
		GetPos();
		return bRet;
	}
	
	BOOL SetCenterPos(HWND Parent = NULL)
	{
		m_Parent = Parent ? Parent : GetParent(m_Hwnd);
		if (m_Parent == NULL)
			return FALSE;
		RECT Rect = {};
		GetPos();
		GetWindowRect(m_Parent, &Rect);
		int X = (Rect.left + Rect.right)/2 - C32GetRectWidth(m_Rect)/2;
		int Y = (Rect.top + Rect.bottom)/2 - C32GetRectHeight(m_Rect)/2;
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
	BOOL AddStyle(DWORD Style)
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

	VOID ReflushWindow()
	{
		SetWindowPos(m_Hwnd, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER  );
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

	virtual VOID SetVisible(BOOL bVisible = TRUE)
	{
		DWORD Style = GetStyle();
		if (bVisible)
			Style |= WS_VISIBLE;
		else
			Style &= ~WS_VISIBLE;

		SetStyle(Style);
		ReflushWindow();
		
	}

	// 小心处理
	VOID SetUserData(LPVOID UserData = NULL)
	{ 
		if (GetUserData())
			return;
		UserData = UserData ? UserData : this;
		SetWindowLongPtr(m_Hwnd, GWLP_USERDATA, (LONG_PTR)UserData);
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
		Width = C32GetRectWidth(m_ClientRect);
		Height = C32GetRectHeight(m_ClientRect);
	}

	VOID GetLength(int & Width, int& Height)
	{
		Width = C32GetRectWidth(m_Rect);
		Height = C32GetRectHeight(m_Rect);
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
		GetPos();
	}

	HWND GetHwnd()
	{
		return m_Hwnd;
	}

	int GetWindowText32()
	{
		m_StringText.AssignStringW(256);
		m_StringText.m_Count = GetWindowText(m_Hwnd, m_StringText, 256);

		return m_StringText.m_Count;
	}
	
	SIZE GetClientSize()
	{
		SIZE Size={m_ClientCx, m_ClientCy};

		return Size;
	}


public:
	VOID DebugRect()
	{
		ZxDebugEx((__FUNCTION__"():: Window: {%d, %d, %d, %d} \n", m_Rect.left, m_Rect.top, m_Rect.right, m_Rect.bottom));		
		ZxDebugEx((__FUNCTION__"():: Client: {%d, %d, %d, %d} \n", m_ClientRect.left, m_ClientRect.top, m_ClientRect.right, m_ClientRect.bottom));
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
	C32String m_StringTitle;
	C32String m_StringText;
};

class C32Menu : public C32Window
{
public:
	static HINSTANCE hInstance;
	C32Menu()
	{
		Init();
	}

	~C32Menu()
	{
		DestroyMenu32();
	}


public:
	HMENU LoadMenu32(int ResourceId)
	{
		m_hMenu = LoadMenu(C32Menu::hInstance, MAKEINTRESOURCE(ResourceId));
		
		return m_hMenu;
	}

	VOID  DestroyMenu32()
	{
		if (m_hMenu)
		{
			DestroyMenu(m_hMenu);
			m_hMenu = NULL;
		}
		if (m_Sub)
		{
			DestroyMenu(m_Sub);
			m_Sub = NULL;
		}
	}

	BOOL Display(int ResorceId, int nPos, int X, int Y, HWND Parent)
	{
		  if (ResorceId == 0)
			return FALSE;

	   if (m_Sub == NULL)
	   {
		   m_hMenu = LoadMenu(C32Menu::hInstance, MAKEINTRESOURCE(ResorceId));
		   m_Sub = GetSubMenu(m_hMenu, nPos);
		   m_Parent = Parent;
	   }
		
	  return TrackPopupMenuEx(m_Sub,  TPM_LEFTALIGN, X, Y, Parent, NULL);
	}
	
	BOOL Display(int xPos, int yPos)
	{
		return Display(m_ResourceId, m_SubPos, xPos, yPos, m_Parent);
	}

	int GetSubItemCount()
	{
		return GetMenuItemCount(m_Sub);
	}

	LPCWSTR GetSubItemString(int CommandId)
	{
		if(GetMenuString(m_Sub, CommandId, m_StringText, 255, MF_BYCOMMAND))
			return m_StringText;
		else
			return NULL;
	}

	// 打勾
	BOOL SetSelectSubItem(int CommandId, BOOL bCheck = TRUE)
	{
		DWORD Status;

		Status = CheckMenuItem(m_hMenu, CommandId, bCheck?MF_CHECKED:MF_UNCHECKED);
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

		C32CtrlDebug((__FUNCTION__"():: Click %ws: \n", GetSubItemString(CommandId)));
	}

	VOID SelectSubItemPos(int nPos)
	{
		CheckMenuItem(m_Sub, nPos, MF_BYPOSITION|MF_CHECKED);
	}

	BOOL IsSubItem(int CommandId)
	{
		BOOL Is = FALSE;
		int Count = GetSubItemCount();
		for(int i = 0; i < Count; i++)
		{
			UINT Id = GetMenuItemID(m_Sub, i);
			if (Id == CommandId)
			{	
				Is = TRUE;
				break;
			}
		}
		return Is;
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

	int GetResourceId()
	{
		return m_ResourceId;
	}


	VOID Set(HWND Parent, int ResorceId, int SubPos = 0)
	{
		m_Parent = Parent;
		m_ResourceId = ResorceId;
		m_SubPos = SubPos;
	}
	
	VOID Init()
	{
		m_hMenu = NULL;
		m_Sub = NULL;
		m_Parent = NULL;
		m_ResourceId = 0;
		m_SubPos = 0;
	}

public:
	HMENU m_hMenu;
	HMENU m_Sub;
	HWND  m_Parent;
	int   m_ResourceId;
	int   m_SubPos;
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

	HWND Create(DWORD Style, int xPos, int yPos, int Cx, int Cy, HWND hwnd)
	{
		m_Hwnd = CreateWindow(WC_BUTTON, L"C32Button", Style, xPos, yPos, Cx, Cy, hwnd, NULL, C32Hinstance, (LPVOID)this);
		if (m_Hwnd)
			Attach(m_Hwnd);

		ZxDebugEx((__FUNCTION__"():: m_Hwnd: %p This: %p \n", m_Hwnd, this));
		
		return m_Hwnd;
	}
	  
public:
	int SetText(LPCWSTR Text)
	{
		return (int)Button_SetText(m_Hwnd, Text);
	}


	LPWSTR GetText()
	{
		m_StringText.AssignStringW(226);

		m_StringText.m_Count = Button_GetText(m_Hwnd, m_StringText, 256);
		return m_StringText;
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
	
	DWORD GetCheck()
	{
		BOOL State = Button_GetCheck(m_Hwnd);

		return State;
	}

	BOOL IsCheck()
	{
		DWORD State = GetCheck();

		return (State & BST_CHECKED);
	}

	VOID SetCheck(BOOL bCheck = TRUE)
	{
		int State = (bCheck ? BST_CHECKED : BST_UNCHECKED);
		Button_SetCheck(m_Hwnd, State);
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

	//If an application processes this message, it should return zero.
	virtual BOOL CALLBACK OnCommand(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		lResult = 0;
		BOOL Handle = FALSE;
		C32SetHandleLReslut(FALSE, 0);
		DWORD NotifyCode;
		NotifyCode = HIWORD(wParam);
		ZxDebugEx((__FUNCTION__"():: Text: %ws \n", this->GetText()));
		switch(NotifyCode)
		{
			case BN_CLICKED:
				Handle  = OnClick(wParam, lParam);
				break;
			case BN_DOUBLECLICKED:
				Handle  = OnDClick(wParam, lParam);
				break;
			case BN_SETFOCUS:
				break;

		}

		if (Handle == TRUE)
			lResult = 0;

		return Handle;
	}

	virtual BOOL OnClick(WPARAM wParam, LPARAM lParam)
	{
		BOOL Handle = FALSE;
		if (m_OnClick)
			Handle = m_OnClick(C32CommandCtrlId(wParam), this);
		
				
		return Handle;
	}

	virtual BOOL OnDClick(WPARAM wParam, LPARAM lParam)
	{
		BOOL Handle = FALSE;
		if (m_OnDClick)
			Handle = m_OnDClick(C32CommandCtrlId(wParam), this);	
		return Handle;
	}

public:
	VOID Init()
	{

	}

	C32Icon  m_Icon;
};

class C32Radio : public C32Button
{
public:
	C32Radio()
	{

	}
	virtual ~C32Radio()
	{


	}

};

class C32GroupBox : public C32Button
{
public:
	C32GroupBox()
	{

	}
	virtual ~C32GroupBox()
	{

	}
};


class C32CheckBox : public C32Button
{
public:
	C32CheckBox()
	{

	}
	~C32CheckBox()
	{

	}

public:
	



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
			m_String.Assign(m_Length*2);
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

	BOOL  SetText(LPCWSTR Text)
	{
		 return Edit_SetText(m_Hwnd, Text);
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
		C32EVENT_UNREFERENCED_PARAMETER();
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
		if (Handle == TRUE)
			lResult = 0;

		return Handle;
	}

	virtual BOOL OnClick(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		C32EVENT_UNREFERENCED_PARAMETER();		
		BOOL Handle = FALSE;
		if (m_OnClick)
			Handle = m_OnClick(C32CommandCtrlId(wParam), this);	
		return Handle;
	}

	virtual BOOL OnDClick(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		C32EVENT_UNREFERENCED_PARAMETER();

		BOOL Handle = FALSE;
		if (m_OnDClick)
			Handle = m_OnDClick(C32CommandCtrlId(wParam), this);	
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

	int  AddString(LPCWSTR String)
	{
		return Add(String);
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

	int SelectItemString(LPCWSTR String)
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
		return ComboBox_SetItemHeight(m_Hwnd,0, iHeight);
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

	int GetCurrentSelect()
	{
		return (int)ComboBox_GetCurSel(m_Hwnd);
	}
	
	int GetString(int Index, C32String& String)
	{
		int Length = (int)ComboBox_GetLBTextLen(m_Hwnd, Index);
		if (Length <= 0)
			return LB_ERR;

		String.AssignStringW(Length++);

		Length = (int)ComboBox_GetLBText(m_Hwnd, Index, (LPWSTR)String.GetString());
		String.m_Length = Length;
		return  String.GetStringLength();
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


};

class C32ListBox : public C32Window
{

public:
	static HINSTANCE hInstance;
	
	static VOID Initialize()
	{
		
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
		 int Count = (int)SendMessage(m_Hwnd,  LB_GETCOUNT, (WPARAM)NULL, (LPARAM)NULL);
		 if (Count == LB_ERR)
			Count = 0;

		return Count;
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

	int GetSelectCount()
	{
		int Count = ListBox_GetSelCount(m_Hwnd);
		if (Count == LB_ERR)
			return 0;

		return Count;
	}

	PINT GetMulSelect(PINT ArraySize)
	{
		int Count = GetSelectCount();
		if (Count == 0)
			return NULL;

		PINT Array = new INT[Count];
		if (Array == NULL)
			return NULL;

		if (Array)
			RtlZeroMemory(Array, sizeof(INT)*4);
		int Sel = ListBox_GetSelItems((HWND)m_Hwnd, Count, Array);
		if (Sel < 0)
		{
			delete Array;
			Array = NULL;
			Count = 0;
		}
		*ArraySize = Count;
		return Array;

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
		//LPARAM lParam = MAKELPARAM(Index, Index);
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
		ListBox_SetColumnWidth(m_Hwnd, Width);	
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
		RECT  Rect = lpdis->rcItem;
		if (IsOwnerDraw() == FALSE)
			return FALSE;

		lResult = (LRESULT)TRUE;
		// If there are no list box items, skip this message. 
		if (lpdis->itemID == -1)
		{
			return TRUE;
		}
		
		C32DrawControl Draw;
		C32DeviceContext Cdc;
		Draw.Open(WC_BUTTON, this->GetWindow());
		
		switch(lpdis->itemAction)
		{
			case ODA_SELECT: 
			case ODA_DRAWENTIRE: 
				  if(GetString(lpdis->itemID, String) ==LB_ERR)
					break;
				 
				Cdc.SetHdc(lpdis->hDC);
				Cdc.SelectFont32();
				  // Is the item selected? 
				if (lpdis->itemState & ODS_SELECTED) 
				{ 		
					Draw.DrawCheckBox(lpdis->hDC, CBS_CHECKEDNORMAL, lpdis->rcItem, String);
				}else
				{
					Draw.DrawCheckBox(lpdis->hDC, CBS_UNCHECKEDNORMAL, lpdis->rcItem, String);
				} 
				break;
			/*case ODA_FOCUS: 
				Draw.DrawCheckBox(lpdis->hDC, CBS_CHECKEDHOT, lpdis->rcItem, String);
				break;*/
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

public:  // 自画需要的图标
	C32Icon   m_IconCheck;
	C32Icon   m_IconUnCheck;

};

class C32ImageList
{
public:
#define IMAGE_LIST_INITIAL_COUNT 32
#define IMAGE_LIST_GROUW_COUNT  10
	static HINSTANCE hInstance;
public:
	C32ImageList():m_List(NULL),m_bDestroy(TRUE)
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
		 m_List = ImageList_Create(Cx, Cy, Flags, Initial, Grow);
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
		if (m_List&& m_bDestroy == TRUE)
		{
			ImageList_Destroy(m_List);
		}
		m_List = NULL;
		m_bDestroy = TRUE;
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

	VOID SetImageList(HIMAGELIST hImageList)
	{
		m_List = hImageList;
	}
	
	VOID Attach(HIMAGELIST hImageList)
	{
		m_List = hImageList;
		m_bDestroy = FALSE;
	}

	VOID Detach()
	{
		m_List = NULL;
	}


	HIMAGELIST GetList()
	{
		return m_List;
	}

	VOID Init()
	{
		m_List = NULL;
		m_bDestroy = TRUE;
	}

	

public:
	HIMAGELIST m_List;

	BOOL      m_bDestroy;

};


typedef BOOL  (WINAPI*C32_EVENT_CALLBACK_TREE_VIEW_NOTIFY_SEL_CHANGE)(C32String& NewText, LPARAM lParam, LPNMTREEVIEW lpnmtv,  LRESULT& lResult, C32TreeView* This);

typedef BOOL  (WINAPI*C32_EVENT_CALLBACK_TREE_VIEW_NOTIFY_ITEM_CHANGE)(C32String& ItemText, NMTVITEMCHANGE* lpnmic,  LRESULT& lResult, C32TreeView* This);


class C32TreeViewEventCallback
{

public:
	C32TreeViewEventCallback()
	{
		Init();
	}
	~C32TreeViewEventCallback()
	{
		Init();
	}

	VOID Init()
	{
		m_OnCommandMenu = NULL;
		m_OnNotifySelChanged = NULL;
		m_OnNotifyItemChanged = NULL;
	}

	VOID SetEventCommandMenu(C32_EVENT_CALLBACK_COMMAND_MENU Callback)
	{
		m_OnCommandMenu = Callback;
	}

	VOID SetEventNotifySelChange(C32_EVENT_CALLBACK_TREE_VIEW_NOTIFY_SEL_CHANGE Callback)
	{
		m_OnNotifySelChanged = Callback;
	}

	VOID SetEventNotifyItemChanged(C32_EVENT_CALLBACK_TREE_VIEW_NOTIFY_ITEM_CHANGE Callback)
	{
		m_OnNotifyItemChanged = Callback;
	}

public:
	//TreeView Event Callback
	C32_EVENT_CALLBACK_COMMAND_MENU  m_OnCommandMenu; //WM_INIT_DIALOG
	/*
		The return value is ignored.
	*/
	C32_EVENT_CALLBACK_TREE_VIEW_NOTIFY_SEL_CHANGE m_OnNotifySelChanged;
	/*
		TVN_ITEMCHANGED Returns FALSE to accept the change, or TRUE to prevent the change.
	*/
	C32_EVENT_CALLBACK_TREE_VIEW_NOTIFY_ITEM_CHANGE m_OnNotifyItemChanged;
};

class C32TreeView : public C32Window, public C32TreeViewEventCallback
{
#define TV_MASK_NO_BIT -1
#define C32TV_CHECK_STATE 0x2000
#define C32TV_UNCHECK_STATE 0x1000
#define C32TvGetCheckState(x) (x &LVIS_STATEIMAGEMASK)
#define C32TvIsCheckState(x) (C32TvGetCheckState(x) == C32TV_CHECK_STATE)
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

	BOOL  IsCheckBoxStyle()
	{
		DWORD Style = GetStyle();
		if (Style& TVS_CHECKBOXES)
			return TRUE;
		else
			return FALSE;
	}

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

	VOID SetImageList(BOOL bNormal = TRUE, BOOL bState = TRUE)
	{
		//Sets the normal image list, which contains the selected and nonselected images for the tree view item
		if (bNormal)
			TreeView_SetImageList(m_Hwnd, m_ImageListNormal, TVSIL_NORMAL);

		if (bState)
			TreeView_SetImageList(m_Hwnd, m_ImageListState, TVSIL_STATE);
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

	HTREEITEM InsertItemFirst(HTREEITEM Parent, LPWSTR Text, int cChildren = 1, int iImage = TV_MASK_NO_BIT,  LPARAM lParam = NULL)
	{
		HTREEITEM hItem = InsertItem(Parent, (HTREEITEM)TV_FIRST, Text, iImage, TV_MASK_NO_BIT, cChildren, lParam);

		return hItem;
	}

	HTREEITEM InsertItemLast(HTREEITEM Parent, LPWSTR Text, int cChildren = 1, int iImage = TV_MASK_NO_BIT,  LPARAM lParam = NULL)
	{
		HTREEITEM hItem = InsertItem(Parent, (HTREEITEM)TVI_LAST, Text, iImage, TV_MASK_NO_BIT, cChildren, lParam);

		return hItem;
	}

	HTREEITEM InsertItemSort(HTREEITEM Parent, LPWSTR Text, int cChildren = 1, int iImage = TV_MASK_NO_BIT,  LPARAM lParam = NULL)
	{
		HTREEITEM hItem = InsertItem(Parent, (HTREEITEM)TVI_SORT, Text, iImage, TV_MASK_NO_BIT, cChildren, lParam);

		return hItem;
	}

	HTREEITEM InsertItemRoot(HTREEITEM InsertAfter, LPWSTR Text, int iImage, int iSelectedImage , int cChildren , LPARAM lParam);

	HTREEITEM InsertItemRootText(HTREEITEM InsertAfter, LPWSTR Text, int cChildren ,LPARAM lParam = NULL)
	{
		HTREEITEM hItem = InsertItemRoot(InsertAfter, Text, TV_MASK_NO_BIT, TV_MASK_NO_BIT, cChildren, lParam);
		return hItem;
	}

	HTREEITEM InsertItemRoot(LPWSTR Text, int cChildren = 1, int iImage =TV_MASK_NO_BIT, LPARAM lParam = NULL)
	{
		HTREEITEM hItem = InsertItemRoot(TVI_LAST, Text, iImage, TV_MASK_NO_BIT, cChildren, lParam);
		return hItem;
	}

	HTREEITEM InsertItemRootSort(LPWSTR Text, int cChildren = 1, int iImage =TV_MASK_NO_BIT, LPARAM lParam = NULL)
	{
		HTREEITEM hItem = InsertItemRoot((HTREEITEM)TVI_SORT, Text, iImage, TV_MASK_NO_BIT, cChildren, lParam);
		return hItem;
	}

	HTREEITEM InsertItemRootFirst(LPWSTR Text, int cChildren = 1, int iImage =TV_MASK_NO_BIT, LPARAM lParam = NULL)
	{
		HTREEITEM hItem = InsertItemRoot((HTREEITEM)TVI_FIRST, Text, iImage, TV_MASK_NO_BIT, cChildren, lParam);
		return hItem;
	}
	
	HTREEITEM InsertItemRootLast(LPWSTR Text, int cChildren = 1, int iImage =TV_MASK_NO_BIT, LPARAM lParam = NULL)
	{
		HTREEITEM hItem = InsertItemRoot((HTREEITEM)TVI_LAST, Text, iImage, TV_MASK_NO_BIT, cChildren, lParam);
		return hItem;
	}


	HTREEITEM InsertItemAsyn(HTREEITEM Parent, HTREEITEM InsertAfter, LPWSTR Text, int iImage, int iSelectedImage, int cChildren, LPARAM lParam);
	
public:
	BOOL   DeleteAllItem()
	{
		return TreeView_DeleteAllItems(m_Hwnd);
	}

	BOOL   GetItem(HTREEITEM hItem,TVITEM &tvi, C32String& Text)
	{
		Text.AssignStringW(260);
		
		//RtlZeroMemory(&tvi, sizeof(tvi));
		tvi.mask = TVIF_TEXT | TVIF_IMAGE| TVIF_PARAM|TVIF_STATE|TVIF_HANDLE|TVIF_CHILDREN;
		tvi.hItem = hItem;
		
		tvi.stateMask = TVIS_SELECTED|TVIS_CUT|TVIS_EXPANDED|TVIS_EXPANDEDONCE|TVIS_EXPANDPARTIAL|TVIS_EX_DISABLED;
		tvi.pszText = Text.GetString();
		tvi.cchTextMax = Text.GetTotalCount();
		
		Text.SetCount();

		return TreeView_GetItem(m_Hwnd, &tvi);
	}
	
	C32String   GetItemText(HTREEITEM hItem)
	{
		C32String Text;
		Text.AssignStringW(260);

		TVITEM tvi = {};
		tvi.mask = TVIF_TEXT ;
		tvi.hItem = hItem;

		tvi.pszText = Text.GetString();
		tvi.cchTextMax = Text.GetTotalCount();

		BOOL bGet = TreeView_GetItem(m_Hwnd, &tvi);
		if (bGet == FALSE)
		{
			return C32String();
		}
		Text.SetCount();
		return Text;
	}

	LPARAM   GetItemUserData(HTREEITEM hItem)
	{
		TVITEM tvi = {};
		tvi.mask = TVIF_PARAM ;
		tvi.hItem = hItem;
		BOOL bGet = TreeView_GetItem(m_Hwnd, &tvi);
		if (bGet == FALSE)
			return NULL;
		
		return tvi.lParam;
	}


	BOOL GetItem(HTREEITEM hItem, C32String& Text, LPARAM& lParam)
	{
		TVITEM tvi = {};
		if(GetItem(hItem, tvi, Text) == TRUE)
		{
			lParam = tvi.lParam;
		}else
			return FALSE;

		return TRUE;
	}

	BOOL GetItemlParam(HTREEITEM hItem, LPARAM& lParam)
	{
		TVITEM tvi = {};
		C32String Text;
		if(GetItem(hItem, tvi,Text) == TRUE)
		{
			lParam = tvi.lParam;
			return TRUE;
		}

		return TRUE;
	} 

	BOOL GetSelectItem(C32String& Text, LPARAM& lParam)
	{ 
		TVITEM tvi = {};
		HTREEITEM hti = TreeView_GetSelection(m_Hwnd);
		if (hti)
		{
			if(GetItem(hti, tvi,Text))
			{
				lParam = tvi.lParam;
				return TRUE;
			}
		}

		return FALSE;
	}

	HTREEITEM GetRootItem()
	{
		return TreeView_GetRoot(m_Hwnd);
	}

	/*
		仅包含Child
	*/
	VOID GetChild(HTREEITEM hItem, std::vector<HTREEITEM>& hChildList)
	{
		HTREEITEM hChild = TreeView_GetChild(m_Hwnd, hItem);
		HTREEITEM hSibling = hChild;
		if (hChild)
		{
			do 
			{
				hChildList.push_back(hSibling);
				GetChild(hSibling, hChildList);
			} while ((hSibling = TreeView_GetNextSibling(m_Hwnd, hSibling)) != NULL);
		}
		
	}

	LPARAM GetSelectItemlParam(LPARAM& lParam)
	{
		C32String Text;
		GetSelectItem(Text, lParam);

		return lParam;
	}
	
	UINT GetCount()
	{
		 return TreeView_GetCount(m_Hwnd);
	}

	VOID GetItemLevel(HTREEITEM hItem, int& Level)
	{
		if (hItem == NULL)
			return ;

		HTREEITEM hParent = TreeView_GetParent(m_Hwnd, hItem);
		if (hParent)
		{
			++Level;
			return  GetItemLevel(hParent, Level);
		}
			

	}
	
	UINT GetCheckState(HTREEITEM hItem)
	{
		UINT Check = TreeView_GetCheckState(m_Hwnd, hItem);
		return Check;
	}

	UINT IsCheckState(HTREEITEM hItem)
	{
		if (GetCheckState(hItem) == 1)
			return TRUE;

		return FALSE;
	}

	VOID SetCheckState(HTREEITEM hItem, BOOL bCheckState = TRUE)
	{
		TreeView_SetCheckState(m_Hwnd, hItem, bCheckState)
	}

	VOID SetChildCheckState(HTREEITEM hItem, BOOL bCheckState = TRUE)
	{
		HTREEITEM hChild = TreeView_GetChild(m_Hwnd, hItem);
		HTREEITEM hSibling = hChild;
		if (hChild)
		{
			do 
			{
				SetChildCheckState(hSibling, bCheckState);
			} while ((hSibling = TreeView_GetNextSibling(m_Hwnd, hSibling)) != NULL);
		}
		SetCheckState(hItem, bCheckState);

	}

	VOID GetCheckStateItems(HTREEITEM hItem, std::vector<HTREEITEM>& List)
	{
		HTREEITEM hChild = TreeView_GetChild(m_Hwnd, hItem);
		HTREEITEM hSibling = hChild;
		if (hChild)
		{
			do 
			{
				GetCheckStateItems(hSibling, List);
			} while ((hSibling = TreeView_GetNextSibling(m_Hwnd, hSibling)) != NULL);
		}
		
		if(IsCheckState(hItem))
		{
			List.push_back(hItem);
		}


	}

	VOID GetCheckStateItems(std::vector<HTREEITEM>& List)
	{
		HTREEITEM hRootItem;
		hRootItem = TreeView_GetRoot(m_Hwnd);

		GetCheckStateItems(hRootItem, List);
	}


public:	
	
	//WM_CONTEXMENU
	virtual BOOL CALLBACK OnContextMenu(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		int xCursor, yCursor;

		xCursor = GET_X_LPARAM(lParam);
		yCursor = GET_Y_LPARAM(lParam);
		if (m_Menu.m_ResourceId == 0)
			return FALSE;
		
		m_Menu.Display(m_Menu.m_ResourceId, 1,xCursor, yCursor, m_Hwnd);

		return TRUE;

	}

	virtual BOOL CALLBACK OnContextMenu(HWND hwnd, int xCursor, int yCursor)
	{
		m_Menu.Display(m_Menu.m_ResourceId, 1,xCursor, yCursor, m_Hwnd);
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

		ZxDebugEx((__FUNCTION__"():: %ws \n", m_Menu.GetSubItemString(C32CommandMenuId(wParam))));

		if (m_OnCommandMenu)
			Handle = m_OnCommandMenu(C32CommandMenuId(wParam), lResult, this);

		
		return TRUE;	
	}
	// WM_NOTIFY
	virtual BOOL CALLBACK OnNotify(WPARAM wParam, LPARAM lParam, LRESULT& lResult);
	 
	//Return nonzero to prevent the default processing, or zero to allow the default processing.
	virtual BOOL CALLBACK OnNotifyNmClick(LPNMHDR lpnmhdr, LRESULT& lResult)
	{
		lResult = FALSE ;
		return TRUE;
	}

	//Return zero to enable the control to set the cursor or nonzero to prevent the control from setting the cursor.

	virtual BOOL CALLBACK OnNotifyNmSetCursor(LPNMMOUSE lpnmm, LRESULT& lResult)
	{
		lResult = 1;
		return TRUE;
	}


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

	virtual BOOL CALLBACK OnNotifyItemChanged(NMTVITEMCHANGE*  lpnmtvi, LRESULT& lResult)
	{
		ZxDebugEx(("uChanged: 0x%08x uStateNew : 0x%08x uStateOld : 0x%08x lParam:%p \n",
				  lpnmtvi->uChanged, lpnmtvi->uStateNew, lpnmtvi->uStateOld, lpnmtvi->lParam));
		(lpnmtvi);
		BOOL Handle = FALSE;
		lResult = FALSE ;

		int Level = 0;  
		GetItemLevel(lpnmtvi->hItem, Level);
		if (IsCheckBoxStyle())
		{
			if (C32TvGetCheckState(lpnmtvi->uStateOld) != C32TvGetCheckState(lpnmtvi->uStateNew))
			{
				if (C32TvIsCheckState(lpnmtvi->uStateNew))
				{
					SetChildCheckState(lpnmtvi->hItem);
				}else
				{
					SetChildCheckState(lpnmtvi->hItem, FALSE);
				}
			} 
		}

		if (m_OnNotifyItemChanged)
		{
			C32String ItemText = GetItemText(lpnmtvi->hItem);
			ZxDebug((__FUNCTION__"()::Item Text: %ws \n", ItemText.GetString()));
			Handle = m_OnNotifyItemChanged(ItemText, lpnmtvi, lResult, this); 

		}
		
		return Handle;
	}
	//The return value is ignored.
	virtual BOOL CALLBACK OnNotifySelChanged(LPNMTREEVIEW lptv, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		lResult = FALSE ;
		if (m_OnNotifySelChanged)
		{
			C32String Text;
			LPARAM    lParam;
			if(GetItem(lptv->itemNew.hItem, Text, lParam) == TRUE)
				Handle = m_OnNotifySelChanged(Text, lParam, lptv, lResult, this);
		}
		
		return Handle;
	}
	//Returns TRUE to prevent the selection from changing.
	virtual BOOL CALLBACK OnNotifySelChanging(LPNMTREEVIEW lptv, LRESULT& lResult)
	{
		lResult = FALSE ;
		return TRUE;
	}

	virtual BOOL CALLBACK OnNotifyCustomDraw(LPNMTVCUSTOMDRAW  lplvcd, LRESULT& lResult)
	{ 
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

class C32HeaderEventCallback
{

public:
	C32HeaderEventCallback()
	{
		Init();
	}
	~C32HeaderEventCallback()
	{
		Init();
	}

	VOID Init()
	{
		m_OnNotifyItemStateIconClick = NULL;
	}

	VOID SetOnNotifyItemStateIconClick(C32_EVENT_CALLBACK_HEADER_NOTIFY Callback)
	{
		m_OnNotifyItemStateIconClick = Callback;
	}

	//点击 CheckBox
	C32_EVENT_CALLBACK_HEADER_NOTIFY m_OnNotifyItemStateIconClick;
};


class C32Header : public C32Window, public C32HeaderEventCallback
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

	int GetHeight()
	{
		HDITEM hdi = {};
		hdi.mask = HDI_HEIGHT;

		if(GetItem(0, hdi) == FALSE)
			return 0;

		return hdi.cxy;
	}

	BOOL SetItem(int iItem, HDITEM& hdi)
	{
		return Header_SetItem((HWND)m_Hwnd, iItem, &hdi);
	}

	BOOL DeleteItem(int iItem)
	{
		return Header_DeleteItem(m_Hwnd, iItem);
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
		if (m_Hwnd)
			m_Count = Header_GetItemCount((HWND)m_Hwnd);
		return m_Count;
	}

	int  Reset()
	{
		int Count = GetCount();

		for(int i = Count-1; i >= 0; i--)
		{
			DeleteItem(i);
		}

		return Count;
	}

	//Check Box
	VOID SetCheckboxStyle(int iItem = 0)
	{
		AddStyle(HDS_CHECKBOXES);

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
		
		C32DbgOutHeaderNotify(lphdr->code);

		switch(lphdr->code)
		{
			case HDN_ITEMSTATEICONCLICK:
				Handle= OnNotifyItemStateIconClick(wParam, lParam, lResult);
				break;
			
		}

		return Handle;
	}

	virtual BOOL OnNotifyItemStateIconClick(WPARAM wParam, LPARAM lParam, LRESULT& lResult);

	virtual BOOL CALLBACK OnContextMenu(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = TRUE;
		int xCursor = GET_X_LPARAM(lParam);
		int yCursor = GET_Y_LPARAM(lParam);
		m_Menu.Display(m_Menu.m_ResourceId, 0, xCursor, yCursor, m_Menu.m_Parent);
		return Handle;
	}

	BOOL IsHaveMenu()
	{
		return !(m_Menu.m_ResourceId == 0);
	}


public:
	VOID Init()
	{
		m_List = NULL;
		m_Count = 0;
	}
public:
	int m_Count; //Item 总数
public:
	C32ImageList m_ImageList;
	C32ListView* m_List; //Header 关联的List
	C32Menu  m_Menu;
};


typedef BOOL  (WINAPI*C32_EVENT_CALLBACK_LIST_VIEW_NOTIFY_ITEM_CHANGED)(int iItem, int iSubItem, LPNMLISTVIEW lpnmlv,LRESULT& lResult, C32ListView* This);
typedef BOOL  (WINAPI*C32_EVENT_CALLBACK_LIST_VIEW_NOTIFY_GET_DISP_INFO)(int iItem, int iSubItem, NMLVDISPINFO* lpnmdi,LRESULT& lResult, C32ListView* This);
typedef BOOL  (WINAPI*C32_EVENT_CALLBACK_LIST_VIEW_NOTIFY_NM_CUSTOMDRAW)(LPNMLVCUSTOMDRAW lpnmcd,LRESULT& lResult, C32ListView* This);
typedef BOOL  (WINAPI*C32_EVENT_CALLBACK_LIST_VIEW_DRAW_ITEM)(LPDRAWITEMSTRUCT lpdis,LRESULT& lResult, C32ListView* This);




class C32ListViewEventCallback
{

public:
	C32ListViewEventCallback()
	{
		Init();
	}
	~C32ListViewEventCallback()
	{
		Init();
	}

	VOID Init()
	{
		m_OnCommandMenu = NULL;
		m_OnNotifyItemChanged = NULL;
		m_OnNotifyGetDispInfo = NULL;
		m_OnNotifyCustomDraw = NULL;
		m_OnDrawItem = NULL;
	}

	VOID SetEventCommandMenu(C32_EVENT_CALLBACK_COMMAND_MENU Callback)
	{
		m_OnCommandMenu = Callback;
	}

	VOID SetEventItemChanged(C32_EVENT_CALLBACK_LIST_VIEW_NOTIFY_ITEM_CHANGED Callback)
	{
		m_OnNotifyItemChanged = Callback;
	}
	
	VOID SetEventGetDispInfo(C32_EVENT_CALLBACK_LIST_VIEW_NOTIFY_GET_DISP_INFO Callback)
	{
		m_OnNotifyGetDispInfo = Callback;
	}
	
	VOID SetEventCustomDraw(C32_EVENT_CALLBACK_LIST_VIEW_NOTIFY_NM_CUSTOMDRAW Callback)
	{
		m_OnNotifyCustomDraw = Callback;
	}

	VOID SetEventDrawItem(C32_EVENT_CALLBACK_LIST_VIEW_DRAW_ITEM Callback)
	{
		m_OnDrawItem = Callback;
	}


	//List View Event Callback
	C32_EVENT_CALLBACK_COMMAND_MENU  m_OnCommandMenu; //WM_INIT_DIALOG
	C32_EVENT_CALLBACK_LIST_VIEW_NOTIFY_ITEM_CHANGED m_OnNotifyItemChanged;
	C32_EVENT_CALLBACK_LIST_VIEW_NOTIFY_GET_DISP_INFO m_OnNotifyGetDispInfo; //ListView_InsertItem Callback
	C32_EVENT_CALLBACK_LIST_VIEW_NOTIFY_NM_CUSTOMDRAW m_OnNotifyCustomDraw;
	C32_EVENT_CALLBACK_LIST_VIEW_DRAW_ITEM			  m_OnDrawItem;

};

class C32ListView : public C32Window, public C32ListViewEventCallback
{
#define LV_MASK_NO_BIT -1
	static HINSTANCE  hInstance;
	static LRESULT CALLBACK ListSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam,
		LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
	{
		LRESULT lResult = 0;
		C32ListView* This = (C32ListView*)dwRefData;
		char* sMsg = C32DbgGetWindowMsgString(uMsg);
		ZxDebug((__FUNCTION__"()::sMsg: %s :hwnd: %p :C32: %p\n", sMsg, hWnd, This));

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
		int X, int Y, int Width, int Height,HWND Parent)
	{
		
		m_Rect.left = X, m_Rect.top = Y, m_Rect.right = X + Width, m_Rect.bottom = Y + Height;
		m_Parent = Parent;

		HWND  List = CreateWindowEx(dwExStyle, WC_LISTVIEW, L"C32ListView",dwStyle,
			X, Y, Width, Height, Parent,(HMENU)0, C32ListView::hInstance, (LPVOID)this);

		ZxDebug((__FUNCTION__"()::List:  %p \n", List));

		m_Hwnd = List;
		Attach(List);
		return m_Hwnd;
	}

public:
	operator HWND ()
	{
		return m_Hwnd;
	}
	
	VOID Attach(HWND Hwnd)
	{
		C32Window::Attach(Hwnd);
		SetListHeader();
	}

	HWND GetWindow()
	{
		return m_Hwnd;
	}

	VOID SetExtendedStyle(DWORD dwExStyle)
	{
		ListView_SetExtendedListViewStyle(m_Hwnd, dwExStyle);
	}

	VOID AddExtendedStyle(DWORD dwExStyle)
	{
		DWORD Ex = ListView_GetExtendedListViewStyle(m_Hwnd);
		Ex |= dwExStyle;
		ListView_SetExtendedListViewStyle(m_Hwnd, Ex);
	}

	DWORD GetExtendedStyle()
	{
		DWORD dwExStyle = ListView_GetExtendedListViewStyle(m_Hwnd);
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
		SetWindowTheme(m_Hwnd, L"Explorer", NULL);
	}

	VOID SetSubclass()
	{
		SetWindowSubclass(m_Hwnd, C32ListView::ListSubclassProc, (UINT_PTR)this, (DWORD_PTR)this);
	}

	BOOL RemovSubClass()
	{
		RemoveWindowSubclass(m_Hwnd, C32ListView::ListSubclassProc, (ULONG_PTR)this);
	}

	HWND SetListHeader()
	{
		HWND Header = ListView_GetHeader(m_Hwnd);

		m_Header.SetHeader(Header, this);

		return Header;
	}

	VOID SetMenuId(int ResourceId)
	{
		m_Menu.SetResourceId(ResourceId);
	}

	VOID SetImageList()
	{
		ListView_SetImageList(m_Hwnd, m_ImageListNormal, LVSIL_NORMAL);
		ListView_SetImageList(m_Hwnd, m_ImageListSmall, LVSIL_SMALL);
		ListView_SetImageList(m_Hwnd, m_ImageListStatus, LVSIL_STATE);
	}

	VOID SetImageListNormal()
	{
		ListView_SetImageList(m_Hwnd, m_ImageListNormal, LVSIL_NORMAL);
	}

	VOID SetImageListSmall()
	{
		ListView_SetImageList(m_Hwnd, m_ImageListSmall, LVSIL_SMALL);
	}
	
	VOID SetImageListState()
	{
		ListView_SetImageList(m_Hwnd, m_ImageListStatus, LVSIL_STATE);
	}

	int InsertColumn(int iCol, int iSubItem, LPWSTR Text,int Format, int Cx, int iImage = -1, int CxMin = 32);

	int InsertColumnCenter(int iCol, int iSubItem, LPWSTR Text, int Cx)
	{
		return InsertColumn(iCol, iSubItem, Text, LVCFMT_CENTER, Cx);
	}

	int InsertColumn(int iCol, int iSubItem, LPWSTR Text, int Cx)
	{
		return InsertColumn(iCol, iSubItem, Text, LVCFMT_LEFT, Cx);
	}

	BOOL GetColumnWidth(int iCol)
	{
		return ListView_GetColumnWidth(m_Hwnd,iCol);
	}

	
	int  GetColumnCount()
	{
		return m_Header.GetCount();
	}

	int  GetSelectedColumn()
	{
		return ListView_GetSelectedColumn(m_Hwnd);
	}

	BOOL DeleteColumn(int iCol)
	{
		return ListView_DeleteColumn(m_Hwnd, iCol);
	}

	VOID DeleteAllColumn()
	{
		DWORD Count = GetColumnCount();
		for(int i = Count; i >= 0; i--)
		{
			DeleteColumn(i);
		}
	}


	int InsertItem(int iItem, LPWSTR Text, int iImage = -1, LPARAM lParam = 0);

	BOOL InsertSubItem(int iItem, int iSubItem, LPWSTR Text, int Image = -1);

	int InsertItemAsyn(int iItem, LPWSTR Text, int iImage = -1, LPARAM lParam = 0);

	int InsertItemAsyn(int iItem, LPCWSTR Text, int iImage = -1, LPARAM lParam = 0)
	{
		return InsertItemAsyn(iItem, (LPWSTR)Text, iImage, lParam);
	}

	int InsertSubItemAsyn(int iItem, int iSubItem, LPWSTR Text, int Image = -1);

	int GetItemCount()
	{
		return ListView_GetItemCount(m_Hwnd);
	}

	C32String GetItemText(int iIndex, int iSubItem)
	{
		C32String Text;
		Text.AssignStringW(260);
		/*LVITEM lvi = {};
		lvi.mask = LVIF_TEXT;
		lvi.pszText = Text;
		lvi.cchTextMax = Text.GetTotalCount();*/

		ListView_GetItemText(m_Hwnd, iIndex,iSubItem,Text, Text.GetTotalCount());
		Text.SetCount();

		return Text;
	}

	BOOL GetItemPosition(int iIdenx, PPOINT Point)
	{
		return ListView_GetItemPosition(m_Hwnd, iIdenx, Point);
	}

	VOID SetItemCountEx(int ItemCount, DWORD Flag = LVSICF_NOINVALIDATEALL)
	{
		ListView_SetItemCountEx(m_Hwnd, ItemCount, Flag);
	}
	
	static int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
	{
		C32ListView* List = (C32ListView*)lParamSort;
		ZxDebug(("iItem1 : %d iItem2: %d  %x\n", lParam1, lParam2,(LOWORD(List->m_Parameter)& HDF_SORTDOWN)));
		WCHAR T1[260]={}, T2[260]={};
		ListView_GetItemText(List->m_Hwnd,  lParam1, HIWORD(List->m_Parameter), T1, 260);
		ListView_GetItemText(List->m_Hwnd,  lParam2, HIWORD(List->m_Parameter), T2, 260);

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
		BOOL Handle = FALSE;
		LRESULT lResult = 0;
		if (m_OnNotifyGetDispInfo)
		{
			Handle = m_OnNotifyGetDispInfo(Disp->item.iItem, Disp->item.iSubItem, Disp, lResult, this);
		}else
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

		}

		

		return TRUE;
	} 


public:
	virtual BOOL CALLBACK OnContextMenu(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		int xCursor = GET_X_LPARAM(lParam);
		int yCursor = GET_Y_LPARAM(lParam);
		POINT Point = {};
		ScreenToClient32(xCursor, yCursor, &Point);
		if (m_Header.IsHaveMenu())
		{
			int ColmunHeight;
			POINT Pt = {};
			GetItemPosition(0, &Pt);
			ColmunHeight = Pt.y;
			if (ColmunHeight)
			{
				if (0 <= Point.y && Point.y <= ColmunHeight)
				{
					m_Header.m_Menu.Display(xCursor, yCursor);
					return TRUE;
				}
			}
		}
		
		m_Menu.Display(m_Menu.m_ResourceId, 0,xCursor, yCursor, m_Hwnd);
		return TRUE;
	}

	virtual BOOL CALLBACK OnCommand(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		HWND HwndCtrl;
		DWORD MenuId;
		HwndCtrl= (HWND)lParam;
		MenuId = LOWORD(wParam);
		C32String String ;
		if (m_Header.IsHaveMenu() && m_Header.m_Menu.IsSubItem(MenuId))
		{
			String = m_Header.m_Menu.GetSubItemString(MenuId);
			 m_Header.m_Menu.SelectSubItem(MenuId);
		}else
		{
			m_Menu.SelectSubMenuItem(MenuId);			
			String = this->m_Menu.GetSubItemString(MenuId);
		}

		ZxDebugEx((__FUNCTION__"():: Click: %ws Hwnd: %p %d \n", (LPWSTR)String, HwndCtrl, MenuId));
		if (m_OnCommandMenu)
			Handle = m_OnCommandMenu(C32CommandMenuId(wParam), lResult, this);

		return Handle;	
	}

	virtual BOOL CALLBACK OnDrawItem(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		LPDRAWITEMSTRUCT lpdis = (LPDRAWITEMSTRUCT)lParam;
		assert(lpdis->CtlType == ODT_LISTVIEW);

		//ZxDebug((__FUNCTION__"()::itemId %d hwndItem: %p ,{%d, %d, %d, %d}\n", lpdis->itemID, lpdis->hwndItem,
		//	lpdis->rcItem.left, lpdis->rcItem.top, lpdis->rcItem.right, lpdis->rcItem.bottom));
		if (m_OnDrawItem)
		{
			Handle = m_OnDrawItem(lpdis, lResult, this);
		}
		

		return FALSE;
	}

	// WM_NOTIFY
	virtual BOOL CALLBACK OnNotify(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		lResult = 0;
		LPNMHDR lphdr = (LPNMHDR)lParam;

		int NotifyCode = 0;
		NotifyCode = lphdr->code;
		C32DbgOutListViewNotify(NotifyCode);
		
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
			case NM_CUSTOMDRAW:
				Handle = OnNotifyCustomDraw(wParam, lParam, lResult);
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
		ZxDebugEx((__FUNCTION__"():: Click : %d  %s\n", iSubItem, (fmt == HDF_SORTDOWN ? "down-arrow" :"up-arrow")));
		
		m_Parameter = MAKELONG(fmt, iSubItem);
		ListView_SortItemsEx(m_Hwnd, CompareFunc, this);

		m_Header.SetHeaderSort(NMLv->iSubItem, (fmt == HDF_SORTDOWN ? FALSE :TRUE));

		return TRUE;
	}

	virtual BOOL  OnNotifyCustomDraw(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		LPNMLVCUSTOMDRAW lpnmcd = (LPNMLVCUSTOMDRAW)lParam;

		if (m_OnNotifyCustomDraw)
		{
			Handle = m_OnNotifyCustomDraw(lpnmcd, lResult, this);
		}

		return Handle;
	}

	virtual BOOL  OnNotifyItemChanged(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		LPNMLISTVIEW lplv = (LPNMLISTVIEW)lParam;
		int iSubItem = lplv->iSubItem;
#if 0
		if (IsCheckBoxStyle())
		{
			if (!(lplv->uOldState&LVIS_SELECTED) && lplv->uNewState&LVIS_SELECTED)
			{
				SetItemCheckState(lplv->iItem);
			}
			if ((lplv->uOldState&LVIS_SELECTED) && !(lplv->uNewState&LVIS_SELECTED))
			{
				ResetItemCheckState(lplv->iItem);
			}

		}
#endif
		C32DbgOutNmListView(lplv);

		if (m_OnNotifyItemChanged)
		{
			ZxDebug((__FUNCTION__"():: %ws \n",GetItemText(lplv->iItem, 0)));
			Handle = m_OnNotifyItemChanged(lplv->iItem, lplv->iSubItem, lplv, lResult, this);
		}
	
		
		return Handle;
	}

	virtual BOOL  OnNotifyItemChanging(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		lResult = FALSE;
		LPNMLISTVIEW lplv = (LPNMLISTVIEW)lParam;
		int iSubItem = lplv->iSubItem;
		
		/*lplv->uNewState &= ~LVIS_FOCUSED;
		lplv->uOldState &= ~LVIS_FOCUSED;*/
		//C32DbgOutNmListView(lplv);
		return TRUE;
	}
	

	
	BOOL DeleteItem(int iItem)
	{
		return ListView_DeleteItem(m_Hwnd, iItem);
	}

	BOOL DeleteAllItem()
	{
		return ListView_DeleteAllItems(m_Hwnd);
	}

	VOID Reset()
	{
		DeleteAllItem();
		DeleteAllColumn();
		
	}

	//LVS_EX_CHECKBOXES
	VOID SetItemCheckState(int iItem)
	{
		ListView_SetCheckState((HWND)m_Hwnd, iItem, TRUE);
	}

	VOID ResetItemCheckState(int iItem)
	{
		ListView_SetCheckState((HWND)m_Hwnd, iItem, FALSE);
	}

	/*
		设置所有Item的CheckBox状态为选中

	*/
	VOID SetListCheckState()
	{
		int Count = GetItemCount();

		for(int i = 0; i < Count; i++)
		{
			SetItemCheckState(i);
		}
	}

	VOID ResetListCheckState()
	{
		int Count = GetItemCount();

		for(int i = 0; i < Count; i++)
		{
			ResetItemCheckState(i);
		}
	}

	BOOL  IsCheckBoxStyle()
	{
		DWORD ExStyle = GetExtendedStyle();

		return (ExStyle & LVS_EX_CHECKBOXES ? TRUE :FALSE);
	}
	
	/*
		five different views
	*/
	BOOL SetView(DWORD iView)
	{
		DWORD iSet = ListView_SetView(m_Hwnd, iView);

		return (iSet == 1 ? TRUE : FALSE);
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

		return (BOOL)SendMessage(m_Hwnd, SB_SETPARTS, (WPARAM)Count,(LPARAM)m_Part);
	}

	BOOL SetText(int iPartType, LPWSTR Text)
	{
		return (BOOL)SendMessage(m_Hwnd, SB_SETTEXT, (WPARAM)(iPartType), (LPARAM)Text);
	}

	BOOL SetIcon(int iPart, HICON hIcon)
	{
		return (BOOL)SendMessage(m_Hwnd, SB_SETICON, (WPARAM)iPart, (LPARAM)hIcon);
	}

	COLORREF SetBkColor(COLORREF clrBk = CLR_DEFAULT)
	{
		return (COLORREF)SendMessage(m_Hwnd, SB_SETBKCOLOR, 0, (LPARAM)(COLORREF) clrBk);
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
//SendMessage(*m_List[i], WM_SIZE, wParam, lParam);\

#define C32ContainerCallOnSize()\
		for(size_t i = 0; i < m_List.size(); i++)\
		{										\
			m_List[i]->OnSize(wParam, lParam, lResult);\
		}

class C32Container : public C32Window, public C32MouseEvent
{
public:
	C32Container()
	{
		Init();
	}

	virtual ~C32Container()
	{
		ZxDebugEx((__FUNCTION__"():: m_Hwnd: %p This: %p \n", m_Hwnd,this));
		Destroy();
	}


	static DWORD RegisterClass()
	{
		HCURSOR hCursor	= (HCURSOR)LoadImage(NULL, MAKEINTRESOURCE(OCR_SIZEWE), IMAGE_CURSOR, 0 , 0, LR_SHARED);
		DWORD Atom = RegisterClassEx32(C32_WC_CONTAINTER);

		return Atom;
	}

	static VOID Initialize()
	{
		//注册C32Container类
		RegisterClass();

	}
public:
	
	VOID AddC32Window(C32Window* Window)
	{
		m_List.push_back(Window);
	}
	
	VOID AddC32Child(C32Window* Window)
	{
		m_List.push_back(Window);
	}

	virtual VOID SetVisible(BOOL bVisible = TRUE)
	{
		int Count = (int)m_List.size();
		for(int i = 0; i < Count; i++)
		{
			m_List[i]->SetVisible(bVisible);
		}
		C32Window::SetVisible(bVisible);
	}

	int GetC32WindowCount()
	{
		return (int)m_List.size();
	}

public:
	virtual BOOL CALLBACK OnDrawItem(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		LPDRAWITEMSTRUCT lpdis = (LPDRAWITEMSTRUCT)lParam;
		C32ContainerCallOnXyz(lpdis->hwndItem, OnDrawItem);

		return Handle;
	}

	virtual BOOL CALLBACK OnSize(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		C32ContainerCallOnSize();
		return FALSE;
	}

	virtual BOOL CALLBACK OnContextMenu(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		int xPos, yPos;

		xPos = GET_X_LPARAM(lParam);
		yPos = GET_Y_LPARAM(lParam);

		if (m_OnContextMenu)
			Handle = m_OnContextMenu((HWND)wParam, xPos, yPos, lResult, this);
		
		if (Handle == FALSE)
			Handle = m_Menu.Display(xPos, yPos);

		if (Handle == FALSE)
			C32ContainerCallOnXyz((HWND)wParam, OnContextMenu);

		return Handle;
	}

	virtual BOOL CALLBACK OnNotify(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		LPNMHDR lphdr = (LPNMHDR)lParam;
		C32ContainerCallOnXyz(lphdr->hwndFrom, OnNotify);
		return FALSE;
	}

	virtual BOOL CALLBACK OnCommand(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		if (m_OnCommand)
			Handle = m_OnCommand(wParam, lParam, lResult, this);
		
		if (Handle == FALSE)
		{
			if (C32CommandIsCtrl(wParam) || (PVOID)lParam != NULL)
			{
				C32ContainerCallOnXyz((HWND)lParam, OnCommand);
			}
		}
			
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
	C32Menu            m_Menu;
	BOOL					m_bDeleteList;

public:
	const C32Container(const C32Container& Other)
	{
		*this = Other;
		

	}

	const C32Container& operator=(const C32Container& Other)
	{
		m_Hwnd = Other.m_Hwnd;
		Attach(Other.m_Hwnd);
		m_List = Other.m_List;
		return *this;
	}

};

/*
	为了实现界面位置和大小的改变.
	太复杂，想不明白如何做暂时搁浅。
*/
class C32Layout
{
public:
	C32Layout()
	{
		Init();
	}

	~C32Layout()
	{
		Destroy();
	}

public:
	VOID SetPosSize(int X, int Y, int Cx, int Cy)
	{
		m_Rect.left = X;
		m_Rect.top = Y;
		m_Rect.right = X + Cx;
		m_Rect.bottom = Y + Cy;
	}

public:
	VOID Init()
	{
		SetRectEmpty(&m_Rect);
	}
	
	VOID Destroy()
	{
		//m_LayList.clear();
		//m_LayList.resize(0);
	
	}
public:
	enum Type
	{
		horizontal,
		vertical,
	};

	VOID SetHorizontalLayout()
	{
		m_Type = horizontal;
	}

	VOID SetVerticalLayout()
	{
		m_Type = vertical;
	}

	int GetWidth()
	{
		return C32GetRectWidth(m_Rect);
	}

	int GetHeight()
	{
		return C32GetRectHeight(m_Rect);
	}

	VOID AddLayout(C32Layout& Layout)
	{
		m_LayList.push_back(Layout);
	}

	
	VOID DebugRect()
	{
		C32DbgOutRectPosSize(m_Rect, __FUNCTION__);
	}

	VOID Debug(int K = 0)
	{
		C32String String;

		String += L"";
		for(int i = 0; i < K; i++)
		{
			String += L"    ";
		}

		ZxDebug((__FUNCTION__"()::	%ws {%d, %d, %d,%d} \n", String.GetString(),m_Rect.left, m_Rect.top, m_Rect.right, m_Rect.bottom));
		

		for(size_t i = 0; i < m_LayList.size(); i++)
		{
			m_LayList[i].Debug(K+1);
		}
	}


public:
	Type  m_Type;
	RECT  m_Rect;
	C32Container m_List; //Layout 中的控件
	std::vector<C32Layout> m_LayList;

};

class C32HLayout : public C32Layout
{
public:
	C32HLayout()
	{
		SetHorizontalLayout();
	}

	~C32HLayout()
	{

	}


};

static VOID C32LayoutTest()
{
	C32Layout hLay;
	hLay.SetPosSize(0,0, 200, 200);
	{
		C32Layout hLayTop;
		C32Layout hLayTop1;
		C32Layout hLayTop2;
		hLayTop.SetPosSize(0,0, 200, 50);
		hLayTop1.SetPosSize(0,0, 50, 50);
		hLayTop2.SetPosSize(50,0, 150, 50);
		hLayTop.AddLayout(hLayTop1);
		hLayTop.AddLayout(hLayTop2);



		C32Layout hLayCenter;
		hLayCenter.SetPosSize(0,50, 200, 50);

		C32Layout hLayBottom;
		hLayBottom.SetPosSize(0,100, 200, 100);

		hLay.AddLayout(hLayTop);
		hLay.AddLayout(hLayCenter);
		hLay.AddLayout(hLayBottom);

	}
	
	hLay.Debug();
	


}

class C32TabCtrlEventCallback
{

public:
	C32TabCtrlEventCallback()
	{
		Init();
	}
	
	~C32TabCtrlEventCallback()
	{
		Init();
	}

	VOID Init()
	{
		m_OnNotifySelChange = NULL;
		m_OnNotifySelChanging = NULL;
	}

	VOID SetEventSelectChange(C32_EVENT_CALLBACK_TAB_CTRL_NOTIFY_SELCHANGE Callback)
	{
		m_OnNotifySelChange = Callback;
	}

	VOID SetEventSelectChanging(C32_EVENT_CALLBACK_TAB_CTRL_NOTIFY_SELCHANGE Callback)
	{
		m_OnNotifySelChanging = Callback;
	}

	//Button Control Event
	C32_EVENT_CALLBACK_TAB_CTRL_NOTIFY_SELCHANGE m_OnNotifySelChange; //已经改变
	C32_EVENT_CALLBACK_TAB_CTRL_NOTIFY_SELCHANGE m_OnNotifySelChanging;//将要改变
};

#define TTCtrl_Active(hwnd, bActivate)\
		SendMessage(hwnd, TTM_ACTIVATE, (WPARAM)bActivate, (LPARAM)0L)
	
#define TTCtrl_SetToolInfo(hwnd, lpti)\
			SendMessage(hwnd, TTM_SETTOOLINFO, (WPARAM)0L, (LPARAM)(LPTOOLINFO)lpti)

#define TTCtrl_AddTool(hwnd, lpti)\
			  (BOOL)SendMessage(hwnd, TTM_ADDTOOL, (WPARAM)0L, (LPARAM)(LPTOOLINFO)lpti)
#define TTCtrl_DelTool(hwnd, lpti)\
				SendMessage(hwnd, TTM_DELTOOL, (WPARAM)0L, (LPARAM)(LPTOOLINFO) lpti)
#define TTCtrl_EnumTool(hwnd, iTool,lpti)\
			 (BOOL)SendMessage(hwnd, TTM_ENUMTOOLS, (WPARAM)(UINT) iTool, (LPARAM)(LPTOOLINFO)lpti)

#define TTCtrl_GetBubbleSize(hwnd, lpti)\
			  (DWORD)SendMessage(hwnd, TTM_GETBUBBLESIZE, (WPARAM)0L, (LPARAM)(LPTOOLINFO)lpti)

#define TTCtrl_GetCurTool(hwnd, lpti)\
     (int)SendMessage(hwnd, TTM_GETCURRENTTOOL, (WPARAM)0L, (LPARAM)(LPTOOLINFO)lpti)

#define TTCtrl_GetDelayTime(hwnd, duration)\
     (int)SendMessage(hwnd, TTM_GETDELAYTIME, (WPARAM)(DWORD)duration, (LPARAM)0L)

#define TTCtrl_SetDelayTime(hwnd, duration, time)\
     (int)SendMessage(hwnd, TTM_SETDELAYTIME, (WPARAM)(DWORD)duration, (LPARAM)(DWORD)time)

#define TTCtrl_GetMargin(hwnd, lprc)\
     SendMessage(hwnd, TTM_GETMARGIN, (WPARAM)0L, (LPARAM)(LPRECT) lprc)

#define TTCtrl_SetMargin(hwnd, lprc) \
    SendMessage(hwnd, TTM_SETMARGIN, (WPARAM)0L, (LPARAM)(LPRECT) lprc)

#define TTCtrl_GetMaxTipWidth(hwnd) \
    (int)SendMessage(hwnd, TTM_GETMAXTIPWIDTH, (WPARAM)0L, (LPARAM)0L)

#define TTCtrl_SetMaxTipWidth(hwnd, width) \
    (int)SendMessage(hwnd, TTM_SETMAXTIPWIDTH, (WPARAM)0L, (LPARAM)(int)width)

#define TTCtrl_GetText(hwnd, iChar, lpti)  \
	SendMessage(hwnd, TTM_GETTEXT, (WPARAM)(DWORD)iChar, (LPARAM)(LPTOOLINFO)lpti)

#define TTCtrl_GetTipBkColor(hwnd)\
     (COLORREF)SendMessage(hwnd, TTM_GETTIPBKCOLOR, (WPARAM)0L, (LPARAM)0L)

#define TTCtrl_SetTipBkColor(hwnd, clr)\
     (COLORREF)SendMessage(hwnd, TTM_SETTIPBKCOLOR, (WPARAM)(COLORREF) clr, (LPARAM) 0L)

#define TTCtrl_GetTipTextColor(hwnd)\
     (COLORREF)SendMessage(hwnd, TTM_GETTIPTEXTCOLOR, (WPARAM)0L, (LPARAM)0L)

#define TTCtrl_SetTipTextColor(hwnd, clr)\
     (COLORREF)SendMessage(hwnd, TTM_SETTIPTEXTCOLOR, (WPARAM)(COLORREF) clr, (LPARAM)0L);

#define TTCtrl_GetTitle(hwnd, lpttgt)\
     SendMessage(hwnd, TTM_GETTITLE, (WPARAM)0L, (LPARAM)(PTTGETTITLE)lpttgt)

#define TTCtrl_SetTitle(hwnd, icon, title)\
     (BOOL)SendMessage(hwnd, TTM_SETTITLE, (WPARAM)(int) icon, (LPARAM)(LPCWSTR) title)

#define TTCtrl_GetToolCount(hwnd)\
     (int)SendMessage(hwnd, TTM_GETTOOLCOUNT, (WPARAM)0L, (LPARAM)0L)

#define TTCtrl_GetToolInfo(hwnd, lpti)\
		  (BOOL)SendMessage(hwnd, TTM_GETTOOLINFO, (WPARAM)0L, (LPARAM)(LPTOOLINFO)lpti)

#define TTCtrl_SetToolInfo(hwnd, lpti)\
		  SendMessage(hwnd, TTM_SETTOOLINFO, (WPARAM)0L, (LPARAM)(LPTOOLINFO)lpti)

#define TTCtrl_SetWindowTheme(hwnd, theme)\
     (BOOL)SendMessage(hwnd, TTM_SETWINDOWTHEME , (WPARAM)0L, (LPARAM))(LPCWSTR) theme)

#define TTCtrl_TrackActive(hwnd, bActivate, lpti)\
		SendMessage(hwnd, TTM_TRACKACTIVATE, (WPARAM) bActivate, (LPARAM)(LPTOOLINFO)lpti)

#define TTCtrl_TrackPosition(hwnd, x, y)\
		SendMessage(hwnd, TTM_TRACKPOSITION, (WPARAM) 0, (LPARAM) MAKELONG(x, y))

#define TTCtrl_HitTest(hwnd, lphti)	\
	  (BOOL)SendMessage(hwnd, TTM_HITTEST, (WPARAM)0L, (LPARAM)(LPHITTESTINFO)lphti)

#define TTCtrl_NewToolRect(hwnd, lpti)\
		  SendMessage(hwnd, TTM_NEWTOOLRECT, (WPARAM)0L, (LPARAM)(LPTOOLINFO)lpti)

#define TTCtrl_Pop(hwnd)\
				SendMessage(hwnd, TTM_POP, (WPARAM)0L, (LPARAM)0L)

#define TTCtrl_PopUP(hwnd)\
				SendMessage(hwnd, TTM_POPUP, (WPARAM)0L, (LPARAM)0L)

#define TTCtrl_RelayEvent(hwnd, lpmsg)\
				SendMessage(hwnd, TTM_RELAYEVENT, (WPARAM)0L, LPARAM)(LPMSG) lpmsg)

#define TTCtrl_Update(hwnd)\
				SendMessage(hwnd, TTM_UPDATE , (WPARAM)0L, (LPARAM)0L)

#define TTCtrl_UpdateTipText(hwnd, lpti)\
		  SendMessage(hwnd, TTM_UPDATETIPTEXT, (WPARAM)0L, (LPARAM)(LPTOOLINFO)lpti)

#define TTCtrl_WindowFromPoint(hwnd, lppt)\
		  SendMessage(hwnd, TTM_WINDOWFROMPOINT, (WPARAM)0L, (LPARAM)(LPPOINT)lppt)

 
class C32ToolTipEventCallback
{

public:
	C32ToolTipEventCallback()
	{
		Init();
	}

	~C32ToolTipEventCallback()
	{
		Init();
	}

	VOID Init()
	{
		m_OnNotifyGetDispInfo = NULL;
	}

	
	VOID SetEventGetDispInfo(C32_EVENT_CALLBACK_TOOLTIP_CTRL_NOTIFY_GETDISPINFO Callback)
	{
		m_OnNotifyGetDispInfo = Callback;
	}

	//取得Tip显示的文本
	C32_EVENT_CALLBACK_TOOLTIP_CTRL_NOTIFY_GETDISPINFO m_OnNotifyGetDispInfo;
	
};



class C32ToolTip : public C32Window,  C32ToolTipEventCallback
{
#define C32ToolTipMaxChar 4096
#define C32ToolTipIdIsHwnd(Flag)((Flag & TTF_IDISHWND) == TTF_IDISHWND)
public:
	C32ToolTip()
	{

	}
	
	~C32ToolTip()
	{


	}

	HWND Create(DWORD Style, int xPos, int yPos, int Cx, int Cy, HWND hwnd)
	{
		m_Hwnd = CreateWindow(TOOLTIPS_CLASS, L"C32ToolTip", Style, xPos, yPos,Cx,Cy, hwnd, NULL, C32Hinstance, (LPVOID)this);
		if (m_Hwnd)
			Attach(m_Hwnd);
		ZxDebugEx((__FUNCTION__"():: m_Hwnd: %p This: %p \n", m_Hwnd, this));
		return m_Hwnd;
	}

	/*
		
		hwndCtrlParent ： Handle to the window that contains the tool
		CtrlId ：Application-defined identifier of the tool. If uFlags includes the TTF_IDISHWND flag, uId must specify the window handle to the tool
	*/
	BOOL AddTip(LPCWSTR Text, DWORD Flag,HWND hwndCtrlParent, ULONG_PTR CtrlId, RECT Rect, LPARAM lParam=0L)
	{
		TOOLINFO ti = {};
		ti.cbSize = sizeof(TOOLINFO);
		ti.uFlags = Flag;
		ti.hwnd = hwndCtrlParent;
		ti.hinst = C32Hinstance;
		ti.lParam = lParam;
		ti.lpszText = (LPWSTR)Text;
		ti.uId = (ULONG_PTR)CtrlId;
		ti.rect = Rect;

		BOOL Ret = TTCtrl_AddTool(m_Hwnd, &ti);

		ZxDebugEx((__FUNCTION__"()::Owner : %p Id : %p %d \n", hwndCtrlParent,reinterpret_cast<PVOID>(CtrlId) ,Ret));

		return Ret;

	}

	/*
		控件添加提示
		CtrlId : 控件的hwnd
		hwndCtrlParent:控件的拥有者
	*/
	BOOL AddCtrlTip(LPCWSTR Text, HWND hwndCtrlParent, HWND hwndCtrl, LPARAM lParam=0L)
	{
		DWORD Flag = TTF_SUBCLASS|TTF_IDISHWND;
		RECT Rect = {};
		return AddTip(Text, Flag,hwndCtrlParent, (ULONG_PTR)hwndCtrl, Rect, lParam);
	}
	/*
		给窗口的Client 域中子域添加提示
		hwndCtrl: 窗口的hwnd
	*/
	BOOL AddRectTip(LPCWSTR Text, HWND hwnd, ULONG_PTR TipId,RECT Rect, LPARAM lParam=0L)
	{
		DWORD Flag = TTF_SUBCLASS;

		return AddTip(Text, Flag, hwnd, TipId, Rect, lParam);
	}

	VOID DeleteTip(HWND hwndToolOwner, HWND hwndTool)
	{
		TOOLINFO ti = {};
		ti.cbSize = sizeof(TOOLINFO);
		ti.uFlags = TTF_IDISHWND;
		ti.hwnd = hwndToolOwner;
		ti.uId = (UINT_PTR)hwndTool;

		TTCtrl_DelTool(m_Hwnd, &ti);
	}

	VOID DeleteTip(HWND hwndToolOwner)
	{
		TOOLINFO ti = {};
		ti.cbSize = sizeof(TOOLINFO);
		ti.hwnd = hwndToolOwner;
		TTCtrl_DelTool(m_Hwnd, &ti);

	}

	
	VOID DeleteAllTip()
	{
		TOOLINFO ti = {};
		ti.cbSize = sizeof(TOOLINFO);
		ti.uFlags = TTF_IDISHWND;
		
	}
	
	BOOL EnumTip(int iTip)
	{
		C32String Text;
		Text.AssignStringW(256);

		TOOLINFO ti = {};
		ti.cbSize = sizeof(TOOLINFO);
		ti.lpszText = (LPWSTR)Text;
		return TTCtrl_EnumTool(m_Hwnd, iTip, &ti);
	}

	SIZE GetBubbleSize(LPTOOLINFO lpti)
	{
		SIZE Size = {};
		DWORD dwSize = TTCtrl_GetBubbleSize(m_Hwnd, lpti);
		Size.cx = LOWORD(dwSize);
		Size.cy = HIWORD(dwSize);

		return Size;
	}

	int GetDelayTime(DWORD dwDuration = TTDT_AUTOPOP)
	{
		return TTCtrl_GetDelayTime(m_Hwnd, dwDuration);
	}

	VOID SetDelayTime(DWORD dwDuration, int iTimeMs)
	{
		TTCtrl_SetDelayTime(m_Hwnd, dwDuration, iTimeMs);
	}

	VOID GetMargin(LPRECT Rect)
	{
		TTCtrl_GetMargin(m_Hwnd, &Rect);
	}

	VOID SetMargin(LPRECT Rect)
	{
		TTCtrl_SetMargin(m_Hwnd, &Rect);
	}
	
	int GetMaxTipWidth()
	{
		return TTCtrl_GetMaxTipWidth(m_Hwnd);
	}

	int SetMaxTipWidth(int Width)
	{
		return TTCtrl_SetMaxTipWidth(m_Hwnd, Width);
	}

	VOID GetText(HWND hwndOwer, HWND hwnd, C32String& Text)
	{
		Text.AssignStringW(C32ToolTipMaxChar);
		TOOLINFO ti = {};
		ti.cbSize = sizeof(TOOLINFO);
		ti.hwnd = hwndOwer;
		ti.uId = (ULONG_PTR)hwnd;
		ti.lpszText = Text;

		TTCtrl_GetText(m_Hwnd, 256, &ti);
	}

	VOID GetTitle(PTTGETTITLE Title, C32String& pszTitle)
	{
		RtlZeroMemory(Title, sizeof(TTGETTITLE));
		pszTitle.AssignStringW(C32ToolTipMaxChar);
		Title->cch = C32ToolTipMaxChar;
		Title->pszTitle = pszTitle;
		TTCtrl_GetTitle(m_Hwnd, &Title);
	}

	BOOL SetTitle(int iIcon, LPCWSTR Title)
	{
		return TTCtrl_SetTitle(m_Hwnd, iIcon,Title);
	}

	COLORREF GetTipBkColor()
	{
		return TTCtrl_GetTipBkColor(m_Hwnd);
	}

	COLORREF SetTipBkColor(COLORREF clr)
	{
		return TTCtrl_SetTipBkColor(m_Hwnd, clr);
	}

	COLORREF GetTipTextColor()
	{
		return TTCtrl_GetTipTextColor(m_Hwnd);
	}

	COLORREF SetTipTextColor(COLORREF clr)
	{
		return TTCtrl_SetTipTextColor(m_Hwnd, clr);
	}

	int GetTipCount()
	{
		int Count = TTCtrl_GetToolCount(m_Hwnd);

		return Count;
	}

	BOOL GetTipInfo(LPTOOLINFO lpti)
	{
		return TTCtrl_GetToolInfo(m_Hwnd, lpti);
	}

	VOID SetTipInfo(LPTOOLINFO lpti)
	{
		TTCtrl_SetToolInfo(m_Hwnd, lpti);
	}

	VOID SetTipRect(LPTOOLINFO lpti)
	{
		TTCtrl_NewToolRect(m_Hwnd, lpti);
	}

public:
	void Activate(_In_ BOOL bActivate = TRUE)
	{
		TTCtrl_Active(m_Hwnd, bActivate);
	}

	VOID Hidden()
	{
		TTCtrl_Pop(m_Hwnd);
	}

	VOID Popup()
	{
		TTCtrl_PopUP(m_Hwnd);
	}
	
	VOID TrackActive(BOOL bActive, HWND hwndOwner, ULONG_PTR hwndId)
	{
		TOOLINFO ti = {};
		ti.cbSize = sizeof(TOOLINFO);
		ti.hwnd = hwndOwner;
		ti.uId = hwndId;

		TTCtrl_TrackActive(m_Hwnd, bActive, &ti);
	}

	VOID TrackActive(int xPos, int yPos)
	{
		TTCtrl_TrackPosition(m_Hwnd, xPos, yPos);
	}

	BOOL    OnNotifyShow(WPARAM idTT, LPNMHDR lpnmhdr,LRESULT& lResult)
	{
		ZxDebugEx((__FUNCTION__"():: idTT : %p hwnd: %p \n", (PVOID)idTT, lpnmhdr->hwndFrom));
		return FALSE;
	}

	BOOL    OnNotifyGetDispInfo(LPNMTTDISPINFO lpnmttd,LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		ZxDebugEx((__FUNCTION__"():: Hwnd: %p idFrom: %p lpszText : %p hinst: %p uFlags: 0x%08X lParam : %p \n",
		lpnmttd->hdr.hwndFrom, (PVOID)lpnmttd->hdr.idFrom,lpnmttd->lpszText, lpnmttd->hinst, lpnmttd->uFlags, (PVOID)lpnmttd->lParam));
		lpnmttd->lpszText = L"0123456789\n0123456789\n0123456789\n01234567890123456789012345678901234567890123456789012345678901234567890\n";
		SetMaxTipWidth(150);
		if (m_OnNotifyGetDispInfo)
		{
			BOOL IsRetain = FALSE;
			Handle = m_OnNotifyGetDispInfo(lpnmttd->hdr.idFrom, C32ToolTipIdIsHwnd(lpnmttd->uFlags), &lpnmttd->lpszText, &IsRetain, lResult, this);
			if (IsRetain)
			{
				lpnmttd->uFlags |= TTF_DI_SETITEM;
			}
		}
		
		return Handle;
	}


	virtual BOOL CALLBACK OnNotify(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;

		LPNMHDR lpnm = (LPNMHDR)lParam;

		CHAR* Str = C32DbgGetToolTipCtrlNotifyString(lpnm->code);
		ZxDebugEx((__FUNCTION__"():: %s \n", Str));
		
		switch(lpnm->code)
		{
			case TTN_SHOW:
				Handle = OnNotifyShow(wParam, lpnm, lResult);
				break;
			case  TTN_GETDISPINFO:
				Handle = OnNotifyGetDispInfo((LPNMTTDISPINFO)lParam,lResult);
				break;
			default:
				break;
		}

		return TRUE;
	}
	

	
public:
	operator HWND() const
	{
		return m_Hwnd;
	}

};

class C32TabCtrl : public C32Container , public C32TabCtrlEventCallback
{
public:
	C32TabCtrl()
	{
		m_iCurSel = 0;
		m_ToolTip = NULL;
	}
	
	virtual ~C32TabCtrl()
	{

	}

	HWND Create(DWORD Style, int xPos, int yPos, int Cx, int Cy, HWND hwnd)
	{
		m_Hwnd = CreateWindow(WC_TABCONTROL, L"C32TabCtrl",Style, xPos, yPos, Cx, Cy, hwnd, NULL, C32Hinstance, NULL);
		ZxDebugEx((__FUNCTION__"():: m_Hwnd : %p This: %p\n", m_Hwnd, this));
		if (m_Hwnd)
			Attach(m_Hwnd);

		return m_Hwnd;
	}

	int InsertItem(int iIndex, LPCWSTR Text, int iImage = -1, LPARAM lParam = NULL)
	{
		TCITEM tci = {};
		tci.mask = TCIF_TEXT | TCIF_IMAGE | TCIF_PARAM;
		tci.pszText = (LPWSTR)Text;
		tci.cchTextMax = (int)wcslen(Text);
		tci.iImage = iImage;
		tci.lParam = lParam;

		int Index = TabCtrl_InsertItem(m_Hwnd, iIndex, &tci);
		ZxDebugEx((__FUNCTION__"():: iIndex :%d %ws Index : %d \n",iIndex, Text,Index));
		if (iIndex != -1)
			CreateTabPage();
		return Index;
	} 

	BOOL DeleteItem(int iIndex)
	{
		return TabCtrl_DeleteItem(m_Hwnd, iIndex);
	}
	
	BOOL DeleteAllItems()
	{
		return TabCtrl_DeleteAllItems(m_Hwnd);
	}

	VOID Reset()
	{
		DeleteAllItems();
	}

	int GetCount()
	{
		return TabCtrl_GetItemCount(m_Hwnd);
	}

	//Only tab controls that have the TCS_MULTILINE style can have multiple rows of tabs
	int GetLineCount()
	{
		return TabCtrl_GetRowCount(m_Hwnd);
	}

	int GetCurrentSelect()
	{
		return TabCtrl_GetCurSel(m_Hwnd);
	}

	int SetCurrentSelect(int iIndex)
	{
		if (iIndex < 0 || iIndex >= GetCount())
			return m_iCurSel;
		
		int iSel = TabCtrl_SetCurSel(m_Hwnd, iIndex);
		if (iSel != -1)
		{
			m_iCurSel = iIndex;
		}
		return iSel;
	}

	DWORD SetItemSize(int Cx, int Cy)
	{
		return TabCtrl_SetItemSize(m_Hwnd, Cx, Cy);
	}

	BOOL GetItemRect(int iIndex, LPRECT Rect)
	{
		return TabCtrl_GetItemRect(m_Hwnd, iIndex, Rect);
	}

	int SetMinWidth(int Cx)
	{
		int Cx0 = 0;
		
		Cx0 = TabCtrl_SetMinTabWidth(m_Hwnd, Cx);
		ZxDebugEx((__FUNCTION__"():: MinTabWidth : %d \n", Cx0));

		return Cx0;
	}

	BOOL GetItem(int iIndex, LPTCITEM lptci)
	{
		m_ItemText.AssignStringW(256);
		lptci->mask = TCIF_TEXT | TCIF_IMAGE | TCIF_RTLREADING | TCIF_PARAM | TCIF_STATE;
		lptci->pszText = (LPWSTR)m_ItemText.GetBuffer();
		lptci->cchTextMax = 256;
		return TabCtrl_GetItem(m_Hwnd, iIndex, lptci);
	}

	DWORD SetExtendedStyle(DWORD ExSyle)
	{
		return TabCtrl_SetExtendedStyle(m_Hwnd, ExSyle);
	}

	DWORD GetExtendedStyle()
	{
		return TabCtrl_GetExtendedStyle(m_Hwnd);
	}
	
	VOID SetPadding(int Cx, int Cy)
	{
		return TabCtrl_SetPadding(m_Hwnd, Cx, Cy);
	}
	 
	VOID SetToolTips(HWND hwndTT)
	{
		TabCtrl_SetToolTips(m_Hwnd, hwndTT);
	}

	HWND GetToolTips()
	{
		return TabCtrl_GetToolTips(m_Hwnd);
	}

	HIMAGELIST SetImageList()
	{
		return TabCtrl_SetImageList(m_Hwnd, m_ImageList);
	}

	HIMAGELIST GetImageList()
	{
		return TabCtrl_GetImageList(m_Hwnd);
	}

	VOID AdjustRect(BOOL fLarger, LPRECT Rect)
	{
		TabCtrl_AdjustRect(m_Hwnd, fLarger, Rect);
		
	}

// 消息处理
public:
	virtual BOOL CALLBACK OnSize(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		DWORD Type = (DWORD)wParam;
		int Cx = GET_X_LPARAM(lParam);
		int Cy = GET_Y_LPARAM(lParam);
		RECT rc = {};
		SetRect(&rc, 0, 0, 
			GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)); 
		SetPos(0, 0, Cx, Cy, SWP_NOMOVE|SWP_NOZORDER);
		OnSizeTabPage();
		//AdjustRect(FALSE, rc);
		if (m_OnSize)
		{
			Handle = m_OnSize(Type, Cx, Cy, lResult, this);
		}

		return Handle;
	}

	virtual BOOL CALLBACK OnNotify(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		LPNMHDR lpnmhdr = (LPNMHDR)lParam;
		int iSelItem = GetCurrentSelect();
		ZxDebugEx((__FUNCTION__"():: iSelItem: %d %s \n", iSelItem,C32DbgGetTabCtrlNotifyString(lpnmhdr->code)));
		switch(lpnmhdr->code)
		{
			case TCN_SELCHANGE:
				SetChildVisible(m_iCurSel, FALSE);
				m_iCurSel = iSelItem;
				SetChildVisible(m_iCurSel);
				InvalidateRect(m_Hwnd, NULL, TRUE);
				if (m_OnNotifySelChange)
				{
					Handle = m_OnNotifySelChange(iSelItem, lResult, this);
				}
			break;
			case TCN_SELCHANGING:
				if (m_OnNotifySelChanging)
				{
					Handle = m_OnNotifySelChanging(iSelItem, lResult, this);
				}
				
			break;


		}
		return Handle;
	}

public:
	virtual VOID AddChild(int iIndex, C32Window* Child)
	{
		if ((int)m_ListTab.size() <= iIndex)
			return;
		::SetParent(Child->GetHwnd(), m_ListTab[iIndex]->GetHwnd());
		m_ListTab[iIndex]->AddC32Window(Child);
	}
	
	virtual VOID SetChildVisible(int iIndex, BOOL bVisible = TRUE)
	{
		if ((int)m_ListTab.size() <= iIndex)
			return;
		m_ListTab[iIndex]->SetVisible(bVisible);
		//UpdateWindow(m_List[iIndex]->GetHwnd());
		//m_List[iIndex]->ReflushWindow();
	}

	int GetTabHeigth()
	{
		int Count;
		int RowCount;
		Count = GetCount();
		RowCount = GetLineCount();

		RECT Rect = m_ClientRect;
		AdjustRect(FALSE, &Rect);
		

		return Rect.top;
	}

	RECT GetDisplayRect()
	{
		RECT Rect = m_ClientRect;
		AdjustRect(FALSE, &Rect);

		return Rect;
	}

private:
	RECT GetTabPageRect()
	{
		RECT TabRect = GetDisplayRect();
		
		return TabRect;
	}
	
	VOID CreateTabPage()
	{
		DWORD Style = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS;
		
		RECT Rect = GetTabPageRect();
		C32Container* TabPage  = new C32Container();
		TabPage->Create(0, C32_WC_CONTAINTER, L"TabPage", Style, Rect.left, Rect.top, C32GetRectWidth(Rect), C32GetRectHeight(Rect), m_Hwnd);
		m_ListTab.push_back(TabPage);

	}	

	VOID OnSizeTabPage()
	{
		GetPos();
		RECT Rect = GetTabPageRect();
		for(int i = 0; i < (int)m_ListTab.size(); i++)
		{
			m_ListTab[i]->SetPos(Rect.left, Rect.top, C32GetRectWidth(Rect), C32GetRectHeight(Rect), SWP_NOMOVE|SWP_NOZORDER);
		}
	}

public:
	operator HWND() const
	{
	  return m_Hwnd;
	}

	operator const HWND() const
	{
		return m_Hwnd;
	}

public:
	C32String m_ItemText;
	std::vector<C32Container*> m_ListTab; //每个Tab项中的所对应的控件
	std::vector<C32Menu*> m_ListTabMenu; //每个Tab项中的所对应的控件

	int       m_iCurSel;
public:
	C32ImageList m_ImageList;
	C32ToolTip* m_ToolTip;
};

class C32Dialog : public C32Container, public C32DialogEventCallback
{
	
public:
	static INT_PTR CALLBACK C32DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		ZxDebug((__FUNCTION__"():: uMsg:%s  (%d) wParam: %d lParam: %08d(%d:%d)\n", C32DbgGetWindowMsgString(uMsg),uMsg, wParam,lParam,LOWORD(lParam), HIWORD(lParam)));
		//C32DbgOutWinowsMsgFilter(uMsg, wParam, lParam, __FUNCTION__);
		C32Dialog * This = (uMsg == WM_INITDIALOG ? (C32Dialog*)lParam : (C32Dialog*)GetWindowLongPtr(hwndDlg, GWLP_USERDATA));
		BOOL Handle = FALSE;
		LRESULT lResult = FALSE;
		if (This == NULL)
			return Handle;
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
			case WM_DESTROY: //因为Dialog 不处理WM_NCDESTROY 所以在此函数释放内存.
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
			//case WM_PAINT:
				
			case WM_DRAWITEM:
				Handle = This->OnDrawItem(wParam, lParam, lResult);
				break;
			case WM_PAINT:
				Handle = This->OnPaint(wParam, lParam, lResult);
				break;
				
		}
		return (INT_PTR)Handle;
	}
	static HINSTANCE hInstance;
public:

	C32Dialog()
	{

	}

	virtual ~C32Dialog()
	{


	}

public:
	VOID CloseDialog()
	{
		EndDialog(m_Hwnd, 0);
	}


public:
	BOOL Create(int ResourceId, HWND hwndParent, BOOL bModeless = FALSE)
	{
		INT_PTR Ret = 0;
		if (bModeless == TRUE)
		{
			CreateDialogParam(C32Dialog::hInstance,
				MAKEINTRESOURCE(ResourceId), 
				hwndParent, C32Dialog::C32DialogProc, (LPARAM)this);

		}else
		{
			Ret = DialogBoxParam(C32Dialog::hInstance,
				MAKEINTRESOURCE(ResourceId), 
				hwndParent, C32Dialog::C32DialogProc, (LPARAM)this);

		}
		
		ZxDebugEx((__FUNCTION__"():: m_Hwnd : %p Error %d \n", Ret, GetLastError()));

		return (Ret != NULL);
	}

	

public:
	VOID SetReturnValue(LRESULT lResult)
	{
		 SetWindowLongPtr(m_Hwnd, DWLP_MSGRESULT, lResult);
	}

	VOID Close()
	{
		EndDialog(m_Hwnd, 0);
	}

	virtual VOID Destroy()
	{
		//C32FreeWindowPtrList(m_List);
	}

	DWORD GetSystemFontCxy()
	{
		return GetDialogBaseUnits();
	}

public: // Windows Message
	virtual BOOL CALLBACK OnInitDialog(HWND hwndDlg, UINT uMsg, WPARAM  DefautFocusHwnd, LPARAM InitParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		(hwndDlg),(uMsg),(DefautFocusHwnd),(InitParam);
		lResult = TRUE;
		this->SetUserData();
		Attach(hwndDlg);
		
		if (m_OnInitDialog)
			Handle = m_OnInitDialog(this);
		this->SetCenterPos(this->m_Parent);
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
			HWND HwndControl = (HWND)lParam;
			C32ContainerCallOnXyz(HwndControl, OnCommand);
			if (LOWORD(wParam) == IDCANCEL)
			{
				Close();
				Handle = TRUE;
			}

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

	/*virtual BOOL CALLBACK OnNotify(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		LPNMHDR lpnmh = (LPNMHDR)lParam;
		HWND HwndControl = (HWND)lpnmh->hwndFrom;
		
		for(size_t i = 0; i < m_List.size(); i++)
		{
			if (m_List[i]->GetPtr() == HwndControl)
			{
				Handle = m_List[i]->OnNotify(wParam, lParam, lResult);
				break;
			}
		}

		return Handle;
	}*/

	virtual BOOL CALLBACK OnSize(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		
		for(size_t i = 0; i < m_List.size(); i++)
		{
			m_List[i]->GetPos();
			m_List[i]->m_SizeWindow.cx = GET_X_LPARAM(lParam);
			m_List[i]->m_SizeWindow.cy = GET_Y_LPARAM(lParam);
			POINT Pt = {};
			SIZE  Size={};
			LPWSTR xx = m_List[i]->GetText();
			m_List[i]->CalPosSize(Pt, Size);
			C32DbgOutRect(m_List[i]->m_Rect,"m_Rect");
			C32DbgOutRect(m_List[i]->m_ClientRect,"m_ClientRect");
			
			C32DbgOutRect(m_List[i]->m_Content,"m_Content");
			C32DbgOutRect(m_List[i]->m_Margin, "m_Margin");

			ZxDebug(("%ws : {%d, %d, %d, %d }\n",m_List[i]->GetText(), Pt.x, Pt.y, Size.cx, Size.cy));
			DWORD Flag = SWP_NOZORDER | m_List[i]->m_SwpFlag;
			
			m_List[i]->SetPos(Pt.x, Pt.y, Size.cx, Size.cy, Flag);
			m_List[i]->OnSize(wParam, (LPARAM)MAKELONG(Size.cx, Size.cy), lResult);
		}

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

	virtual BOOL CALLBACK OnPaint(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		lResult = 1;
		SetReturnValue(0);

		return FALSE;
	}
	
	operator HWND() const
	{
		return m_Hwnd;
	}

};

class C32Explorer : public C32Container
{
public:

	static HINSTANCE hInstance;

	static DWORD RegisterClass()
	{
		HCURSOR hCursor	= (HCURSOR)LoadImage(NULL, MAKEINTRESOURCE(OCR_SIZEWE), IMAGE_CURSOR, 0 , 0, LR_SHARED);
		DWORD Atom = RegisterClassEx32(C32_WC_EXPLORER, NULL, hCursor);

		return Atom;
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

	BOOL CALLBACK OnCreate(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = TRUE;
		C32SetHandleLReslut(TRUE, 0);

		LPCREATESTRUCT Cs = (LPCREATESTRUCT)lParam;

		C32Explorer* This = (C32Explorer*)Cs->lpCreateParams;
		Handle = This->OnCreate(Cs);

		return Handle;
	}

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
			TreeRt.left, TreeRt.top, C32GetRectWidth(TreeRt), C32GetRectHeight(TreeRt), 
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
			Rt.left, Rt.top, C32GetRectWidth(Rt), C32GetRectHeight(Rt), 
			(HWND)m_Hwnd);
		m_List.SetSubclass();
		m_List.SetExplorerTheme();

		//m_Tree.SetExtendedStyles();
		return TRUE;
	}

	virtual BOOL CreateStatusCtl()
	{
		DWORD Style3 = WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP | SBARS_TOOLTIPS ;
		m_Status.CreateStatus(0, Style3, (HWND)m_Hwnd);
		m_Status.GetPos();
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
		SetWindowLongPtr(m_Hwnd, GWLP_USERDATA, (LONG_PTR)this);
		return hwnd;
	}

public:
	virtual BOOL OnCreate(LPCREATESTRUCT Cs)
	{
		RECT RcTree = {0, 0, m_Tree.m_Cx, Cs->cy};
		RECT RcList = {m_Tree.m_Cx, 0, Cs->cx - m_Tree.m_Cx, Cs->cy};
		
		CreateTreeCtl(RcTree);
		CreateListCtl(RcList);
		CreateStatusCtl();

		
		AddC32Window(&m_Tree);
		AddC32Window(&m_List.m_Header);
		AddC32Window(&m_List);
		AddC32Window(&m_Status);

		return TRUE;

	}

	virtual BOOL OnDestroy()
	{
		return TRUE;
	}


	virtual BOOL CALLBACK OnSize(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
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
		// m_Tree.m_Hwnd.GetPos();

		// m_List.m_Hwnd.SetPos(m_Tree.m_Hwnd.m_Cx+10,0,Cx - m_Tree.m_Hwnd.m_Cx-10, Cy - m_Status.m_Hwnd.m_Cy);
		// m_List.m_Hwnd.GetPos();
		// 
		// m_Status.m_Hwnd.SetPos(0,m_Tree.m_Hwnd.m_Cy, Cx, m_Status.m_Hwnd.m_Cy);
		// m_Status.m_Hwnd.GetPos();

		//InvalidateRect(m_Hwnd,NULL, TRUE);
		//RedrawWindow(m_Hwnd, )
		HDWP hdwp = BeginDeferWindowPos(3);
		SetPos(0, 0, Cx, Cy);

		DeferWindowPos(hdwp, m_Tree, NULL,0,0,m_Tree.m_Cx, Cy - m_Status.m_Cy, SWP_NOZORDER);
		DeferWindowPos(hdwp, m_List, NULL,m_Tree.m_Cx+10,0,Cx - m_Tree.m_Cx-10, Cy - m_Status.m_Cy, SWP_NOZORDER);
		DeferWindowPos(hdwp, m_Status, NULL,0,Cy-m_Status.m_Cy, Cx, m_Status.m_Cy, SWP_NOZORDER);
		EndDeferWindowPos(hdwp);
		m_List.GetPos();
		m_Status.GetPos();

		GetPos();
		m_Tree.GetPos();

		return Handle;
	}

	virtual BOOL CALLBACK OnLButtonUp(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = TRUE;
		C32SetHandleLReslut(TRUE, 0);

		lResult = 0;
		DWORD Type = (DWORD)wParam;
		int xCursor = GET_X_LPARAM(lParam);
		int yCursor = GET_Y_LPARAM(lParam);
		m_Tree.m_Cx = xCursor;

		SendMessage((HWND)m_Hwnd, WM_SIZE, (WPARAM)-1, (LPARAM)MAKELPARAM(m_ClientCx, m_ClientCy));
		ReleaseCapture();

		return Handle;
	}
	
	//If an application processes this message, it should return zero
	virtual BOOL CALLBACK OnLButtonDown(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		lResult = 0;

		SetCapture(m_Hwnd);
		
		return Handle;
	}


public:
	int m_CxMin; 

public:
	C32TreeView m_Tree;
	C32ListView m_List;
	C32StatusBar m_Status;
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

		}

		return Ret;
	}

	virtual BOOL OnDestroy()
	{
		return TRUE;
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
		Attach(hDialog);
		SetUserData();
		HWND Ok = GetDlgItem(hDialog, IDOK);
		HWND Cancel = GetDlgItem(hDialog, IDCANCEL);
		HWND Progress = GetDlgItem(hDialog, IDC_PROGRESS);

		m_ProBar.Attach(Progress);
		m_ProBar.SetStyle(PBS_MARQUEE| WS_CHILD|WS_VISIBLE);
		m_ProBar.SetMarqueem();
		m_Ok.Attach(Ok);
		m_Cancel.Attach(Cancel);
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

/*
	@brief: 
	对话框包含两个button，一个进度条。
	提供暂停，重启等操作。
*/
class C32SynDialog : public C32Dialog
{
public:
	/*C32SynDialog()
	{

	}	
	*/
	C32SynDialog(LPCWSTR Title = L"任务进度提示", 
				LPCWSTR OkText = L"暂停", 
				LPCWSTR CancelText = L"取消",
				C32_EVENT_CALLBACK_BUTTON_CLICK BtnEventClickOk = NULL,
				C32_EVENT_CALLBACK_BUTTON_CLICK BtnEventClickCancel = NULL,
				C32_EVENT_CALLBACK_BUTTON_CLICK BtnEventClickClose = NULL,
				PVOID Context = NULL)
	{
		m_TitelText = Title;
		m_BtnOkText = OkText;
		m_BtnCancelText = CancelText;
		m_BtnOk.SetEventClick(BtnEventClickOk);
		m_BtnCancel.SetEventClick(BtnEventClickCancel);
		m_BtnClose.SetEventClick(BtnEventClickClose);

		m_Context = Context;
	}


	virtual ~C32SynDialog()
	{

	}

	virtual BOOL CALLBACK OnInitDialog(HWND hwndDlg, UINT uMsg, WPARAM  DefautFocusHwnd, LPARAM InitParam, LRESULT& lResult)
	{
		C32Dialog::OnInitDialog(hwndDlg, uMsg, DefautFocusHwnd, InitParam, lResult);

		//初始化控件
		InitC32Ctrl(hwndDlg);

		SetCenterPos(m_Parent);

		m_Event.Set();

		return TRUE;
	}

	VOID InitC32Ctrl(HWND hwndDlg)
	{
		HWND Ok = GetDlgItem(hwndDlg, IDD_DIALOG_C32_CLASS_PROGRESS_OK);
		HWND Cancel = GetDlgItem(hwndDlg, IDD_DIALOG_C32_CLASS_PROGRESS_CANCEL);
		HWND Close = GetDlgItem(hwndDlg, IDCANCEL);
		HWND Progress = GetDlgItem(hwndDlg, IDC_PROGRESS);

		m_Progress.Attach(Progress);
		m_Progress.SetStyle(PBS_MARQUEE| WS_CHILD|WS_VISIBLE);
		m_Progress.SetMarqueem();

		m_BtnOk.Attach(Ok);
		m_BtnCancel.Attach(Cancel);

		m_BtnOk.SetText(m_BtnOkText);
		m_BtnCancel.SetText(m_BtnCancelText);
		SetText(m_TitelText);

		m_BtnClose.Attach(Close);
		AddC32Window(&m_BtnClose);
		AddC32Window(&m_Progress);
		AddC32Window(&m_BtnOk);
		AddC32Window(&m_BtnCancel);
		AddC32Window(&m_BtnClose);
		
		

	}

	static DWORD WINAPI ThreadCreateDialog(LPVOID Parameter)
	{
		C32SynDialog* This = (C32SynDialog*)Parameter;
		This->Create(IDD_DIALOG_C32CLASS_PROGRESS, NULL);
		return 0;
	}

	BOOL CreateThreadDialog(HWND hwndOwner)
	{
		m_Parent = hwndOwner;
		m_Event.Create(FALSE);
		m_ThreadGui.Create(C32SynDialog::ThreadCreateDialog, this);
		
		//m_Thread.Wait();
		ZxDebugEx((__FUNCTION__"():: Exit \n"));
		return TRUE;
	}

public:
	C32Button  m_BtnOk;
	C32Button  m_BtnCancel;
	C32Button  m_BtnClose;

	C32Progress m_Progress;
	C32String    m_BtnOkText;   
	C32String    m_BtnCancelText;
	C32String    m_TitelText;

	C32SynEvent m_Event;       //事件同步，暂定重启退出...
	C32SynThread m_Thread;     //工作线程。
	C32SynThread m_ThreadGui; //在此线程中创建Dialog
	
	PVOID   m_Context; //同步Dialog关联信息。
};

/*
	@brief: 仅显示一个等待操作对话框，该对话框由代码Create。代码EndDialog。不提供任何点击操作。
	背景:执行某些操作可能需要一段时间，为了确保该操作完成之后用户才能进行下一次操作。所以提供此类。
	使用方法：
		在需要长时间才能完成的函数里直接调用 C32SynSimpleDialog xx;即可
	
	
*/
class C32SynSimpleDialog : public C32SynDialog
{
public:
	virtual BOOL CALLBACK OnInitDialog(HWND hwndDlg, UINT uMsg, WPARAM  DefautFocusHwnd, LPARAM InitParam, LRESULT& lResult)
	{
		C32SynDialog::OnInitDialog(hwndDlg, uMsg, DefautFocusHwnd, InitParam, lResult);
		SetText(L"请耐心等待...");
		m_BtnOk.SetVisible(FALSE);
		m_BtnCancel.SetVisible(FALSE);
		Disable();
		m_Event.Set();
		return TRUE;
	}

	C32SynSimpleDialog()
	{
		CreateThreadDialog(C32Hwnd);
	}

	~C32SynSimpleDialog()
	{
		m_Event.WaitFor();
		CloseDialog();
	}


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
		
		BOOL Handle = FALSE;
		HWND hwndCombo = GetDlgItem(hwndDlg, IDC_DIALOG_SEARCH_COMBO);
		HWND hwndEdit = GetDlgItem(hwndDlg, IDC_DIALOG_SEARCH_EDIT);
		HWND hwndButton = GetDlgItem(hwndDlg, IDC_DIALOG_SEARCH_BUTTON);
		HWND hwndGroup = GetDlgItem(hwndDlg, IDC_DIALOG_SEARCH_GROUP);
		HWND hwndList = GetDlgItem(hwndDlg, IDC_DIALOG_SEARCH_LIST);

		C32Dialog::OnInitDialog(hwndDlg, uMsg, FocusHwnd,InitParam, lResult);
		m_ComboBox.Attach(hwndCombo);
		m_Edit.Attach(hwndEdit);
		m_Button.Attach(hwndButton);
		m_Group.Attach(hwndGroup);
		m_LV.Attach(hwndList);


		m_ComboBox.SetItemHeight(38);
		//m_Button.SetEventClick(OnSearchClick);
		
		m_List.push_back(&m_ComboBox);
		m_List.push_back(&m_Edit);
		m_List.push_back(&m_Button);
		m_List.push_back(&m_LV);
		
		SetText(L"C32查找对话框");
		GetPos();
		SetMinCxy(m_ClientCx, m_ClientCy);
		
		SetCenterPos(GetParent(m_Hwnd));
		if (m_OnInitDialog)
			Handle = m_OnInitDialog(this);

		return Handle;
	}
	 
	

public: // WindowsMessage

	
	virtual BOOL CALLBACK OnSize(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
	
		int Cx = GET_X_LPARAM(lParam);
		int Cy = GET_Y_LPARAM(lParam);
		if (Cx <= m_MinCx && Cy <= m_MinCy)
			return FALSE;
		
		GetPos();
		
		RECT GroupRc = m_Group.GetContentRect();
		m_Group.SetPos(0, 0, Cx - GroupRc.left*2 , m_Group.m_Cy, SWP_NOZORDER | SWP_NOMOVE);
		 GroupRc = m_Group.GetContentRect();
		// combo box 不变
		m_ComboBox.SetPos(0, 0, 0,0, SWP_NOZORDER | SWP_NOMOVE| SWP_NOSIZE);
		RECT CommboRc = m_ComboBox.GetContentRect();

		RECT ButtonRc = m_Button.GetContentRect();
		
		int BtnX = m_ClientRect.right - C32GetRectWidth(ButtonRc) -  GroupRc.left - 10;
		m_Button.GetContentRect();
		m_Button.SetPos(BtnX, ButtonRc.top, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		ButtonRc = m_Button.GetContentRect();

		RECT EditRc = m_Edit.GetContentRect();
		int EditCx = BtnX - EditRc.left -20 ;
		m_Edit.SetPos(0, 0,  EditCx, m_Edit.m_Cy, SWP_NOZORDER | SWP_NOMOVE);

		RECT LvRc = m_LV.GetContentRect();
		
		m_LV.SetPos(0, 0,  m_Group.m_Cx, Cy - LvRc.top-80, SWP_NOZORDER | SWP_NOMOVE);


		return TRUE;
	}

	virtual BOOL CALLBACK OnMove(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		int xPos = GET_X_LPARAM(lParam);
		int yPos = GET_Y_LPARAM(lParam);
		/*if (Cx <= m_MinCx && Cy <= m_MinCy)
			return TRUE;*/
		m_ComboBox.GetPos();
		

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


/*
	打开文件，保存文件对话框
*/

class C32DialogFile
{
public:
	enum eFileDialogType
	{
		FILE_DIALOG_OPEN,
		FILE_DIALOG_SAVE,
	};

public:
	C32DialogFile():m_Type(FILE_DIALOG_OPEN)
	{
		Init();
	}

	C32DialogFile(eFileDialogType Type):
	m_Type(Type)
	{
		Init();
	}

	virtual ~C32DialogFile()
	{

	}

	// OK button, the return value is nonzero
	// cancels or closes the Open dialog box or an error occurs
	//TRUE : Ok
	//FALSE: Cancel or close
	virtual BOOL Show()
	{
		int ret;
		if (m_Type == FILE_DIALOG_OPEN)
		{
			ret = GetOpenFileName(&m_File);
		}else
		{
			ret = GetSaveFileName(&m_File);
		}
		ZxDebug(("m_Path: %ws \n", m_String.GetString()));
		return !!(ret);
	}

	virtual BOOL Show(LPCWSTR Title, LPCWSTR Filter = NULL)
	{
		m_File.lpstrTitle = (LPWSTR)Title;

		m_File.lpstrFilter = (LPWSTR)Filter;
		m_File.nFilterIndex = 1;

		return Show();
	}

	virtual BOOL Open(LPCWSTR Title, LPCWSTR Filter = NULL)
	{
		m_Type = FILE_DIALOG_OPEN;
		return Show(Title, Filter);
	}

	virtual BOOL Save(LPCWSTR Title, LPCWSTR Filter = NULL)
	{
		m_Type = FILE_DIALOG_SAVE;
		return Show(Title, Filter);
	}

	VOID Init()
	{
		m_Filter = NULL;
		RtlZeroMemory(&m_File, sizeof(OPENFILENAME));
		m_String.AssignStringW(8192);

		m_File.lStructSize = sizeof(OPENFILENAMEW);
		m_File.hwndOwner = NULL;
		m_File.nMaxFile = 8192;//这个必须设置，不设置的话不会出现打开文件对话框  
		m_File.lpstrFilter = m_Filter;
		m_File.lpstrFile = (LPWSTR)m_String;
		m_File.nFilterIndex = 1;
		m_File.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER | OFN_NOCHANGEDIR;


	}

public:
	eFileDialogType m_Type;
	OPENFILENAMEW m_File;
	LPCWSTR  m_Filter;
	C32String m_String;
};


typedef struct _C32TSystemMetrics
{
	//LoadIcon 函数只能加载具有SM_CXICON和SM_CYICON指定尺寸的图标
	int SmCxIcon;  //图标的系统大宽度（以像素为单位）。
	int SmCyIcon;  //图标的系统高度（以像素为单位）。

	int SmCxSmIcon; //图标的系统小宽度（以像素为单位）。 小图标通常显示在窗口标题和小图标视图中。
	int SmCySmIcon; //图标的系统小高度（以像素为单位）。 小图标通常显示在窗口标题和小图标视图中.
	//窗口
	int SmCxMin; //窗口的最小宽度（以像素为单位）。
	int SmCyMin; //窗口的最小高度（以像素为单位）。

	int SmCyMinimized;//最小化窗口的高度（以像素为单位）。
	int SmCxMinimized; //最小化窗口的宽度（以像素为单位）


	//主显示监视器
	int SmCyMaximized;//主显示监视器上最大化的顶级窗口的默认高度（以像素为单位）。
	int SmCxMaximized; //主显示监视器上最大化的顶级窗口的默认宽度（以像素为单位）。

	//屏幕
	int SmCxScreen;   //主显示器的屏幕宽度（以像素为单位）。 这是通过调用 GetDeviceCaps 获取的相同值，
	int SmCyScreen;   //主显示器的屏幕高度（以像素为单位）。 这是通过调用 GetDeviceCaps 获取的相同值

	//滚动条
	int SmCxHscroll; //水平滚动条上箭头位图的宽度（以像素为单位）。
	int SmCyHscroll; // 水平滚动条的高度（以像素为单位）

	int SmCxVscroll; //垂直滚动条的宽度（以像素为单位）。
	int SmCyVscroll; //垂直滚动条上箭头位图的高度（以像素为单位）。

	int SmCxHthumb;  //水平滚动条中拇指框的宽度（以像素为单位）。
	int SmCyHthumb;  //垂直滚动条中拇指框的高度（以像素为单位）。

}C32TSystemMetrics, *PC32TSystemMetrics;

extern C32TSystemMetrics C32SystemMetrics;

#define C32DeletePtrInVector(List) \
				{\
					for(size_t i = 0; i < List.size(); i++)\
					{\
						delete List[i];\
						List[i] = NULL;\
					}\
				}

class C32TLvItem
{
public:
	C32TLvItem()
	{
		m_iIcon = 0;
	}
public:
	int m_iIcon;
	CString m_Text;
};

class C32LvItem
{
public:
	std::vector<C32TLvItem> m_List; //所有列项信息。
	int iIndent;
	LPARAM lParam; //要与项关联的值。

	VOID DebugThis()
	{
		CString Str;
		for (int i = 0; i < (int)m_List.size(); i++)
		{
			Str += m_List[i].m_Text + L"##";
		}

		ZxDebug((__FUNCTION__"():: %ws \n", (LPCWSTR)Str));

	}

	CString DebugGetLvItemString()
	{
		CString Str;
		for (int i = 0; i < (int)m_List.size(); i++)
		{
			Str += m_List[i].m_Text + L" ";
		}

		return Str;
	}

};

class C32LvList
{
public:
	C32LvList()
	{

	}
	virtual ~C32LvList()
	{


	}

public:

	int InsertLvItem(int iIndex, C32LvItem& Item)
	{
		if (iIndex > (int)m_List.size())
			return -1;

		std::vector<C32LvItem>::iterator First = m_List.begin();

		m_List.insert(First+iIndex, Item);

		ZxDebug((__FUNCTION__"():: iIndex = %d \n", iIndex));
		return iIndex;

	}

	int  GetLvItem(LPARAM lParam)
	{
		int iIndex = -1;
		for(int i = 0; i < (int)m_List.size(); i++)
		{
			if (m_List[i].lParam == lParam)
			{
				iIndex = i;
				break;
			}
		}
		return iIndex;
	}

	int  RemoveLvItem(LPARAM lParam)
	{
		int iIndex = -1;
		for(int i = 0; i < (int)m_List.size(); i++)
		{
			if (m_List[i].lParam == lParam)
			{
				iIndex = i;
				break;
			}
		}
		CString lvItemString;
		if (iIndex != -1)
		{
			lvItemString = m_List[iIndex].DebugGetLvItemString();
			m_List.erase(m_List.begin() + iIndex);
		}
		ZxDebug((__FUNCTION__"():: iIndex = %d %ws Size: %d\n", iIndex, lvItemString, (int)m_List.size()));

		return iIndex;

	}

	VOID DebugThis()
	{
		for (int i = 0; i < (int)m_List.size(); i++)
		{
			ZxDebug((__FUNCTION__"():: iIndex : %d iIndent : %d  lParam:%p", i, m_List[i].iIndent, m_List[i].lParam));
			m_List[i].DebugThis();

		}
	}

	

public:
	std::vector<C32LvItem> m_List;
};

class C32TreeNode
{
	#define C32TV_EXPANDED   0x00000001
	#define C32TV_COLLAPSE   0x00000000

public:
	C32TreeNode()
	{
		m_Expanded = C32TV_EXPANDED;
		m_Indent = 0;
		m_lParam = (LPARAM)0;
		m_lvList = NULL;
		m_ListView = NULL;
	}

	~C32TreeNode()
	{
		C32DeletePtrInVector(m_Child);
		//DeleteNode();
	}

public:
	C32TreeNode(std::vector<CString> StringList, C32LvList* List, C32ListView* ListView,LPARAM lParam = NULL)
	{
		m_Indent = 0;
		m_ItemString = StringList;
		m_lParam = lParam;
		m_Indent = 32;
		m_lvList = List;
		m_ListView = ListView;
		m_Expanded = C32TV_EXPANDED;
	}

public:

	VOID Insert(std::vector<CString> StringList, LPARAM lParam = NULL)
	{
		//树结构添加节点
		C32TreeNode* Node = new C32TreeNode(StringList,m_lvList, m_ListView, lParam);
		Node->m_Indent = m_Indent + 20;

		//关联的List 插入节点.
		C32LvItem lvItem;
		lvItem.m_List.resize(StringList.size());
		for(int i = 0; i < (int)StringList.size(); i++)
		{
			lvItem.m_List[i].m_Text = StringList[i];
		}
		lvItem.lParam = (LPARAM)Node->GetThis();
		lvItem.iIndent = Node->m_Indent;

		int iIndex = m_lvList->GetLvItem((LPARAM)GetThis());
		if (iIndex == -1)
		{
			iIndex = (int)m_lvList->m_List.size();
		}else
		{
			iIndex += (int)m_Child.size();
			iIndex++;

		}


		//iIndex++;
		m_lvList->InsertLvItem(iIndex, lvItem);
		m_Child.push_back(Node);

		if (m_ListView)
		{
			m_ListView->InsertItemAsyn(iIndex, lvItem.m_List[0].m_Text);
			for(int i = 0; i < (int)lvItem.m_List.size(); i++)
			{
				
			}
		}

		
	}

	C32TreeNode* GetThis()
	{
		return this;
	}

	std::vector<CString>& GetItemString()
	{
		return m_ItemString;
	}

	LPARAM GetlParam()
	{
		return m_lParam;
	}

	std::vector<C32TreeNode*>& GetChild()
	{
		return m_Child;
	}


	int InsertLvList(C32TreeNode* ChildNode, int NodeIndex = -1)
	{
		C32LvItem lvItem;
		lvItem.m_List.resize(ChildNode->m_ItemString.size());
		for(int i = 0; i < (int)ChildNode->m_ItemString.size(); i++)
		{
			lvItem.m_List[i].m_Text = ChildNode->m_ItemString[i];
		}

		lvItem.lParam = (LPARAM)ChildNode;
		lvItem.iIndent = ChildNode->m_Indent;

		int iIndex = m_lvList->GetLvItem((LPARAM)GetThis());
		if (iIndex == -1)
		{
			iIndex = (int)m_lvList->m_List.size();
		}else
		{
			iIndex += NodeIndex;
			iIndex++;
		}

		m_lvList->InsertLvItem(iIndex, lvItem);

		ZxDebug((__FUNCTION__"():: iIndex : %d %ws \n", iIndex,lvItem.DebugGetLvItemString()));

		return iIndex;
	}


	int CollapseChild()
	{
		int Count = 0;
		CollapseChild(Count);

		/*int LvCount = m_ListView->GetItemCount();
		m_ListView->SetItemCountEx( LvCount - Count, LVSICF_NOSCROLL);*/
		return Count;
	}

	VOID CollapseChild(int& Count)
	{
		SetCollapse();
		for (int i = 0; i < (int)m_Child.size(); i++)
		{
			if (m_Child[i]->IsHasChild())
			{
				m_Child[i]->CollapseChild(Count);
			}
			m_Child[i]->SetCollapse();
			{
				C32TreeNode* Node = m_Child[i];
				
				int iIndex = m_lvList->RemoveLvItem((LPARAM)Node);
				m_ListView->DeleteItem(iIndex);
				ZxDebug((__FUNCTION__"():: %ws \n",(LPCWSTR)Node->DebugGetItemString()));
				Count++;
				
			}
		}
		

	}
	
	int ExpanedChild()
	{
		int Count = 0;
		int LvCount111 = m_ListView->GetItemCount();
		ExpanedChild(Count);

		//int LvCount = m_ListView->GetItemCount();
		//m_ListView->SetItemCountEx(Count + LvCount, LVSICF_NOSCROLL);

		return Count;

	}
	
	//包括自身节点
	VOID GetChildCount(int& Count)
	{
		for(int i = 0; i < (int)m_Child.size(); i++)
		{
			if (m_Child[i]->IsHasChild())
			{
				m_Child[i]->GetChildCount(Count);
			}
			Count++;
		}
	}

	int GetChildPartCount(int iIndex1, int iIndex2)
	{
		int Count = 0;
		for(int i = 0; i < (int)m_Child.size(); i++)
		{
			if (iIndex1 <= i && i <= iIndex2)
			{
				m_Child[i]->GetChildCount(Count);
				Count++;
			}

		}

		return Count;

	}
	

	VOID ExpanedChild(int& Count)
	{
		SetExpanded();
		
		for (int i = 0; i < (int)m_Child.size(); i++)
		{
			ZxDebug((__FUNCTION__"():: %ws \n", m_Child[i]->DebugGetItemString()));	
			int iChildIndex = 0;
			if (i != 0)
			{
				iChildIndex = GetChildPartCount(0, i-1);
			}
				
			int iIndex = InsertLvList(m_Child[i], iChildIndex);
			
			m_ListView->InsertItemAsyn(iIndex,m_ItemString[0], -1, (LPARAM)m_Child[i]);
			m_Child[i]->SetExpanded();
			Count++;
			if (m_Child[i]->IsHasChild())
			{
				m_Child[i]->ExpanedChild(Count);

			}
		}

	}

	int DeleteChild()
	{
		int Count = 0;

		DeleteChild(Count);
		
		return Count;
		
	}

	VOID DeleteChild(int& Count)
	{

		for (int i = 0; i < (int)m_Child.size(); i++)
		{
			if (m_Child[i]->IsHasChild())
			{
				m_Child[i]->DeleteChild();

			}else
			{
				C32TreeNode* Node = m_Child[i];
				m_Child.erase(m_Child.begin()+i);
				m_lvList->RemoveLvItem((LPARAM)Node);
				ZxDebug((__FUNCTION__"():: %ws \n",(LPCWSTR)Node->DebugGetItemString()));
				Count++;
				delete Node;
				Node = NULL;
			}
		}

	}

	BOOL IsHasChild()
	{
		return !m_Child.empty();
	}

	BOOL IsExpanded()
	{
		return (m_Expanded&C32TV_EXPANDED);
	}

	VOID SetCollapse()
	{
		m_Expanded = C32TV_COLLAPSE;
	}

	VOID SetExpanded()
	{
		m_Expanded = C32TV_EXPANDED;
	}

	VOID DeleteNode()
	{
		for(int i = 0; i < (int)m_Child.size(); i++)
		{
			if (m_Child[i]->IsHasChild())
			{
				m_Child[i]->DeleteNode();
			}
			ZxDebug((__FUNCTION__"():: %ws \n", m_Child[i]->DebugGetItemString()));
			delete m_Child[i];
			m_Child[i]=NULL;

		}
		m_Child.clear();
	}

public:
	int m_Indent;		//缩进的数量（以像素为单位）
	LPARAM m_lParam;	//要与项关联的值

	std::vector<C32TreeNode*> m_Child;  //子节点
	std::vector<CString>   m_ItemString; //多列文本
	DWORD m_Expanded;
	C32LvList*   m_lvList;
	C32ListView*  m_ListView;
	CString DebugGetItemString()
	{
		CString String;
		for(int i =0; i < (int)m_ItemString.size(); i++)
		{
			String += m_ItemString[i] + L" \t";;
		}

		return String;
	}

	VOID DebugThis()
	{
		ZxDebug((__FUNCTION__"():: %*s iIndent :%8d %ws\n", m_Indent/2," ",m_Indent, DebugGetItemString()));

		if (!m_Child.empty())
		{
			for(int i = 0 ; i < (int)m_Child.size(); i++)
			{
				//ZxDebug((__FUNCTION__"():: %.*s iIndent :%8d %ws\n", m_Child[i]->m_Indent/5, "\t",m_Child[i]->m_Indent, m_Child[i]->DebugGetItemString()));
				m_Child[i]->DebugThis();
			}
		}
	}

	C32TreeNode(const C32TreeNode& Other)
	{
		m_ItemString = Other.m_ItemString;
		m_Child = Other.m_Child;
		m_Indent = Other.m_Indent;
	}

};

class C32TreeTable : public C32Container
{
public:
	 static BOOL  CALLBACK OnNotifyListViewItemChange(int iItem, int iSubItem, LPNMLISTVIEW lpnmlv,LRESULT& lResult, C32ListView* This)
	 {
		if (iItem == -1)
			return TRUE;
		C32TreeTable* Table = (C32TreeTable*)This->GetParentC32Class(); 
		C32TreeNode* Node = (C32TreeNode*)Table->m_List.m_List[iItem].lParam;
		POINT Pt = {};
		if (!(lpnmlv->uNewState& LVIS_SELECTED))
			return TRUE;
		if(Table->m_ListView.GetCursorPos32(Pt))
		{
			RECT rcClose={};
			rcClose.left = Node->m_Indent;
			rcClose.right = rcClose.left + 32;
			if (rcClose.left < Pt.x && Pt.x < rcClose.right)
			{
				ZxDebug((__FUNCTION__"():: 展开按钮 : %ws : %d\n", Node->DebugGetItemString(), iItem));

				if (Node->IsExpanded())
				{
					int DelCount = Node->CollapseChild();
					Node->SetCollapse();
				}else
				{
					int DelCount = Node->ExpanedChild();
					Node->SetExpanded();
				}
				

			}

		}

		return TRUE;
	 }
	 
	 static BOOL  CALLBACK OnNotifyListViewGetDispInfo(int iItem, int iSubItem, NMLVDISPINFO* lpnmdi,LRESULT& lResult, C32ListView* This)
	 {
		 C32ListView* ListView = (C32ListView*)This;
		 C32TreeTable* Table = (C32TreeTable*)This->GetParentC32Class(); 
		
		ZxDebug((__FUNCTION__"():: %d %d \n",iItem, iSubItem));
		if (iItem > (int)Table->m_List.m_List.size() -1)
		{
			ZxDebug((__FUNCTION__"()::Error iItem \n"));
			return FALSE;
		}
		lpnmdi->item.mask = lpnmdi->item.mask|LVIF_DI_SETITEM ;
		if (lpnmdi->item.mask & LVIF_TEXT)
		{
			
			lpnmdi->item.pszText = (LPWSTR)(LPCWSTR)Table->m_List.m_List[iItem].m_List[iSubItem].m_Text;
			lpnmdi->item.cchTextMax = 256;
		}else if (lpnmdi->item.mask & LVIF_IMAGE)
		{
			
		}
		return TRUE;
	 }

	 static BOOL CALLBACK OnNotifyCustomDraw(LPNMLVCUSTOMDRAW lplvcd, LRESULT& lResult, C32ListView* This)
	 {
		return FALSE;
		/* ZxDebug((__FUNCTION__"():: dwItemSpec: %p dwDrawStage: 0x%08x iSubItem: %d dwItemType:0x%08x\n",
						(PVOID)lplvcd->nmcd.dwItemSpec,lplvcd->nmcd.dwDrawStage, lplvcd->iSubItem, lplvcd->dwItemType));
		 */ switch(lplvcd->nmcd.dwDrawStage) {
  
		  case CDDS_PREPAINT:
			  lResult = CDRF_NOTIFYITEMDRAW;
			  break;
		  case CDDS_ITEMPREPAINT:
			  lResult = CDRF_NEWFONT;
			  break;
		  case CDDS_SUBITEM | CDDS_ITEMPREPAINT:
			  lResult = CDRF_NEWFONT; 
			  break;
			     
		  }


		return FALSE;
	 }
	 //
	 static BOOL CALLBACK OnDrawItem(LPDRAWITEMSTRUCT lpdis, LRESULT& lResult, C32ListView* This)
	 {
		C32TreeTable* Table = (C32TreeTable*)This->GetParentC32Class(); 
		C32TreeNode* Node = (C32TreeNode*)Table->m_List.m_List[lpdis->itemID].lParam;
		C32String DbgText = This->GetItemText(lpdis->itemID, 0);
		//ZxDebug(("iItem: %d Text: %ws Indent : %d \n", lpdis->itemID, (LPWSTR)DbgText, Node->m_Indent));
		ZxDebug(("%ws  %ws itemState: 0x%08x itemAction: 0x%08x\n", 
					DbgText.GetString(),
					C32DbgGetStringRect(lpdis->rcItem).GetString(),
					lpdis->itemState, lpdis->itemAction));
		DWORD iState = Node->IsExpanded()?GLPS_OPENED:GLPS_CLOSED;
		int ColumnCount = This->m_Header.GetCount();
		int ColumnWidth = 0;
		RECT rcText = lpdis->rcItem;
		int ArrayClomunWidth = 0;
		
		C32DeviceContext Dc32;

		COLORREF Clr;
		if (ODS_SELECTED & lpdis->itemState)
			Clr = RGB(91, 173, 255);
		else
			Clr = RGB(255, 255, 255);

		HBRUSH hBrush = CreateSolidBrush(Clr);
		Dc32.SetHdc(lpdis->hDC);
		Dc32.SelectBrush32(hBrush);

		FillRect(lpdis->hDC, &lpdis->rcItem, hBrush);
		
		for(int i = 0; i < ColumnCount; i++)
		{
			ColumnWidth = This->GetColumnWidth(i);
			
			RECT rcClose ={};
			if (i == 0)
			{
				C32DrawControl DrawCtrl;
				DrawCtrl.Open(VSCLASS_TREEVIEW);
				SIZE Size={};
				DrawCtrl.GetPartSize(lpdis->hDC, TVP_GLYPH, GLPS_CLOSED, Size);
				SetRect(&rcClose, Node->m_Indent, lpdis->rcItem.top, Node->m_Indent+Size.cx, lpdis->rcItem.bottom);
				if (Node->IsHasChild())
				{
					rcClose.right = rcClose.left + ColumnWidth;
					DrawCtrl.DrawControlSystemStyle(lpdis->hDC, TVP_GLYPH, iState, &rcClose);
				}

				rcText.left += rcClose.right +10;
			}else
			{
				rcText.left = ArrayClomunWidth;
			}
			rcText.right = ArrayClomunWidth + ColumnWidth;
			
			C32String sTextRect = C32DbgGetStringRect(rcText);
			
			CString Text = Table->m_List.m_List[lpdis->itemID].m_List[i].m_Text;
			
			DrawText(lpdis->hDC, Text, Text.GetLength(),&rcText, DT_END_ELLIPSIS);
			ArrayClomunWidth += ColumnWidth;

		}
		DeleteObject((HGDIOBJ)hBrush);
		
		 return FALSE;
	 }


public:
	
	 
	C32TreeTable()
	{

	}

	~C32TreeTable()
	{
		m_RootNode.DeleteNode();
	}

	 BOOL CALLBACK  OnCreate(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	 {
		lResult = 0;
		BOOL Handle = TRUE;
		
		LPCREATESTRUCT lpcs = (LPCREATESTRUCT)lParam;

		DWORD ExStyle = LVS_EX_FULLROWSELECT | LVS_EX_INFOTIP;
		DWORD Style = WS_CHILD | WS_VISIBLE |LVS_REPORT|LVS_OWNERDRAWFIXED|LVS_OWNERDATA;

		C32Window* Pos = C32GetUserClass(lpcs->hwndParent);
		assert(Pos!= NULL);

		HWND hwnd = m_ListView.Create(0, Style, 0, 0, Pos->m_ClientCx, Pos->m_ClientCy, m_Hwnd);
		ZxDebug((__FUNCTION__"()::m_ListView:  %p \n", hwnd));
		if (hwnd == NULL)
		{
			lResult = -1;
			return Handle;
		}

		m_ListView.SetExtendedStyle(ExStyle);
		m_ListView.SetSubclass();
		m_ListView.SetEventItemChanged(OnNotifyListViewItemChange);
		m_ListView.SetEventGetDispInfo(OnNotifyListViewGetDispInfo);
		m_ListView.SetEventCustomDraw(OnNotifyCustomDraw);
		m_ListView.SetEventDrawItem(OnDrawItem);

		m_RootNode.m_ListView = &m_ListView;
		m_RootNode.m_lvList = &m_List;

		AddC32Window(&m_ListView);

		InsertColumn();
		
		return TRUE;
	 }
	 

public:
	VOID InsertRoot(std::vector<CString> StringList,LPARAM lParam)
	{
		m_RootNode.m_ItemString = StringList;
		m_RootNode.m_Indent = 0;
	}

public:
	VOID InsertColumn()
	{
		m_ListView.InsertColumn(0, 0, L"C32TreeTableColumn0", 100);
		m_ListView.InsertColumn(1, 1, L"C32TreeTableColumn1", 100);
		m_ListView.InsertColumn(2, 2, L"C32TreeTableColumn2", 100);

	
	}

public:
	C32TreeNode m_RootNode;
	C32ListView m_ListView;
	C32LvList m_List;
};

VOID C32TreeTableTest(HWND Parent);

VOID C32DialogFileTest();

VOID C32DrawControlTest(HDC hDc);

VOID C32VisualStyleTest(LPCWSTR Class, HDC Hdc);

VOID C32ListBoxTest(HWND Parent);

C32Button* C32ButtonTest();

C32ToolTip* C32ToolTipTest();

VOID C32DialogSearchTest();

C32Explorer* C32ExplorerTest(HWND hWnd);

VOID C32DialogProgressTest(HWND hWnd);

VOID C32StatusBarTest();

VOID InitializeC32Control(HINSTANCE hInstance);

