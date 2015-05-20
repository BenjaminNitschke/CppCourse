#include "stdafx.h"
#include "Player.h"

using namespace TextAdventure;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TextAdventureTests
{
	TEST_CLASS(PlayerTests)
	{
	public:
		PlayerTests()
			: player(std::make_shared<Player>()) {}
		std::shared_ptr<Player> player;

		TEST_METHOD(PlayerStartsInTheWoods)
		{
			Assert::AreEqual(player->GetCurrentLocation(), std::string("Woods"));
		}

		TEST_METHOD(PlayerCanMoveToRoadCastleOrCliff)
		{
			AssertPlayerCanMoveTo("Road");
			AssertPlayerCanMoveTo("Castle");
			AssertPlayerCanMoveTo("Cliff");
			Assert::ExpectException<Player::QuestNotDefined>([=]() { AssertPlayerCanMoveTo("Water"); });
		}

		void AssertPlayerCanMoveTo(std::string targetQuest)
		{
			player->MoveTo(targetQuest);
			Assert::AreEqual(player->GetCurrentLocation(), targetQuest);
			// Restore old quest for next AssertPlayerCanMoveTo call
			player->MoveTo("Woods");
		}

		TEST_METHOD(LoseGameByGoingToTheCliff)
		{
			player->MoveTo("Cliff");
			Assert::IsTrue(player->HasLostGame());
		}

		TEST_METHOD(LoseGameByFightingTheSpiderWithSword)
		{
			player->MoveTo("Road");
			player->MoveTo("AttackSpider");
			Assert::IsTrue(player->HasLostGame());
		}

		TEST_METHOD(WinGameByFightingTheSpiderWithSword)
		{
			player->MoveTo("Road");
			player->MoveTo("ThrowSword");
			player->MoveTo("CheckSpiderRemains");
			player->MoveTo("Exit");
			Assert::IsFalse(player->HasLostGame());
		}
	};
}