//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include "objetos_B5.h"

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
	glColor3f(r, g, b);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
	glDrawArrays(GL_POINTS, 0, vertices.size());

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
	b_normales_caras = false;
	b_normales_vertices = false;
	difusa = _vertex4f(0.90, 0.0, 0.0, 1.0);
	ambiente = _vertex4f(1, 0.2, 0.2, 1.0);
	especular = _vertex4f(0.5, 0.5, 0.5, 1.0);
	brillo = 50;
	int c = 100;
}

//*************************************************************************
// dibujar en modo arista
//*************************************************************************

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor)
{
	//**** usando vertex_array ****
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(grosor);
	glColor3f(r, g, b);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
	glDrawElements(GL_TRIANGLES, caras.size() * 3, GL_UNSIGNED_INT, &caras[0]);

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

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3f(r, g, b);
	glBegin(GL_TRIANGLES);
	for (i = 0; i < caras.size(); i++)
	{
		glVertex3fv((GLfloat *)&vertices[caras[i]._0]);
		glVertex3fv((GLfloat *)&vertices[caras[i]._1]);
		glVertex3fv((GLfloat *)&vertices[caras[i]._2]);
	}
	glEnd();
}

//*************************************************************************
// dibujar en modo sólido con apariencia de ajedrez
//*************************************************************************

void _triangulos3D::draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2)
{
	int i;
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);
	for (i = 0; i < caras.size(); i++)
	{
		if (i % 2 == 0)
			glColor3f(r1, g1, b1);
		else
			glColor3f(r2, g2, b2);
		glVertex3fv((GLfloat *)&vertices[caras[i]._0]);
		glVertex3fv((GLfloat *)&vertices[caras[i]._1]);
		glVertex3fv((GLfloat *)&vertices[caras[i]._2]);
	}
	glEnd();
}

//*************************************************************************
// dibujar en modo seleccion
//*************************************************************************

void _triangulos3D::draw_seleccion(int r, int g, int b)
{
	int i;
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3ub(r, g, b);
	glBegin(GL_TRIANGLES);
	for (i = 0; i < caras.size(); i++)
	{
		glVertex3fv((GLfloat *)&vertices[caras[i]._0]);
		glVertex3fv((GLfloat *)&vertices[caras[i]._1]);
		glVertex3fv((GLfloat *)&vertices[caras[i]._2]);
	}
	glEnd();
}

/*
void _cubo::seleccion(){
	int c;
	c = color_selec[0][0];
	glPushMatrix();
	draw(SELECT, c, c, c, c, c, c, 1, VACIO);
	glPopMatrix();
}
*/

//*************************************************************************
// dibujar con distintos modos
//*************************************************************************

void _triangulos3D::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, _material mate)
{
	switch (modo)
	{
	case POINTS:
		draw_puntos(r1, g1, b1, grosor);
		break;
	case EDGES:
		draw_aristas(r1, g1, b1, grosor);
		break;
	case SOLID_CHESS:
		draw_solido_ajedrez(r1, g1, b1, r2, g2, b2);
		break;
	case SOLID:
		draw_solido(r1, g1, b1);
		break;
	case SOLID_ILLUMINATED_FLAT:
		draw_iluminacion_plana(mate);
		break;
	case SOLID_ILLUMINATED_GOURAUD:
		draw_iluminacion_suave(mate);
		break;
	case SELECT:
		draw_seleccion(r1, g1, b1);
		break;
	}
}

//*************************************************************************
// dibujar en modo iluminación plana
//*************************************************************************

void _triangulos3D::draw_iluminacion_plana(_material mate)
{
	int i;

	if (b_normales_caras == false)
		calcular_normales_caras();

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glEnable(GL_LIGHTING);
	glShadeModel(GL_FLAT);
	glEnable(GL_NORMALIZE); //normalizar en caso de que se escale -> normalizacion de los vectores normales

	//Establecemos material
	if (mate != VACIO)
	{
		material = _Material(mate);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material.difusa);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material.ambiente);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material.especular);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material.brillo);
	}
	else
	{
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, (GLfloat *)&difusa);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, (GLfloat *)&ambiente);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat *)&especular);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, brillo);
	}
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);

	for (i = 0; i < caras.size(); i++)
	{
		glNormal3fv((GLfloat *)&normales_caras[i]);
		glVertex3fv((GLfloat *)&vertices[caras[i]._0]);
		glVertex3fv((GLfloat *)&vertices[caras[i]._1]);
		glVertex3fv((GLfloat *)&vertices[caras[i]._2]);
	}
	glEnd();

	glDisable(GL_LIGHTING);
}

//*************************************************************************
// dibujar en modo iluminación suave
//*************************************************************************

void _triangulos3D::draw_iluminacion_suave(_material mate)
{

	if (!b_normales_vertices)
		calcular_normales_vertices();
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);

	//Establecemos material
	if (mate != VACIO)
	{
		material = _Material(mate);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material.difusa);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material.ambiente);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material.especular);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material.brillo);
	}
	else
	{
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, (GLfloat *)&ambiente);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, (GLfloat *)&difusa);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat *)&especular);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, brillo);
	}

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);

	for (int i = 0; i < caras.size(); i++)
	{
		glNormal3fv((GLfloat *)&normales_vertices[caras[i]._0]);
		glVertex3fv((GLfloat *)&vertices[caras[i]._0]);
		glNormal3fv((GLfloat *)&normales_vertices[caras[i]._1]);
		glVertex3fv((GLfloat *)&vertices[caras[i]._1]);
		glNormal3fv((GLfloat *)&normales_vertices[caras[i]._2]);
		glVertex3fv((GLfloat *)&vertices[caras[i]._2]);
	}

	glEnd();

	glDisable(GL_LIGHTING);
}

//*************************************************************************
// calcular_normales_caras
//*************************************************************************

void _triangulos3D::calcular_normales_caras()
{
	_vertex3f a1, a2, n;
	normales_caras.resize(caras.size());

	for (int i = 0; i < caras.size(); i++)
	{
		// obtener dos vectores en el triángulo y calcular el producto vectorial
		a1 = vertices[caras[i]._1] - vertices[caras[i]._0];
		a2 = vertices[caras[i]._2] - vertices[caras[i]._0];
		n = a1.cross_product(a2);
		// modulo
		float m = sqrt(n.x * n.x + n.y * n.y + n.z * n.z);
		// normalización
		normales_caras[i] = _vertex3f(n.x / m, n.y / m, n.z / m);
	}

	b_normales_caras = true;
}

//*************************************************************************
// calcular_normales_vertices
//*************************************************************************

void _triangulos3D::calcular_normales_vertices()
{

	if (!b_normales_caras)
		calcular_normales_caras();

	normales_vertices.resize(vertices.size());
	for (int i = 0; i < vertices.size(); ++i)
		normales_vertices[i] = _vertex3f(0.0, 0.0, 0.0);

	for (int i = 0; i < caras.size(); ++i)
	{
		normales_vertices[caras[i]._0] += normales_caras[i];
		normales_vertices[caras[i]._1] += normales_caras[i];
		normales_vertices[caras[i]._2] += normales_caras[i];
	}

	for (int i = 0; i < vertices.size(); ++i)
		normales_vertices[i] = normales_vertices[i].normalize();

	b_normales_vertices = true;
}

//*************************************************************************
// calcular_normales_vertices (esfera)
//*************************************************************************

void _esfera::calcular_normales_vertices()
{
	_vertex3f a1, a2, n;
	normales_vertices.resize(vertices.size());
	for (int i = 0; i < vertices.size(); ++i)
	{
		a1 = vertices[caras[i]._0];
		// modulo
		float m = sqrt(a1.x * a1.x + a1.y * a1.y + a1.z * a1.z);
		// normalización
		normales_vertices[i] = _vertex3f(a1.x / m, a1.y / m, a1.z / m);
	}

	//normales_vertices[i] = normales_vertices[i].normalize();

	b_normales_vertices = true;
}

//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam)
{
	//vertices
	vertices.resize(8);
	vertices[0].x = -tam;
	vertices[0].y = -tam;
	vertices[0].z = tam;
	vertices[1].x = tam;
	vertices[1].y = -tam;
	vertices[1].z = tam;
	vertices[2].x = tam;
	vertices[2].y = -tam;
	vertices[2].z = -tam;
	vertices[3].x = -tam;
	vertices[3].y = -tam;
	vertices[3].z = -tam;
	vertices[4].x = -tam;
	vertices[4].y = tam;
	vertices[4].z = tam;
	vertices[5].x = tam;
	vertices[5].y = tam;
	vertices[5].z = tam;
	vertices[6].x = tam;
	vertices[6].y = tam;
	vertices[6].z = -tam;
	vertices[7].x = -tam;
	vertices[7].y = tam;
	vertices[7].z = -tam;

	// triangulos
	caras.resize(12);
	caras[0]._0 = 0;
	caras[0]._1 = 2;
	caras[0]._2 = 1;
	caras[1]._0 = 0;
	caras[1]._1 = 3;
	caras[1]._2 = 2;
	caras[2]._0 = 0;
	caras[2]._1 = 1;
	caras[2]._2 = 4;
	caras[3]._0 = 1;
	caras[3]._1 = 5;
	caras[3]._2 = 4;
	caras[4]._0 = 1;
	caras[4]._1 = 2;
	caras[4]._2 = 5;
	caras[5]._0 = 2;
	caras[5]._1 = 6;
	caras[5]._2 = 5;
	caras[6]._0 = 3;
	caras[6]._1 = 6;
	caras[6]._2 = 2;
	caras[7]._0 = 3;
	caras[7]._1 = 7;
	caras[7]._2 = 6;
	caras[8]._0 = 0;
	caras[8]._1 = 7;
	caras[8]._2 = 3;
	caras[9]._0 = 0;
	caras[9]._1 = 4;
	caras[9]._2 = 7;
	caras[10]._0 = 5;
	caras[10]._1 = 7;
	caras[10]._2 = 4;
	caras[11]._0 = 5;
	caras[11]._1 = 6;
	caras[11]._2 = 7;
}

