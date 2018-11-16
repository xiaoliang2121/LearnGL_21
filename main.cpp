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
    GLfloat x,y,angle;                  // Storeage for varying X Y coordinate
    int iPivot = 1;                     // Used to flag alternating colors

    // Clear the window with current clearing color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Turn culling on if flag is set
    if(iCull)
        glEnable(GL_CULL_FACE);
    else
        glDisable(GL_CULL_FACE);

    // Enable depth testing if flag is set
    if(iDepth)
        glEnable(GL_DEPTH_TEST);
    else
        glDisable(GL_DEPTH_TEST);

    // Draw back side as a polygon only, if flag is set
    if(iOutline)
        glPolygonMode(GL_BACK,GL_LINE);
    else
        glPolygonMode(GL_BACK,GL_FILL);

    glPushMatrix();
    glRotatef(xRot,1.0f,0.0f,0.0f);
    glRotatef(yRot,0.0f,1.0f,0.0f);

    // Begin a triangle fan
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0.0f, 0.0f, 75.0f);
        for(angle=0.0f; angle<(2.0f*GL_PI); angle+=(GL_PI/8.0f))
        {
            x = 50.0f*sin(angle);
            y = 50.0f*cos(angle);

            if(iPivot%2 == 0)
                glColor3f(0.0f,1.0f,0.0f);
            else
                glColor3f(1.0f,0.0f,0.0f);

            iPivot++;

            glVertex2f(x,y);
        }
    // Done drawing fan for cone
    glEnd();

    // Begin a new triangle fan to cover the bottom
    glBegin(GL_TRIANGLE_FAN);
        // Center of fan is at the origin
        glVertex2f(0.0f,0.0f);
        for(angle=0.0f; angle<(2.0f*GL_PI); angle+=(GL_PI/8.0f))
        {
            x = 50.0f*sin(angle);
            y = 50.0f*cos(angle);

            if(iPivot%2 == 0)
                glColor3f(0.0f,1.0f,0.0f);
            else
                glColor3f(1.0f,0.0f,0.0f);

            iPivot++;

            glVertex2f(x,y);
        }
    // Done drawing the fan that covers the bottom
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

    glShadeModel(GL_FLAT);
    glFrontFace(GL_CW);
    }

///////////////////////////////////////////////////////////
// Main program entry point
int main(int argc, char* argv[])
    {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800,600);
    glutCreateWindow("Triangle Culling Example");

    // Create the Menu
    glutCreateMenu(ProcessMenu);
    glutAddMenuEntry("Toggle depth test",1);
    glutAddMenuEntry("Toggle cull backface",2);
    glutAddMenuEntry("Toggle outline back",3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

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

