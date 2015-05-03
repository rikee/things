#include "helper.h"

void Helper::initGameWindow(HWND hwnd, char game)
{
	switch(game)
	{
	case 't':
		SetWindowText(hwnd,Thieves::wndTitle.c_str());
		SetWindowPos(hwnd,NULL,NULL,NULL,Thieves::wndWidth,Thieves::wndHeight,SWP_NOMOVE);
		InvalidateRect(hwnd,NULL,NULL);
		break;
	case 'k':
		SetWindowText(hwnd,Kings::wndTitle.c_str());
		SetWindowPos(hwnd,NULL,NULL,NULL,Kings::wndWidth,Kings::wndHeight,SWP_NOMOVE);
		InvalidateRect(hwnd,NULL,NULL);
		break;
	}
}
HWND Helper::initDialog(HWND hwnd)
{
	return CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG1), hwnd, (DLGPROC)DialogProc);
}