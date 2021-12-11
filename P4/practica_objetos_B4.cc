//**************************************************************************
// Práctica 3 usando objetos
//**************************************************************************

#include <GL/glut.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include "objetos_B4.h"


using namespace std;

// tipos
typedef enum{CUBO, PIRAMIDE, OBJETO_PLY, ROTACION, ARTICULADO, CILINDRO, CONO, ESFERA} _tipo_objeto;

_tipo_objeto t_objeto=ARTICULADO;
_modo   modo=SOLID;
_material materi = ORO;
// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Size_x,Size_y,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int Window_x=50,Window_y=50,Window_width=450,Window_high=450;

bool materiales = false;
// objetos
_cubo cubo;
_piramide piramide(0.85,1.3);
_objeto_ply  ply; 
_rotacion rotacion; 
_tanque tanque;
_ruedas ruedas;
_chasis chasis;
_plataforma plataforma;
_carroceria carroceria;
_escaleragrande escaleragrande;
_escalerachica escalerachica;
_cabina cabina;
_camionbomberos camionbomberos;
_elevador elevador;
_pistola pistola;
_agua agua;

float luz1[]={1.0,1.0,1.0, 1}, pos1[]= {25, 10, 20, 1}, luz2[]={0.7922,0.0824,0.4157, 1}, pos2[]= {-20, -15.0, -20.0, 0};
Luz luz(GL_LIGHT1, luz1, luz1, pos1);
Luz luzb(GL_LIGHT2, luz2, luz2, pos2);

_objeto_ply ply_perfil; 
_rotacion rotacionx, rotaciony, rotacionz;
_cilindro cilindrox(0.6,1.8,15,0), cilindroy(0.6,1.8,15,1), cilindroz(0.6,1.8,15,2);
_cono conox(0.6,1.8,15,0), conoy(0.6,1.8,15,1), conoz(0.6,1.8,15,2);
_esfera esferax(1.2,15,0), esferay(1.2,15,1), esferaz(1.2,15,2);

// _objeto_ply *ply1;

//variables de movimiento
bool mov = false;
int n_mov = 0;
int n = 0;
float v_plataforma = 1;
float v_ruedas = 1;
float v_escaleras = 1;
float v_escalera = 1;
float v_elevador = 1;
float v_camion = 1;
float v_pistola = 1;
float v_agua = 1;
float v_max = 2;
float v_min = 0.1;
int velocidad_gl = 0;
int eje = 1;
//**************************************************************************
//
//***************************************************************************

void clean_window()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

glMatrixMode(GL_PROJECTION);
glLoadIdentity();

// formato(x_minimo,x_maximo, y_minimo, y_maximo,plano_delantero, plano_traser)
//  plano_delantero>0  plano_trasero>PlanoDelantero)
glFrustum(-Size_x,Size_x,-Size_y,Size_y,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación*ply1 de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
	
glDisable(GL_LIGHTING);
glLineWidth(2);
glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(-AXIS_SIZE,0,0);
glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,-AXIS_SIZE,0);
glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,-AXIS_SIZE);
glVertex3f(0,0,AXIS_SIZE);
glEnd();
}


//**************************************************************************
// Funcion que dibuja los objetos
//****************************2***********************************************

