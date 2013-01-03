//
//  ViewController.h
//  lge_helloworld
//
//  Created by 佳 王 on 13-1-3.
//  Copyright (c) 2013年 佳 王. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "EAGLView.h"

@interface ViewController : UIViewController
{
    EAGLView* glView;
}

@property(nonatomic, retain) EAGLView* glView;
@end
