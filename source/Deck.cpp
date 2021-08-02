// ------------------------------------------------------------ Project Headers
#include "Deck.h"

// ------------------------------------------------------------ Library Headers
#include <algorithm>
#include <random>

// --------------------------------------------------------------- Constructors
Deck::Deck()
{
	Initialize(cards_);
}

// ------------------------------------------------------- Public Class Methods
Card Deck::Take()
{
	Card card = cards_.back();
	cards_.pop_back();
	return card;
}

void Deck::Return(Card card)
{
	cards_.push_back(card);
}

std::size_t Deck::Remaining() const
{
	return cards_.size();
}

void Deck::Shuffle()
{
	std::random_device rd;
	std::mt19937 engine(rd());
	std::shuffle(cards_.begin(), cards_.end(), engine);
}

// ------------------------------------------------------ Private Class Methods
void Deck::Initialize(std::vector<Card> &cards)
{
	const int ranks = 13;
	const int suits = 4;

	for (int suit = 0; suit < suits; ++suit) {
		for (int rank = 0; rank < ranks; ++rank) {
			cards.emplace_back(rank, suit);
		}
	}
}
