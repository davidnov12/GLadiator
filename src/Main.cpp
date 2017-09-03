/*#undef CALC_TB

#include <iostream>
#include <stdlib.h>
#include "Shader.h"
#include "Window.h"
#include "Materials.h"
#include "FPSCamera.h"
#include "Mesh.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "CameraCallbacks.h"
#include "Diagnostics.h"
#include "Octree.h"
#include "Skybox.h"





int main(void) {

	/*std::string vs = "#version 450\nlayout (location = 0) in vec3 pos;\nvoid main(){gl_Position = vec4(pos, 1.0);}";
	std::string fs = "#version 450\nout vec4 color;\nvoid main(){color = vec4(0.0, 1.0, 0.5, 1.0);}";

	bool ex;

	Window w(600, 200, "GLadiator", true);

	Shader s;

	Textures t;

	Mesh m("../test/Lara_Croft/Lara_Croft.obj");
	//Mesh m("../test/abcd");

	if(t.loadTexture("image.jpg")) std::cout << "bad ERROR\n";

	if(!t.loadTexture("../test/path.png")) std::cout << "ok ERROR\n";

	std::cout << t.getTextureCount() << std::endl;

	std::cout << t.getTexture(0) << std::endl;

	ex = s.attachShader(Shader::VERTEX, vs, SHADER_CODE);
	std::cout << "VERTEX " << ex << std::endl;
	
	ex = s.attachShader(Shader::FRAGMENT, "../test/fragment.txt", SHADER_FILE);
	std::cout << "FRAGMENT " << ex << std::endl;
	
	ex = s.linkProgram();
	std::cout << "LINK " << ex << std::endl;
	
	s.useProgram();
	std::cout << s.getProgram() << std::endl;
	
	w.getWindow();

	std::string file = "../dir1/dir2/fit";
	std::string dir;
	int tmp = -1;

	tmp = file.find_last_of("/");

	dir = file.substr(0, tmp);

	std::cout << dir << std::endl;

	while (!w.isClosed()) {
		glClearColor(0.2f, 0.9f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		w.swapBuffers();
	}

	//system("pause");*/

	//Octree<int> o;

	/*Mesh::Vertex v1 = {
		glm::vec3(-0.9f, -0.9f, 0.0f),
		glm::vec3(0.0f),
		glm::vec2(0.0f),
		1
	};
	Mesh::Vertex v2 = {
		glm::vec3(0.9f, -0.9f, 0.0f),
		glm::vec3(0.0f),
		glm::vec2(0.0f),
		2
	};
	Mesh::Vertex v3 = {
		glm::vec3(0.0f, 0.9f, 0.0f),
		glm::vec3(0.0f),
		glm::vec2(0.0f),
		2
	};
	std::vector<Mesh::Vertex> geom;
	std::vector<GLuint> ebo;
	geom.push_back(v1);
	geom.push_back(v2);
	geom.push_back(v3);


	Window w(900, 900, "GLadiator", true);
	Shader s;
	//Materials ts;
	
	

	//ts.buildTextureBuffer(0);

	s.attachShader(Shader::VERTEX, "../test/ray.vert");
	s.attachShader(Shader::GEOMETRY, "../test/ray.geom");
	s.attachShader(Shader::FRAGMENT, "../test/ray.frag");
	s.linkProgram();

	w.setMouseCallback(mouse_callback);
	w.enableFeature(GL_DEPTH_TEST);
	w.enableFeature(GL_MULTISAMPLE);
	
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	std::vector<glm::vec3> scr;

	while (!w.isClosed()) {
		
		float current = glfwGetTime();
		delta = current - last;
		last = current;

		key_callback(w.getWindow());

		//glClearColor(0.201f, 0.701f, 0.401f, 1.0f);
		glClearColor(0.01f, 0.01f, 0.01f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		s.useProgram();

		scr = c.getScreenCoords();
		glUniform3f(glGetUniformLocation(s.getProgram(), "screenCoords[0]"), scr[0].x, scr[0].y, scr[0].z);
		glUniform3f(glGetUniformLocation(s.getProgram(), "screenCoords[1]"), scr[1].x, scr[1].y, scr[1].z);
		glUniform3f(glGetUniformLocation(s.getProgram(), "screenCoords[2]"), scr[2].x, scr[2].y, scr[2].z);
		glUniform3f(glGetUniformLocation(s.getProgram(), "screenCoords[3]"), scr[3].x, scr[3].y, scr[3].z);

		glUniform3f(glGetUniformLocation(s.getProgram(), "viewPos"), c.getPosition().x, c.getPosition().y, c.getPosition().z);
		glUniform3f(glGetUniformLocation(s.getProgram(), "lightPos"), 0.2, 0.5, 0.5);

		glDrawArrays(GL_POINTS, 0, 1);
		
		w.swapBuffers();

	}

	return 0;
}*/


