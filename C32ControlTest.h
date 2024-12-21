#pragma once
#include<locale.h>
#include <string>
#include "stdafx.h"

#include "C32Control.h"
#include "GdiTest.h"

typedef BOOL (CALLBACK* C32_EVENT_ON_CALLBACK_CREATE)(HWND hwndDlg, UINT uMsg, WPARAM  DefautFocusHwnd, LPARAM InitParam, LRESULT& lResult);

class C32ListBoxDialog : public C32Dialog
{
	static BOOL  WINAPI StaticOnClick(DWORD StaticCtrlId, C32Window* This)
	{
		UNREFERENCED_PARAMETER(StaticCtrlId);
		UNREFERENCED_PARAMETER(This);

		ZxDebug((__FUNCTION__"():: This Text: %ws \n",This->GetText()));
		return TRUE;
	}
	
	static BOOL  WINAPI ButtonOnClick(DWORD ButtonCtrlId, C32Button* This)
	{
		UNREFERENCED_PARAMETER(ButtonCtrlId);
		
		UNREFERENCED_PARAMETER(This);
		
		C32ListBoxDialog* Top = (C32ListBoxDialog*)This->GetParentC32Class();

		LPCWSTR SelectString = Top->m_ListBox.GetCurrentSelectString();
		std::wstring Text = L"点击 : ";
		Text += SelectString;
		Top->m_Static.SetText(Text.c_str());
		
		ZxDebug((__FUNCTION__"():: This Text: %ws \n",SelectString));
		return TRUE;
	}

	

public:
	C32ListBoxDialog()
	{

	}
	~C32ListBoxDialog()
	{

	}

public:
	virtual BOOL CALLBACK OnInitDialog(HWND hwndDlg, UINT uMsg, WPARAM  DefautFocusHwnd, LPARAM InitParam, LRESULT& lResult)
	{
	/*	C32Dialog* Base = reinterpret_cast<C32Dialog*>(this);
		Base->OnInitDialog(hwndDlg,  uMsg, DefautFocusHwnd,InitParam, lResult);*/

		
		(hwndDlg),(uMsg),(DefautFocusHwnd),(InitParam);
		HWND hwndListBox = GetDlgItem(hwndDlg, IDC_C32LISTBOXTEST_LIST);
		HWND hwndOk = GetDlgItem(hwndDlg, IDC_C32LISTBOXTEST_OK);
		HWND hwndStatis =  GetDlgItem(hwndDlg, IDC_C32LISTBOXTEST_STATIC);
	
		Attach(hwndDlg);
		m_Button.Attach(hwndOk);
		m_Button.SetEventClick(C32ListBoxDialog::ButtonOnClick);
		m_ListBox.Attach(hwndListBox);
		m_Static.Attach(hwndStatis);
		m_Static.SetEventClick(StaticOnClick);

		//m_ListBox.SetExplorerTheme();
		//m_ListBox.AddStyle(LBS_MULTIPLESEL);
		AddC32Window(&m_ListBox);
		AddC32Window(&m_Button);
		AddC32Window(&m_Static);

		for(int i =0; i < 13; i++)
		{
			int index = m_ListBox.AddString(L"福州");
			int index1= m_ListBox.AddString(L"泉州");
			int index2= m_ListBox.AddString(L"厦门");
			int index3= m_ListBox.AddString(L"漳州");

		}
		
		m_ListBox.SetItemHeight(32);
		for(int i =0; i < 4; i++)
		{
			C32String String;

			m_ListBox.GetString(i, String);
			
			ZxDebug(("%ws \n", (LPWSTR)String.GetBuffer()));

		}

		SetCenterPos();
		
		lResult = TRUE;
		return FALSE;
	}


	C32ListBox m_ListBox;
	C32Button  m_Button;
	C32Static  m_Static;
	
};

class C32ListViewDialog : public C32Dialog
{
	
