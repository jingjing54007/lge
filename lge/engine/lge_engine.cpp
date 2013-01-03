
#include "lge_platform.h"

#include "lge_engine.h"
#include "lge_renderer_gles2.h"

NAMESPACE_BEGIN

Engine::Engine()
{
}

Engine::~Engine()
{
}

bool Engine::initGraphic(HWND hWnd)
{
    m_renderer = new RendererGLES2(hWnd);
    return true;
}


void Engine::beginScene()
{
    m_renderer->beginScene();
}

void Engine::endScene()
{
    m_renderer->endScene();
}

void Engine::flip()
{
    m_renderer->flip();
}

void Engine::clear()
{
    m_renderer->clear();
}
NAMESPACE_END