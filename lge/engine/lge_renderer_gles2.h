#pragma once

#include "lge_gl.h"
#include "lge_renderer.h"

NAMESPACE_BEGIN

class RendererGLES2 : public Renderer
{
public:
    RendererGLES2(HWND hwnd);
    ~RendererGLES2();
    
    virtual void beginScene();
    virtual void endScene();
	virtual void flip();
    virtual void clear();
    
private:
#ifdef __WIN32__
#elif defined __IOS__
    
#elif defined __ANDROID__
#endif
};

NAMESPACE_END