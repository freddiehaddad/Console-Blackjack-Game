#include "pch.h"
#include "CppUnitTest.h"

#include <sstream>
#include <string>

#include "../source/Input.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace InputTests
{
TEST_CLASS(InputTests) {
    public:
	TEST_METHOD(GetCharacterEmptyString)
	{
		char actual, expected;
		std::istringstream istream;
		Input input(istream);
		
		actual = input.GetCharacter();
		expected = '\0';
		Assert::AreEqual(expected, actual);
	}
	
	TEST_METHOD(GetCharacterSingleCharacter)
	{
		char actual, expected;
		std::istringstream istream("a");
		Input input(istream);
		
		actual = input.GetCharacter();
		expected = 'a';
		Assert::AreEqual(expected, actual);
	}
	
	TEST_METHOD(GetCharacterFlushExtra)
	{
		char actual, expected;
		std::istringstream istream("aa");
		Input input(istream);
		
		actual = input.GetCharacter();
		expected = 'a';
		Assert::AreEqual(expected, actual);
		
		actual = input.GetCharacter();
		expected = '\0';
		Assert::AreEqual(expected, actual);
	}
	
	TEST_METHOD(GetStringEmptyString)
	{
		std::string actual, expected;
		std::istringstream istream("");
		Input input(istream);

		actual = input.GetString();
		expected = "";
		Assert::AreEqual(expected, actual);
	}

	TEST_METHOD(GetStringSingleCharacterString)
	{
		std::string actual, expected;
		std::istringstream istream("a");
		Input input(istream);

		actual = input.GetString();
		expected = "a";
		Assert::AreEqual(expected, actual);
	}

	TEST_METHOD(GetStringMultiCharacterString)
	{
		std::string actual, expected;
		std::istringstream istream("aa");
		Input input(istream);

		actual = input.GetString();
		expected = "aa";
		Assert::AreEqual(expected, actual);
	}

	TEST_METHOD(GetStringAfterRead)
	{
		std::string actual, expected;
		std::istringstream istream("aa");
		Input input(istream);

		actual = input.GetString();
		expected = "aa";
		Assert::AreEqual(expected, actual);

		actual = input.GetString();
		expected = "";
		Assert::AreEqual(expected, actual);
	}
};
}

