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

	RegisterClassEx(&wndclassex);

	gMenu = LoadMenu(hinstance,MAKEINTRESOURCE(IDR_MENU1));

	hwnd = CreateWindowEx(
		NULL,
		kClassName.c_str(),
		winTitle.c_str(),
		WS_OVERLAPPEDWINDOW,
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

	gHDC = GetDC(hwnd);
	if(!gHDC) return EXIT_FAILURE;

	GetClientRect(hwnd, &gRect);

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
	thieves.setHWND(hwnd);
	kings.setHWND(hwnd);

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
			thieves.paintScreen();
		}
		return 0;

	case WM_PAINT:
		switch(game)
		{
		case 't':
			if(thieves.getState() < 2)
			{
				thieves.paintScreen();
				thieves.setState(2);
			}
			break;
		case 'k':
			if(kings.getState() < 2)
			{
				kings.paintScreen();
			}
			break;
		}
		return 0;

	case WM_DESTROY:
		ReleaseDC(hwnd,gHDC);
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, message, wparam, lparam);
}