#undef CALC_TB

#include <iostream>
#include <stdlib.h>
#include "Shader.h"
#include "Window.h"
#include "Materials.h"
#include "FPSCamera.h"
#include "Mesh.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "CameraCallbacks.h"
#include "Diagnostics.h"
#include "Octree.h"
#include "Skybox.h"





int main(void) {

	/*std::string vs = "#version 450\nlayout (location = 0) in vec3 pos;\nvoid main(){gl_Position = vec4(pos, 1.0);}";
	std::string fs = "#version 450\nout vec4 color;\nvoid main(){color = vec4(0.0, 1.0, 0.5, 1.0);}";

	bool ex;

	Window w(600, 200, "GLadiator", true);

	Shader s;

	Textures t;

	Mesh m("../test/Lara_Croft/Lara_Croft.obj");
	//Mesh m("../test/abcd");

	if(t.loadTexture("image.jpg")) std::cout << "bad ERROR\n";

	if(!t.loadTexture("../test/path.png")) std::cout << "ok ERROR\n";

	std::cout << t.getTextureCount() << std::endl;

	std::cout << t.getTexture(0) << std::endl;

	ex = s.attachShader(Shader::VERTEX, vs, SHADER_CODE);
	std::cout << "VERTEX " << ex << std::endl;

	ex = s.attachShader(Shader::FRAGMENT, "../test/fragment.txt", SHADER_FILE);
	std::cout << "FRAGMENT " << ex << std::endl;

	ex = s.linkProgram();
	std::cout << "LINK " << ex << std::endl;

	s.useProgram();
	std::cout << s.getProgram() << std::endl;

	w.getWindow();

	std::string file = "../dir1/dir2/fit";
	std::string dir;
	int tmp = -1;

	tmp = file.find_last_of("/");

	dir = file.substr(0, tmp);

	std::cout << dir << std::endl;

	while (!w.isClosed()) {
	glClearColor(0.2f, 0.9f, 0.6f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	w.swapBuffers();
	}

	//system("pause");*/

	//Octree<int> o;

	/*Mesh::Vertex v1 = {
	glm::vec3(-0.9f, -0.9f, 0.0f),
	glm::vec3(0.0f),
	glm::vec2(0.0f),
	1
	};
	Mesh::Vertex v2 = {
	glm::vec3(0.9f, -0.9f, 0.0f),
	glm::vec3(0.0f),
	glm::vec2(0.0f),
	2
	};
	Mesh::Vertex v3 = {
	glm::vec3(0.0f, 0.9f, 0.0f),
	glm::vec3(0.0f),
	glm::vec2(0.0f),
	2
	};
	std::vector<Mesh::Vertex> geom;
	std::vector<GLuint> ebo;
	geom.push_back(v1);
	geom.push_back(v2);
	geom.push_back(v3);*/


	Window w(900, 900, "GLadiator", true);
	Shader s, u;
	Materials ts;
	//Shader h;

	std::vector<std::string> faces = { "../test/skybox/nightsky_rt.tga", "../test/skybox/nightsky_lf.tga", "../test/skybox/nightsky_up.tga", "../test/skybox/nightsky_dn.tga", "../test/skybox/nightsky_bk.tga", "../test/skybox/nightsky_ft.tga" };

	Skybox b(faces);
	//Mesh m(geom, ebo);
	//Mesh m("../test/dragon.obj");
	//Mesh m("../test/Lara_Croft/Lara_Croft.obj", true, &ts, DN_TEX);
	Mesh m("../test/US Galaxy/galaxy.obj", false, nullptr, NO_TEX);
	//Mesh m("../test/Aventador/Avent.obj");
	//Mesh e("../test/hairball.obj", false, 0);
	//Mesh m("../test/San Miguel/san-miguel-low-poly.obj");
	//Mesh m("../test/F-111/Airplane F111.obj");
	//Mesh n("../test/Pumpkin/potiron.obj", true, &ts);
	//Mesh m("../test/sponza.obj", false, nullptr, NO_TEX);
	//Mesh m("../test/Alduin/alduin.obj", true, &ts, DN_TEX);

	ts.buildTextureBuffer(0);

	s.attachShader(Shader::VERTEX, "../test/test_shader.vs");
	s.attachShader(Shader::FRAGMENT, "../test/test_shader.fs");
	s.linkProgram();

	u.attachShader(Shader::VERTEX, "../test/skybox_shader.vs");
	u.attachShader(Shader::FRAGMENT, "../test/skybox_shader.fs");
	u.linkProgram();

	/*h.attachShader(Shader::VERTEX, "../test/test_shader.vs");
	h.attachShader(Shader::FRAGMENT, "../test/test_shader.fs");
	h.linkProgram();*/

	w.setMouseCallback(mouse_callback);
	//w.setKeyCallback(key_callback);
	//w.setWindowProperty(GLFW_RESIZABLE, GL_FALSE);
	w.enableFeature(GL_DEPTH_TEST);
	w.enableFeature(GL_MULTISAMPLE);
	//glDisable(GL_CULL_FACE);

	//Diag d(900, 900);

	while (!w.isClosed()) {

		float current = glfwGetTime();
		delta = current - last;
		last = current;

		key_callback(w.getWindow());

		glClearColor(0.001f, 0.701f, 0.951f, 1.0f);
		//glClearColor(0.201f, 0.701f, 0.401f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glClear(0x4100);


		glm::mat4 view;


		//std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();
		//d.startMeasure();
		s.useProgram();

		glm::mat4 model;
		//model = glm::scale(model, glm::vec3(0.2340325f, 0.2340325f, 0.2340325f));
		model = glm::scale(model, glm::vec3(0.0195f, 0.0195f, 0.0195f));
		//model = glm::scale(model, glm::vec3(0.215f, 0.215f, 0.215f));
		//model = glm::scale(model, glm::vec3(0.000195f, 0.000195f, 0.000195f));
		//model = glm::scale(model, glm::vec3(0.0009202f, 0.0009202f, 0.0009202f));
		model = glm::translate(model, glm::vec3(0.0f, -2.04f, -0.75f));
		//model = glm::translate(model, glm::vec3(0.0f, -1.74f, 0.75f));

		glm::mat4 projection;
		//projection = c.getProjectionMatrix(600, 600);
		projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
		//projection = glm::perspective(glm::radians(45.f), 1.0f, 0.1f, 100.f);
		view = c.getViewMatrix();
		glUniformMatrix4fv(glGetUniformLocation(s.getProgram(), "model"), 1, false, &model[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(s.getProgram(), "view"), 1, false, &view[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(s.getProgram(), "projection"), 1, false, &projection[0][0]);

		glUniform1i(glGetUniformLocation(s.getProgram(), "meshID"), 1);

		m.drawArrays();
		//d.stopMeasure();
		//h.useProgram();

		u.useProgram();
		view = glm::mat4(glm::mat3(c.getViewMatrix()));

		glUniformMatrix4fv(glGetUniformLocation(u.getProgram(), "view"), 1, false, &view[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(s.getProgram(), "projection"), 1, false, &projection[0][0]);

		//b.draw();

		//model = glm::mat4();
		//model = glm::scale(model, glm::vec3(0.0195f, 0.0195f, 0.0195f));
		//glUniformMatrix4fv(glGetUniformLocation(s.getProgram(), "model"), 1, false, &model[0][0]);
		//glUniformMatrix4fv(glGetUniformLocation(s.getProgram(), "view"), 1, false, &view[0][0]);
		//glUniformMatrix4fv(glGetUniformLocation(s.getProgram(), "projection"), 1, false, &projection[0][0]);

		//glUniform1i(glGetUniformLocation(s.getProgram(), "meshID"), 2);

		//n.drawArrays();
		/*
		glUniform1i(glGetUniformLocation(s.getProgram(), "meshID"), 3);
		model = glm::mat4();
		model = glm::scale(model, glm::vec3(0.105f, 0.105f, 0.105f));
		model = glm::translate(model, glm::vec3(-0.4f, 0.0f, -0.7f));
		glUniformMatrix4fv(glGetUniformLocation(s.getProgram(), "model"), 1, false, &model[0][0]);
		e.drawArrays();*/

		/*std::vector<glm::vec3> x;
		x = c.getScreenCoords();

		std::cout << x[0].x << " " << x[0].y << " " << x[0].z << std::endl;
		std::cout << x[1].x << " " << x[1].y << " " << x[1].z << std::endl;
		std::cout << x[2].x << " " << x[2].y << " " << x[2].z << std::endl;
		std::cout << x[3].x << " " << x[3].y << " " << x[3].z << std::endl;*/

		w.swapBuffers();

		//system("pause");
		//std::cout << "FRAME\n";
		//d.stopMeasure();
		//std::cout << d.getFrameRate() << std::endl;
		//std::cout << d.getFillrate() << std::endl;
		//std::chrono::high_resolution_clock::time_point endTime = std::chrono::high_resolution_clock::now();
		//std::chrono::duration<double> time = std::chrono::duration_cast<std::chrono::duration<double>>(endTime - startTime);

		//std::cout << time.count() << " s" << std::endl;
	}

	return 0;
}