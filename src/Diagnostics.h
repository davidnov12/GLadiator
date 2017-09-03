#pragma once

#include <GL/glew.h>


class Diag {

public:

	Diag() {}
	Diag(GLuint frameWidth, GLuint frameHeight);
	~Diag() {}

	GLuint getRenderingTimeNS();
	GLuint getTotalTimeNS();
	GLfloat getFrameRate();
	GLfloat getFillrate();

	void startMeasure();
	void stopMeasure();

	void changeWidth(GLuint newWidth);
	void changeHeight(GLuint newHeight);

private:

	GLuint64 start, finish, total;
	GLuint width = 0, height = 0;
	unsigned int queryID[2];
	bool first = true;

	void evaluate();

};