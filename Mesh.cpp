#include "Mesh.h"
#include <vector>


Mesh::Mesh(const std::string& fileName) {
	IndexedModel model = OBJModel(fileName+".obj").ToIndexedModel();
	
	InitMesh(model);
}

Mesh::Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices)
{
	IndexedModel model;

	for (unsigned int i = 0; i < numVertices; i++) {
		model.positions.push_back(*vertices[i].GetPos());
		model.texCoords.push_back(*vertices[i].GetTextCordinates());
		model.normals.push_back(*vertices[i].GetNormals());
	}

	for (unsigned int i = 0; i < numIndices; i++) {
		model.indices.push_back(indices[i]);
	}

	InitMesh(model);

	////m_drawCount = numVertices;

	//m_drawCount = numIndices;
	//
	//std::vector<glm::vec3> positions;
	//std::vector<glm::vec2> textCordinates;

	//positions.reserve(numVertices);
	//textCordinates.reserve(numVertices);

	//for (unsigned int i = 0; i < numVertices; i ++) {
	//	positions.push_back(*vertices[i].GetPos());
	//	textCordinates.push_back(*vertices[i].GetTextCordinates());
	//}
}


void Mesh::InitMesh(const IndexedModel& model) {
	m_drawCount = model.indices.size();

	//Generate Vertex Array Objects
	glGenVertexArrays(1, &m_vertexArrayObject);

	//Bind Vertex Array
	glBindVertexArray(m_vertexArrayObject);

	//Generate Vertex Buffers on the GPU
	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);

	//Interpreting the Data
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//Generate Vertex Buffers on the GPU	
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXTCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.texCoords.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);

	//Interpreting the Data
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	//Generate Vertex Buffers on the GPU	
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(model.normals[0]), &model.normals[0], GL_STATIC_DRAW);

	//Interpreting the Data
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//Generate Vertex Buffers on the GPU	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);

	//Unbind Vertex Array
	glBindVertexArray(0);
}


Mesh::~Mesh()
{
	glDeleteBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::Draw() {
	glBindVertexArray(m_vertexArrayObject);

	glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0);

	//glDrawArrays(GL_TRIANGLES, 0, m_drawCount);

	glBindVertexArray(0);
}
