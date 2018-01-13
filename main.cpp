#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#define ANIM_FPS	40

using namespace std;

enum
{
    FULL_WINDOW,
    ASPECT_1_1,
    EXIT
};


int Aspect = FULL_WINDOW;

GLdouble snakex = 0.5;
GLdouble snakez = -0.5;
GLint snakeDirection = 3;

GLboolean gameover = false;

GLdouble eyex = 0;
GLdouble eyey = 3.2;
GLdouble eyez = 0.7;


GLdouble centerx = 0;
GLdouble centery = 0;
GLdouble centerz = -10;

GLfloat lightAmb[] = {0, 0, 0, 1};
GLfloat lightDif[] = {1, 1, 1, 1};
GLfloat lightPos[] = {0, 0, 1, 0};
GLfloat lightSpec[] = {1, 1, 1, 1};

void Menu( int value );

void setupScene(void) {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDif);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpec);
	glEnable(GL_LIGHT0);
	glMaterialfv(GL_FRONT, GL_SPECULAR, lightSpec);
	glMateriali(GL_FRONT, GL_SHININESS, 100);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

void Display()
{
    glClearColor( 0, 0, 0, 0 );
    glClear( GL_COLOR_BUFFER_BIT );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt( eyex, eyey, eyez, centerx, centery, centerz, 0, 1, 0 );
   // glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glColor3f( 0.0, 1.0, 0.0 );
    glBegin( GL_POLYGON);
        glVertex3f( -3.0, 0.0, 0.0 );
        glVertex3f( -3.0, 0.0, -2.0 );
        glVertex3f( 3.0, 0.0, -2.0 );
        glVertex3f( 3.0, 0.0, 0.0 );
    glEnd();
    glColor3f(1,0,0);
    glTranslated(1,0,-1);
    glutSolidSphere(0.05, 10, 10);
    switch(snakeDirection){
    case 0:{
        snakez-=0.1;
        break;
    }
    case 1:{
        snakex+=0.1;
        break;
    }
    case 2:{
        snakez+=0.1;
        break;
    }
    case 3:{
        snakex-=0.1;
        break;
    }
    }
    if((snakex <= -4.1 || snakex >= 2.1) || (snakez <= -1 || snakez >= 0.9)){
        Menu(EXIT);
    }
    glColor3f(0,0,1);
    glTranslated(snakex,0,snakez);
    glutSolidCube(0.1);
    //glDisable( GL_LIGHTING );
    //glDisable( GL_COLOR_MATERIAL );
    glFlush();
    glutSwapBuffers();
}

/*void ZegarFun(int val) {
	switch(snakeDirection){
    case 0:{
        snakez-=0.1;
        break;
    }
    case 1:{
        snakex+=0.1;
        break;
    }
    case 2:{
        snakez+=0.1;
        break;
    }
    case 3:{
        snakex-=0.1;
        break;
    }
    glutPostRedisplay();
	glutTimerFunc(1000/ANIM_FPS, ZegarFun, 0);
}
}*/

void Reshape( int width, int height )
{
    glViewport( 0, 0, width, height );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    if( Aspect == ASPECT_1_1 )
    {
        if( width < height && width > 0 )
             glFrustum( - 2.0, 2.0, - 2.0 * height / width, 2.0 * height / width, 1.0, 5.0 );
        else
        if( width >= height && height > 0 )
             glFrustum( - 2.0 * width / height, 2.0 * width / height, - 2.0, 2.0, 1.0, 5.0 );

    }
    else
         glFrustum( - 2.0, 2.0, - 2.0, 2.0, 1.0, 5.0 );
    Display();
}


void Keyboard( unsigned char key, int x, int y )
{
    if( key == '+' )
         eyez -= 0.1;
    if( key == '-' )
         eyez += 0.1;
    if(key == 'w' || key == 'W')
        snakeDirection = 0;
    if(key == 'd' || key == 'D')
        snakeDirection = 1;
    if(key == 's' || key == 'S')
        snakeDirection = 2;
    if(key == 'a' || key == 'A')
        snakeDirection = 3;
    Reshape( glutGet( GLUT_WINDOW_WIDTH ), glutGet( GLUT_WINDOW_HEIGHT ) );
}


void SpecialKeys( int key, int x, int y )
{
    switch( key )
    {
    case GLUT_KEY_LEFT:
        eyex += 0.1;
        break;

    case GLUT_KEY_UP:
        eyey -= 0.1;
        break;

    case GLUT_KEY_RIGHT:
        eyex -= 0.1;
        break;

    case GLUT_KEY_DOWN:
        eyey += 0.1;
        break;

    }

    Reshape( glutGet( GLUT_WINDOW_WIDTH ), glutGet( GLUT_WINDOW_HEIGHT ) );
}

void Menu( int value )
{
    switch( value )
    {
    case FULL_WINDOW:
        Aspect = FULL_WINDOW;
        Reshape( glutGet( GLUT_WINDOW_WIDTH ), glutGet( GLUT_WINDOW_HEIGHT ) );
        break;

    case ASPECT_1_1:
        Aspect = ASPECT_1_1;
        Reshape( glutGet( GLUT_WINDOW_WIDTH ), glutGet( GLUT_WINDOW_HEIGHT ) );
        break;

    case EXIT:
        exit( 0 );
    }
}

int main( int argc, char * argv[] )
{ // wyszuka� �r�d�o bug�w
    glutInit( & argc, argv );
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );
    glutInitWindowSize( 400, 400 );
    glutCreateWindow( "Snake 3D" );
    glutDisplayFunc( Display );
    glutReshapeFunc( Reshape );
    glutKeyboardFunc(Keyboard);
    glutSpecialFunc(SpecialKeys);
    glutCreateMenu( Menu );
    //glutTimerFunc(1000/ANIM_FPS, ZegarFun, 0);
    //setupScene();
    glutMainLoop();
    return 0;
}
