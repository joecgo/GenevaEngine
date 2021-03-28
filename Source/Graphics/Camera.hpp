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

#include <glad/glad.h> // GLboolean constrainPitch
#include <glm/gtc/matrix_transform.hpp> // vec3 mat4 perspective lookAt

#include <iostream> // cout
#include <vector>

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

		// camera Attributes
		glm::vec3 Position;
		glm::vec3 Front;
		glm::vec3 Up;
		glm::vec3 Right;
		glm::vec3 WorldUp;

		// Default camera values
		static constexpr float YAW = -90.0f;
		static constexpr float PITCH = 0.0f;
		static constexpr float SPEED = 2.5f;
		static constexpr float SENSITIVITY = 0.3f;
		static constexpr float FOV = 50.0f;

		// euler Angles
		float Yaw = -90.0f;
		float Pitch = 0.0f;

		// camera options
		float MovementSpeed;
		float MouseSensitivity;
		float Fov;
		float NearClipping = 0.1f;
		float FarClipping = 1000.0f;
		float MaxFov = 150.0f;
		float MinFov = 20.0f;
		float OrthoWidth = 50.0f;
		bool OrthoView = false; // as opposed to perspective

		// constructor with vectors
		Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);

		// constructor with scalar values
		Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw,
			float pitch);

		// returns the view matrix calculated using Euler Angles,
		// the LookAt Matrix and (potentially) a perspective transformation
		glm::mat4 GetViewMatrix(int screen_width, int screen_height) const;

		// processes input received from any keyboard-like input system.
		// Accepts input parameter in the form of camera defined ENUM
		void ProcessCameraMovement(Movement direction, float deltaTime);

		// processes input received from a mouse input system.
		// Expects the offset value in both the x and y direction.
		void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

		// processes input received from a mouse scroll-wheel event.
		// Only requires input on the vertical wheel-axis
		void ProcessMouseScroll(float yoffset);

	private:
		// calculates the front vector from the Camera's (updated) Euler Angles
		void updateCameraVectors();
	};
}