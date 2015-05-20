#pragma once

namespace TextAdventure
{
	class Quest
	{
	public:
		Quest(const std::string &name, const std::string &description,
			const std::vector<std::pair<std::string, std::string>> &choices)
			: name(name), description(description), choices(choices) {}

		const std::string& GetName()
		{
			return name;
		}

		bool operator==(const std::string &checkName) const
		{
			return name == checkName;
		}

		bool HasChoices()
		{
			return choices.size() > 0;
		}

		#define EXIT "Exit"
		std::string name;
		std::string description;
		std::vector<std::pair<std::string, std::string>> choices;
	};
}