#include "stdafx.h"
#include "FpsGame.h"
#include "FpsVisualTests.h"

using namespace Fps;

int _stdcall WinMain(struct HINSTANCE__ *hInstance, struct HINSTANCE__ *hPrevInstance,
	char *lpszCmdLine, int nCmdShow)
{
	//FpsVisualTests().ShowSkyBackground();
	//FpsVisualTests().LoadGroundAndWallTextures();
	//FpsVisualTests().LoadWorld();
	FpsGame().PlayGame();
	return 0;
}