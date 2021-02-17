#pragma once
#include<iostream>
#include<vector>
#include "Shader.h"
#include "texture.h"
#include "vertex.h"
class Mesh {
private:
	unsigned noOfVertices;
	unsigned noOfindices;

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	glm::mat4 ModelMatrix;
    
	
	void initVAO(Vertex* vertexArray, const unsigned& noOfVertices, GLuint* indexArray, const unsigned& noOfIndices) {
		
		this->noOfVertices = noOfVertices;
		this->noOfindices = noOfIndices;

		glCreateVertexArrays(1, &this->VAO);
		glBindVertexArray(this->VAO);
		//vertex buffer
	
		glGenBuffers(1, &this->VBO);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferData(GL_ARRAY_BUFFER,this-> noOfVertices*sizeof(Vertex),vertexArray, GL_STATIC_DRAW);

		// element buffer
		
		glGenBuffers(1, &this->EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->noOfindices * sizeof(GLuint), indexArray, GL_STATIC_DRAW);

		//vertex pointers input assembly
		//position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
		glEnableVertexAttribArray(0);
		//color
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
		glEnableVertexAttribArray(1);

		//texcoord
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
		glEnableVertexAttribArray(2);

		//Normal
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
		glEnableVertexAttribArray(3);


		glBindVertexArray(0);
	}
	void initModelMatrix() {
		this->position = glm::vec3(0.f);
		this->rotation = glm::vec3(0.f);
		this->scale = glm::vec3(1.f);
		this->ModelMatrix = glm::mat4(1.f);
		this->ModelMatrix = glm::translate(this->ModelMatrix, this->position);
		//rotation
		this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.x), glm::vec3(1.f, 0.f, 0.f));
		this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.y), glm::vec3(0.f, 1.f, 0.f));
		this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.z), glm::vec3(0.f, 0.f, 1.f));
		//scale
		this->ModelMatrix = glm::scale(this->ModelMatrix, this->scale);
	}
	void updateUniforms(Shader*shader) {
		shader->setMat4fv(this->ModelMatrix,"ModelMatrix");
	}
public:
	Mesh(Vertex* vertexArray, const unsigned& noOfVertices, GLuint* indexArray, const unsigned& noOfIndices) {
	
		this->initVAO(vertexArray, noOfVertices, indexArray, noOfIndices);
		this->initModelMatrix();
		
	}
	~Mesh() {
		glDeleteVertexArrays(1, &this->VAO);
		glDeleteBuffers(1, &this->VBO);
		glDeleteBuffers(1, &this->EBO);
	}
	void update() {

	}
	void render(Shader* shader) {
		this->updateUniforms(shader);
		shader->use();
		glBindVertexArray(this->VAO);

		
		
		glDrawElements(GL_TRIANGLES, this->noOfindices, GL_UNSIGNED_INT, 0);
	}
};