//*************************************************************************
// clase piramide
//*************************************************************************

_piramide::_piramide(float tam, float al)
{

	//vertices
	vertices.resize(5);
	vertices[0].x = -tam;
	vertices[0].y = 0;
	vertices[0].z = tam;
	vertices[1].x = tam;
	vertices[1].y = 0;
	vertices[1].z = tam;
	vertices[2].x = tam;
	vertices[2].y = 0;
	vertices[2].z = -tam;
	vertices[3].x = -tam;
	vertices[3].y = 0;
	vertices[3].z = -tam;
	vertices[4].x = 0;
	vertices[4].y = al;
	vertices[4].z = 0;

	caras.resize(6);
	caras[0]._0 = 0;
	caras[0]._1 = 1;
	caras[0]._2 = 4;
	caras[1]._0 = 1;
	caras[1]._1 = 2;
	caras[1]._2 = 4;
	caras[2]._0 = 2;
	caras[2]._1 = 3;
	caras[2]._2 = 4;
	caras[3]._0 = 3;
	caras[3]._1 = 0;
	caras[3]._2 = 4;
	caras[4]._0 = 3;
	caras[4]._1 = 1;
	caras[4]._2 = 0;
	caras[5]._0 = 3;
	caras[5]._1 = 2;
	caras[5]._2 = 1;
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
	int n_ver, n_car;

	vector<float> ver_ply;
	vector<int> car_ply;

	_file_ply::read(archivo, ver_ply, car_ply);

	n_ver = ver_ply.size() / 3;
	n_car = car_ply.size() / 3;

	printf("Number of vertices=%d\nNumber of faces=%d\n", n_ver, n_car);

	//if (n_ver<3 || n_car<1){
	//	printf("Error %d %d\n",__FILE__,__LINE__);
	//	exit(-1);
	//	}

	vertices.resize(n_ver);
	caras.resize(n_car);

	_vertex3f ver_aux;
	_vertex3i car_aux;

	for (int i = 0; i < n_ver; i++)
	{
		ver_aux.x = ver_ply[i * 3];
		ver_aux.y = ver_ply[i * 3 + 1];
		ver_aux.z = ver_ply[i * 3 + 2];
		vertices[i] = ver_aux;
	}

	for (int i = 0; i < n_car; i++)
	{
		car_aux.x = car_ply[i * 3];
		car_aux.y = car_ply[i * 3 + 1];
		car_aux.z = car_ply[i * 3 + 2];
		caras[i] = car_aux;
	}

	return (0);
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
	int i, j;
	_vertex3f vertice_aux;
	_vertex3i cara_aux;
	int num_aux, num_auxB;

	//creamos un perfil nuevo
	vector<_vertex3f> perfilnuevo;

	//rotamos el vertice segun el eje

	if (eje == 0)
	{
		for (int i = 0; i < perfil.size(); i++)
		{
			int aux = perfil[i].z;
			perfil[i].z = perfil[i].x;
			perfil[i].x = perfil[i].y;
			perfil[i].y = aux;
		}
	}
	else if (eje == 2)
	{
		for (int i = 0; i < perfil.size(); i++)
		{
			int aux = perfil[i].z;
			perfil[i].z = perfil[i].y;
			perfil[i].y = perfil[i].x;
			perfil[i].x = aux;
		}
	}

	////// tratamiento de los vértices //////
	switch (eje)
	{
	case 0:

		//metemos en el nuevo perfil los vértices del perfil que NO están en el eje y
		for (int i = 0; i < perfil.size(); i++)
		{
			if (fabs(perfil[i].z) > 0)
				perfilnuevo.push_back(perfil[i]);
		}
		num_aux = perfil.size();
		num_auxB = perfilnuevo.size(); //numero de vertices del perfil sin los del eje y
		//rotamos los vértices
		for (j = 0; j < num; j++)
		{
			for (i = 0; i < num_auxB; i++)
			{
				vertice_aux.x = perfilnuevo[i].x;
				vertice_aux.z = -perfilnuevo[i].y * sin(2.0 * M_PI * j / (1.0 * num)) +
								perfilnuevo[i].z * cos(2.0 * M_PI * j / (1.0 * num));
				vertice_aux.y = perfilnuevo[i].y * cos(2.0 * M_PI * j / (1.0 * num)) +
								perfilnuevo[i].z * sin(2.0 * M_PI * j / (1.0 * num));
				vertices.push_back(vertice_aux);
			}
		}

		break;
	case 1:
		//metemos en el nuevo perfil los vértices del perfil que NO están en el eje y
		for (int i = 0; i < perfil.size(); i++)
		{
			if (fabs(perfil[i].x) > 0)
				perfilnuevo.push_back(perfil[i]);
		}
		num_aux = perfil.size();
		num_auxB = perfilnuevo.size(); //numero de vertices del perfil sin los del eje y

		//rotamos los vértices
		for (j = 0; j < num; j++)
		{
			for (i = 0; i < num_auxB; i++)
			{
				vertice_aux.x = perfilnuevo[i].x * cos(2.0 * M_PI * j / (1.0 * num)) +
								perfilnuevo[i].z * sin(2.0 * M_PI * j / (1.0 * num));
				vertice_aux.z = -perfilnuevo[i].x * sin(2.0 * M_PI * j / (1.0 * num)) +
								perfilnuevo[i].z * cos(2.0 * M_PI * j / (1.0 * num));
				vertice_aux.y = perfilnuevo[i].y;
				vertices.push_back(vertice_aux);
			}
		}

		break;
	case 2:
		//metemos en el nuevo perfil los vértices del perfil que NO están en el eje y
		for (int i = 0; i < perfil.size(); i++)
		{
			if (fabs(perfil[i].y) > 0)
				perfilnuevo.push_back(perfil[i]);
		}
		num_aux = perfil.size();
		num_auxB = perfilnuevo.size(); //numero de vertices del perfil sin los del eje y

		//rotamos los vértices
		for (j = 0; j < num; j++)
		{
			for (i = 0; i < num_auxB; i++)
			{
				vertice_aux.x = perfilnuevo[i].x * cos(2.0 * M_PI * j / (1.0 * num)) +
								perfilnuevo[i].y * sin(2.0 * M_PI * j / (1.0 * num));
				vertice_aux.z = perfilnuevo[i].z;
				vertice_aux.y = -perfilnuevo[i].x * sin(2.0 * M_PI * j / (1.0 * num)) +
								perfilnuevo[i].y * cos(2.0 * M_PI * j / (1.0 * num));
				vertices.push_back(vertice_aux);
			}
		}
		break;
	}

	////// Tratamiento de las tapas //////
	// tapa inferior
	switch (eje)
	{
	case 0:
		vertice_aux.x = perfil[0].x;
		vertice_aux.y = 0.0;
		vertice_aux.z = 0.0;
		vertices.push_back(vertice_aux);
		cara_aux._0 = vertices.size() - 1;
		for (int i = 0; i < num; i++)
		{
			cara_aux._2 = ((i + 1) % num) * num_auxB;
			cara_aux._1 = i * num_auxB;
			caras.push_back(cara_aux);
		}
		break;
	case 1:
		vertice_aux.x = 0.0;
		vertice_aux.y = perfil[0].y;
		vertice_aux.z = 0.0;
		vertices.push_back(vertice_aux);
		cara_aux._0 = vertices.size() - 1;
		for (int i = 0; i < num; i++)
		{
			cara_aux._1 = ((i + 1) % num) * num_auxB;
			cara_aux._2 = i * num_auxB;
			caras.push_back(cara_aux);
		}
		break;
	case 2:
		vertice_aux.x = 0.0;
		vertice_aux.y = 0.0;
		vertice_aux.z = perfil[0].z;
		vertices.push_back(vertice_aux);
		cara_aux._0 = vertices.size() - 1;
		for (int i = 0; i < num; i++)
		{
			cara_aux._2 = ((i + 1) % num) * num_auxB;
			cara_aux._1 = i * num_auxB;
			caras.push_back(cara_aux);
		}
		break;
	}

	// tapa superior
	switch (eje)
	{
	case 0:
		vertice_aux.x = perfil[perfil.size() - 1].x;
		vertice_aux.y = 0.0;
		vertice_aux.z = 0.0;
		vertices.push_back(vertice_aux);
		cara_aux._0 = vertices.size() - 1;
		for (int i = 0; i < num; i++)
		{
			cara_aux._1 = ((i + 1) % num) * num_auxB + num_auxB - 1;
			cara_aux._2 = (i + 1) * num_auxB - 1;

			caras.push_back(cara_aux);
		}
		break;
	case 1:
		vertice_aux.x = 0.0;
		vertice_aux.y = perfil[perfil.size() - 1].y;
		vertice_aux.z = 0.0;
		vertices.push_back(vertice_aux);
		cara_aux._0 = vertices.size() - 1;
		for (int i = 0; i < num; i++)
		{
			cara_aux._2 = ((i + 1) % num) * num_auxB + num_auxB - 1;
			cara_aux._1 = (i + 1) * num_auxB - 1;

			caras.push_back(cara_aux);
		}
		break;
	case 2:
		vertice_aux.x = 0.0;
		vertice_aux.y = 0.0;
		vertice_aux.z = perfil[perfil.size() - 1].z;
		vertices.push_back(vertice_aux);
		cara_aux._0 = vertices.size() - 1;
		for (int i = 0; i < num; i++)
		{
			cara_aux._1 = ((i + 1) % num) * num_auxB + num_auxB - 1;
			cara_aux._2 = (i + 1) * num_auxB - 1;

			caras.push_back(cara_aux);
		}
		break;
	}

	////// tratamiento de las caras //////
	switch (eje)
	{
	case 0:
		for (int i = 0; i < num; ++i)
		{
			for (int j = 0; j < num_auxB - 1; ++j)
			{
				cara_aux._1 = i * num_auxB + j;					  //1
				cara_aux._0 = ((i + 1) % num) * num_auxB + j;	  //4
				cara_aux._2 = ((i + 1) % num) * num_auxB + j + 1; //5
				caras.push_back(cara_aux);

				cara_aux._0 = i * num_auxB + j;					  //1
				cara_aux._1 = i * num_auxB + j + 1;				  //2
				cara_aux._2 = ((i + 1) % num) * num_auxB + j + 1; //5
				caras.push_back(cara_aux);
			}
		}
		break;

	case 1:
		for (int i = 0; i < num; ++i)
		{
			for (int j = 0; j < num_auxB - 1; ++j)
			{
				cara_aux._2 = i * num_auxB + j;					  //1
				cara_aux._0 = ((i + 1) % num) * num_auxB + j;	  //4
				cara_aux._1 = ((i + 1) % num) * num_auxB + j + 1; //5
				caras.push_back(cara_aux);

				cara_aux._2 = i * num_auxB + j;					  //1
				cara_aux._1 = i * num_auxB + j + 1;				  //2
				cara_aux._0 = ((i + 1) % num) * num_auxB + j + 1; //5
				caras.push_back(cara_aux);
			}
		}
		break;
	case 2:
		for (int i = 0; i < num; ++i)
		{
			for (int j = 0; j < num_auxB - 1; ++j)
			{
				cara_aux._1 = i * num_auxB + j;					  //1
				cara_aux._0 = ((i + 1) % num) * num_auxB + j;	  //4
				cara_aux._2 = ((i + 1) % num) * num_auxB + j + 1; //5
				caras.push_back(cara_aux);

				cara_aux._0 = i * num_auxB + j;					  //1
				cara_aux._1 = i * num_auxB + j + 1;				  //2
				cara_aux._2 = ((i + 1) % num) * num_auxB + j + 1; //5
				caras.push_back(cara_aux);
			}
		}
		break;
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

	vertice_aux.x = radio;
	vertice_aux.y = -al / 2;
	vertice_aux.z = 0;
	perfil.push_back(vertice_aux);
	vertice_aux.x = radio;
	vertice_aux.y = al / 2;
	vertice_aux.z = 0;
	perfil.push_back(vertice_aux);

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

	vertice_aux.x = radio;
	vertice_aux.y = -al / 2;
	vertice_aux.z = 0;
	perfil.push_back(vertice_aux);
	vertice_aux.x = 0;
	vertice_aux.y = al / 2;
	vertice_aux.z = 0;
	perfil.push_back(vertice_aux);

	parametros(perfil, n, eje);
}

//*************************************************************************
// clase esfera
//*******************
_esfera::_esfera(float radio, int n, int eje)
{
	vector<_vertex3f> perfil;
	_vertex3f vertice_aux;
	int angulo_llano = 180;
	float angulo = 0;
	int num = 15;

	for (int i = 0; i <= num; i++)
	{
		angulo = (angulo_llano / num) * i;
		angulo += 270;
		vertice_aux.x = cos(angulo * M_PI / 180) * radio;
		vertice_aux.y = sin(angulo * M_PI / 180) * radio;
		vertice_aux.z = 0.0;
		perfil.push_back(vertice_aux);
	}
	perfil[0].x = 0;
	perfil[num].x = 0;

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
	aux.x = 0.107;
	aux.y = -0.5;
	aux.z = 0.0;
	perfil.push_back(aux);
	aux.x = 0.107;
	aux.y = 0.5;
	aux.z = 0.0;
	perfil.push_back(aux);
	rodamiento.parametros(perfil, 12, 1);
	altura = 0.22;
};

void _chasis::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, _material mate)
{
	glPushMatrix();
	glScalef(1.0, 0.22, 0.95);
	base.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90.0, 1, 0, 0);
	rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.25, 0.0, 0.0);
	glRotatef(90.0, 1, 0, 0);
	rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.5, 0.0, 0.0);
	glRotatef(90.0, 1, 0, 0);
	rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.25, 0.0, 0.0);
	glRotatef(90.0, 1, 0, 0);
	rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5, 0.0, 0.0);
	glRotatef(90.0, 1, 0, 0);
	rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();
}

