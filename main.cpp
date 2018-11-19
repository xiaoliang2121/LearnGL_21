// Simple.cpp
// The Simplest OpenGL program with GLUT
// OpenGL SuperBible, 3rd Edition
// Richard S. Wright Jr.
// rwright@starstonesoftware.com

#include <cstdio>
#include "gltools.h"	// OpenGL toolkit
#include "math3d.h"
#include <cmath>

M3DVector3f vLightDir = {-1.0f,1.0f,1.0f};

// Draw a torus (doughnut), using the current 1D texture for light shading
void toonDrawTorus(GLfloat majorRadius, GLfloat minorRadius,
                   int numMajor, int  numMinor, M3DVector3f vLightDir)
{
    M3DMatrix44f mModelViewMatrix;
    M3DMatrix44f mInvertedLight;
    M3DVector3f vNewLight;
    M3DVector3f vNormal;
    double majorStep = 2.0f*M3D_PI / numMajor;
    double minorStep = 2.0f*M3D_PI / numMinor;
    int i, j;

    // Get the modelview matrix
    glGetFloatv(GL_MODELVIEW_MATRIX, mModelViewMatrix);

    // Instead of transforming every normal and then dotting it with
    // the light vector, we will transform the light into object
    // space by multiplying it by the inverse of the modelview matrix
    m3dInvertMatrix44(mInvertedLight, mModelViewMatrix);
    m3dTransformVector3(vNewLight, vLightDir, mInvertedLight);
    vNewLight[0] -= mInvertedLight[12];
    vNewLight[1] -= mInvertedLight[13];
    vNewLight[2] -= mInvertedLight[14];
    m3dNormalizeVector(vNewLight);

    // Draw torus as a series of triangle strips
    for (i=0; i<numMajor; ++i)
    {
        double a0 = i * majorStep;
        double a1 = a0 + majorStep;
        GLfloat x0 = (GLfloat) cos(a0);
        GLfloat y0 = (GLfloat) sin(a0);
        GLfloat x1 = (GLfloat) cos(a1);
        GLfloat y1 = (GLfloat) sin(a1);

        glBegin(GL_TRIANGLE_STRIP);
        for (j=0; j<=numMinor; ++j)
        {
            double b = j * minorStep;
            GLfloat c = (GLfloat) cos(b);
            GLfloat r = minorRadius * c + majorRadius;
            GLfloat z = minorRadius * (GLfloat) sin(b);

            // First point
            vNormal[0] = x0*c;
            vNormal[1] = y0*c;
            vNormal[2] = z/minorRadius;
            m3dNormalizeVector(vNormal);

            // Texture coordinate is set by intensity of light
            glTexCoord1f(m3dDotProduct(vNewLight, vNormal));
            glVertex3f(x0*r, y0*r, z);

            // Second point
            vNormal[0] = x1*c;
            vNormal[1] = y1*c;
            vNormal[2] = z/minorRadius;
            m3dNormalizeVector(vNormal);

            // Texture coordinate is set by intensity of light
            glTexCoord1f(m3dDotProduct(vNewLight, vNormal));
            glVertex3f(x1*r, y1*r, z);
        }
        glEnd();
    }
}

// Change viewing volume and viewport.  Called when window is resized
void ChangeSize(int w, int h)
{
    GLfloat fAspect;

    // Prevent a divide by zero
    if(h == 0)
        h = 1;

    // Set Viewport to window dimensions
    glViewport(0, 0, w, h);

    fAspect = (GLfloat)w/(GLfloat)h;

    // Reset coordinate system
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Produce the perspective projection
    gluPerspective(35.0f, fAspect, 1.0f, 50.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


// This function does any needed initialization on the rendering
// context.  Here it sets up and initializes the lighting for
// the scene.
void SetupRC()
{
    GLbyte toonTable[4][3] = { { 0, 32, 0 },
                               { 0, 64, 0 },
                               { 0, 128, 0 },
                               { 0, 192, 0 }};

    glClearColor(0.0f,0.0f,0.5f,1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);
    glTexParameteri(GL_TEXTURE_1D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_1D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_1D,GL_TEXTURE_WRAP_S,GL_CLAMP);

    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
    glTexImage1D(GL_TEXTURE_1D,0,GL_RGB,4,0,GL_RGB,GL_UNSIGNED_BYTE,toonTable);

    glEnable(GL_TEXTURE_1D);

}

// Respond to arrow keys
//void SpecialKeys(int key, int x, int y)
//{
//    if(key == GLUT_KEY_UP)
//        xRot-= 5.0f;

//    if(key == GLUT_KEY_DOWN)
//        xRot += 5.0f;

//    if(key == GLUT_KEY_LEFT)
//        yRot -= 5.0f;

//    if(key == GLUT_KEY_RIGHT)
//        yRot += 5.0f;

//        xRot = (GLfloat)((const int)xRot % 360);
//        yRot = (GLfloat)((const int)yRot % 360);

//    // Refresh the Window
//    glutPostRedisplay();
//}


// Called to draw scene
void RenderScene(void)
{
    static GLfloat yRot = 0.0f;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
        glTranslatef(0.0f,0.0f,-2.5f);
        glRotatef(yRot,0.0f,1.0f,0.0f);
        toonDrawTorus(0.35f, 0.15f, 50, 25, vLightDir);
    glPopMatrix();

    // Buffer swap
    glutSwapBuffers();

    yRot += 0.5f;
}

void TimerFunction(int value){
    // Redraw the scene with new coordinates
    glutPostRedisplay();
    glutTimerFunc(33,TimerFunction,1);
}

///////////////////////////////////////////////////////////
// Main program entry point
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800,600);
    glutCreateWindow("Toon/Cell Shading Demo");

    glutReshapeFunc(ChangeSize);
//    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(RenderScene);
    glutTimerFunc(33,TimerFunction,1);

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

