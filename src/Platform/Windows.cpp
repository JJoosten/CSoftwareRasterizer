#include "Platform.h"
#include "../Settings.h"

#include <GL/glew.h>
#include <GL/wglew.h>

// window setup partially copied from Pez.Windows.c to speed up development

#undef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
#undef WINVER
#define WINVER 0x0500
#undef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <stdio.h>
#include <stdlib.h>

#define CSR_WIN32_WINDOW_CLASS_NAME "WinGLSR"


typedef struct
{
	HWND windowContext;
	HGLRC renderingContext;
	HDC deviceContext;
	WNDCLASS winClass;
	HINSTANCE moduleHandle;
	Window* window;
} Win32Window;


Win32Window* g_win32Window; // global

// windows MsgProcedure (callback)
LRESULT WINAPI msgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	// check if both windows are valid
	{
		if (g_win32Window == NULL ||
			g_win32Window->window == NULL)
			return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	Window* window = g_win32Window->window;
	Keyboard* keyboard = g_win32Window->window->Keyboard;
	Mouse* mouse = g_win32Window->window->Mouse;

	int x = LOWORD(lParam);
	int y = HIWORD(lParam);

	if (mouse)
	{
		switch (msg)
		{
		case WM_LBUTTONUP:
			Mouse_SetKeyUp(mouse, csrMouseButtonLeft);
			break;
		case WM_LBUTTONDOWN:
			Mouse_SetKeyDown(mouse, csrMouseButtonLeft);
			break;
		case WM_RBUTTONUP:
			Mouse_SetKeyUp(mouse, csrMouseButtonRight);
			break;
		case WM_RBUTTONDOWN:
			Mouse_SetKeyDown(mouse, csrMouseButtonRight);
			break;
		case WM_MBUTTONUP:
			Mouse_SetKeyUp(mouse, csrMouseButtonMiddle);
			break;
		case WM_MBUTTONDOWN:
			Mouse_SetKeyDown(mouse, csrMouseButtonMiddle);
			break;
		case WM_MOUSEMOVE:
			Mouse_SetScreenPos(mouse, x, y);
			break;
		}
	}

	if (keyboard)
	{
		switch (msg)
		{
		case WM_KEYUP:
			Keyboard_SetKeyUp(keyboard, wParam);
			break;
		case WM_KEYDOWN:
			Keyboard_SetKeyDown(keyboard, wParam);
			break;
		}
	}

	switch (msg)
	{
		case WM_KEYDOWN:
		{
			switch (wParam)
			{
			case VK_ESCAPE:
				PostQuitMessage(0);
				break;
			case VK_OEM_2: // Question Mark / Forward Slash for US Keyboards
				break;
			}
			break;
		}

	case WM_SETFOCUS:
		window->HasFocus = true;
		break;
	case WM_KILLFOCUS:
		window->HasFocus = false;
		break;
	case WM_ACTIVATE:
		{
			if (LOWORD(wParam) == WA_ACTIVE)
				window->HasFocus = true;
			else
				window->HasFocus = false;
		}
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

void createWin32Window(Win32Window* const win32Window, Window* const window)
{
	win32Window->moduleHandle = GetModuleHandle(NULL);

	// setup window parameters
	{
		win32Window->winClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		win32Window->winClass.lpfnWndProc = msgProc;
		win32Window->winClass.cbClsExtra = 0;
		win32Window->winClass.cbWndExtra = 0;
		win32Window->winClass.hInstance = win32Window->moduleHandle;
		win32Window->winClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
		win32Window->winClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		win32Window->winClass.hbrBackground = NULL;
		win32Window->winClass.lpszMenuName = NULL;
		win32Window->winClass.lpszClassName = CSR_WIN32_WINDOW_CLASS_NAME;
		RegisterClass(&win32Window->winClass); 
	}

	DWORD dwStyle = WS_OVERLAPPEDWINDOW;
	DWORD dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;

	RECT rect;
	SetRect(&rect, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	window->Width = rect.right - rect.left;
	window->Height = rect.bottom - rect.top;
	window->X = GetSystemMetrics(SM_CXSCREEN) / 2 - window->Width / 2;
	window->Y = GetSystemMetrics(SM_CYSCREEN) / 2 - window->Height / 2;
	AdjustWindowRectEx(&rect, dwStyle, FALSE, dwExStyle);
	win32Window->windowContext = CreateWindowEx(dwExStyle, CSR_WIN32_WINDOW_CLASS_NAME, window->Title, dwStyle | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, window->X, window->Y, window->Width, window->Height, 0, 0, win32Window->moduleHandle, 0);

}

void destroyWin32Window(Win32Window* const win32Window)
{
	// destroy the win32 rendering context
	wglDeleteContext(win32Window->renderingContext);

	ReleaseDC(win32Window->windowContext, win32Window->deviceContext);

	// destroy the win32 window class
	DestroyWindow(win32Window->windowContext);

	UnregisterClass(CSR_WIN32_WINDOW_CLASS_NAME, win32Window->winClass.hInstance);
}

void createGLContext(Win32Window* const win32Window, Window* const window)
{
	// Create the GL context.
	int pixelFormat = 0;
	PIXELFORMATDESCRIPTOR pfd;
	DWORD dwStyle = WS_OVERLAPPEDWINDOW;
	DWORD dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;

	ZeroMemory(&pfd, sizeof(pfd));
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 8;
	pfd.iLayerType = PFD_MAIN_PLANE;

	win32Window->deviceContext = GetDC(win32Window->windowContext);
	pixelFormat = ChoosePixelFormat(win32Window->deviceContext, &pfd);

	SetPixelFormat(win32Window->deviceContext, pixelFormat, &pfd);
	win32Window->renderingContext = wglCreateContext(win32Window->deviceContext);
	wglMakeCurrent(win32Window->deviceContext, win32Window->renderingContext);

	if (CSR_ENABLE_MULTISAMPLING)
	{
		int pixelAttribs[] =
		{
			WGL_SAMPLES_ARB, 16,
			WGL_SAMPLE_BUFFERS_ARB, GL_TRUE,
			WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
			WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
			WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
			WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
			WGL_RED_BITS_ARB, 8,
			WGL_GREEN_BITS_ARB, 8,
			WGL_BLUE_BITS_ARB, 8,
			WGL_ALPHA_BITS_ARB, 8,
			WGL_DEPTH_BITS_ARB, 24,
			WGL_STENCIL_BITS_ARB, 8,
			WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
			0
		};

		int* sampleCount = pixelAttribs + 1;
		int* useSampleBuffer = pixelAttribs + 3;
		int pixelFormat = -1;
		PROC proc = wglGetProcAddress("wglChoosePixelFormatARB");
		unsigned int numFormats = 0;
		PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)proc;

		if (!wglChoosePixelFormatARB)
			printf("Could not load function pointer for 'wglChoosePixelFormatARB'.  Is your driver properly installed?");

		// Try fewer and fewer samples per pixel till we find one that is supported:
		while (pixelFormat <= 0 && *sampleCount >= 0)
		{
			wglChoosePixelFormatARB(win32Window->deviceContext, pixelAttribs, 0, 1, &pixelFormat, &numFormats);
			(*sampleCount)--;
			if (*sampleCount <= 1)
				*useSampleBuffer = GL_FALSE;
		}

		// Win32 allows the pixel format to be set only once per app, so destroy and re-create the app:
		DestroyWindow(win32Window->windowContext);
		win32Window->windowContext = CreateWindowEx(dwExStyle, CSR_WIN32_WINDOW_CLASS_NAME, window->Title, dwStyle | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, window->X, window->Y, window->Width, window->Height, 0, 0, win32Window->moduleHandle, 0);
		SetWindowPos(win32Window->windowContext, HWND_TOP, window->X, window->Y, window->Width, window->Height, 0);
		win32Window->deviceContext = GetDC(win32Window->windowContext);
		bool setPixFormat = SetPixelFormat(win32Window->deviceContext, pixelFormat, &pfd);
		win32Window->renderingContext = wglCreateContext(win32Window->deviceContext);
		wglMakeCurrent(win32Window->deviceContext, win32Window->renderingContext);
	}

	// initialize glew
	{
		GLint err = glewInit();
		if (GLEW_OK != err)
		{
			printf("GLEW Error: %s\n", glewGetErrorString(err));
			return;
		}
		printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	}

	Window_SetVSync(window, CSR_ENABLE_VSYNC);

	// make GL3+ context (forward compatible)
	if (GL_VERSION_3_0)
	{
		const int contextAttribs[] =
		{
			WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
			WGL_CONTEXT_MINOR_VERSION_ARB, 2,
			WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
			0
		};

		HGLRC newRC = wglCreateContextAttribsARB(win32Window->deviceContext, 0, contextAttribs);
		wglMakeCurrent(0, 0);
		wglDeleteContext(win32Window->renderingContext);
		win32Window->renderingContext = newRC;
		wglMakeCurrent(win32Window->deviceContext, win32Window->renderingContext);
	}

	ShowWindow(win32Window->windowContext, SW_SHOW);
}


// create window
Window* Window_Create(unsigned int x, unsigned int y, unsigned int width, unsigned int height, const char* const defaultName)
{
	// initialize application window
	Window* window = malloc(sizeof(Window));
	{ 
		memset(window, 0, sizeof(Window));
		window->X = x;
		window->Y = y;
		window->Width = width;
		window->Height = height;

		Window_SetTitle(window, defaultName);
	}

	// initialize win32 window struct
	g_win32Window = malloc(sizeof(Win32Window));
	{
		memset(g_win32Window, 0, sizeof(Win32Window));
		g_win32Window->window = window;
	}

	// create win32 window
	createWin32Window(g_win32Window, window);

	// create opengl context
	createGLContext(g_win32Window, window);

	return window;
}

void Window_Destroy(Window* const window)
{
	destroyWin32Window(g_win32Window);

	free(g_win32Window);

	free(window);
}


void Window_SetKeyboard(Window* const window, Keyboard* const keyboard)
{
	window->Keyboard = keyboard;
}

void Window_SetMouse(Window* const window, Mouse* const mouse)
{
	window->Mouse = mouse;
}

bool Window_HandleMessages(Window* const window)
{
	MSG msg = { 0 };

	// go over all messages of windows
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			return true;
		}
	}

	// when we receive WM_QUIT, we can
	return false;
}

void Window_SwapBuffer(Window* const window)
{
	SwapBuffers(g_win32Window->deviceContext);
}

void Window_SetTitle(Window* const window, const char* const title)
{
	int nameLength = strlen(title);
	if (nameLength > CSR_MAX_WINDOW_NAME_LENGTH)
	{
		printf("Name %s is %d characters long, please make it smaller then %d characters", title, nameLength, CSR_MAX_WINDOW_NAME_LENGTH);
		return;
	}

	// we add + 1 to copy the null terminator
	memcpy(window->Title, title, nameLength + 1);

	// check if we have an existing win32 window
	if (g_win32Window && g_win32Window->windowContext)
		SetWindowTextA(g_win32Window->windowContext, title);
}

void Window_SetVSync(Window* const window, bool isVSyncEnabled)
{
	wglSwapIntervalEXT(isVSyncEnabled);
}

bool Window_HasFocus(Window* const window)
{
	return window->HasFocus;
}