//************************************************************************
// torreta
//************************************************************************

_torreta::_torreta()
{
	altura = 0.18;
	anchura = 0.65;
};

void _torreta::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, _material mate)
{
	glPushMatrix();
	glScalef(0.65, 0.18, 0.6);
	base.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.325, 0, 0);
	glRotatef(90.0, 0, 0, 1);
	glScalef(0.18, 0.16, 0.6);
	parte_trasera.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();
}

//************************************************************************
// tubo
//************************************************************************

_tubo::_tubo()
{
	// perfil para un cilindro
	vector<_vertex3f> perfil;
	_vertex3f aux;
	aux.x = 0.04;
	aux.y = -0.4;
	aux.z = 0.0;
	perfil.push_back(aux);
	aux.x = 0.04;
	aux.y = 0.4;
	aux.z = 0.0;
	perfil.push_back(aux);
	tubo_abierto.parametros(perfil, 12, 1);
};

void _tubo::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, _material mate)
{

	glPushMatrix();
	glTranslatef(0.4, 0, 0);
	glRotatef(90.0, 0, 0, 1);
	tubo_abierto.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();
}

//************************************************************************
// tanque
//************************************************************************

_tanque::_tanque()
{
	int c = 100;
	giro_tubo = 2.0;
	giro_torreta = 0.0;
	giro_tubo_min = -9;
	giro_tubo_max = 20;

	piezas = 3;
	color_pick[0] = 1.0;
	color_pick[1] = 0.0;
	color_pick[2] = 0.0;
	for (int i = 0; i < piezas; i++)
	{
		activo[i] = 0;
		color_selec[0][i] = color_selec[1][i] = color_selec[2][i] = c;
		c = c + 20;
	}
};

void _tanque::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, _material mate)
{
	float r_p, g_p, b_p;

	r_p = color_pick[0];
	g_p = color_pick[1];
	b_p = color_pick[2];

	glPushMatrix();
	if (activo[0] == 1)
		chasis.draw(modo, r_p, g_p, b_p, r_p, g_p, b_p, grosor, mate);
	else
		chasis.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);

	glRotatef(giro_torreta, 0, 1, 0);
	glPushMatrix();
	glTranslatef(0.0, (chasis.altura + torreta.altura) / 2.0, 0.0);
	if (activo[1] == 1)
		torreta.draw(modo, r_p, g_p, b_p, r_p, g_p, b_p, grosor, mate);
	else
		torreta.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(torreta.anchura / 2.0, (chasis.altura + torreta.altura) / 2.0, 0.0);
	glRotatef(giro_tubo, 0, 0, 1);
	if (activo[2] == 1)
		tubo.draw(modo, r_p, g_p, b_p, r_p, g_p, b_p, grosor, mate);
	else
		tubo.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();
	glPopMatrix();
}

void _tanque::seleccion()
{
	int c;
	c = color_selec[0][0];
	glPushMatrix();
	chasis.draw(SELECT, c, c, c, c, c, c, 1, VACIO);

	c = color_selec[0][1];
	glRotatef(giro_torreta, 0, 1, 0);
	glPushMatrix();
	glTranslatef(0.0, (chasis.altura + torreta.altura) / 2.0, 0.0);
	torreta.draw(SELECT, c, c, c, c, c, c, 1, VACIO);
	glPopMatrix();

	c = color_selec[0][2];
	glPushMatrix();
	glTranslatef(torreta.anchura / 2.0, (chasis.altura + torreta.altura) / 2.0, 0.0);
	glRotatef(giro_tubo, 0, 0, 1);
	tubo.draw(SELECT, c, c, c, c, c, c, 1, VACIO);
	glPopMatrix();
	glPopMatrix();
}

//************************************************************************
// objeto articulado: camion de bomberos
//************************************************************************

//************************************************************************
// ruedas
//************************************************************************
_ruedas_der::_ruedas_der()
{
	// perfil para un cilindro

	rueda = _cilindro(0.235, 0.165, 15, 1);
	rueda.ambiente = _vertex4f(0.25, 0.25, 0.25, 1.0); //coeficientes ambiente y difuso
	rueda.difusa = _vertex4f(0.1, 0.1, 0.1, 1.0);
	rueda.especular = _vertex4f(0.5, 0.5, 0.5, 1.0); //coeficiente especular
	brillo = 50;
};

void _ruedas_der::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, _material mate)
{
	//Goma de las ruedas
	glPushMatrix();
	glTranslatef(0.0, 0.0, -0.5);
	glRotatef(90.0, 1, 0, 0);
	rueda.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();

/*
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.5); //mueve distancia (0.5 | 0 | 0)
	glRotatef(90.0, 1, 0, 0);
	rueda.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();
*/
	//Llanta de las ruedas
	glPushMatrix();
	glTranslatef(0.0, 0.0, -0.575);
	glRotatef(90.0, 1, 0, 0);
	glScalef(0.5, 0.1, 0.5);
	rueda.draw(modo, 0.4, 0.4, 0.4, 0.2, 0.2, 0.2, grosor, mate);
	glPopMatrix();
/*
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.575);
	glRotatef(90.0, 1, 0, 0);
	glScalef(0.5, 0.1, 0.5);
	rueda.draw(modo, 0.4, 0.4, 0.4, 0.2, 0.2, 0.2, grosor, mate);
	glPopMatrix();*/
}

