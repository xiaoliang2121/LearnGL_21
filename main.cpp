// Simple.cpp
// The Simplest OpenGL program with GLUT
// OpenGL SuperBible, 3rd Edition
// Richard S. Wright Jr.
// rwright@starstonesoftware.com

#include <cstdio>
#include "gltools.h"	// OpenGL toolkit
#include <cmath>

#define GL_PI 3.1415f

// Rotation amounts
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

///////////////////////////////////////////////////////////
// Called to draw scene
void RenderScene(void)
    {
    GLfloat x,y,z,angle;

    // Clear the window with current clearing color
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    glRotatef(xRot,1.0f,0.0f,0.0f);
    glRotatef(yRot,0.0f,1.0f,0.0f);

    glBegin(GL_LINE_STRIP);
        z = -50.0f;
        for(angle=0.0f; angle<=(2.0f*GL_PI)*3.0f; angle+=0.1f)
        {
            x = 50.0f*sin(angle);
            y = 50.0f*cos(angle);

            glVertex3f(x,y,z);
            z += 0.5f;
        }
    glEnd();

    glPopMatrix();


    // Flush drawing commands
    glutSwapBuffers();
    }

void ChangeSize(int w, int h){
    GLfloat nRange = 100.0f;

    if(h == 0)
        h = 1;

    glViewport(0,0,w,h);

    // Reset projection matrix stack
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if(w <= h)
        glOrtho(-nRange,nRange,-nRange*h/w,nRange*h/w,-nRange,nRange);
    else
        glOrtho(-nRange*w/h,nRange*w/h,-nRange,nRange,-nRange,nRange);

    // Reset Model view matrix stack
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void SpecialKeys(int key, int x, int y){
    if(key == GLUT_KEY_UP)
        xRot-= 5.0f;

    if(key == GLUT_KEY_DOWN)
        xRot += 5.0f;

    if(key == GLUT_KEY_LEFT)
        yRot -= 5.0f;

    if(key == GLUT_KEY_RIGHT)
        yRot += 5.0f;

    if(key > 356.0f)
        xRot = 0.0f;

    if(key < -1.0f)
        xRot = 355.0f;

    if(key > 356.0f)
        yRot = 0.0f;

    if(key < -1.0f)
        yRot = 355.0f;

    // Refresh the Window
    glutPostRedisplay();
}

///////////////////////////////////////////////////////////
// Setup the rendering state
void SetupRC(void)
    {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glColor3f(0.0f,1.0f,0.0f);
    }

///////////////////////////////////////////////////////////
// Main program entry point
int main(int argc, char* argv[])
    {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800,600);
    glutCreateWindow("Line Strips Example");

    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKeys);

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

