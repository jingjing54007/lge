#include "lge_platform.h"
#include "lge_logger.h"
#include "lge_util.h"
#include "lge_renderer_gles2.h"

NAMESPACE_BEGIN

void RendererGLES2::beginScene()
{
}

void RendererGLES2::endScene()
{
}

void RendererGLES2::clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

NAMESPACE_END