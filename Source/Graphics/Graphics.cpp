/****************************************************************************
 * Copyright (C) 2021 by Joe Goldman	                                    *
 *                                                                          *
 * This file is part of GenevaEngine.                                       *
 *                                                                          *
 *   GenevaEngine is a custom C++ engine built for the purposes of 			*
 *	 learning and fun. You can reach me at joecgo@gmail.com. 				*
 *                                                                          *
 ****************************************************************************/

 /**
  * \file Graphics.cpp
  * \author Joe Goldman
  * \brief Graphics system class definition
  *
  **/

#include <Core/GameCommon.hpp>

namespace GenevaEngine
{
	// define static member variables for mouse callback function
	double Graphics::mouse_x = 0.0;
	double Graphics::mouse_y = 0.0;
	double Graphics::mouse_scroll = 0.0;

	void Graphics::Start()
	{
		// glfw: initialize and configure
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// glfw: window creation
		window = glfwCreateWindow(Graphics::SCR_WIDTH, Graphics::SCR_HEIGHT,
			"GenevaEngine", NULL, NULL);
		if (window == NULL)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return; // TODO: inform GameSession of fatal error
		}
		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

		// tell GLFW to capture our mouse
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		// glad: load all OpenGL function pointers
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return; // TODO: inform GameSession of fatal error
		}

		// configure global opengl state
		glEnable(GL_DEPTH_TEST);

		// create, save, and assign shaders. TODO: do this with a config file
		glLineWidth(2.0f);
		triangle_shader = new Shader("Shaders/TriangleShader.vert", "Shaders/TriangleShader.frag");
		triangle_shader->m_drawType = GL_TRIANGLES;
		line_shader = new Shader("Shaders/TriangleShader.vert", "Shaders/TriangleShader.frag");
		line_shader->m_drawType = GL_LINES;

		// set clear color
		Graphics::SetClearColor(Graphics::palette[1]);
	}

	void Graphics::End()
	{
		delete (triangle_shader);
		delete (line_shader);

		// glfw: terminate, clearing all previously allocated GLFW resources.
		glfwTerminate();
	}
	void Graphics::Update(double dt)
	{
		// clear graphics before the work starts
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// pass projection from camera to shader
		glm::mat4 projection = camera.GetViewMatrix(SCR_WIDTH, SCR_HEIGHT);
		triangle_shader->UpdateProjection(projection);
		line_shader->UpdateProjection(projection);

		// render entities
		for (Entity* entity : gamesession->entities)
			RenderEntity(entity);
		Flush();

		// glfw: swap buffers
		glfwSwapBuffers(window);
	}

	void Graphics::RenderEntity(Entity* entity)
	{
		// draw shape depending on type
		b2PolygonShape shape = entity->GetShape();
		b2Transform xf = entity->GetBody()->GetTransform();
		for (size_t i = 0; i < shape.m_count; i++)
			transformed_verts[i] = b2Mul(xf, shape.m_vertices[i]);

		switch (shape.GetType())
		{
		case b2Shape::e_polygon:

			DrawSolidPolygon(transformed_verts, shape.m_count, palette[5]);
			break;

		case b2Shape::e_chain:
		case b2Shape::e_circle:
		case b2Shape::e_edge:
		default:
			break;
		}
	}

	/*!
	 *  Sets window the clear color.
	 *
	 *      \param [in] color Color to set.
	 */
	void Graphics::SetClearColor(Color color)
	{
		glClearColor(color.r, color.g, color.b, 1.0f);
	}

	/*!
	 *  Saves a shader by name.
	 *
	 *      \param [in] name
	 *      \param [in] shader
	 */
	void Graphics::SaveShader(std::string name, Shader shader)
	{
		shaders[name] = shader;
	}

	/*!
	 *  Retrieves a shader from Graphics system by name.
	 *
	 *      \param [in] name
	 *
	 *      \return The shader.
	 */
	Shader* Graphics::GetShader(std::string name)
	{
		return &(shaders[name]);
	}

	void Graphics::UpdateCameraMovement()
	{
		if (firstMouse)
		{
			lastX = mouse_x;
			lastY = mouse_y;
			firstMouse = false;
		}

		float xoffset = (float)mouse_x - (float)lastX;
		float yoffset = (float)lastY - (float)mouse_y; // reversed since y-coordinates go from bottom to top
		lastX = mouse_x;
		lastY = mouse_y;

		float look_sensitivity = 0.1f;
		float scroll_sensitivity = 3.0f;
		xoffset *= look_sensitivity;
		yoffset *= look_sensitivity;
		float mouseScrollDelta = (float)mouse_scroll * scroll_sensitivity;
		mouse_scroll = 0.0; // reset value

		camera.ProcessMouseMovement(xoffset, yoffset);
		camera.ProcessMouseScroll(mouseScrollDelta);
	}

	/*!
	 *  callback for the mouse position
	 *
	 *      \param [in,out] window
	 *      \param [in]     xpos
	 *      \param [in]     ypos
	 */
	void Graphics::mouse_callback(GLFWwindow* window, double xpos, double ypos)
	{
		mouse_x = xpos;
		mouse_y = ypos;
	}

	/*!
	 *  callback for scroll input
	 *
	 *      \param [in,out] window
	 *      \param [in]     xoffset
	 *      \param [in]     yoffset
	 */
	void Graphics::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		mouse_scroll = yoffset;
	}

	/*!
	 *  Callback for the framebuffer
	 *
	 *      \param [in,out] window
	 *      \param [in]     width
	 *      \param [in]     height
	 */
	void Graphics::framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	//
	void Graphics::DrawSolidPolygon(b2Vec2* vertices, int vertexCount, Color& color)
	{
		Color fillColor = color * 0.7f;

		for (int i = 1; i < vertexCount - 1; ++i)
		{
			triangle_shader->Vertex(vertices[0], fillColor);
			triangle_shader->Vertex(vertices[i], fillColor);
			triangle_shader->Vertex(vertices[i + 1], fillColor);
		}

		b2Vec2 p1 = vertices[vertexCount - 1];
		for (int32 i = 0; i < vertexCount; ++i)
		{
			b2Vec2 p2 = vertices[i];
			line_shader->Vertex(p1, color);
			line_shader->Vertex(p2, color);
			p1 = p2;
		}
	}

	//
	void Graphics::Flush()
	{
		line_shader->Flush();
		triangle_shader->Flush();
	}
}