/*********************************************************
Materia: Gr�ficas Computacionales
Fecha: 16 de septiembre del 2017
Autor: A01169073 Aldo A. Reyna G�mez
*********************************************************/

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <glm/glm.hpp>
#include "glm/gtx/string_cast.hpp"
#include <vector>

#include "Mesh.h"
#include "ShaderProgram.h"	
#include "Transform.h"
#include "Camera.h"

using namespace std;
using namespace glm;

// Identificador del manager al que vamos a asociar todos los VBOs que tenga nuestra geometr�a
unique_ptr<Mesh> mesh(new Mesh);
// Identificador del manager de los shaders (shaderProgram)
unique_ptr<ShaderProgram> shaderProgram(new ShaderProgram);
unique_ptr<Transform> geometria1(new Transform); // Geometr�a 1
unique_ptr<Transform> geometria2(new Transform); // Geometr�a 2
unique_ptr<Camera> camara(new Camera);

// Identificador del manager al que vamos a asociar todos los VBOs que tenga nuestra geometr�a
GLuint vao;

// Identificador del manager de los shaders (shaderProgramme)
// GLuint shaderProgram;

float pos = 0.0; // �ndice para la trayectoria del c�rculo de la geometr�a1
float deltaCirculo = 0.01f;
float inc = 0.0; // Incremento en la escala de la geometr�a2
float deltaEscala = 0.00005f;
double colour = 0.0; // Color de fondo

