// Simple.cpp
// The Simplest OpenGL program with GLUT
// OpenGL SuperBible, 3rd Edition
// Richard S. Wright Jr.
// rwright@starstonesoftware.com

#include <cstdio>
#include "gltools.h"	// OpenGL toolkit

// Bitmap of camp fire
GLubyte fire[128] = { 0x00, 0x00, 0x00, 0x00,
                   0x00, 0x00, 0x00, 0x00,
                   0x00, 0x00, 0x00, 0x00,
                   0x00, 0x00, 0x00, 0x00,
                   0x00, 0x00, 0x00, 0x00,
                   0x00, 0x00, 0x00, 0x00,
                   0x00, 0x00, 0x00, 0xc0,
                   0x00, 0x00, 0x01, 0xf0,
                   0x00, 0x00, 0x07, 0xf0,
                   0x0f, 0x00, 0x1f, 0xe0,
                   0x1f, 0x80, 0x1f, 0xc0,
                   0x0f, 0xc0, 0x3f, 0x80,
                   0x07, 0xe0, 0x7e, 0x00,
                   0x03, 0xf0, 0xff, 0x80,
                   0x03, 0xf5, 0xff, 0xe0,
                   0x07, 0xfd, 0xff, 0xf8,
                   0x1f, 0xfc, 0xff, 0xe8,
                   0xff, 0xe3, 0xbf, 0x70,
                   0xde, 0x80, 0xb7, 0x00,
                   0x71, 0x10, 0x4a, 0x80,
                   0x03, 0x10, 0x4e, 0x40,
                   0x02, 0x88, 0x8c, 0x20,
                   0x05, 0x05, 0x04, 0x40,
                   0x02, 0x82, 0x14, 0x40,
                   0x02, 0x40, 0x10, 0x80,
                   0x02, 0x64, 0x1a, 0x80,
                   0x00, 0x92, 0x29, 0x00,
                   0x00, 0xb0, 0x48, 0x00,
                   0x00, 0xc8, 0x90, 0x00,
                   0x00, 0x85, 0x10, 0x00,
                   0x00, 0x03, 0x00, 0x00,
                   0x00, 0x00, 0x10, 0x00 };

///////////////////////////////////////////////////////////
// Called to draw scene
void RenderScene(void)
{
    GLubyte *pImage = NULL;
    GLint iWidth,iHeight,iComponents;
    GLenum eFormat;

    // Clear the window with current clearing color
    glClear(GL_COLOR_BUFFER_BIT);

    glPixelStorei(GL_UNPACK_ALIGNMENT,1);

    pImage = (GLubyte *)gltLoadTGA("../LearnGL_21/Res/fire.tga",&iWidth,&iHeight,&iComponents,
                        &eFormat);

    glRasterPos2i(0,0);

    if(pImage != NULL)
        glDrawPixels(iWidth,iHeight,eFormat,GL_UNSIGNED_BYTE,pImage);

    free(pImage);


    // Flush drawing commands
    glutSwapBuffers();
}

// Set coordinate system to match window coordinates
void ChangeSize(int w, int h)
{
    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if(h == 0)
        h = 1;

    glViewport(0, 0, w, h);

    // Reset the coordinate system before modifying
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Psuedo window coordinates
    gluOrtho2D(0.0, (GLfloat) w, 0.0f, (GLfloat) h);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

///////////////////////////////////////////////////////////
// Setup the rendering state
void SetupRC(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

///////////////////////////////////////////////////////////
// Main program entry point
int main(int argc, char* argv[])
    {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(512, 512);
    glutCreateWindow("OpenGL Bitmaps");

    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);

    // 获取OpenGL版本号和厂商信息
    const GLubyte *name = glGetString(GL_VENDOR);
    const GLubyte *label = glGetString(GL_RENDERER);
    const GLubyte *glVersion = glGetString(GL_VERSION);
    const GLubyte *gluVersion = glGetString(GLU_VERSION);

    printf("OpenGL实现厂商的名字：%s\n",name);
    printf("渲染器标识符：%s\n",label);
    printf("OpenGL实现的版本号：%s\n",glVersion);
    printf("GLU工具库版本：%s\n",gluVersion);

    SetupRC();

    glutMainLoop();

    return 0;
    }

