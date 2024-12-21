/*
	头文件 应用程序的运行环境

*/
#pragma once

#define OEMRESOURCE
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

#include <WindowsX.h>
#include <WinUser.h>
#include <Uxtheme.h>
#include <vsstyle.h>
#include <vssym32.h>
#include <commctrl.h>
#include <Commdlg.h>
#include <comdef.h>
#include <GdiPlus.h>


// C RunTime Header Files
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <locale>


//Using GDI Plus
#pragma comment(lib, "GdiPlus.lib")

//Using Win32 Common Control Lib
#pragma comment(lib, "comctl32.lib")

//Visual Styles 
#pragma comment(lib, "Uxtheme.lib")

//Changes the appearance of common controls
//Enabling Visual Styles
// Configure->Manifest Tool-> Input And Output-> Enable DPI Awareness yes
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
