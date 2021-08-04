#include "pch.h"
#include "CppUnitTest.h"

#include <sstream>
#include <string>

#include "../source/Player.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PlayerTests
{
TEST_CLASS(PlayerTests){
    public:
	TEST_METHOD(Constructor)
	{
		const size_t cards = 0;
		const std::string name("Test Player");
		Player player(name);
		Assert::AreEqual(cards, player.Cards());
		Assert::AreEqual(name, player.GetName());
		Assert::IsTrue(player.Begin() == player.End());
		auto r = [&player]() { player.Return(); };
		Assert::ExpectException<std::logic_error>(r);
		auto b = [&player]() { player.Back(); };
		Assert::ExpectException<std::logic_error>(b);
	}

	TEST_METHOD(PlayerTakeCard)
	{
		const size_t cards = 1;
		const std::string name("Test Player");
		const Card card(0, 0);
		Player player(name);
		player.Take(card);
		Assert::AreEqual(cards, player.Cards());
		const Card &back = player.Back();
		Assert::AreEqual(card.Name(), back.Name());
	}

	TEST_METHOD(PlayerTakeCardIterate)
	{
		const size_t cards = 1;
		const std::string name("Test Player");
		const Card card(0, 0);
		Player player(name);
		player.Take(card);
		Assert::AreEqual(cards, player.Cards());
		auto i = player.Begin();
		Assert::IsTrue(i != player.End());
		Card fromIterator = *i;
		Assert::AreEqual(card.Name(), fromIterator.Name());
	}

	TEST_METHOD(PlayerTakeCardAndReturn)
	{
		size_t cards = 0;
		const std::string name("Test Player");
		const Card card(0, 0);
		Player player(name);
		player.Take(card);
		++cards;
		Assert::AreEqual(cards, player.Cards());
		Card returned = player.Return();
		--cards;
		Assert::AreEqual(cards, player.Cards());
		Assert::IsTrue(player.Begin() == player.End());
		Assert::AreEqual(card.Name(), returned.Name());
		auto r = [&player]() { player.Return(); };
		Assert::ExpectException<std::logic_error>(r);
		auto b = [&player]() { player.Back(); };
		Assert::ExpectException<std::logic_error>(b);
	}

	TEST_METHOD(PlayerTakeTwoCards)
	{
		const std::string name("Test Player");
		const Card card1(0, 0);
		const Card card2(1, 0);
		size_t cards = 0;
		Player player(name);
		player.Take(card1);
		++cards;
		Assert::AreEqual(cards, player.Cards());
		const Card &back1 = player.Back();
		Assert::AreEqual(card1.Name(), back1.Name());
		player.Take(card2);
		++cards;
		Assert::AreEqual(cards, player.Cards());
		const Card &back2 = player.Back();
		Assert::AreEqual(card2.Name(), back2.Name());
		Assert::IsTrue(player.Begin() != player.End());
		auto i = player.Begin();
		Card iCard1 = *i++;
		Assert::AreEqual(card1.Name(), iCard1.Name());
		Card iCard2 = *i++;
		Assert::AreEqual(card2.Name(), iCard2.Name());
		Assert::IsTrue(i == player.End());
	}

	TEST_METHOD(PlayerTakeAndReturnTwoCards)
	{
		const std::string name("Test Player");
		const Card card1(0, 0);
		const Card card2(1, 0);
		size_t cards = 0;
		Player player(name);
		player.Take(card1);
		++cards;
		Assert::AreEqual(cards, player.Cards());
		const Card &back1 = player.Back();
		Assert::AreEqual(card1.Name(), back1.Name());
		player.Take(card2);
		++cards;
		Assert::AreEqual(cards, player.Cards());
		const Card &back2 = player.Back();
		Assert::AreEqual(card2.Name(), back2.Name());
		Assert::IsTrue(player.Begin() != player.End());
		auto i = player.Begin();
		Card iCard1 = *i++;
		Assert::AreEqual(card1.Name(), iCard1.Name());
		Card iCard2 = *i++;
		Assert::AreEqual(card2.Name(), iCard2.Name());
		Assert::IsTrue(i == player.End());
		Card rCard2 = player.Return();
		--cards;
		Assert::AreEqual(card2.Name(), rCard2.Name());
		Assert::IsTrue(player.Begin() != player.End());
		Assert::AreEqual(cards, player.Cards());
		Card rCard1 = player.Return();
		--cards;
		Assert::AreEqual(card1.Name(), rCard1.Name());
		Assert::AreEqual(cards, player.Cards());
		Assert::IsTrue(player.Begin() == player.End());
	}
};
}
