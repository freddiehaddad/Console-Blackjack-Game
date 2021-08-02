#pragma once
//
// Deck - a descriptor for a collection of Cards.
//

// ------------------------------------------------------------ Project Headers
#include "Card.h"

// ------------------------------------------------------------ Library Headers
#include <vector>

// ----------------------------------------------------------- Class Definition
class Deck {
    public:
	Deck();

	Card Take();
	void Return(Card card);

	std::size_t Remaining() const;

	void Shuffle();

    private:
	std::vector<Card> cards_;

	static void Initialize(std::vector<Card> &cards);
};
