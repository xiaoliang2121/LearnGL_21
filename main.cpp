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

// Flags for effects
int iCull = 0;
int iOutline = 0;
int iDepth = 0;

///////////////////////////////////////////////////////////
// Reset flags as appropriate in response to menu selections
/**
 * @brief ProcessMenu
 * @param value
 */
void ProcessMenu(int value){
    switch(value)
    {
    case 1:
        iDepth = !iDepth;
        break;
    case 2:
        iCull = !iCull;
        break;
    case 3:
        iOutline = !iOutline;
    default:
        break;
    }
}


// Called to draw scene
void RenderScene(void)
{
    // Clear the window with current clearing color
    glClear(GL_COLOR_BUFFER_BIT);

    // Enable smooth shading
    glShadeModel(GL_SMOOTH);

    // Draw the triangle
    glBegin(GL_TRIANGLES);
        // Red Apex
        glColor3ub((GLubyte)255,(GLubyte)0,(GLubyte)0);
        glVertex3f(0.0f,200.0f,0.0f);

        // Green on the right bottom corner
        glColor3ub((GLubyte)0,(GLubyte)255,(GLubyte)0);
        glVertex3f(200.0f,-70.0f,0.0f);

        // Blue on the left bottom corner
        glColor3ub((GLubyte)0,(GLubyte)0,(GLubyte)255);
        glVertex3f(-200.0f, -70.0f, 0.0f);
    glEnd();

    // Flush drawing commands
    glutSwapBuffers();
}

void ChangeSize(int w, int h){
    GLfloat windowHeight,windowWidth;

    if(h == 0)
        h = 1;

    glViewport(0,0,w,h);

    // Reset projection matrix stack
//    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Window is higher than wide
    if (w <= h)
    {
        windowHeight = 250.0f*h/w;
        windowWidth = 250.0f;
    }
    else
    {
        // Window is wider than high
        windowWidth = 250.0f*w/h;
        windowHeight = 250.0f;
    }

    // Set the clipping volume
    glOrtho(-windowWidth, windowWidth, -windowHeight, windowHeight, 1.0f, -1.0f);
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
}

///////////////////////////////////////////////////////////
// Main program entry point
int main(int argc, char* argv[])
    {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800,600);
    glutCreateWindow("RGB Triangle");

    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
//    glutSpecialFunc(SpecialKeys);

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

