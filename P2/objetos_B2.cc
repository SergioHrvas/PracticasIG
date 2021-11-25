//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include "objetos_B2.h"
#include <iostream>
#include "file_ply_stl.hpp"
#include <cmath>

using namespace std;
//*************************************************************************
// _puntos3D
//*************************************************************************

_puntos3D::_puntos3D()
{
}

//*************************************************************************
// dibujar puntos
//*************************************************************************

void _puntos3D::draw_puntos(float r, float g, float b, int grosor)
{
int i;
glPointSize(grosor);
glColor3f(r,g,b);
glBegin(GL_POINTS);
for (i=0;i<vertices.size();i++){
	glVertex3fv((GLfloat *) &vertices[i]);
	}
glEnd();
}


//*************************************************************************
// _triangulos3D
//*************************************************************************

_triangulos3D::_triangulos3D()
{
}


//*************************************************************************
// dibujar en modo arista
//*************************************************************************

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor)
{
int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
glLineWidth(grosor);
glColor3f(r,g,b);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();
}

//*************************************************************************
// dibujar en modo sólido
//*************************************************************************

void _triangulos3D::draw_solido(float r, float g, float b)
{
int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
glColor3f(r,g,b);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();




}

//*************************************************************************
// dibujar en modo sólido con apariencia de ajedrez
//*************************************************************************

void _triangulos3D::draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2)
{
int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	if(i%2==0){
		glColor3f(r1,g1,b1);
	}
	else if(i==6){
		glColor3f(r2,g2,b2);

	}
	else{
		glColor3f(r2,g2,b2);
	}
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();
}

//*************************************************************************
// dibujar con distintos modos
//*************************************************************************

void _triangulos3D::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
switch (modo){
	case POINTS:draw_puntos(r1, g1, b1, grosor);break;
	case EDGES:draw_aristas(r1, g1, b1, grosor);break;
	case SOLID_CHESS:draw_solido_ajedrez(r1, g1, b1, r2, g2, b2);break;
	case SOLID:draw_solido(r1, g1, b1);break;
	}
}

//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam)
{

//vértices
vertices.resize(8); 
vertices[0].x=-tam;vertices[0].y=0;vertices[0].z=tam;
vertices[1].x=tam;vertices[1].y=0;vertices[1].z=tam;
vertices[2].x=tam;vertices[2].y=0;vertices[2].z=-tam;
vertices[3].x=-tam;vertices[3].y=0;vertices[3].z=-tam;
vertices[4].x=-tam;vertices[4].y=2*tam;vertices[4].z=tam;
vertices[5].x=tam;vertices[5].y=2*tam;vertices[5].z=tam;
vertices[6].x=tam;vertices[6].y=2*tam;vertices[6].z=-tam;
vertices[7].x=-tam;vertices[7].y=2*tam;vertices[7].z=-tam;


// triangulos
caras.resize(12);
caras[0]._0=0;caras[0]._1=1;caras[0]._2=2;
caras[1]._0=2;caras[1]._1=3;caras[1]._2=0;
caras[2]._0=0;caras[2]._1=1;caras[2]._2=5;
caras[3]._0=5;caras[3]._1=4;caras[3]._2=0;
caras[4]._0=1;caras[4]._1=6;caras[4]._2=2;
caras[5]._0=6;caras[5]._1=5;caras[5]._2=1;
caras[6]._0=2;caras[6]._1=6;caras[6]._2=3;
caras[7]._0=3;caras[7]._1=7;caras[7]._2=6;
caras[8]._0=6;caras[8]._1=5;caras[8]._2=4;
caras[9]._0=6;caras[9]._1=7;caras[9]._2=4;
caras[10]._0=7;caras[10]._1=3;caras[10]._2=0;
caras[11]._0=4;caras[11]._1=7;caras[11]._2=0;
}



//*************************************************************************
// clase piramide
//*************************************************************************

_piramide::_piramide(float tam, float al)
{

//vertices 
vertices.resize(5); 
vertices[0].x=-tam;vertices[0].y=0;vertices[0].z=tam;
vertices[1].x=tam;vertices[1].y=0;vertices[1].z=tam;
vertices[2].x=tam;vertices[2].y=0;vertices[2].z=-tam;
vertices[3].x=-tam;vertices[3].y=0;vertices[3].z=-tam;
vertices[4].x=0;vertices[4].y=al;vertices[4].z=0;

caras.resize(6);
caras[0]._0=0;caras[0]._1=1;caras[0]._2=4;
caras[1]._0=1;caras[1]._1=2;caras[1]._2=4;
caras[2]._0=2;caras[2]._1=3;caras[2]._2=4;
caras[3]._0=3;caras[3]._1=0;caras[3]._2=4;
caras[4]._0=3;caras[4]._1=1;caras[4]._2=0;
caras[5]._0=3;caras[5]._1=2;caras[5]._2=1;
}

//*************************************************************************
// clase objeto ply
//*************************************************************************


