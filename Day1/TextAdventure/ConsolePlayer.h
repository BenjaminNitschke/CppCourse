#pragma once
#include "Player.h"
#include <iostream>

namespace TextAdventure
{
	class ConsolePlayer : public Player
	{
	public:
		void Run()
		{
			while (GetCurrentLocation() != EXIT)
				MoveTo(GetChoiceFromInput());
		}

		const std::string GetChoiceFromInput()
		{
			std::cout << currentQuest->description;
			if (currentQuest->choices.size() == 0)
				return EXIT;
			while (true)
			{
				int choiceIndex = 1;
				for (auto ch : currentQuest->choices)
					std::cout << choiceIndex++ << ": " << ch.first << '\n';
				int selection;
				std::cin >> selection;
				if (selection >= 1 && selection <= choiceIndex)
					return currentQuest->choices[selection - 1].second;
			}
		}
	};
}