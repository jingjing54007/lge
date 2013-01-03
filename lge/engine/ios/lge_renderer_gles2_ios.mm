//
//  lge_renderer_gles2_ios.mm
//  lge_helloworld
//
//  Created by 佳 王 on 13-1-3.
//  Copyright (c) 2013年 佳 王. All rights reserved.
//
#include "lge_platform.h"
#include "lge_renderer_gles2.h"

#import "GLES2Renderer.h"
#import "EAGLView.h"

NAMESPACE_BEGIN

GLES2Renderer* g_renderer = nil;

RendererGLES2::RendererGLES2(HWND hWnd)
{
    // Get the layer
    CAEAGLLayer *eaglLayer = (__bridge CAEAGLLayer *)hWnd;
    
    eaglLayer.opaque = TRUE;
    eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:
                                    [NSNumber numberWithBool:NO], kEAGLDrawablePropertyRetainedBacking, kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat, nil];

    g_renderer = [[GLES2Renderer alloc]initWithDepthFormat:GL_DEPTH_COMPONENT16 withPixelFormat:kEAGLColorFormatRGBA8 withSharegroup:nil withMultiSampling:NO withNumberOfSamples:0];
    [g_renderer resizeFromLayer:eaglLayer];
}

RendererGLES2::~RendererGLES2()
{
}

void RendererGLES2::flip()
{
    [g_renderer swapBuffers];
}



NAMESPACE_END