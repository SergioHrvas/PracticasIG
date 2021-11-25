//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include "objetos_B.h"


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
// _triangulos3D - Constructor
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
// clase cuboRaro
//*************************************************************************

_cuboRaro::_cuboRaro(float tam)
{

//vértices
vertices.resize(17); 
vertices[0].x=0;vertices[0].y=0;vertices[0].z=2*tam;
vertices[1].x=2*tam;vertices[1].y=0;vertices[1].z=2*tam;
vertices[2].x=2*tam;vertices[2].y=0;vertices[2].z=0;
vertices[3].x=0;vertices[3].y=0;vertices[3].z=0;
vertices[4].x=0;vertices[4].y=0.2;vertices[4].z=2*tam;
vertices[5].x=0.2;vertices[5].y=0.2;vertices[5].z=2*tam;
vertices[6].x=2*tam;vertices[6].y=0.2;vertices[6].z=2*tam;
vertices[7].x=2*tam;vertices[7].y=0.2;vertices[7].z=0.4;
vertices[8].x=0.2;vertices[8].y=0.2;vertices[8].z=0.4;
vertices[9].x=2*tam;vertices[9].y=0.2;vertices[9].z=0;
vertices[10].x=0.2;vertices[10].y=0.2;vertices[10].z=0;
vertices[11].x=0;vertices[11].y=0.2;vertices[11].z=0;
vertices[12].x=0;vertices[12].y=2*tam;vertices[12].z=2*tam;
vertices[13].x=0.2;vertices[13].y=2*tam;vertices[13].z=2*tam;
vertices[14].x=0.2;vertices[14].y=2*tam;vertices[14].z=0.4;
vertices[15].x=0.2;vertices[15].y=2*tam;vertices[15].z=0;
vertices[16].x=0;vertices[16].y=2*tam;vertices[16].z=0;

// triangulos
caras.resize(26);
caras[0]._0=0;caras[0]._1=1;caras[0]._2=4;
caras[1]._0=1;caras[1]._1=4;caras[1]._2=6;

caras[2]._0=1;caras[2]._1=2;caras[2]._2=6;
caras[3]._0=2;caras[3]._1=9;caras[3]._2=6;

caras[4]._0=9;caras[4]._1=3;caras[4]._2=11;
caras[5]._0=3;caras[5]._1=2;caras[5]._2=9;

caras[6]._0=11;caras[6]._1=0;caras[6]._2=3;
caras[7]._0=4;caras[7]._1=0;caras[7]._2=11;

caras[8]._0=4;caras[8]._1=5;caras[8]._2=12;
caras[9]._0=5;caras[9]._1=13;caras[9]._2=12;

caras[10]._0=13;caras[10]._1=5;caras[10]._2=8;
caras[11]._0=13;caras[11]._1=14;caras[11]._2=8;

caras[12]._0=8;caras[12]._1=5;caras[12]._2=7;
caras[13]._0=6;caras[13]._1=5;caras[13]._2=7;

caras[14]._0=14;caras[14]._1=8;caras[14]._2=7;

caras[15]._0=14;caras[15]._1=7;caras[15]._2=9;
caras[16]._0=14;caras[16]._1=15;caras[16]._2=9;

caras[17]._0=9;caras[17]._1=15;caras[17]._2=10;

caras[18]._0=11;caras[18]._1=10;caras[18]._2=16;
caras[19]._0=10;caras[19]._1=15;caras[19]._2=16;

caras[20]._0=11;caras[20]._1=12;caras[20]._2=4;
caras[21]._0=16;caras[21]._1=12;caras[21]._2=11;

caras[22]._0=16;caras[22]._1=15;caras[22]._2=12;
caras[23]._0=12;caras[23]._1=15;caras[23]._2=13;

caras[24]._0=0;caras[24]._1=1;caras[24]._2=2;
caras[25]._0=0;caras[25]._1=2;caras[25]._2=3;
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
