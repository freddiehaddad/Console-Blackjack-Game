// ------------------------------------------------------------ Project Headers
#include "State.h"

// ------------------------------------------------------------ Library Headers

// --------------------------------------------------------------- Constructors
State::State() : State("")
{
}

State::State(std::string_view name) : name_(name)
{
}

// ------------------------------------------------------- Public Class Methods
std::string State::GetName() const
{
	return name_;
}

bool State::operator<(const State &state) const
{
	return GetName() < state.GetName();
}

// ------------------------------------------------------ Private Class Methods
