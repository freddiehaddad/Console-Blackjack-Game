// ------------------------------------------------------------ Project Headers
#include "Player.h"

// ------------------------------------------------------------ Library Headers
#include <stdexcept>

// --------------------------------------------------------------- Constructors
Player::Player(std::string_view name) : name_(name)
{
}

// ------------------------------------------------------- Public Class Methods
std::string Player::GetName() const
{
	return name_;
}

void Player::Take(Card card)
{
	cards_.push_back(card);
}

Card Player::Return()
{
	if (Cards() == 0) {
		throw std::logic_error("Player doesn't have any cards!");
	}
	Card card = cards_.back();
	cards_.pop_back();
	return card;
}

std::vector<Card>::const_iterator Player::Begin() const
{
	return cards_.cbegin();
}

std::vector<Card>::const_iterator Player::End() const
{
	return cards_.cend();
}

const Card &Player::Back() const
{
	if (Cards() == 0) {
		throw std::logic_error("Player doesn't have any cards!");
	}
	return cards_.back();
}

std::size_t Player::Cards() const
{
	return cards_.size();
}

// ------------------------------------------------------ Private Class Methods
