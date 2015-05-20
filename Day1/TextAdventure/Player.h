#pragma once
#include "Quest.h"

namespace TextAdventure
{
	class Player
	{
	public:
		Player();
		const std::string& GetCurrentLocation()
		{
			return currentQuest->GetName();
		}
		bool HasLostGame()
		{
			return currentQuest->GetName() != EXIT && currentQuest->HasChoices() == 0;
		}

		void MoveTo(const std::string& targetQuest);
		class QuestNotDefined : public std::exception {};

	protected:
		std::vector<Quest> allQuests;
		std::_Vector_iterator<std::_Vector_val<std::_Simple_types<TextAdventure::Quest>>> currentQuest;
	};
}