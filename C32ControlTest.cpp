#include "stdafx.h"
#include "C32ControlTest.h"
#include "GdiTest.h"

VOID C32ListBoxDialogTest(HWND Parent)
{
	C32ListBoxDialog  Dialog;

	Dialog.Create(IDD_C32_LIST_BOX_TEST, Parent);

}

VOID C32ListViewDialogTest(HWND Parent)
{
	C32ListViewDialog  Dialog;

	Dialog.Create(IDD_C32LISTVIEW_TEST, Parent);

}


VOID C32SynDialogDialogTest(HWND Parent)
{
	//C32SynDialogDialog  Dialog;
	C32SynDialogDialog* Dialog = new C32SynDialogDialog();
	Dialog->CreateThreadDialog(Parent);
	C32Window* Owner = C32GetUserClass(Parent);
	Owner->Disable();
	//Dialog.Create(IDD_DIALOG_C32CLASS_PROGRESS, Parent);
}


VOID C32TreeTableDialogTest(HWND Parent)
{
	C32TreeTableDialog  Dialog;

	Dialog.Create(IDD_C32TREETABLE_TEST, Parent);

}


VOID C32ExplorerDialogTest(HWND Parent)
{
	C32ExplorerDialog  Dialog;

	Dialog.Create(IDD_C32EXPLORER_TEST, Parent);

}

VOID C32SearchDialogTest(HWND Parent)
{
	C32SearchDialog  Dialog;

	Dialog.Create(IDD_DIALOG_C32CLASSFIND, Parent);
}

VOID C32MoveSizeDialogTest(HWND Parent)
{
	C32MoveSizeDialog  Dialog;

	Dialog.Create(IDD_C32POSSIZE_TEST, Parent);

}

VOID C32GdiPlushDialogTest(HWND Parent)
{
	C32GdiPlusDialog  Dialog;

	Dialog.Create(IDD_C32GDIPLUS_TEST, Parent);

}

VOID C32TabCtrlDialogTest(HWND Parent)
{
	
	C32TabCtrlDialog Dialog;
	Dialog.Create(IDD_C32TABCTRL_TEST, Parent);
	
}

