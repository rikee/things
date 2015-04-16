#include "win_main.h"

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hprev, PSTR cmdline, int ishow)
{
	MSG msg;
	HWND hwnd;
	WNDCLASSEX wndclassex = {0};

	ULONG_PTR m_gdiplusToken;
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);

	winTitle = Helper::getTitle(game);

	wndclassex.cbSize = sizeof(WNDCLASSEX);
	wndclassex.style = CS_HREDRAW | CS_VREDRAW;
	wndclassex.lpfnWndProc = WinProc;
	wndclassex.hInstance = hinstance;
	wndclassex.hbrBackground = kBackground;
	wndclassex.lpszClassName = kClassName.c_str();
	wndclassex.hCursor = (HCURSOR)LoadImage(NULL, MAKEINTRESOURCE(IDC_ARROW), IMAGE_CURSOR, 0, 0, LR_SHARED);

	RegisterClassEx(&wndclassex);

	hwnd = CreateWindowEx(
		NULL,
		kClassName.c_str(),
		winTitle.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		kWinWid,
		kWinHgt,
		NULL,
		NULL,
		hinstance,
		NULL
	);
	if(!hwnd) return EXIT_FAILURE;

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
	Thieves thieves(hwnd);

	switch(message)
	{
	case WM_PAINT:
		if(game == 't')
		{
			thieves.paintScreen();
		}
		break;
	case WM_DESTROY:
		ReleaseDC(hwnd,gHDC);
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, message, wparam, lparam);
}