_ruedas_izq::_ruedas_izq()
{
	// perfil para un cilindro

	rueda = _cilindro(0.235, 0.165, 15, 1);
	rueda.ambiente = _vertex4f(0.25, 0.25, 0.25, 1.0); //coeficientes ambiente y difuso
	rueda.difusa = _vertex4f(0.1, 0.1, 0.1, 1.0);
	rueda.especular = _vertex4f(0.5, 0.5, 0.5, 1.0); //coeficiente especular
	brillo = 50;
};

void _ruedas_izq::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, _material mate)
{
	//Goma de las ruedas
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.5);
	glRotatef(90.0, 1, 0, 0);
	rueda.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();

/*
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.5); //mueve distancia (0.5 | 0 | 0)
	glRotatef(90.0, 1, 0, 0);
	rueda.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();
*/
	//Llanta de las ruedas
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.575);
	glRotatef(90.0, 1, 0, 0);
	glScalef(0.5, 0.1, 0.5);
	rueda.draw(modo, 0.4, 0.4, 0.4, 0.2, 0.2, 0.2, grosor, mate);
	glPopMatrix();
/*
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.575);
	glRotatef(90.0, 1, 0, 0);
	glScalef(0.5, 0.1, 0.5);
	rueda.draw(modo, 0.4, 0.4, 0.4, 0.2, 0.2, 0.2, grosor, mate);
	glPopMatrix();*/
}
//************************************************************************
// carroceria
//************************************************************************
_carroceria::_carroceria()
{
	// perfil para un cilindro
	carcasa = _cubo();
	reposa = _cubo();
	ventana = _cubo();
	puerta = _cubo();
	foco = _esfera();
	sirena = _cilindro();
	matricula_b = _cubo();
	matricula_a = _cubo();

	carcasa.difusa = _vertex4f(0.90, 0.0, 0.0, 1.0); //coeficientes ambiente y difuso
	carcasa.ambiente = _vertex4f(0.15, 0.15, 0.15, 1.0);
	carcasa.especular = _vertex4f(0.5, 0.5, 0.5, 1.0); //coeficiente especular
	carcasa.brillo = 50;

	reposa.difusa = _vertex4f(0.90, 0.0, 0.0, 1.0);
	reposa.ambiente = _vertex4f(0.15, 0.15, 0.15, 0.0);
	//reposa.especular=_vertex4f(0.5,0.5,0.5,1.0);
	reposa.brillo = 50;

	ventana.difusa = _vertex4f(0.15, 0.15, 0.15, 1.0);
	ventana.ambiente = _vertex4f(0.55, 0.55, 0.55, 1.0);
	ventana.especular = _vertex4f(0.5, 0.5, 0.5, 1.0);
	ventana.brillo = 50;

	puerta.difusa = _vertex4f(0.25, 0.25, 0.25, 1.0); //coeficientes ambiente y difuso
	puerta.ambiente = _vertex4f(0.55, 0.55, 0.55, 1.0);
	puerta.especular = _vertex4f(0.5, 0.5, 0.5, 1.0); //coeficiente especular
	puerta.brillo = 50;

	foco.difusa = _vertex4f(1, 0.9882, 0.2745, 1.0);
	foco.ambiente = _vertex4f(0.55, 0.55, 0.55, 1.0);
	foco.especular = _vertex4f(0.5, 0.5, 0.5, 1.0);
	foco.brillo = 50;

	sirena.difusa = _vertex4f(0.0, 0.5020, 0.8745, 1.0);
	sirena.ambiente = _vertex4f(0.55, 0.55, 0.55, 1.0);
	sirena.especular = _vertex4f(0.5, 0.5, 0.5, 1.0);
	sirena.brillo = 50;

	matricula_b.difusa = _vertex4f(0.9, 0.9, 0.9, 1.0);
	matricula_b.ambiente = _vertex4f(0.55, 0.55, 0.55, 1.0);
	matricula_b.especular = _vertex4f(0.5, 0.5, 0.5, 1.0);
	matricula_b.brillo = 50;

	matricula_a.difusa = _vertex4f(0.0, 0.2902, 0.8353, 1.0);
	matricula_a.ambiente = _vertex4f(0.55, 0.55, 0.55, 1.0);
	matricula_a.especular = _vertex4f(0.5, 0.5, 0.5, 1.0);
	matricula_a.brillo = 50;

	luza.difusa = _vertex4f(0.803, 0.043, 0.043, 1.0);
	luza.ambiente = _vertex4f(0.55, 0.55, 0.55, 1.0);
	luza.especular = _vertex4f(0.5, 0.5, 0.5, 1.0);
	luza.brillo = 50;

	luzb.difusa = _vertex4f(1, 0.9882, 0.2745, 1.0);
	luzb.ambiente = _vertex4f(0.55, 0.55, 0.55, 1.0);
	luzb.especular = _vertex4f(0.5, 0.5, 0.5, 1.0);
	luzb.brillo = 50;

	luzc.difusa = _vertex4f(0.55, 0.55, 0.55, 1.0);
	luzc.ambiente = _vertex4f(0.55, 0.55, 0.55, 1.0);
	luzc.especular = _vertex4f(0.5, 0.5, 0.5, 1.0);
	luzc.brillo = 50;
};

void _carroceria::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, _material mate)
{

	//carcasa
	glPushMatrix();
	glTranslatef(1.4, 0.6, 0.0);
	glScalef(3.6, 0.8, 1);
	carcasa.draw(modo, 0.90, 0.0, 0.0, r2, g2, b2, grosor, mate);
	glPopMatrix();

	//reposa escaleras
	glPushMatrix();
	glTranslatef(2.8, 1.1, 0.0);
	glScalef(0.9, 0.2, 1);
	reposa.draw(modo, 0.90, 0.0, 0.0, r2, g2, b2, grosor, mate);
	glPopMatrix();

	//parabrisas
	glPushMatrix();
	glTranslatef(3.21, 0.8, 0.0);
	glScalef(0.01, 0.3, 0.8);
	ventana.draw(modo, 0.2, 0.2, 0.2, 0.5, 0.5, 0.5, grosor, mate);
	glPopMatrix();

	//focos
	glPushMatrix();
	glTranslatef(3.21, 0.4, 0.38);
	glScalef(0.07, 0.07, 0.07);
	foco.draw(modo, 1, 0.9882, 0.2745, 0.8588, 0.4627, 0.0941, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.21, 0.4, -0.38);
	glScalef(0.07, 0.07, 0.07);
	foco.draw(modo, 1, 0.9882, 0.2745, 0.8588, 0.4627, 0.0941, grosor, mate);
	glPopMatrix();

	//luces
	glPushMatrix();
	glTranslatef(-0.4, 0.3, 0.0);
	glScalef(0.01, 0.15, 0.98);
	luzc.draw(modo, 0.55, 0.55, 0.55, 0.7, 0.7, 0.7, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.41, 0.3, 0.3);
	glScalef(0.01, 0.07, 0.15);
	luza.draw(modo, 0.803, 0.043, 0.043, 0.819, 0.3686, 0.3686, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.41, 0.3, -0.3);
	glScalef(0.01, 0.07, 0.15);
	luza.draw(modo, 0.803, 0.043, 0.043, 0.819, 0.3686, 0.3686, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.41, 0.3, 0.41);
	glScalef(0.01, 0.07, 0.07);
	luzb.draw(modo, 1, 0.9882, 0.2745, 0.8588, 0.4627, 0.0941, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.41, 0.3, -0.41);
	glScalef(0.01, 0.07, 0.07);
	luzb.draw(modo, 1, 0.9882, 0.2745, 0.8588, 0.4627, 0.0941, grosor, mate);
	glPopMatrix();

	//matriculas
	glPushMatrix();
	glTranslatef(-0.41, 0.3, 0.0);
	glScalef(0.01, 0.15, 0.4);
	matricula_b.draw(modo, 0.9, 0.9, 0.9, 0.8, 0.8, 0.8, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.415, 0.3, -0.15);
	glScalef(0.01, 0.15, 0.1);
	matricula_a.draw(modo, 0.0, 0.2902, 0.8353, 0.0, 0.0, 0.3333, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.2, 0.3, 0.0);
	glScalef(0.01, 0.15, 0.4);
	matricula_b.draw(modo, 0.9, 0.9, 0.9, 0.8, 0.8, 0.8, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.21, 0.3, 0.15);
	glScalef(0.01, 0.15, 0.1);
	matricula_a.draw(modo, 0.0, 0.2902, 0.8353, 0.0, 0.0, 0.3333, grosor, mate);
	glPopMatrix();

	//Sirenas
	glPushMatrix();
	glTranslatef(3.18, 1.17, 0.24);
	glScalef(0.1, 0.1, 0.1);
	sirena.draw(modo, 0.0, 0.5020, 0.8745, 0.0, 0.2902, 0.8353, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.18, 1.17, -0.24);
	glScalef(0.1, 0.1, 0.1);
	sirena.draw(modo, 0.0, 0.5020, 0.8745, 0.0, 0.2902, 0.8353, grosor, mate);
	glPopMatrix();

	//Puertas
	glPushMatrix();
	glTranslatef(1, 0.6, 0.501);
	glScalef(0.8, 0.48, 0.01);
	puerta.draw(modo, 0.6, 0.6, 0.6, 0.8, 0.8, 0.8, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1, 0.6, -0.501);
	glScalef(0.8, 0.48, 0.01);
	puerta.draw(modo, 0.6, 0.6, 0.6, 0.8, 0.8, 0.8, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.4, 0.68, 0);
	glScalef(0.01, 0.48, 0.8);
	puerta.draw(modo, 0.6, 0.6, 0.6, 0.8, 0.8, 0.8, grosor, mate);
	glPopMatrix();
}


