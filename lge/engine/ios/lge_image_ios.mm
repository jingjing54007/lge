//
//  lge_image_loader_ios.m
//  lge_helloworld
//
//  Created by 佳 王 on 13-1-3.
//  Copyright (c) 2013年 佳 王. All rights reserved.
//
#include "lge_platform.h"
#include "lge_image.h"

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NAMESPACE_BEGIN

Image::Image(unsigned char* data, int length)
{
    CGImageRef cgImage;
    NSData * imageData;
    
    imageData = [NSData dataWithBytes:data length:length];
    cgImage = [[UIImage imageWithData:imageData] CGImage];
    
    if(cgImage == NULL)
    {
        return;
    }
    
    // get image info
    
    m_width = CGImageGetWidth(cgImage);
    m_height = CGImageGetHeight(cgImage);
    
    CGImageAlphaInfo info = CGImageGetAlphaInfo(cgImage);
    m_hasAlpha = (info == kCGImageAlphaPremultipliedLast)
    || (info == kCGImageAlphaPremultipliedFirst)
    || (info == kCGImageAlphaLast)
    || (info == kCGImageAlphaFirst);
    
    CGColorSpaceRef colorSpace = CGImageGetColorSpace(cgImage);
    if (colorSpace)
    {
        if (m_hasAlpha)
        {
            info = kCGImageAlphaPremultipliedLast;
            m_isPremultipliedAlpha = true;
        }
        else
        {
            info = kCGImageAlphaNoneSkipLast;
            m_isPremultipliedAlpha = false;
        }
    }
    else
    {
        return;
    }
    
    // change to RGBA8888
    m_hasAlpha = true;
    m_bpp = 8;
    m_data = new unsigned char[m_width * m_height * 4];
    colorSpace = CGColorSpaceCreateDeviceRGB();
    CGContextRef context = CGBitmapContextCreate(m_data,
                                                 m_width,
                                                 m_height,
                                                 8,
                                                 4 * m_width,
                                                 colorSpace,
                                                 info | kCGBitmapByteOrder32Big);
    
    CGContextClearRect(context, CGRectMake(0, 0, m_width, m_height));
    //CGContextTranslateCTM(context, 0, 0);
    CGContextDrawImage(context, CGRectMake(0, 0,m_width, m_height), cgImage);
    
    CGContextRelease(context);
    CFRelease(colorSpace);
}

NAMESPACE_END