void Initialise() {
	vector<vec3> positions;
	vector<vec3> colors;

	/*float arr[6] = { 18.f, 306.f, 234.f, 162.f, 90.f, 18.f };
	for (int i = 0; i < 6; i++) {
	positions.push_back(vec2(cos(radians(arr[i])), sin(radians(arr[i]))));
	colors.push_back(vec3(0.0f, 0.0f, 1.0f));
	positions.push_back(vec2(0.5*cos(radians(arr[i])), 0.5*sin(radians(arr[i]))));
	colors.push_back(vec3(1.0f, 0.0f, 0.0f));
	}*/

	/*
	// Cara frontal
	positions.push_back(vec3(-3.0f, -3.0f, 3.0f));
	positions.push_back(vec3(3.0f, -3.0f, 3.0f));
	positions.push_back(vec3(3.0f, 3.0f, 3.0f));
	positions.push_back(vec3(-3.0f, 3.0f, 3.0f));
	colors.push_back(vec3(0.0f, 1.0f, 0.0f));
	colors.push_back(vec3(0.0f, 1.0f, 0.0f));
	colors.push_back(vec3(0.0f, 1.0f, 0.0f));
	colors.push_back(vec3(0.0f, 1.0f, 0.0f));

	// Cara lateral derecha
	positions.push_back(vec3(3.0f, 3.0f, 3.0f));
	positions.push_back(vec3(3.0f, 3.0f, -3.0f));
	positions.push_back(vec3(3.0f, -3.0f, -3.0f));
	positions.push_back(vec3(3.0f, -3.0f, 3.0f));
	colors.push_back(vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(vec3(1.0f, 0.0f, 0.0f));

	// Cara trasera
	positions.push_back(vec3(-3.0f, -3.0f, -3.0f));
	positions.push_back(vec3(3.0f, -3.0f, -3.0f));
	positions.push_back(vec3(3.0f, 3.0f, -3.0f));
	positions.push_back(vec3(-3.0f, 3.0f, -3.0f));
	colors.push_back(vec3(0.0f, 0.0f, 1.0f));
	colors.push_back(vec3(0.0f, 0.0f, 1.0f));
	colors.push_back(vec3(0.0f, 0.0f, 1.0f));
	colors.push_back(vec3(0.0f, 0.0f, 1.0f));

	// Cara lateral izquierda
	positions.push_back(vec3(-3.0f, -3.0f, -3.0f));
	positions.push_back(vec3(-3.0f, -3.0f, 3.0f));
	positions.push_back(vec3(-3.0f, 3.0f, 3.0f));
	positions.push_back(vec3(-3.0f, 3.0f, -3.0f));
	colors.push_back(vec3(1.0f, 0.5f, 0.0f));
	colors.push_back(vec3(1.0f, 0.5f, 0.0f));
	colors.push_back(vec3(1.0f, 0.5f, 0.0f));
	colors.push_back(vec3(1.0f, 0.5f, 0.0f));

	// Cara superior
	positions.push_back(vec3(3.0f, 3.0f, 3.0f));
	positions.push_back(vec3(-3.0f, 3.0f, 3.0f));
	positions.push_back(vec3(-3.0f, 3.0f, -3.0f));
	positions.push_back(vec3(3.0f, 3.0f, -3.0f));
	colors.push_back(vec3(1.0f, 1.0f, 1.0f));
	colors.push_back(vec3(1.0f, 1.0f, 1.0f));
	colors.push_back(vec3(1.0f, 1.0f, 1.0f));
	colors.push_back(vec3(1.0f, 1.0f, 1.0f));

	// Cara inferior
	positions.push_back(vec3(-3.0f, -3.0f, -3.0f));
	positions.push_back(vec3(3.0f, -3.0f, -3.0f));
	positions.push_back(vec3(3.0f, -3.0f, 3.0f));
	positions.push_back(vec3(-3.0f, -3.0f, 3.0f));
	colors.push_back(vec3(1.0f, 1.0f, 0.0f));
	colors.push_back(vec3(1.0f, 1.0f, 0.0f));
	colors.push_back(vec3(1.0f, 1.0f, 0.0f));
	colors.push_back(vec3(1.0f, 1.0f, 0.0f));

	vector<unsigned int> indices = {
		0, 1, 2, 0, 2, 3, // Frontal
		4, 5, 6, 4, 6, 7, // Derecha
		8, 9, 10, 8, 10, 11, // Trasera
		12, 13, 14, 12, 14, 15, // Izquierda
		16, 17, 18, 16, 18, 19, // Superior
		20, 21, 22, 20, 22, 23 // Inferior
	};
	*/

	/*
	// Cara frontal
	positions.push_back(vec3(-3.0f, -3.0f, 3.0f));
	positions.push_back(vec3(3.0f, -3.0f, 3.0f));
	positions.push_back(vec3(3.0f, 3.0f, 3.0f));
	positions.push_back(vec3(-3.0f, 3.0f, 3.0f));
	colors.push_back(vec3(0.0f, 1.0f, 0.0f));
	colors.push_back(vec3(0.0f, 1.0f, 0.0f));
	colors.push_back(vec3(0.0f, 1.0f, 0.0f));
	colors.push_back(vec3(0.0f, 1.0f, 0.0f));

	// Cara lateral derecha
	positions.push_back(vec3(3.0f, 3.0f, 3.0f));
	positions.push_back(vec3(3.0f, 3.0f, -3.0f));
	positions.push_back(vec3(3.0f, -3.0f, -3.0f));
	positions.push_back(vec3(3.0f, -3.0f, 3.0f));
	colors.push_back(vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(vec3(1.0f, 0.0f, 0.0f));

	// Cara trasera
	positions.push_back(vec3(-3.0f, -3.0f, -3.0f));
	positions.push_back(vec3(3.0f, -3.0f, -3.0f));
	positions.push_back(vec3(3.0f, 3.0f, -3.0f));
	positions.push_back(vec3(-3.0f, 3.0f, -3.0f));
	colors.push_back(vec3(0.0f, 0.0f, 1.0f));
	colors.push_back(vec3(0.0f, 0.0f, 1.0f));
	colors.push_back(vec3(0.0f, 0.0f, 1.0f));
	colors.push_back(vec3(0.0f, 0.0f, 1.0f));

	// Cara lateral izquierda
	positions.push_back(vec3(-3.0f, -3.0f, -3.0f));
	positions.push_back(vec3(-3.0f, -3.0f, 3.0f));
	positions.push_back(vec3(-3.0f, 3.0f, 3.0f));
	positions.push_back(vec3(-3.0f, 3.0f, -3.0f));
	colors.push_back(vec3(1.0f, 0.5f, 0.0f));
	colors.push_back(vec3(1.0f, 0.5f, 0.0f));
	colors.push_back(vec3(1.0f, 0.5f, 0.0f));
	colors.push_back(vec3(1.0f, 0.5f, 0.0f));

	// Cara superior
	positions.push_back(vec3(3.0f, 3.0f, 3.0f));
	positions.push_back(vec3(-3.0f, 3.0f, 3.0f));
	positions.push_back(vec3(-3.0f, 3.0f, -3.0f));
	positions.push_back(vec3(3.0f, 3.0f, -3.0f));
	colors.push_back(vec3(1.0f, 1.0f, 1.0f));
	colors.push_back(vec3(1.0f, 1.0f, 1.0f));
	colors.push_back(vec3(1.0f, 1.0f, 1.0f));
	colors.push_back(vec3(1.0f, 1.0f, 1.0f));

	// Cara inferior
	positions.push_back(vec3(-3.0f, -3.0f, -3.0f));
	positions.push_back(vec3(3.0f, -3.0f, -3.0f));
	positions.push_back(vec3(3.0f, -3.0f, 3.0f));
	positions.push_back(vec3(-3.0f, -3.0f, 3.0f));
	colors.push_back(vec3(1.0f, 1.0f, 0.0f));
	colors.push_back(vec3(1.0f, 1.0f, 0.0f));
	colors.push_back(vec3(1.0f, 1.0f, 0.0f));
	colors.push_back(vec3(1.0f, 1.0f, 0.0f));

	vector<unsigned int> indices = {
		0, 1, 2, 0, 2, 3, // Frontal
		4, 5, 6, 4, 6, 7, // Derecha
		8, 9, 10, 8, 10, 11, // Trasera
		12, 13, 14, 12, 14, 15, // Izquierda
		16, 17, 18, 16, 18, 19, // Superior
		20, 21, 22, 20, 22, 23 // Inferior
	};
	*/

	vector<vec3> positionsPyramid;
	vector<vec3> colorsPyramid;

	// Cara frontal
	positionsPyramid.push_back(vec3(-1.0f, -1.0f, -1.0f));		//0
	positionsPyramid.push_back(vec3(-1.0f, -1.0f, 1.0f));		//1
	positionsPyramid.push_back(vec3(1.0f, -1.0f, 1.0f));		//2
	positionsPyramid.push_back(vec3(1.0f, -1.0f, -1.0f));		//3
	positionsPyramid.push_back(vec3(0.0f, 1.0f, 0.0f));			//4
	colorsPyramid.push_back(vec3(1.0f, 0.0f, 0.0f));
	colorsPyramid.push_back(vec3(0.0f, 1.0f, 0.0f));
	colorsPyramid.push_back(vec3(0.0f, 0.0f, 1.0f));
	colorsPyramid.push_back(vec3(1.0f, 1.0f, 0.0f));
	colorsPyramid.push_back(vec3(0.0f, 1.0f, 1.0f));

	vector<unsigned int> indicesPyramid = {
		0, 1, 2, 0, 2, 3,
		0, 1, 4, 1, 2, 4,
		2, 3, 4, 3, 0, 4
	};

	mesh->CreateMesh(positionsPyramid.size());
	mesh->SetPositionAttribute(positionsPyramid, GL_STATIC_DRAW, 0);
	mesh->SetColorAttribute(colorsPyramid, GL_STATIC_DRAW, 1);
	mesh->SetIndices(indicesPyramid, GL_STATIC_DRAW);

	/*/
	// Queremos gengerar 1 manager
	glGenVertexArrays(1, &vao);
	// Utilizar el vao
	// A partir de este momento, todos los VBOs creados y configurados se van a asociar a este manager
	glBindVertexArray(vao);

	// Tipo de dato de OpenGL entero sin signo multiplataforma
	// Empezamos a crear bufers (identificador de VBO de posiciones)
	GLuint positionsVBO;
	// Creaci�n del VBO de posiciones lo guarda en positionsVBO y da un identificador para utilizarlo
	glGenBuffers(1, &positionsVBO);
	// Activamos el buffer de posiciones para poder utilizarlo, este buffer ES UN ATRIBUTO (GL ARRAY BUFFER)
	glBindBuffer(GL_ARRAY_BUFFER, positionsVBO);
	// Creamos la memoria y la inicializamos con los datos del atributo de posiciones
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec2)*positions.size(), positions.data(), GL_STATIC_DRAW);
	// Activamos el atributo en la tarjeta de video
	glEnableVertexAttribArray(0);
	// Configuramos los datos del atributo en la tarjeta de video
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	// Ya no vamos a utilizar este Vertex Buffer Object en este momento
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLuint colorsVBO;
	glGenBuffers(1, &colorsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3)*colors.size(), colors.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0);*/

	/*
	// Creamos un objeto para leer archivos
	InputFile myfile;

	// VERTEX SHADER
	// Leemos el archivo Default.vert donde est� el c�digo del vertex shader.
	myfile.Read("Default.vert");
	// Obtenemos el c�digo fuente y lo guardamos en un string
	string vertexSource = myfile.GetContents();
	// Creamos un shader de tipo vertex guardamos su identificador en una variable
	GLuint vertexShaderHandle =
	glCreateShader(GL_VERTEX_SHADER);
	// Obtener los datos en el formato correcto: Vil Cast
	const GLchar *vertexSource_c =
	(const GLchar*)vertexSource.c_str();
	// Le estamos dando el c�digo fuente a OpenGL para que se los asigne al shader
	glShaderSource(vertexShaderHandle, 1, &vertexSource_c, nullptr);
	// Compilamos el shader en busca de errores.
	// Vamos a asumir que no hay ning�n error.
	glCompileShader(vertexShaderHandle);

	myfile.Read("Default.frag");
	string fragmentSource = myfile.GetContents();
	GLuint fragmentShaderHandle =
	glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar *fragmentSource_c =
	(const GLchar*)fragmentSource.c_str();
	// Continuar leyendo hasta que encuentre un nullptr
	glShaderSource(fragmentShaderHandle, 1, &fragmentSource_c, nullptr);
	glCompileShader(fragmentShaderHandle);*/

	shaderProgram->CreateProgram();
	shaderProgram->AttachShader("Default.vert", GL_VERTEX_SHADER);
	shaderProgram->AttachShader("Default.frag", GL_FRAGMENT_SHADER);
	shaderProgram->SetAttribute(0, "VertexPosition");
	shaderProgram->SetAttribute(1, "VertexColor");
	shaderProgram->LinkProgram();

	// El cubo del piso
	//transform1->SetRotation(90.0f, 0.0f, 0.0f);
	//transform1->SetScale(2.0f, 0.001f, 1.0f);
	//transform1->SetPosition(0.0f, -8.0f, 12.0f);


	//camara->SetPosition(0.0f, 0.0f, 0.0f); // C�mara en el origen
	//camara->SetOrthographic(2.0f, 1.0f);
	//camara->SetPerspective(-2.0f, -4.0f, 4.0f, 1.0f);
	//camara->SetPerspective(0.7f, 1000.0f, 60.0f, 1.0f);
	//camara->SetRotation(90.0f, 0, 0);
	
	

	// Cambio de escala de la geometr�a1 a 3 veces su tama�o original en los 3 ejes
	geometria1->SetScale(3, 3, 3);

	// Inicialmente la geometr�a2 empieza con una escala de 0.5
	geometria2->SetScale(0.5f, 0.5f, 0.5f);
	// La posici�n de la geometr�a2 siempre est� en (0,0,0)
	geometria2->SetPosition(0, 0, 0);

	// Colocando la c�mara en (0, 0, 25) para visualizar correctamente las dos geometr�as
	camara->SetPosition(0, 0, 25.0f);
	//camara->MoveForward(24.0f);

	/*
	// Regresa el identificador de este manager
	// Creamos el identificador para el manager de los shaders
	shaderProgram = glCreateProgram();
	// Adjuntamos el vertex shader del manager (van a trabajar juntos)
	glAttachShader(shaderProgram, vertexShaderHandle);
	// Adjuntamos el fragment shader al manager (van a trabajar juntos)
	glAttachShader(shaderProgram, fragmentShaderHandle);
	// Asociamos un buffer con �ndice 0 (posiciones) a la variable VertexPosition
	glBindAttribLocation(shaderProgram, 0, "VertexPosition");
	// Asociamos un buffer con �ndice 1 (colores) a la variable VertexColor
	glBindAttribLocation(shaderProgram, 1, "VertexColor");
	// Ejecutamos el proceso de linker (asegurarnos que el vertex y fragment son compatibles)
	glLinkProgram(shaderProgram);*/
}

