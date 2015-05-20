#include "stdafx.h"
#include <stdio.h>
#include <tchar.h>
#include <cstring>
#include "Program.h"
#include "ConsolePlayer.h"

using namespace TextAdventure;

int _tmain()
{
	printf("Welcome to our Adventure\n");
	ConsolePlayer().Run();
	return 0;
}

int Program::AddStringNumbers(const char* inputText)
{
	std::string text = std::string(inputText);
	if (text.empty())
		return 0;
	auto plusIndex = text.find('+');
	return std::stoi(text.substr(0, plusIndex)) + std::stoi(text.substr(plusIndex + 1));
}