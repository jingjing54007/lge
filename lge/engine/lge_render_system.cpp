#include "lge_platform.h"
#include "lge_logger.h"
#include "lge_util.h"
#include "lge_render_system.h"

RenderSystem::RenderSystem()
{

}

RenderSystem::~RenderSystem()
{

}

bool RenderSystem::init(HWND hwnd)
{
	m_hWnd = hwnd;
	initContext();
	return true;
}

EGLConfig RenderSystem::setEGLConfiguration()
{
    EGLint		num_config;
	EGLConfig	conf;

	// Setup the configuration list for our surface.
    EGLint conflist[] =
	{
		EGL_LEVEL, 0,
		EGL_NATIVE_RENDERABLE, EGL_FALSE,
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES_BIT,
		EGL_CONFIG_CAVEAT, EGL_NONE,
		/*
			Tell it the minimum size we want for our colour buffer and the depth size so
			eglChooseConfig will choose the config that is the closest match.
		*/
		EGL_BUFFER_SIZE, 32,
		EGL_DEPTH_SIZE, 16,
		// The PBuffer bit is the important part as it shows we want a PBuffer
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT | EGL_PBUFFER_BIT,
		EGL_BIND_TO_TEXTURE_RGBA, EGL_TRUE,
		EGL_SAMPLE_BUFFERS, 0,
		EGL_NONE
	};

	// Return null config if config is not found
    if(!eglChooseConfig(m_eglDisplay, conflist, &conf, 1, &num_config) || num_config != 1){
		lge_debug_log("Unable to choose a valid config.." );
		return 0;
    }

	// Return config index
	return conf;
}

bool RenderSystem::initContext(){

	// code followed is from ImgSdk and minimized.
	EGLint	majorVersion, minorVersion;

	m_eglContext = 0;

	m_hDC = GetDC(m_hWnd);
	m_eglDisplay = eglGetDisplay( m_hDC );

	if( m_eglDisplay == EGL_NO_DISPLAY )
		m_eglDisplay = eglGetDisplay((EGLNativeDisplayType)EGL_DEFAULT_DISPLAY);

	if(!eglInitialize(m_eglDisplay, &majorVersion, &minorVersion)){
		lge_debug_log("Unable to initialize EGL.");
		return false;
	}

	lge_debug_log("EGL %d.%d initialized.", majorVersion, minorVersion);

	if(!eglBindAPI(EGL_OPENGL_ES_API)){
		lge_debug_log( "Failed to bind OpenGL ES API." );
		return false;
	}

	m_eglConfig = setEGLConfiguration();


	EGLint ai32ContextAttribs[32];
	int	i = 0;

	//ai32ContextAttribs[i++] = EGL_CONTEXT_CLIENT_VERSION;
	//ai32ContextAttribs[i++] = 2;

	ai32ContextAttribs[i] = EGL_NONE;

	m_eglContext = eglCreateContext(m_eglDisplay, m_eglConfig, NULL, NULL);

	if( m_eglContext == EGL_NO_CONTEXT ){
		lge_debug_log( "Failed to create EGL Context." );
		return false;
	}

	EGLint		attrib_list[16];
	i = 0;
	attrib_list[i] = EGL_NONE;

	m_eglWindow = eglCreateWindowSurface(m_eglDisplay, m_eglConfig, m_hWnd, NULL);
	
	if( m_eglWindow == EGL_NO_SURFACE){
		lge_debug_log( "Failed to create window surface." );
		return false;
	}

	if ( eglMakeCurrent(m_eglDisplay, m_eglWindow, m_eglWindow, m_eglContext) == EGL_TRUE )
		return eglSwapInterval(m_eglDisplay, 1) == EGL_TRUE;
	else{
		lge_debug_log("Failed to make current context." );
		return false;
	}
}

void RenderSystem::destroy()
{
	if (m_eglDisplay != NULL)
    {
        eglMakeCurrent( m_eglDisplay, NULL, NULL, EGL_NO_CONTEXT );
        if (m_eglContext != NULL) {
            eglDestroyContext( m_eglDisplay, m_eglContext );
        }
        if (m_eglWindow != NULL) {
            eglDestroySurface( m_eglDisplay, m_eglWindow );
        }
        eglTerminate( m_eglDisplay );
    }

    m_eglWindow = NULL;
    m_eglContext = NULL;
    m_eglDisplay = NULL;
}

void RenderSystem::swapBuffers()
{
    eglSwapBuffers(m_eglDisplay, m_eglWindow);
}