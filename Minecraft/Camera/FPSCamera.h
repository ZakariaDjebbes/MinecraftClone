#pragma once
#include <glm/glm.hpp>
#include "../OpenGL/Shader.h"
#include <GLFW/glfw3.h>

class FPSCamera
{
private:
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 front = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::vec3 velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
	const float drag = 0.9f;

	glm::mat4 view;
	glm::mat4 projection;

	float aspect; //Aspect ratio of the window
	float fov; //Field of view in degreees
	float zNear; //near plane
	float zFar; //far plane
	
	float sensitivity = 0.2f; //sensitivity of the rotation of the cam in units

	float pitch = 0.0f; //rotation arround X axis
	float yaw = -90.0f; //roation arround Y axis
	float roll = 0.0f; //rotation arround Z axis

	float lastX = 0.0f;
	float lastY = 0.0f;

	bool isFirstMove = true;
public:
	FPSCamera(float _fov, float _aspect, float _zNear, float _zFar);
	~FPSCamera();

	void Update(float deltaTime);
	void UpdateMouseMovement(float xPos, float yPos);
	void SetAspectRatio(const float aspect);
	void SetPosition(const glm::vec3& position);
	void SetUp(const glm::vec3& up);
	void SetFront(const glm::vec3& orientation);
	void SetView(const glm::mat4& view);
	void SetSensitivity(const float sensitivity);


	inline void ResetAcceleration() { acceleration = glm::vec3(0.0f); }
	inline void ResetVelocity() { velocity = glm::vec3(0.0f); }
	inline void ApplyAcceleration(const glm::vec3& acceleration) { this->acceleration = this->acceleration + acceleration; }
	inline glm::mat4 GetView() const { return view; }
	inline glm::mat4 GetProjection() const { return projection; }
	inline glm::vec3 GetPosition() const { return position; }
	inline glm::vec3 GetRight() const { return glm::normalize(glm::cross(front, up)); }
	inline glm::vec3 GetFront() const { return front; }
	inline glm::vec3 GetUp() const { return up; }
private:
	void RefreshView();
	void RefreshProjection();
};
