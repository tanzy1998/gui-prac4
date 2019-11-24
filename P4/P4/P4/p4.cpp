#include <Windows.h>
#include <gl/GL.h>

#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "OpenGL Window"

float xRotateDeg = 0, yRotateDeg = 0, zRotateDeg = 0;
float yRotateDegRobot = 0, zRotateDegRobot = 0;
int page = 1;

extern "C"
{
	__declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
}

extern "C"
{
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_CHAR:
		switch (wParam)
		{
		case 0x78:
			xRotateDeg += 0.5f;
			break;
		case 0x79:
			yRotateDeg += 0.5f;
			break;
		case 0x7A:
			zRotateDeg += 0.5f;
			break;
		case VK_SPACE:
			xRotateDeg = 0;
			yRotateDeg = 0;
			zRotateDeg = 0;
			zRotateDegRobot = 0;
			yRotateDegRobot = 0;
			break;
		}
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_UP:
			zRotateDegRobot += 0.5f;
			break;
		case VK_DOWN:
			zRotateDegRobot -= 0.5f;
			break;
		case VK_LEFT:
			yRotateDegRobot -= 0.5f;
			break;
		case VK_RIGHT:
			yRotateDegRobot += 0.5f;
			break;
		case VK_F1:
			page = 1;
			break;

		case VK_F2:
			page = 2;
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------

void demo(float size) {

	glBegin(GL_QUADS);

	// front
	//red
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, size);
	glVertex3f(size, 0, size);
	glVertex3f(size, 0, 0);
	glVertex3f(0, 0, 0);

	// left
	//green
	glColor3f(0, 1, 0);
	glVertex3f(size, 0, size);
	glVertex3f(size, size, size);
	glVertex3f(size, size, 0);
	glVertex3f(size, 0, 0);
	
	// bottom
	//blue
	glColor3f(0, 0, 1);
	glVertex3f(0, size, 0);
	glVertex3f(size, size, 0);
	glVertex3f(size, 0, 0);
	glVertex3f(0, 0, 0);

	// right
	glColor3f(1, 0, 1);
	glVertex3f(0, size, size);
	glVertex3f(0, 0, size);
	glVertex3f(0, 0, 0);
	glVertex3f(0, size, 0);

	// behind
	//white
	glColor3f(0, 1, 1);
	glVertex3f(0, size, size);
	glVertex3f(size, size, size);
	glVertex3f(size, size, 0);
	glVertex3f(0, size, 0);

	// top
	//black
	glColor3f(1, 1, 1);
	glVertex3f(0, size, size);
	glVertex3f(size, size, size);
	glVertex3f(size, 0, size);
	glVertex3f(0, 0, size);

	glEnd();
}

void pyramid() {

	glPushMatrix();
	
	glRotatef(xRotateDeg+24, 1, 0, 0);
	glRotatef(yRotateDeg+24, 0, 1, 0);
	glRotatef(zRotateDeg+24, 0, 0, 1);
	
	glBegin(GL_LINE_LOOP);
	glColor3f(1, 1, 1);
	glVertex3f(0, 0.5, -0.3);
	glVertex3f(-0.2, 0, 0);
	glVertex3f(0.2, 0, 0);

	glColor3f(1, 1, 1);
	glVertex3f(0, 0.5, -0.3);
	glVertex3f(-0.2, 0, 0);
	glVertex3f(-0.2, 0, -0.5);

	glColor3f(1, 1, 1);
	glVertex3f(0, 0.5, -0.3);
	glVertex3f(0.2, 0, 0);
	glVertex3f(0.2, 0, -0.5);

	glColor3f(1, 1, 1);
	glVertex3f(0, 0.5, -0.3);
	glVertex3f(0.2, 0, -0.5);
	glVertex3f(-0.2, 0, -0.5);

	

	glEnd();
	glPopMatrix();

}

