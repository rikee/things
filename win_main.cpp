#include "win_main.h"

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hprev, PSTR cmdline, int ishow)
{
	MSG msg;
	HWND hwnd;

	switch(game)
	{
	case 't':
		winTitle = "Forty Thieves";
		break;
	case 'k':
		winTitle = "Kings Corners";
		break;
	default:
		winTitle = "Things";
	}

	hwnd = CreateCustomWindow(kClassName, winTitle, kWinWid, kWinHgt, hinstance, kBackground);

	gHDC = GetDC(hwnd);
	if(!gHDC) return EXIT_FAILURE;

	GetClientRect(hwnd, &gRect);

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

		}
	}

	UnregisterClass(kClassName.c_str(),hinstance);
	return msg.wParam;
}

HWND CreateCustomWindow(std::string szClassName, std::string winTitle, int width, int height, HINSTANCE hinstance, HBRUSH background)
{
	HWND hwnd;
	WNDCLASSEX wndclassex = {0};

	wndclassex.cbSize = sizeof(WNDCLASSEX);
	wndclassex.style = CS_HREDRAW | CS_VREDRAW;
	wndclassex.lpfnWndProc = WinProc;
	wndclassex.hInstance = hinstance;
	wndclassex.hbrBackground = background;
	wndclassex.lpszClassName = szClassName.c_str();
	wndclassex.hCursor = (HCURSOR)LoadImage(NULL, MAKEINTRESOURCE(IDC_ARROW), IMAGE_CURSOR, 0, 0, LR_SHARED);

	RegisterClassEx(&wndclassex);

	hwnd = CreateWindowEx(
		NULL,
		szClassName.c_str(),
		winTitle.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		width,
		height,
		NULL,
		NULL,
		hinstance,
		NULL
	);
	if(!hwnd) return NULL;
	
	ShowWindow(hwnd, SW_SHOWDEFAULT);
	UpdateWindow(hwnd);

	return hwnd;
}

LRESULT CALLBACK WinProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	switch(message)
	{
	case WM_DESTROY:
		ReleaseDC(hwnd,gHDC);
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, message, wparam, lparam);
}