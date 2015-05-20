#include "stdafx.h"
#include "SpaceGame.h"
#include "SpaceInvadersVisualTests.h"

using namespace SpaceInvaders;

int _stdcall WinMain(struct HINSTANCE__ *hInstance, struct HINSTANCE__ *hPrevInstance,
	char *lpszCmdLine, int nCmdShow)
{
	//SpaceInvadersVisualTests().ShowEmptyWindow();
	//SpaceInvadersVisualTests().ShowBlueBackground();
	//SpaceInvadersVisualTests().DrawColoredTriangle();
	//SpaceInvadersVisualTests().DrawTexturedBackground();
	//SpaceInvadersVisualTests().DrawShip();
	//SpaceInvadersVisualTests().ControlShip();
	//SpaceInvadersVisualTests().DrawAllEnemies();
	//SpaceInvadersVisualTests().MoveAllEnemies();
	SpaceGame().PlayGame();
	return 0;
}