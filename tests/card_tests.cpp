#include "pch.h"
#include "CppUnitTest.h"

#include <sstream>
#include <string>

#include "../source/Card.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CardTests
{
TEST_CLASS(CardTests) {
    public:
	TEST_METHOD(Constructor)
	{
		const std::string name("Ace of Clubs");
		Card card(0, 0);
		Assert::AreEqual(0, card.Rank());
		Assert::AreEqual(0, card.Suit());
		Assert::AreEqual(std::string_view(name), card.Name());
	}

	TEST_METHOD(ConstructorRankException)
	{
		auto f = []() { Card card(-1, 0); };
		Assert::ExpectException<std::invalid_argument>(f);
	}

	TEST_METHOD(ConstructorSuitException)
	{
		auto f = []() { Card card(0, -1); };
		Assert::ExpectException<std::invalid_argument>(f);
	}

	TEST_METHOD(RankValid)
	{
		Card card(1, 0);
		Assert::AreEqual(1, card.Rank());
	}

	TEST_METHOD(SuitValid)
	{
		Card card(0, 1);
		Assert::AreEqual(1, card.Suit());
	}

	TEST_METHOD(NameValid)
	{
		const std::string name("Two of Diamonds");
		Card card(1, 1);
		Assert::AreEqual(1, card.Rank());
		Assert::AreEqual(1, card.Suit());
		Assert::AreEqual(std::string_view(name), card.Name());
	}
};
}
