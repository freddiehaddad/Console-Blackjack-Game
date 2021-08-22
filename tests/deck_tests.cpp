#include "pch.h"
#include "CppUnitTest.h"

#include "../source/DeckFactory.h"

#include <algorithm>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DeckTests
{
TEST_CLASS(DeckTests){
    public:
	static void emptyFunction(void *){}
	static void someOtherFunction(void *){}

	TEST_METHOD(Constructor)
	{
		size_t remaining = 52;
		Deck deck = DeckFactory::CreateStandardDeck();
		Assert::AreEqual(remaining, deck.Remaining());
	}

	TEST_METHOD(TakeSingleCard)
	{
		size_t remaining = 52;
		Deck deck = DeckFactory::CreateStandardDeck();
		Assert::AreEqual(remaining, deck.Remaining());
		deck.Take();
		--remaining;
		Assert::AreEqual(remaining, deck.Remaining());
	}

	TEST_METHOD(TakeCardException)
	{
		const size_t cards = 52;
		size_t taken = 0;
		Deck deck = DeckFactory::CreateStandardDeck();
		Assert::AreEqual(cards, deck.Remaining());
		while (taken != 52) {
			deck.Take();
			++taken;
		}
		auto f = [&deck]() { deck.Take(); };
		Assert::ExpectException<std::logic_error>(f);
	}

	TEST_METHOD(CheckCards)
	{
		const int ranks = 13;
		const int suits = 4;
		size_t remainder = 0;
		size_t nCards = ranks * suits;
		Deck deck = DeckFactory::CreateStandardDeck();
		Assert::AreEqual(nCards, deck.Remaining());
		for (int suit = 3; suit >= 0; --suit) {
			for (int rank = 12; rank >= 0; --rank) {
				Card card = deck.Take();
				--nCards;
				Assert::AreEqual(rank, card.Rank());
				Assert::AreEqual(suit, card.Suit());
				Assert::AreEqual(nCards, deck.Remaining());
			}
		}
		Assert::AreEqual(remainder, deck.Remaining());
	}

	TEST_METHOD(CheckTakeAndReturn)
	{
		size_t remaining = 52;
		Deck deck = DeckFactory::CreateStandardDeck();
		Assert::AreEqual(remaining, deck.Remaining());
		Card card = deck.Take();
		--remaining;
		Assert::AreEqual(remaining, deck.Remaining());
		deck.Return(card);
		++remaining;
		Assert::AreEqual(remaining, deck.Remaining());
	}

	TEST_METHOD(Shuffle)
	{
		const size_t suits = 4;
		const size_t ranks = 13;
		const size_t cards = suits * ranks;

		Deck deck = DeckFactory::CreateStandardDeck();
		
		// Create a hash table to account for all the shuffled cards
		std::vector<std::vector<int> > hashTable;
		hashTable.resize(suits);
		std::for_each(hashTable.begin(), hashTable.end(),
			      [&ranks](std::vector<int> &vector) {
				      vector.resize(ranks);
			      });

		
		// Shuffle the deck and remove all the cards placing them in
		// the hash table.
		deck.Shuffle();
		Assert::AreEqual(cards, deck.Remaining());
		
		while (deck.Remaining() > 0) {
			Card card = deck.Take();
			hashTable[card.Suit()][card.Rank()] = card.Rank();
		}

		// Sort all the cards
		std::for_each(hashTable.begin(), hashTable.end(),
			      [](std::vector<int> &ranks) {
				      std::sort(ranks.begin(), ranks.end());
			      });

		// Check to make sure they are all present
		std::for_each(hashTable.begin(), hashTable.end(),
			      [&ranks](const std::vector<int> &cards) {
				      Assert::AreEqual(ranks, cards.size());
				      for (size_t i = 0; i < cards.size(); ++i) {
					      Assert::AreEqual(static_cast<int>(i), cards[i]);
				      }
			      });
	}

};
}