	static BOOL  WINAPI ButtonOnClick(DWORD ButtonCtrlId, C32Button* This)
	{
		UNREFERENCED_PARAMETER(ButtonCtrlId);
		
		UNREFERENCED_PARAMETER(This);
		
		C32ListViewDialog* Top = (C32ListViewDialog*)This->GetParentC32Class();

		LPCWSTR SelectString = Top->m_ComboBox.GetCurrentSelectString();
		if (SelectString)
		{	
			if(wcscmp(SelectString, L"Icon view") == 0)
			{
				Top->m_ListView.SetView(LV_VIEW_ICON );
			}else if(wcscmp(SelectString, L"Small icon view") == 0)
			{
				Top->m_ListView.SetView(LV_VIEW_SMALLICON  );
				
			}else if(wcscmp(SelectString, L"List view") == 0)
			{
				Top->m_ListView.SetView(LV_VIEW_LIST);

			}else if(wcscmp(SelectString, L"Detail View") == 0)
			{
				Top->m_ListView.SetView(LV_VIEW_DETAILS);

			}else if(wcscmp(SelectString, L"Tile View") == 0)
			{
				Top->m_ListView.SetView(LV_VIEW_TILE);

			}
		}
		ZxDebug((__FUNCTION__"():: This Text: %ws \n",SelectString));
		return TRUE;
	}

	

public:
	C32ListViewDialog()
	{

	}
	~C32ListViewDialog()
	{

	}

public:
	virtual BOOL CALLBACK OnInitDialog(HWND hwndDlg, UINT uMsg, WPARAM  DefautFocusHwnd, LPARAM InitParam, LRESULT& lResult)
	{
	/*	C32Dialog* Base = reinterpret_cast<C32Dialog*>(this);
		Base->OnInitDialog(hwndDlg,  uMsg, DefautFocusHwnd,InitParam, lResult);*/

		C32Dialog::OnInitDialog(hwndDlg, uMsg, DefautFocusHwnd, InitParam, lResult);
		(hwndDlg),(uMsg),(DefautFocusHwnd),(InitParam);
		HWND hwndListView = GetDlgItem(hwndDlg, IDC_C32LISTVIEW_TEST_LIST);
		HWND hwndComboBox =  GetDlgItem(hwndDlg, IDC_C32LISTVIEW_TEST_COMBO);
		HWND hwndOk = GetDlgItem(hwndDlg, IDC_C32LISTVIEW_TEST_OK);
		HWND hwndCancel = GetDlgItem(hwndDlg, IDCANCEL);

		Attach(hwndDlg);
		m_Button.Attach(hwndOk);
		m_Button.SetEventClick(C32ListViewDialog::ButtonOnClick);
		m_ButtonCancel.Attach(hwndCancel);
		m_ListView.Attach(hwndListView);
		m_ComboBox.Attach(hwndComboBox);
		
		m_ListView.SetNoMoveRightBottom();
		m_ComboBox.SetNoSizeLeftBottom();

		m_Button.SetNoSizeRightBotton();
		m_ButtonCancel.SetNoSizeRightBotton();

		AddC32Window(&m_ListView);
		AddC32Window(&m_ComboBox);
		AddC32Window(&m_Button);
		AddC32Window(&m_ButtonCancel);

		m_ListView.SetExplorerTheme();
		m_ListView.m_ImageListNormal.Create(64, 64, ILC_COLOR32);
		m_ListView.m_ImageListNormal.AddIcon(IDI_EXPLORER);
		m_ListView.m_ImageListNormal.AddIcon(IDI_RED_CHECK);
		m_ListView.m_ImageListSmall.Create(32, 32, ILC_COLOR32);
		m_ListView.m_ImageListSmall.AddIcon(IDI_EXPLORER);
		m_ListView.m_ImageListSmall.AddIcon(IDI_RED_CHECK);
		m_ListView.SetImageList();
		m_ListView.InsertItem(0, L"Explorer", 0);
		m_ListView.InsertItem(1, L"ReadCheck", 1);
		m_ListView.InsertItem(2, L"Explorer", 0);
		m_ListView.InsertItem(3, L"ReadCheck", 1);
		m_ListView.InsertItem(4, L"Explorer", 0);
		m_ListView.InsertItem(5, L"ReadCheck", 1);

		int index = m_ComboBox.AddString(L"Icon view");
		int index1= m_ComboBox.AddString(L"Small icon view");
		int index2= m_ComboBox.AddString(L"List view");
		int index3= m_ComboBox.AddString(L"Tile View");
		int index4= m_ComboBox.AddString(L"Detail View");
		
		m_ComboBox.SelectItemString(L"Icon view");	
		//m_ComboBox.SetItemHeight(48);
		

		lResult = TRUE;
		return FALSE;
	}


	C32ListView m_ListView;
	C32Button  m_Button;
	C32Button  m_ButtonCancel;

	C32ComboBox  m_ComboBox;
	
};