void robotlowerarm(float yRotateDeg, float zRotateDeg) {
	glPushMatrix();
	glRotatef(yRotateDeg, 0, 1, 0);
	glRotatef(zRotateDeg, 0, 0, 1);

	glBegin(GL_LINE_LOOP);
	glColor3f(1, 1, 1);

	// Front
	glVertex3f(0, 0.2, 0.1f);
	glVertex3f(0.5, 0.2, 0.1f);
	glVertex3f(0.5, 0, 0.1f);
	glVertex3f(0, 0, 0.1f);

	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(yRotateDeg, 0, 1, 0);
	glRotatef(zRotateDeg, 0, 0, 1);

	glBegin(GL_LINE_LOOP);
	glColor3f(1, 1, 1);

	//Bottom
	glVertex3f(0.5, 0, 0.1f);
	glVertex3f(0.5, 0, -0.1f);
	glVertex3f(0, 0, -0.1f);
	glVertex3f(0, 0, 0.1f);

	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(yRotateDeg, 0, 1, 0);
	glRotatef(zRotateDeg, 0, 0, 1);

	glBegin(GL_LINE_LOOP);
	glColor3f(1, 1, 1);

	// Back
	glVertex3f(0.5, 0.2, -0.1f);
	glVertex3f(0, 0.2, -0.1f);
	glVertex3f(0, 0, -0.1f);
	glVertex3f(0.5, 0, -0.1f);
	
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(yRotateDeg, 0, 1, 0);
	glRotatef(zRotateDeg, 0, 0, 1);

	glBegin(GL_LINE_LOOP);
	glColor3f(1, 1, 1);

	// Top
	glVertex3f(0, 0.2, 0.1f);
	glVertex3f(0, 0.2, -0.1f);
	glVertex3f(0.5, 0.2, -0.1f);
	glVertex3f(0.5, 0.2, 0.1f);

	glEnd();
	glPopMatrix();
}

void robotupperarm(float yRotateDeg, float zRotateDeg) {
	glPushMatrix();
	glRotatef(yRotateDeg, 0, 1, 0);
	glRotatef(zRotateDeg, 0, 0, 1);

	glBegin(GL_LINE_LOOP);
	glColor3f(1, 1, 1);

	// Front
	glVertex3f(0, 0.2, 0.1f);
	glVertex3f(-0.5, 0.2, 0.1f);
	glVertex3f(-0.5, 0, 0.1f);
	glVertex3f(0, 0, 0.1f);

	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(yRotateDeg, 0, 1, 0);
	glRotatef(zRotateDeg, 0, 0, 1);

	glBegin(GL_LINE_LOOP);
	glColor3f(1, 1, 1);

	//Bottom
	glVertex3f(-0.5, 0, 0.1f);
	glVertex3f(-0.5, 0, -0.1f);
	glVertex3f(0, 0, -0.1f);
	glVertex3f(0, 0, 0.1f);

	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(yRotateDeg, 0, 1, 0);
	glRotatef(zRotateDeg, 0, 0, 1);

	glBegin(GL_LINE_LOOP);
	glColor3f(1, 1, 1);

	// Back
	glVertex3f(-0.5, 0.2, -0.1f);
	glVertex3f(0, 0.2, -0.1f);
	glVertex3f(0, 0, -0.1f);
	glVertex3f(-0.5, 0, -0.1f);

	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(yRotateDeg, 0, 1, 0);
	glRotatef(zRotateDeg, 0, 0, 1);

	glBegin(GL_LINE_LOOP);
	glColor3f(1, 1, 1);

	// Top
	glVertex3f(0, 0.2, 0.1f);
	glVertex3f(0, 0.2, -0.1f);
	glVertex3f(-0.5, 0.2, -0.1f);
	glVertex3f(-0.5, 0.2, 0.1f);

	glEnd();
	glPopMatrix();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	switch (page)
	{
	case 1:
		pyramid();
		break;
	case 2:
		robotlowerarm(yRotateDegRobot, zRotateDegRobot);
		robotupperarm(yRotateDegRobot, 0);
		break;

	default:
		break;
	}
	
}
//--------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 800,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		display();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------
