#pragma once

#include<string>

#include"VAO.h"
#include"EBO.h"
#include"Camera.h"
#include"Texture.h"


class Mesh
{
public:
	std::vector <Vertex> vertices;
	std::vector <GLuint> indices;
	std::vector <Texture> textures;
	std::vector <glm::mat4> instanceMatrix;

	unsigned int instances = 1;
	float Modifier = 0;
	// Store VAO in public so it can be used in the Draw function
	VAO VAO;

	// Initializes the mesh
	Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures, std::vector <glm::vec3> Position,unsigned int instances);

	// Draws the mesh
	void Draw(Shader& shader, Camera& camera,int primType);
};