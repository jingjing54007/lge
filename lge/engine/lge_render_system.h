#pragma once
#include "lge_singleton.h"
#include "lge_render_gles2.h"

class RenderSystem : public MySingleton<RenderSystem>
{
public:
	RenderSystem();
	~RenderSystem();

public:
	bool init(HWND hwnd);
	void destroy();
	void swapBuffers();

	EGLConfig setEGLConfiguration();
	bool initContext();
private:
	HWND		m_hWnd;			// ��Ҫ��ʼ����ʱ�����ⲿ����
	HDC			m_hDC;
	EGLDisplay	m_eglDisplay;
	EGLSurface	m_eglWindow;
	EGLContext	m_eglContext;
	EGLConfig	m_eglConfig;
};