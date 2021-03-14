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
const int triangleCount = 1;

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
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  1.0f,
		 0.5f, -0.5f, -0.5f,  2.0f,
		 0.5f,  0.5f, -0.5f,  3.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,
		-0.5f,  0.5f, -0.5f,  2.0f,
		-0.5f, -0.5f, -0.5f,  3.0f,

		-0.5f, -0.5f,  0.5f,  1.0f,
		 0.5f, -0.5f,  0.5f,  2.0f,
		 0.5f,  0.5f,  0.5f,  3.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,
		-0.5f,  0.5f,  0.5f,  2.0f,
		-0.5f, -0.5f,  0.5f,  3.0f,

		-0.5f,  0.5f,  0.5f,  1.0f,
		-0.5f,  0.5f, -0.5f,  2.0f,
		-0.5f, -0.5f, -0.5f,  3.0f,
		-0.5f, -0.5f, -0.5f,  1.0f,
		-0.5f, -0.5f,  0.5f,  2.0f,
		-0.5f,  0.5f,  0.5f,  3.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,
		 0.5f,  0.5f, -0.5f,  2.0f,
		 0.5f, -0.5f, -0.5f,  3.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,
		 0.5f, -0.5f,  0.5f,  2.0f,
		 0.5f,  0.5f,  0.5f,  3.0f,

		-0.5f, -0.5f, -0.5f,  1.0f,
		 0.5f, -0.5f, -0.5f,  2.0f,
		 0.5f, -0.5f,  0.5f,  3.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,
		-0.5f, -0.5f,  0.5f,  2.0f,
		-0.5f, -0.5f, -0.5f,  3.0f,

		-0.5f,  0.5f, -0.5f,  1.0f,
		 0.5f,  0.5f, -0.5f,  2.0f,
		 0.5f,  0.5f,  0.5f,  3.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,
		-0.5f,  0.5f,  0.5f,  2.0f,
		-0.5f,  0.5f, -0.5f,  3.0f
	};

	unsigned int VBO[triangleCount], VAO[triangleCount];
	glGenBuffers(triangleCount, VBO);
	glGenVertexArrays(triangleCount, VAO);

	for (int i = 0; i < triangleCount; i++)
	{
		/*
			bind the Vertex Array Object first, then bind and set vertex buffer(s),
			and then configure vertex attributes(s).
		*/
		glBindVertexArray(VAO[i]);
		// copy our vertices array in a vertex buffer for OpenGL to use
		glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		// then set the vertex attributes pointers
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
			(void*)(3 * sizeof(float)));
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
		// transform and drawing triangles
		for (int i = 0; i < triangleCount; i++)
		{
			// practice with coordinate systems
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
			glm::mat4 view = glm::mat4(1.0f);
			// note that we're translating the scene in the reverse direction of where we want to move
			view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
			glm::mat4 projection;
			projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
			int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
			int projectionLoc = glGetUniformLocation(shaderProgram.ID, "projection");
			glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

			// draw the triangle
			int startVert = i * 3;
			glBindVertexArray(VAO[i]);
			glDrawArrays(GL_TRIANGLES, startVert, 36);
		}

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(triangleCount, VAO);
	glDeleteBuffers(triangleCount, VBO);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}