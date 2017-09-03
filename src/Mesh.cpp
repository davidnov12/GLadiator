#define TINYOBJLOADER_IMPLEMENTATION
#include "Mesh.h"


Mesh::Mesh(std::string file, bool loadMaterials, Materials* texHandler, GLuint texMode) {

	if(texHandler == nullptr && loadMaterials)
		throw std::runtime_error("Cannot load obj model");
	
	mode = texMode;

	std::string dir;
	int tmp = -1;
	
	tmp = file.find_last_of("/");

	dir = file.substr(0, tmp + 1);
	mtlDir = dir;

	textures.reset(texHandler);

	if (!loadModelFromFile(file, loadMaterials))
		std::cout << "chyba" << std::endl;//throw std::runtime_error("Cannot load obj model");

	prepareBuffers();
	setupBuffers();
}

Mesh::Mesh(std::vector<Vertex> geometry, std::vector<GLuint> elements) {
	//std::cout << "BUFFERS\n";
	vertices = geometry;
	indices = elements;

	mode = D_TEX;
	prepareBuffers();
	setupBuffers();	
}

Mesh::~Mesh() {
	if(textures.get() != nullptr)
		textures.release();

	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
	glDeleteVertexArrays(1, &vao);
}

void Mesh::setMode(int texMode) {

	if (mode >= D_TEX && mode <= DSN_TEX)
		mode = texMode;
}

void Mesh::draw() {

	if (indexCount == 0)
		drawArrays();

	else
		drawWithEBO();
}

void Mesh::drawWithEBO() {
	
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	
}

void Mesh::drawArrays() {
	//textures.bindTextureBuffer();
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
	glBindVertexArray(0);
	//textures.unbindTextureBuffer();
}

Mesh::Material Mesh::getMaterial(GLuint index){
	return shapesMaterials.at(index);
}

Mesh::Material* Mesh::getAllMaterials() {
	return shapesMaterials.data();
}

void Mesh::setTextureName(GLuint meshID, textureType type, std::string name){
	/*if(type == DIFFUSE)
		shapesMaterials.at(meshID).diffuseTextureName = name;
	else if(type == SPECULAR)
		shapesMaterials.at(meshID).specularTextureName = name;*/
}

void Mesh::prepareBuffers() {
	glCreateVertexArrays(1, &vao);
	glCreateBuffers(1, &vbo);
	glCreateBuffers(1, &ebo);
}

bool Mesh::setupBuffers() {

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

	if (indices.size() > 0) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), indices.data(), GL_STATIC_DRAW);
	}

	//if (mode == VERTEX_CNT) {
	
		#ifdef CALC_TB

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat) + sizeof(GLuint), (void*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat) + sizeof(GLuint), (void*)(3 * sizeof(GLfloat)));
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat) + sizeof(GLuint), (void*)(6 * sizeof(GLfloat)));
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat) + sizeof(GLuint), (void*)(9 * sizeof(GLfloat)));
		glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat) + sizeof(GLuint), (void*)(12 * sizeof(GLfloat)));
		glVertexAttribIPointer(5, 1, GL_UNSIGNED_INT, 14 * sizeof(GLfloat) + sizeof(GLuint), (void*)(14 * sizeof(GLfloat)));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);
		glEnableVertexAttribArray(4);
		glEnableVertexAttribArray(5);

		#else
		
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat) + sizeof(GLuint), (void*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat) + sizeof(GLuint), (void*)(3 * sizeof(GLfloat)));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat) + sizeof(GLuint), (void*)(6 * sizeof(GLfloat)));
		glVertexAttribIPointer(3, 1, GL_UNSIGNED_INT, 8 * sizeof(GLfloat) + sizeof(GLuint), (void*)(8 * sizeof(GLfloat)));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);

		#endif
	

	/*
	else if (mode == VERTEX_SSBO){
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (8 * sizeof(GLfloat)) + (2 * sizeof(GLuint)), (void*)0);
		glVertexAttribIPointer(1, 1, GL_UNSIGNED_INT, (8 * sizeof(GLfloat)) + (2 * sizeof(GLuint)), (void*)(3 * sizeof(GLfloat)));
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, (8 * sizeof(GLfloat)) + (2 * sizeof(GLuint)), (void*)(3 * sizeof(GLfloat) + sizeof(GLuint)));
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, (8 * sizeof(GLfloat)) + (2 * sizeof(GLuint)), (void*)(6 * sizeof(GLfloat) + (2 * sizeof(GLuint))));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);
	}
	*/
	/*}
	else if (mode == VERTEX_CN) {
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
		glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)(8 * sizeof(GLfloat)));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
	}
	else if (mode == VERTEX_CT) {
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
	}
	else {
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(0);
	}*/

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	vertexCount = vertices.size();
	indexCount = indices.size();

	vertices.clear();
	indices.clear();

	return true;
}

