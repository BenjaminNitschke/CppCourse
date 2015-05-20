#include <memory>
#include <GLFW/glfw3.h>
#include "Texture.h"
#include "Sprite.h"
#include "SpaceGame.h"
#include <vector>

namespace SpaceInvaders
{
	// Provides us with a bunch of visual tests we can always execute and go back to
	class SpaceInvadersVisualTests : public SpaceGame
	{
	public:
		void ShowEmptyWindow()
		{
			Run([](){});
		}

		void ShowBlueBackground()
		{
			glClearColor(100 / 255.0f, 149 / 255.0f, 237 / 255.0f, 1.0f);
			Run([](){});
		}

		void DrawColoredTriangle()
		{
			Run([]()
			{
				glBegin(GL_TRIANGLES);
				glColor3f(1.f, 0.f, 0.f);
				glVertex3f(-0.6f, -0.4f, 0.f);
				glColor3f(0.f, 1.f, 0.f);
				glVertex3f(0.6f, -0.4f, 0.f);
				glColor3f(0.f, 0.f, 1.f);
				glVertex3f(0.f, 0.6f, 0.f);
				glEnd();
			});
		}

		void DrawTexturedBackground()
		{
			CreateBackground();
			Run([=]() { DrawAll(); });
		}

		void DrawPlayerShip()
		{
			CreateShip();
			Run([=]() { DrawAll(); });
		}

		void ControlPlayerShip()
		{
			CreateShip();
			Run([=]()
			{
				ControlShip();
				DrawAll();
			});
		}

		void DrawAllEnemies()
		{
			CreateEnemies();
			Run([=]()
			{
				DrawAll();
			});
		}

		void MoveAllEnemies()
		{
			CreateEnemies();
			Run([=]()
			{
				MoveEnemies();
				DrawAll();
			});
		}
	};
}