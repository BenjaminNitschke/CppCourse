#include "Game.h"
#include "GLFW/glfw3.h"
#include <functional>
#include <algorithm>

using namespace CppGameEngine;
bool Game::leftPressed;
bool Game::rightPressed;
bool Game::upPressed;
bool Game::downPressed;
bool Game::spacePressed;

void OnKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_LEFT || key == GLFW_KEY_A)
		Game::leftPressed = action != GLFW_RELEASE;
	else if (key == GLFW_KEY_RIGHT || key == GLFW_KEY_D)
		Game::rightPressed = action != GLFW_RELEASE;
	else if (key == GLFW_KEY_UP || key == GLFW_KEY_W)
		Game::upPressed = action != GLFW_RELEASE;
	else if (key == GLFW_KEY_DOWN || key == GLFW_KEY_S)
		Game::downPressed = action != GLFW_RELEASE;
	else if (key == GLFW_KEY_SPACE || key == GLFW_KEY_LEFT_CONTROL || key == GLFW_KEY_RIGHT_CONTROL)
		Game::spacePressed = action != GLFW_RELEASE;
	else if (key == GLFW_KEY_ESCAPE)
		glfwSetWindowShouldClose(window, true);
}

Game::Game(std::string gameName)
{
	glfwInit();
	window = glfwCreateWindow(1280, 720, gameName.c_str(), NULL, NULL);
	glfwMakeContextCurrent(window);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glfwSetKeyCallback(window, OnKeyPressed);
}

Game::~Game()
{
	glfwTerminate();
}

void Game::Run(std::function<void()> tickMethod)
{
	lastTime = glfwGetTime();
	while (!glfwWindowShouldClose(window))
	{
		glfwGetWindowSize(window, &viewportWidth, &viewportHeight);
		glViewport(0, 0, viewportWidth, viewportHeight);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		time = glfwGetTime();
		timeThisTick = time - lastTime;
		lastTime = time;
		tickMethod();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}