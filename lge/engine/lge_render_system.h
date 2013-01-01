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
	HWND		m_hWnd;			// 需要初始化的时候由外部传入
	HDC			m_hDC;
	EGLDisplay	m_eglDisplay;
	EGLSurface	m_eglWindow;
	EGLContext	m_eglContext;
	EGLConfig	m_eglConfig;
};