#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include "OpenGL/IndexBuffer.h"
#include "OpenGL/VertexBuffer.h"
#include "OpenGL/VertexArray.h"
#include "OpenGL/Shader.h"
#include "Renderer/Renderer.h"
#include "Display/DisplayManager.h"
#include "OpenGL/Texture.h"
#include "Camera/FPSCamera.h"

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void process_input(GLFWwindow* window, float deltaTime);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// settings
constexpr unsigned int SCR_WIDTH = 1280;
constexpr unsigned int SCR_HEIGHT = 960;
FPSCamera camera = FPSCamera(45.0f, (static_cast<float>(SCR_WIDTH) / static_cast<float>(SCR_HEIGHT)), 0.1f, 100.0f);
float deltaTime = 0.0f; // Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame
glm::vec3 lightPos(1.2f, 1.0f, -5.0f);

int main()
{
	DisplayManager display = DisplayManager(SCR_WIDTH, SCR_HEIGHT, "Minecraft in C++");
	Renderer renderer;

	float vertices[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
	};

	glm::vec3 positions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(2.3f, 1.0f, -5.0f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	VertexBuffer vb(vertices, sizeof(vertices));
	VertexBufferLayout vbLayout;
	vbLayout.AddElements(GL_FLOAT, 3);
	vbLayout.AddElements(GL_FLOAT, 3);
	vbLayout.AddElements(GL_FLOAT, 2);
	VertexArray va;
	va.BindBuffer(vb, vbLayout);
	Shader shader("shaders/vertex.glsl", "shaders/fragement.glsl");
	Shader lightShader("shaders/light_vertex.glsl", "shaders/light_fragment.glsl");
	Texture texture("resources/textures/container.png");
	Texture specular("resources/textures/container_specular.png", TextureType::Specular);

	camera.SetPosition(glm::vec3(0.0f, 0.0f, 2.0f));
	camera.SetFront(glm::vec3(0.0f, 0.0f, -1.0f));

	glfwSetCursorPosCallback(display.GetWindow(), mouse_callback);
	glfwSetInputMode(display.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetFramebufferSizeCallback(display.GetWindow(), framebuffer_size_callback);

	bool dir = false;

	while (!display.ShouldClose()) {
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		process_input(display.GetWindow(), deltaTime);

		//render
		renderer.Clear(0.1f, 0.1f, 0.1f, 1.0f);
		glm::vec3 rotation(1.0f, 1.0f, 0.0f);
		glm::vec3 scale(1.0f);
		glm::mat4 model(1.0f);

		shader.Use();
		texture.Bind();
		specular.Bind();
		shader.setMatrix4f("view", camera.GetView());
		shader.setMatrix4f("proj", camera.GetProjection());
		shader.SetVector3f("viewPos", camera.GetPosition());

		//DIRECTIONAL LIGHT
		shader.SetVector3f("dirLight.direction", -0.2f, -1.0f, -0.3f);
		shader.SetVector3f("dirLight.ambient", 0.05f, 0.05f, 0.05f);
		shader.SetVector3f("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
		shader.SetVector3f("dirLight.specular", 0.5f, 0.5f, 0.5f);

		//POINT LIGHT
		shader.SetVector3f("pointLight.position", lightPos);
		shader.SetFloat("pointLight.constant", 1.0f);
		shader.SetFloat("pointLight.linear", 0.09f);
		shader.SetFloat("pointLight.quadratic", 0.032f);
		shader.SetVector3f("pointLight.ambient", 0.05f, 0.05f, 0.05f);
		shader.SetVector3f("pointLight.diffuse", 0.8f, 0.8f, 0.8f);
		shader.SetVector3f("pointLight.specular", 1.0f, 1.0f, 1.0f);

		//shader.SetFloat("light.cutOff", glm::cos(glm::radians(12.5f)));
		//shader.SetFloat("light.outerCutOff", glm::cos(glm::radians(17.5f)));

		//Material
		shader.SetFloat("material.shininess", 32.0f);
		shader.SetInteger("material.diffuse", 0);
		shader.SetInteger("material.specular", 1);

		for (int i = 0; i < std::size(positions); i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, positions[i]);
			float angle = 0.0f + (i * 20);
			model = glm::rotate(model, glm::radians(angle), rotation);
			model = glm::scale(model, scale);
			shader.setMatrix4f("model", model);

			renderer.Draw(va, shader, 36);
		}

		rotation = glm::vec3(0.0f, 0.0f, 1.0f);
		scale = glm::vec3(0.25f, 0.25f, 0.25f);

		model = glm::mat4(1.0f);
		model = glm::translate(glm::mat4(1.0f), lightPos);
		model = glm::rotate(model, glm::radians(0.0f), rotation);
		model = glm::scale(model, scale);
		lightShader.Use();
		lightShader.setMatrix4f("model", model);
		lightShader.setMatrix4f("view", camera.GetView());
		lightShader.setMatrix4f("proj", camera.GetProjection());
		renderer.Draw(va, lightShader, 36);

		display.Update();
	}

	shader.Unbind();
	glfwTerminate();
	return 0;
}

void mouse_callback(GLFWwindow* window, const double xpos, const double ypos)
{
	camera.UpdateMouseMovement(xpos, ypos);
}

void process_input(GLFWwindow* window, const float deltaTime)
{
	constexpr float speed = 50.0f;
	camera.ResetAcceleration();

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		// Take the cross product of the camera's right and up.
		glm::vec3 front = -glm::cross(camera.GetRight(), camera.GetUp());
		camera.ApplyAcceleration(front * speed);
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		glm::vec3 back = glm::cross(camera.GetRight(), camera.GetUp());
		camera.ApplyAcceleration(back * speed);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera.ApplyAcceleration(-(camera.GetRight() * speed));
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera.ApplyAcceleration(camera.GetRight() * speed);
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		camera.ApplyAcceleration(camera.GetUp() * speed);
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		camera.ApplyAcceleration(-(camera.GetUp() * speed));
	}

	camera.Update(deltaTime);
}

void framebuffer_size_callback(GLFWwindow* window, const int width, const int height)
{
	glViewport(0, 0, width, height);
	camera.SetAspectRatio(static_cast<float>(width) / static_cast<float>(height));
}