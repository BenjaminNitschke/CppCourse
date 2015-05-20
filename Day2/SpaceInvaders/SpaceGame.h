#pragma once
#include <GLFW/glfw3.h>
#include <functional>
#include <vector>
#include "Sprite.h"
#include "Game.h"

namespace SpaceInvaders
{
	// Started with an empty window, then got extended while adding visual tests.
	// Normally there should be classes for each responsibility here:
	// Input, initialization, player ship, enemies, movement ai, etc.
	class SpaceGame : public CppGameEngine::Game
	{
	public:
		SpaceGame()
			: Game("Space Invaders") {}
		void PlayGame();
		void CreateBackground();
		void CreateShip();
		void ControlShip();
		void FireMissile();
		void HandleMissiles();
		bool CollidingWithEnemyAndKilledIt(std::shared_ptr<Sprite> missile);
		void CreateEnemies();
		void MoveEnemies();
		void DrawAll();
		
	private:
		double lastTimeShot;
		std::shared_ptr<Sprite> background;
		std::shared_ptr<Sprite> ship;
		float shipPosition = 0;
		std::shared_ptr<Texture> missileTexture;
		std::vector<std::shared_ptr<Sprite>> activeMissiles;
		std::vector<std::shared_ptr<Sprite>> enemies;
		float enemiesPosition = 0;
		bool enemiesMovingRight = true;
	};
}