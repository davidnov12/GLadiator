#pragma once

#define CALC_TB
//#define CALC_NORM

#include <vector>
#include <iostream>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <objLoader/tiny_obj_loader.h>
#include <chrono>
#include <map>
#include "materials.h"

#define NO_TEX 0x0		// No texture
#define D_TEX 0x1		// Diffuse texture
#define S_TEX 0x2		// Specular texture
#define N_TEX 0x4		// Normal texture
#define DS_TEX 0x3		// Diffuse + Specular texture
#define DN_TEX 0x5		// Diffuse + Normal texture
#define DSN_TEX	0x7		// Diffuse + Specular + Normal texture


class Mesh {

public:

	typedef struct {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 uv;

		#ifdef CALC_TB
		glm::vec3 tangent;
		glm::vec3 bitangent;
		#endif

		GLuint materialID;
	} Vertex;

	typedef struct {
		glm::vec3 ambient = glm::vec3(0.0f);
		glm::vec3 diffuse = glm::vec3(0.0f);
		glm::vec3 specular = glm::vec3(0.0f);
		GLuint64 diffuseTexture = 0;
		//std::string diffuseTextureName = "diffuseTexture";
		GLuint64 specularTexture = 0;
		//std::string specularTextureName = "specularTexture";
		GLuint64 normalMap = 0;
	} Material;

	typedef enum {
		AMBIENT,
		DIFFUSE,
		SPECULAR,
		NORMAL,
		AO,
	} textureType;

	/**
	* \brief
	* \param file
	*/
	Mesh(std::string file, bool loadMaterials, Materials* texHandler, GLuint texMode = D_TEX);
	
	
	/**
	* \brief
	* \param goemetry
	* \param elements
	*/
	Mesh(std::vector<Mesh::Vertex> geometry, std::vector<GLuint> elements);


	/**
	* \brief
	*/
	~Mesh();


	/**
	* \brief
	* \param vertexMode
	*/
	void setMode(int texMode);


	/**
	* \brief
	*/
	void draw();


	/**
	* \brief
	*/
	void drawWithEBO();

	/**
	* \brief
	*/
	void drawArrays();


	/**
	* \brief
	* \param index
	* \return
	*/
	Material getMaterial(GLuint index);


	/**
	* \brief
	* \return
	*/
	Material* getAllMaterials();


	/**
	*/
	void setTextureName(GLuint meshID, textureType type, std::string name);

private:

	std::vector<Mesh::Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Mesh::Material> shapesMaterials;
	std::string mtlDir;
	std::unique_ptr<Materials> textures;
	GLuint vao, vbo, ebo, mode;
	GLuint64 indexCount, vertexCount;

	/**
	* \brief
	*/
	void prepareBuffers();
	
	
	/**
	* \brief
	*/
	bool setupBuffers();


	/**
	* \brief
	* \param file
	* \return
	*/
	bool loadModelFromFile(std::string file, bool loadMaterials);

};