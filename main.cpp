// Simple.cpp
// The Simplest OpenGL program with GLUT
// OpenGL SuperBible, 3rd Edition
// Richard S. Wright Jr.
// rwright@starstonesoftware.com

#include <cstdio>
#include "gltools.h"	// OpenGL toolkit
#include <string>

// Texture objects
#define TEXTURE_BRICK   0
#define TEXTURE_FLOOR   1
#define TEXTURE_CEILING 2
#define TEXTURE_COUNT   3

GLuint textures[TEXTURE_COUNT];
const char *szTextureFiles[TEXTURE_COUNT] = {"brick.tga", "floor.tga", "ceiling.tga"};
// Rotation amounts
static GLfloat zPos = -60.0f;

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
    gluPerspective(90.0f,fAspect,1,120);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


// This function does any needed initialization on the rendering
// context.  Here it sets up and initializes the lighting for
// the scene.
void SetupRC()
{
    GLbyte *pBytes;
    GLint iWidth, iHeight, iComponents;
    GLenum eFormat;

    // Black blue background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );

    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);

    // Load texture
    glGenTextures(TEXTURE_COUNT, textures);
    std::string path = "../LearnGL_21/Res/";
    for(int i=0; i<TEXTURE_COUNT; i++)
    {
        glBindTexture(GL_TEXTURE_2D,textures[i]);

        std::string file = path+szTextureFiles[i];
        pBytes = gltLoadTGA(file.c_str(),&iWidth,&iHeight,&iComponents,&eFormat);

        gluBuild2DMipmaps(GL_TEXTURE_2D, iComponents, iWidth, iHeight, eFormat, \
                          GL_UNSIGNED_BYTE, pBytes);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        free(pBytes);
    }
}

void ShutdownRC(){
    glDeleteTextures(TEXTURE_COUNT, textures);
}

// Respond to arrow keys
void SpecialKeys(int key, int x, int y)
{
    if(key == GLUT_KEY_UP)
        zPos += 1.0f;

    if(key == GLUT_KEY_DOWN)
        zPos -= 1.0f;

    // Refresh the Window
    glutPostRedisplay();
}


// Called to draw scene
void RenderScene(void)
{
    GLfloat z;

    // Clear the window with current clearing color
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
        glTranslatef(0.0f, 0.0f, zPos);

        // Floor
        for(z = 60.0f; z >= 0.0f; z -= 10)
        {
            glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_FLOOR]);
            glBegin(GL_QUADS);
                glTexCoord2f(0.0f, 0.0f);
                glVertex3f(-10.0f, -10.0f, z);

                glTexCoord2f(1.0f, 0.0f);
                glVertex3f(10.0f, -10.0f, z);

                glTexCoord2f(1.0f, 1.0f);
                glVertex3f(10.0f, -10.0f, z - 10.0f);

                glTexCoord2f(0.0f, 1.0f);
                glVertex3f(-10.0f, -10.0f, z - 10.0f);
            glEnd();

            // Ceiling
            glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_CEILING]);
            glBegin(GL_QUADS);
                glTexCoord2f(0.0f, 1.0f);
                glVertex3f(-10.0f, 10.0f, z - 10.0f);

                glTexCoord2f(1.0f, 1.0f);
                glVertex3f(10.0f, 10.0f, z - 10.0f);

                glTexCoord2f(1.0f, 0.0f);
                glVertex3f(10.0f, 10.0f, z);

                glTexCoord2f(0.0f, 0.0f);
                glVertex3f(-10.0f, 10.0f, z);
            glEnd();


            // Left Wall
            glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_BRICK]);
            glBegin(GL_QUADS);
                glTexCoord2f(0.0f, 0.0f);
                glVertex3f(-10.0f, -10.0f, z);

                glTexCoord2f(1.0f, 0.0f);
                glVertex3f(-10.0f, -10.0f, z - 10.0f);

                glTexCoord2f(1.0f, 1.0f);
                glVertex3f(-10.0f, 10.0f, z - 10.0f);

                glTexCoord2f(0.0f, 1.0f);
                glVertex3f(-10.0f, 10.0f, z);
            glEnd();


            // Right Wall
            glBegin(GL_QUADS);
                glTexCoord2f(0.0f, 1.0f);
                glVertex3f(10.0f, 10.0f, z);

                glTexCoord2f(1.0f, 1.0f);
                glVertex3f(10.0f, 10.0f, z - 10.0f);

                glTexCoord2f(1.0f, 0.0f);
                glVertex3f(10.0f, -10.0f, z - 10.0f);

                glTexCoord2f(0.0f, 0.0f);
                glVertex3f(10.0f, -10.0f, z);
            glEnd();
        }
    glPopMatrix();

    glutSwapBuffers();
}

void ProcessMenu(int value){
    GLint iLoop;

    for(iLoop = 0; iLoop < TEXTURE_COUNT; iLoop++)
    {
        glBindTexture(GL_TEXTURE_2D, textures[iLoop]);

        switch(value)
        {
        case 0:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            break;

        case 1:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            break;

        case 2:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
            break;

        case 3:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
            break;

        case 4:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
            break;

        case 5:
        default:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            break;
        }
    }

        // Trigger Redraw
        glutPostRedisplay();
}

///////////////////////////////////////////////////////////
// Main program entry point
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800,600);
    glutCreateWindow("Tunnel");

    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(RenderScene);

    // add menu
    glutCreateMenu(ProcessMenu);
    glutAddMenuEntry("GL_NEAREST",0);
    glutAddMenuEntry("GL_LINEAR",1);
    glutAddMenuEntry("GL_NEAREST_MIPMAP_NEAREST",2);
    glutAddMenuEntry("GL_NEAREST_MIPMAP_LINEAR",3);
    glutAddMenuEntry("GL_LINEAR_MIPMAP_NEAREST",4);
    glutAddMenuEntry("GL_LINEAR_MIPMAP_LINEAR",5);
    glutAttachMenu(GLUT_RIGHT_BUTTON);


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

