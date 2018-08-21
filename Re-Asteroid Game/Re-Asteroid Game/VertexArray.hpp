#pragma once

class VertexArray
{
public:
	VertexArray(const float* verts, unsigned int numVerts, const unsigned int* indices, unsigned int numIndices);
	~VertexArray();
	void SetActive();
	unsigned int GetNumIndices() const { return mNumIndices; }
	unsigned int GetNumVerts() const { return mNumVerts; }

private:
	unsigned int mNumVerts;
	unsigned int mNumIndices;
	unsigned int mVertexBuffer; //OpenGL ID of the vertex buffer
	unsigned int mIndexBuffer; //OpenGL ID of the index buffer
	unsigned int mVertexArray; //OpenGL ID of the vertex array object
};