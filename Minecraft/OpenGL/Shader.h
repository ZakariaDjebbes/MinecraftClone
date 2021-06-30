#pragma once
#include <unordered_map>
#include <string>
#include <glm/glm.hpp>

class Shader
{
private:
	unsigned int id;
	std::unordered_map<std::string, int> locationMap;
public:
	Shader(const std::string& filePath);
	Shader(const std::string& vertexShaderPath, const std::string& fragementShaderPath);
	~Shader();

	void Use() const;
	void Unbind() const;
	void SetFloat(const std::string& name, const float value, const bool useShader = 0);
	void SetInteger(const std::string& name, const int value, const bool useShader = 0);
	void SetVector2f(const std::string& name, const float x, const float y, const bool useShader = 0);
	void SetVector3f(const std::string& name, const float x, const float y, const float z, const bool useShader = 0);
	void SetVector3f(const std::string& name, const glm::vec3 vector3, const bool useShader = 0);
	void SetVector4f(const std::string& name, const float x, float y, float z, float w, bool useShader = 0);
	void setMatrix4f(const std::string& name, const glm::mat4 mat, const bool useShader = 0);

private:
	void ParseShader(const std::string& filePath, std::string* vs = nullptr, std::string* fs = nullptr);
	unsigned int CreateProgram(const std::string& vertexShader, const std::string& fragementShader);
	unsigned int CompileShader(const std::string& source, unsigned int type);
	int GetUniformLocation(const std::string& name);
};