//************************************************************************
// carroceria
//************************************************************************
_ventana::_ventana()
{
	// perfil para un cilindro
	ventana = _cubo();

	ventana.difusa = _vertex4f(0.15, 0.15, 0.15, 1.0);
	ventana.ambiente = _vertex4f(0.55, 0.55, 0.55, 1.0);
	ventana.especular = _vertex4f(0.5, 0.5, 0.5, 1.0);
	ventana.brillo = 50;

};

void _ventana::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, _material mate)
{

	//Ventanas
	glPushMatrix();
	glTranslatef(2.8, 0.8, 0.501);
	glScalef(0.5, 0.3, 0.01);
	ventana.draw(modo, r1,g1,b1,r2,g2,b2, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.8, 0.8, -0.501);
	glScalef(0.5, 0.3, 0.01);
	ventana.draw(modo, r1,g1,b1,r2,g2,b2, grosor, mate);
	glPopMatrix();

}
//************************************************************************
// plataforma
//************************************************************************

_plataforma::_plataforma()
{
	// perfil para un cilindro
	cubo = _cubo();

	cubo.difusa = _vertex4f(0.20, 0.2, 0.2, 1.0);	  //coeficientes ambiente y difuso
	cubo.ambiente = _vertex4f(0.55, 0.55, 0.55, 1.0); //coeficientes ambiente y difuso
	cubo.especular = _vertex4f(0.5, 0.5, 0.5, 1.0);	  //coeficiente especular
	cubo.brillo = 50;
};

void _plataforma::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, _material mate)
{

	//base
	glPushMatrix();
	glScalef(0.8, 0.12, 0.8);
	cubo.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();

	//lateral 1
	glPushMatrix();
	glTranslatef(0.0, 0.31, 0.37);
	glScalef(0.6, 0.5, 0.04);
	cubo.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();

	//lateral 2
	glPushMatrix();
	glTranslatef(0.0, 0.31, -0.37);
	glScalef(0.6, 0.5, 0.04);
	cubo.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();
}

//************************************************************************
// escalera grande
//************************************************************************

_escaleragrande::_escaleragrande()
{
	// perfil para un cilindro
	barra = _cubo();

	barra.difusa = _vertex4f(0.40, 0.4, 0.4, 1.0);	   //coeficientes ambiente y difuso
	barra.ambiente = _vertex4f(0.55, 0.55, 0.55, 1.0); //coeficientes ambiente y difuso
	barra.especular = _vertex4f(0.5, 0.5, 0.5, 1.0);   //coeficiente especular
	barra.brillo = 50;
};

void _escaleragrande::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, _material mate)
{

	//barras de mano
	glPushMatrix();
	glTranslated(0.025, 0.0, 0.0);
	glScalef(0.05, 0.05, 0.59);
	barra.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.225, 0.0, 0.0);
	glScalef(0.05, 0.05, 0.59);
	barra.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.425, 0.0, 0.0);
	glScalef(0.05, 0.05, 0.59);
	barra.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.625, 0.0, 0.0);
	glScalef(0.05, 0.05, 0.59);
	barra.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.825, 0.0, 0.0);
	glScalef(0.05, 0.05, 0.59);
	barra.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslated(1.025, 0.0, 0.0);
	glScalef(0.05, 0.05, 0.59);
	barra.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslated(1.225, 0.0, 0.0);
	glScalef(0.05, 0.05, 0.59);
	barra.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslated(1.425, 0.0, 0.0);
	glScalef(0.05, 0.05, 0.59);
	barra.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslated(1.625, 0.0, 0.0);
	glScalef(0.05, 0.05, 0.59);
	barra.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslated(1.825, 0.0, 0.0);
	glScalef(0.05, 0.05, 0.59);
	barra.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslated(2.025, 0.0, 0.0);
	glScalef(0.05, 0.05, 0.59);
	barra.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslated(2.225, 0.0, 0.0);
	glScalef(0.05, 0.05, 0.59);
	barra.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslated(2.425, 0.0, 0.0);
	glScalef(0.05, 0.05, 0.59);
	barra.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();

	//barras laterales
	glPushMatrix();
	glTranslatef(1.25, 0, 0.32);
	glScalef(2.5, 0.06, 0.06);
	barra.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.25, 0, -0.32);
	glScalef(2.5, 0.06, 0.06);
	barra.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();
}

//************************************************************************
// escalera chica
//************************************************************************

_escalerachica::_escalerachica()
{
	// perfil para un cilindro
	barra = _cubo();

	// perfil para un cilindro
	barra = _cubo();

	barra.difusa = _vertex4f(0.30, 0.3, 0.3, 1.0);	   //coeficientes ambiente y difuso
	barra.ambiente = _vertex4f(0.55, 0.55, 0.55, 1.0); //coeficientes ambiente y difuso
	barra.especular = _vertex4f(0.5, 0.5, 0.5, 1.0);   //coeficiente especular
	barra.brillo = 50;
};

void _escalerachica::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, _material mate)
{
	//barras de mano
	glPushMatrix();
	glTranslated(0.025, 0.0, 0.0);
	glScalef(0.04, 0.04, 0.49);
	barra.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.225, 0.0, 0.0);
	glScalef(0.04, 0.04, 0.49);
	barra.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.425, 0.0, 0.0);
	glScalef(0.04, 0.04, 0.49);
	barra.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.625, 0.0, 0.0);
	glScalef(0.04, 0.04, 0.49);
	barra.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.825, 0.0, 0.0);
	glScalef(0.04, 0.04, 0.49);
	barra.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslated(1.025, 0.0, 0.0);
	glScalef(0.04, 0.04, 0.49);
	barra.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslated(1.225, 0.0, 0.0);
	glScalef(0.04, 0.04, 0.49);
	barra.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslated(1.425, 0.0, 0.0);
	glScalef(0.04, 0.04, 0.49);
	barra.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslated(1.625, 0.0, 0.0);
	glScalef(0.04, 0.04, 0.49);
	barra.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslated(1.825, 0.0, 0.0);
	glScalef(0.04, 0.04, 0.49);
	barra.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslated(2.025, 0.0, 0.0);
	glScalef(0.04, 0.04, 0.49);
	barra.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslated(2.225, 0.0, 0.0);
	glScalef(0.04, 0.04, 0.49);
	barra.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();

	//barras laterales
	glPushMatrix();
	glTranslatef(1.25, 0, 0.25);
	glScalef(2.5, 0.05, 0.05);
	barra.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.25, 0, -0.25);
	glScalef(2.5, 0.05, 0.05);
	barra.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();
}

//************************************************************************
// cabina
//************************************************************************

_cabina::_cabina()
{
	barra = _cubo();

	barra.difusa = _vertex4f(0.8, 0.2, 0.2, 1.0);	   //coeficientes ambiente y difuso
	barra.ambiente = _vertex4f(0.55, 0.55, 0.55, 1.0); //coeficientes ambiente y difuso
	barra.especular = _vertex4f(0.5, 0.5, 0.5, 1.0);   //coeficiente especular
	barra.brillo = 50;
};

void _cabina::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, _material mate)
{
	//barras inferiores
	glPushMatrix();
	glTranslated(0.025, 0.0, 0.0);
	glScalef(0.05, 0.05, 0.5);
	barra.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.575, 0.0, 0.0);
	glScalef(0.05, 0.05, 0.5);
	barra.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.300, 0.0, -0.250);
	glRotatef(90, 0, 1, 0);
	glTranslated(0.025, 0.0, 0.0);
	glScalef(0.05, 0.05, 0.6);
	barra.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.300, 0.0, 0.250);
	glRotatef(-90, 0, 1, 0);
	glTranslated(0.025, 0.0, 0.0);
	glScalef(0.05, 0.05, 0.6);
	barra.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();

	//barras verticales
	glPushMatrix();
	glTranslated(0.025, 0.325, -0.275);
	glScalef(0.05, 0.6, 0.05);
	barra.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.025, 0.325, +0.275);
	glScalef(0.05, 0.6, 0.05);
	barra.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.575, 0.325, -0.275);
	glScalef(0.05, 0.6, 0.05);
	barra.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.575, 0.325, +0.275);
	glScalef(0.05, 0.6, 0.05);
	barra.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();
}

//************************************************************************
// objeto articulado: elevador
//************************************************************************

_elevador::_elevador()
{
	// perfil para un cilindro
	barra = _cubo();
	barra.difusa = _vertex4f(0.8, 0.5, 0.5, 1.0);	   //coeficientes ambiente y difuso
	barra.ambiente = _vertex4f(0.55, 0.55, 0.55, 1.0); //coeficientes ambiente y difuso
	barra.especular = _vertex4f(0.5, 0.5, 0.5, 1.0);   //coeficiente especular
	barra.brillo = 50;
};

