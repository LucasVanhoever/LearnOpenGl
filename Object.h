#pragma once

#include "Mesh.h"


class Object
{
public:
	std::vector <glm::vec3> Position;
	std::vector <glm::mat4> Transformation;

	unsigned int instances;

	Mesh mesh;

	// Initializes the mesh
	Object(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures, std::vector <glm::vec3> Position,unsigned int instances);

	// Draws the Object
	void UpdateTransformation(std::vector <glm::vec3> newPos);
	void Draw(Shader& shader, Camera& camera,int primType);
};