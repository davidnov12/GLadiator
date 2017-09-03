#include "Skybox.h"

Skybox::Skybox(std::vector<std::string> walls){
	initVertices();
	initBuffers();
	
	if(!loadTextures(walls))
		throw std::exception("unable to load\n");
}

Skybox::~Skybox(){
	glDeleteTextures(1, &cubemapID);

	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
}

void Skybox::draw(){

	glDisable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LEQUAL);

	glBindVertexArray(vao);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapID);
	
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	//glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
}

bool Skybox::loadTextures(std::vector<std::string> walls){
	
	if (walls.size() != 6)
		return false;

	int width, height, comp;
	unsigned char* imageData;

	glGenTextures(1, &cubemapID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapID);

	for (int i = 0; i < walls.size(); i++) {
		imageData = stbi_load(walls.at(i).c_str(), &width, &height, &comp, 0);

		if (imageData) {
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, comp == 3 ? GL_RGB : GL_RGBA, width, height, 0, comp == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, imageData);
			stbi_image_free(imageData);
		}
		else {
			stbi_image_free(imageData);
			return false;
		}
	}
	
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	return true;
}

void Skybox::initVertices(){
	skyboxVertices = {
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	};

	for (int i = 0; i < skyboxVertices.size(); i++);
		//skyboxVertices.at(i) *= 12.5f;
}

void Skybox::initBuffers(){

	glCreateVertexArrays(1, &vao);
	glCreateBuffers(1, &vbo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * skyboxVertices.size(), skyboxVertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	skyboxVertices.clear();
}
