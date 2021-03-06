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

#include <glad/glad.h> // extension of GLFW
#include <GLFW/glfw3.h> // GLFW

#include <Constructs/Construct.hpp>
#include <Graphics/Graphics.hpp>
#include <Graphics/Shader.hpp>
#include <Core/Entity.hpp>
#include <Core/GameSession.hpp>

namespace GenevaEngine
{
	/*!
	 *  Starts the graphics.
	 */
	void Graphics::Start()
	{
		// glfw: initialize and configure
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// glfw: window creation
		m_window = glfwCreateWindow(Graphics::SCR_WIDTH, Graphics::SCR_HEIGHT,
			"GenevaEngine", NULL, NULL);
		if (m_window == NULL)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return; // TODO: inform GameSession of error
		}
		glfwMakeContextCurrent(m_window);
		glfwSetFramebufferSizeCallback(m_window, FrameBufferSizeCallback);

		// tell GLFW to capture our mouse
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		// glad: load all OpenGL function pointers
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return; // TODO: inform GameSession of error
		}

		// configure global opengl state
		glEnable(GL_DEPTH_TEST);

		// create, save, and assign shaders. TODO: do this with a config file
		glLineWidth(2.0f);
		// triangle shader
		m_triangle_shader =
			new Shader("Shaders/TriangleShader.vert", "Shaders/TriangleShader.frag");
		m_triangle_shader->DrawType = GL_TRIANGLES;
		// line shader
		m_line_shader =
			new Shader("Shaders/LineShader.vert", "Shaders/LineShader.frag");
		m_line_shader->DrawType = GL_LINES;

		// set clear color
		Graphics::SetClearColor(GetPaletteColor(1));
	}

	/*!
	 *  Ends the graphics.
	 */
	void Graphics::End()
	{
		delete (m_triangle_shader);
		delete (m_line_shader);

		// glfw: terminate, clearing all previously allocated GLFW resources.
		glfwTerminate();
	}

	/*!
	 *  Updates the graphics.
	 *
	 *      \param [in] dt
	 */
	void Graphics::Update(double dt)
	{
		// check for close window
		if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(m_window, true);

		// clear graphics before the work starts
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// pass projection from camera to shader
		float proj[16]{ 0 };
		m_camera.BuildProjectionMatrix(proj, 0.0f, SCR_WIDTH, SCR_HEIGHT);
		m_triangle_shader->UpdateProjection(proj);
		m_line_shader->UpdateProjection(proj);

		// render entities
		for (Entity* entity : m_gameSession->m_entities)
			RenderEntity(*entity);
		Flush();

		// glfw: swap buffers
		glfwSwapBuffers(m_window);
	}

	/*!
	 *  Renders the entity.
	 *
	 *      \param [in,out] entity
	 */
	void Graphics::RenderEntity(Entity& entity)
	{
		// draw entities contruct (composite of box2d bodies)
		const Color color = entity.GetRenderColor();
		Construct& construct = entity.GetConstruct();
		const ConstructRenderData& constructData = construct.GetConstructRenderData();

		// render each joint
		if (constructData.FillBetweenJoints)
		{
			const int count = constructData.JointRenderList.size();
			for (int i = 0; i < count; i++)
			{
				const b2Joint* joint = constructData.JointRenderList[i].Joint;
				const b2Vec2 offset = constructData.JointRenderList[i].aOffset;
				m_transformedVerts[i] = joint->GetAnchorA() + offset;
			}

			DrawSolidPolygon(m_transformedVerts, count, color);
		}
		else
		{
			for (const JointRenderData jointData : constructData.JointRenderList)
			{
				b2Joint* joint = jointData.Joint;
				DrawSegment(
					joint->GetAnchorA() + jointData.aOffset,
					joint->GetAnchorB() + jointData.bOffset,
					color);
			}
		}

		// render each body
		for (const BodyRenderData bodyData : constructData.BodyRenderList)
		{
			b2Shape* shape = bodyData.Body->GetFixtureList()->GetShape();
			b2Body* body = bodyData.Body;
			b2Transform xf = body->GetTransform();
			b2PolygonShape* polygon = nullptr;
			b2CircleShape* circle = nullptr;

			switch (shape->GetType())
			{
			case b2Shape::e_polygon:
				polygon = (b2PolygonShape*)shape;

				for (int i = 0; i < polygon->m_count; i++)
					m_transformedVerts[i] = b2Mul(xf, polygon->m_vertices[i]);

				DrawSolidPolygon(m_transformedVerts, polygon->m_count, color);
				break;

			case b2Shape::e_chain:
			case b2Shape::e_circle:
				DrawCircle(body->GetPosition(), shape->m_radius, color);
				break;

			case b2Shape::e_edge:
			default:
				break;
			}
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
	 *  Returns the graphics's window.
	 *
	 *      \return The window.
	 */
	GLFWwindow* Graphics::GetWindow()
	{
		return m_window;
	}

	Camera* Graphics::GetCamera()
	{
		return &m_camera;
	}

	void Graphics::SaveShader(std::string name, Shader shader)
	{
		m_shaders[name] = shader;
	}

	Shader* Graphics::GetShader(std::string name)
	{
		return &(m_shaders[name]);
	}

	void Graphics::FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void Graphics::DrawCircle(const b2Vec2& center, float radius, const Color& color)
	{
		const float segments = 16.0f;
		const float increment = 2.0f * b2_pi / segments;
		float sinInc = sinf(increment);
		float cosInc = cosf(increment);
		b2Vec2 r1(1.0f, 0.0f);
		b2Vec2 v1 = center + radius * r1;
		for (int i = 0; i < segments; ++i)
		{
			// Perform rotation to avoid additional trigonometry.
			b2Vec2 r2;
			r2.x = cosInc * r1.x - sinInc * r1.y;
			r2.y = sinInc * r1.x + cosInc * r1.y;
			b2Vec2 v2 = center + radius * r2;
			m_line_shader->Vertex(v1, color);
			m_line_shader->Vertex(v2, color);
			r1 = r2;
			v1 = v2;
		}
	}

	void Graphics::DrawSolidPolygon(const b2Vec2* vertices, int vertexCount, const Color& color)
	{
		Color fillColor = color * 0.7f;

		for (int i = 1; i < vertexCount - 1; ++i)
		{
			m_triangle_shader->Vertex(vertices[0], fillColor);
			m_triangle_shader->Vertex(vertices[i], fillColor);
			m_triangle_shader->Vertex(vertices[i + 1], fillColor);
		}

		b2Vec2 p1 = vertices[vertexCount - 1];
		for (int32 i = 0; i < vertexCount; ++i)
		{
			b2Vec2 p2 = vertices[i];
			m_line_shader->Vertex(p1, color);
			m_line_shader->Vertex(p2, color);
			p1 = p2;
		}
	}

	void Graphics::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const Color& color)
	{
		m_line_shader->Vertex(p1, color);
		m_line_shader->Vertex(p2, color);
	}

	/*!
	 *  Flush the remaining buffers to be rendered
	 */
	void Graphics::Flush()
	{
		m_line_shader->Flush();
		m_triangle_shader->Flush();
	}

	/*!
	 *  Returns a color from the pallete using a color id
	 *
	 *      \param [in] color_id
	 *
	 *      \return The palette color.
	 */
	Color Graphics::GetPaletteColor(int color_id)
	{
		// if color id is out of range, return full red
		if (color_id < 0 || color_id >= m_palette.size())
			return Color(0xFF0000);

		return m_palette[color_id];
	}
}