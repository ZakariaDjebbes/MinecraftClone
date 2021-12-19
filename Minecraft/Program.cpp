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
#include "Objects/Mesh.h"

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void process_input(GLFWwindow* window, float deltaTime);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// settings
constexpr unsigned int SCR_WIDTH = 1280;
constexpr unsigned int SCR_HEIGHT = 960;
FPSCamera camera = FPSCamera(45.0f, (static_cast<float>(SCR_WIDTH) / static_cast<float>(SCR_HEIGHT)), 0.1f, 100.0f);
float deltaTime = 0.0f; // Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

std::vector<Vertex> lightVertices =
{ //     COORDINATES     //
	Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f,  0.1f)}
};

std::vector<unsigned int> lightIndices =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};

// Vertices coordinates
std::vector<Vertex> vertices =
{
	Vertex{glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}
};

// Indices for vertices order
std::vector<unsigned int> indices =
{
	0, 1, 2,
	0, 2, 3
};

int main()
{
	DisplayManager display = DisplayManager(SCR_WIDTH, SCR_HEIGHT, "Minecraft in C++");
	Renderer renderer;
	glfwSetCursorPosCallback(display.GetWindow(), mouse_callback);
	glfwSetInputMode(display.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetFramebufferSizeCallback(display.GetWindow(), framebuffer_size_callback);

	glm::vec3 lightPos(1.2f, 1.0f, -5.0f);

	Shader shader("shaders/vertex.glsl", "shaders/fragement.glsl");
	Shader lightShader("shaders/light_vertex.glsl", "shaders/light_fragment.glsl");

	Texture textures[]
	{
		Texture("resources/textures/container.png", TextureType::Diffuse),
		Texture("resources/textures/container_specular.png", TextureType::Specular)
	};
	std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));

	Mesh light(lightVertices, lightIndices, tex);
	Mesh object(vertices, indices, tex);

	camera.SetPosition(glm::vec3(0.0f, 0.0f, 2.0f));
	camera.SetFront(glm::vec3(0.0f, 0.0f, -1.0f));

	shader.Use();
	//Directional light
	shader.SetVector3f("dirLight.direction", -0.2f, -1.0f, -0.3f);
	shader.SetVector3f("dirLight.ambient", 0.05f, 0.05f, 0.05f);
	shader.SetVector3f("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
	shader.SetVector3f("dirLight.specular", 0.5f, 0.5f, 0.5f);
	//POINT LIGHT
	shader.SetVector3f("pointLight.position", 1.2f, 1.0f, -5.0f);
	shader.SetFloat("pointLight.constant", 1.0f);
	shader.SetFloat("pointLight.linear", 0.09f);
	shader.SetFloat("pointLight.quadratic", 0.032f);
	shader.SetVector3f("pointLight.ambient", 0.05f, 0.05f, 0.05f);
	shader.SetVector3f("pointLight.diffuse", 0.8f, 0.8f, 0.8f);
	shader.SetVector3f("pointLight.specular", 1.0f, 1.0f, 1.0f);
	//Material
	shader.SetFloat("material.shininess", 32.0f);
	shader.SetInteger("material.diffuse", 0);
	shader.SetInteger("material.specular", 1);

	// Create light mesh

	while (!display.ShouldClose()) {
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		process_input(display.GetWindow(), deltaTime);
		//render
		renderer.Clear(0.1f, 0.1f, 0.1f, 1.0f);
		lightShader.setMatrix4f("model", glm::mat4(1.0f), true);
		shader.setMatrix4f("model", glm::translate(glm::mat4(1.0f), glm::vec3(5.0f, 0.0f, 0.0f)), true);
		light.Draw(lightShader, camera, renderer);
		object.Draw(shader, camera, renderer);
		display.Update();
	}

	//shader.Unbind();
	lightShader.Unbind();
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