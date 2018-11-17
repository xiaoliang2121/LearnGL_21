// Simple.cpp
// The Simplest OpenGL program with GLUT
// OpenGL SuperBible, 3rd Edition
// Richard S. Wright Jr.
// rwright@starstonesoftware.com

#include <cstdio>
#include "gltools.h"	// OpenGL toolkit
#include "math3d.h"
#include <cmath>

// Lighting values
GLfloat  whiteLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat  sourceLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat	 lightPos[] = { 0.0f, 0.0f, 0.0f, 1.0f };

void DrawTorus(M3DMatrix44f mTransform){
    GLfloat majorRadius = 0.35f;
    GLfloat minorRadius = 0.15f;
    GLint   numMajor = 40;
    GLint   numMinor = 20;
    M3DVector3f objectVertex;         // Vertex in object/eye space
    M3DVector3f transformedVertex;    // New Transformed vertex
    double majorStep = 2.0f*M3D_PI / numMajor;
    double minorStep = 2.0f*M3D_PI / numMinor;
    int i, j;

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
            objectVertex[0] = x0*r;
            objectVertex[1] = y0*r;
            objectVertex[2] = z;
            m3dTransformVector3(transformedVertex, objectVertex, mTransform);
            glVertex3fv(transformedVertex);

            // Second point
            objectVertex[0] = x1*r;
            objectVertex[1] = y1*r;
            objectVertex[2] = z;
            m3dTransformVector3(transformedVertex, objectVertex, mTransform);
            glVertex3fv(transformedVertex);
        }
        glEnd();
    }
}

// Called to draw scene
void RenderScene(void)
{
    M3DMatrix44f translationMatrix,rotationMatrix,transformationMatrix;
    static GLfloat yRot = 0.0f;

    yRot += 0.5f;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    1
//    m3dRotationMatrix44(transformationMatrix,m3dDegToRad(yRot),\
//                        0.0f,1.0f,0.0f);
//    transformationMatrix[12] = 0.0f;
//    transformationMatrix[13] = 0.0f;
//    transformationMatrix[14] = -2.5f;

//    glLoadMatrixf(transformationMatrix);

//    gltDrawTorus(0.35,0.15,40,20);

//    2
    glPushMatrix();
        glTranslatef(0.0f,0.0f,-2.5f);
        glRotatef(yRot,0.0f,1.0f,0.0f);

        gltDrawTorus(0.35,0.15,40,20);
    glPopMatrix();

//    3     未知原因没有工作
//    m3dRotationMatrix44(rotationMatrix,m3dDegToRad(yRot),\
//                        0.0f,1.0f,0.0f);
//    m3dTranslateMatrix44(translationMatrix,0.0f,0.0f,-2.5f);
//    m3dMatrixMultiply44(transformationMatrix,translationMatrix,rotationMatrix);
//    glLoadMatrixf(transformationMatrix);

//    gltDrawTorus(0.35f,0.15f,40,20);

//    4     未知原因没有工作
//    glPushMatrix();
//        m3dRotationMatrix44(rotationMatrix,m3dDegToRad(yRot),\
//                            0.0f,1.0f,0.0f);
//        m3dTranslateMatrix44(translationMatrix,0.0f,0.0f,-2.5f);

//        glMultMatrixf(translationMatrix);
//        glMultMatrixf(rotationMatrix);

//        gltDrawTorus(0.35f,0.15f,40,20);
//    glPopMatrix();

    glutSwapBuffers();

}


// This function does any needed initialization on the rendering
// context.
void SetupRC()
{
    glClearColor(0.0f,0.0f,0.5f,1.0f);

    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
}


void TimerFunc(int value)
    {
    glutPostRedisplay();
    glutTimerFunc(33, TimerFunc, 1);
    }

void ChangeSize(int w, int h)
    {
    GLfloat fAspect;

    // Prevent a divide by zero
    if(h == 0)
        h = 1;

    // Set Viewport to window dimensions
    glViewport(0, 0, w, h);

    // Calculate aspect ratio of the window
    fAspect = (GLfloat)w/(GLfloat)h;

    // Set the perspective coordinate system
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // field of view of 45 degrees, near and far planes 1.0 and 425
    gluPerspective(35.0f, fAspect, 1.0f, 50.0f);

    // Modelview matrix reset
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
    glutCreateWindow("OpenGL Transformations Demo");

    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);

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