_objeto_ply::_objeto_ply() 
{
   // leer lista de coordenadas de vértices y lista de indices de vértices
 
}



int _objeto_ply::parametros(char *archivo)
{
int n_ver,n_car;

vector<float> ver_ply ;
vector<int>   car_ply ;
 
_file_ply::read(archivo, ver_ply, car_ply );

n_ver=ver_ply.size()/3;
n_car=car_ply.size()/3;

printf("Number of vertices=%d\nNumber of faces=%d\n", n_ver, n_car);

vertices.resize(n_ver);
for(int i=0; i<n_ver; i++){
	vertices[i].x = ver_ply[3*i];
	vertices[i].y = ver_ply[3*i+1];
	vertices[i].z = ver_ply[3*i+2];

}



caras.resize(n_car);
for(int i=0; i<n_car; i++){
	caras[i]._0=car_ply[3*i];
	caras[i]._1=car_ply[3*i+1];
	caras[i]._2=car_ply[3*i+2];

}


return(0);
}


//************************************************************************
// objeto por revolucion
//************************************************************************

_rotacion::_rotacion()
{

}

//num_aux: nro de puntos que tiene el perfil
//num: numero de perfiles
//eje:
	// x -> 0
	// y -> 1
	// z -> 2
void _rotacion::parametros(vector<_vertex3f> perfil, int num, int eje)
{
//cout << endl;
int i,j;
_vertex3f vertice_aux;
_vertex3i cara_aux;
int num_aux, num_auxB;

//creamos un perfil nuevo
vector<_vertex3f> perfilnuevo;


//rotamos el vertice segun el eje 

if(eje==0){
	for(int i = 0; i < perfil.size(); i++){
		int aux = perfil[i].z;
		perfil[i].z = perfil[i].x;
		perfil[i].x = perfil[i].y;
		perfil[i].y = aux;
	}
}
else if(eje==2){
	for(int i = 0; i < perfil.size(); i++){
		int aux = perfil[i].z;
		perfil[i].z = perfil[i].y;
		perfil[i].y = perfil[i].x;
		perfil[i].x = aux;
	}
}
//cout << "\t" << "PN: " << perfilnuevo.size() << "  " << endl;


////// tratamiento de los vértices //////
switch(eje){
	case 0: 

			//metemos en el nuevo perfil los vértices del perfil que NO están en el eje y
			for(int i = 0 ; i < perfil.size(); i++){
				if(fabs(perfil[i].z)>0)
					perfilnuevo.push_back(perfil[i]);
			}
			num_aux=perfil.size();
			num_auxB=perfilnuevo.size(); //numero de vertices del perfil sin los del eje y
			cout << "NUMAUX: " << num_aux << endl;
			//rotamos los vértices
			for (j=0;j<num;j++)
			  {for (i=0;i<num_auxB;i++)
			     {
			      vertice_aux.x=perfilnuevo[i].x;
			      vertice_aux.z=-perfilnuevo[i].y*sin(2.0*M_PI*j/(1.0*num))+
			                    perfilnuevo[i].z*cos(2.0*M_PI*j/(1.0*num));
			      vertice_aux.y=perfilnuevo[i].y*cos(2.0*M_PI*j/(1.0*num))+
			                    perfilnuevo[i].z*sin(2.0*M_PI*j/(1.0*num));
			      vertices.push_back(vertice_aux);
			     }
			  }

				break;
	case 1:
			//metemos en el nuevo perfil los vértices del perfil que NO están en el eje y
			for(int i = 0 ; i < perfil.size(); i++){
				if(fabs(perfil[i].x)>0)
					perfilnuevo.push_back(perfil[i]);
			}
			num_aux=perfil.size();
			num_auxB=perfilnuevo.size(); //numero de vertices del perfil sin los del eje y

			//rotamos los vértices
			for (j=0;j<num;j++)
			  {for (i=0;i<num_auxB;i++)
			     {
			      vertice_aux.x=perfilnuevo[i].x*cos(2.0*M_PI*j/(1.0*num))+
			                    perfilnuevo[i].z*sin(2.0*M_PI*j/(1.0*num));
			      vertice_aux.z=-perfilnuevo[i].x*sin(2.0*M_PI*j/(1.0*num))+
			                    perfilnuevo[i].z*cos(2.0*M_PI*j/(1.0*num));
			      vertice_aux.y=perfilnuevo[i].y;
			      vertices.push_back(vertice_aux);
			     }
			  }

				break;
	case 2: 
			//metemos en el nuevo perfil los vértices del perfil que NO están en el eje y
			for(int i = 0 ; i < perfil.size(); i++){
				if(fabs(perfil[i].y)>0)
					perfilnuevo.push_back(perfil[i]);
			}
			num_aux=perfil.size();
			num_auxB=perfilnuevo.size(); //numero de vertices del perfil sin los del eje y

			//rotamos los vértices
			for (j=0;j<num;j++)
			  {for (i=0;i<num_auxB;i++)
			     {
			      vertice_aux.x=perfilnuevo[i].x*cos(2.0*M_PI*j/(1.0*num))+
			                    perfilnuevo[i].y*sin(2.0*M_PI*j/(1.0*num));
			      vertice_aux.z=perfilnuevo[i].z;
			      vertice_aux.y=-perfilnuevo[i].x*sin(2.0*M_PI*j/(1.0*num))+
			                    perfilnuevo[i].y*cos(2.0*M_PI*j/(1.0*num));
			      vertices.push_back(vertice_aux);
			     }
			  }
				break;
}

  
 ////// Tratamiento de las tapas //////
 // tapa inferior
switch(eje){
	case 0:
  	vertice_aux.x = perfil[0].x;
  	vertice_aux.y = 0.0;
  	vertice_aux.z = 0.0;
				break;
	case 1:  	
			vertice_aux.x = 0.0;
  		vertice_aux.y = perfil[0].y;
  		vertice_aux.z = 0.0;
				break;
	case 2:
			vertice_aux.x = 0.0;
  		vertice_aux.y = 0.0;
  		vertice_aux.z = perfil[0].z;
				break;				

}

  	vertices.push_back(vertice_aux);
  	cara_aux._0 = vertices.size()-1;
  	for(int i = 0; i<num; i++){
  		cara_aux._2 = ((i+1)%num)*num_auxB;
   		cara_aux._1 = i*num_auxB;
  		caras.push_back(cara_aux);
  	}
 
 // tapa superior
switch(eje){
	case 0:
  	vertice_aux.x = perfil[perfil.size()-1].x;
  	vertice_aux.y = 0.0;
  	vertice_aux.z = 0.0;
				break;
	case 1:  	
			vertice_aux.x = 0.0;
  		vertice_aux.y = perfil[perfil.size()-1].y;
  		vertice_aux.z = 0.0;
				break;
	case 2:
			vertice_aux.x = 0.0;
  		vertice_aux.y = 0.0;
  		vertice_aux.z = perfil[perfil.size()-1].z;
				break;				

}

  	vertices.push_back(vertice_aux);
  	cara_aux._0 = vertices.size()-1;
  	for(int i = 0; i<num; i++){
  		cara_aux._1 = ((i+1)%num)*num_auxB+num_auxB-1;
   		cara_aux._2 = (i+1)*num_auxB-1;

  		caras.push_back(cara_aux);
  	}

  	
 ////// tratamiento de las caras ////// 
for (int i = 0; i < num; ++i)
{
	for (int j = 0; j < num_auxB-1; ++j)
	{
	  cara_aux._0 = i*num_auxB+j; //1
	  cara_aux._1 = ((i+1)%num)*num_auxB+j; //4
	  cara_aux._2 = ((i+1)%num)*num_auxB+j+1; //5
	  caras.push_back(cara_aux);


	  cara_aux._2 = i*num_auxB+j; //1
	  cara_aux._1 = i*num_auxB+j+1; //2
	  cara_aux._0 = ((i+1)%num)*num_auxB+j+1; //5
	  caras.push_back(cara_aux);
	}
}





  }
