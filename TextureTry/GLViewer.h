//
//  GLViewer.h
//  TextureTry
//
//  Created by Mykola Farion on 4/17/13.
//  Copyright (c) 2013 Mykola Farion. All rights reserved.
//

#ifndef __TextureTry__GLViewer__
#define __TextureTry__GLViewer__

#include <vector>
#include <iostream>
#include <GLUT/GLUT.h>
#endif /* defined(__TextureTry__GLViewer__) */

struct GLRect {
    GLint width;
    GLint height;
    GLint x;
    GLint y;
};

struct GLPixel {
    GLubyte red;
    GLubyte green;
    GLubyte blue;
    GLubyte alpha;
};

class GLViewer{
    
public:
    
    // uses texture sizes
    void initWithBuffer(std::vector<GLPixel> &buffer, int width, int height);// works +
    
    // uses window width and height
    void updateImage(std::vector<GLPixel> &buffer, int width, int height);
    void updateImage(std::vector<GLPixel> &buffer, int width, int height, std::vector<GLRect> &rects);
    
    void render();
    
private:
    
    std::vector<GLPixel> subImage;
    
    GLsizei texture_width;
    GLsizei texture_height;
    GLuint texName;

    GLsizei window_width;
    GLsizei window_height;
    
    // subImage functions
    void addSubImage(std::vector<GLPixel> &subImage, GLRect &rect);
    
    // implement here grab funtion
    void grabSubTex(std::vector<GLPixel> &buffer, GLRect &rect);
    
    // size
    bool didSizeChanged(int width, int height);
};