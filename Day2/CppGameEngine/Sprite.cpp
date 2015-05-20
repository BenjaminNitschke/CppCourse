#include "Sprite.h"
#include <GLFW/glfw3.h>
#include <GL/gl.h>

using namespace CppGameEngine;

void Sprite::Draw(float x, float y)
{
	glBindTexture(GL_TEXTURE_2D, texture->GetHandle());
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3f(initialX + x - width, initialY + y - height, 0);
	glTexCoord2d(0, 1);
	glVertex3f(initialX + x - width, initialY + y + height, 0);
	glTexCoord2d(1, 1);
	glVertex3f(initialX + x + width, initialY + y + height, 0);
	glTexCoord2d(1, 0);
	glVertex3f(initialX + x + width, initialY + y - height, 0);
	glEnd();
}