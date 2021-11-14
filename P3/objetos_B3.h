//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>
#include "file_ply_stl.hpp"

using namespace std;

const float AXIS_SIZE=5000;
typedef enum{POINTS,EDGES,SOLID_CHESS,SOLID} _modo;

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:

  
	_puntos3D();
void 	draw_puntos(float r, float g, float b, int grosor);

vector<_vertex3f> vertices;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D
{
public:

	_triangulos3D();
void 	draw_aristas(float r, float g, float b, int grosor);
void    draw_solido(float r, float g, float b);
void 	draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

vector<_vertex3i> caras;
};


//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo: public _triangulos3D
{
public:

	_cubo(float tam=0.5);
};


//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide: public _triangulos3D
{
public:

	_piramide(float tam=0.5, float al=0.75);
};

//*************************************************************************
// clase objeto ply
//*************************************************************************

class _objeto_ply: public _triangulos3D
{
public:
   _objeto_ply();

int   parametros(char *archivo);
};

//************************************************************************
// objeto por revolución
//************************************************************************

class _rotacion: public _triangulos3D
{
public:
       _rotacion();
void  parametros(vector<_vertex3f> perfil1, int num1, int tapas);

vector<_vertex3f> perfil; 
int num;
};


//*************************************************************************
// clase cilindro
//*************************************************************************

class _cilindro: public _rotacion
{
public:

	_cilindro(float radio=0.60, float al=1.8, int n = 15, int eje = 1);
};


//*************************************************************************
// clase cono
//*************************************************************************

class _cono: public _rotacion
{
public:

	_cono(float radio=0.6, float al=1.8, int n = 15, int eje = 1);
};


//*************************************************************************
// clase esfera
//*************************************************************************

class _esfera: public _rotacion
{
public:

	_esfera(float radio=1.2, int n = 10, int eje = 2);

};


//************************************************************************
// objeto articulado: tanque
//************************************************************************

class _chasis: public _triangulos3D
{
public:
       _chasis();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float altura;

protected:
_rotacion  rodamiento;
_cubo  base;
};

//************************************************************************

class _torreta: public _triangulos3D
{
public:
       _torreta();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float altura;
float anchura;

protected:
_cubo  base;
_piramide parte_trasera;
};

//************************************************************************

class _tubo: public _triangulos3D
{
public:
       _tubo();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

protected:
_rotacion tubo_abierto; // caña del cañón
};

//************************************************************************

class _tanque: public _triangulos3D
{
public:
       _tanque();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float giro_tubo;
float giro_torreta;

float giro_tubo_min;
float giro_tubo_max;

protected:
_chasis  chasis;
_torreta  torreta;
_tubo     tubo;
};


//*********************************************************************
// objeto articulado: camion de bomberos
//*********************************************************************
class _ruedas: public _triangulos3D
{
public:
       _ruedas();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float radio;

protected:
_cilindro rueda;

};


class _carroceria: public _triangulos3D
{
public:
       _carroceria();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float radio;

protected:
_cubo carcasa;
_esfera foco;
_cilindro sirena;
};


class _plataforma: public _triangulos3D
{
public:
       _plataforma();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float radio;

protected:
_cubo base;
_cubo lateral1;
_cubo lateral2;

};



class _escaleragrande: public _triangulos3D
{
public:
       _escaleragrande();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float radio;

protected:
_cubo barra_mano;
_cubo barra_lateral;

};

class _escalerachica: public _triangulos3D
{
public:
       _escalerachica();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float radio;

protected:
_cubo barra_mano;
_cubo barra_lateral;

};


class _cabina: public _triangulos3D
{
public:
       _cabina();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float radio;

protected:
_cubo barra;

};

class _elevador: public _triangulos3D
{
public:
       _elevador();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float radio;

protected:
_cubo barra;

};

class _agua: public _triangulos3D
{
public:
       _agua();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

protected:
_esfera gota;

};

class _pistola: public _triangulos3D
{
public:
       _pistola();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

protected:
_cubo base;
_cilindro pistola;

};

class _camionbomberos: public _triangulos3D{
       public:
       _camionbomberos();
       void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

       float giro_tubo;
       int giro_ruedas;
       int giro_plataforma = 0.0;
       float translacion_escalera = 0.0;
       float translacion_escalera_min = 0.0;
       float translacion_escalera_max = 2.3;
       int giro_escalera = -2;
       float giro_escalera_min = -2.0;
       float giro_escalera_max = 30.0;
       float levantamiento = 0;
       float levantamiento_max = 0.6;
       float levantamiento_min = 0;
       float giro_pistola_horizontal_min = -30;
       float giro_pistola_horizontal_max = 30;
       float giro_pistola_horizontal = 0;
       float giro_pistola_vertical_min = -30;
       float giro_pistola_vertical_max = 30;
       float giro_pistola_vertical = 0;
       float movimiento_agua = 0;
       
       protected:
       _ruedas  ruedas;
       _carroceria carroceria;
       _plataforma plataforma;
       _escaleragrande escaleragrande;
       _escalerachica escalerachica;
       _cabina cabina;
       _elevador elevador;
       _pistola pistola;
       _agua agua;
};
