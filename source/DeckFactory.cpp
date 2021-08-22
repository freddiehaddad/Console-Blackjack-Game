#include "DeckFactory.h"

Deck DeckFactory::CreateEmptyDeck()
{
	Deck deck;
	return deck;
}

Deck DeckFactory::CreateStandardDeck()
{
	Deck deck;

	const int ranks = 13;
	const int suits = 4;

	for (int suit = 0; suit < suits; ++suit) {
		for (int rank = 0; rank < ranks; ++rank) {
			deck.Return(Card(rank, suit));
		}
	}

	return deck;
}
