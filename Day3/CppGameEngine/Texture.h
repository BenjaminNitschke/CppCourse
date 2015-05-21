#pragma once
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <string>

namespace CppGameEngine
{
	class Texture
	{
	public:
		Texture(std::string filename);
		class ImageNotFound : public std::exception {};
		class UnsupportedPngImageFormat : public std::exception {};
		~Texture();
		int GetHandle()
		{
			return handle;
		}

	private:
		GLuint handle;
		int width;
		int height;
	};
}