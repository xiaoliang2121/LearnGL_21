// Simple.cpp
// The Simplest OpenGL program with GLUT
// OpenGL SuperBible, 3rd Edition
// Richard S. Wright Jr.
// rwright@starstonesoftware.com

#include <cstdio>
#include "gltools.h"	// OpenGL toolkit
#include "math3d.h"

// Rotation amounts
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;


// Called to draw scene
void RenderScene(void)
{
    M3DVector3f vNormal;	// Storeage for calculated surface normal

    // Clear the window with current clearing color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Save the matrix state and do the rotations
    glPushMatrix();
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);


    // Nose Cone - Points straight down
    // Set material color
    glColor3ub(128, 128, 128);
    glBegin(GL_TRIANGLES);
        glNormal3f(0.0f, -1.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 60.0f);
        glVertex3f(-15.0f, 0.0f, 30.0f);
        glVertex3f(15.0f,0.0f,30.0f);


        // Verticies for this panel
        {
        M3DVector3f vPoints[3] = {{ 15.0f, 0.0f,  30.0f},
                                        { 0.0f,  15.0f, 30.0f},
                                        { 0.0f,  0.0f,  60.0f}};

        // Calculate the normal for the plane
        m3dFindNormal(vNormal, vPoints[0], vPoints[1], vPoints[2]);
        glNormal3fv(vNormal);
        glVertex3fv(vPoints[0]);
        glVertex3fv(vPoints[1]);
        glVertex3fv(vPoints[2]);
        }


        {
        M3DVector3f vPoints[3] = {{ 0.0f, 0.0f, 60.0f },
                                  { 0.0f, 15.0f, 30.0f },
                                  { -15.0f, 0.0f, 30.0f }};

        m3dFindNormal(vNormal, vPoints[0], vPoints[1], vPoints[2]);
        glNormal3fv(vNormal);
        glVertex3fv(vPoints[0]);
        glVertex3fv(vPoints[1]);
        glVertex3fv(vPoints[2]);
        }


        // Body of the Plane ////////////////////////
        {
        M3DVector3f vPoints[3] = {{ -15.0f, 0.0f, 30.0f },
                                  { 0.0f, 15.0f, 30.0f },
                                  { 0.0f, 0.0f, -56.0f }};

        m3dFindNormal(vNormal, vPoints[0], vPoints[1], vPoints[2]);
        glNormal3fv(vNormal);
        glVertex3fv(vPoints[0]);
        glVertex3fv(vPoints[1]);
        glVertex3fv(vPoints[2]);
        }

        {
        M3DVector3f vPoints[3] = {{ 0.0f, 0.0f, -56.0f },
                                  { 0.0f, 15.0f, 30.0f },
                                  { 15.0f,0.0f,30.0f }};

        m3dFindNormal(vNormal, vPoints[0], vPoints[1], vPoints[2]);
        glNormal3fv(vNormal);
        glVertex3fv(vPoints[0]);
        glVertex3fv(vPoints[1]);
        glVertex3fv(vPoints[2]);
        }


        glNormal3f(0.0f, -1.0f, 0.0f);
        glVertex3f(15.0f,0.0f,30.0f);
        glVertex3f(-15.0f, 0.0f, 30.0f);
        glVertex3f(0.0f, 0.0f, -56.0f);

        ///////////////////////////////////////////////
        // Left wing
        // Large triangle for bottom of wing
        {
        M3DVector3f vPoints[3] = {{ 0.0f,2.0f,27.0f },
                                  { -60.0f, 2.0f, -8.0f },
                                  { 60.0f, 2.0f, -8.0f }};

        m3dFindNormal(vNormal, vPoints[0], vPoints[1], vPoints[2]);
        glNormal3fv(vNormal);
        glVertex3fv(vPoints[0]);
        glVertex3fv(vPoints[1]);
        glVertex3fv(vPoints[2]);
        }


        {
        M3DVector3f vPoints[3] = {{ 60.0f, 2.0f, -8.0f},
                                   {0.0f, 7.0f, -8.0f},
                                   {0.0f,2.0f,27.0f }};

        m3dFindNormal(vNormal, vPoints[0], vPoints[1], vPoints[2]);
        glNormal3fv(vNormal);
        glVertex3fv(vPoints[0]);
        glVertex3fv(vPoints[1]);
        glVertex3fv(vPoints[2]);
        }

        {
        M3DVector3f vPoints[3] = {{60.0f, 2.0f, -8.0f},
                    {-60.0f, 2.0f, -8.0f},
                    {0.0f,7.0f,-8.0f }};

        m3dFindNormal(vNormal, vPoints[0], vPoints[1], vPoints[2]);
        glNormal3fv(vNormal);
        glVertex3fv(vPoints[0]);
        glVertex3fv(vPoints[1]);
        glVertex3fv(vPoints[2]);
        }

        {
        M3DVector3f vPoints[3] = {{0.0f,2.0f,27.0f},
                                    {0.0f, 7.0f, -8.0f},
                                    {-60.0f, 2.0f, -8.0f}};

        m3dFindNormal(vNormal, vPoints[0], vPoints[1], vPoints[2]);
        glNormal3fv(vNormal);
        glVertex3fv(vPoints[0]);
        glVertex3fv(vPoints[1]);
        glVertex3fv(vPoints[2]);
        }


        // Tail section///////////////////////////////
        // Bottom of back fin
        glNormal3f(0.0f, -1.0f, 0.0f);
        glVertex3f(-30.0f, -0.50f, -57.0f);
        glVertex3f(30.0f, -0.50f, -57.0f);
        glVertex3f(0.0f,-0.50f,-40.0f);

        {
        M3DVector3f vPoints[3] = {{ 0.0f,-0.5f,-40.0f },
                                  {30.0f, -0.5f, -57.0f},
                                {0.0f, 4.0f, -57.0f }};

        m3dFindNormal(vNormal, vPoints[0], vPoints[1], vPoints[2]);
        glNormal3fv(vNormal);
        glVertex3fv(vPoints[0]);
        glVertex3fv(vPoints[1]);
        glVertex3fv(vPoints[2]);
        }


        {
        M3DVector3f vPoints[3] = {{ 0.0f, 4.0f, -57.0f },
                { -30.0f, -0.5f, -57.0f },
                { 0.0f,-0.5f,-40.0f }};

        m3dFindNormal(vNormal, vPoints[0], vPoints[1], vPoints[2]);
        glNormal3fv(vNormal);
        glVertex3fv(vPoints[0]);
        glVertex3fv(vPoints[1]);
        glVertex3fv(vPoints[2]);
        }

        {
        M3DVector3f vPoints[3] = {{ 30.0f,-0.5f,-57.0f },
                    { -30.0f, -0.5f, -57.0f },
                    { 0.0f, 4.0f, -57.0f }};

        m3dFindNormal(vNormal, vPoints[0], vPoints[1], vPoints[2]);
        glNormal3fv(vNormal);
        glVertex3fv(vPoints[0]);
        glVertex3fv(vPoints[1]);
        glVertex3fv(vPoints[2]);
        }

        {
        M3DVector3f vPoints[3] = {{ 0.0f,0.5f,-40.0f },
                    { 3.0f, 0.5f, -57.0f },
                    { 0.0f, 25.0f, -65.0f }};

        m3dFindNormal(vNormal, vPoints[0], vPoints[1], vPoints[2]);
        glNormal3fv(vNormal);
        glVertex3fv(vPoints[0]);
        glVertex3fv(vPoints[1]);
        glVertex3fv(vPoints[2]);
        }


        {
        M3DVector3f vPoints[3] = {{ 0.0f, 25.0f, -65.0f },
                    { -3.0f, 0.5f, -57.0f},
                    { 0.0f,0.5f,-40.0f }};

        m3dFindNormal(vNormal, vPoints[0], vPoints[1], vPoints[2]);
        glNormal3fv(vNormal);
        glVertex3fv(vPoints[0]);
        glVertex3fv(vPoints[1]);
        glVertex3fv(vPoints[2]);
        }

        {
        M3DVector3f vPoints[3] = {{ 3.0f,0.5f,-57.0f },
                    { -3.0f, 0.5f, -57.0f },
                    { 0.0f, 25.0f, -65.0f }};

        m3dFindNormal(vNormal, vPoints[0], vPoints[1], vPoints[2]);
        glNormal3fv(vNormal);
        glVertex3fv(vPoints[0]);
        glVertex3fv(vPoints[1]);
        glVertex3fv(vPoints[2]);
        }


        glEnd();

        // Restore the matrix state
    glPopMatrix();
    // Display the results
    glutSwapBuffers();
}

