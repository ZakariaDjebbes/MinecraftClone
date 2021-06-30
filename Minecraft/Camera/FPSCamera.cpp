#include "FPSCamera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

FPSCamera::FPSCamera(float _fov, float _aspect, float _zNear, float _zFar) :
	fov(_fov), aspect(_aspect), zNear(_zNear), zFar(_zFar)
{
	view = glm::lookAt(position, position + front, up);
	projection = glm::perspective(glm::radians(fov), aspect, zNear, zFar);
}

FPSCamera::~FPSCamera()
{
}

void FPSCamera::Update(float deltaTime)
{
	velocity += acceleration * deltaTime;
	velocity *= drag;
	position += velocity * deltaTime;

	RefreshView();
}

void FPSCamera::UpdateMouseMovement(float xPos, float yPos)
{
	if (isFirstMove)
	{
		lastX = xPos;
		lastY = yPos;
		isFirstMove = false;
	}

	float xoffset = xPos - lastX;
	float yoffset = lastY - yPos; // reversed since y-coordinates range from bottom to top
	lastX = xPos;
	lastY = yPos;

	pitch += yoffset * sensitivity;
	yaw += xoffset * sensitivity;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;

	front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	front.y = sin(glm::radians(pitch));
	front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));

	this->front = front;
	RefreshView();
}

void FPSCamera::SetAspectRatio(const float aspect)
{
	this->aspect = aspect;

	RefreshProjection();
}

void FPSCamera::SetPosition(const glm::vec3& position)
{
	this->position = position;

	RefreshView();
}

void FPSCamera::SetUp(const glm::vec3& up)
{
	this->up = up;

	RefreshView();
}

void FPSCamera::SetFront(const glm::vec3& orientation)
{
	this->front = orientation;

	RefreshView();
}

void FPSCamera::SetView(const glm::mat4& view)
{
	this->view = view;

	RefreshView();
}

void FPSCamera::SetSensitivity(const float sensitivity)
{
	this->sensitivity = sensitivity;
}

void FPSCamera::RefreshView()
{
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	view = glm::lookAt(position, position + front, up);
}

void FPSCamera::RefreshProjection()
{
	projection = glm::perspective(glm::radians(fov), aspect, zNear, zFar);

	std::cout << aspect << std::endl;
}