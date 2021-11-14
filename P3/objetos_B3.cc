//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include "objetos_B3.h"


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
//**** usando vertex_array ****
glPointSize(grosor);
glColor3f(r,g,b);

glEnableClientState(GL_VERTEX_ARRAY);
glVertexPointer(3,GL_FLOAT,0,&vertices[0]);
glDrawArrays(GL_POINTS,0,vertices.size()); 

/*int i;
glPointSize(grosor);
glColor3f(r,g,b);
glBegin(GL_POINTS);
for (i=0;i<vertices.size();i++){
	glVertex3fv((GLfloat *) &vertices[i]);
	}
glEnd();*/
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
//**** usando vertex_array ****
glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
glLineWidth(grosor);
glColor3f(r,g,b);

glEnableClientState(GL_VERTEX_ARRAY);
glVertexPointer(3,GL_FLOAT,0,&vertices[0]);
glDrawElements(GL_TRIANGLES,caras.size()*3,GL_UNSIGNED_INT,&caras[0]);

/*int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
glLineWidth(grosor);
glColor3f(r,g,b);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();*/
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
	if (i%2==0) glColor3f(r1,g1,b1);
	else glColor3f(r2,g2,b2);
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
//vertices
vertices.resize(8);
vertices[0].x=-tam;vertices[0].y=-tam;vertices[0].z=tam;
vertices[1].x=tam;vertices[1].y=-tam;vertices[1].z=tam;
vertices[2].x=tam;vertices[2].y=tam;vertices[2].z=tam;
vertices[3].x=-tam;vertices[3].y=tam;vertices[3].z=tam;
vertices[4].x=-tam;vertices[4].y=-tam;vertices[4].z=-tam;
vertices[5].x=tam;vertices[5].y=-tam;vertices[5].z=-tam;
vertices[6].x=tam;vertices[6].y=tam;vertices[6].z=-tam;
vertices[7].x=-tam;vertices[7].y=tam;vertices[7].z=-tam;

// triangulos
caras.resize(12);
caras[0]._0=0;caras[0]._1=1;caras[0]._2=3;
caras[1]._0=3;caras[1]._1=1;caras[1]._2=2;
caras[2]._0=1;caras[2]._1=5;caras[2]._2=2;
caras[3]._0=5;caras[3]._1=6;caras[3]._2=2;
caras[4]._0=5;caras[4]._1=4;caras[4]._2=6;
caras[5]._0=4;caras[5]._1=7;caras[5]._2=6;
caras[6]._0=0;caras[6]._1=7;caras[6]._2=4;
caras[7]._0=0;caras[7]._1=3;caras[7]._2=7;
caras[8]._0=3;caras[8]._1=2;caras[8]._2=7;
caras[9]._0=2;caras[9]._1=6;caras[9]._2=7;
caras[10]._0=0;caras[10]._1=1;caras[10]._2=4;
caras[11]._0=1;caras[11]._1=5;caras[11]._2=4;  
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

//if (n_ver<3 || n_car<1){
//	printf("Error %d %d\n",__FILE__,__LINE__);
//	exit(-1);
//	}

vertices.resize(n_ver);
caras.resize(n_car);

_vertex3f ver_aux;
_vertex3i car_aux;

for (int i=0;i<n_ver;i++)
	{ver_aux.x=ver_ply[i*3];
	 ver_aux.y=ver_ply[i*3+1];
	 ver_aux.z=ver_ply[i*3+2];
	 vertices[i]=ver_aux;
	}