void draw_objects()
{
        switch (t_objeto){
                case CUBO: cubo.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2,  materi);break;
                case PIRAMIDE: piramide.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2, materi);break;
                case OBJETO_PLY: ply.draw(modo,1.0,0.6,0.0,0.0,1.0,0.3,2, materi);break;
                case ARTICULADO: camionbomberos.draw(modo,0.803,0.043,0.043,0.819,0.3686,0.3686,2, materi);break;
                case ROTACION: if (eje==0)
                                        rotacionx.draw(modo,0.0,0.0,0.0,0.0,1.0,0.0,2, materi);
                                else if (eje==1)
                                        rotaciony.draw(modo,0.0,0.0,0.0,0.0,1.0,0.0,2, materi);
                                else if (eje==2)
                                        rotacionz.draw(modo,0.0,0.0,0.0,0.0,1.0,0.0,2, materi);
                                break;
                case CILINDRO: if (eje==0)
                                        cilindrox.draw(modo,0.0,0.0,0.0,0.0,1.0,0.0,2, materi);
                                else if (eje==1)
                                        cilindroy.draw(modo,0.0,0.0,0.0,0.0,1.0,0.0,2, materi);
                                else if (eje==2)
                                        cilindroz.draw(modo,0.0,0.0,0.0,0.0,1.0,0.0,2, materi);
                                break;
                case CONO:  if (eje==0)
                                        conox.draw(modo,0.0,0.0,0.0,0.0,1.0,0.0,2, materi);
                                else if (eje==1)
                                        conoy.draw(modo,0.0,0.0,0.0,0.0,1.0,0.0,2, materi);
                                else if (eje==2)
                                        conoz.draw(modo,0.0,0.0,0.0,0.0,1.0,0.0,2, materi);
                                break;
                case ESFERA:  if (eje==0)
                                        esferax.draw(modo,0.0,0.0,0.0,0.0,1.0,0.0,2, materi);
                                else if (eje==1)
                                        esferay.draw(modo,0.0,0.0,0.0,0.0,1.0,0.0,2, materi);
                                else if (eje==2)
                                        esferaz.draw(modo,0.0,0.0,0.0,0.0,1.0,0.0,2, materi);
                                break;	
                }

}

void luces ()
{

	float luz1[]={1.0,1.0,1.0, 1}, pos1[]= {25, 10, 20, 1},luz2[]={0.7922,0.0824,0.4157, 1}, pos2[]= {-20, -15.0, -20.0, 0};
        luz.setAmbienteDifuso(luz1);
        luz.setEspecular(luz1);
        luz.setAmbienteDifuso(luz1);
        luz.setPosicion(pos1);
        luz.draw();

        // glLightfv(GL_LIGHT1, GL_DIFFUSE, luz1);
	//	glLightfv(GL_LIGHT1, GL_SPECULAR, luz1);
	//	glLightfv(GL_LIGHT1, GL_POSITION, pos1);
/*
	glLightfv(GL_LIGHT2, GL_DIFFUSE, luz2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, luz2);
	glLightfv(GL_LIGHT2, GL_POSITION, pos2);*/
	//	la luz 0 esta activda por defecto y la tenemos que desactivar
	glDisable(GL_LIGHT0);
	luz.encenderLuz();

	//glEnable(GL_LIGHT1);
	//glEnable (GL_LIGHT2);
}

//**************************************************************************
//
//***************************************************************************

void draw(void)
{

clean_window();
change_observer();
luces();
draw_axis();
draw_objects();
glutSwapBuffers();
}



//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
float Aspect_ratio;

Aspect_ratio=(float) Alto1/(float )Ancho1;
Size_y=Size_x*Aspect_ratio;
change_projection();
glViewport(0,0,Ancho1,Alto1);
glutPostRedisplay();
}


