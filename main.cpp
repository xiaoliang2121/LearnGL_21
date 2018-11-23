// Simple.cpp
// The Simplest OpenGL program with GLUT
// OpenGL SuperBible, 3rd Edition
// Richard S. Wright Jr.
// rwright@starstonesoftware.com

#include <cstdio>
#include "gltools.h"	// OpenGL toolkit

// Array containing the six vertices of the cube
static GLfloat corners[] = { -25.0f, 25.0f, 25.0f, // 0 // Front of cube
                              25.0f, 25.0f, 25.0f, // 1
                              25.0f, -25.0f, 25.0f,// 2
                             -25.0f, -25.0f, 25.0f,// 3
                             -25.0f, 25.0f, -25.0f,// 4  // Back of cube
                              25.0f, 25.0f, -25.0f,// 5
                              25.0f, -25.0f, -25.0f,// 6
                             -25.0f, -25.0f, -25.0f };// 7

// Array of indexes to create the cube
static GLubyte indexes[] = { 0, 1, 2, 3,	// Front Face
                             4, 5, 1, 0,	// Top Face
                             3, 2, 6, 7,	// Bottom Face
                             5, 4, 7, 6,	// Back Face
                             1, 5, 6, 2,	// Right Face
                             4, 0, 3, 7 };	// Left Face

// Rotation amounts
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

///////////////////////////////////////////////////////////
// Called to draw scene
void RenderScene(void)
{
    // Clear the window with current clearing color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glTranslatef(0.0f,0.0f,-200.0f);

        glRotatef(xRot,1.0f,0.0f,0.0f);
        glRotatef(yRot,0.0f,1.0f,0.0f);

        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3,GL_FLOAT,0,corners);

        glDrawElements(GL_QUADS,24,GL_UNSIGNED_BYTE,indexes);

    glPopMatrix();

    // Flush drawing commands
    glutSwapBuffers();
}

///////////////////////////////////////////////////////////////////////////////
// Process arrow keys
void SpecialKeys(int key, int x, int y)
    {
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
    gluPerspective(35.0f, (float)w/(float)h, 1.0f, 1000.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

///////////////////////////////////////////////////////////
// Setup the rendering state
void SetupRC(void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glColor3ub(0,0,0);
}

///////////////////////////////////////////////////////////
// Main program entry point
int main(int argc, char* argv[])
    {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Cube DX");

    glutDisplayFunc(RenderScene);
    glutSpecialFunc(SpecialKeys);
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

