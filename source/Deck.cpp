// ------------------------------------------------------------ Project Headers
#include "Deck.h"

// ------------------------------------------------------------ Library Headers
#include <algorithm>
#include <random>
#include <stdexcept>

// --------------------------------------------------------------- Constructors
Deck::Deck()
{
}

// ------------------------------------------------------- Public Class Methods
Card Deck::Take()
{
	if (Remaining() == 0) {
		throw std::logic_error("No more cards!");
	}
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
