#pragma once

class VertexBuffer
{
public:
	VertexBuffer(const void* data, const unsigned int size);

	~VertexBuffer();

	void Bind() const;
	void UnBind() const;
private:
	unsigned int m_RendererID;
};

