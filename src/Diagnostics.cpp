#include "Diagnostics.h"

Diag::Diag(GLuint frameWidth, GLuint frameHeight) {
	width = frameWidth;
	height = frameHeight;
}

GLuint Diag::getRenderingTimeNS() {
	return (finish - start);
}

GLuint Diag::getTotalTimeNS() {
	return total;
}

GLfloat Diag::getFrameRate() {
	return 1000000000.0f / (finish - start);
}

GLfloat Diag::getFillrate() {
	return getFrameRate() * (width * height);
}

void Diag::startMeasure() {
	glQueryCounter(queryID[0], GL_TIMESTAMP);
}

void Diag::stopMeasure(){
	glQueryCounter(queryID[1], GL_TIMESTAMP);
	evaluate();
}

void Diag::changeWidth(GLuint newWidth){
	width = newWidth;
}

void Diag::changeHeight(GLuint newHeight){
	height = newHeight;
}

void Diag::evaluate() {

	GLint stopTimerAvailable = 0;

	while (!stopTimerAvailable)
		glGetQueryObjectiv(queryID[1], GL_QUERY_RESULT_AVAILABLE, &stopTimerAvailable);
	

	glGetQueryObjectui64v(queryID[0], GL_QUERY_RESULT, &start);
	glGetQueryObjectui64v(queryID[1], GL_QUERY_RESULT, &finish);

	
	if (first) {
		total += start;
		first = false;
	}
	
	else
		total += finish - start;
}