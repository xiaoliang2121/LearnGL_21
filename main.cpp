// Simple.cpp
// The Simplest OpenGL program with GLUT
// OpenGL SuperBible, 3rd Edition
// Richard S. Wright Jr.
// rwright@starstonesoftware.com

#include <cstdio>
#include "gltools.h"	// OpenGL toolkit
#include <cmath>

///////////////////////////////////////////////////////////
// Called to draw scene
void RenderScene(void)
    {
        static GLdouble dRadius = 0.1;
        static GLdouble dAngle = 0.0;

        // Clear blue window
        glClearColor(0.0f, 0.0f, 1.0f, 0.0f);

        if(dAngle == 0.0)
            glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_POINTS);
            glVertex2d(dRadius * cos(dAngle), dRadius * sin(dAngle));
        glEnd();

        dRadius *= 1.01;
        dAngle += 0.1;

        if(dAngle > 30.0)
            {
            dRadius = 0.1;
            dAngle = 0.0;
            }

        glFlush();
        }

///////////////////////////////////////////////////////////
// Trigger a repaint
void Timer(int value)
    {
    glutTimerFunc(50,Timer, 0);
    glutPostRedisplay();
    }


///////////////////////////////////////////////////////////
// Set viewport and projection
void ChangeSize(int w, int h)
    {
    // Prevent a divide by zero
    if(h == 0)
        h = 1;

    // Set Viewport to window dimensions
        glViewport(0, 0, w, h);


    // Set the perspective coordinate system
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Set 2D Coordinate system
    gluOrtho2D(-4.0, 4.0, -3.0, 3.0);

    // Modelview matrix reset
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    }

///////////////////////////////////////////////////////////
// Main program entry point
int main(int argc, char* argv[])
    {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800,600);
    glutCreateWindow("OpenGL Single Buffered");

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

//    SetupRC();
    glutTimerFunc(50,Timer,0);
    glutMainLoop();

    return 0;
    }

