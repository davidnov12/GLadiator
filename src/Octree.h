#pragma once

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>

#define ROOT_NODE 0
#define CHILD_COUNT 8

template <typename octreeData> class Octree {

public:

	typedef struct {
		octreeData data;
		
		glm::vec3 start;
		bool leaf = true;
		
		glm::vec3 end;
		GLuint gap;
		
		GLuint childs[CHILD_COUNT] = {0, 0, 0, 0,
									  0, 0, 0, 0};
	} OctreeNode;


	Octree(){

		if (sizeof(octreeData) % 16 != 0)
			std::cout << "bad type" << std::endl;

		OctreeNode n;
		n.start = glm::vec3(-1.0f, -1.0f, 1.0f);
		n.end = glm::vec3(1.0f, 1.0f, -1.0f);
		nodes.push_back(n);
	}


	Octree(glm::vec3 rootStart, glm::vec3 rootEnd) {
		OctreeNode n;
		n.start = glm::vec3(rootStart);
		n.end = glm::vec3(rootEnd);
		nodes.push_back(n);
	}


	OctreeNode* getOctree() {
		return nodes.data();
	}


	OctreeNode getNode(GLuint index) {
		return nodes.at(index);
	}


	GLuint getOctreeSize() {
		return nodes.size();
	}


	void loadToGPU() {

	}

private:

	std::vector<OctreeNode> nodes;

};