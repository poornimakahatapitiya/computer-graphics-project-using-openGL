#pragma once
#include<iostream>


#include<string>

#include<glew.h>
#include<glfw3.h>

#include<glm.hpp>
#include<SOIL2.h>
class Texture {
private:
	GLuint id;
	int height;
	int width;
	unsigned int type;
	GLint texture_Unit;
public:
	Texture(const char*fileName, GLenum type,GLint textureUnit) {
		this->type = type;
		this->texture_Unit = textureUnit;
		unsigned char* image = SOIL_load_image(fileName, &this->width, &this->height, NULL, SOIL_LOAD_RGBA);


		glGenTextures(1, &this->id);
		glBindTexture(type, this->id);

		glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		if (image) {
			glTexImage2D(type, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
			glGenerateMipmap(type);
		}
		else {
			std::cout << "ERROR TEXTURE LOADING FAILED" <<fileName<<"\n";
		}
		glActiveTexture(0);
		glBindTexture(type, 0);
		SOIL_free_image_data(image);
		
	}
	~Texture() {
		glDeleteTextures(1,&this->id);
	}
	inline GLuint getID() const { return this->id; }

	void bind() {
		glActiveTexture(GL_TEXTURE + this->texture_Unit);
		glBindTexture(this->type,this->id );
	}
	void unBind() {
		glActiveTexture(0);
		glBindTexture(this->type, 0);
	}
	inline GLint getTextureUnit() const { return this->texture_Unit; }
};