VOID C32DrawControlDialogTest(HWND Parent)
{
	C32DrawControlDialog Dialog;

	Dialog.Create(IDD_C32DRAWCONTROL_TEST, Parent);

}

 VOID C32DrawControlTest(HDC hDc)
 {
	//画一个checkbox的复选框.
	C32DrawControl Draw;
	RECT Rect= {0,0, 30,30};
	Draw.Open(WC_BUTTON);
	Draw.DrawCheckBoxImage(hDc, CBS_CHECKEDNORMAL, Rect);

	Draw.Open(L"PROGRESS");
	RECT ProgressiPartRect = {30, 0, 130, 30};
	for(int i = PP_BAR; i <= PP_TRANSPARENTBARVERT; i++)
	{
		
		ProgressiPartRect.top = i*30;
		ProgressiPartRect.bottom = ProgressiPartRect.top +30;
		for (int k = 1; k <=4; k++)
		{
			ProgressiPartRect.left =  30 + k*100;
			ProgressiPartRect.right =  ProgressiPartRect.left + 100;

			Draw.DrawControl(hDc, i, k, &ProgressiPartRect);
		}
		
	}


 }

 VOID C32VisualStyleTest(LPCWSTR Class, HDC Hdc)
 {
	 C32DrawControl Draw;
	 RECT Rect= {0,0, 30,30};
	 //int iPart1, iPart2 , iStatus1, iStatus2;
	 Draw.Open(Class);
	 RECT iPartRect = {0, 0, 0, 0};
	 
	 for(int i = 0; i <= 30; i++)
	 {
		 iPartRect.top = 100+ i*30;
		 iPartRect.bottom = iPartRect.top +30;
		 for (int k = 0; k <=30; k++)
		 {
			 iPartRect.left =  100 + k*60;
			 iPartRect.right =  iPartRect.left + 60;
			 Draw.DrawControl(Hdc, i, k, &iPartRect);
		 }
		 C32DrawText Text;
		 C32String   String;
		 RECT textRect={30, iPartRect.top, 60, iPartRect.bottom};
		 String.FormatString(L"%d", i);
		 Text.TextOutExt(Hdc, 0, &textRect, String,String.GetCount());
	 }

	 //输出大小
	 for(int i = 0; i <= 30; i++)
	 {
		 C32String String;
		 String.FormatString(L"%2d ", i);
		 for (int k = 0; k <=30; k++)
		 {
			 SIZE Size = {};
			 Draw.GetPartSize(Hdc, i, k, Size);
			 C32String SizeString;
			 SizeString.FormatString(L"{%02d, %02d} ", Size.cx, Size.cy);
			 String += SizeString;
		 }
		 ZxDebugEx((__FUNCTION__"():: %ws \n", String.GetString()));
	 }



 }

 VOID C32ListViewTest(HWND hWnd, HINSTANCE hInstance)
 {
	 InitCommonControls();
	 RECT Rect = {};
	 GetClientRect(hWnd, &Rect);
	 DebugInitialize();
	 C32TreeView::hInstance = hInstance;
	 C32ImageList::hInstance = hInstance;
	 C32Menu::hInstance = hInstance;

	 C32ListView* List = new C32ListView;
	 DWORD ExStyle = 0;
	 DWORD Style = WS_VISIBLE | WS_CHILD ;
	 Style |=   LVS_REPORT ;
	 SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)List);
	 HWND hwndTv = List->Create(ExStyle, Style, 0, 0, Rect.right, Rect.bottom, hWnd);
	 List->m_ImageListNormal.Create(32, 32, ILC_COLOR32, 10, 1);
	 List->m_ImageListNormal.AddIcon(IDI_ICON_TREE_2);

	 List->m_ImageListSmall.Create(32, 32, ILC_COLOR32, 10, 1);
	 List->m_ImageListSmall.AddIcon(IDI_ICON_TREE_2);

	List->AddExtendedStyle(LVS_EX_SUBITEMIMAGES|LVS_EX_FULLROWSELECT);
	List->m_Menu.SetResourceId(IDR_MENU_EXPLORER_LIST);
	// List->SetExplorerTheme();
	List->SetImageListSmall();
	// Tree->SetSubclass();
	List->SetListHeader();

	List->m_Menu.SetParent(List->m_Hwnd);
	
	List->SetSubclass();

	
	List->InsertColumn(0, 0, L"Name", LVCFMT_SPLITBUTTON, 200, -1, 32);
	List->InsertColumn(1, 1,L"Value", LVCFMT_SPLITBUTTON, 200, -1, 32);
	//List->InsertColumn(2, 2,L"Age", LVCFMT_LEFT, 200, 0, 32);

	List->InsertItem(0, L"123", -1, 0);
	List->InsertSubItem(0, 1, L"321", 0);

	List->InsertItem(1, L"456", 0, 0);
	List->InsertSubItem(1, 1, L"654", 0);

 }

 VOID C32TreeViewTest(HWND hWnd, HINSTANCE hInstance)
 {
	 RECT Rect = {};
	 GetClientRect(hWnd, &Rect);
	 DebugInitialize();
	 C32TreeView::hInstance = hInstance;
	 C32ImageList::hInstance = hInstance;

	 C32TreeView* Tree = new C32TreeView;
	 DWORD Style = WS_VISIBLE | WS_CHILD ;
	 Style |= TVS_LINESATROOT  | TVS_HASBUTTONS;
	 Style |= TVS_FULLROWSELECT;
	 SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)Tree);
	 HWND hwndTv = Tree->Create(0, Style, 0, 0, Rect.right, Rect.bottom, hWnd);
	 Tree->m_ImageListNormal.Create(32, 32, ILC_COLOR32, 10, 1);
	 Tree->m_ImageListNormal.AddIcon(IDI_ICON_TREE_2);
	 Tree->SetImageList();
	 Tree->SetSubclass();
	 Tree->SetMenuId(IDR_MENU_EXPLORER_TREE);

