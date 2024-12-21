// AWin32Frame.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "AWin32Frame.h"
#include "C32Control.h"
#include "C32Control.h"
#include "C32ControlTest.h"
#include "resource.h"
#include "resource1.h"
#include "GdiTest.h"
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE g_hInst;								// current instance
HWND	  g_hwndHome;							// main window
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:

BOOL				InitInstance(HINSTANCE, int);


class CAWin32Frame : public C32Container
{
public:
	CAWin32Frame()
	{

	}
	~CAWin32Frame()
	{


	}

public:
	BOOL OnCommandMenu(WPARAM wParam, LPARAM Param, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		switch(C32CommandMenuId(wParam))
		{
		case ID_C32CONTROL_C32LISTBOX:
			C32ListBoxDialogTest(C32Hwnd);
			Handle = TRUE;
			break;
		case ID_C32CONTROL_C32EXPLORER:
			C32ExplorerDialogTest(C32Hwnd);
			Handle = TRUE;
			break;
		case ID_C32CONTROL_C32PROGRESSDIALOG:
			C32DialogProgressTest(C32Hwnd);
			Handle = TRUE;
			break;
		case ID_C32CONTROL_C32SEARCHDIALOG:
			C32SearchDialogTest(C32Hwnd);
			Handle = TRUE;
			break;
		case ID_C32CONTROL_C32POSSIZEDIALOG:
			C32MoveSizeDialogTest(C32Hwnd);
			Handle = TRUE;
			break;
		case ID_C32CONTROL_C32GDIPLUSHDIALOG:
			C32GdiPlushDialogTest(C32Hwnd);
			Handle = TRUE;
			break;
		case ID_C32CONTROL_C32DRAWCONTROLDIALOG:
			C32DrawControlDialogTest(C32Hwnd);
			Handle = TRUE;
			break;
		case ID_C32CONTROL_C32LISTVIEWDIALOG:
			C32ListViewDialogTest(C32Hwnd);
			Handle = TRUE;
			break;
		case ID_C32CONTROL_C32TREETABLEDIALOG:
			C32TreeTableDialogTest(C32Hwnd);
			Handle = TRUE;
			break;
		case ID_C32CONTROL_C32SYNDIALOG:
			C32SynDialogDialogTest(C32Hwnd);
			Handle = TRUE;
			break;
			
		case ID_C32CONTROL_C32TABCTRLDIALOG:
			C32TabCtrlDialogTest(C32Hwnd);
			Handle = TRUE;
			break;
		case ID_C32CONTROL_C32SYSTEMCOLORDIALOG:
			C32SystemColorDialogTest(C32Hwnd);
			Handle = TRUE;
			break;
		case IDM_ABOUT:
			{
				C32Dialog AboutDiaolg;
				AboutDiaolg.Create(IDD_ABOUTBOX, C32Hwnd);
			}
			break;
		default:
			break;
		}
		
		return Handle;

	}

	BOOL CALLBACK OnCommand(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;

		if (C32CommandIsMenu(wParam) && (PVOID)lParam == NULL)
		{
			Handle = OnCommandMenu(wParam, lParam, lResult);
		}else
		{
			Handle = C32Container::OnCommand(wParam, lParam, lResult);
		}

		return Handle;
	}

	BOOL CALLBACK OnDestroy(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		PostQuitMessage(0);
		return Handle;
	}

	BOOL CALLBACK OnPaint(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		PAINTSTRUCT Ps = {};
		HDC Hdc = BeginPaint(m_Hwnd, &Ps);
		
		//C32VisualStyleTest(VSCLASS_EXPLORERBAR,Hdc);

		EndPaint(m_Hwnd, &Ps);

		return FALSE;
	}


};


int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	setlocale( LC_ALL, "Chinese" );
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_CHECK_ALWAYS_DF| _CRTDBG_LEAK_CHECK_DF);//_CrtDumpMemoryLeaks();
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;
	
	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_AWIN32FRAME, szWindowClass, MAX_LOADSTRING);
	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_AWIN32FRAME));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;
   DebugInitialize();
   InitializeC32Control(hInstance);
   CAWin32Frame* MainFrame = new CAWin32Frame;
   C32MainFrame = MainFrame;
   MainFrame->RegisterClassEx32(szWindowClass, NULL, NULL, NULL, IDC_AWIN32FRAME,  IDI_C32, IDI_C32);

   hWnd = MainFrame->Create(0,szWindowClass, szTitle,WS_OVERLAPPEDWINDOW|WS_VISIBLE,   CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL);
   ZxDebug((__FUNCTION__"():: %p %p \n", hWnd, MainFrame));
     
   if (!hWnd)
   {
      return FALSE;
   }
   C32Hwnd = hWnd;
   
   //C32SynSimpleDialog Dialog;
   //C32TreeTableTest();
   //C32ListBoxTest(hWnd);
   //C32DialogProgressTest(hWnd, hInstance);
	//C32DialogSearchTest();
	C32Explorer* Explorer = C32ExplorerTest(hWnd);
	MainFrame->AddC32Window(Explorer);
	//C32TabCtrl* Tab = C32TabCtrlTest();
	//MainFrame->AddC32Window((C32Window*)Tab);
	//MainFrame->AddC32Window((C32Window*)Tab->m_ToolTip);
	//C32Button* Btn = C32ButtonTest();
	//MainFrame->AddC32Window((C32Window*)Btn);
  /* C32ToolTip* Tip = C32ToolTipTest();
   MainFrame->AddC32Window((C32Window*)Tip);*/

   ShowWindow(hWnd, nCmdShow);

   UpdateWindow(hWnd);
  
  
   return TRUE;
}