bool Mesh::loadModelFromFile(std::string file, bool loadMaterials) {

	std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();

	tinyobj::attrib_t attr;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string err_out;
	GLint texID = 0;
	std::map<std::string, GLuint> mats;

	bool result = tinyobj::LoadObj(&attr, &shapes, &materials, &err_out, file.c_str(), mtlDir.c_str(), true);

	if (!err_out.empty()) {
		std::cout << err_out << std::endl;
		return false;
	}

	if (!result)
		return false;

	if(loadMaterials){
		for (int i = 0; i < materials.size(); i++) {
			mats.insert(std::pair<std::string, GLuint>(materials.at(i).name, i));

			Material m;
	
				m.ambient = glm::vec3(materials.at(i).ambient[0],
					materials.at(i).ambient[1],
					materials.at(i).ambient[2]);

				m.diffuse = glm::vec3(materials.at(i).diffuse[0],
					materials.at(i).diffuse[1],
					materials.at(i).diffuse[2]);

				m.specular = glm::vec3(materials.at(i).specular[0],
					materials.at(i).specular[1],
					materials.at(i).specular[2]);

				/*if (textures->loadTexture(mtlDir + materials.at(i).diffuse_texname)) {
					//std::cout << mtlDir << materials.at(shapes.at(shape).mesh.material_ids.at(0)).diffuse_texname << std::endl;
					m.diffuseTexture = texID;
					texID += 1;
				}*/
				/*if (textures->loadTexture(mtlDir + materials.at(i).diffuse_texname)) {
					m.diffuseTexture = texID;
					texID += 1;
				}*/

				if (mode == NO_TEX)
					continue;

				if (mode & D_TEX) {
					//std::cout << "DIFF\n";
					if (textures->loadTexture(mtlDir + materials.at(i).diffuse_texname)) {
						m.diffuseTexture = texID;
						texID += 1;
					}
					else
						textures->addEmptyTexture();
				}

				if (mode & S_TEX) {

					//std::cout << "SPEC\n";
					if (textures->loadTexture(mtlDir + materials.at(i).specular_texname)) {
						m.specularTexture = texID;
						texID += 1;
					}
					else
						textures->addEmptyTexture();
				}
				
				if (mode & N_TEX) {
					//std::cout << "NORM\n";
					if(textures->loadTexture(mtlDir + materials.at(i).normal_texname)) {
						m.normalMap = texID;
						texID += 1;
					}

					else if (textures->loadTexture(mtlDir + materials.at(i).bump_texname)) {
						m.normalMap = texID;
						texID += 1;
					}

					else
						textures->addEmptyTexture();
				}

		
			shapesMaterials.push_back(m);

		}

		//textures.buildTextureBuffer(bind);
		//std::cout << "BIND " << bind << std::endl;
	}
	//mats.at("name") = 2;

	for (GLuint64 shape = 0; shape < shapes.size(); shape++) {

		GLuint indexOffset = 0;
		for (GLuint64 f = 0; f < shapes.at(shape).mesh.num_face_vertices.size(); f++) {
			int v = shapes.at(shape).mesh.num_face_vertices.at(f);
			
			for (GLuint64 vtx = 0; vtx < v; vtx++) {
				tinyobj::index_t id = shapes.at(shape).mesh.indices.at(indexOffset + vtx);
				Vertex tmp;

				if (mats.size() > 0)
					tmp.materialID = mats.at(materials.at(shapes.at(shape).mesh.material_ids.at(0)).name);
				else
					tmp.materialID = 0;

				if (attr.vertices.size() > 0) {
					tmp.position.x = attr.vertices.at(3 * id.vertex_index);
					tmp.position.y = attr.vertices.at(3 * id.vertex_index + 1);
					tmp.position.z = attr.vertices.at(3 * id.vertex_index + 2);
				}

				if (attr.normals.size() > 0) {
					tmp.normal.x = attr.normals.at(3 * id.normal_index);
					tmp.normal.y = attr.normals.at(3 * id.normal_index + 1);
					tmp.normal.z = attr.normals.at(3 * id.normal_index + 2);
				}

				if (attr.texcoords.size() > 0) {
					try{
						tmp.uv.x = attr.texcoords.at(2 * id.texcoord_index);
						tmp.uv.y = attr.texcoords.at(2 * id.texcoord_index + 1);
					}
					catch (std::exception e) {
						tmp.uv.x = tmp.uv.y = 0.0;
					}
				}	
				
				//tmp.textureID = shape;
				//std::cout << materials.at(shapes.at(shape).mesh.material_ids.at(f)).diffuse_texname << std::endl;
				//std::cout << vtx << std::endl;
				
				vertices.push_back(tmp);
				
			}
			
#ifdef CALC_TB
			glm::vec3 edge1, edge2, tang, bitang;
			glm::vec2 deltaUV1, deltaUV2;
			float fx;

			// TRIANGLE 1

			edge1 = vertices.at(vertices.size() - 2).position - vertices.at(vertices.size() - 3).position;
			edge2 = vertices.at(vertices.size() - 1).position - vertices.at(vertices.size() - 3).position;

			deltaUV1 = vertices.at(vertices.size() - 2).uv; -vertices.at(vertices.size() - 3).uv;
			deltaUV2 = vertices.at(vertices.size() - 1).uv - vertices.at(vertices.size() - 3).uv;

			fx = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

			tang.x = fx * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
			tang.y = fx * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
			tang.z = fx * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
			tang = glm::normalize(tang);

			bitang.x = fx * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
			bitang.y = fx * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
			bitang.z = fx * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
			bitang = glm::normalize(bitang);

			vertices.at(vertices.size() - 3).tangent = tang;
			vertices.at(vertices.size() - 3).bitangent = bitang;
#ifdef CALC_NORM			
			vertices.at(vertices.size() - 3).normal = glm::cross(tang, bitang);
#endif

			// TRIANGLE 2
			
			edge1 = vertices.at(vertices.size() - 1).position - vertices.at(vertices.size() - 2).position;
			edge2 = vertices.at(vertices.size() - 3).position - vertices.at(vertices.size() - 2).position;

			deltaUV1 = vertices.at(vertices.size() - 1).uv; -vertices.at(vertices.size() - 2).uv;
			deltaUV2 = vertices.at(vertices.size() - 3).uv - vertices.at(vertices.size() - 2).uv;

			fx = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

			tang.x = fx * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
			tang.y = fx * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
			tang.z = fx * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
			tang = glm::normalize(tang);

			bitang.x = fx * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
			bitang.y = fx * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
			bitang.z = fx * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
			bitang = glm::normalize(bitang);

			vertices.at(vertices.size() - 2).tangent = tang;
			vertices.at(vertices.size() - 2).bitangent = bitang;
#ifdef CALC_NORM			
			vertices.at(vertices.size() - 2).normal = glm::cross(tang, bitang);
#endif

			// TRIANGLE 3

			edge1 = vertices.at(vertices.size() - 3).position - vertices.at(vertices.size() - 1).position;
			edge2 = vertices.at(vertices.size() - 2).position - vertices.at(vertices.size() - 1).position;

			deltaUV1 = vertices.at(vertices.size() - 3).uv; -vertices.at(vertices.size() - 1).uv;
			deltaUV2 = vertices.at(vertices.size() - 2).uv - vertices.at(vertices.size() - 1).uv;

			fx = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

			tang.x = fx * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
			tang.y = fx * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
			tang.z = fx * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
			tang = glm::normalize(tang);

			bitang.x = fx * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
			bitang.y = fx * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
			bitang.z = fx * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
			bitang = glm::normalize(bitang);

			vertices.at(vertices.size() - 1).tangent = tang;
			vertices.at(vertices.size() - 1).bitangent = bitang;
#ifdef CALC_NORM			
			vertices.at(vertices.size() - 1).normal = glm::cross(tang, bitang);
#endif

#endif


			indexOffset += v;
		}
		//std::cout << shapes.at(shape).mesh.material_ids.size() << " " << shapes.at(shape).mesh.indices.size() << std::endl;
		//std::cout << shape << "  " << mtlDir << materials.at(shapes.at(shape).mesh.material_ids.at(0)).name << std::endl;
		//std::cout << mtlDir << materials.size() << std::endl;
		
		
		//shapesIndices.push_back(shapes.at(shape).mesh.indices.size() + shapesIndices.at(shape));
		
	}

	//std::cout << shapesIndices.size() << std::endl;

	//for (GLuint shape = 0; shape < (shapesIndices.size() - 1); shape++)
	//	std::cout << shapesIndices.at(shape) << " " << shapesIndices.at(shape + 1) << std::endl;

	std::chrono::high_resolution_clock::time_point endTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> time = std::chrono::duration_cast<std::chrono::duration<double>>(endTime - startTime);

	std::cout << "verteices loaded " << vertices.size() << std::endl;
	std::cout << time.count() << " s" << std::endl;

	return true;
}