// This function does any needed initialization on the rendering
// context.
void SetupRC()
{
    GLfloat ambientLight[] = {0.3f,0.3f,0.3f,1.0f};
    GLfloat diffuseLight[] = {0.7f,0.7f,0.7f,1.0f};

    glEnable(GL_DEPTH_TEST);	// Hidden surface removal
    glEnable(GL_CULL_FACE);		// Do not calculate inside of jet
    glFrontFace(GL_CCW);		// Counter clock-wise polygons face out

    // 打开设置背景光
    glEnable(GL_LIGHTING);
//    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambientLight);
    glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight);
    glEnable(GL_LIGHT0);

    glEnable(GL_COLOR_MATERIAL);    // 启用材料颜色追踪
    glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);

    // Nice light blue
    glClearColor(0.0f, 0.0f, 1.0f,1.0f);

    glEnable(GL_NORMALIZE);
}

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
    GLfloat nRange = 80.0f;
    // Prevent a divide by zero
    if(h == 0)
        h = 1;

    // Set Viewport to window dimensions
    glViewport(0, 0, w, h);

    // Reset coordinate system
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Establish clipping volume (left, right, bottom, top, near, far)
    if (w <= h)
        glOrtho (-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);
    else
        glOrtho (-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    }

///////////////////////////////////////////////////////////
// Main program entry point
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800,600);
    glutCreateWindow("Jet");

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

