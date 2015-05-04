#include "helper.h"

void Helper::initGameWindow(HWND hwnd, char game)
{
	eraseWindow(hwnd);
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
void Helper::eraseWindow(HWND hwnd)
{
	RECT cRect;
	GetClientRect(hwnd, &cRect);
	HDC hdc = GetDC(hwnd);

	int clientWidth = cRect.right - cRect.left;
	int clientHeight = cRect.bottom - cRect.top;

	HBRUSH hbrush = CreateSolidBrush(RGB(0,127,0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, hbrush);
	HPEN hpen = CreatePen(PS_NULL, 0, RGB(0,127,0));
	HPEN oldPen = (HPEN)SelectObject(hdc, hpen);

	Rectangle(hdc, 0, 0, clientWidth, clientHeight);

	SelectObject(hdc, oldBrush);
	DeleteObject(hbrush);
	SelectObject(hdc, oldPen);
	DeleteObject(hpen);
	ReleaseDC(hwnd,hdc);
}