void _elevador::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, _material mate)
{

	//Suelo elevador
	glPushMatrix();
	glTranslated(0.25, 0.0, 0.0);
	glScalef(0.50, 0.05, 0.5);
	barra.draw(modo, 0.8, 0.8, 0.8, r2, g2, b2, grosor, mate);
	glPopMatrix();

	//paredes elevador
	glPushMatrix();
	glTranslated(0.02, 0.22, 0);
	glScalef(0.04, 0.4, 0.52);
	barra.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.25, 0.22, -0.22);
	glScalef(0.42, 0.40, 0.04);
	barra.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.48, 0.22, 0);
	glScalef(0.04, 0.4, 0.52);
	barra.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.25, 0.22, 0.22);
	glScalef(0.42, 0.40, 0.04);
	barra.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();

	//barras superiores
	glPushMatrix();
	glTranslated(0.02, 0.44, 0.0);
	glScalef(0.04, 0.04, 0.5);
	barra.draw(modo, 0.3, 0.3, 0.3, r2, g2, b2, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.48, 0.44, 0.0);
	glScalef(0.04, 0.04, 0.5);
	barra.draw(modo, 0.3, 0.3, 0.3, r2, g2, b2, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.25, 0.44, 0.23);
	glRotatef(90, 0, 1, 0);
	glScalef(0.04, 0.04, 0.42);
	barra.draw(modo, 0.3, 0.3, 0.3, r2, g2, b2, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.25, 0.44, -0.23);
	glRotatef(90, 0, 1, 0);
	glScalef(0.04, 0.04, 0.5);
	barra.draw(modo, 0.3, 0.3, 0.3, r2, g2, b2, grosor, mate);
	glPopMatrix();

	//base de la pistola
	glPushMatrix();
	glTranslated(0.5, 0.15, 0);
	glRotatef(-90, 1, 0, 0);
	glTranslated(0.02, 0.0, 0.2);
	glScalef(0.04, 0.24, 0.24);
	barra.draw(modo, 0.87, 0.6235, 0.1686, r2, g2, b2, grosor, mate);
	glPopMatrix();
}

//************************************************************************
// pistola
//************************************************************************

_pistola::_pistola()
{
	pistola = _cilindro(0.06, 0.4, 15, 1);
	pistola.difusa = _vertex4f(0.3, 0.5, 0.7, 1.0);		 //coeficientes ambiente y difuso
	pistola.ambiente = _vertex4f(0.25, 0.25, 0.25, 1.0); //coeficientes ambiente y difuso
	pistola.especular = _vertex4f(0.5, 0.5, 0.5, 1.0);	 //coeficiente especular
	pistola.brillo = 50;
};

void _pistola::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, _material mate)
{

	glPushMatrix();
	glTranslatef(0.2, 0, 0);
	glRotatef(90, 0, 0, 1);
	pistola.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();
}

//************************************************************************
// agua
//************************************************************************

_agua::_agua()
{
	gota = _esfera();
	gota.difusa = _vertex4f(0.0, 0.81, 1, 1.0);		  //coeficientes ambiente y difuso
	gota.ambiente = _vertex4f(0.25, 0.25, 0.25, 1.0); //coeficientes ambiente y difuso
	gota.especular = _vertex4f(0.5, 0.5, 0.5, 1.0);	  //coeficiente especular
	gota.brillo = 50;
};

void _agua::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, _material mate)
{

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glScalef(0.035, 0.035, 0.035);
	gota.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();
}

//************************************************************************
// camion de bomberos
//************************************************************************

_camionbomberos::_camionbomberos()
{
	int c = 90;
	piezas = 15;
	color_pick[0] = 1.0;
	color_pick[1] = 0.0;
	color_pick[2] = 0.0;
	for (int i = 0; i < piezas; i++)
	{
		activo[i] = 0;
		color_selec[0][i] = color_selec[1][i] = color_selec[2][i] = c;
		c = c + 5;
	}
}