for (int i=0;i<n_car;i++)
	{car_aux.x=car_ply[i*3];
	 car_aux.y=car_ply[i*3+1];
	 car_aux.z=car_ply[i*3+2];
	 caras[i]=car_aux;
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


//************************************************************************
// objeto articulado: tanque
//************************************************************************

_chasis::_chasis()
{
// perfil para un cilindro
vector<_vertex3f> perfil;
_vertex3f aux;
aux.x=0.107;aux.y=-0.5;aux.z=0.0;
perfil.push_back(aux);
aux.x=0.107;aux.y=0.5;aux.z=0.0;
perfil.push_back(aux);
rodamiento.parametros(perfil,12,1);
altura=0.22;
};

void _chasis::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
glPushMatrix();
glScalef(1.0,0.22,0.95);
base.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();


glPushMatrix();
glRotatef(90.0,1,0,0); //rota en el eje x 90º
rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(-0.25,0.0,0.0);
glRotatef(90.0,1,0,0);
rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(-0.5,0.0,0.0);
glRotatef(90.0,1,0,0);
rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(0.25,0.0,0.0);
glRotatef(90.0,1,0,0);
rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(0.5,0.0,0.0); //mueve distancia (0.5 | 0 | 0)
glRotatef(90.0,1,0,0);
rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();
}

//************************************************************************

_torreta::_torreta()
{
altura=0.18;
anchura=0.65;
};

void _torreta::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
glPushMatrix();
glScalef(0.65,0.18,0.6);
base.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(-0.325,0,0);
glRotatef(90.0,0,0,1);
glScalef(0.18,0.16,0.6);
parte_trasera.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();
}

//************************************************************************

_tubo::_tubo()
{
// perfil para un cilindro
vector<_vertex3f> perfil;
_vertex3f aux;
aux.x=0.04;aux.y=-0.4;aux.z=0.0;
perfil.push_back(aux);
aux.x=0.04;aux.y=0.4;aux.z=0.0;
perfil.push_back(aux);
tubo_abierto.parametros(perfil,12,0);
};

void _tubo::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{

glPushMatrix();
glTranslatef(0.4,0,0);
glRotatef(90.0,0,0,1);
tubo_abierto.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();
}


//************************************************************************

_tanque::_tanque()
{
giro_tubo=2.0;
giro_torreta=0.0;
giro_tubo_min=-9;
giro_tubo_max=20;
};

void _tanque::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
glPushMatrix();
chasis.draw(modo, r1, g1, b1, r2, g2, b2, grosor);

//las transformaciones se hacen de abajo a arriba
//las clases torreta, tubo... están sobre el eje para poder girarlos
//luego se giran y se ponen bien en la puta clase tanque de mierda

glRotatef(giro_torreta,0,1,0);
glPushMatrix();
glTranslatef(0.0,(chasis.altura+torreta.altura)/2.0,0.0);
torreta.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(torreta.anchura/2.0,(chasis.altura+torreta.altura)/2.0,0.0);
glRotatef(giro_tubo,0,0,1);
tubo.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();
glPopMatrix();

};


//************************************************************************
// objeto articulado: camion de bomberos
//************************************************************************
_ruedas::_ruedas()
{
// perfil para un cilindro

rueda = _cilindro(0.235, 0.165, 15, 1);

};

