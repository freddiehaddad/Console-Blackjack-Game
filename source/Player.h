#pragma once

//
// Player - a descriptor for a game player.
//

// ------------------------------------------------------------ Project Headers
#include "Card.h"

// ------------------------------------------------------------ Library Headers
#include <string>
#include <vector>

// ----------------------------------------------------------- Class Definition
class Player {
    public:
	explicit Player(std::string_view name);

	std::string GetName() const;

	void Take(Card card);
	Card Return();

	std::vector<Card>::const_iterator Begin() const;
	std::vector<Card>::const_iterator End() const;
	const Card &Back() const;

	std::size_t Cards() const;

    private:
	std::string name_;
	std::vector<Card> cards_;
};
