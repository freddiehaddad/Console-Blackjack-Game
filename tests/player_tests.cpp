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
		const std::string name("Test Player");
		Player player(name);
		Assert::AreEqual(0u, player.Cards());
		Assert::AreEqual(name, player.GetName());
		Assert::IsTrue(player.Begin() == player.End());
		auto r = [&player]() { player.Return(); };
		Assert::ExpectException<std::logic_error>(r);
		auto b = [&player]() { player.Back(); };
		Assert::ExpectException<std::logic_error>(b);
	}

	TEST_METHOD(PlayerTakeCard)
	{
		const std::string name("Test Player");
		const Card card(0, 0);
		Player player(name);
		player.Take(card);
		Assert::AreEqual(1u, player.Cards());
		const Card &back = player.Back();
		Assert::AreEqual(card.Name(), back.Name());
	}

	TEST_METHOD(PlayerTakeCardIterate)
	{
		const std::string name("Test Player");
		const Card card(0, 0);
		Player player(name);
		player.Take(card);
		Assert::AreEqual(1u, player.Cards());
		auto i = player.Begin();
		Assert::IsTrue(i != player.End());
		Card fromIterator = *i;
		Assert::AreEqual(card.Name(), fromIterator.Name());
	}

	TEST_METHOD(PlayerTakeCardAndReturn)
	{
		const std::string name("Test Player");
		const Card card(0, 0);
		Player player(name);
		player.Take(card);
		Assert::AreEqual(1u, player.Cards());
		Card returned = player.Return();
		Assert::AreEqual(0u, player.Cards());
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
		Player player(name);
		player.Take(card1);
		Assert::AreEqual(1u, player.Cards());
		const Card &back1 = player.Back();
		Assert::AreEqual(card1.Name(), back1.Name());
		player.Take(card2);
		Assert::AreEqual(2u, player.Cards());
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
		Player player(name);
		player.Take(card1);
		Assert::AreEqual(1u, player.Cards());
		const Card &back1 = player.Back();
		Assert::AreEqual(card1.Name(), back1.Name());
		player.Take(card2);
		Assert::AreEqual(2u, player.Cards());
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
		Assert::AreEqual(card2.Name(), rCard2.Name());
		Assert::IsTrue(player.Begin() != player.End());
		Assert::AreEqual(1u, player.Cards());
		Card rCard1 = player.Return();
		Assert::AreEqual(card1.Name(), rCard1.Name());
		Assert::AreEqual(0u, player.Cards());
		Assert::IsTrue(player.Begin() == player.End());
	}
};
}
