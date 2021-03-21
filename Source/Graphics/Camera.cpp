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
	 *      \param [in] up
	 *      \param [in] yaw
	 *      \param [in] pitch
	 */
	Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) :
		Front(glm::vec3(0.0f, 0.0f, -1.0f)),
		MovementSpeed(SPEED),
		MouseSensitivity(SENSITIVITY),
		Fov(FOV)
	{
		Position = position;
		WorldUp = up;
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}

	/*!
	 *  Constructor with scalar values.
	 *
	 *      \param [in] posX
	 *      \param [in] posY
	 *      \param [in] posZ
	 *      \param [in] upX
	 *      \param [in] upY
	 *      \param [in] upZ
	 *      \param [in] yaw
	 *      \param [in] pitch
	 */
	Camera::Camera(float posX, float posY, float posZ, float upX, float upY,
		float upZ, float yaw, float pitch) :
		Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED),
		MouseSensitivity(SENSITIVITY), Fov(FOV)
	{
		Position = glm::vec3(posX, posY, posZ);
		WorldUp = glm::vec3(upX, upY, upZ);
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}
	/*!
	 *  Returns the camera's view matrix.
	 *
	 *      \return The view matrix.
	 */
	glm::mat4 Camera::GetViewMatrix(int screen_width, int screen_height) const
	{
		glm::mat4 view = glm::lookAt(Position, Position + Front, Up);
		glm::mat4 perspective = glm::perspective(glm::radians(Fov),
			(float)screen_width / (float)screen_height, NearClipping, FarClipping);

		return perspective * view;
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
		float velocity = MovementSpeed * deltaTime;
		if (direction == Movement::FORWARD)
			Position += Front * velocity;
		if (direction == Movement::BACKWARD)
			Position -= Front * velocity;
		if (direction == Movement::LEFT)
			Position -= Right * velocity;
		if (direction == Movement::RIGHT)
			Position += Right * velocity;
		if (direction == Movement::UP)
			Position += Up * velocity;
		if (direction == Movement::DOWN)
			Position -= Up * velocity;
	}

	/*!
	 *  Processes the mouse movement.
	 *
	 *      \param [in] xoffset
	 *      \param [in] yoffset
	 *      \param [in] constrainPitch
	 */
	void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
	{
		xoffset *= MouseSensitivity;
		yoffset *= MouseSensitivity;

		Yaw += xoffset;
		Pitch += yoffset;

		// make sure that when pitch is out of bounds, screen doesn't get flipped
		if (constrainPitch)
		{
			if (Pitch > 89.0f)
				Pitch = 89.0f;
			if (Pitch < -89.0f)
				Pitch = -89.0f;
		}

		// update Front, Right and Up Vectors using the updated Euler angles
		updateCameraVectors();
	}

	/*!
	 *  Processes the mouse scroll.
	 *
	 *      \param [in] yoffset
	 */
	void Camera::ProcessMouseScroll(float yoffset)
	{
		Fov -= (float)yoffset;
		if (Fov < MinFov)
			Fov = MinFov;
		if (Fov > MaxFov)
			Fov = MaxFov;
	}

	/*!
	 *  Calculates the front vector from the Camera's (updated) Euler Angles
	 */
	void Camera::updateCameraVectors()
	{
		// calculate the new Front vector
		glm::vec3 front;
		front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		front.y = sin(glm::radians(Pitch));
		front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		Front = glm::normalize(front);
		// also re-calculate the Right and Up vector
		Right = glm::normalize(glm::cross(Front, WorldUp));
		Up = glm::normalize(glm::cross(Right, Front));
	}
}