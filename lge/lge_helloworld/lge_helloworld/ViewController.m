//
//  ViewController.m
//  lge_helloworld
//
//  Created by 佳 王 on 13-1-3.
//  Copyright (c) 2013年 佳 王. All rights reserved.
//

#import "ViewController.h"
@implementation ViewController
@synthesize glView;

-(void)loadView
{
    CGRect rect = [[UIScreen mainScreen]bounds];
    glView = [[EAGLView alloc]initWithFrame:rect];
    self.view = glView;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}
@end
