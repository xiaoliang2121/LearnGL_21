// Simple.cpp
// The Simplest OpenGL program with GLUT
// OpenGL SuperBible, 3rd Edition
// Richard S. Wright Jr.
// rwright@starstonesoftware.com

#include <cstdio>
#include "gltools.h"	// OpenGL toolkit
#include <string>

// Rotation amounts
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

GLuint toTextures[2];       // Two texture objects
int iRenderMode = 3;        // Sphere Mapped is default

const char *szTextureFiles[2] = {"stripes.tga","Environment.tga"};

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
    gluPerspective(45.0f, fAspect, 1.0f, 225.0f);

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

    // Black background
    glClearColor(0.0f, 0.0f, 0.0f,1.0f);

    glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);

    // Textures applied as decals, no lighting or coloring effects
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    // Load textures
    glGenTextures(2, toTextures);
    std::string path = "../LearnGL_21/Res/";
    for(int iLoop = 0; iLoop < 2; iLoop++)
    {
        // Bind to next texture object
        glBindTexture(GL_TEXTURE_2D, toTextures[iLoop]);

        // Load texture, set filter and wrap modes
        std::string file = path+szTextureFiles[iLoop];
        pBytes = gltLoadTGA(file.c_str(),&iWidth, &iHeight, &iComponents, &eFormat);

        glTexImage2D(GL_TEXTURE_2D,0,iComponents,iWidth,iHeight,0,eFormat,
                     GL_UNSIGNED_BYTE,pBytes);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // Don't need original texture data any more
        free(pBytes);
    }

    // Turn on texture coordiante generation
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);

    // Sphere Map will be the default
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
}

// Respond to arrow keys
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


// Called to draw scene
void RenderScene(void)
{
    // Clear the window with current clearing color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Switch to orthographic view for background drawing
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0f, 1.0f, 0.0f, 1.0f);

    glMatrixMode(GL_MODELVIEW);
    glBindTexture(GL_TEXTURE_2D, toTextures[1]);    // Background texture

    // We will specify texture coordinates
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);

    // No depth buffer writes for background
    glDepthMask(GL_FALSE);

    // Background image
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex2f(0.0f, 0.0f);

        glTexCoord2f(1.0f, 0.0f);
        glVertex2f(1.0f, 0.0f);

        glTexCoord2f(1.0f, 1.0f);
        glVertex2f(1.0f, 1.0f);

        glTexCoord2f(0.0f, 1.0f);
        glVertex2f(0.0f, 1.0f);
    glEnd();

    // Back to 3D land
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    // Turn texgen and depth writing back on
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glDepthMask(GL_TRUE);

    // May need to swtich to stripe texture
    if(iRenderMode != 3)
        glBindTexture(GL_TEXTURE_2D, toTextures[0]);

    // Save the matrix state and do the rotations
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -2.0f);
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);

    // Draw the tours
    gltDrawTorus(0.35, 0.15, 61, 37);

    // Restore the matrix state
    glPopMatrix();

    // Display the results
    glutSwapBuffers();
}

void ProcessMenu(int value){
    // Projection plane
    GLfloat zPlane[] = { 0.0f, 0.0f, 1.0f, 0.0f };

    // Store render mode
    iRenderMode = value;

    // Set up textgen based on menu selection
    switch (value) {
    case 0:
        glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
        glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
        glTexGenfv(GL_S,GL_OBJECT_PLANE,zPlane);
        glTexGenfv(GL_T,GL_OBJECT_PLANE,zPlane);

        break;

    case 1:
        glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);
        glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);
        glTexGenfv(GL_S,GL_EYE_PLANE,zPlane);
        glTexGenfv(GL_T,GL_EYE_PLANE,zPlane);

        break;

    case 2:
    default:
        glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_SPHERE_MAP);
        glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_SPHERE_MAP);

        break;
    }

    // Trigger Redraw
    glutPostRedisplay();
}

///////////////////////////////////////////////////////////
// Main program entry point
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800,600);
    glutCreateWindow("Texture Coordinate Generation");

    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(RenderScene);

    // add menu
    glutCreateMenu(ProcessMenu);
    glutAddMenuEntry("Object Linear",0);
    glutAddMenuEntry("Eye Linear",1);
    glutAddMenuEntry("Sphere Map",2);
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

    glDeleteTextures(2,toTextures);

    return 0;
}