//**********-o*****************************************************************
// Funcion llamada cuando se aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_key(unsigned char Tecla1,int x,int y)
{
        switch (toupper(Tecla1)){
                case 'Q':exit(0);
                case '1':if(materiales) materi = BRONCE_PULIDO;
                        else modo=POINTS;break;
                case '2':if(materiales) materi = CROMO;
                        else modo=EDGES;break;
                case '3':if(materiales) materi = COBRE;
                        else modo=SOLID;break;
                case '4':if(materiales) materi = COBRE_PULIDO;
                        else modo=SOLID_CHESS;break;
                case 'P':t_objeto=PIRAMIDE;break;
                case 'C':t_objeto=CUBO;break;
                case 'O':t_objeto=OBJETO_PLY;break;	
                case 'R':t_objeto=ROTACION;break;
                case 'D':t_objeto=CILINDRO;break;
                case 'V':t_objeto=CONO;break;
                case 'E':t_objeto=ESFERA;break;
                case 'A':t_objeto=ARTICULADO;break;
                case 'W':eje = (eje+1) % 3;break;
                case '.':camionbomberos.movimiento_camion+=0.1*v_camion;break;
                case ',':camionbomberos.movimiento_camion-=0.1*v_camion;break;
                case '5':if(materiales) materi = ORO;
                        else velocidad_gl = 1;break;
                case '6':if(materiales) materi = ORO_PULIDO;
                        else velocidad_gl = 2;break;
                case '7':if(materiales) materi = PELTRE;
                        else velocidad_gl = 3;break;
                case '8':if(materiales) materi = PLATA;
                        else velocidad_gl = 4;break;
                case '9':if(materiales) materi = PLATA_PULIDA;
                        else velocidad_gl = 5;break;
                case 'I':if(materiales) materi = OBSIDIANA;
                        else velocidad_gl = 6;break;
                case 'U':if(materiales) materi = PERLA;
                        else velocidad_gl = 7;break;
                case 'K':if(materiales) materi = RUBI;
                        else velocidad_gl = 8;break;
                case '0':if(materiales) materi = ESMERALDA;
                        else velocidad_gl = 0;break;
                case '<':modo=SOLID_ILLUMINATED_FLAT;break;
                case '>':modo=SOLID_ILLUMINATED_GOURAUD;break;
                case 'M':mov=true;
                        n_mov = 0;
                        break;
                case 'Y': materi = TURQUESA;
                        break;
                case 'X': materi = PLASTICO_NEGRO;
                        break;
                case 'Z': materi = CAUCHO_NEGRO;
                case '+':
                        switch(velocidad_gl){
                                case 0: //0
                                        v_agua += 0.1;
                                        v_camion += 0.1;
                                        v_elevador += 0.1;
                                        v_ruedas += 0.1;
                                        v_pistola += 0.1;
                                        v_plataforma += 0.1;
                                        v_escalera += 0.1;
                                        v_escaleras += 0.1;
                                        if (v_agua > v_max)
                                                v_agua = v_max;
                                        if(v_camion > v_max)
                                                v_camion = v_max;
                                        if (v_elevador > v_elevador)
                                                v_elevador = v_max;
                                        if(v_ruedas > v_max)
                                                v_ruedas = v_max;
                                        if (v_pistola > v_max)
                                                v_pistola = v_max;
                                        if(v_plataforma > v_max)
                                                v_plataforma = v_max;
                                        if (v_escalera > v_max)
                                                v_escalera = v_max;
                                        if(v_escaleras > v_max)
                                                v_escaleras = v_max;
                                        break;
                                case 1: //5
                                        v_camion += 0.1;
                                        if(v_camion > v_max)
                                                v_camion = v_max;
                                        break;
                                case 2: //6
                                        v_plataforma += 0.1;
                                        if(v_plataforma > v_max)
                                                v_plataforma = v_max;
                                        break;
                                case 3: //7
                                        v_escaleras += 0.1;
                                        if(v_escaleras > v_max)
                                                v_escaleras = v_max;
                                        break;
                                case 4: //8
                                        v_escalera += 0.1;
                                        if(v_escalera > v_max)
                                                v_escalera = v_max;
                                        break;
                                case 5: //9
                                        v_ruedas += 0.1;
                                        if(v_ruedas > v_max)
                                                v_ruedas = v_max;
                                        break;
                                case 6: //I
                                        v_elevador += 0.1;
                                        if(v_elevador > v_max)
                                                v_elevador = v_max;
                                        break;
                                case 7: //U
                                        v_pistola += 0.1;
                                        if(v_pistola > v_max)
                                                v_pistola = v_max;
                                        break;
                                case 8: //Y
                                        v_agua += 0.1;
                                        if(v_agua > v_max)
                                                v_agua = v_max;
                                        break;

                        }


                break;
                case '-':switch(velocidad_gl){
                                case 0://0
                                        v_agua -= 0.1;
                                        v_camion -= 0.1;
                                        v_elevador -= 0.1;
                                        v_ruedas -= 0.1;
                                        v_pistola -= 0.1;
                                        v_plataforma -= 0.1;
                                        v_escalera -= 0.1;
                                        v_escaleras -= 0.1;
                                        if (v_agua < v_min)
                                                v_agua = v_min;
                                        if(v_camion < v_min)
                                                v_camion = v_min;
                                        if (v_elevador > v_elevador)
                                                v_elevador = v_min;
                                        if(v_ruedas < v_min)
                                                v_ruedas = v_min;
                                        if (v_pistola < v_min)
                                                v_pistola = v_min;
                                        if(v_plataforma < v_min)
                                                v_plataforma = v_min;
                                        if (v_escalera < v_min)
                                                v_escalera = v_min;
                                        if(v_escaleras < v_min)
                                                v_escaleras = v_min;
                                        break;
                                case 1://5
                                        v_camion -= 0.1;
                                        if(v_camion < v_min)
                                                v_camion = v_min;
                                        break;
                                case 2://6
                                        v_plataforma -= 0.1;
                                        if(v_plataforma < v_min)
                                                v_plataforma = v_min;
                                        break;
                                case 3://7
                                        v_escaleras -= 0.1;
                                        if(v_escaleras < v_min)
                                                v_escaleras = v_min;
                                        break;
                                case 4://8
                                        v_escalera -= 0.1;
                                        if(v_escalera < v_min)
                                                v_escalera = v_min;
                                        break;
                                case 5://9
                                        v_ruedas -= 0.1;
                                        if(v_ruedas < v_min)
                                                v_ruedas = v_min;
                                        break;
                                case 6://I
                                        v_elevador -= 0.1;
                                        if(v_elevador < v_min)
                                                v_elevador = v_min;
                                        break;
                                case 7: //U
                                        v_pistola -= 0.1;
                                        if(v_pistola < v_min)
                                                v_pistola = v_min;
                                        break;
                                case 8: //Y
                                        v_agua -= 0.1;
                                        if(v_agua < v_min)
                                                v_agua = v_min;
                                        break;

                        }

                break;
                case 'J': 
                        if(materiales){
                                materi = LATON;
                        }
                        else luz.movimientoLuz(1);
                break;
                case 'H': 
                        if(materiales)
                                materi = BRONCE;
                        else luz.movimientoLuz(0);
                break;
                /*case 'L': luz.elevar();
                break;
                case 'Ñ': luz.bajar();
                break;*/
                case 'F':materi = JADE;
                        break;
                case 'B': materi = VACIO;
                        break;
                case 'L': materiales = !materiales;
                }
        glutPostRedisplay();
}

