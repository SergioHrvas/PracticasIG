//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>
#include "file_ply_stl.hpp"

using namespace std;

const float AXIS_SIZE = 5000;
typedef enum
{
       POINTS,
       EDGES,
       SOLID_CHESS,
       SOLID,
       SOLID_ILLUMINATED_FLAT,
       SOLID_ILLUMINATED_GOURAUD,
       SELECT
} _modo;
typedef enum
{
       VACIO,
       ORO,
       ORO_PULIDO,
       BRONCE,
       BRONCE_PULIDO,
       LATON,
       CROMO,
       COBRE,
       COBRE_PULIDO,
       PELTRE,
       PLATA,
       PLATA_PULIDA,
       ESMERALDA,
       JADE,
       OBSIDIANA,
       PERLA,
       RUBI,
       TURQUESA,
       PLASTICO_NEGRO,
       CAUCHO_NEGRO
} _material;

//*************************************************************************
// clase material
//*************************************************************************

class _Material
{
public:
       GLfloat ambiente[4], difusa[4], especular[4];
       float brillo;

       _material mat;
       _Material(_material mat = ORO);
};

//*************************************************************************
// clase luz
//*************************************************************************

class Luz
{
private:
       _vertex4f ambiente, difusa, especular;
       _vertex4f posicion;
       int angulo = 0;
       GLenum id;

public:
       Luz();
       Luz(GLenum id, _vertex4f amb, _vertex4f dif, _vertex4f espec, _vertex4f pos);
       void encenderLuz();
       void apagarLuz();
       void draw();
       void movimientoLuz(bool horario);
       void setAmbiente(float *color);
       void setDifusa(float *color);
       void setEspecular(float *color);
       void setPosicion(float *pos);
       void setIDLuz(GLenum id);
};

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:
       _puntos3D();
       void draw_puntos(float r, float g, float b, int grosor);

       vector<_vertex3f> vertices;
};

void luces();
//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D : public _puntos3D
{
public:
       _triangulos3D();
       void draw_aristas(float r, float g, float b, int grosor);
       void draw_solido(float r, float g, float b);
       void draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);
       void draw_iluminacion_plana(_material mate);
       void draw_iluminacion_suave(_material mate);
       void draw_seleccion(int r, int g, int b);
       void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, _material mate);

       //calcular las normales
       void calcular_normales_caras();
       void calcular_normales_vertices();

       vector<_vertex3i> caras;

       vector<_vertex3f> normales_caras;
       vector<_vertex3f> normales_vertices;

       //para saber si se ha calculado o no y asi no calcularlo cada vez que dibujemos
       bool b_normales_caras;
       bool b_normales_vertices;

       //material
       _vertex4f ambiente; //coeficientes ambiente y difuso
       _vertex4f difusa;
       _vertex4f especular; //coeficiente especular
       float brillo;        //exponente del brillo

       _Material material;



};

//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo : public _triangulos3D
{
public:
       _cubo(float tam = 0.5);
       void seleccion();

};

//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide : public _triangulos3D
{
public:
       _piramide(float tam = 0.5, float al = 0.75);
};

//*************************************************************************
// clase objeto ply
//*************************************************************************

class _objeto_ply : public _triangulos3D
{
public:
       _objeto_ply();

       int parametros(char *archivo);
};

//************************************************************************
// objeto por revolución
//************************************************************************

class _rotacion : public _triangulos3D
{
public:
       _rotacion();
       void parametros(vector<_vertex3f> perfil1, int num1, int tapas);

       vector<_vertex3f> perfil;
       int num;
};

//*************************************************************************
// clase cilindro
//*************************************************************************

class _cilindro : public _rotacion
{
public:
       _cilindro(float radio = 0.60, float al = 1.8, int n = 15, int eje = 1);
};

//*************************************************************************
// clase cono
//*************************************************************************

class _cono : public _rotacion
{
public:
       _cono(float radio = 0.6, float al = 1.8, int n = 15, int eje = 1);
};

//*************************************************************************
// clase esfera
//*************************************************************************

class _esfera : public _rotacion
{
public:
       _esfera(float radio = 1.2, int n = 10, int eje = 2);
       void calcular_normales_vertices();
};

//************************************************************************
// objeto articulado: tanque
//************************************************************************

class _chasis : public _triangulos3D
{
public:
       _chasis();
       void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, _material mate);

       float altura;

protected:
       _rotacion rodamiento;
       _cubo base;
};

//************************************************************************

class _torreta : public _triangulos3D
{
public:
       _torreta();
       void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, _material mate);

       float altura;
       float anchura;

protected:
       _cubo base;
       _piramide parte_trasera;
};

//************************************************************************