#if 0
	 HTREEITEM X = Tree->InsertItemAsyn((HTREEITEM)TVI_ROOT,(HTREEITEM)TV_FIRST, L"123", 0, 0, 1, 0x123);
	 HTREEITEM Y = Tree->InsertItemAsyn((HTREEITEM)TVI_ROOT,(HTREEITEM)TV_FIRST, L"456", 0, 0, 1, 0x456);
	 HTREEITEM Z = Tree->InsertItemAsyn((HTREEITEM)TVI_ROOT,(HTREEITEM)TV_FIRST, L"789", 0, 0, 1, 0x789);


#else
	 HTREEITEM X = Tree->InsertItem((HTREEITEM)TVI_ROOT,(HTREEITEM)TV_FIRST, L"123", 0, 0, 1, 0x123);
	 HTREEITEM Y = Tree->InsertItem((HTREEITEM)TVI_ROOT,(HTREEITEM)TV_FIRST, L"456", 0, 0, 1, 0x456);
	 HTREEITEM Z = Tree->InsertItem((HTREEITEM)TVI_ROOT,(HTREEITEM)TV_FIRST, L"789", 0, 0, 1, 0x789);


#endif

 }


 C32Explorer* C32ExplorerTest(HWND hWnd)
 {
	 InitCommonControls();
	 RECT Rect = {};
	 GetClientRect(hWnd, &Rect);
	 DebugInitialize();
	
	 C32Explorer::RegisterClass();

	 C32ListView* List;
	 C32TreeView* Tree;
	
	C32Explorer* Exp =  new C32Explorer();
	C32Window Cw(hWnd);
	Exp->m_Tree.m_Cx = 300;
	
	Exp->CreateExplorer(Cw, 0, 0, Cw.m_ClientRect.right, Cw.m_ClientRect.bottom);
	Cw.SetPtr();
	Tree = &Exp->m_Tree;
	List = &Exp->m_List;

	List->SetMenuId(IDR_MENU_EXPLORER_LIST);
	List->m_Header.m_Menu.SetResourceId(IDR_MENU_LIST_HEADER);
	List->m_Header.m_Menu.SetParent(List->GetWindow());

	List->m_ImageListNormal.AddIcon(IDI_RED_CHECK);

	List->m_ImageListSmall.Create(32, 32, ILC_COLOR32, 10, 1);
	List->m_ImageListSmall.AddIcon(IDI_RED_CHECK);
	 
	List->AddExtendedStyle(LVS_EX_DOUBLEBUFFER|LVS_EX_SUBITEMIMAGES|LVS_EX_FULLROWSELECT|LVS_EX_CHECKBOXES);
	//List->AddExtendedStyle(LVS_EX_DOUBLEBUFFER  );
	
	 List->SetExplorerTheme();
	 List->SetImageListSmall();
	 List->SetImageListNormal();
	 List->SetImageListSmall();
	
	 List->m_Menu.SetParent(List->m_Hwnd);

	 List->InsertColumn(0, 0, L"人口", LVCFMT_SPLITBUTTON, 200, 0, 32);
	 List->InsertColumn(1, 1,L"平均收入", LVCFMT_SPLITBUTTON, 200, -1, 32);
	 List->InsertColumn(2, 2,L"男女比列", LVCFMT_LEFT, 200, 0, 32);
	 List->InsertColumn(3, 3,L"儿童占比", LVCFMT_LEFT, 0, 0, 0);
	 List->InsertColumn(4, 4,L"景点", LVCFMT_LEFT, 200, 0, 32);
	 List->SetHeaderCheckBox();
	
	// List->AddExtendedStyle(LVS_EX_CHECKBOXES);
	 //List->m_Header.SetCheckboxStyle();
	//List->SetExplorerTheme();
	 List->InsertItem(0, L"123", -1, 0);
	 List->InsertSubItem(0, 1, L"321", 0);

	 List->InsertItem(1, L"456", 0, 0);
	 List->InsertSubItem(1, 1, L"654", 0);
	  
	   
	 Tree->SetMenuId(IDR_MENU_EXPLORER_TREE);
	 Tree->m_ImageListNormal.Create(32, 32, ILC_COLOR32, 10, 1);
	 Tree->m_ImageListNormal.AddIcon(IDI_EXPLORER);
	 Tree->SetImageList();
	// Tree->SetSubclass();


	 /* HTREEITEM X = Tree->InsertItemAsyn((HTREEITEM)TVI_ROOT,(HTREEITEM)TV_FIRST, L"123", 1, -1, 1, 0x123);
	 HTREEITEM Y = Tree->InsertItemAsyn((HTREEITEM)TVI_ROOT,(HTREEITEM)TV_FIRST, L"456", 0, -1, 1, 0x456);
	 HTREEITEM Z = Tree->InsertItemAsyn((HTREEITEM)TVI_ROOT,(HTREEITEM)TV_FIRST, L"789", 0, -1, 1, 0x789);
	 */
	 HTREEITEM X = Tree->InsertItem((HTREEITEM)TVI_ROOT,(HTREEITEM)TV_FIRST, L"北京", 0, -1, 1, 0x123);
	 HTREEITEM Y = Tree->InsertItem((HTREEITEM)TVI_ROOT,(HTREEITEM)TV_FIRST, L"河北", 0, -1, 1, 0x456);
	 HTREEITEM Z = Tree->InsertItem((HTREEITEM)TVI_ROOT,(HTREEITEM)TV_FIRST, L"福建", 0, -1, 1, 0x789);
	 HTREEITEM A = Tree->InsertItem((HTREEITEM)TVI_ROOT,(HTREEITEM)TV_FIRST, L"汕头", 0, -1, 1, 0x789);
	 HTREEITEM B = Tree->InsertItem((HTREEITEM)TVI_ROOT,(HTREEITEM)TV_FIRST, L"潮州", 0, -1, 1, 0x789);

	 return Exp;
 }
 
 VOID C32ListBoxTest(HWND Parent)
 {
	/* HWND hListBox = CreateWindow(_T("listbox"), NULL, WS_CHILD | WS_VISIBLE | WS_TABSTOP | LBS_STANDARD,
		 20, 20, 60, 80,hWnd,(HMENU)10001,(HINSTANCE)GetWindowLongW(hWnd,GWL_HINSTANCE),NULL);
	 SendMessageW(hListBox, LB_ADDSTRING, 0, (LPARAM)_T("中国"));
	 SendMessageW(hListBox, LB_ADDSTRING, 0, (LPARAM)_T("美国"));
	 SendMessageW(hListBox, LB_ADDSTRING, 0, (LPARAM)_T("英国"));

	 return;*/
	
	C32ListBox* Box = new C32ListBox();
	//DWORD dwStyle = WS_POPUP|WS_CHILD|WS_VISIBLE|LBS_HASSTRINGS |LBS_MULTIPLESEL  ;
	DWORD dwStyle =  WS_CHILD | WS_VISIBLE | WS_TABSTOP | LBS_STANDARD | LBS_HASSTRINGS|LBS_MULTIPLESEL   |LBS_OWNERDRAWFIXED;
	Box->Create(dwStyle,20,20,300,300, Parent);
	int index = Box->AddString(L"123");
	int index1= Box->AddString(L"456");
	int index2= Box->AddString(L"789");
	Box->SetItemHeight(32);
	Box->SetUserData();

	ZxDebug(("%d %d \n", index, index1));

 }
  
 VOID C32DialogProgressTest(HWND hWnd)
 {
	
	C32DialogProgress DlgProgress;
	//DlgProgress.SetCtrlText();
	DlgProgress.Create(hWnd);

 }

 VOID C32DialogSearchTest()
 {
	C32DialogSearch Search;

	Search.Create(IDD_DIALOG_C32CLASSFIND, C32Hwnd);



 }
 
 BOOL  CALLBACK BtnEventClick(DWORD CtrlId, C32Button* This)
 {
	ZxDebugEx((__FUNCTION__"():: \n"));
	C32Container * Frame = (C32Container*)This->GetParentC32Class();
	Frame->m_List[0]->SetVisible(FALSE);
	Frame->m_List[0]->SetText(L"BtnEventClick");	
	Frame->ReflushWindow();
	UpdateWindow(Frame->GetHwnd());
	return TRUE;
 }

 C32Button* C32ButtonTest()
 {
	C32Button* Btn = new C32Button();

	DWORD Style = BS_PUSHBUTTON |WS_CHILD | WS_VISIBLE ;
	Btn->Create(Style, 0, 0, 100, 100, C32Hwnd);

	C32Button* Btn1 = new C32Button();

	Btn1->Create(Style, 100, 100, 200, 200, C32Hwnd);
	Btn1->SetText(L"显示");
	Btn1->SetEventClick(BtnEventClick);

	C32MainFrame->AddC32Child(Btn);
	C32MainFrame->AddC32Child(Btn1);

	return Btn1;
	

 }

 C32ToolTip* C32ToolTipTest()
 {
	 C32Button* Btn = new C32Button();
	 {
		DWORD Style = BS_PUSHBUTTON |WS_CHILD | WS_VISIBLE ;
		Btn->Create(Style, 0, 0, 100, 100, C32Hwnd);
	 }

	 C32ToolTip* Tip = new C32ToolTip();
	 DWORD Style = WS_POPUP |TTS_ALWAYSTIP | TTS_BALLOON;
	 Tip->Create(Style, 0, 0, 0, 0, C32Hwnd);

	 Tip->AddCtrlTip(L"This Is C32Button Tip", C32Hwnd, Btn->GetWindow());
	 
	 RECT TipRect1 = {100, 0, 200, 100};
	 Tip->AddRectTip(L"This Is Rect Tip \n{100, 0, 200, 100}", C32Hwnd, 1,TipRect1);
	 
	 RECT TipRect2 = {200, 0, 300, 100};
	 Tip->AddRectTip(L"This Is Rect Tip {200, 0, 300, 100} ", C32Hwnd, 2,TipRect2);

	 RECT TipRect3 = {300, 0, 400, 100};
	 Tip->AddRectTip(LPSTR_TEXTCALLBACK, C32Hwnd, 3, TipRect3);


	 Tip->Activate();
	 COLORREF XX = Tip->SetTipBkColor(0x00FFFFFF);
	 COLORREF XX1 = Tip->SetTipBkColor(0x123456);
	 RECT MarginRect = {};
	 Tip->GetMargin(&MarginRect);
	 int TipWidth = Tip->GetMaxTipWidth();
	 int TipCount = Tip->GetTipCount();
	 
	 ZxDebugEx((__FUNCTION__"():: Margin { %d, %d, %d, %d }\n", MarginRect.left, MarginRect.top, MarginRect.right, MarginRect.bottom));
	 ZxDebugEx((__FUNCTION__"():: MaxTipWidth : %d  TipCount = %d\n", TipWidth, TipCount));
	 Tip->SetMaxTipWidth(200);
	 Tip->SetTitle(TTI_INFO, L"SetTitle");


	 Tip->Popup();

	 return Tip;
 }
 
 VOID C32StatusBarTest()
 {
	C32StatusBar* Status = new C32StatusBar();


 }

 VOID C32DialogFileTest()
 {
	 C32DialogFile FileDialog;
	 C32String CurrentFoloder;
	 CurrentFoloder.AssignStringW(256);
	 FileDialog.Show();
	 GetCurrentDirectory(256, CurrentFoloder);
	 ZxDebug(("CurrentDirectory :%ws \n", CurrentFoloder));
	 C32DialogFile SaveDialog(C32DialogFile::FILE_DIALOG_SAVE);

	 SaveDialog.Show(L"保存文件", NULL);

	  CurrentFoloder.AssignStringW(256);
	  GetCurrentDirectory(256, CurrentFoloder);
	  ZxDebug(("CurrentDirectory :%ws \n", CurrentFoloder));

 }

 VOID C32TreeTableTest(HWND Parent)
 {
	 setlocale(LC_ALL, "Chinese");
	 C32TreeTable* Table = new C32TreeTable;
	 Table->RegisterClassEx32(L"C32TreeTable");

	 C32Container* Pos = (C32Container*)C32GetUserClass(Parent);

	 Table->Create(0, L"C32TreeTable", L"C32TreeTable", WS_CHILD|WS_VISIBLE, 0, 0, Pos->m_ClientCx,Pos->m_ClientCy, C32Hwnd);

	 Pos->AddC32Window(Table);
	 
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

 }

 VOID C32SystemColorDialogTest(HWND Parent)
 {
	C32SystemColorDialog Dialog;

	Dialog.Create(IDD_SYSTEM_COLOR_TEST, Parent);


 }
