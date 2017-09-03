#pragma once

#include <GL/glew.h>
#include <vector>
#include <iostream>
#include <memory>
#include <stb/stb_image.h>


class Materials {

public:


	/**
	* \brief
	*/
	Materials();


	/**
	* \brief
	*/
	~Materials();


	/**
	* \brief
	* \param texturePath
	* \param alpha
	* \return
	*/
	bool loadTexture(std::string texturePath);
	

	/**
	* \brief
	* \param index
	* \return
	*/
	GLuint getTexture(unsigned int index);
	
	
	/**
	* \brief
	* \return
	*/
	GLuint* getAllTextures();


	/**
	* \brief
	* \return
	*/
	int getTextureCount();


	/**
	* \brief
	*/
	void buildTextureBuffer(GLuint binding);


	/**
	*/
	void bindTextureBuffer();


	/**
	*/
	void unbindTextureBuffer();

	/**
	*/
	void addEmptyTexture();

private:

	std::vector<GLuint> textureIDs;
	std::vector<GLuint64> texHandles;
	GLuint texBuffer;

};