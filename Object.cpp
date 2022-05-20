#include "Object.h"

Object::Object(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures, std::vector <glm::vec3> Position,unsigned int instances)
	:mesh(vertices, indices, textures,Position,instances)
{
	Object::Position = Position;
	for (int i = 0; i < Position.size(); i++)
	{
		Object::Transformation.push_back(glm::translate(glm::mat4(1.0f), Position[i]));
	}
	Object::instances = instances;

}



void Object::UpdateTransformation(std::vector <glm::vec3> newPos)
{
	Position = newPos;
	for (int i = 0; i < Position.size(); i++)
	{
		Transformation[i] =  glm::translate(Transformation[i], Position[i]);
	}
	mesh.instanceMatrix = Transformation;
}


void Object::Draw(Shader& shader, Camera& camera,int primType)
{
	mesh.Draw(shader, camera, primType);
}