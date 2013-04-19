//
//  GLViewer.cpp
//  TextureTry
//
//  Created by Mykola Farion on 4/17/13.
//  Copyright (c) 2013 Mykola Farion. All rights reserved.
//
#include "GLViewer.h"


// used just for white rect generation for test
std::vector<GLPixel> genTestSubTex(int width, int height)
{
    std::vector<GLPixel> mySubTex;
    GLPixel subImPixel;
    int color;
    for (int i = 1; i <= height; i++)
    {
        for(int j = 1; j <= width; j++)
        {
            if(i%2==0) {
                color = 0;
            } else {
                if(j%2){
                    color = 125;
                } else {
                    color = 255;
                }
            }
            subImPixel.red = (GLubyte) color;
            subImPixel.green = (GLubyte) color;
            subImPixel.blue = (GLubyte) color;
            subImPixel.alpha = (GLubyte) 255;
            mySubTex.push_back(subImPixel);
        }
    }
    return mySubTex;
}

/*void GLViewer::grabSubTex(std::vector<GLPixel> &buffer, GLRect &rect)
{
    int position; //= rect.y*texture_width+rect.x;
    
    for (int i=0;i<rect.height;i++)
    {
        position = rect.y*i*texture_width+rect.x;
        
        for(int j=0;j<rect.width;j++)
        {
            subImage.push_back(buffer[position]);
            position++;
        }
    }
}*/

bool GLViewer::didSizeChanged(int width, int height)
{
    if((width!=texture_width)||(height!=texture_height))
    {
        return true;
    }
    else {
        return false;
    }
}

void GLViewer::updateImage(std::vector<GLPixel> &buffer, int width, int height)
{
    bool needSizeUpdate = didSizeChanged(width,height);

    if(needSizeUpdate)
    {
        //check for scale without stretching image property
        GLfloat wRatio = (GLfloat) width/ (GLfloat)texture_width;
        GLfloat hRatio = (GLfloat) height/ (GLfloat)texture_height;
        if((wRatio != hRatio)&& needSizeUpdate)
        {
            GLfloat minRatio = (wRatio-hRatio<0)?wRatio:hRatio;
            width = minRatio * texture_width;
            height = minRatio * texture_height;
        }
        //update image
        window_width = width;
        window_height = height;
        //glLoadIdentity();
        glViewport(0, 0, window_width, window_height);
        //glMatrixMode(GL_PROJECTION);
    }
}

void GLViewer::updateImage(std::vector<GLPixel> &buffer, int width, int height,std::vector <GLRect> &rects)
{
    
    GLRect winRect;
    GLRect texRect;
    GLfloat ratioH = (GLfloat)texture_height/(GLfloat)window_height;
    GLfloat ratioW = (GLfloat)texture_height/(GLfloat)window_height;
    
    // work with each rect 
    while(!rects.empty())
    {
        //clear subImage
        while(!subImage.empty())
        {
            subImage.pop_back();
        }
        
        //get rect in win sizes
        winRect = rects.back();
        
        // convert rect to tex coordinates
        texRect.height = winRect.height*ratioH;
        texRect.width = winRect.width*ratioW;
        texRect.x = winRect.x * ratioW;
        texRect.y = winRect.y * ratioH;

        
        
//////////////////////////////////////////////
//        IMPLEMENT HERE RECTANGLE GRAB

        subImage = genTestSubTex(texRect.width, texRect.height);
        //grabSubTex(buffer, texRect);
//////////////////////////////////////////////
        
        addSubImage(subImage, texRect);
        rects.pop_back();
    }
    
    // full image update
    updateImage(buffer,width,height);
}


void GLViewer::addSubImage(std::vector<GLPixel> &subImage, GLRect &rect)
{
    glTexSubImage2D(GL_TEXTURE_2D, 0, rect.x, rect.y, rect.width , rect.height, GL_RGBA, GL_UNSIGNED_BYTE, &subImage[0]);
}
    
void GLViewer::initWithBuffer(std::vector<GLPixel> &buffer, int width, int height)
{
    texture_width = width;
    texture_height = height;
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &texName);
    glBindTexture(GL_TEXTURE_2D, texName);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_width, texture_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &buffer[0]);
}

void GLViewer::render(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    //-------------RENDER----------
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texName);
    glBegin(GL_QUADS);
    
    glTexCoord2f(0.0, 0.0);
    glVertex2f(-1.0, -1.0);
    
    glTexCoord2f(0.0, 1.0);
    glVertex2f(-1.0, 1.0);
    
    glTexCoord2f(1.0, 1.0);
    glVertex2f(1.0, 1.0);
    
    glTexCoord2f(1.0, 0.0);
    glVertex2f(1.0, -1.0);
    
    glEnd();
    //--------------------------------
    glFlush();
    glDisable(GL_TEXTURE_2D);
}