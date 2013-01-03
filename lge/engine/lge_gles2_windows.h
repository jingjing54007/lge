#pragma once

#ifdef __WIN32__

#include "lge_gl.h"
#include "lge_renderer.h"

// windows平台下gles2模拟器的封装(egl)

NAMESPACE_BEGIN

class RendererGLES2 : public Renderer
{
public:
	bool init(HWND hwnd);
	void destroy();
	void swapBuffers();
    
	bool initContext();
private:
	HWND		m_hWnd;			// 需要初始化的时候由外部传入
	HDC			m_hDC;
	EGLDisplay	m_eglDisplay;
	EGLSurface	m_eglWindow;
	EGLContext	m_eglContext;
	EGLConfig	m_eglConfig;
    
    
	EGLConfig setEGLConfiguration();
};

NAMESPACE_END

#endif