class C32TreeTableDialog : public C32Dialog
{
	
public:
	C32TreeTableDialog()
	{

	}
	~C32TreeTableDialog()
	{

	}

public:
	virtual BOOL CALLBACK OnInitDialog(HWND hwndDlg, UINT uMsg, WPARAM  DefautFocusHwnd, LPARAM InitParam, LRESULT& lResult)
	{
		
		setlocale(LC_ALL, "Chinese");
		C32Dialog::OnInitDialog(hwndDlg, uMsg, DefautFocusHwnd, InitParam,lResult);
		
		C32TreeTable* Table; 
		m_Table = new C32TreeTable;
		Table =m_Table;
		Table->RegisterClassEx32(L"C32TreeTable");

		C32Container* Pos = (C32Container*)C32GetUserClass(hwndDlg);

		Table->Create(0, L"C32TreeTable", L"C32TreeTable", WS_CHILD|WS_VISIBLE, 0, 0, Pos->m_ClientCx,Pos->m_ClientCy, hwndDlg);
		//Pos->AddC32Window(Table);

		std::vector<CString> Items;

		Items.push_back(L"中国");
		Items.push_back(L"景点");
		Items.push_back(L"评级");

		typedef LPCWSTR LPWSTRA3[3];

		LPWSTRA3 Detail[] =
		{ 
			{L"北京", L"故宫", L"AAAAA"},
			{L"天津", L"码头", L"AAAA"},
			{L"上海", L"东方明珠", L"AAAAA"},
			{L"重庆", L"洪崖洞", L"AAAAA"},
		};
		Table->InsertRoot(Items, NULL);
		for(int i = 0; i < 3; i++)
		{
			std::vector<CString> Item;

			Item.push_back(Detail[i][0]);
			Item.push_back(Detail[i][1]);
			Item.push_back(Detail[i][2]);

			Table->m_RootNode.Insert(Item);

		}
		LPWSTRA3 DiDu[] = 
		{
			{L"海淀区", L"中坞公园",   L"AAAA"},
			{L"西城区", L"白云观",	    L"AAAAAAA+"},
			{L"延庆区", L"八达岭长城", L"AAAA"},
		};
		for(int i = 0; i < 3; i++)	
		{
			std::vector<CString> Item;

			Item.push_back(DiDu[i][0]);
			Item.push_back(DiDu[i][1]);
			Item.push_back(DiDu[i][2]);

			Table->m_RootNode.m_Child[0]->Insert(Item);

		}

		LPWSTRA3 West[] = 
		{
			{L"帝都大观园", L"AAAAA", L"门票便宜"},
			{L"陶然亭公园", L"AAAAA", L"门票便宜"},
			{L"恭王府花园", L"AAAAA", L"没去过"},
		};
		for(int i = 0; i < 3; i++)	
		{
			std::vector<CString> Item;

			Item.push_back(West[i][0]);
			Item.push_back(West[i][1]);
			Item.push_back(West[i][2]);

			Table->m_RootNode.m_Child[0]->m_Child[1]->Insert(Item);

		}


		Table->m_RootNode.DebugThis();

		Table->m_List.DebugThis();

		
		AddC32Window(Table);

		return TRUE;
	}


	C32TreeTable* m_Table;
	
};

class C32ExplorerDialog : public C32Dialog
{
	static BOOL  WINAPI StaticOnClick(DWORD StaticCtrlId, LRESULT& lResult, C32Window* This)
	{
		UNREFERENCED_PARAMETER(StaticCtrlId);
		UNREFERENCED_PARAMETER(lResult);
		UNREFERENCED_PARAMETER(This);

		ZxDebug((__FUNCTION__"():: This Text: %ws \n",This->GetText()));
		return TRUE;
	}
	
	static BOOL  WINAPI ButtonOnClick(DWORD ButtonCtrlId, LRESULT& lResult, C32Window* This)
	{
		UNREFERENCED_PARAMETER(ButtonCtrlId);
		UNREFERENCED_PARAMETER(lResult);
		UNREFERENCED_PARAMETER(This);

		C32ListBoxDialog* Top = (C32ListBoxDialog*)This->GetParentC32Class();

		LPCWSTR SelectString = Top->m_ListBox.GetCurrentSelectString();
		std::wstring Text = L"点击 : ";
		Text += SelectString;
		Top->m_Static.SetText(Text.c_str());
		
		ZxDebug((__FUNCTION__"():: This Text: %ws \n",SelectString));
		return TRUE;
	}


public:
	C32ExplorerDialog()
	{
		m_Explorer = NULL;
	}
	~C32ExplorerDialog()
	{

	}

public:

