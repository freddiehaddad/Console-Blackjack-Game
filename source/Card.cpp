// ------------------------------------------------------------ Project Headers
#include "Card.h"

// ------------------------------------------------------------ Library Headers
#include <sstream>
#include <stdexcept>

// --------------------------------------------------------------- Constructors
Card::Card(int rank, int suit) : rank_(rank), suit_(suit)
{
	std::ostringstream stream;
	stream << Card::GetRank(rank);
	stream << " of ";
	stream << Card::GetSuit(suit);

	name_ = stream.str();
}

// ------------------------------------------------------- Public Class Methods
int Card::Rank() const
{
	return rank_;
}

int Card::Suit() const
{
	return suit_;
}

std::string_view Card::Name() const
{
	return name_;
}

// ------------------------------------------------------ Private Class Methods

// ---------------------------------------------- Private Static Helper Methods
std::string Card::GetRank(int rank)
{
	std::string string;

	switch (rank) {
	case 0:
		string = "Ace";
		break;
	case 1:
		string = "Two";
		break;
	case 2:
		string = "Three";
		break;
	case 3:
		string = "Four";
		break;
	case 4:
		string = "Five";
		break;
	case 5:
		string = "Six";
		break;
	case 6:
		string = "Seven";
		break;
	case 7:
		string = "Eight";
		break;
	case 8:
		string = "Nine";
		break;
	case 9:
		string = "Ten";
		break;
	case 10:
		string = "Jack";
		break;
	case 11:
		string = "Queen";
		break;
	case 12:
		string = "King";
		break;
	default:
		throw std::invalid_argument("Invalid rank value: " + rank);
		break;
	}

	return string;
}

std::string Card::GetSuit(int suit)
{
	std::string string;

	switch (suit) {
	case 0:
		string = "Clubs";
		break;
	case 1:
		string = "Diamonds";
		break;
	case 2:
		string = "Hearts";
		break;
	case 3:
		string = "Spades";
		break;
	default:
		throw std::invalid_argument("Invalid suit value: " + suit);
		break;
	}

	return string;
}
