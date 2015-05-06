#include "win_main.h"

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hprev, PSTR cmdline, int ishow)
{
	std::srand(unsigned(std::time(0)));

	ULONG_PTR m_gdiplusToken;
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);

	wndclassex.cbSize = sizeof(WNDCLASSEX);
	wndclassex.style = CS_HREDRAW | CS_VREDRAW;
	wndclassex.lpfnWndProc = WinProc;
	wndclassex.hInstance = hinstance;
	wndclassex.hbrBackground = kBackground;
	wndclassex.lpszClassName = kClassName.c_str();
	wndclassex.hCursor = (HCURSOR)LoadImage(NULL, MAKEINTRESOURCE(IDC_ARROW), IMAGE_CURSOR, 0, 0, LR_SHARED);
	wndclassex.hIcon = (HICON)LoadImage(hinstance,MAKEINTRESOURCE(IDI_ICON1),IMAGE_ICON,0,0,LR_DEFAULTSIZE);
	wndclassex.hIconSm = wndclassex.hIcon;

	RegisterClassEx(&wndclassex);

	gMenu = LoadMenu(hinstance,MAKEINTRESOURCE(IDR_MENU1));

	hwnd = CreateWindowEx(
		NULL,
		kClassName.c_str(),
		winTitle.c_str(),
		WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		578,
		388,
		NULL,
		gMenu,
		hinstance,
		NULL
	);
	if(!hwnd)
	{
		DestroyMenu(gMenu);
		return EXIT_FAILURE;
	}
	
	thieves.setHWND(hwnd);
	kings.setHWND(hwnd);

	ShowWindow(hwnd, SW_SHOWDEFAULT);
	UpdateWindow(hwnd);

	while(1)
	{
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{
				break;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Sleep(10);
		}
	}

	Gdiplus::GdiplusShutdown(m_gdiplusToken);
	UnregisterClass(kClassName.c_str(),hinstance);
	return msg.wParam;
}

LRESULT CALLBACK WinProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	PAINTSTRUCT paintStruct;
	HINSTANCE hinstance = GetModuleHandle(NULL);
	HDC hdc = NULL;

	switch(message)
	{
	case WM_COMMAND:
		switch(LOWORD(wparam))
		{
		case ID_DEAL_KINGS:
			game = 'k';
			kings.setState(0);
			Helper::initGameWindow(hwnd, game);
			break;
		case ID_DEAL_THIEVES:
			game = 't';
			thieves.setState(0);
			Helper::initGameWindow(hwnd, game);
			break;
		case ID_QUIT:
			SendMessage(hwnd, WM_CLOSE, 0 ,0);
			break;
		}
		return 0;

	case WM_CREATE:
		Helper::initGameWindow(hwnd, game);
		return 0;

	case WM_LBUTTONDOWN:
		switch(game)
		{
		case 't':
			thieves.processClick(LOWORD(lparam), HIWORD(lparam));
		}
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &paintStruct);

		switch(game)
		{
		case 't':
			thieves.setHDC(hdc);
			thieves.paintScreen();
			thieves.setState(2);
			break;
		case 'k':
			if(kings.getState() < 2)
			{
				kings.paintScreen();
			}
			break;
		}
		EndPaint(hwnd, &paintStruct);
		return 0;

	case WM_DESTROY:
	case WM_CLOSE:
		ReleaseDC(hwnd,hdc);
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, message, wparam, lparam);
}

BOOL CALLBACK DialogProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	HWND mainHwnd = GetParent(hwnd);
	static HDC hdc;
	static HBRUSH dlgBG;
	switch(message)
	{
	case WM_INITDIALOG:
		dlgBG = CreateSolidBrush(RGB(255,255,255));
		hdc = (HDC)wparam;
		return true;

	case WM_CTLCOLORDLG:
		return (LONG)dlgBG;

	case WM_CTLCOLORSTATIC:
		{
		SetBkMode(hdc, TRANSPARENT);
		return (LONG)dlgBG;
		}

	case WM_CTLCOLORBTN:
		SetBkMode(hdc, TRANSPARENT);
		return (LONG)dlgBG;

	case WM_COMMAND:
		switch(LOWORD(wparam))
		{
		case IDT_YES:
			if(game == 't')
			{
				thieves.setState(0);
				Helper::initGameWindow(mainHwnd, game);
			}
			DeleteObject(dlgBG);
			ReleaseDC(hwnd,hdc);
			DestroyWindow(hwnd);
			return true;
			
		case IDT_SWITCH:
			if(game == 't')
			{
				game = 'k';
				kings.setState(0);
				Helper::initGameWindow(mainHwnd, game);
			}
			DeleteObject(dlgBG);
			ReleaseDC(hwnd,hdc);
			DestroyWindow(hwnd);
			return true;
			
		case IDT_NO:
			DeleteObject(dlgBG);
			ReleaseDC(hwnd,hdc);
			SendMessage(mainHwnd, WM_CLOSE, 0 ,0);
			DestroyWindow(hwnd);
			return true;
		}
		
	case WM_CLOSE:
	case WM_DESTROY:
		DeleteObject(dlgBG);
		thieves.releaseDC();
		ReleaseDC(hwnd,hdc);
		DestroyWindow(hwnd);
		return true;
	}

	return false;
}