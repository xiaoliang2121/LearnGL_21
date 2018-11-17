// Simple.cpp
// The Simplest OpenGL program with GLUT
// OpenGL SuperBible, 3rd Edition
// Richard S. Wright Jr.
// rwright@starstonesoftware.com

#include <cstdio>
#include "gltools.h"	// OpenGL toolkit

// Rotation amounts
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;


// Called to draw scene
void RenderScene(void)
    {
    // Clear the window with current clearing color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();

    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);


    // Draw six quads
    glBegin(GL_QUADS);
        // Front Face
        // White
        glColor3ub((GLubyte) 255, (GLubyte)255, (GLubyte)255);
        glVertex3f(50.0f,50.0f,50.0f);

        // Yellow
        glColor3ub((GLubyte) 255, (GLubyte)255, (GLubyte)0);
        glVertex3f(50.0f,-50.0f,50.0f);

        // Red
        glColor3ub((GLubyte) 255, (GLubyte)0, (GLubyte)0);
        glVertex3f(-50.0f,-50.0f,50.0f);

        // Magenta
        glColor3ub((GLubyte) 255, (GLubyte)0, (GLubyte)255);
        glVertex3f(-50.0f,50.0f,50.0f);


    // Back Face
        // Cyan
        glColor3f(0.0f, 1.0f, 1.0f);
        glVertex3f(50.0f,50.0f,-50.0f);

        // Green
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(50.0f,-50.0f,-50.0f);

        // Black
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex3f(-50.0f,-50.0f,-50.0f);

        // Blue
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(-50.0f,50.0f,-50.0f);

    // Top Face
        // Cyan
        glColor3f(0.0f, 1.0f, 1.0f);
        glVertex3f(50.0f,50.0f,-50.0f);

        // White
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(50.0f,50.0f,50.0f);

        // Magenta
        glColor3f(1.0f, 0.0f, 1.0f);
        glVertex3f(-50.0f,50.0f,50.0f);

        // Blue
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(-50.0f,50.0f,-50.0f);

    // Bottom Face
        // Green
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(50.0f,-50.0f,-50.0f);

        // Yellow
        glColor3f(1.0f, 1.0f, 0.0f);
        glVertex3f(50.0f,-50.0f,50.0f);

        // Red
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-50.0f,-50.0f,50.0f);

        // Black
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex3f(-50.0f,-50.0f,-50.0f);

    // Left face
        // White
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(50.0f,50.0f,50.0f);

        // Cyan
        glColor3f(0.0f, 1.0f, 1.0f);
        glVertex3f(50.0f,50.0f,-50.0f);

        // Green
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(50.0f,-50.0f,-50.0f);

        // Yellow
        glColor3f(1.0f, 1.0f, 0.0f);
        glVertex3f(50.0f,-50.0f,50.0f);

    // Right face
        // Magenta
        glColor3f(1.0f, 0.0f, 1.0f);
        glVertex3f(-50.0f,50.0f,50.0f);

        // Blue
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(-50.0f,50.0f,-50.0f);

        // Black
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex3f(-50.0f,-50.0f,-50.0f);

        // Red
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-50.0f,-50.0f,50.0f);
    glEnd();

    glPopMatrix();

    // Show the graphics
    glutSwapBuffers();
    }

// This function does any needed initialization on the rendering
// context.
void SetupRC()
{
    // Black background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_DITHER);
    glShadeModel(GL_SMOOTH);
}

/////////////////////////////////////////////////
// Get Arrow Keys
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


void ChangeSize(int w, int h)
{
    GLfloat fAspect;

    // Prevent a divide by zero
    if(h == 0)
        h = 1;

    // Set Viewport to window dimensions
    glViewport(0, 0, w, h);

    // Reset coordinate system
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    fAspect = (GLfloat)w / (GLfloat)h;
    gluPerspective(35.0f, fAspect, 1.0f, 1000.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -400.0f);
}

///////////////////////////////////////////////////////////
// Main program entry point
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800,600);
    glutCreateWindow("RGB Cube");

    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKeys);
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

