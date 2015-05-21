#pragma once
#include "Game.h"
#include "VertexPositionUV.h"
#include "Vector2D.h"

using namespace CppGameEngine;

namespace Fps
{
	class FpsGame : public CppGameEngine::Game
	{
	public:
		FpsGame();
		void PlayGame() override;
		void SetupWorld();
		void HandleInput();
		void DrawWorld();
		void SetupProjectionMatrix();
		void SetupCameraViewMatrix();
		void DrawGround();
		void DrawWalls();

	protected:
		std::shared_ptr<Texture> groundTexture;
		std::shared_ptr<Texture> wallTexture;
	private:
		std::vector<VertexPositionUV> vertices;
		float headingInDegree = 0;
		Vector2D playerPosition = Vector2D();
	};
}