void _ruedas::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{

glPushMatrix();
glTranslatef(0.0,0.0,-0.5);
glRotatef(90.0,1,0,0);
rueda.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(0.0,0.0,0.5); //mueve distancia (0.5 | 0 | 0)
glRotatef(90.0,1,0,0);
rueda.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(0.0,0.0,-0.575);
glRotatef(90.0,1,0,0);
glScalef(0.5,0.1,0.5);
rueda.draw(modo, 0.4,0.4,0.4, 0.2,0.2,0.2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(0.0,0.0,0.575); //mueve distancia (0.5 | 0 | 0)
glRotatef(90.0,1,0,0);
glScalef(0.5,0.1,0.5);
rueda.draw(modo, 0.4,0.4,0.4, 0.2,0.2,0.2, grosor);
glPopMatrix();

}
//************************************************************************

_carroceria::_carroceria()
{
// perfil para un cilindro
carcasa = _cubo();
foco = _esfera();
sirena = _cilindro();
};

void _carroceria::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{

//cuadro rojo
glPushMatrix();
glTranslatef(1.4,0.6,0.0);
glScalef(3.6,0.8,1);
carcasa.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(2.8,1.1,0.0);
glScalef(0.9,0.2,1);
carcasa.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();


//Ventanas

glPushMatrix();
glTranslatef(2.8,0.8,0.501);
glScalef(0.5,0.3,0.01);
carcasa.draw(modo, 0.2, 0.2, 0.2, 0.5, 0.5, 0.5, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(2.8,0.8,-0.501);
glScalef(0.5,0.3,0.01);
carcasa.draw(modo, 0.2, 0.2, 0.2, 0.5, 0.5, 0.5, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(3.21,0.8,0.0);
glScalef(0.01,0.3,0.8);
carcasa.draw(modo, 0.2, 0.2, 0.2, 0.5, 0.5, 0.5, grosor);
glPopMatrix();

//focos
glPushMatrix();
glTranslatef(3.21,0.4,0.38);
glScalef(0.07,0.07,0.07);
foco.draw(modo, 1, 0.9882, 0.2745, 0.8588, 0.4627, 0.0941, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(3.21,0.4,-0.38);
glScalef(0.07,0.07,0.07);
foco.draw(modo, 1, 0.9882, 0.2745, 0.8588, 0.4627, 0.0941, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(-0.4,0.3,0.0);
glScalef(0.01,0.15,0.98);
carcasa.draw(modo, 0.55, 0.55, 0.55, 0.7, 0.7, 0.7, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(-0.41,0.3,0.3);
glScalef(0.01,0.07,0.15);
carcasa.draw(modo, 0.803,0.043,0.043,0.819,0.3686,0.3686, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(-0.41,0.3,0.41);
glScalef(0.01,0.07,0.07);
carcasa.draw(modo, 1, 0.9882, 0.2745, 0.8588, 0.4627, 0.0941, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(-0.41,0.3,-0.3);
glScalef(0.01,0.07,0.15);
carcasa.draw(modo, 0.803,0.043,0.043,0.819,0.3686,0.3686, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(-0.41,0.3,-0.41);
glScalef(0.01,0.07,0.07);
carcasa.draw(modo, 1, 0.9882, 0.2745, 0.8588, 0.4627, 0.0941, grosor);
glPopMatrix();

//matriculas
glPushMatrix();
glTranslatef(-0.41,0.3,0.0);
glScalef(0.01,0.15,0.4);
carcasa.draw(modo, 0.9, 0.9, 0.9, 0.8, 0.8, 0.8, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(-0.415,0.3,-0.15);
glScalef(0.01,0.15,0.1);
carcasa.draw(modo, 0.0, 0.2902, 0.8353, 0.0, 0.0, 0.3333, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(3.2,0.3,0.0);
glScalef(0.01,0.15,0.4);
carcasa.draw(modo, 0.9, 0.9, 0.9, 0.8, 0.8, 0.8, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(3.21,0.3,0.15);
glScalef(0.01,0.15,0.1);
carcasa.draw(modo, 0.0, 0.2902, 0.8353, 0.0, 0.0, 0.3333, grosor);
glPopMatrix();

//Sirenas
glPushMatrix();
glTranslatef(3.18,1.17,0.24);
glScalef(0.1,0.1,0.1);
sirena.draw(modo, 0.0, 0.5020, 0.8745, 0.0, 0.2902, 0.8353, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(3.18,1.17,-0.24);
glScalef(0.1,0.1,0.1);
sirena.draw(modo, 0.0, 0.5020, 0.8745, 0.0, 0.2902, 0.8353, grosor);
glPopMatrix();

//Puertas
glPushMatrix();
glTranslatef(1.2,0.7,0.501);
glScalef(0.6,0.34,0.01);
carcasa.draw(modo, 0.6, 0.6, 0.6, 0.8, 0.8, 0.8, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(2.8,0.8,-0.501);
glScalef(0.5,0.3,0.01);
carcasa.draw(modo, 0.6, 0.6, 0.6, 0.8, 0.8, 0.8, grosor);
glPopMatrix();
}
//************************************************************************

_plataforma::_plataforma()
{
// perfil para un cilindro
base = _cubo();
lateral1 = _cubo();
lateral2 = _cubo();
};

void _plataforma::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{

glPushMatrix();
glScalef(0.8,0.12,0.8);
base.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(0.0,0.31,0.37);
glScalef(0.6,0.5,0.04);
lateral1.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(0.0,0.31,-0.37);
glScalef(0.6,0.5,0.04);
lateral2.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();


}

//************************************************************************

_escaleragrande::_escaleragrande()
{
// perfil para un cilindro
barra_lateral = _cubo();
barra_mano = _cubo();
};

void _escaleragrande::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{

glPushMatrix();
glTranslated(0.025, 0.0, 0.0);
glScalef(0.05,0.05,0.59);
barra_mano.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslated(0.225, 0.0, 0.0);
glScalef(0.05,0.05,0.59);
barra_mano.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslated(0.425, 0.0, 0.0);
glScalef(0.05,0.05,0.59);
barra_mano.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslated(0.625, 0.0, 0.0);
glScalef(0.05,0.05,0.59);
barra_mano.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslated(0.825, 0.0, 0.0);
glScalef(0.05,0.05,0.59);
barra_mano.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslated(1.025, 0.0, 0.0);
glScalef(0.05,0.05,0.59);
barra_mano.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslated(1.225, 0.0, 0.0);
glScalef(0.05,0.05,0.59);
barra_mano.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslated(1.425, 0.0, 0.0);
glScalef(0.05,0.05,0.59);
barra_mano.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslated(1.625, 0.0, 0.0);
glScalef(0.05,0.05,0.59);
barra_mano.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslated(1.825, 0.0, 0.0);
glScalef(0.05,0.05,0.59);
barra_mano.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslated(2.025, 0.0, 0.0);
glScalef(0.05,0.05,0.59);
barra_mano.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslated(2.225, 0.0, 0.0);
glScalef(0.05,0.05,0.59);
barra_mano.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslated(2.425, 0.0, 0.0);
glScalef(0.05,0.05,0.59);
barra_mano.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(1.25,0,0.32);
glScalef(2.5,0.06,0.06);
barra_lateral.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(1.25,0,-0.32);
glScalef(2.5,0.06,0.06);
barra_lateral.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

}


//************************************************************************

_escalerachica::_escalerachica()
{
// perfil para un cilindro
barra_lateral = _cubo();
barra_mano = _cubo();
};

void _escalerachica::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{

glPushMatrix();
glTranslated(0.025, 0.0, 0.0);
glScalef(0.04,0.04,0.49);
barra_mano.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslated(0.225, 0.0, 0.0);
glScalef(0.04,0.04,0.49);
barra_mano.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslated(0.425, 0.0, 0.0);
glScalef(0.04,0.04,0.49);
barra_mano.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslated(0.625, 0.0, 0.0);
glScalef(0.04,0.04,0.49);
barra_mano.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslated(0.825, 0.0, 0.0);
glScalef(0.04,0.04,0.49);
barra_mano.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslated(1.025, 0.0, 0.0);
glScalef(0.04,0.04,0.49);
barra_mano.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslated(1.225, 0.0, 0.0);
glScalef(0.04,0.04,0.49);
barra_mano.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslated(1.425, 0.0, 0.0);
glScalef(0.04,0.04,0.49);
barra_mano.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslated(1.625, 0.0, 0.0);
glScalef(0.04,0.04,0.49);
barra_mano.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslated(1.825, 0.0, 0.0);
glScalef(0.04,0.04,0.49);
barra_mano.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslated(2.025, 0.0, 0.0);
glScalef(0.04,0.04,0.49);
barra_mano.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslated(2.225, 0.0, 0.0);
glScalef(0.04,0.04,0.49);
barra_mano.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(1.25,0,0.25);
glScalef(2.5,0.05,0.05);
barra_lateral.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(1.25,0,-0.25);
glScalef(2.5,0.05,0.05);
barra_lateral.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

}



//************************************************************************

_cabina::_cabina()
{
barra = _cubo();
};

void _cabina::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{

glPushMatrix();
glTranslated(0.025, 0.0, 0.0);
glScalef(0.05,0.05,0.5);
barra.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslated(0.575, 0.0, 0.0);
glScalef(0.05,0.05,0.5);
barra.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslated(0.300, 0.0, -0.250);
glRotatef(90,0,1,0);
glTranslated(0.025, 0.0, 0.0);
glScalef(0.05,0.05,0.6);
barra.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslated(0.300, 0.0, 0.250);
glRotatef(-90,0,1,0);
glTranslated(0.025, 0.0, 0.0);
glScalef(0.05,0.05,0.6);
barra.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslated(0.0,0.025,-0.275);
glRotatef(-90,1,0,0);
glTranslated(0.025, 0.0, 0.3);
glScalef(0.05,0.05,0.6);
barra.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslated(0.0,0.025,0.275);
glRotatef(-90,1,0,0);
glTranslated(0.025, 0.0, 0.3);
glScalef(0.05,0.05,0.6);
barra.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslated(0.55,0.025,-0.275);
glRotatef(-90,1,0,0);
glTranslated(0.025, 0.0, 0.3);
glScalef(0.05,0.05,0.6);
barra.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslated(0.55,0.025,0.275);
glRotatef(-90,1,0,0);
glTranslated(0.025, 0.0, 0.3);
glScalef(0.05,0.05,0.6);
barra.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();
}



//************************************************************************

_elevador::_elevador()
{
// perfil para un cilindro
barra = _cubo();
};

void _elevador::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{

glPushMatrix();
glTranslated(0.25, 0.0, 0.0);
glScalef(0.50,0.05,0.5);
barra.draw(modo, 0.8,0.8,0.8, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslated(0.0,0.025,0);
glRotatef(-90,1,0,0);
glTranslated(0.02, 0.0, 0.2);
glScalef(0.04,0.5,0.40);
barra.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();


glPushMatrix();
glTranslated(0.23,0.025,-0.23);
glRotatef(-90,1,0,0);
glTranslated(0.02, 0.0, 0.2);
glScalef(0.42,0.04,0.40);
barra.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslated(0.46,0.025,0);
glRotatef(-90,1,0,0);
glTranslated(0.02, 0.0, 0.2);
glScalef(0.04,0.5,0.40);
barra.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();


glPushMatrix();
glTranslated(0.23,0.025,0.23);
glRotatef(-90,1,0,0);
glTranslated(0.02, 0.0, 0.2);
glScalef(0.42,0.04,0.40);
barra.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();



glPushMatrix();
glTranslated(0.02, 0.44, 0.0);
glScalef(0.04,0.04,0.5);
barra.draw(modo,0.3, 0.3,0.3, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslated(0.48, 0.44, 0.0);
glScalef(0.04,0.04,0.5);
barra.draw(modo,0.3, 0.3,0.3, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslated(0.25, 0.44, 0.23);
glRotatef(90,0,1,0);
glScalef(0.04,0.04,0.42);
barra.draw(modo,0.3, 0.3,0.3, r2, g2, b2, grosor);
glPopMatrix();


glPushMatrix();
glTranslated(0.25, 0.44, -0.23);
glRotatef(90,0,1,0);
glScalef(0.04,0.04,0.5);
barra.draw(modo,0.3, 0.3,0.3, r2, g2, b2, grosor);
glPopMatrix();

//base de la pistola
glPushMatrix();
glTranslated(0.5,0.15,0);
glRotatef(-90,1,0,0);
glTranslated(0.02, 0.0, 0.2);
glScalef(0.04,0.24,0.24);
barra.draw(modo, 0.87,0.6235,0.1686, r2, g2, b2, grosor);
glPopMatrix();
}

//************************************************************************

_pistola::_pistola()
{
pistola = _cilindro(0.06,0.4,15,1);
};

void _pistola::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{

glPushMatrix();
glTranslatef(0.2,0,0);
glRotatef(90,0,0,1);
pistola.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();
}


//************************************************************************

_agua::_agua()
{
gota = _esfera();
};

void _agua::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{


glPushMatrix();
glRotatef(90,0,1,0);
glScalef(0.04,0.04,0.04);
gota.draw(modo, r1, g1, b1, r2,g2,b2, grosor);
glPopMatrix();
}

//************************************************************************

_camionbomberos::_camionbomberos()
{

};

void _camionbomberos::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{


glPushMatrix();
glTranslatef(movimiento_camion, 0, 0);
glTranslatef(0.0,0.2,0.0);
glRotatef(giro_ruedas,0,0,1);
ruedas.draw(modo, 0, 0, 0, 0.7, 0.7, 0.7, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(movimiento_camion, 0, 0);
glTranslatef(1.9,0.2,0.0);
glRotatef(giro_ruedas,0,0,1);
ruedas.draw(modo, 0, 0, 0, 0.7, 0.7, 0.7, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(movimiento_camion, 0, 0);
glTranslatef(2.7,0.2,0.0);
glRotatef(giro_ruedas,0,0,1);
ruedas.draw(modo, 0, 0, 0, 0.7, 0.7, 0.7, grosor);
glPopMatrix();
//las transformaciones se hacen de abajo a arriba
//las clases torreta, tubo... están sobre el eje para poder girarlos
//luego se giran y se ponen bien en la puta clase tanque de mierda

glPushMatrix();
glTranslatef(movimiento_camion, 0, 0);
carroceria.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(movimiento_camion, 0, 0);
glTranslatef(0.0,1.05,0.0);
glRotatef(giro_plataforma,0,1,0);
plataforma.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(movimiento_camion, 0, 0);
glTranslatef(0.0,1.30,0.0);
glRotatef(giro_plataforma,0,1,0);
glRotatef(giro_escalera,0,0,1);
escaleragrande.draw(modo, 0.75, 0.75, 0.75, 0.8, 0.8, 0.1, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(movimiento_camion, 0, 0);
glTranslatef(0.0,1.30,0.0);
glRotatef(giro_plataforma,0,1,0);
glRotatef(giro_escalera,0,0,1);
glTranslatef(translacion_escalera,0,0);
escalerachica.draw(modo, 0.3, 0.5, 0.7, 0.1, 0.1, 0.5, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(movimiento_camion, 0, 0);
glTranslatef(0.0,1.30,0.0);
glRotatef(giro_plataforma,0,1,0);
glRotatef(giro_escalera,0,0,1);
glTranslatef(translacion_escalera,0,0);
glTranslatef(2.5,0,0);
glRotatef(-giro_escalera,0,0,1);
cabina.draw(modo, 0.1, 0.3, 0.1, 0.1, 0.1, 0.5, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(movimiento_camion, 0, 0);
glTranslatef(0.0,1.30,0.0);
glRotatef(giro_plataforma,0,1,0);
glRotatef(giro_escalera,0,0,1);
glTranslatef(translacion_escalera,0,0);
glTranslatef(2.55,0,0);
glRotatef(-giro_escalera,0,0,1);
glTranslatef(0,levantamiento,0);
elevador.draw(modo, 0.45,0.45,0.45,0.8,0.8,0.8, grosor);
glPopMatrix();


glPushMatrix();
glTranslatef(movimiento_camion, 0, 0);
glTranslatef(0.0,1.30,0.0);
glRotatef(giro_plataforma,0,1,0);
glTranslatef(0.4,+0.35,0);
glRotatef(giro_escalera,0,0,1);
glTranslatef(translacion_escalera,0,0);
glTranslatef(2.55,0.00,0);
glRotatef(-giro_escalera,0,0,1);
glTranslatef(0,levantamiento,0);
glRotatef(giro_pistola_vertical, 0, 0 ,1);
glRotatef(giro_pistola_horizontal, 0, 1 ,0);
pistola.draw(modo, 0.27,0.6235,0.5686, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(movimiento_camion, 0, 0);
glTranslatef(0.0,1.30,0.0);
glRotatef(giro_plataforma,0,1,0);
glTranslatef(0.45,+0.35,0);
glRotatef(giro_escalera,0,0,1);
glTranslatef(translacion_escalera,0,0);
glTranslatef(2.55,0,0);
glRotatef(-giro_escalera,0,0,1);
glTranslatef(0,levantamiento,0);
glRotatef(giro_pistola_vertical, 0, 0 ,1);
glRotatef(giro_pistola_horizontal, 0, 1 ,0);
glTranslatef(movimiento_agua, 0, 0);
agua.draw(modo, 0.0, 0.81, 1, 0.34, 0.1, 0.1, grosor);
glPopMatrix();
};