//***************************************************************************
// Funcion l-olamada cuando se aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_key(int Tecla1,int x,int y)
{

        switch (Tecla1){
                case GLUT_KEY_LEFT:Observer_angle_y--;break;
                case GLUT_KEY_RIGHT:Observer_angle_y++;break;
                case GLUT_KEY_UP:Observer_angle_x--;break;
                case GLUT_KEY_DOWN:Observer_angle_x++;break;
                case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
                case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
                case GLUT_KEY_F1:camionbomberos.giro_escalera-=1*v_escaleras;
                                if (camionbomberos.giro_escalera<camionbomberos.giro_escalera_min) camionbomberos.giro_escalera=camionbomberos.giro_escalera_min;
                                break;
                case GLUT_KEY_F2:camionbomberos.giro_escalera+=1*v_escaleras;
                                if (camionbomberos.giro_escalera>camionbomberos.giro_escalera_max) camionbomberos.giro_escalera=camionbomberos.giro_escalera_max;
                                break;
                case GLUT_KEY_F3:camionbomberos.giro_plataforma+=5*v_plataforma;break;
                case GLUT_KEY_F4:camionbomberos.giro_plataforma-=5*v_plataforma;break;
                case GLUT_KEY_F5:camionbomberos.translacion_escalera-=0.1*v_escalera;
                                if (camionbomberos.translacion_escalera<camionbomberos.translacion_escalera_min) camionbomberos.translacion_escalera=camionbomberos.translacion_escalera_min;
                                break;
                case GLUT_KEY_F6:camionbomberos.translacion_escalera+=0.1*v_escalera;
                                if (camionbomberos.translacion_escalera>camionbomberos.translacion_escalera_max) camionbomberos.translacion_escalera=camionbomberos.translacion_escalera_max;
                                break;
                case GLUT_KEY_F7:camionbomberos.giro_ruedas+=2*v_ruedas;
                                break;
                case GLUT_KEY_F8:camionbomberos.giro_ruedas-=2*v_ruedas;
                                break;
                case GLUT_KEY_F9:camionbomberos.levantamiento+=0.08*v_elevador;
                                if (camionbomberos.levantamiento>camionbomberos.levantamiento_max) camionbomberos.levantamiento=camionbomberos.levantamiento_max;
                                break;
                case GLUT_KEY_F10:camionbomberos.levantamiento-=0.08*v_elevador;
                                if (camionbomberos.levantamiento<camionbomberos.levantamiento_min) camionbomberos.levantamiento=camionbomberos.levantamiento_min;
                                break;
                case GLUT_KEY_F11:camionbomberos.giro_pistola_vertical+=1*v_pistola;
                                if (camionbomberos.giro_pistola_vertical>camionbomberos.giro_pistola_vertical_max) camionbomberos.giro_pistola_vertical=camionbomberos.giro_pistola_vertical_max;
                                break;
                case GLUT_KEY_F12:camionbomberos.giro_pistola_vertical-=1*v_pistola;
                                if (camionbomberos.giro_pistola_vertical<camionbomberos.giro_pistola_vertical_min) camionbomberos.giro_pistola_vertical=camionbomberos.giro_pistola_vertical_min;
                                break;
                case GLUT_KEY_HOME:camionbomberos.giro_pistola_horizontal+=1*v_pistola;
                                if (camionbomberos.giro_pistola_horizontal>camionbomberos.giro_pistola_horizontal_max) camionbomberos.giro_pistola_horizontal=camionbomberos.giro_pistola_horizontal_max;
                                break;
                case GLUT_KEY_END: camionbomberos.giro_pistola_horizontal-=1*v_pistola;
                                if (camionbomberos.giro_pistola_horizontal<camionbomberos.giro_pistola_horizontal_min) camionbomberos.giro_pistola_horizontal=camionbomberos.giro_pistola_horizontal_min;
                                break;
                case GLUT_KEY_INSERT: camionbomberos.movimiento_agua+=0.1*v_agua;
                                if (camionbomberos.movimiento_agua>2) camionbomberos.movimiento_agua=0;
                                break;
                }

        glutPostRedisplay();
}

