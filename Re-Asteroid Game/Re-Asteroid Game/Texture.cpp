#include"Texture.hpp"
#include<SDL.h>
#include<GL\glew.h>
#include<SOIL\SOIL.h>

Texture::Texture() : mTextureID(0), mWidth(0), mHeight(0)
{

}

Texture::~Texture()
{

}

bool Texture::Load(const std::string& fileName)
{
	int channels = 0;
	
	unsigned char* image = SOIL_load_image(
		fileName.c_str(), //name of file
		&mWidth, //stores width
		&mHeight, //stores height
		&channels, //stores number of channels
		SOIL_LOAD_AUTO //type of image file, or auto for any
	);

	if (image == nullptr)
	{
		SDL_Log("SOIL failed to load image %s: %s", fileName.c_str(), SOIL_last_result());
		return false;
	}

	int format = GL_RGB;
	if (channels == 4)
	{
		format = GL_RGBA;
	}

	glGenTextures(1, &mTextureID);
	glBindTexture(GL_TEXTURE_2D, mTextureID);

	glTexImage2D(
		GL_TEXTURE_2D, //texture target
		0, //level of detail
		format, //color format OpenGL should use
		mWidth,
		mHeight,
		0, //border, this value must be 0
		format, //color format of input data
		GL_UNSIGNED_BYTE, //bit depth of input data, unsigned byte specifies 8-bit channels
		image //pointer to raw image data
	);

	SOIL_free_image_data(image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return true;

}

void Texture::Unload()
{
	glDeleteTextures(1, &mTextureID);
}

void Texture::SetActive()
{
	glBindTexture(GL_TEXTURE_2D, mTextureID);
}