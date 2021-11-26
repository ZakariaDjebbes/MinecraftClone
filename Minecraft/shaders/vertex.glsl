#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

// uniform mat3 normalMatrix

out vec3 normal;
out vec3 fragPos;  
out vec2 texCoords;

void main()
{

	gl_Position = proj * view * model * vec4(aPos, 1.0);
	normal = mat3(transpose(inverse(model))) * aNormal; //normalMatrix * the normal, this should be done on the cpu***
	fragPos = vec3(model * vec4(aPos, 1.0));
	texCoords = aTexCoords;
}