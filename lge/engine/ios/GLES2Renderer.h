//
//  GLES2Renderer.h
//  lge_helloworld
//
//  Created by 佳 王 on 13-1-3.
//  Copyright (c) 2013年 佳 王. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <QuartzCore/QuartzCore.h>
#import <OpenGLES/EAGL.h>
#import <OpenGLES/EAGLDrawable.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>


// ios平台下gles2的封装
@interface GLES2Renderer : NSObject
{
    // The pixel dimensions of the CAEAGLLayer
    GLint backingWidth_;
    GLint backingHeight_;
    
    unsigned int    samplesToUse_;
    BOOL            multiSampling_;
    
    unsigned int    depthFormat_;
    unsigned int    pixelFormat_;
    
    // The OpenGL ES names for the framebuffer and renderbuffer used to render to this view
    GLuint defaultFramebuffer_;
    GLuint colorRenderbuffer_;
    GLuint depthBuffer_;
    
    
    //buffers for MSAA
    GLuint msaaFramebuffer_;
    GLuint msaaColorbuffer_;
    
    EAGLContext *context_;
}

- (id) initWithDepthFormat:(unsigned int)depthFormat withPixelFormat:(NSString*)pixelFormat withSharegroup:(EAGLSharegroup*)sharegroup withMultiSampling:(BOOL) multiSampling withNumberOfSamples:(unsigned int) requestedSamples;

- (BOOL) resizeFromLayer:(CAEAGLLayer *)layer;
- (void)swapBuffers;
- (CGSize) backingSize;

/** Color Renderbuffer */
@property (nonatomic,readonly) GLuint colorRenderbuffer;

/** Default Renderbuffer */
@property (nonatomic,readonly) GLuint defaultFramebuffer;

/** MSAA Framebuffer */
@property (nonatomic,readonly) GLuint msaaFramebuffer;

/** MSAA Color Buffer */
@property (nonatomic,readonly) GLuint msaaColorbuffer;

/** EAGLContext */
@property (nonatomic,readonly) EAGLContext* context;
@end