void GameLoop() {
	// Siempre hacerlo al inicio del frame!
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Geometr�a1 rota en sus tres ejes coordenados
	geometria1->Rotate(0.03f, 0.015f, 0.03f, false);
	// Geometr�a1 sigue una trayectoria circular en el plano XY
	geometria1->SetPosition(5 * cos(radians(pos)), 5 * sin(radians(pos)), 0);
	pos += deltaCirculo;

	// Geometr�a2 rota en sus tres ejes coordenados, pero en sentido contrario
	geometria2->Rotate(-0.03f, -0.015f, -0.03f, false);

	// Incrementar la escala de la geometr�a2 en el rango de 0.25 -> 1.0
	geometria2->SetScale(0.5f + inc, 0.5f + inc, 0.5f + inc);
	if (geometria2->GetScale().x <= 0.25f || geometria2->GetScale().x >= 1.0f) {
		deltaEscala *= -1.0f;
	}
	inc += deltaEscala;

	shaderProgram->Activate();
	// Dibujado de geometr�a1
	shaderProgram->SetUniformMatrix("mvpMatrix", camara->GetViewProjection()*geometria1->GetModelMatrix());
	mesh->Draw(GL_TRIANGLES);
	// Dibujado de geometr�a2
	shaderProgram->SetUniformMatrix("mvpMatrix", camara->GetViewProjection()*geometria2->GetModelMatrix());
	mesh->Draw(GL_TRIANGLES);

	shaderProgram->Deactivate();


	/*
	// Activamos el vertexShader y el fragmentShader utilizando el manager
	//glUseProgram(shaderProgram);

	// Activamos el manager y en este momento se activan todos los VBOs asociados autom�ticamente
	//glBindVertexArray(vao);

	//glDrawArrays(GL_TRIANGLE_STRIP, 0, 12);ime

	// Terminamos de utilizar el manager
	//glBindVertexArray(0);

	// Desactivamos el manager
	//glUseProgram(0);
	*/

	//Cuando terminamos de renderear, cambiamos los buffers
	glutSwapBuffers();

	// Cambiando la tonalidad del fondo
	colour += 0.01f;
	glClearColor(0.5 + 0.5*cos(radians(colour)), 0.5 + 0.5*sin(radians(colour)), sin(radians(colour))*cos(radians(colour)), 1.0f);
}

