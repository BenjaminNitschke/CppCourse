#pragma once
#include "stdafx.h"
#include <GLFW/glfw3.h>
#include "Texture.h"
#include "Sprite.h"
#include "FpsGame.h"

using namespace CppGameEngine;

namespace Fps
{
	class FpsVisualTests : public FpsGame
	{
	public:
		void ShowSkyBackground()
		{
			Run([]() {});
		}

		void LoadGroundAndWallTextures()
		{
			auto ground = std::make_shared<Sprite>(groundTexture, -0.5f, 0.0f, 0.5f, 0.5f);
			auto wall = std::make_shared<Sprite>(wallTexture, 0.5f, 0.0f, 0.5f, 0.5f);
			Run([=]()
			{
				ground->Draw();
				wall->Draw();
			});
		}

		void LoadWorld()
		{
			SetupWorld();
			Run([=]()
			{
				DrawWorld();
			});
		}
	};
}