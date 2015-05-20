#include "stdafx.h"
#include "Program.h"

using namespace TextAdventure;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TextAdventureTests
{
	// These tests are not needed for the TextAdventure game, they are for learning C++
	TEST_CLASS(ProgramTests)
	{
	public:
		TEST_METHOD(AddStringNumbers)
		{
			Assert::AreEqual(Program::AddStringNumbers(""), 0);
			Assert::AreEqual(Program::AddStringNumbers("2 + 1"), 3);
			Assert::AreEqual(Program::AddStringNumbers("3 + 4"), 7);
			Assert::AreEqual(Program::AddStringNumbers("335835 + 5834"), 335835 + 5834);
		}

		TEST_METHOD(FibonacciNumbers)
		{
			Assert::AreEqual(Program::Fibonacci(1), 1);
			Assert::AreEqual(Program::Fibonacci(3), 2);
			Assert::AreEqual(Program::Fibonacci(4), 3);
			Assert::AreEqual(Program::Fibonacci(5), 5);
			Assert::AreEqual(Program::Fibonacci(6), 8);
			Assert::AreEqual(Program::Fibonacci(7), 13);
		}

		TEST_METHOD(PrimitiveTypes)
		{
			// Creation and assignment
			int number = 27;
			Assert::AreEqual(number, 27);
			// Dividing int numbers always returns the rounded down value
			number /= 2;
			Assert::AreEqual(number, 13);
			// int with 32-bit cannot handle any number above 2147483647
			number = 2147483649;
			// Overflows to the negative
			Assert::AreEqual(number, -2147483647);
			// Use long long instead, which can handle around 20 digits
			long long bigNumber = 2147483648;
			Assert::AreEqual((double)bigNumber, 2147483648.0);
		}

		TEST_METHOD(CustomTypes)
		{
			// Definitions on a 64-bit platform
			typedef unsigned char uint8;
			typedef unsigned short uint16;
			typedef unsigned int uint32;
			typedef unsigned long long uint64;
			// Use sizeof to figure out what the size is
			Assert::AreEqual(sizeof(int), size_t(4));
			Assert::AreEqual(sizeof(uint64), size_t(8));
		}

		TEST_METHOD(UsingVariables)
		{
			// Creating any variable gives us direct access
			int number = 8;
			number++;
			Assert::AreEqual(number, 9);
			// Assigning the variable to something else creates a copy!
			int otherNumber = number;
			number++;
			Assert::AreEqual(otherNumber, 9);
			Assert::AreEqual(number, 10);
		}

		TEST_METHOD(Pointers)
		{
			int number = 10;
			int otherNumber = 9;
			// Point to the number from our previous example
			int *pointToNumber = &number;
			Assert::AreEqual(*pointToNumber, 10);
			// We can reassign the pointer to any other int value
			pointToNumber = &otherNumber;
			Assert::AreEqual(*pointToNumber, 9);
			(*pointToNumber)--;
			Assert::AreEqual(*pointToNumber, 8);
		}

		TEST_METHOD(CreatingDataViaPointers)
		{
			// Anytime you create something with new memory is
			// allocated and if available the constructor is invoked
			int *pointToNumber = new int;
			// Unlike C# or Java data is NOT zero initially, it will be
			// whatever was at that memory location before.
			Assert::AreNotEqual(*pointToNumber, 0);
			*pointToNumber = 17;
			Assert::AreEqual(*pointToNumber, 17);
			Program *program = new Program();
			// You are responsible for cleanup if you created something!
			delete pointToNumber;
			delete program;
			// The pointer still points to the data, but the value is not longer ours
			Assert::AreNotEqual(*pointToNumber, 17);//might still point to 17 in release mode!
			Assert::IsNotNull(program);
			// It is better to null out pointers after deletion so we do not use them anymore!
			pointToNumber = NULL;
			program = NULL;
			// Anything executed here on pointToNumber or program causes an Access Violation,
			// which cannot be catched in C++ (it is a hardware exception) unlike C# or Java.
		}

		TEST_METHOD(UsingSmartPointers)
		{
			std::shared_ptr<int> pointToNumber = std::make_shared<int>();
			*(pointToNumber.get()) = 4;
			Assert::AreEqual(*(pointToNumber.get()), 4);
		} // pointToNumber pointer is automatically destroyed here, there is no GC in C++

		TEST_METHOD(CreateABunchOfPrograms)
		{
			// This is basically how you would use a generic list like in C# (using templates in C++)
			std::vector<std::shared_ptr<Program>> programs;
			programs.push_back(std::make_shared<Program>("Program 1"));
			programs.push_back(std::make_shared<Program>("Program 2"));
			Assert::AreEqual(programs.size(), size_t(2));
			Assert::AreEqual(programs[0]->Name, std::string("Program 1"));
		} // The programs vector and all of the created Programs are automatically destroyed here

		TEST_METHOD(EnumerationsAndSwitchStatement)
		{
			enum Color { RED, GREEN, BLUE };
			Color color = RED; // Notice Color:: is not needed in C++
			std::string result;
			switch (color)
			{
				case RED:
					result = "red";
					break;
				case GREEN:
					result = "green";
					break;
				case BLUE:
					result = "blue";
					break;
			}
			Assert::AreEqual(result, std::string("red"));
		}

		TEST_METHOD(UnionDataType)
		{
			struct SharedData
			{
				enum { CHAR, INT } type;
				union
				{
					char letter;
					int number;
				};
			};
			SharedData data1 = { SharedData::CHAR, 'a' };
			Assert::AreEqual(data1.letter, 'a');
			Assert::AreEqual(data1.number, 97);
			SharedData data2 = { SharedData::INT, 121 };
			Assert::AreEqual(data2.letter, 'y');
			Assert::AreEqual(data2.number, 121);
		}
	};
}