	static BOOL WINAPI OnListCommandMenu(DWORD CtrlId, LRESULT& lResult, C32Window* This)
	{
		lResult = 0;

		C32ListView* List = reinterpret_cast<C32ListView*>(This);

		LPCWSTR String = List->m_Menu.GetSubItemString(CtrlId);

		ZxDebug((__FUNCTION__"():: Click : %ws \n", String));
		return TRUE;
	}

	static BOOL WINAPI OnTreeCommandMenu(DWORD CtrlId, LRESULT& lResult, C32Window* This)
	{
		lResult = 0;

		C32TreeView* List = reinterpret_cast<C32TreeView*>(This);

		LPCWSTR String = List->m_Menu.GetSubItemString(CtrlId);

		ZxDebug((__FUNCTION__"():: Click : %ws \n", String));
		return TRUE;
	}
	
	virtual BOOL CALLBACK OnInitDialog(HWND hwndDlg, UINT uMsg, WPARAM  DefautFocusHwnd, LPARAM InitParam, LRESULT& lResult)
	{
	/*	C32Dialog* Base = reinterpret_cast<C32Dialog*>(this);
		Base->OnInitDialog(hwndDlg,  uMsg, DefautFocusHwnd,InitParam, lResult);*/

		m_Explorer =C32ExplorerTest(hwndDlg);
		m_Explorer->m_List.SetEventCommandMenu(OnListCommandMenu);
		m_Explorer->m_Tree.SetEventCommandMenu(OnTreeCommandMenu);
		Attach(hwndDlg);
		AddC32Window(m_Explorer);
		
		lResult = TRUE;
		return FALSE;
	}

	virtual BOOL CALLBACK OnSize(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		m_Explorer->OnSize(wParam, lParam, lResult);
		return FALSE;
	}

public:
	C32Explorer* m_Explorer;
	
};

class C32MoveSizeDialog : public C32Dialog
{
	
public:
	C32MoveSizeDialog()
	{

	}
	~C32MoveSizeDialog()
	{

	}

public:
	virtual BOOL CALLBACK OnInitDialog(HWND hwndDlg, UINT uMsg, WPARAM  DefautFocusHwnd, LPARAM InitParam, LRESULT& lResult)
	{
	/*	C32Dialog* Base = reinterpret_cast<C32Dialog*>(this);
		Base->OnInitDialog(hwndDlg,  uMsg, DefautFocusHwnd,InitParam, lResult);*/

		Attach(hwndDlg);
		(hwndDlg),(uMsg),(DefautFocusHwnd),(InitParam);
		HWND hwndStatic1 = GetDlgItem(hwndDlg, IDC_MOVE_SIZE_STATIC_TOP);
		HWND hwndButton1 = GetDlgItem(hwndDlg, IDC_MOVE_SIZE_BUTTON1);
		HWND hwndEdit1 =  GetDlgItem(hwndDlg, IDC_MOVE_SIZE_EDIT1);
		HWND hwndButton2 = GetDlgItem(hwndDlg, IDC_MOVE_SIZE_BUTTON2);
		HWND hwndList = GetDlgItem(hwndDlg, IDC_MOVE_SIZE_LIST1);

		HWND hwndOk = GetDlgItem(hwndDlg, IDOK);
		HWND hwndCancel = GetDlgItem(hwndDlg, IDCANCEL);
		

		m_Static.Attach(hwndStatic1);
		m_Button1.Attach(hwndButton1);
		m_Edit1.Attach(hwndEdit1);
		m_Button2.Attach(hwndButton2);
		m_ButtonOK.Attach(hwndOk);
		m_ButtonCancel.Attach(hwndCancel);
		m_Lv.Attach(hwndList);
		
		m_Static.SetNoHeigthRight();
		m_Button1.SetNoSizeLeftTop();
		m_Edit1.SetNoHeigthRight();
		m_Button2.SetNoSizeRightTop();

		m_Lv.SetNoMoveRightBottom();
		m_ButtonCancel.SetNoSizeRightBotton();
		m_ButtonOK.SetNoSizeRightBotton();
		

		AddC32Window(&m_Static);
		AddC32Window(&m_Button1);
		AddC32Window(&m_Edit1);
		AddC32Window(&m_Button2);
		AddC32Window(&m_Lv);
		AddC32Window(&m_ButtonOK);	
		AddC32Window(&m_ButtonCancel);
			
		
		
		
		lResult = TRUE;
		return FALSE;
	}


	C32Static m_Static;
	C32Button m_Button1;
	C32Edit   m_Edit1;
	C32Button m_Button2;
	C32ListView m_Lv;
	C32Button m_ButtonOK;
	C32Button m_ButtonCancel;
	

	
};

