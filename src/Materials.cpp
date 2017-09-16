#define STB_IMAGE_IMPLEMENTATION

#include "Materials.h"


Materials::Materials() {}

Materials::~Materials() {
	glDeleteTextures(textureIDs.size(), textureIDs.data());
	glDeleteBuffers(1, &texBuffer);
}

bool Materials::loadTexture(std::string texturePath) {

	GLuint textureID;
	int width, height, comp;
	
	glGenTextures(1, &textureID);

	std::unique_ptr<unsigned char> imageData;

	stbi_set_flip_vertically_on_load(true);
	imageData.reset(stbi_load(texturePath.c_str(), &width, &height, &comp, STBI_default));
	
	if (imageData.get() == nullptr)
		return false;

	GLenum components = comp == 3 ? GL_RGB : comp == 1? GL_RED : GL_RGBA;

	glBindTexture(GL_TEXTURE_2D, textureID);
	
	glTexImage2D(GL_TEXTURE_2D, 0, components, width, height, 0, components, GL_UNSIGNED_BYTE, imageData.get());
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBindTexture(GL_TEXTURE_2D, 0);

	textureIDs.push_back(textureID);
	texHandles.push_back(glGetTextureHandleARB(textureIDs.at(textureIDs.size() - 1)));
	glMakeTextureHandleResidentARB(texHandles.at(texHandles.size() - 1));

	stbi_image_free(imageData.get());
	imageData.release();

	//std::cout << "Loaded " << texturePath.c_str() << std::endl;

	return true;
}

GLuint Materials::getTexture(unsigned int index) {
	
	if (index >= textureIDs.size())
		return 0;

	return textureIDs.at(index);
}

GLuint * Materials::getAllTextures() {
	return textureIDs.data();
}

int Materials::getTextureCount() {
	return textureIDs.size();
}

void Materials::buildTextureBuffer(GLuint binding){

	glGenBuffers(1, &texBuffer);
	//glBindBuffer(GL_SHADER_STORAGE_BUFFER, texBuffer);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, binding, texBuffer);
	glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(GLuint64) * texHandles.size(), texHandles.data(), GL_STATIC_DRAW);
	//glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

	std::cout << texHandles.size() << std::endl;

	for (int i = 0; i < texHandles.size(); i++)
		std::cout << "Texture: " << i << " Handle: " << texHandles[i] << std::endl;
}

void Materials::bindTextureBuffer(){
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, texBuffer);
}

void Materials::unbindTextureBuffer() {
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void Materials::addEmptyTexture() {
	texHandles.push_back(0);
}