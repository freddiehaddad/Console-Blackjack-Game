#pragma once
//
// DeckFactory - used for creating various types of Decks.
//

// ------------------------------------------------------------ Project Headers
#include "Deck.h"

// ------------------------------------------------------------ Library Headers

// ----------------------------------------------------------- Class Definition
class DeckFactory {
    public:
	static Deck CreateEmptyDeck();
	static Deck CreateStandardDeck();
};