class C32SearchDialog : public C32DialogSearch
{
public:
	static BOOL  WINAPI SearchOnClick(DWORD StaticCtrlId, C32Button* This)
	{
		UNREFERENCED_PARAMETER(StaticCtrlId);
		UNREFERENCED_PARAMETER(This);
		C32DialogSearch* Top = (C32DialogSearch*)This->GetParentC32Class();

		LPCWSTR SelectString = Top->m_ComboBox.GetCurrentSelectString();
		LPWSTR  EditString = Top->m_Edit.GetText();
		ZxDebug((__FUNCTION__"()::Combobox Select String: %ws Edit: %ws\n",SelectString, EditString));
		
		return TRUE;
	}

	static BOOL WINAPI OnInitDialogEvent(C32Dialog* ThisDialog)
	{
		C32SearchDialog* This= reinterpret_cast<C32SearchDialog*>(ThisDialog);
		
		This->m_Button.SetEventClick(SearchOnClick);
		This->InitComboBox();
		This->m_Edit.SetText(L"456");
		return TRUE;
	}
public:
	C32SearchDialog()
	{
		SetEventDialogInit(C32SearchDialog::OnInitDialogEvent);
		
	}
	~C32SearchDialog()
	{

	}
public:
	virtual BOOL InitComboBox()
	{
		m_ComboBox.Add(L"123");
		m_ComboBox.Add(L"456");	
		m_ComboBox.Add(L"789");	

		m_ComboBox.SelectItem(0);

		return TRUE;
	} 

};

class C32GdiPlusDialog : public C32Dialog
{

public:
	C32GdiPlusDialog()
	{

	}
	~C32GdiPlusDialog()
	{

	}

public:
	virtual BOOL CALLBACK OnInitDialog(HWND hwndDlg, UINT uMsg, WPARAM  DefautFocusHwnd, LPARAM InitParam, LRESULT& lResult)
	{
		C32Dialog::OnInitDialog(hwndDlg, uMsg, DefautFocusHwnd, InitParam, lResult);
		lResult = TRUE;
		return FALSE;
	}

	virtual BOOL CALLBACK OnPaint(WPARAM  wParam, LPARAM lParam, LRESULT& lResult)
	{
		PAINTSTRUCT  Ps;
		RECT rcUpdate = {};
		HDC  Hdc;
		//没有更新域
		if (GetUpdateRect(this->m_Hwnd, &rcUpdate, TRUE) == 0)
			return FALSE;
		Hdc = BeginPaint(this->GetWindow(), &Ps);

		Example_GdiTest(Hdc);

		EndPaint(this->GetWindow(), &Ps);

		lResult = TRUE;
		return FALSE;
	}

};

class C32DrawControlDialog : public C32Dialog
{
	static BOOL  CALLBACK TabOnNotifySelChange(int iSelectItem, LRESULT& lResult, C32TabCtrl* This)
	 {
		C32DrawControlDialog* Top = (C32DrawControlDialog*)This->GetParentC32Class();
		
		Top->GetPos();
		This->GetPos();
		RECT InvRect = {};
		InvRect.right = Top->m_ClientRect.right;
		InvRect.top = This->m_ClientRect.bottom;
		InvRect.bottom = Top->m_ClientRect.bottom;
		InvalidateRect(Top->GetHwnd(), &InvRect, TRUE);

		return TRUE;
	 }

public:
	C32DrawControlDialog()
	{
		static LPWSTR TabString[] = {L"BUTTON", L"CLOCK", L"COMBOBOX", L"COMMUNICATIONS", L"CONTROLPANEL", L"DATEPICKER", L"DRAGDROP", L"EDIT", L"EXPLORERBAR", L"FLYOUT", L"GLOBALS",\
		 L"HEADER" ,L"LISTBOX" ,L"LISTVIEW", L"MENU",L"MENUBAND", L"PAGE", L"PROGRESS", L"REBAR", L"SCROLLBAR", L"SEARCHEDITBOX", L"SPIN", L"STARTPANEL", L"STATUS", \
		 L"TAB", L"TASKBAND", L"TASKBAR", L"TASKDIALOG", L"TEXTSTYLE", L"TOOLBAR", L"TOOLTIP", L"TRACKBAR", L"TRAYNOTIFY",L"TREEVIEW",L"WINDOW", NULL};
		m_TabString = (LPCWSTR*)TabString;
	}
	
