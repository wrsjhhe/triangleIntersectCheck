#define GLAD_GL_IMPLEMENTATION
#include "gl.h"

#include "glContext.h"
static const char* vertex_shader_text =
"#version 330\n"
"uniform mat4 MVP;\n"
"in vec3 vCol;\n"
"in vec3 vPos;\n"
"out vec3 color;\n"
"void main()\n"
"{\n"
"    gl_Position = MVP * vec4(vPos, 1.0);\n"
"    color = vCol;\n"
"}\n";

static const char* fragment_shader_text =
"#version 330\n"
"in vec3 color;\n"
"out vec4 fragment;\n"
"void main()\n"
"{\n"
"    fragment = vec4(color, 1.0);\n"
"}\n";

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);

}
GLContext::GLContext()
{
	if (!glfwInit())
		exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(640, 480, "Check Triangle", NULL, NULL);
	if (!m_window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetKeyCallback(m_window, key_callback);

	glfwMakeContextCurrent(m_window);
	gladLoadGL(glfwGetProcAddress);
	glfwSwapInterval(1);

	const GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
	glCompileShader(vertex_shader);

	const GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
	glCompileShader(fragment_shader);

	m_program = glCreateProgram();
	glAttachShader(m_program, vertex_shader);
	glAttachShader(m_program, fragment_shader);
	glLinkProgram(m_program);

	glEnable(GL_DEPTH_TEST);

	glGenBuffers(1, &m_vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);

	const GLint vpos_location = glGetAttribLocation(m_program, "vPos");
	const GLint vcol_location = glGetAttribLocation(m_program, "vCol");

	glGenVertexArrays(1, &m_vertex_array);
	glBindVertexArray(m_vertex_array);
	glEnableVertexAttribArray(vpos_location);
	glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE,
		sizeof(GLVertex), (void*)offsetof(GLVertex, pos));
	glEnableVertexAttribArray(vcol_location);
	glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
		sizeof(GLVertex), (void*)offsetof(GLVertex, col));
}

GLContext::~GLContext()
{

}


void GLContext::UpdateVertices(const std::vector<GLVertex>& vertices)
{
	for (int i = 0; i < vertices.size(); ++i)
	{
		m_vertices[i] = vertices.at(i);
	}
	glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(m_vertices), m_vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GLContext::Draw()
{
	if (!glfwWindowShouldClose(m_window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDepthFunc(GL_LEQUAL);  // ÉèÖÃÉî¶È»º´æ

		int width, height;
		glfwGetFramebufferSize(m_window, &width, &height);
		const float ratio = width / (float)height;

		glViewport(0, 0, width, height);

		mat4x4 m, p, mvp;
		mat4x4_identity(m);
		mat4x4_rotate_Y(m, m, (float)glfwGetTime());
		//mat4x4_rotate_Z(m, m, (float) glfwGetTime());
		mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
		mat4x4_mul(mvp, p, m);

		const GLint mvp_location = glGetUniformLocation(m_program, "MVP");

		glUseProgram(m_program);
		glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*)&mvp);
		glBindVertexArray(m_vertex_array);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}
}

void GLContext::Exit()
{
	glfwDestroyWindow(m_window);

	glfwTerminate();
}
