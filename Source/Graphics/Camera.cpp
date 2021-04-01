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
 * \file Camera.cpp
 * \author Joe Goldman
 * \brief Camera class definition
 */
#include <Graphics/Camera.hpp>

namespace GenevaEngine
{
	/*!
	 *  Constructor with vectors.
	 *
	 *      \param [in] position
	 */
	Camera::Camera(b2Vec2 position) : Position(position)
	{
	}

	/*!
	 *	Convert from world coordinates to normalized device coordinates.
	 *	Copied from box2d testbed
	 *  http://www.songho.ca/opengl/gl_projectionmatrix.html
	 *
	 *      \param [in,out] m
	 *      \param [in]     zBias
	 *      \param [in]     screen_width
	 *      \param [in]     screen_height
	 */
	void Camera::BuildProjectionMatrix(float* m, float zBias, int screen_width, int screen_height)
	{
		// camera view
		//glm::mat4 view = glm::lookAt(Position, Position + Front, Up);

		float w = float(screen_width);
		float h = float(screen_height);
		float ratio = w / h;
		b2Vec2 extents(ratio * 25.0f, 25.0f);
		extents *= Zoom;

		b2Vec2 lower = Position - extents;
		b2Vec2 upper = Position + extents;

		m[0] = 2.0f / (upper.x - lower.x);
		m[1] = 0.0f;
		m[2] = 0.0f;
		m[3] = 0.0f;

		m[4] = 0.0f;
		m[5] = 2.0f / (upper.y - lower.y);
		m[6] = 0.0f;
		m[7] = 0.0f;

		m[8] = 0.0f;
		m[9] = 0.0f;
		m[10] = 1.0f;
		m[11] = 0.0f;

		m[12] = -(upper.x + lower.x) / (upper.x - lower.x);
		m[13] = -(upper.y + lower.y) / (upper.y - lower.y);
		m[14] = zBias;
		m[15] = 1.0f;
	}

	/*!
	 *  processes input received from any keyboard-like input system.
	 *  Accepts input parameter in the form of camera defined ENUM
	 *
	 *      \param [in] direction
	 *      \param [in] deltaTime
	 *
	 */
	void Camera::ProcessCameraMovement(Movement direction, float deltaTime)
	{
		float velocity = DebugFlySpeed * deltaTime;
		b2Vec2 right(1.0f, 0.0f);
		b2Vec2 up(0.0, 1.0f);
		if (direction == Movement::FORWARD)
			Zoom -= velocity * 0.05f;
		if (direction == Movement::BACKWARD)
			Zoom += velocity * 0.05f;
		if (direction == Movement::LEFT)
			Position -= velocity * right;
		if (direction == Movement::RIGHT)
			Position += velocity * right;
		if (direction == Movement::UP)
			Position += velocity * up;
		if (direction == Movement::DOWN)
			Position -= velocity * up;
		std::cout << Position.x << ", " << Position.y << ", " << Zoom << ", " << std::endl;
	}
}