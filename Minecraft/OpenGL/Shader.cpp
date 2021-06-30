#include "Shader.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader(const std::string& filePath) : id(0)
{
	std::string vs, fs;
	ParseShader(filePath, &vs, &fs);
	id = CreateProgram(vs, fs);
}

Shader::Shader(const std::string& vertexShaderPath, const std::string& fragementShaderPath)
{
	std::ifstream stream(vertexShaderPath);
	std::stringstream vertexShader, fragmentShader;

	if (!stream.good())
		throw std::invalid_argument("file at path " + vertexShaderPath + " doesn't exist");

	while (stream >> vertexShader.rdbuf());

	stream.close();
	stream.clear();
	stream.open(fragementShaderPath);
	
	if (!stream.good())
		throw std::invalid_argument("file at path " + vertexShaderPath + " doesn't exist");

	while (stream >> fragmentShader.rdbuf());

	id = CreateProgram(vertexShader.str(), fragmentShader.str());
}

Shader::~Shader()
{
	glDeleteProgram(id);
}

void Shader::Use() const
{
	glUseProgram(id);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

void Shader::SetFloat(const std::string& name, const float value, const bool useShader)
{
	if (useShader == GL_TRUE)
		Use();

	glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetInteger(const std::string& name, const int value, const bool useShader)
{
	if (useShader == GL_TRUE)
		Use();

	glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetVector2f(const std::string& name, const float x, const float y, const bool useShader)
{
	if (useShader == GL_TRUE)
		Use();

	glUniform2f(GetUniformLocation(name), x, y);
}

void Shader::SetVector3f(const std::string& name, const float x, const float y, const float z, const bool useShader)
{
	if (useShader == GL_TRUE)
		Use();

	glUniform3f(GetUniformLocation(name), x, y, z);
}

void Shader::SetVector3f(const std::string& name, const glm::vec3 vector3, const bool useShader)
{
	if (useShader == GL_TRUE)
		Use();

	glUniform3f(GetUniformLocation(name), vector3.x, vector3.y, vector3.z);
}

void Shader::SetVector4f(const std::string& name, const float x, const float y, const float z, const float w, const bool useShader)
{
	if (useShader == GL_TRUE)
		Use();

	glUniform4f(GetUniformLocation(name), x, y, z, w);
}

void Shader::setMatrix4f(const std::string& name, const glm::mat4 mat, const bool useShader)
{
	if (useShader == GL_TRUE)
		Use();

	glUniformMatrix4fv(GetUniformLocation(name), 1, 0, &mat[0][0]);
}

void Shader::ParseShader(const std::string& filePath, std::string* vs, std::string* fs)
{
	unsigned int shaderType = 0;

	std::ifstream stream(filePath);

	if (!stream.good())
		throw std::invalid_argument("file at path " + filePath + " doesn't exist");

	std::string line;
	std::stringstream ss[2];

	while (getline(stream, line))
	{
		if (line.find(".shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				shaderType = GL_VERTEX_SHADER;
			else if (line.find("fragment") != std::string::npos)
				shaderType = GL_FRAGMENT_SHADER;
		}
		else
		{
			switch (shaderType)
			{
			case GL_VERTEX_SHADER:
				ss[0] << line << "\n";;
				break;
			case GL_FRAGMENT_SHADER:
				ss[1] << line << "\n";
				break;
			case 0: default:
				throw std::invalid_argument("received source code doesn't fit any shader type");
				break;
			}
		}
	}

	*vs = ss[0].str();
	*fs = ss[1].str();
}

unsigned int Shader::CreateProgram(const std::string& vertexShader, const std::string& fragementShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(vertexShader, GL_VERTEX_SHADER);
	unsigned int fs = CompileShader(fragementShader, GL_FRAGMENT_SHADER);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	int success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);

	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		return false;
	}

	glDeleteShader(vs);
	glDeleteShader(fs);
	return program;
}

unsigned int Shader::CompileShader(const std::string& source, unsigned int type)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);

		std::string shaderName;

		switch (type)
		{
		case GL_FRAGMENT_SHADER:
			shaderName = "GL_FRAGMENT_SHADER";
			break;
		case GL_VERTEX_SHADER:
			shaderName = "GL_VERTEX_SHADER";
			break;
		default:
			shaderName = "UNKNOWN";
			break;
		}

		std::cout << "Failed to compile shader " << shaderName << " \nERROR MESSAGE:" << std::endl;
		std::cout << message << std::endl;

		glDeleteShader(id);
		return 0;
	}

	return id;
}

int Shader::GetUniformLocation(const std::string& name)
{
	if (locationMap.find(name) != locationMap.end())
	{
		return locationMap[name];
	}

	int location = glGetUniformLocation(id, name.c_str());

	if (location == -1)
		std::cout << "Uniform: (" << name << ") doesn't exist" << std::endl;
		
	locationMap[name] = location;
	return location;
}