void movimiento()
{
        if(mov){
                switch(n_mov){
                        case 0: //camion acelera
                                camionbomberos.giro_ruedas-=2;  
                                n++;
                                if(n>20) //para que acelere bien
                                camionbomberos.movimiento_camion+=0.01;
                                if(camionbomberos.movimiento_camion > 2){
                                        n_mov = 1;
                                        n=0;
                                }
                        break;
                        case 1: //levanto las escaleras
                                camionbomberos.giro_escalera+=0.4;  
                                if(camionbomberos.giro_escalera > camionbomberos.giro_escalera_max){
                                        n_mov = 2;
                                }
                        break;
                        case 2: //giro las escaleras
                                camionbomberos.giro_plataforma+=1;  
                                if(camionbomberos.giro_plataforma > 30){
                                        n_mov = 3;
                                }
                        break;
                        case 3: //subo la escalera pequeña
                                camionbomberos.translacion_escalera+=0.007;
                                if(camionbomberos.translacion_escalera > camionbomberos.translacion_escalera_max){
                                        n_mov = 4;
                                }
                        break;
                        case 4: //subo el elevador
                                camionbomberos.levantamiento+=0.005;
                                if(camionbomberos.levantamiento > camionbomberos.levantamiento_max){
                                        n_mov = 5;
                                }
                        break;
                        case 5: //muevo la pistola
                                camionbomberos.giro_pistola_horizontal+=0.4;
                                camionbomberos.giro_pistola_vertical+=0.4;
                                if (camionbomberos.giro_pistola_horizontal > 8.3)
                                        n_mov = 6;
                        break;
                        case 6: //expulso agua
                                if(n<20){
                                        camionbomberos.movimiento_agua+=0.1;
                                        if (camionbomberos.movimiento_agua > 2){
                                                camionbomberos.movimiento_agua=0;
                                                n++;
                                        }
                                }
                                else{
                                        n_mov = 7;
                                }
                        break;
                        case 7:
                                camionbomberos.movimiento_agua = 0;
                                n_mov = 8;
                        break;
                        case 8:
                                //muevo la pistola
                                camionbomberos.giro_pistola_horizontal-=0.4;
                                camionbomberos.giro_pistola_vertical-=0.4;
                                if (camionbomberos.giro_pistola_horizontal < 0.0)
                                        n_mov = 9;

                        break;
                        case 9://bajo el elevador
                                camionbomberos.levantamiento-=0.005;
                                if(camionbomberos.levantamiento < 0.0){
                                        n_mov = 10;
                                }
                        break;
                        case 10: //bajo la escalera pequeña
                                camionbomberos.translacion_escalera-=0.007;
                                if(camionbomberos.translacion_escalera < 0.0){
                                        n_mov = 11;
                                }
                        break;
                        case 11://giro las escaleras
                                camionbomberos.giro_plataforma-=1;  
                                if(camionbomberos.giro_plataforma < 0){
                                        n_mov = 12;
                                }
                        break;
                        case 12: //levanto las escaleras
                                camionbomberos.giro_escalera-=0.4;  
                                if(camionbomberos.giro_escalera < 0){
                                        n_mov = 13;
                                }
                        break;
                        case 13: //camion acelera
                                camionbomberos.giro_ruedas+=2;  
                                n++;
                                if(n>20) //para que acelere bien
                                camionbomberos.movimiento_camion-=0.01;
                                if(camionbomberos.movimiento_camion < 0){
                                        n_mov = 14;
                                        n=0;
                                }
                        break;
                        


                }
                glutPostRedisplay();
         }
}

