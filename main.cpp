// Simple.cpp
// The Simplest OpenGL program with GLUT
// OpenGL SuperBible, 3rd Edition
// Richard S. Wright Jr.
// rwright@starstonesoftware.com

#include <cstdio>
#include "gltools.h"	// OpenGL toolkit
#include "glframe.h"
#include <cmath>
#include <cstdlib>

#define NUM_SPHERES 50
GLFrame spheres[NUM_SPHERES];
GLFrame frameCamera;

void SetupRC(){
    int iSphere;

    glClearColor(0.0f,0.0f,0.5f,1.0f);

    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

    // Randomly place the sphere inhabitants
    for(iSphere=0; iSphere<NUM_SPHERES;  iSphere++){
        float x = (float)((rand()%400)-200)*0.1f;
        float z = (float)((rand()%400)-200)*0.1f;

        spheres[iSphere].SetOrigin(x,0.0f,z);
    }
}

/**
 * @brief DrawGround Draw a gridded ground
 */
void DrawGround(void){
    GLfloat fExtent = 20.0f;
    GLfloat fStep = 1.0f;
    GLfloat y = -0.4f;
    GLfloat iLine;

    glBegin(GL_LINES);
        for(iLine=-fExtent; iLine<=fExtent; iLine+=fStep)
        {
            glVertex3f(iLine,y,fExtent);
            glVertex3f(iLine,y,-fExtent);

            glVertex3f(fExtent,y,iLine);
            glVertex3f(-fExtent,y,iLine);
        }
    glEnd();
}

void RenderScene(void)
{
    int i;
    static GLfloat yRot = 0.0f;
    yRot += 0.5f;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
        frameCamera.ApplyCameraTransform();

        DrawGround();

        for(i=0; i<NUM_SPHERES; i++)
        {
            glPushMatrix();
                spheres[i].ApplyActorTransform();
                glutSolidSphere(0.1f,13,26);
            glPopMatrix();
        }

        glPushMatrix();
            glTranslatef(0.0f,0.0f,-2.5f);

            glPushMatrix();
                glRotatef(-yRot*2.0f,0.0f,1.0f,0.0f);
                glTranslatef(1.0f,0.0f,0.0f);
                glutSolidSphere(0.1f,13,26);
            glPopMatrix();

            glRotatef(yRot,0.0f,1.0f,0.0f);
            gltDrawTorus(0.35f,0.15f,40,20);
        glPopMatrix();

    glPopMatrix();

    glutSwapBuffers();

}

/**
 * @brief ChangeSize
 * @param w
 * @param h
 */
void ChangeSize(int w, int h)
{
    GLfloat fAspect;

    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if(h == 0)
        h = 1;

    glViewport(0, 0, w, h);

    fAspect = (GLfloat)w / (GLfloat)h;

    // Reset the coordinate system before modifying
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Set the clipping volume
    gluPerspective(35.0f, fAspect, 1.0f, 50.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void SpecialKeys(int key, int x, int y){
    if(key == GLUT_KEY_UP)
        frameCamera.MoveForward(0.1f);

    if(key == GLUT_KEY_DOWN)
        frameCamera.MoveForward(-0.1f);

    if(key == GLUT_KEY_LEFT)
        frameCamera.RotateLocalY(0.1f);

    if(key == GLUT_KEY_RIGHT)
        frameCamera.RotateLocalY(-0.1f);

    // 更新窗口
    glutPostRedisplay();
}

/**
 * @brief TimerFunc
 * @param value
 */
void TimerFunc(int value)
{
    // Redraw the scene with new coordinates
    glutPostRedisplay();
    glutTimerFunc(33,TimerFunc,1);
}

///////////////////////////////////////////////////////////
// Main program entry point
int main(int argc, char* argv[])
    {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800,600);
    glutCreateWindow("OpenGL SphereWorld Demo");

    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    glutSpecialFunc(SpecialKeys);

    glutTimerFunc(33, TimerFunc, 1);

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

