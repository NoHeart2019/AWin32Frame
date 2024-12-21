#include "stdafx.h"
#include "C32Control.h"


 
class C32Window;
    
HINSTANCE C32Menu::hInstance = NULL;
HINSTANCE C32ImageList::hInstance = NULL;
HINSTANCE C32TreeView::hInstance = NULL; //
HINSTANCE C32Explorer::hInstance = NULL;
HINSTANCE C32StatusBar::hInstance = NULL;
HINSTANCE C32Icon::hInstance = NULL;
HINSTANCE C32ListBox::hInstance = NULL;
HINSTANCE C32Dialog::hInstance = NULL;
HINSTANCE C32DialogProgress::hInstance = NULL;


HFONT C32GdiObject::m_SysFont = NULL;
HFONT C32GdiObject::m_SysGuiFont = NULL;

ULONG_PTR C32GdiPlus::m_GdiToken;
Gdiplus::GdiplusStartupInput C32GdiPlus::m_GdiInput;
Gdiplus::GdiplusStartupOutput C32GdiPlus::m_GdiOutput;

HINSTANCE C32Hinstance;
HWND      C32Hwnd;
C32Container* C32MainFrame;

C32TSystemMetrics C32SystemMetrics;


VOID  C32FreeWindowList(std::vector<C32Window*>& List, BOOL DeletePtr)
{
	if (DeletePtr)
	{
		for(size_t i = 0; i < List.size(); i++)
		{
			delete List[i];
			List[i] = NULL;
		}
	}
	List.resize(0);
}
  
VOID C32CreateTree(C32TreeView& Tree, HWND hwndParent, int xPos, int yPos, int Cx, int Cy)
{
	DWORD Style = WS_CHILD | WS_VISIBLE;
	Style |= TVS_LINESATROOT  | TVS_HASBUTTONS | TVS_FULLROWSELECT|TVS_DISABLEDRAGDROP;
	Style |= TVS_TRACKSELECT ;
	Tree.Create(0, Style,
		xPos, yPos, Cx, Cy, 
		(HWND)hwndParent);

	Tree.SetSubclass();
	Tree.SetExplorerTheme();
	//Tree.m_ImageListNormal.CreateNormal();
	//Tree.m_ImageListState.CreateNormal();

}

VOID C32CreateList(C32ListView& List, HWND hwndParent, int xPos, int yPos, int Cx, int Cy)
{
	DWORD Style = WS_CHILD | WS_VISIBLE  ;
	Style |=   LVS_REPORT   ;
	DWORD ExStyle = LVS_EX_FULLROWSELECT|LVS_EX_LABELTIP ;
	List.Create(ExStyle, Style,
		xPos, yPos, Cx, Cy, 
		(HWND)hwndParent);
		  
	List.SetExtendedStyle(ExStyle);
	List.SetListHeader();
	List.SetSubclass();
	//List.SetExplorerTheme();

}

VOID C32CreateStatus(C32StatusBar& Status, HWND hwndParent)
{
	DWORD Style3 = WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP | SBARS_TOOLTIPS ;
	Status.CreateStatus(WS_EX_WINDOWEDGE, Style3, hwndParent);
	Status.SetExplorerTheme();
	
	INT I = 0;
}

