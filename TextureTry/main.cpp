//
//  main.cpp
//  TextureTry
//
//  Created by Mykola Farion on 4/16/13.
//  Copyright (c) 2013 Mykola Farion. All rights reserved.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include "GLViewer.h"

//struct GLRect{
//    GLsizei/*float*/ width;
//    GLsizei/*float*/ height;
//    GLint/*float*/ x;
//    GLint/*float*/ y;
//};

//#define window_width 256
//#define window_height 256
//#define texture_width 128
//#define texture_height 128


//void keyPressed(unsigned char c, int x, int y);
void mouseClick(int button, int state, int x, int y);
void reshape(int w, int h);
void spinDisplay(void);
//void updateImage(GLubyte* buffer, int width, int height, GLRect rects[],int rectsSize);

static GLPixel fullImPixel;
static GLPixel subImPixel;
bool textureOn;
GLViewer myViewer;
std::vector<GLPixel> buffer;
std::vector<GLPixel> subImage;
std::vector<GLRect> rects;
GLint window_width = 256;
GLint window_height = 256;
GLint texture_width = 128;
GLint texture_height = 128;

void makeCheckImage(void)
{
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
    myViewer.updateImage(buffer, w, h);
    
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
                myViewer.updateImage(buffer, window_width, window_height, rects);
                
            }
            else {
                myViewer.updateImage(buffer, window_width, window_height);
               //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_width, texture_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &buffer[0]);
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
    //init();
    glutReshapeFunc(reshape);

    glutMouseFunc(mouseClick);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

