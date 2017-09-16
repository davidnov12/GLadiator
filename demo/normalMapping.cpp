/*#include "../src/Window.h"
#include "../src/Shader.h"
#include "../src/Materials.h"
#include "../src/Mesh.h"
#include "../src/CameraCallbacks.h"

int main(void) {

	Window w(900, 900, "GLadiator", true);
	Shader s;
	Materials ts;	
	Mesh m("../test/plane.obj", true, &ts, DN_TEX);
	
	ts.buildTextureBuffer(0);

	s.attachShader(Shader::VERTEX, "../test/test_shader.vs");
	s.attachShader(Shader::FRAGMENT, "../test/test_shader.fs");
	s.linkProgram();

	w.setMouseCallback(mouse_callback);
	
	w.enableFeature(GL_DEPTH_TEST);
	//w.enableFeature(GL_MULTISAMPLE);

	while (!w.isClosed()) {

	float current = glfwGetTime();
	delta = current - last;
	last = current;

	key_callback(w.getWindow());

	glClearColor(0.001f, 0.701f, 0.951f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 view;

	s.useProgram();

	glm::mat4 model;
	model = glm::scale(model, glm::vec3(0.2340325f, 0.2340325f, 0.2340325f));
	model = glm::translate(model, glm::vec3(0.0f, -2.04f, -0.75f));
	model = glm::rotate(model, glm::radians(10.0f), glm::vec3(1.0, 0.0, 0.0));

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
	view = c.getViewMatrix();
	
	glUniformMatrix4fv(glGetUniformLocation(s.getProgram(), "model"), 1, false, &model[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(s.getProgram(), "view"), 1, false, &view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(s.getProgram(), "projection"), 1, false, &projection[0][0]);
	glUniform3f(glGetUniformLocation(s.getProgram(), "viewPos"), c.getPosition().x, c.getPosition().y, c.getPosition().z);
	glUniform1i(glGetUniformLocation(s.getProgram(), "meshID"), 1);

	m.drawArrays();

	w.swapBuffers();

	
	}

	return 0;

}*/