BOOL C32Header::OnNotifyItemStateIconClick(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
{
	BOOL Handle = FALSE;
	//如果此Header 是 ListView 的Header，将ListView 所有的Item check box 设置 状态
	LPNMHEADER lpnmhdr = (LPNMHEADER)lParam;
	if (m_List)
	{
		if(IsCheckState(lpnmhdr->iItem))
			m_List->ResetListCheckState();
		else
			m_List->SetListCheckState();
	}
	if (m_OnNotifyItemStateIconClick != NULL)
	{
		Handle = m_OnNotifyItemStateIconClick(lpnmhdr, lResult, this);
	}
	return Handle;
}

HWND C32TreeView::Create(DWORD  dwExStyle, DWORD dwStyle,int X, int Y, int Width, int Height, HWND Parent)
{
	m_Rect.left = X, m_Rect.top = Y, m_Rect.right = X + Width, m_Rect.bottom = Y + Height;
	m_Cx = Width, m_Cy = Height;

	m_Parent = Parent;

	HWND hwnd = CreateWindowEx(dwExStyle,
					WC_TREEVIEW,
					L"C32TreeView",
					dwStyle,
					X,
					Y,
					Width,
					Height,
					Parent,
					(HMENU)NULL,
					C32TreeView::hInstance,
					this);
	ZxDebug((__FUNCTION__"():: hwnd: %p This:%p Code:%d\n", hwnd, this, GetLastError()));
	m_Hwnd = hwnd;
	
	return hwnd;
}

VOID C32TreeView::DestroyView()
{
	if (m_Hwnd)
	{
		DestroyWindow(m_Hwnd);
		m_Hwnd = NULL;
	}

}

VOID C32TreeView::SetExtendedStyles(DWORD dwExStyle)
{
	if (m_Hwnd)
	{
		TreeView_SetExtendedStyle(m_Hwnd, dwExStyle, 0);
	}
}

VOID C32TreeView::AddExtendedStyles(DWORD dwExStyle)
{
	if (m_Hwnd)
	{
		DWORD Ex = TreeView_GetExtendedStyle(m_Hwnd);
		Ex |= dwExStyle;
		TreeView_SetExtendedStyle(m_Hwnd, dwExStyle, Ex);
	}
}

DWORD C32TreeView::GetExtendedStyles()
{
	DWORD ExSytle = 0;

	if (m_Hwnd)
		ExSytle = TreeView_GetExtendedStyle(m_Hwnd);
		
	return ExSytle;
}

BOOL C32TreeView::SetSubclass()
{
	BOOL Ret = FALSE;

	if (m_Hwnd)
	{
		Ret	= SetWindowSubclass(m_Hwnd, C32TreeView::TreeSubclassProc, (UINT_PTR)this, (DWORD_PTR)this);
	}

	return FALSE;
}


HTREEITEM C32TreeView::InsertItem(HTREEITEM Parent, HTREEITEM InsertAfter, LPWSTR Text,
									int iImage, int iSelectedImage, int cChildren, LPARAM lParam)
{
	TVINSERTSTRUCT its = {};
	if (Text == NULL)
		Text = L"";
	TVITEM & it = its.item;
	it.mask = TVIF_TEXT;

	if (iImage != TV_MASK_NO_BIT)
	{
		it.mask |= TVIF_IMAGE;
		it.mask |= TVIF_SELECTEDIMAGE;
	}
	if (cChildren != TV_MASK_NO_BIT)
		it.mask |= TVIF_CHILDREN;

	if (lParam != NULL)
		it.mask |= TVIF_PARAM;

	it.pszText = Text;
	it.cchTextMax = (int)wcslen(Text);
	it.iImage = iImage;
	it.iSelectedImage = iImage ;//iSelectedImage;
	it.cChildren = cChildren;
	it.lParam = lParam;

	its.hParent = Parent;
	its.hInsertAfter = InsertAfter;
	
	return TreeView_InsertItem(m_Hwnd, &its);
}

HTREEITEM C32TreeView::InsertItemRoot(HTREEITEM InsertAfter, LPWSTR Text, 
					int iImage, int iSelectedImage, int cChildren , LPARAM lParam)
{
	return InsertItem(TVI_ROOT, InsertAfter, Text, iImage, iSelectedImage,cChildren,lParam);
}

HTREEITEM C32TreeView::InsertItemAsyn(HTREEITEM Parent, HTREEITEM InsertAfter, LPWSTR Text,
	int iImage, int iSelectedImage, int cChildren, LPARAM lParam)
{
	TVINSERTSTRUCT its = {};

	TVITEM & it = its.item;
	it.mask = TVIF_TEXT;
	it.mask |= TVIF_DI_SETITEM;
	if (iImage != TV_MASK_NO_BIT)
		it.mask |= TVIF_IMAGE;
	if (iSelectedImage != TV_MASK_NO_BIT)
		it.mask |= TVIF_SELECTEDIMAGE;
	if (cChildren != TV_MASK_NO_BIT)
		it.mask |= TVIF_CHILDREN;

	if (lParam != NULL)
		it.mask |= TVIF_PARAM;

	it.pszText = LPSTR_TEXTCALLBACK ;
	it.cchTextMax = 0;
	it.iImage = I_IMAGECALLBACK ;
	it.iSelectedImage = I_IMAGECALLBACK;
	it.cChildren = I_CHILDRENCALLBACK;
	it.lParam = lParam;

	its.hParent = Parent;
	its.hInsertAfter = InsertAfter;

	return TreeView_InsertItem(m_Hwnd, &its);
}

//处理通知

LRESULT  CALLBACK C32TreeView::TreeSubclassProc (HWND hWnd, UINT uMsg, WPARAM wParam,
	LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	//C32DbgOutTreeViewMsg(uMsg);
	BOOL bSub = FALSE;
	LRESULT Result = 0;
	C32TreeView* This = (C32TreeView*)dwRefData;
	switch(uMsg)
	{
	case WM_COMMAND:
		bSub = This->OnCommand(wParam, lParam, Result);
		break;
	case WM_NOTIFY:
		bSub = This->OnNotify(wParam, lParam, Result);
		break;
	}
	if (bSub == FALSE)
	{
		return DefSubclassProc(hWnd, uMsg, wParam, lParam);
	}
	return (LRESULT)bSub;
}

 BOOL CALLBACK C32TreeView::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT& lResult)
{
	BOOL bNotify = FALSE;
	int NotifyCode = 0;
	LPNMTREEVIEW NmTv = NULL;
	LPNMHDR lphdr = (LPNMHDR)lParam;
	NotifyCode = lphdr->code;
	C32DbgOutTreeViewNotify(NotifyCode);

	
	if (lphdr->idFrom != (ULONG_PTR)this->m_Hwnd && lphdr->hwndFrom != this->m_Hwnd)
	{
		DebugBreak();
		return FALSE;
	}
	
	switch(NotifyCode)
	{
		/*case NM_SETCURSOR:
			bNotify = OnNotifyNmSetCursor((LPNMMOUSE)lphdr, lResult); 
		break;

		case NM_CLICK:
			bNotify = OnNotifyNmClick((LPNMHDR)lphdr, lResult); 
			break;*/
		case TVN_SELCHANGED:
			bNotify = OnNotifySelChanged((LPNMTREEVIEW)lphdr, lResult); 
			break;
		case TVN_SELCHANGING:
			bNotify = OnNotifySelChanging((LPNMTREEVIEW)lphdr, lResult); 
			break;
		case TVN_ITEMCHANGING:
			bNotify = OnNotifyItemChanging((NMTVITEMCHANGE*)lphdr); 
			break;
		case TVN_ITEMCHANGED:
			bNotify = OnNotifyItemChanged((NMTVITEMCHANGE*)lphdr, lResult); 
			break;
		case NM_CUSTOMDRAW:
			bNotify = OnNotifyCustomDraw((LPNMTVCUSTOMDRAW)lphdr, lResult);
			break;
		case TVN_GETDISPINFO:
			bNotify = OnNotifyGetDispInfo((LPNMTVDISPINFO)lphdr);
			break;
		
			 

	}

	return bNotify;	
}

 BOOL CALLBACK C32TreeView::OnNotifyGetDispInfo(LPNMTVDISPINFO NMTvDispInfo)
 {
	TVITEM & it = NMTvDispInfo->item;
	ZxDebug(("TvItem->mask %04x state: %04x ->lParam : %p\n",it.mask, it.state ,(LPVOID)it.lParam));
	
	if(it.mask == 0x40)
		return TRUE;

	if (it.mask & TVIF_CHILDREN)
	{
		it.cChildren = AsynGetChildren(it);
	}
	
	if (it.mask & TVIF_TEXT)
	{
		it.pszText = AsynGetText(it);
	}

	if (it.mask & TVIF_IMAGE)
	{
		it.iImage = AsynGetImage(it);
	}
	if (it.mask & TVIF_SELECTEDIMAGE)
	{
		//it.iImage = AsynGetImage(it);
		it.iSelectedImage = AsynGetSelectedImage(it);
	}
	it.mask |= TVIF_DI_SETITEM;
	if (it.mask & TVIF_STATE)
	{
		DebugBreak();
	}

	return TRUE;
 }
 
 HINSTANCE  C32ListView::hInstance;

 int C32ListView::InsertColumn(int iCol, int iSubItem, LPWSTR Text,int Format, int Cx,  int iImage, int CxMin)
 {
	BOOL Index = -1;
	
	LVCOLUMN lvc={};
	if (iImage != -1)
		lvc.mask |= LVCF_IMAGE;

	lvc.mask |=   LVCF_FMT | LVCF_TEXT | LVCF_WIDTH |  LVCF_SUBITEM | LVCF_MINWIDTH ;
	lvc.fmt = Format;
	lvc.pszText = Text;
	lvc.cchTextMax = (int)wcslen(Text);
	lvc.cx = Cx;
	lvc.iSubItem = iSubItem;
	lvc.iImage = iImage;
	lvc.cxMin = CxMin;

	if (iCol == 0)
	{
		if(ListView_SetColumn(m_Hwnd, iCol, &lvc) == TRUE)
			return 0;
	}
	Index = ListView_InsertColumn(m_Hwnd, iCol, &lvc);
	return Index;

 }

 int C32ListView::InsertItem(int iItem, LPWSTR Text, int iImage, LPARAM lParam)
 {
	int Index = -1;

	LVITEM lvi = {};

	if (iImage != -1)
		lvi.mask |= LVIF_IMAGE;

	if (lParam != 0ULL)
		lvi.mask |= LVIF_PARAM;

	lvi.mask |= LVIF_TEXT  ;

	lvi.iItem = iItem;
	lvi.iSubItem = 0;
	lvi.pszText = Text;
	lvi.cchTextMax = (int)wcslen(Text);
	lvi.lParam = lParam;
	lvi.iImage = iImage;
	Index = ListView_InsertItem(m_Hwnd, &lvi);
	
	return Index;
 }

 BOOL C32ListView::InsertSubItem(int iItem, int iSubItem, LPWSTR Text, int iImage)
 {
	 BOOL bSet =FALSE;

	 LVITEM lvi = {};
	 if (iImage != -1)
		lvi.mask |= LVIF_IMAGE;
	 
	 lvi.mask |=  LVIF_TEXT  ;
	 lvi.iItem = iItem;
	 lvi.iSubItem = iSubItem;
	 lvi.pszText = Text;
	 lvi.cchTextMax = (int)wcslen(Text);
	
	 bSet = ListView_SetItem(m_Hwnd, &lvi);

	 return bSet;
 }

 int C32ListView::InsertItemAsyn(int iItem, LPWSTR Text, int iImage, LPARAM lParam)
 {
	 int Index = -1;

	 LVITEM lvi = {};
	// lvi.mask = LVIF_DI_SETITEM;
	 if (iImage != -1)
		 lvi.mask |= LVIF_IMAGE;

	 if (lParam != 0ULL)
		 lvi.mask |= LVIF_PARAM;

	 lvi.mask |=  LVIF_TEXT  ;
	
	 lvi.iItem = iItem;
	 lvi.iSubItem = 0;
	 lvi.pszText = LPSTR_TEXTCALLBACK;
	 lvi.cchTextMax = 260;
	 lvi.lParam = lParam;
	 lvi.iImage = I_IMAGECALLBACK ;
	 Index = ListView_InsertItem(m_Hwnd, &lvi);

	 return Index;
 }

 int C32ListView::InsertSubItemAsyn(int iItem, int iSubItem, LPWSTR Text, int iImage)
 {
	 int Index = -1;

	 LVITEM lvi = {};
	 if (iImage != -1)
		 lvi.mask |= LVIF_IMAGE;

	 lvi.mask |=  LVIF_TEXT  ;
	 lvi.iItem = iItem;
	 lvi.iSubItem = iSubItem;
	 lvi.pszText = LPSTR_TEXTCALLBACK;
	 lvi.iImage = I_IMAGECALLBACK ;
	 //lvi.cchTextMax = (int)wcslen(Text);

	 Index = ListView_SetItem(m_Hwnd, &lvi);

	 return Index;
 }


 VOID InitializeC32Control(HINSTANCE hInstance)
 {
	 C32Hinstance = hInstance;
	 C32Menu::hInstance = hInstance;
	 C32ImageList::hInstance = hInstance;
	 C32TreeView::hInstance = hInstance;
	 C32Explorer::hInstance = hInstance;
	 C32StatusBar::hInstance = hInstance;
	 C32Icon::hInstance = hInstance;
	 C32ListBox::hInstance = hInstance;
	 C32Dialog::hInstance = hInstance;
	 C32DialogProgress::hInstance = hInstance;
	 C32ListBox::Initialize();
	 C32Explorer::Initialize();
	 C32GdiPlus::Initialize();
	 C32GdiObject::Initialize();
	 C32Container::Initialize();
	 //SetProcessDPIAware();

 }