class _tubo : public _triangulos3D
{
public:
       _tubo();
       void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, _material mate);

protected:
       _rotacion tubo_abierto; // caña del cañón
};

//************************************************************************

class _tanque : public _triangulos3D
{
public:
       _tanque();
       void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, _material mate);
       void seleccion();

       float giro_tubo;
       float giro_torreta;

       float giro_tubo_min;
       float giro_tubo_max;

       float color_pick[3];
       int color_selec[3][3];
       int activo[3];
       int piezas;

protected:
       _chasis chasis;
       _torreta torreta;
       _tubo tubo;
};

//*********************************************************************
// objeto articulado: camion de bomberos
//*********************************************************************
class _ruedas_der : public _triangulos3D
{
public:
       _ruedas_der();
       void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, _material mate);
       void seleccion();
       float radio;

       float color_pick[3];
       int color_selec[3][2];
       int activo[2];
       int piezas;
       
protected:
       _cilindro rueda;
       _cilindro llanta;

};
class _ruedas_izq : public _triangulos3D
{
public:
       _ruedas_izq();
       void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, _material mate);
       void seleccion();      
       float radio;
       float color_pick[3];
       int color_selec[3][2];
       int activo[2];
       int piezas;
protected:
       _cilindro rueda;
       _cilindro llanta;
};

class _carroceria : public _triangulos3D
{
public:
       _carroceria();
       void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, _material mate);
       void seleccion();
       float radio;

       float color_pick[3];
       int color_selec[3][18];
       int activo[18];
       int piezas;
protected:
       _cubo carcasa;
       _cubo reposa;
       _cubo puerta1, puerta2, puerta3;
       _esfera foco1, foco2;
       _cilindro sirena1, sirena2;
       _cubo matricula_b,matricula_a,matricula_b2,matricula_a2;
       _cubo luza, luza2, luzb, luzb2, luzc, luzc2; 
};

class _ventana : public _triangulos3D
{
public:
       _ventana();
       void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, _material mate);
       void seleccion();
       float radio;
       
       float color_pick[3];
       int color_selec[3][3];
       int activo[3];
       int piezas;
       
       protected:
       _cubo ventana1, ventana2, parabrisas;


};

class _plataforma : public _triangulos3D
{
public:
       _plataforma();
       void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, _material mate);
       float radio;

protected:
       _cubo cubo;
};

class _escaleragrande : public _triangulos3D
{
public:
       _escaleragrande();
       void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, _material mate);
       float radio;

protected:
       _cubo barra;
};

class _escalerachica : public _triangulos3D
{
public:
       _escalerachica();
       void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, _material mate);
       float radio;

protected:
       _cubo barra;
};

class _cabina : public _triangulos3D
{
public:
       _cabina();
       void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, _material mate);
       float radio;

protected:
       _cubo barra;
};

class _elevador : public _triangulos3D
{
public:
       _elevador();
       void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, _material mate);
       float radio;

protected:
       _cubo barra;
};

class _agua : public _triangulos3D
{
public:
       _agua();
       void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, _material mate);

protected:
       _esfera gota;
};

class _pistola : public _triangulos3D
{
public:
       _pistola();
       void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, _material mate);

protected:
       _cubo base;
       _cilindro pistola;
};

class _camionbomberos : public _triangulos3D
{
public:
       _camionbomberos();
       void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, _material mate);
       void seleccion();
       float giro_tubo;
       int giro_ruedas;
       float giro_plataforma = 0.0;
       float translacion_escalera = 0.0;
       float translacion_escalera_min = 0.0;
       float translacion_escalera_max = 2.3;
       float giro_escalera = -2;
       float giro_escalera_min = -2.0;
       float giro_escalera_max = 30.0;
       float levantamiento = 0;
       float levantamiento_max = 0.6;
       float levantamiento_min = 0;
       float giro_pistola_horizontal_min = -20;
       float giro_pistola_horizontal_max = 20;
       float giro_pistola_horizontal = 0;
       float giro_pistola_vertical_min = -20;
       float giro_pistola_vertical_max = 20;
       float giro_pistola_vertical = 0;
       float movimiento_agua = 0;
       float movimiento_camion = 0;
       float movimiento_camion_max = 3;
       float movimiento_camion_min = -3;

       float color_pick[3];
       int color_selec[3][7];
       int activo[7];
       int piezas;

              _ruedas_der rueda1, rueda2, rueda3;
       _ruedas_izq rueda4, rueda5, rueda6;
       _carroceria carroceria;
       _ventana ventana;
       _plataforma plataforma;
       _escaleragrande escaleragrande;
       _escalerachica escalerachica;
       _cabina cabina;
       _elevador elevador;
       _pistola pistola;
       _agua agua;
};
