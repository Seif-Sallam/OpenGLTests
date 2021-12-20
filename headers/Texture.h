#pragma once
#include "../headers/Renderer.h"

class Texture
{
public:
	Texture(const std::string &filePath);
	~Texture();
	void Bind(unsigned int slot = 0);
	void UnBind();

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }

private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char *m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
};
