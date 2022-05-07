#include "pch.h"

#define INJECTION_DLL
#include "dllmain.h"

//*****分配共享数据段*****
#pragma data_seg("dstHwnd")
static HWND gdstHWnd = NULL;
#pragma data_seg()
#pragma comment(linker,"/SECTION:dstHwnd,rws")

const int R = 450;
const POINT pO{ 1160, 560 };
HHOOK mouseHook = NULL;

//接口函数，设置全局变量
void __cdecl SetDstHwnd(HWND dstHWnd)
{
    gdstHWnd = dstHWnd;
}

//处理鼠标消息的回调函数
LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode != HC_ACTION)
    {
        return CallNextHookEx(mouseHook, nCode, wParam, lParam);
    }

    MOUSEHOOKSTRUCT* mslp = (MOUSEHOOKSTRUCT*)lParam;

    LPARAM postLParam = (LPARAM)((mslp->pt.y << (sizeof(WORD) * 8)) + mslp->pt.x);
    if (gdstHWnd != NULL)
    {
        PostMessage(gdstHWnd, (UINT)wParam, 0, postLParam);
    }

    return CallNextHookEx(mouseHook, nCode, wParam, lParam);
}
