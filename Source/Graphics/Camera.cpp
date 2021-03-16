#include <Graphics/Camera.hpp>

namespace GenevaEngine
{
	// constructor with vectors
	Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) :
		Front(glm::vec3(0.0f, 0.0f, -1.0f)),
		MovementSpeed(SPEED),
		MouseSensitivity(SENSITIVITY), Fov(FOV)
	{
		Position = position;
		WorldUp = up;
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}

	// constructor with scalar values
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

	// returns the view matrix calculated using Euler Angles and the LookAt Matrix
	glm::mat4 Camera::GetViewMatrix()
	{
		return glm::lookAt(Position, Position + Front, Up);
	}

	// processes input received from any keyboard-like input system.
	// Accepts input parameter in the form of camera defined ENUM
	void Camera::ProcessKeyboard(Movement direction, float deltaTime)
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

	// processes input received from a mouse input system.
	// Expects the offset value in both the x and y direction.
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

	// processes input received from a mouse scroll-wheel event.
	// Only requires input on the vertical wheel-axis
	void Camera::ProcessMouseScroll(float yoffset)
	{
		Fov -= (float)yoffset;
		if (Fov < MinFov)
			Fov = MinFov;
		if (Fov > MaxFov)
			Fov = MaxFov;
	}

	// calculates the front vector from the Camera's (updated) Euler Angles
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