//
//  main.cpp
//  TextureTry
//
//  Created by Mykola Farion on 4/16/13.
//  Copyright (c) 2013 Mykola Farion. All rights reserved.
//

/*  Developer guide
    
    Texture sizes must be 2^n, where n - unsigned number;
    updateImage(buffer, texture_width, texture_height) redraw all texture, buffer - new image;
    updateImage(buffer, rects) replace rects in used texture, it gets rect from new image and set it;
    
    NOTE, to see what updateImage changes - find in GLViewer.cpp  method called
    void GLViewer::updateImage(std::vector<GLPixel> &buffer,std::vector <GLRect> &rects)
    and make change which is in comment. 
    After it run program and click  - left mouse for view update methods perform;
                                    - right mouse for exit;
    Window resizing  will save ratio of texture sides and display maximum posible for insert texture.
 */


#include <iostream>
#include <GLUT/GLUT.h>
#include "GLViewer.h"



void makeCheckImage(void);
void display(void);
void mouseClick(int button, int state, int x, int y);
void reshape(int w, int h);

static GLPixel fullImPixel;
static GLPixel subImPixel;
bool textureOn;
GLViewer myViewer;
std::vector<GLPixel> buffer;
std::vector<GLPixel> subImage;
std::vector<GLRect> rects;

//window and texture consts 
GLint window_width = 256;
GLint window_height = 256;
GLint texture_width = 128;
GLint texture_height = 128;

void makeCheckImage(void)
{
    while(!buffer.empty())
    {
        buffer.pop_back();
    }
    int i, j, c;
    for (i = 0; i < texture_width; i++)
    {
        for(j = 0; j < texture_width; j++)
        {
            
            if((i<12)&&(j<12))
            {
                c = (((i&0x4) == 0)^((j&0x4) == 0))*255;
                subImPixel.red = (GLubyte) c;
                subImPixel.green = (GLubyte) c;
                subImPixel.blue = (GLubyte) c;
                subImPixel.alpha = (GLubyte) 255;
                subImage.push_back(subImPixel);
            }
    
            fullImPixel.red = (GLubyte) 2*i;
            fullImPixel.green = (GLubyte) 2*j;
            fullImPixel.blue = (GLubyte) (texture_width-1-i)+(texture_height-1-j);
            fullImPixel.alpha = (GLubyte) 255;
            buffer.push_back(fullImPixel);
        }
    }
}


void display()
{
    myViewer.render();
}

void reshape(int w, int h)
{
    window_height = h;
    window_width = w;
    myViewer.reshape(w,h);
    
}

void mouseClick(int button, int state, int x, int y)
{
    if(button == GLUT_RIGHT_BUTTON) {
        exit(0);
    }
    if (button == GLUT_LEFT_BUTTON) {
        if(state == GLUT_DOWN) {
            GLRect rect,rect2;
            rect.height = 12;
            rect.width = 12;
            rect.x = 40;
            rect.y = 44;
            rect2 = rect;
            rect2.x = 3;
            rect2.y = 2;
            rect2.height = 18;
            rect2.width = 7;
            rects.push_back(rect);
            rects.push_back(rect2);
            textureOn = !textureOn;
            if(textureOn){
                myViewer.updateImage(buffer, rects);
            }
            else {
                myViewer.updateImage(buffer, texture_width, texture_height);
            }
            glutPostRedisplay();
        }
    }
}


int main(int argc,  char* argv[])
{

    
    makeCheckImage();
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_SINGLE| GLUT_RGB);
    glutInitWindowPosition(160,160);
    glutInitWindowSize(window_width, window_height);
    glutCreateWindow("OpenGL window");
    myViewer.initWithBuffer(buffer,texture_width,texture_height);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouseClick);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

