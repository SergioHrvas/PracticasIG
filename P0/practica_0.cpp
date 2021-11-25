#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>



void Ejes (int width)
{   
    glLineWidth(width);
    glBegin(GL_LINES);
       glColor3f(1.0,0.0,0.0);
       glVertex3f(-1.0,0.0,0.0);
       glVertex3f(1.0,0.0,0.0);
       glColor3f(0.0,1.0,0.0);
       glVertex3f(0.0,-1.0,0.0);
       glColor3f(1.0,1.0,0.0);
       glVertex3f(0.0,1.0,0.0);   
    glEnd();
   
       
}


void Cerdito ()
{
  
  

   
    // orejas
   glColor3f(1.0f,0.63f,0.94f);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glBegin(GL_POLYGON);
      glVertex3f(-0.2,0.45,0.0);
      glVertex3f(-0.25,0.57,0.0);
      glVertex3f(-0.22,0.66,0.0);
      glVertex3f(-0.14,0.61,0.0);
      glVertex3f(-0.11,0.55,0.0);
   glEnd(); 
   
   glLineWidth(4);
   glColor3f(0.0,0.0,0.0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glBegin(GL_POLYGON);
      glVertex3f(-0.2,0.45,0.0);
      glVertex3f(-0.25,0.57,0.0);
      glVertex3f(-0.22,0.66,0.0);
      glVertex3f(-0.14,0.61,0.0);
      glVertex3f(-0.11,0.55,0.0);
   glEnd();  

   
   glColor3f(1.0f,0.63f,0.94f);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glBegin(GL_POLYGON);
      glVertex3f(0.2,0.45,0.0);
      glVertex3f(0.25,0.57,0.0);
      glVertex3f(0.22,0.66,0.0);
      glVertex3f(0.14,0.61,0.0);
      glVertex3f(0.11,0.55,0.0);
   glEnd(); 
   
      glLineWidth(1);
   glColor3f(0.0,0.0,0.0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glBegin(GL_POLYGON);
      glVertex3f(0.2,0.45,0.0);
      glVertex3f(0.25,0.57,0.0);
      glVertex3f(0.22,0.66,0.0);
      glVertex3f(0.14,0.61,0.0);
      glVertex3f(0.11,0.55,0.0);
   glEnd();  

// cara
   glLineWidth(1);
   glColor3f(1.0f,0.63f,0.94f);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glBegin(GL_POLYGON);
      glVertex3f(-0.2,0.0,0.0);
      glVertex3f(0.2,0.0,0.0);
      glVertex3f(0.2,0.55,0.0);
      glVertex3f(-0.2,0.55,0.0);
   glEnd(); 

   glColor3f(0.0,0.0,0.);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glBegin(GL_POLYGON);
      glVertex3f(-0.2,0.0,0.0);
      glVertex3f(0.2,0.0,0.0);
      glVertex3f(0.2,0.55,0.0);
      glVertex3f(-0.2,0.55,0.0);
   glEnd(); 
   
   
    //hocico
   glColor3f(0.87,0.251,0.78);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glBegin(GL_POLYGON);
      glVertex3f(-0.15,0.05,0.0);
      glVertex3f(0.15,0.05,0.0);
      glVertex3f(0.15,0.20,0.0);
      glVertex3f(-0.15,0.20,0.0);
   glEnd(); 
   
   glColor3f(0.0,0.0,0.);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glBegin(GL_POLYGON);
      glVertex3f(-0.15,0.05,0.0);
      glVertex3f(0.15,0.05,0.0);
      glVertex3f(0.15,0.20,0.0);
      glVertex3f(-0.15,0.20,0.0);
   glEnd(); 

   glColor3f(0.0,0.0,0.0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glBegin(GL_POLYGON);
      glVertex3f(-0.10,0.10,0.0);
      glVertex3f(-0.05,0.10,0.0);
      glVertex3f(-0.05,0.15,0.0);
      glVertex3f(-0.10,0.15,0.0);
   glEnd(); 
   
   glColor3f(0.0,0.0,0.0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glBegin(GL_POLYGON);
      glVertex3f(0.05,0.10,0.0);
      glVertex3f(0.10,0.10,0.0);
      glVertex3f(0.10,0.15,0.0);
      glVertex3f(0.05,0.15,0.0);
   glEnd(); 
   
   
   //ojos
   glColor3f(0.0,0.0,0.0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glBegin(GL_POLYGON);
      glVertex3f(-0.15,0.45,0.0);
      glVertex3f(-0.05,0.45,0.0);
      glVertex3f(-0.05,0.25,0.0);
      glVertex3f(-0.15,0.25,0.0);
   glEnd(); 
   
   glColor3f(0.0,0.0,0.0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glBegin(GL_POLYGON);
      glVertex3f(0.05,0.45,0.0);
      glVertex3f(0.15,0.45,0.0);
      glVertex3f(0.15,0.25,0.0);
      glVertex3f(0.05,0.25,0.0);
   glEnd(); 
   
   
   glColor3f(1.0,1.0,1.0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glBegin(GL_POLYGON);
      glVertex3f(-0.12,0.40,0.0);
      glVertex3f(-0.08,0.40,0.0);
      glVertex3f(-0.08,0.35,0.0);
      glVertex3f(-0.12,0.35,0.0);
   glEnd(); 
   
   glColor3f(1.0,1.0,1.0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glBegin(GL_POLYGON);
      glVertex3f(0.08,0.40,0.0);
      glVertex3f(0.12,0.40,0.0);
      glVertex3f(0.12,0.35,0.0);
      glVertex3f(0.08,0.35,0.0);
   glEnd(); 
   
   


}


static void Init( )
{

   glShadeModel( GL_FLAT);
}


static void Reshape( int width, int height )
{
    glViewport(0, 0, (GLint)width, (GLint)height);
    glOrtho (-1.0, 1.0,-1.0, 1.0, -10, 10.0);
}

static void Display( )
{

  glClearColor(0.5,0.5,0.5,0.0);
  glClear( GL_COLOR_BUFFER_BIT );
   
  
   
   Ejes(6);
   Cerdito();
   
   glFlush();
}


static void Keyboard(unsigned char key, int x, int y )
{
 
  if (key==27)
      exit(0);

}


int main( int argc, char **argv )
{
   glutInit(&argc,argv);
   glutInitDisplayMode( GLUT_RGB );

   glutInitWindowPosition( 20, 100 );
   glutInitWindowSize(500, 500 );
   glutCreateWindow("Practica 0 IG");


   Init();

   glutReshapeFunc(Reshape);
   glutDisplayFunc(Display);
   glutKeyboardFunc(Keyboard);
  
   glutMainLoop( );

   return 0;
}