void _camionbomberos::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, _material mate)
{
	float r_p, g_p, b_p;

	r_p = color_pick[0];
	g_p = color_pick[1];
	b_p = color_pick[2];
	glPushMatrix();
	glTranslatef(movimiento_camion, 0, 0);
	glTranslatef(0.0, 0.2, 0);
	glRotatef(giro_ruedas, 0, 0, 1);
	if (activo[0] == 1)
		rueda1.draw(modo, r_p, g_p, b_p, r_p, g_p, b_p, grosor, mate);
	else
		rueda1.draw(modo, 0, 0, 0, 0.7, 0.7, 0.7, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(movimiento_camion, 0, 0);
	glTranslatef(1.9, 0.2, 0);
	glRotatef(giro_ruedas, 0, 0, 1);
	if (activo[1] == 1)
		rueda2.draw(modo, r_p, g_p, b_p, r_p, g_p, b_p, grosor, mate);
	else
		rueda2.draw(modo, 0, 0, 0, 0.7, 0.7, 0.7, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(movimiento_camion, 0, 0);
	glTranslatef(2.7, 0.2, 0);
	glRotatef(giro_ruedas, 0, 0, 1);
	if (activo[2] == 1)
		rueda3.draw(modo, r_p, g_p, b_p, r_p, g_p, b_p, grosor, mate);
	else
		rueda3.draw(modo, 0, 0, 0, 0.7, 0.7, 0.7, grosor, mate);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(movimiento_camion, 0, 0);
	glTranslatef(0.0, 0.2, 0);
	glRotatef(giro_ruedas, 0, 0, 1);
	if (activo[3] == 1)
		rueda4.draw(modo, r_p, g_p, b_p, r_p, g_p, b_p, grosor, mate);
	else
		rueda4.draw(modo, 0, 0, 0, 0.7, 0.7, 0.7, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(movimiento_camion, 0, 0);
	glTranslatef(1.9, 0.2, 0);
	glRotatef(giro_ruedas, 0, 0, 1);
	if (activo[4] == 1)
		rueda5.draw(modo, r_p, g_p, b_p, r_p, g_p, b_p, grosor, mate);
	else
		rueda5.draw(modo, 0, 0, 0, 0.7, 0.7, 0.7, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(movimiento_camion, 0, 0);
	glTranslatef(2.7, 0.2, 0);
	glRotatef(giro_ruedas, 0, 0, 1);
	if (activo[5] == 1)
		rueda6.draw(modo, r_p, g_p, b_p, r_p, g_p, b_p, grosor, mate);
	else
		rueda6.draw(modo, 0, 0, 0, 0.7, 0.7, 0.7, grosor, mate);
	glPopMatrix();
	//las transformaciones se hacen de abajo a arriba
	//las clases torreta, tubo... están sobre el eje para poder girarlos
	//luego se giran y se ponen bien en la puta clase tanque de mierda

	glPushMatrix();
	glTranslatef(movimiento_camion, 0, 0);
	if (activo[6] == 1){
		carroceria.draw(modo, r_p, g_p, b_p, r_p, g_p, b_p, grosor, mate);
	}
	else{
		carroceria.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(movimiento_camion, 0, 0);
	if (activo[7] == 1){
		ventana.draw(modo, r_p, g_p, b_p, r_p, g_p, b_p, grosor, mate);
	}
	else{
		ventana.draw(modo, 0.2, 0.2, 0.2, 0.5, 0.5, 0.5, grosor, mate);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(movimiento_camion, 0, 0);
	glTranslatef(0.0, 1.05, 0.0);
	glRotatef(giro_plataforma, 0, 1, 0);
	if (activo[8] == 1)
		plataforma.draw(modo, r_p, g_p, b_p, r_p, g_p, b_p, grosor, mate);
	else
		plataforma.draw(modo, r1, g1, b1, r2, g2, b2, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(movimiento_camion, 0, 0);
	glTranslatef(0.0, 1.30, 0.0);
	glRotatef(giro_plataforma, 0, 1, 0);
	glRotatef(giro_escalera, 0, 0, 1);
	if (activo[9] == 1)
		escaleragrande.draw(modo, r_p, g_p, b_p, r_p, g_p, b_p, grosor, mate);
	else
		escaleragrande.draw(modo, 0.75, 0.75, 0.75, 0.8, 0.8, 0.1, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(movimiento_camion, 0, 0);
	glTranslatef(0.0, 1.30, 0.0);
	glRotatef(giro_plataforma, 0, 1, 0);
	glRotatef(giro_escalera, 0, 0, 1);
	glTranslatef(translacion_escalera, 0, 0);
	if (activo[10] == 1)
		escalerachica.draw(modo, r_p, g_p, b_p, r_p, g_p, b_p, grosor, mate);
	else
		escalerachica.draw(modo, 0.3, 0.5, 0.7, 0.1, 0.1, 0.5, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(movimiento_camion, 0, 0);
	glTranslatef(0.0, 1.30, 0.0);
	glRotatef(giro_plataforma, 0, 1, 0);
	glRotatef(giro_escalera, 0, 0, 1);
	glTranslatef(translacion_escalera, 0, 0);
	glTranslatef(2.5, 0, 0);
	glRotatef(-giro_escalera, 0, 0, 1);
	if (activo[11] == 1)
		cabina.draw(modo, r_p, g_p, b_p, r_p, g_p, b_p, grosor, mate);
	else
		cabina.draw(modo, 0.1, 0.3, 0.1, 0.1, 0.1, 0.5, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(movimiento_camion, 0, 0);
	glTranslatef(0.0, 1.30, 0.0);
	glRotatef(giro_plataforma, 0, 1, 0);
	glRotatef(giro_escalera, 0, 0, 1);
	glTranslatef(translacion_escalera, 0, 0);
	glTranslatef(2.55, 0, 0);
	glRotatef(-giro_escalera, 0, 0, 1);
	glTranslatef(0, levantamiento, 0);
	if (activo[12] == 1)
		elevador.draw(modo, r_p, g_p, b_p, r_p, g_p, b_p, grosor, mate);
	else
		elevador.draw(modo, 0.45, 0.45, 0.45, 0.8, 0.8, 0.8, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(movimiento_camion, 0, 0);
	glTranslatef(0.0, 1.30, 0.0);
	glRotatef(giro_plataforma, 0, 1, 0);
	glTranslatef(0.4, +0.35, 0);
	glRotatef(giro_escalera, 0, 0, 1);
	glTranslatef(translacion_escalera, 0, 0);
	glTranslatef(2.55, 0.00, 0);
	glRotatef(-giro_escalera, 0, 0, 1);
	glTranslatef(0, levantamiento, 0);
	glRotatef(giro_pistola_vertical, 0, 0, 1);
	glRotatef(giro_pistola_horizontal, 0, 1, 0);
	if (activo[13] == 1)
		pistola.draw(modo, r_p, g_p, b_p, r_p, g_p, b_p, grosor, mate);
	else
		pistola.draw(modo, 0.27, 0.6235, 0.5686, r2, g2, b2, grosor, mate);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(movimiento_camion, 0, 0);
	glTranslatef(0.0, 1.30, 0.0);
	glRotatef(giro_plataforma, 0, 1, 0);
	glTranslatef(0.45, +0.35, 0);
	glRotatef(giro_escalera, 0, 0, 1);
	glTranslatef(translacion_escalera, 0, 0);
	glTranslatef(2.55, 0, 0);
	glRotatef(-giro_escalera, 0, 0, 1);
	glTranslatef(0, levantamiento, 0);
	glRotatef(giro_pistola_vertical, 0, 0, 1);
	glRotatef(giro_pistola_horizontal, 0, 1, 0);
	glTranslatef(movimiento_agua, 0, 0);
	if (activo[14] == 1)
		agua.draw(modo, r_p, g_p, b_p, r_p, g_p, b_p, grosor, mate);
	else
		agua.draw(modo, 0.0, 0.81, 1, 0.34, 0.1, 0.1, grosor, mate);
	glPopMatrix();
};

void _camionbomberos::seleccion()
{
	int c;
	c = color_selec[0][0];
	glPushMatrix();
	glTranslatef(movimiento_camion, 0, 0);
	glTranslatef(0.0, 0.2, 0.0);
	glRotatef(giro_ruedas, 0, 0, 1);
	rueda1.draw(SELECT, c, c, c, c, c, c, 1, VACIO);
	glPopMatrix();

	c = color_selec[0][1];
	glPushMatrix();
	glTranslatef(movimiento_camion, 0, 0);
	glTranslatef(1.9, 0.2, 0.0);
	glRotatef(giro_ruedas, 0, 0, 1);
	rueda2.draw(SELECT, c, c, c, c, c, c, 1, VACIO);
	glPopMatrix();

	c = color_selec[0][2];
	glPushMatrix();
	glTranslatef(movimiento_camion, 0, 0);
	glTranslatef(2.7, 0.2, 0.0);
	glRotatef(giro_ruedas, 0, 0, 1);
	rueda3.draw(SELECT, c, c, c, c, c, c, 1, VACIO);
	glPopMatrix();

	c = color_selec[0][3];
	glPushMatrix();
	glTranslatef(movimiento_camion, 0, 0);
	glTranslatef(0.0, 0.2, 0.0);
	glRotatef(giro_ruedas, 0, 0, 1);
	rueda4.draw(SELECT, c, c, c, c, c, c, 1, VACIO);
	glPopMatrix();

	c = color_selec[0][4];
	glPushMatrix();
	glTranslatef(movimiento_camion, 0, 0);
	glTranslatef(1.9, 0.2, 0.0);
	glRotatef(giro_ruedas, 0, 0, 1);
	rueda5.draw(SELECT, c, c, c, c, c, c, 1, VACIO);
	glPopMatrix();

	c = color_selec[0][5];
	glPushMatrix();
	glTranslatef(movimiento_camion, 0, 0);
	glTranslatef(2.7, 0.2, 0.0);
	glRotatef(giro_ruedas, 0, 0, 1);
	rueda6.draw(SELECT, c, c, c, c, c, c, 1, VACIO);
	glPopMatrix();

	c = color_selec[0][6];
	glPushMatrix();
	glTranslatef(movimiento_camion, 0, 0);
	carroceria.draw(SELECT, c, c, c, c, c, c, 1, VACIO);
	glPopMatrix();

	c = color_selec[0][7];
	glPushMatrix();
	glTranslatef(movimiento_camion, 0, 0);
	ventana.draw(SELECT, c, c, c, c, c, c, 1, VACIO);
	glPopMatrix();

	c = color_selec[0][8];
	glPushMatrix();
	glTranslatef(movimiento_camion, 0, 0);
	glTranslatef(0.0, 1.05, 0.0);
	glRotatef(giro_plataforma, 0, 1, 0);
	plataforma.draw(SELECT, c, c, c, c, c, c, 1, VACIO);
	glPopMatrix();

	c = color_selec[0][9];
	glPushMatrix();
	glTranslatef(movimiento_camion, 0, 0);
	glTranslatef(0.0, 1.30, 0.0);
	glRotatef(giro_plataforma, 0, 1, 0);
	glRotatef(giro_escalera, 0, 0, 1);
	escaleragrande.draw(SELECT, c, c, c, c, c, c, 1, VACIO);
	glPopMatrix();

	c = color_selec[0][10];
	glPushMatrix();
	glTranslatef(movimiento_camion, 0, 0);
	glTranslatef(0.0, 1.30, 0.0);
	glRotatef(giro_plataforma, 0, 1, 0);
	glRotatef(giro_escalera, 0, 0, 1);
	glTranslatef(translacion_escalera, 0, 0);
	escalerachica.draw(SELECT, c, c, c, c, c, c, 1, VACIO);
	glPopMatrix();

	c = color_selec[0][11];
	glPushMatrix();
	glTranslatef(movimiento_camion, 0, 0);
	glTranslatef(0.0, 1.30, 0.0);
	glRotatef(giro_plataforma, 0, 1, 0);
	glRotatef(giro_escalera, 0, 0, 1);
	glTranslatef(translacion_escalera, 0, 0);
	glTranslatef(2.5, 0, 0);
	glRotatef(-giro_escalera, 0, 0, 1);
	cabina.draw(SELECT, c, c, c, c, c, c, 1, VACIO);
	glPopMatrix();

	c = color_selec[0][12];
	glPushMatrix();
	glTranslatef(movimiento_camion, 0, 0);
	glTranslatef(0.0, 1.30, 0.0);
	glRotatef(giro_plataforma, 0, 1, 0);
	glRotatef(giro_escalera, 0, 0, 1);
	glTranslatef(translacion_escalera, 0, 0);
	glTranslatef(2.55, 0, 0);
	glRotatef(-giro_escalera, 0, 0, 1);
	glTranslatef(0, levantamiento, 0);
	elevador.draw(SELECT, c, c, c, c, c, c, 1, VACIO);
	glPopMatrix();

	c = color_selec[0][13];
	glPushMatrix();
	glTranslatef(movimiento_camion, 0, 0);
	glTranslatef(0.0, 1.30, 0.0);
	glRotatef(giro_plataforma, 0, 1, 0);
	glTranslatef(0.4, +0.35, 0);
	glRotatef(giro_escalera, 0, 0, 1);
	glTranslatef(translacion_escalera, 0, 0);
	glTranslatef(2.55, 0.00, 0);
	glRotatef(-giro_escalera, 0, 0, 1);
	glTranslatef(0, levantamiento, 0);
	glRotatef(giro_pistola_vertical, 0, 0, 1);
	glRotatef(giro_pistola_horizontal, 0, 1, 0);
	pistola.draw(SELECT, c, c, c, c, c, c, 1, VACIO);
	glPopMatrix();

	c = color_selec[0][14];
	glPushMatrix();
	glTranslatef(movimiento_camion, 0, 0);
	glTranslatef(0.0, 1.30, 0.0);
	glRotatef(giro_plataforma, 0, 1, 0);
	glTranslatef(0.45, +0.35, 0);
	glRotatef(giro_escalera, 0, 0, 1);
	glTranslatef(translacion_escalera, 0, 0);
	glTranslatef(2.55, 0, 0);
	glRotatef(-giro_escalera, 0, 0, 1);
	glTranslatef(0, levantamiento, 0);
	glRotatef(giro_pistola_vertical, 0, 0, 1);
	glRotatef(giro_pistola_horizontal, 0, 1, 0);
	glTranslatef(movimiento_agua, 0, 0);
	agua.draw(SELECT, c, c, c, c, c, c, 1, VACIO);
	glPopMatrix();
}
//************************************************************************
// Métodos de luz
//************************************************************************

Luz::Luz()
{
	float l[] = {20, 30, 20, 1};
	posicion = l;
}

Luz::Luz(GLenum iden, _vertex4f amb, _vertex4f dif, _vertex4f espec, _vertex4f pos)
{
	id = iden;
	ambiente = amb;
	difusa = dif;
	especular = espec;
	posicion = pos;
}

void Luz::encenderLuz()
{
	glEnable(id);
}

void Luz::movimientoLuz(bool horario)
{
	if (horario)
		angulo += 3.0;
	else
		angulo -= 3.0;
}

void Luz::apagarLuz()
{
	glDisable(id);
}

void Luz::draw()
{
	glEnable(GL_LIGHTING);
	glLightfv(id, GL_DIFFUSE, (GLfloat *)&difusa);
	//glLightfv(id, GL_SPECULAR, (GLfloat*) &especular);

	glPushMatrix();
	glRotatef(angulo, 0.0, 1.0, 0.0);
	glLightfv(id, GL_POSITION, (GLfloat *)&posicion);
	glPopMatrix();
}

void Luz::setAmbiente(float *color)
{
	ambiente = color;
}

void Luz::setDifusa(float *color)
{
	difusa = color;
}

void Luz::setEspecular(float *color)
{
	especular = color;
}

void Luz::setPosicion(float *pos)
{
	posicion = pos;
}

void Luz::setIDLuz(GLenum iden)
{
	id = iden;
}

//************************************************************************
// Constructor de Material
//************************************************************************

_Material::_Material(_material mat)
{
	switch (mat)
	{
	case LATON:
		ambiente[0] = 0.329412;
		ambiente[1] = 0.223529;
		ambiente[2] = 0.027451;
		ambiente[3] = 1.0;
		difusa[0] = 0.780392;
		difusa[1] = 0.568627;
		difusa[2] = 0.113725;
		difusa[3] = 1;
		especular[0] = 0.992157;
		especular[1] = 0.941176;
		especular[2] = 0.807843;
		especular[3] = 1;
		brillo = 27.8974;
		break;
	case BRONCE:
		ambiente[0] = 0.2125;
		ambiente[1] = 0.1275;
		ambiente[2] = 0.054;
		ambiente[3] = 1.0;
		difusa[0] = 0.714;
		difusa[1] = 0.4284;
		difusa[2] = 0.18144;
		difusa[3] = 1;
		especular[0] = 0.393548;
		especular[1] = 0.271906;
		especular[2] = 0.166721;
		especular[3] = 1;
		brillo = 25.6;
		break;
	case BRONCE_PULIDO:
		ambiente[0] = 0.25;
		ambiente[1] = 0.148;
		ambiente[2] = 0.06475;
		ambiente[3] = 1.0;
		difusa[0] = 0.4;
		difusa[1] = 0.2368;
		difusa[2] = 0.1036;
		difusa[3] = 1;
		especular[0] = 0.774597;
		especular[1] = 0.458561;
		especular[2] = 0.200621;
		especular[3] = 1;
		brillo = 76.8;
		break;
	case CROMO:
		ambiente[0] = 0.25;
		ambiente[1] = 0.25;
		ambiente[2] = 0.25;
		ambiente[3] = 1.0;
		difusa[0] = 0.4;
		difusa[1] = 0.4;
		difusa[2] = 0.4;
		difusa[3] = 1;
		especular[0] = 0.774597;
		especular[1] = 0.774597;
		especular[2] = 0.774597;
		especular[3] = 1;
		brillo = 76.8;
		break;
	case COBRE:
		ambiente[0] = 0.19125;
		ambiente[1] = 0.0735;
		ambiente[2] = 0.0225;
		ambiente[3] = 1.0;
		difusa[0] = 0.7038;
		difusa[1] = 0.27048;
		difusa[2] = 0.0828;
		difusa[3] = 1;
		especular[0] = 0.256777;
		especular[1] = 0.137622;
		especular[2] = 0.086014;
		especular[3] = 1;
		brillo = 12.8;
		break;
	case COBRE_PULIDO:
		ambiente[0] = 0.2295;
		ambiente[1] = 0.08825;
		ambiente[2] = 0.0275;
		ambiente[3] = 1.0;
		difusa[0] = 0.5508;
		difusa[1] = 0.2118;
		difusa[2] = 0.066;
		difusa[3] = 1;
		especular[0] = 0.580594;
		especular[1] = 0.223257;
		especular[2] = 0.0695701;
		especular[3] = 1;
		brillo = 51.2;
		break;
	case ORO:
		ambiente[0] = 0.24725;
		ambiente[1] = 0.1995;
		ambiente[2] = 0.0745;
		ambiente[3] = 1.0;
		difusa[0] = 0.75164;
		difusa[1] = 0.60648;
		difusa[2] = 0.22648;
		difusa[3] = 1;
		especular[0] = 0.628281;
		especular[1] = 0.555802;
		especular[2] = 0.366065;
		especular[3] = 1;
		brillo = 51.2;
		break;
	case ORO_PULIDO:
		ambiente[0] = 0.24725;
		ambiente[1] = 0.2245;
		ambiente[2] = 0.0645;
		ambiente[3] = 1.0;
		difusa[0] = 0.34615;
		difusa[1] = 0.3143;
		difusa[2] = 0.0903;
		difusa[3] = 1;
		especular[0] = 0.797357;
		especular[1] = 0.723991;
		especular[2] = 0.208006;
		especular[3] = 1;
		brillo = 51.2;
		break;
	case PELTRE:
		ambiente[0] = 0.105882;
		ambiente[1] = 0.058824;
		ambiente[2] = 0.113725;
		ambiente[3] = 1.0;
		difusa[0] = 0.427451;
		difusa[1] = 0.470588;
		difusa[2] = 0.541176;
		difusa[3] = 1;
		especular[0] = 0.333333;
		especular[1] = 0.333333;
		especular[2] = 0.521569;
		especular[3] = 1;
		brillo = 9.84615;
		break;
	case PLATA:
		ambiente[0] = 0.19225;
		ambiente[1] = 0.19225;
		ambiente[2] = 0.19225;
		ambiente[3] = 1.0;
		difusa[0] = 0.2775;
		difusa[1] = 0.2775;
		difusa[2] = 0.2775;
		difusa[3] = 1;
		especular[0] = 0.773911;
		especular[1] = 0.773911;
		especular[2] = 0.773911;
		especular[3] = 1;
		brillo = 51.2;
		break;
	case PLATA_PULIDA:
		ambiente[0] = 0.23125;
		ambiente[1] = 0.23125;
		ambiente[2] = 0.23125;
		ambiente[3] = 1.0;
		difusa[0] = 0.2775;
		difusa[1] = 0.2775;
		difusa[2] = 0.2775;
		difusa[3] = 1;
		especular[0] = 0.773911;
		especular[1] = 0.773911;
		especular[2] = 0.773911;
		especular[3] = 1;
		brillo = 89.6;
		break;
	case ESMERALDA:
		ambiente[0] = 0.0215;
		ambiente[1] = 0.1745;
		ambiente[2] = 0.0215;
		ambiente[3] = 0.55;
		difusa[0] = 0.07568;
		difusa[1] = 0.61424;
		difusa[2] = 0.07568;
		difusa[3] = 0.55;
		especular[0] = 0.633;
		especular[1] = 0.727811;
		especular[2] = 0.633;
		especular[3] = 0.55;
		brillo = 76.8;
		break;
	case JADE:
		ambiente[0] = 0.135;
		ambiente[1] = 0.2225;
		ambiente[2] = 0.1575;
		ambiente[3] = 0.95;
		difusa[0] = 0.54;
		difusa[1] = 0.89;
		difusa[2] = 0.63;
		difusa[3] = 0.95;
		especular[0] = 0.316228;
		especular[1] = 0.316228;
		especular[2] = 0.316228;
		especular[3] = 0.95;
		brillo = 12.8;
		break;
	case OBSIDIANA:
		ambiente[0] = 0.05375;
		ambiente[1] = 0.05;
		ambiente[2] = 0.06625;
		ambiente[3] = 0.82;
		difusa[0] = 0.18275;
		difusa[1] = 0.17;
		difusa[2] = 0.22525;
		difusa[3] = 0.82;
		especular[0] = 0.332741;
		especular[1] = 0.328634;
		especular[2] = 0.346435;
		especular[3] = 0.82;
		brillo = 38.4;
		break;
	case PERLA:
		ambiente[0] = 0.25;
		ambiente[1] = 0.20725;
		ambiente[2] = 0.20725;
		ambiente[3] = 0.922;
		difusa[0] = 1;
		difusa[1] = 0.829;
		difusa[2] = 0.829;
		difusa[3] = 0.922;
		especular[0] = 0.296648;
		especular[1] = 0.296648;
		especular[2] = 0.296648;
		especular[3] = 0.922;
		brillo = 11.264;
		break;
	case RUBI:
		ambiente[0] = 0.1745;
		ambiente[1] = 0.01175;
		ambiente[2] = 0.01175;
		ambiente[3] = 0.55;
		difusa[0] = 0.61424;
		difusa[1] = 0.04136;
		difusa[2] = 0.04136;
		difusa[3] = 0.55;
		especular[0] = 0.727811;
		especular[1] = 0.626959;
		especular[2] = 0.626959;
		especular[3] = 0.55;
		brillo = 76.8;
		break;
	case TURQUESA:
		ambiente[0] = 0.1;
		ambiente[1] = 0.18725;
		ambiente[2] = 0.1745;
		ambiente[3] = 0.8;
		difusa[0] = 0.396;
		difusa[1] = 0.74151;
		difusa[2] = 0.69102;
		difusa[3] = 0.8;
		especular[0] = 0.297254;
		especular[1] = 0.30829;
		especular[2] = 0.306678;
		especular[3] = 0.8;
		brillo = 12.8;
		break;
	case PLASTICO_NEGRO:
		ambiente[0] = 0.0;
		ambiente[1] = 0.0;
		ambiente[2] = 0.0;
		ambiente[3] = 1.0;
		difusa[0] = 0.01;
		difusa[1] = 0.01;
		difusa[2] = 0.01;
		difusa[3] = 1;
		especular[0] = 0.5;
		especular[1] = 0.5;
		especular[2] = 5.366065;
		especular[3] = 1;
		brillo = 32;
		break;
	case CAUCHO_NEGRO:
		ambiente[0] = 0.02;
		ambiente[1] = 0.02;
		ambiente[2] = 0.02;
		ambiente[3] = 1.0;
		difusa[0] = 0.01;
		difusa[1] = 0.01;
		difusa[2] = 0.01;
		difusa[3] = 1;
		especular[0] = 0.4;
		especular[1] = 0.4;
		especular[2] = 0.4;
		especular[3] = 1;
		brillo = 10;
		break;
	}
}

//Examen lampara
//GLLIGHTTWO SIDES
//a2.cross_product(a1); para cruzar el vector
