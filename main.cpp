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

#define NUM_SPHERES 30
GLFrame spheres[NUM_SPHERES];
GLFrame frameCamera;

// Light and material Data
GLfloat fLightPos[4]   = { -100.0f, 100.0f, 50.0f, 1.0f };  // Point source
GLfloat fNoLight[] = { 0.0f, 0.0f, 0.0f, 0.0f };
GLfloat fLowLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };
GLfloat fBrightLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };

M3DMatrix44f mShadowMatrix;

/**
 * @brief SetupRC This function does any needed initialization on the rendering context.
 */
void SetupRC(){
    int iSphere;

    // Calculate shadow matrix
    M3DVector3f vPoints[3] = {{ 0.0f, -0.4f, 0.0f },
                             { 10.0f, -0.4f, 0.0f },
                             { 5.0f, -0.4f, -5.0f }};

    glEnable(GL_MULTISAMPLE_ARB);

    glClearColor(fLowLight[0], fLowLight[1], fLowLight[2], fLowLight[3]);

    // Clear stencil buffer with zero, increment by one whenever anybody
    // draws into it. When stencil function is enabled, only write where
    // stencil value is zero. This prevents the transparent shadow from drawing
    // over itself
    glStencilOp(GL_INCR, GL_INCR, GL_INCR);
    glClearStencil(0);
    glStencilFunc(GL_EQUAL, 0x0, 0x01);

    // Setup Fog parameters
    glEnable(GL_FOG);
    glFogfv(GL_FOG_COLOR, fLowLight);
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogf(GL_FOG_START, 5.0f);
    glFogf(GL_FOG_END, 30.0f);
    glHint(GL_FOG_HINT, GL_NICEST);

    // Cull backs of polygons
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE_ARB);

    // Setup light parameters
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,fNoLight);
    glLightfv(GL_LIGHT0,GL_AMBIENT,fLowLight);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,fBrightLight);
    glLightfv(GL_LIGHT0,GL_SPECULAR,fBrightLight);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Get the plane equation from three points on the ground
    M3DVector4f vPlaneEquation;
    m3dGetPlaneEquation(vPlaneEquation,vPoints[0],vPoints[1],vPoints[2]);

    // Calculate projection matrix to draw shadow on the ground
    m3dMakePlanarShadowMatrix(mShadowMatrix,vPlaneEquation,fLightPos);

//    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    // Mostly use material tracking
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glMateriali(GL_FRONT, GL_SHININESS, 128);

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
    GLfloat iStrip, iRun;

    for(iStrip=-fExtent; iStrip<=fExtent; iStrip+=fStep)
    {
        glBegin(GL_TRIANGLE_STRIP);
            glNormal3f(0.0f,1.0f,0.0f);

            for(iRun=fExtent; iRun>=-fExtent; iRun-=fStep)
            {
                glVertex3f(iStrip,y,iRun);
                glVertex3f(iStrip+fStep,y,iRun);
            }
        glEnd();
    }
}

// Draw random inhabitants and the rotating torus/sphere duo
/**
 * @brief DrawInhabitants
 * @param nShadow
 */
void DrawInhabitants(GLint nShadow){
    static GLfloat yRot = 0.0f;
    GLint i;

    if(nShadow == 0)
        yRot += 0.5f;
    else
        glColor3f(0.0f,0.0f,0.0f);

    if(nShadow == 0)
        glColor3f(0.0f,1.0f,0.0f);

    for(i=0; i<NUM_SPHERES; i++)
    {
        glPushMatrix();
            spheres[i].ApplyActorTransform();
            glutSolidSphere(0.3f,17,9);
        glPopMatrix();
    }

    glPushMatrix();
        glTranslatef(0.0f,0.1f,-2.5f);

        if(nShadow == 0)
            glColor3f(0.0f,0.0f,1.0f);

        glPushMatrix();
            glRotatef(-yRot*2.0f,0.0f,1.0f,0.0f);
            glTranslatef(1.0f,0.0f,0.0f);
            glutSolidSphere(0.1f,17,9);
        glPopMatrix();

        if(nShadow == 0)
        {
            glColor3f(1.0f,0.0f,0.0f);
            glMaterialfv(GL_FRONT,GL_SPECULAR,fBrightLight);
        }

        glRotatef(yRot,0.0f,1.0f,0.0f);
        gltDrawTorus(0.35f,0.15f,61,37);
        glMaterialfv(GL_FRONT,GL_SPECULAR,fNoLight);
    glPopMatrix();
}

void RenderScene(void)
{
    // Clear the window with current clearing color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
        frameCamera.ApplyCameraTransform();

        // Position light before any other transformations
        glLightfv(GL_LIGHT0,GL_POSITION,fLightPos);

        // Draw the ground
        glColor3f(0.6f,0.4f,0.1f);
        DrawGround();

        // Draw shadows first
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_LIGHTING);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_STENCIL_TEST);
        glPushMatrix();
            glMultMatrixf(mShadowMatrix);
            DrawInhabitants(1);
        glPopMatrix();
        glDisable(GL_STENCIL_TEST);
        glDisable(GL_BLEND);
        glEnable(GL_LIGHTING);
        glEnable(GL_DEPTH_TEST);

        // Draw inhabitants normally
        DrawInhabitants(0);

    glPopMatrix();

    glutSwapBuffers();
//    glutPostRedisplay();
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
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL |
                        GLUT_MULTISAMPLE);
    glutInitWindowSize(800,600);
    glutCreateWindow("OpenGL SphereWorld Demo + Lights and Shadow");

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

