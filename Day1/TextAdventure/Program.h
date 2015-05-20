#pragma once
#include <string>

namespace TextAdventure
{
	class Program
	{
	public:
		Program(std::string name = "Program")
			: Name(name) {}
		std::string Name;
		static int AddStringNumbers(const char* inputText);
		static int Fibonacci(int iterations)
		{
			if (iterations <= 2)
				return 1;
			else
				return Fibonacci(iterations - 2) + Fibonacci(iterations - 1);
		}
	};
}