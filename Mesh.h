#pragma once

#include <glm\glm\glm.hpp>
#include <glew\glew.h>
#include "obj_loader.h"

class Vertex {
public:
	Vertex(const glm::vec3& pos, const glm::vec2& textCordinates, const glm::vec3& normals = glm::vec3(0 , 0 , 0)) {
		this->pos = pos;
		this->textCordinates = textCordinates;
		this->normals = normals;
	}	

	inline glm::vec3* GetPos() {
		return &pos;
	}

	inline glm::vec2* GetTextCordinates() {
		return &textCordinates;
	}

	inline glm::vec3* GetNormals() {
		return &normals;
	}

protected:
	
private:
	glm::vec3 pos;
	glm::vec2 textCordinates;
	glm::vec3 normals;
};

class Mesh
{
public:
	Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
	Mesh(const std::string& fileName);

	void Draw();

	virtual ~Mesh();

private:
	enum {
		POSITION_VB,
		TEXTCOORD_VB,
		NORMAL_VB,

		INDEX_VB,

		NUM_BUFFERS		
	};

	void InitMesh(const IndexedModel& model);

	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_drawCount;
};