// Funci�n que mueve la c�mara dependiendo de la tecla presionada
void Keyboard(unsigned char key, int x, int y) {
	if (key == 'w')
		camara->MoveForward(0.1f, false);
	if (key == 's')
		camara->MoveForward(-0.1f, false);
	if (key == 'd')
		camara->MoveRight(0.1f, false);
	if (key == 'a')
		camara->MoveRight(-0.1f, false);
}

void SpecialKeys(int key, int x, int y) {
	if (key == GLUT_KEY_UP)
		camara->MoveForward(0.1f, false);
	if (key == GLUT_KEY_DOWN)
		camara->MoveForward(-0.1f, false);
	if (key == GLUT_KEY_RIGHT)
		camara->Rotate(0.0f, 4.0f, 0.0f, true);
	if (key == GLUT_KEY_LEFT)
		camara->Rotate(0.0f, -4.0f, 0.0f, true);
}

void Idle() {
	// Cuando OpenGL entra en modo Idle o de resposo (para guardar bater�a, por ejemplo)}
	// le decimos que vuelva a dibujar => vuelve a mandar a llamar GameLoop
	glutPostRedisplay();
}

void ReshapeWindow(int width, int height) {
	// Para configurar un uniform, tenemos que decirle a OpenGL que vamos a utilizar el shader program (manager)
	glViewport(0, 0, width, height);
	//shProgram.SetUniform("Resolution", width, height);
}

