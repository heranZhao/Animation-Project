//
//  OpenGLWindow.cpp
//  test2
//
//  Created by heran zhao on 9/6/18.
//  Copyright © 2018 heran zhao. All rights reserved.
//

#include "OpenGLWindow.hpp"


OpenGLWindow* OpenGLWindow::Instance = new OpenGLWindow();

BioSystemManager* OpenGLWindow::bioSystem = new BioSystemManager();
GLUI* OpenGLWindow::glui_create = NULL;


OpenGLWindow* OpenGLWindow::getInstance()
{
    return Instance;
}


void OpenGLWindow::reshapeWindow(int w, int h)
{
    if (h == 0)
        h = 1;
    float ratio = 1.0* w / h;
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    //glViewport(0, 0, w, h);
    glOrtho(-14,14, -6, 6, 0, 40);

    //gluPerspective(15, ratio, 1, 500);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, -1.0, 0.0f, 1.0f, 0.0f);
}

void OpenGLWindow::initWindow()
{
    glShadeModel(GL_SMOOTH);
    glClearColor(0, 0, 0, 0);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void OpenGLWindow::openLight()
{
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    
    //enable lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
        //light source attributes
    GLfloat LightAmbient[]    = { 0.4f, 0.4f, 0.4f, 1.0f };
    GLfloat LightDiffuse[]    = { 0.3f, 0.3f, 0.3f, 1.0f };
    GLfloat LightSpecular[]    = { 0.4f, 0.4f, 0.4f, 1.0f };
    GLfloat LightPosition[] = { 5.0f, 5.0f, 5.0f, 1.0f };
    
    glLightfv(GL_LIGHT0, GL_AMBIENT , LightAmbient );
    glLightfv(GL_LIGHT0, GL_DIFFUSE , LightDiffuse );
    glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular);
    glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);

    // surface material attributes
    GLfloat material_Ka[]    = { 0.11f, 0.06f, 0.11f, 1.0f };
    GLfloat material_Kd[]    = { 0.43f, 0.47f, 0.54f, 1.0f };
    GLfloat material_Ks[]    = { 0.33f, 0.33f, 0.52f, 1.0f };
    GLfloat material_Ke[]    = { 0.1f , 0.0f , 0.1f , 1.0f };
    GLfloat material_Se        = 10;
    
    glMaterialfv(GL_FRONT, GL_AMBIENT    , material_Ka);
    glMaterialfv(GL_FRONT, GL_DIFFUSE    , material_Kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR    , material_Ks);
    glMaterialfv(GL_FRONT, GL_EMISSION    , material_Ke);
    glMaterialf (GL_FRONT, GL_SHININESS    , material_Se);
}


void OpenGLWindow::displayWindow(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    glPushMatrix();
    glTranslatef(0,0,-10);
    //glTranslatef(12,6.5,0);
    //glutSolidSphere(1,50,50);
    bioSystem->runSystem();
    glPopMatrix();

    /* swap the back and front buffers so we can see what we just drew */
    glutSwapBuffers();
    
}


void OpenGLWindow::createWindow(int argc, char *argv[])
{
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(1280, 640);

    glutCreateWindow ("project1");
    
    
    initWindow();
    glutDisplayFunc(displayWindow);
    glutIdleFunc(displayWindow);
    glutReshapeFunc(reshapeWindow); //指定窗口形状变化时的回调函数
    glEnable(GL_DEPTH_TEST);
    //initUI();
    glutMainLoop();
    reshapeWindow(1279,640);

}


//GLUI FUNCTIONS
void OpenGLWindow::myGlutIdle( void )
{
    if ( glutGetWindow() != 1 )
        glutSetWindow(1);

    glutPostRedisplay();
}

void OpenGLWindow::initUI()
{
    glui_create = GLUI_Master.create_glui( "GLUI" );
    glui_create->set_main_gfx_window( 1 );
    
    GLUI_Panel* listPanel = glui_create->add_panel("");
    glui_create->add_edittext_to_panel(listPanel,"AX",GLUI_EDITTEXT_FLOAT, &(bioSystem->height));
    glui_create->add_column_to_panel (listPanel, true);
    glui_create->add_edittext_to_panel(listPanel,"AY",GLUI_EDITTEXT_FLOAT,&(bioSystem->height));
    glui_create->add_column_to_panel (listPanel, true);
    glui_create->add_edittext_to_panel(listPanel,"AZ",GLUI_EDITTEXT_FLOAT, &(bioSystem->height));
    GLUI_Master.set_glutIdleFunc( myGlutIdle );
}
