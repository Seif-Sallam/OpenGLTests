#pragma once
#include <vector>
#include "Renderer.h"

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;
	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT:
			return 4;
		case GL_UNSIGNED_INT:
			return 4;
		case GL_UNSIGNED_BYTE:
			return 1;
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout
{
public:
	VertexBufferLayout()
		: m_Stride(0)
	{
	}

	template <class T>
	void Push(unsigned int count)
	{
		if (typeid(T) == typeid(float))
		{
			m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
			m_Stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count;
		}
		else if (typeid(T) == typeid(unsigned int))
		{
			m_Elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
			m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
		}
		else if (typeid(T) == typeid(unsigned char))
		{
			m_Elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
			m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
		}
		else
			ASSERT(false);
	}

	inline const std::vector<VertexBufferElement>
	GetElements() const
	{
		return m_Elements;
	}
	inline unsigned int GetStride() const { return m_Stride; }

private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;
};