int main(int argc, char* argv[]) {
	// Inicializar freeglut
	// Freeglut se encargfa de crear una ventana en donde podemos dibujar Gr�ficas Computacionales
	glutInit(&argc, argv);
	glutInitContextVersion(4, 4);


	// Iniciar el contexto de OpenGL, se refiere a las capacidades de la aplicaci�n gr�fica
	// En este caso se trabaja con el pipeline progamable
	glutInitContextProfile(GLUT_CORE_PROFILE);

	// Freeglut nos permite configurar eventos que ocurren en la ventana
	// Un evento que interesa es cuando alguien cierra la centana
	// En este caso, se deja de renderear la escena y se termina el programa
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	// Tambi�n configuramos frambuffer, en este caso solicitamos un buffer
	// true color RGBA, un buffer de produndidad y un segundo buffer para renderear
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE); // Dos framebuffers

	// Iniciar las dimensiones de la ventana (en pixeles)
	glutInitWindowSize(400, 400);

	// Creeamos la ventana y le damos un t�tulo.
	glutCreateWindow("T�tulo S�per Cool GL");

	glutDisplayFunc(GameLoop);

	// Asociamos una funci�n para el cambio de la resoluci�n de la ventana
	// FreeGlut la va a mandar a llamar cuando alguien cambie el tama�o de la ventana
	glutReshapeFunc(ReshapeWindow);

	// Cuando OpenGL entre en modo de reposo
	glutIdleFunc(Idle);

	// Avisar que existen la funciones que detectan el teclado
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeys);

	// Inicializamos GLEW. Esta librer�a se encarga de obtener el API de OpenGL de nuestra tarjeta de video
	glewInit();

	// Configurar OpenGl. Este es el color por dedault del buffer de color en el framebuffer.
	glClearColor(1.0f, 1.0f, 0.5f, 1.0f);
	// Ademas de solicitar el buffer de profundidad, tenemos
	// que decirle a OpenGL que lo queremos activo
	glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);
	// Activamos el borrado de caras traseras.
	// Ahora todos los triangulos que dibujemos deben estar en CCW
	//glEnable(GL_CULL_FACE);
	// No dibujar las caras traseras de las geometr�as.
	//glCullFace(GL_BACK);
	//glFrontFace(GL_CW);

	cout << glGetString(GL_VERSION) << endl;

	// Configuraci�n inicial de nuestro programa
	Initialise();

	// Iniciar la aplicaci�n. El Main se pausar� en esta l�nea hasta que se cierre la ventana.
	glutMainLoop();

	return 0;
}
