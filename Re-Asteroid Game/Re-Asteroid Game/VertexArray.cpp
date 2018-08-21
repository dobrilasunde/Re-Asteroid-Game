#include"VertexArray.hpp"
#include<GL\glew.h>

VertexArray::VertexArray(const float* verts, unsigned int numVerts, const unsigned int* indices, unsigned int numIndices): mNumVerts(numVerts), mNumIndices(numIndices)
{
	//create vertex array
	glGenVertexArrays(1, &mVertexArray);
	glBindVertexArray(mVertexArray);

	//create vertex buffer
	glGenBuffers(1, &mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, numVerts * 5 * sizeof(float), verts, GL_STATIC_DRAW);

	//create index buffer
	glGenBuffers(1, &mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	//specify the vertex attributes
	//position is 3 floats starting at offset 0
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1, //vertex attribute index
		2, //number of components (2 because of UV coordinates)
		GL_FLOAT, //type of each component 
		GL_FALSE, //not used for GL_FLOAT
		sizeof(float) * 5, //stride (usually size of each vertex)
		reinterpret_cast<void*> (sizeof(float) * 3)); //offset pointer
}

VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &mVertexBuffer);
	glDeleteBuffers(1, &mIndexBuffer);
	glDeleteVertexArrays(1, &mVertexArray);
}

void VertexArray::SetActive()
{
	glBindVertexArray(mVertexArray);
}