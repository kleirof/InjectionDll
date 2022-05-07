#pragma once

#include "windows.h"

# if defined(INJECTION_DLL)
#  define INJECTIONDLL_EXPORT __declspec(dllexport)
# else
#  define INJECTIONDLL_EXPORT __declspec(dllimport)
# endif

extern "C" INJECTIONDLL_EXPORT LRESULT MouseProc(int nCode, WPARAM wParam, LPARAM lParam);

extern "C" INJECTIONDLL_EXPORT void SetDstHwnd(HWND dstHWnd);