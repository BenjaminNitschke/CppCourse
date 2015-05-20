#include "stdafx.h"
#include "SpaceGame.h"
#include <GLFW/glfw3.h>
#include <functional>
#include <algorithm>

using namespace SpaceInvaders;

void SpaceGame::PlayGame()
{
	CreateBackground();
	CreateShip();
	CreateEnemies();
	Run([=]()
	{
		ControlShip();
		MoveEnemies();
		DrawAll();
	});
}

void SpaceGame::CreateBackground()
{
	background = std::make_shared<Sprite>(std::make_shared<Texture>("Background.png"),
		0.0f, 0.0f, 2.0f, 1.0f);
}

void SpaceGame::CreateShip()
{
	ship = std::make_shared<Sprite>(std::make_shared<Texture>("Ship.png"),
		0.0f, -0.8f, 0.075f, 0.075f);
	missileTexture = std::make_shared<Texture>("Missile.png");
}

void SpaceGame::ControlShip()
{
	if (leftPressed && shipPosition > -1.0f + ship->GetWidth())
		shipPosition -= GetTimeDelta();
	if (rightPressed && shipPosition < 1.0f - ship->GetWidth())
		shipPosition += GetTimeDelta();
	if (spacePressed && lastTimeShot < time - 0.33f)
		FireMissile();
	HandleMissiles();
}

void SpaceGame::FireMissile()
{
	lastTimeShot = time;
	activeMissiles.push_back(std::make_shared<Sprite>(missileTexture, shipPosition, -0.67f, 0.02f, 0.02f));
}

void SpaceGame::HandleMissiles()
{
	activeMissiles.erase(std::remove_if(activeMissiles.begin(), activeMissiles.end(),
		[=](std::shared_ptr<Sprite> missile)
		{
			return missile->IncreaseY(GetTimeDelta() * 3) || CollidingWithEnemyAndKilledIt(missile);
		}),
		activeMissiles.end());
}

bool SpaceGame::CollidingWithEnemyAndKilledIt(std::shared_ptr<Sprite> missile)
{
	for (auto enemy : enemies)
		if (enemy->DistanceTo(missile, enemiesPosition) < 0.05f)
		{
			enemy->IncreaseY(1.0f); // Move out of screen
			return true;
		}
	return false;
}

void SpaceGame::CreateEnemies()
{
	auto enemyTexture = std::make_shared<Texture>("Enemy.png");
	for (float y = 0.7f; y > 0.3f; y -= 0.3f)
		for (float x = -0.8f; x <= 0.8f; x += 0.2f)
			enemies.push_back(std::make_shared<Sprite>(enemyTexture, x, y, 0.05f, 0.05f));
}

void SpaceGame::MoveEnemies()
{
	enemiesPosition += (enemiesMovingRight ? 0.2f : -0.2f) * GetTimeDelta();
	if (enemiesPosition < -0.1f || enemiesPosition > 0.1f)
		enemiesMovingRight = !enemiesMovingRight;
}

void SpaceGame::DrawAll()
{
	if (background)
		background->Draw();
	for (auto missile : activeMissiles)
		missile->Draw();
	if (ship)
		ship->Draw(shipPosition);
	for (auto enemy : enemies)
		enemy->Draw(enemiesPosition);
}