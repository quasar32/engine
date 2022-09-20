#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define CLIENT_WIDTH 640
#define CLIENT_HEIGHT 480

static HINSTANCE g_ins;
static HWND g_wnd;

static LRESULT __stdcall wnd_proc(HWND wnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(wnd, msg, wp, lp);
}

static void create_main_window(void)
{
	WNDCLASS wc;
	RECT rect;
	int width;
	int height;

	ZeroMemory(&wc, sizeof(wc));
	wc.style = CS_VREDRAW | CS_HREDRAW; 
	wc.lpfnWndProc = wnd_proc;
	wc.hInstance = g_ins;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); 
	wc.lpszClassName = L"WndClass"; 

	if (!RegisterClass(&wc)) {
		MessageBox(NULL, L"Window registration failed", 
				L"Error", MB_ICONERROR);
		exit(1);
	}

	rect.left = 0;
	rect.top = 0;
	rect.right = CLIENT_WIDTH;
	rect.bottom = CLIENT_HEIGHT;
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	width = rect.right - rect.left;
	height = rect.bottom - rect.top;

	g_wnd = CreateWindow(wc.lpszClassName, L"Engine", WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, width, height, 
			NULL, NULL, g_ins, NULL);
	if (!g_wnd) {
		MessageBox(NULL, L"Window creation failed", 
				L"Error", MB_ICONERROR);
		exit(1);
	}

	ShowWindow(g_wnd, SW_SHOW);
}

static void msg_loop(void)
{
	MSG msg; 

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

int __stdcall wWinMain(HINSTANCE ins, HINSTANCE prev, LPWSTR cmd, int show) 
{
	UNREFERENCED_PARAMETER(prev);
	UNREFERENCED_PARAMETER(cmd);
	UNREFERENCED_PARAMETER(show);

	g_ins = ins;
	create_main_window();
	msg_loop();
	
	return 0;
}
