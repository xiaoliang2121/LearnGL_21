// Simple.cpp
// The Simplest OpenGL program with GLUT
// OpenGL SuperBible, 3rd Edition
// Richard S. Wright Jr.
// rwright@starstonesoftware.com

#include <cstdio>
#include "gltools.h"	// OpenGL toolkit

// The number of control points for this curve
GLint nNumPoints = 3;

GLfloat ctrlPoints[3][3][3]= {{{  -4.0f, 0.0f, 4.0f},
                               { -2.0f, 4.0f, 4.0f},
                               { 4.0f, 0.0f, 4.0f }},

                             {{  -4.0f, 0.0f, 0.0f},
                              { -2.0f, 4.0f, 0.0f},
                              {  4.0f, 0.0f, 0.0f }},

                             {{  -4.0f, 0.0f, -4.0f},
                              { -2.0f, 4.0f, -4.0f},
                              {  4.0f, 0.0f, -4.0f }}};

////////////////////////////////////////////////////////////////////////////
// Change viewing volume and viewport.  Called when window is resized
void ChangeSize(int w, int h)
{
    // Prevent a divide by zero
    if(h == 0)
        h = 1;

    // Set Viewport to window dimensions
    glViewport(0, 0, w, h);

    // Reset coordinate system
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Produce the perspective projection
//    gluOrtho2D(-10.0f,10.0f,-10.0f,10.0f);
    glOrtho(-10.0f, 10.0f, -10.0f, 10.0f, -10.0f, 10.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


// This function does any needed initialization on the rendering
// context.  Here it sets up and initializes the lighting for
// the scene.
void SetupRC()
{
    // white background
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f );

    glColor3f(0.0f,0.0f,1.0f);
    glEnable(GL_AUTO_NORMAL);
}

void DrawPoints(){
    glPointSize(5.0f);

    glBegin(GL_POINTS);
        for(int i=0; i<nNumPoints; i++)
            for(int j=0; j<3; j++)
                glVertex3fv(ctrlPoints[i][j]);
    glEnd();
}

// Called to draw scene
void RenderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glRotatef(45.0f,0.0f,1.0f,0.0f);
        glRotatef(60.0f,1.0f,0.0f,0.0f);

        glMap2f(GL_MAP2_VERTEX_3,
                0.0f,10.0f,3,3,
                0.0f,10.0f,9,3,
                &ctrlPoints[0][0][0]);

        glEnable(GL_MAP2_VERTEX_3);

        glMapGrid2f(10,0.0f,10.0f,10,0.0f,10.0f);
//        glEvalMesh2(GL_LINE,0,10,0,10);
        glEvalMesh2(GL_FILL,0,10,0,10);

        DrawPoints();

    glPopMatrix();

    // Buffer swap
    glutSwapBuffers();
}

///////////////////////////////////////////////////////////
// Main program entry point
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Bezier Surface");

    glutDisplayFunc(RenderScene);
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

