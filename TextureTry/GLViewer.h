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
    
    void render();
    
    // uses texture sizes
    void initWithBuffer(std::vector<GLPixel> &buffer, int width, int height);// works +
    void updateImage(std::vector<GLPixel> &buffer, int width, int height);
    void updateImage(std::vector<GLPixel> &buffer/*, int width, int height*/, std::vector<GLRect> &rects);
    
    // uses window sizes
    void reshape(int width, int height);
    
    ~GLViewer()
    {
        removeTexture(1, &texName);
    }
    
    
private:
    
    std::vector<GLPixel> subImage;
    
    GLsizei texture_width;
    GLsizei texture_height;
    GLuint texName;

    GLsizei window_width;
    GLsizei window_height;
    
    // texture functions
    void addTexImage(std::vector<GLPixel> &texImage, GLint width, GLint height);
    void removeTexture(GLsizei n, const GLuint *textureNames);
    
    // subImage
    void addSubImage(std::vector<GLPixel> &subImage, GLRect &rect);
    
    // getting subtexture from texture
    void grabSubTex(std::vector<GLPixel> &buffer, GLRect &rect);
    
    // size
    bool didSizeChanged(int width, int height);
};