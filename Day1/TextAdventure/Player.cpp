#include "stdafx.h"
#include "Player.h"

TextAdventure::Player::Player()
{
	allQuests.push_back(Quest("Woods",
		"You are in the woods. There is a road to the north,\n"
		"a castle west of your position and a cliff on the east.\n"
		"Which way do you want to go?\n",
		std::vector<std::pair<std::string, std::string>>
		{
			{ "Go North", "Road" },
			{ "Go West", "Castle" },
			{ "Go East", "Cliff" }
		}));
	allQuests.push_back(Quest("Road",
		"You travel down the road about 100 metres and you encounter a giant spider.\n"
		"Your throat goes dry and your knees to shake! What will you do?\n",
		std::vector<std::pair<std::string, std::string>>
		{
			{ "Attempt to attack the spider with your sword.", "AttackSpider" },
			{ "Throw your sword in the off chance it might kill it.", "ThrowSword" },
			{ "RUN FOR YOUR LIFE!", "RunAway" }
		}));
	allQuests.push_back(Quest("Castle",
		"The Castle is closed.\n"
		"Seems no one is home and you do not have a key to open the door.\n"
		"From here you can go east back into the woods or\n"
		"approach another cliff in the west.\n",
		std::vector<std::pair<std::string, std::string>>
		{
			{ "Go East", "Woods" },
			{ "Go West", "Cliff" }
		}));
	allQuests.push_back(Quest("Cliff",
		"As you approach the cliff the ground becomes unstable and\n"
		"you fall to your death!\n"
		"Game Over! This was a quite un-hero like death, try again.\n",
		std::vector<std::pair<std::string, std::string>>()));
	allQuests.push_back(Quest("AttackSpider",
		"You viscously swing your sword at the spiders general direction.\n"
		"The swing was so great, your arms jolts out of place,\n"
		"creating a surge of pain.\n"
		"Your arm is now broken, and you fall to the ground in pain....\n"
		"The spider launches 3 metres straight into your body...\n"
		"What on earth is it doing?\n"
		"Oh My God! The spider is devouring everything....\n"
		"All that remained was bones of the once mobile adventurer.\n",
		std::vector<std::pair<std::string, std::string>>()));
	allQuests.push_back(Quest("ThrowSword",
		"You throw your sword and hit the spider in one of its eyes.\n"
		"It screams in utter pain and runs away. Lucky shot by you.\n"
		"What do you want to do next?\n",
		std::vector<std::pair<std::string, std::string>>
		{
			{ "Check out the place the spider was protecting", "CheckSpiderRemains"},
			{ "Go back the woods in the south, you are lucky you survived", "Woods" }
		}));
	allQuests.push_back(Quest("RunAway",
		"You try to run away, but the spider still sees you as a threat.\n"
		"The spider drives you to the cliff in the east.\n"
		"Do you want to approach the cliff\n"
		"or turn around and face the spider?\n",
		std::vector<std::pair<std::string, std::string>>
		{
			{ "Approach the cliff", "Cliff"},
			{ "Go back the road and face the spider", "Road" }
		}));
	allQuests.push_back(Quest("CheckSpiderRemains",
		"You find the holy grail, this is what you have been searching for your\n"
		"whole life. You go home to your village to be celebrated as a hero!\n",
		std::vector<std::pair<std::string, std::string>>
		{
			{ "Play again?", "Woods" },
			{ "Exit", "Exit" },
		}));
	allQuests.push_back(Quest("Exit",
		"Game Over.\n",
		std::vector<std::pair<std::string, std::string>>()));
	currentQuest = std::find(allQuests.begin(), allQuests.end(), "Woods");
}

void TextAdventure::Player::MoveTo(const std::string & targetQuest)
{
	currentQuest = std::find(allQuests.begin(), allQuests.end(), targetQuest);
	if (currentQuest == allQuests.end())
		throw QuestNotDefined();
}