	~C32DrawControlDialog()
	{

	}

public:
	virtual BOOL CALLBACK OnInitDialog(HWND hwndDlg, UINT uMsg, WPARAM  DefautFocusHwnd, LPARAM InitParam, LRESULT& lResult)
	{
		C32Dialog::OnInitDialog(hwndDlg, uMsg, DefautFocusHwnd, InitParam, lResult);
		
		HWND hwndTab = GetDlgItem(hwndDlg, IDC_C32DRAWCONTROL_TEST_TAB);
		m_Tab.Attach(hwndTab);
		m_Tab.SetNoHeigthRight();
		InitTab();
		m_Tab.SetEventSelectChange(TabOnNotifySelChange);

		AddC32Child(&m_Tab);
		lResult = TRUE;

		return FALSE;
	}

	virtual BOOL CALLBACK OnPaint(WPARAM  wParam, LPARAM lParam, LRESULT& lResult)
	{
		PAINTSTRUCT  Ps;
		RECT rcUpdate = {};
		HDC  Hdc;
		int iSel = m_Tab.GetCurrentSelect();
		ZxDebugEx((__FUNCTION__"():: %ws : Tab : %ws\n", this->GetText(), m_TabString[iSel]));
		//return FALSE;
		
		//没有更新域
		if (GetUpdateRect(this->m_Hwnd, &rcUpdate, TRUE) == 0)
			return FALSE;
		

		Hdc = BeginPaint(m_Hwnd, &Ps);
		//DefWindowProc(m_Hwnd, WM_PAINT, wParam, lParam);

		C32VisualStyleTest(m_TabString[iSel],Hdc);

		EndPaint(m_Hwnd, &Ps);

		lResult = TRUE;
		return TRUE;
	}

	VOID  InitTab()
	{
		LPCWSTR*  Strings = m_TabString;
		LPCWSTR  TabText = *Strings;
		int iIndex = 0;
		do 
		{
			m_Tab.InsertItem(iIndex, TabText);
			iIndex++;
		} while ((TabText = *++Strings) != NULL);
	}

public:
	C32TabCtrl  m_Tab;

	LPCWSTR*     m_TabString;
};

class C32SynDialogDialog : public C32SynDialog
{
public:
	static BOOL CALLBACK BtnEventClickOk(DWORD CtrlId, C32Button* This)
	{
		C32SynDialogDialog* Dialog = (C32SynDialogDialog*)This->GetParentC32Class();
		ZxDebugEx((__FUNCTION__"():: \n"));
		return TRUE;
	}

	static BOOL CALLBACK BtnEventClickCancel(DWORD CtrlId, C32Button* This)
	{
		C32SynDialogDialog* Dialog = (C32SynDialogDialog*)This->GetParentC32Class();
		
		ZxDebugEx((__FUNCTION__"():: \n"));		
		return TRUE;
	}
	
	static BOOL CALLBACK BtnEventClickClose(DWORD CtrlId, C32Button* This)
	{
		C32SynDialogDialog* Dialog = (C32SynDialogDialog*)This->GetParentC32Class();
		C32Window* Owner = C32GetUserClass(Dialog->m_Parent);
		Owner->Enable();
		
		ZxDebugEx((__FUNCTION__"():: \n"));		
		return TRUE;
	}

	VOID  Destroy()
	{
		delete this;
	}

public:
	C32SynDialogDialog()
	{
		m_BtnOk.SetEventClick(BtnEventClickOk);
		m_BtnCancel.SetEventClick(BtnEventClickCancel);
		m_BtnClose.SetEventClick(BtnEventClickClose);

	}
	
	virtual ~C32SynDialogDialog()
	{

	}




};

class C32TabCtrlDialog : public C32Dialog
{
	static BOOL CALLBACK TabOnInitDialog  (C32Dialog* This)
	{
		C32TabCtrlDialog* Tcl = (C32TabCtrlDialog*)This;
		Tcl->m_HwndMain = This->GetHwnd();
		Tcl->InitTabCtrl();
		Tcl->Tab->SetNoMoveRightBottom();
		This->AddC32Window(Tcl->Tab);
		return TRUE;
	}
	
