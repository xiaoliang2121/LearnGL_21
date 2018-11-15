// Simple.cpp
// The Simplest OpenGL program with GLUT
// OpenGL SuperBible, 3rd Edition
// Richard S. Wright Jr.
// rwright@starstonesoftware.com

#include <cstdio>
#include "gltools.h"	// OpenGL toolkit

///////////////////////////////////////////////////////////
// Called to draw scene
void RenderScene(void)
    {
    // Clear the window with current clearing color
    glClear(GL_COLOR_BUFFER_BIT);


    // Flush drawing commands
    glFlush();
    }

///////////////////////////////////////////////////////////
// Setup the rendering state
void SetupRC(void)
    {
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    }

///////////////////////////////////////////////////////////
// Main program entry point
int main(int argc, char* argv[])
    {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutCreateWindow("Simple");

    glutDisplayFunc(RenderScene);

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

