#pragma once
#include <string.h>
#include <iostream>
#include <glew\glew.h>
#include <std_image\stb_image.h>
#include <cassert>

class Texture
{
public:
	Texture(const std::string& fileName);

	void Bind(unsigned int unit);

	virtual ~Texture();

private:
	GLuint m_texture;
};