//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{

// se inicalizan la ventana y los planos de corte
Size_x=0.5;
Size_y=0.5;
Front_plane=1;
Back_plane=1000;

// se incia la posicion del observador, en el eje z
Observer_distance=4*Front_plane;
Observer_angle_x=0;
Observer_angle_y=0;

// se indica cua*ply1l sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(1,1,1,1);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
change_projection();
glViewport(0,0,Window_width,Window_high);



}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************


int main(int argc, char **argv)
{
// creación del objeto ply

ply.parametros((char *)"beethoven");


// perfil 

vector<_vertex3f> perfil2;
_vertex3f aux;
aux.x=1.0;aux.y=-1.4;aux.z=0.0;
perfil2.push_back(aux);
aux.x=1.0;aux.y=-1.1;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.5;aux.y=-0.7;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.4;aux.y=-0.4;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.4;aux.y=0.5;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.5;aux.y=0.6;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.3;aux.y=0.6;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.5;aux.y=0.8;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.55;aux.y=1.0;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.5;aux.y=1.2;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.3;aux.y=1.4;aux.z=0.0;
perfil2.push_back(aux);
rotaciony.parametros(perfil2,6,1);
rotacionz.parametros(perfil2,6,0);
rotacionx.parametros(perfil2,6,2);


// se llama a la inicialización de glut
glutInit(&argc, argv);

// se indica las caracteristicas que se desean para la visualización con OpenGL
// Las posibilidades son:
// GLUT_SIMPLE -> memoria de imagen simple
// GLUT_DOUBLE -> memoria de imagen doble
// GLUT_INDEX -> memoria de imagen con color indizado
// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
// GLUT_DEPTH -> memoria de profundidad o z-bufer
// GLUT_STENCIL -> memoria de estarcido_rotation Rotation;
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

// posicion de la esquina inferior izquierdad de la ventana
glutInitWindowPosition(Window_x,Window_y);

// tamaño de la ventana (ancho y alto)
glutInitWindowSize(Window_width,Window_high);

// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
// al bucle de eventos)
glutCreateWindow("PRACTICA - 4");

// asignación de la funcion llamada "dibujar" al evento de dibujo
glutDisplayFunc(draw);
// asignación de la funcion llamada "change_window_size" al evento correspondiente
glutReshapeFunc(change_window_size);
// asignación de la funcion llamada "normal_key" al evento correspondiente
glutKeyboardFunc(normal_key);
// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
glutSpecialFunc(special_key);

glutIdleFunc(movimiento);

// funcion de inicialización
initialize();

// inicio del bucle de eventos
glutMainLoop();
return 0;
}

