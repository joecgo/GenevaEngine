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
  * \file Camera.hpp
  * \author Joe Goldman
  * \brief Camera class declaration
  */

#pragma once

#include <box2d/box2d.h> // box2d

#include <iostream> // cout endl

namespace GenevaEngine
{
	/**
	 * \brief An abstract camera class that processes input and calculates the corresponding
	 * Euler Angles, aVectors and Matrices for use in OpenGL
	 */
	class Camera
	{
	public:

		/**
		 * Defines several possible options for camera movement.
		 */
		enum class Movement
		{
			FORWARD,
			BACKWARD,
			LEFT,
			RIGHT,
			UP,
			DOWN
		};

		// Camera Attributes
		b2Vec2 Position;
		float Yaw = -90.0f;
		float DebugFlySpeed = 3.0f;
		float Zoom = 2.0f;

		// constructor with vectors
		Camera(b2Vec2 position = b2Vec2(0.0f, 30.0f));

		// returns the view matrix calculated using Euler Angles,
		// the LookAt Matrix and (potentially) a perspective transformation
		void BuildProjectionMatrix(float* m, float zBias, int screen_width, int screen_height);

		// processes input received from any keyboard-like input system.
		// Accepts input parameter in the form of camera defined ENUM
		void ProcessCameraMovement(Movement direction, float deltaTime);

	private:
		// calculates the front vector from the Camera's (updated) Euler Angles
		void UpdateCameraVectors();
	};
}