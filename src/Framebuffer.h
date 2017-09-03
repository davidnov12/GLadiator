#pragma once

#include <GL/glew.h>
#include <iostream>

class Framebuffer {

public:

	Framebuffer(GLuint width, GLuint height);
	~Framebuffer();

	void bind();
	void unbind();

private:

	GLuint fbo, colorbuffer, depthbuffer;

};