	static BOOL CALLBACK TabOnCommand(WPARAM wParam, LPARAM lParam, LRESULT& lResult, C32Window* This)
	{
		C32TabCtrl* Tab = (C32TabCtrl*)This->GetParentC32Class();
		int iSel = Tab->GetCurrentSelect();
		C32String MenuString;
		if(C32CommandIsMenu(wParam)&& lParam == NULL)
		{
			int CommandId = C32CommandMenuId(wParam);
			MenuString = Tab->m_ListTab[iSel]->m_Menu.GetSubItemString(CommandId);
			Tab->m_ListTab[iSel]->m_Menu.SelectSubMenuItem(CommandId);
			ZxDebugEx((__FUNCTION__"():: Click Menu : %ws \n", (LPCTSTR)MenuString));

			return TRUE;
		}else
		{
			C32Window* Cmm = C32GetUserClass((HWND)lParam);
			ZxDebugEx((__FUNCTION__"():: Cmm : %ws \n", Cmm->GetText()));
		}

		return FALSE;

	}

public:
	C32TabCtrlDialog()
	{
		Init();
		SetEventDialogInit(TabOnInitDialog);
	}

	~C32TabCtrlDialog()
	{


	}

public:
	VOID Init()
	{
		m_HwndMain = C32Hwnd;
		Tab = new C32TabCtrl();
		Tip = new C32ToolTip();
	}

	C32TabCtrl* InitTabCtrl()
	{

		DWORD Style = WS_CHILD|WS_VISIBLE|TCS_FIXEDWIDTH | WS_CLIPSIBLINGS ;
		C32Window Pos;
		Pos.Attach(m_HwndMain);
		SIZE Size = Pos.GetClientSize();
		Tab->Create(Style, 0, 0,Size.cx, Size.cy, m_HwndMain);

		Tab->GetTabHeigth();

		Tab->SetExplorerTheme();
		Tab->m_ImageList.CreateSmall();
		Tab->m_ImageList.AddIcon(IDI_EXPLORER);
		Tab->SetImageList();

		Tab->InsertItem(0, L"PTA", 0);
		Tab->InsertItem(1, L"PTC", 0);
		Tab->InsertItem(2, L"PTD", 0);

		int Count = Tab->GetCount();
		//int iSel0 = Tab->SetCurrentSelect(1);
		int iSel = Tab->GetCurrentSelect();
		for(int i = 0; i < Count; i++)
		{
			Tab->m_ListTab[i]->m_Menu.Set(Tab->m_ListTab[i]->GetHwnd(), IDR_MENU_TAB_CTRL, i);
			Tab->m_ListTab[i]->SetOnCommand(TabOnCommand);

		}
		for(int i = 0; i < Count; i++)
		{
			TCITEM tci = {};
			Tab->GetItem(i, &tci);
			ZxDebugEx(("Text : %ws State : 0x%08x \n", tci.pszText, tci.dwState));
		}

		Style = WS_POPUP |TTS_ALWAYSTIP | TTS_BALLOON;
		Tip->Create(Style, 0, 0, 0, 0, Tab->GetHwnd());


		for(int i = 0; i < Count; i++)
		{
			RECT Rect = {};
			Tab->GetItemRect(i, &Rect);
			ZxDebugEx((__FUNCTION__"():: iIndex : %d {%d, %d, %d, %d} \n", i ,Rect.left, Rect.top, Rect.right, Rect.bottom));
			C32String TipStr;
			TipStr.FormatString(L"This Is RectTip %d", i);
			Tip->AddRectTip(TipStr, Tab->GetHwnd(), i, Rect);
		}
		for(int i = 0; i < Count; i++)
		{
			C32Button* Btn = new C32Button();
			{
				DWORD Style = BS_PUSHBUTTON |WS_CHILD | WS_VISIBLE ;
				Btn->Create(Style, 50*(i+1), 50, 100*(i+1), 100, m_HwndMain);
			}
			C32String Text;
			Text.FormatString(L"C32Button-%d", i);
			Btn->SetText(Text);
			Tab->AddChild(i, (C32Window*)Btn);
			C32String TipText;
			TipText.FormatString(L"This Is C32Button-%d", i);
			Tip->AddCtrlTip(TipText,Tab->GetHwnd(), *Btn);
		}

		Tab->m_ToolTip = Tip;
		Tab->SetToolTips(*Tip);
		HWND hwtt1 = Tab->GetToolTips();

		return Tab;
	}


public:
	HWND m_HwndMain;
	C32TabCtrl* Tab;
	C32ToolTip* Tip;
};

class C32SystemColorDialog : public C32Dialog
{
	static BOOL  WINAPI StaticOnClick(DWORD StaticCtrlId, C32Window* This)
	{
		UNREFERENCED_PARAMETER(StaticCtrlId);
		UNREFERENCED_PARAMETER(This);

		ZxDebug((__FUNCTION__"():: This Text: %ws \n",This->GetText()));
		return TRUE;
	}
	
