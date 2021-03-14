#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <shader.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

struct Color
{
	float r = 0.0f, g = 0.0f, b = 0.0f;
	Color(int hexValue)
	{
		r = ((hexValue >> 16) & 0xFF) / 255.0f;
		g = ((hexValue >> 8) & 0xFF) / 255.0f;
		b = ((hexValue) & 0xFF) / 255.0f;
	}
};

Color palette[]{
  Color(0x7eed94),
  Color(0x1a2c79),
  Color(0xe6a26e),
  Color(0x64a6ea),
  Color(0xa163a2),
};

void setClearColor(Color color)
{
	glClearColor(color.r, color.g, color.b, 1.0f);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		setClearColor(palette[0]);

	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		setClearColor(palette[1]);

	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		setClearColor(palette[2]);

	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
		setClearColor(palette[3]);

	if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
		setClearColor(palette[4]);
}

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "GenevaEngine", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// create shader program
	Shader shaderProgram("Shaders\\shader_vs.glsl", "Shaders\\shader_fs.glsl");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float verticies[] = {
	-0.2f, -0.4f, 0.0f, 1.0f,
	-0.2f, 0.8f, 0.0f, 2.0f,
	-0.8f, -0.2f, 0.0f,3.0f,
	-0.1f, 0.9f, 0.0f, 1.0f,
	0.9f, 0.9f, 0.0f, 2.0f,
	0.9f, -0.1f, 0.0f, 3.0f,
	};

	unsigned int VBO[2], VAO[2];
	glGenBuffers(2, VBO);
	glGenVertexArrays(2, VAO);

	for (int i = 0; i < 2; i++)
	{
		/*
			bind the Vertex Array Object first, then bind and set vertex buffer(s),
			and then configure vertex attributes(s).
		*/
		glBindVertexArray(VAO[i]);
		// copy our vertices array in a vertex buffer for OpenGL to use
		glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);
		// then set the vertex attributes pointers
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}

	// draw in wireframe polygons
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);

		// render
		// ------
		glClear(GL_COLOR_BUFFER_BIT);
		shaderProgram.use();
		// update the uniform color
		float timeValue = glfwGetTime();
		float rgbValue1 = sin(timeValue + 2.09f) + 0.5f;
		float rgbValue2 = sin(timeValue + 4.18f) + 0.5f;
		float rgbValue3 = sin(timeValue) + 0.5f;
		int vertexColorLocation1 = glGetUniformLocation(shaderProgram.ID, "color1");
		glUniform4f(vertexColorLocation1, rgbValue1, rgbValue2, rgbValue3, 1.0f);
		int vertexColorLocation2 = glGetUniformLocation(shaderProgram.ID, "color2");
		glUniform4f(vertexColorLocation2, rgbValue3, rgbValue1, rgbValue2, 1.0f);
		int vertexColorLocation3 = glGetUniformLocation(shaderProgram.ID, "color3");
		glUniform4f(vertexColorLocation3, rgbValue2, rgbValue3, rgbValue1, 1.0f);
		// draw our rectangles
		for (int i = 0; i < 2; i++)
		{
			int startVert = i * 3;
			glBindVertexArray(VAO[i]);
			glDrawArrays(GL_TRIANGLES, startVert, 3);
		}

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(2, VAO);
	glDeleteBuffers(2, VBO);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}