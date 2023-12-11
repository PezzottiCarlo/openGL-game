#include "texture.h"

int Texture::test() {

	Texture texture("TestTexture");

	// test setTextureSettings
	assert(texture.getWidth() == 0);
	assert(texture.getHeight() == 0);

	texture.setTextureSettings(100, 100);

	assert(texture.getWidth() == 100);
	assert(texture.getHeight() == 100);

	return 0;
}