	static BOOL  WINAPI ButtonOnClick(DWORD ButtonCtrlId, C32Button* This)
	{
		UNREFERENCED_PARAMETER(ButtonCtrlId);
		
		UNREFERENCED_PARAMETER(This);
		
		C32ListBoxDialog* Top = (C32ListBoxDialog*)This->GetParentC32Class();

		LPCWSTR SelectString = Top->m_ListBox.GetCurrentSelectString();
		std::wstring Text = L"点击 : ";
		Text += SelectString;
		Top->m_Static.SetText(Text.c_str());
		
		ZxDebug((__FUNCTION__"():: This Text: %ws \n",SelectString));
		return TRUE;
	}

	

public:
	C32SystemColorDialog()
	{

	}
	~C32SystemColorDialog()
	{

	}

public:
	virtual BOOL CALLBACK OnInitDialog(HWND hwndDlg, UINT uMsg, WPARAM  DefautFocusHwnd, LPARAM InitParam, LRESULT& lResult)
	{
	/*	C32Dialog* Base = reinterpret_cast<C32Dialog*>(this);
		Base->OnInitDialog(hwndDlg,  uMsg, DefautFocusHwnd,InitParam, lResult);*/

		
		(hwndDlg),(uMsg),(DefautFocusHwnd),(InitParam);
		HWND hwndListBox = GetDlgItem(hwndDlg, IDC_LIST_SYSTEM_COLOR_TEST);
		HWND hwndOk = GetDlgItem(hwndDlg, IDOK);
		HWND hwndStatis =  GetDlgItem(hwndDlg, IDCANCEL);
	
		Attach(hwndDlg);
		m_Button.Attach(hwndOk);
		m_Button.SetEventClick(C32SystemColorDialog::ButtonOnClick);
		m_ListBox.Attach(hwndListBox);
		m_Static.Attach(hwndStatis);
		m_Static.SetEventClick(StaticOnClick);

		m_ListBox.SetNoMoveRightBottom();
		//m_ListBox.SetExplorerTheme();
		//m_ListBox.AddStyle(LBS_MULTIPLESEL);
		AddC32Window(&m_ListBox);
		AddC32Window(&m_Button);
		AddC32Window(&m_Static);

		for(int i =0; i < 13; i++)
		{
			int index = m_ListBox.AddString(L"福州");
			int index1= m_ListBox.AddString(L"泉州");
			int index2= m_ListBox.AddString(L"厦门");
			int index3= m_ListBox.AddString(L"漳州");

		}
		
		m_ListBox.SetItemHeight(32);
		for(int i =0; i < 4; i++)
		{
			C32String String;

			m_ListBox.GetString(i, String);
			
			ZxDebug(("%ws \n", (LPWSTR)String.GetBuffer()));

		}

		SetCenterPos();
		
		lResult = TRUE;
		return FALSE;
	}

	virtual BOOL CALLBACK OnDrawItem(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
	{
		BOOL Handle = FALSE;
		LPDRAWITEMSTRUCT lpdis = (LPDRAWITEMSTRUCT)lParam;
		
		ZxDebugEx((__FUNCTION__"():: CtlType:%d itemID:%d \n", lpdis->CtlType, lpdis->itemID));

		COLORREF Color = GetSysColor(lpdis->itemID);
		FillRect(lpdis->hDC, &lpdis->rcItem, GetSysColorBrush(lpdis->itemID));
		WCHAR* Text = GetSystemColorToString(lpdis->itemID);

		CString String;
		String += Text;
		String.AppendFormat(L"(%d, %d, %d)", GetRValue(Color), GetGValue(Color), GetBValue(Color));
		DrawText(lpdis->hDC, String, -1, &lpdis->rcItem, 0);


		return Handle;
	}

	C32ListBox m_ListBox;
	C32Button  m_Button;
	C32Static  m_Static;
	
};



VOID C32ListBoxDialogTest(HWND Parent);

VOID C32ListViewDialogTest(HWND Parent);

VOID C32SynDialogDialogTest(HWND Parent);


VOID C32TreeTableDialogTest(HWND Parent);

VOID C32ExplorerDialogTest(HWND Parent);

VOID C32SearchDialogTest(HWND Parent);

VOID C32MoveSizeDialogTest(HWND Parent);

VOID C32GdiPlushDialogTest(HWND Parent);

VOID C32DrawControlDialogTest(HWND Parent);


VOID C32TabCtrlDialogTest(HWND Parent);

VOID C32SystemColorDialogTest(HWND Parent);
