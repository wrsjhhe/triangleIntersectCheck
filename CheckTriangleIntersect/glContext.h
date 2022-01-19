#pragma once
#include <vector>

#define GLFW_INCLUDE_NONE
#include "glfw3.h"
#include "linmath.h"

typedef struct GLVertex
{
	vec3 pos;
	vec3 col;

	GLVertex& operator=(const GLVertex& other)
	{
		this->pos[0] = other.pos[0];
		this->pos[1] = other.pos[1];
		this->pos[2] = other.pos[2];

		this->col[0] = other.col[0];
		this->col[1] = other.col[1];
		this->col[2] = other.col[2];

		return *this;
	}
};
typedef unsigned int GLuint;
class GLContext
{
public:
	GLContext();
	~GLContext();

	void UpdateVertices(const std::vector<GLVertex>& vertices);

	void Draw();

	void Exit();
private:
	GLFWwindow* m_window;
	GLuint m_program;
	GLuint m_vertex_buffer;
	GLuint m_vertex_array;
	GLVertex m_vertices[6];
};