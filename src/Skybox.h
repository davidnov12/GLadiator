#pragma once

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <stb/stb_image.h>

class Skybox {

public:

	Skybox(std::vector<std::string> walls);
	~Skybox();

	void draw();

private:
	
	GLuint vao, vbo, cubemapID;
	std::vector<GLfloat> skyboxVertices;

	bool loadTextures(std::vector<std::string> walls);

	void initVertices();
	void initBuffers();

};