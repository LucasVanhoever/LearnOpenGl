#include "Mesh.h"

Mesh::Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures, std::vector <glm::vec3> Position,unsigned int instances)
{
	Mesh::vertices = vertices;
	Mesh::indices = indices;
	Mesh::textures = textures;
	Mesh::instances = instances;

	for (int i = 0; i < Position.size(); i++)
	{
		Mesh::instanceMatrix.push_back(glm::translate(glm::mat4(1.0f), Position[i]));
	}

	VAO.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO instanceVBO(instanceMatrix);
	VBO VBO(vertices);
	// Generates Element Buffer Object and links it to indices
	EBO EBO(indices);

	// Links VBO to VAO
	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	VAO.LinkAttrib(VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
	VAO.LinkAttrib(VBO, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));

	if (instances != 1)
	{
		std::cout << "UsingInstances \n";
		instanceVBO.Bind();
		// Can't link to a mat4 so you need to link four vec4s
		VAO.LinkAttrib(instanceVBO, 4, 4, GL_FLOAT, sizeof(glm::mat4), (void*)0);
		VAO.LinkAttrib(instanceVBO, 5, 4, GL_FLOAT, sizeof(glm::mat4), (void*)(1 * sizeof(glm::vec4)));
		VAO.LinkAttrib(instanceVBO, 6, 4, GL_FLOAT, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
		VAO.LinkAttrib(instanceVBO, 7, 4, GL_FLOAT, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));
		// Makes it so the transform is only switched when drawing the next instance
		glVertexAttribDivisor(4, 1);
		glVertexAttribDivisor(5, 1);
		glVertexAttribDivisor(6, 1);
		glVertexAttribDivisor(7, 1);
	}
	// Unbind all to prevent accidentally modifying them
	VAO.Unbind();
	VBO.Unbind();
	instanceVBO.Unbind();
	EBO.Unbind();
}

void Mesh::Draw(Shader& shader, Camera& camera,int primType)
{
	shader.Activate();
	VAO.Bind();
	
	if (textures.size() != 0)
	{
		for (int i = 0; i < textures.size(); i++)
		{
			textures[i].texUnit(shader, "tex0", i);
			textures[i].Bind();
		}
	}
	
	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	camera.Matrix(shader, "camMatrix");

	// Draw the actual mesh
	if (instances == 1)
	{
		Modifier += 0.005f;
		std::vector <float> chargePos2 = { 0.5f * cos(Modifier), 0.5f * sin(Modifier * 2.0f), 0 };
		
		
		glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(instanceMatrix[0]));
		glUniform3f(glGetUniformLocation(shader.ID, "chargePos2"), chargePos2[0], chargePos2[1], chargePos2[2]);
		glUniform1f(glGetUniformLocation(shader.ID, "phi"), Modifier);
		glUniform1f(glGetUniformLocation(shader.ID, "theta"), Modifier);
		glDrawElements(primType, indices.size(), GL_UNSIGNED_INT, 0);
	}
	else
	{
		Modifier += 0.01;
		
		glUniform1f(glGetUniformLocation(shader.ID, "phi"), Modifier);
		glUniform1f(glGetUniformLocation(shader.ID, "theta"), Modifier);
		glDrawElementsInstanced(primType, indices.size(), GL_UNSIGNED_INT, 0,instances);
	}

}