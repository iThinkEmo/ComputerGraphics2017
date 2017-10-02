/*********************************************************
Materia: Gr�ficas Computacionales
Fecha: 2 de octubre del 2017
Autor: A01169073 Aldo A. Reyna G�mez
*********************************************************/

#pragma once
#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

class Mesh {
public:
	Mesh();
	~Mesh();
	void CreateMesh(GLint vertexCount);
	void Draw(GLenum primitive);
	void SetPositionAttribute(vector<vec2> positions, GLenum usage, GLuint locationIndex);
	void SetPositionAttribute(vector<vec3> positions, GLenum usage, GLuint locationIndex);
	void SetColorAttribute(vector<vec3> colors, GLenum usage, GLuint locationIndex);
	void SetColorAttribute(vector<vec4> colors, GLenum usage, GLuint locationIndex);

private:
	GLuint vao;
	GLuint positionsVBO;
	GLuint colorsVBO;
	GLint _vertexCount;
	void SetAttributeData(GLuint& buffer, const GLsizeiptr size, const void* data, GLenum usage,
		GLuint locationIndex, const GLint components);
};