//*************************************************************************
// clase cilindro
//*************************************************************************

_cilindro::_cilindro(float radio, float al, int n, int eje)
{

//vértices
vector<_vertex3f> perfil;
_vertex3f vertice_aux;

vertice_aux.x=radio;vertice_aux.y=-al/2;vertice_aux.z=0;
perfil.push_back(vertice_aux);
vertice_aux.x=radio;vertice_aux.y=al/2;vertice_aux.z=0;
perfil.push_back(vertice_aux);

cout << "Cilindro: ";
parametros(perfil, n, eje);

}


//*************************************************************************
// clase cono
//*************************************************************************

_cono::_cono(float radio, float al, int n, int eje)
{


	vector<_vertex3f> perfil;
_vertex3f vertice_aux;
//vértices

vertice_aux.x=radio;vertice_aux.y=-al/2;vertice_aux.z=0;
					perfil.push_back(vertice_aux);
					vertice_aux.x=0;vertice_aux.y=al/2;vertice_aux.z=0;
					perfil.push_back(vertice_aux);

cout << "Cono: ";
parametros(perfil, n, eje);

}



//*************************************************************************
// clase esfera
//*******************
_esfera::_esfera(float radio, int n, int eje){
	vector<_vertex3f> perfil;
_vertex3f vertice_aux;
int angulo_llano = 180;
float angulo = 0;
int num = 15;


				for(int i = 0; i <= num; i++){
					angulo = (angulo_llano/num)*i;
					angulo +=270;
					vertice_aux.x = cos(angulo*M_PI/180)*radio;
					vertice_aux.y = sin(angulo*M_PI/180)*radio;
					vertice_aux.z = 0.0;
					perfil.push_back(vertice_aux);
				}
				perfil[0].x = 0;
				perfil[num].x = 0;
	
cout << "Esfera: ";

parametros(perfil, n, eje);

}
