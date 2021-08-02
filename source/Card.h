#pragma once
//
// Card - a descriptor for a generic playing card.
//

// ------------------------------------------------------------ Project Headers

// ------------------------------------------------------------ Library Headers
#include <string>

// ----------------------------------------------------------- Class Definition
class Card {
    public:
	Card(int rank, int suit);

	int Rank() const;
	int Suit() const;

	std::string_view Name() const;

    private:
	int rank_;
	int suit_;

	std::string name_;

	static std::string GetRank(int rank);
	static std::string GetSuit(int suit);
};
