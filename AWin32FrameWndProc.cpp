#include "stdafx.h"
#include "C32Control.h"
#include "C32ControlTest.h"
#include "resource.h"
#include "resource1.h"
#include "GdiTest.h"

extern C32Explorer* g_Exp;
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

static BOOL OnCommandMenu(WPARAM wParam, LPARAM Param, LRESULT& lResult)
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
	case ID_C32CONTROL_C32LISTVIEWDIALOG:
		C32ListViewDialogTest(C32Hwnd);
		Handle = TRUE;
		break;

	case IDM_ABOUT:
		DialogBox(C32Hinstance, MAKEINTRESOURCE(IDD_ABOUTBOX),C32Hwnd, About);
		break;
	default:
		break;
	}

	return Handle;

}

static BOOL  OnCommand(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
{
	BOOL Handle = FALSE;

	if (C32CommandIsMenu(wParam))
	{
		Handle = OnCommandMenu(wParam, lParam, lResult);
	}

	return Handle;
}






LRESULT CALLBACK WndProcFrame(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//C32TreeView* ThisTv = (C32TreeView*)GetWindowLongPtr(hWnd,GWLP_USERDATA);
	//C32ListView* ThisLv = (C32ListView*)GetWindowLongPtr(hWnd,GWLP_USERDATA);
	//C32ListBox* ThisLb = (C32ListBox*)GetWindowLongPtr(hWnd,GWLP_USERDATA);
	C32TreeView* ThisTv = NULL;
	C32ListView* ThisLv = NULL;
	C32ListBox* ThisLb = NULL;
	(ThisLv),(ThisTv),(ThisLb);
	BOOL Handle = FALSE;

	LRESULT lResult;
	PAINTSTRUCT ps;
	HDC hdc;
	switch (message)
	{
	
	case WM_PAINT:
		{
			RECT rcChange = {};
			if(GetUpdateRect(hWnd, &rcChange, FALSE) == 0)
			{
				ZxDebug(("GetUpdateRect Fail \n"));
				return 0;
			}
		
			hdc = BeginPaint(hWnd, &ps);
			C32DbgOutMsgPaint(&ps);
			RECT rcUpdate = {};
			GetUpdateRect(hWnd, &rcUpdate, FALSE);
		
			C32DbgOutRect(rcUpdate, "GetUpdateRect");
			
			//ZxDebug((__FUNCTION__"():: DrawEllipse : Status : %d \n",StatusRet));

			// TODO: Add any drawing code here...
			EndPaint(hWnd, &ps);

			return 0;
			break;
		}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	//case WM_SIZE:   //Left Mouse Button
	//	{
	//		C32Window Win(hWnd);
	//		Win.SetPtr();
	//		//g_Exp->OnSize((DWORD)wParam, Win.m_ClientRect.right, Win.m_ClientRect.bottom);
	//		if (g_Exp)
	//		g_Exp->OnSize((DWORD)wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));

	//	}
	case WM_MEASUREITEM:
			if ((ULONG)wParam != 0)
				if(ThisLb)
					Handle = ThisLb->OnMeasureItem(( LPMEASUREITEMSTRUCT )lParam, lResult);
			break;
	//case WM_DRAWITEM:
	//		ThisLb->OnDrawItem((LPDRAWITEMSTRUCT)lParam, lResult);
	case WM_COMMAND:
		Handle = OnCommand(wParam, lParam, lResult);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	if (Handle == FALSE)
	{
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return lResult;
}
