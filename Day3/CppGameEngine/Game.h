#pragma once
#include <GLFW/glfw3.h>
#include <functional>
#include <vector>
#include "Sprite.h"

namespace CppGameEngine
{
	// Started with an empty window, then got extended while adding visual tests.
	// Normally there should be classes for each responsibility here:
	// Input, initialization, player ship, enemies, movement ai, etc.
	class Game
	{
	public:
		Game(std::string gameName);
		virtual ~Game();
		void Run(std::function<void()> tickMethod);
		virtual void PlayGame() = 0;
		static bool leftPressed;
		static bool rightPressed;
		static bool upPressed;
		static bool downPressed;
		static bool spacePressed;
		float GetTimeDelta() { return static_cast<float>(timeThisTick); }

	private:
		GLFWwindow* window;
		double lastTime;
		double timeThisTick;
	protected:
		double time;
		int viewportWidth, viewportHeight;
	};
}