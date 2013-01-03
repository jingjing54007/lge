#include "lge_platform.h"
#import "EAGLView.h"
#include "lge_engine.h"

@implementation EAGLView
@synthesize animating;
@dynamic animationFrameInterval;
// You must implement this method
+ (Class)layerClass
{
    return [CAEAGLLayer class];
}

//The EAGL view is stored in the nib file. When it's unarchived it's sent -initWithCoder:
- (id)initWithFrame:(CGRect)frame
{    
    if ((self = [super initWithFrame:frame]))
    {	
        animating = FALSE;
        animationFrameInterval = 1;
        displayLink = nil;

        LGE::Engine::getSingleton().initGraphic((__bridge void*)self.layer);
    }

    return self;
}

- (void)drawView:(id)sender
{
    LGE::Engine::getSingleton().clear();
    
    

    LGE::Engine::getSingleton().flip();
}

- (void)layoutSubviews
{
    [self drawView:nil];
}

- (NSInteger)animationFrameInterval
{
    return animationFrameInterval;
}

- (void)setAnimationFrameInterval:(NSInteger)frameInterval
{
    // Frame interval defines how many display frames must pass between each time the
    // display link fires. The display link will only fire 30 times a second when the
    // frame internal is two on a display that refreshes 60 times a second. The default
    // frame interval setting of one will fire 60 times a second when the display refreshes
    // at 60 times a second. A frame interval setting of less than one results in undefined
    // behavior.
    if (frameInterval >= 1)
    {
        animationFrameInterval = frameInterval;

        if (animating)
        {
            [self stopAnimation];
            [self startAnimation];
        }
    }
}

- (void)startAnimation
{
    if (!animating)
    {
        displayLink = [NSClassFromString(@"CADisplayLink") displayLinkWithTarget:self selector:@selector(drawView:)];
        [displayLink setFrameInterval:animationFrameInterval];
        [displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];

        animating = TRUE;
    }
}

- (void)stopAnimation
{
    if (animating)
    {
        [displayLink invalidate];
        displayLink = nil;

        animating = FALSE;
    }
}

- (void)dealloc
{
//	CQDestroy();
}

-(BOOL)canBecomeFirstResponder
{
	return NO;
}
@end

