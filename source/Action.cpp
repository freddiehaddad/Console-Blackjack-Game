// ------------------------------------------------------------ Project Headers
#include "Action.h"

// ------------------------------------------------------------ Library Headers

// --------------------------------------------------------------- Constructors
Action::Action() : Action('\0', "", nullptr)
{
}

Action::Action(int key, std::string_view name,
	       const std::function<void(void *)> handler)
	: key_(key), name_(name), handler_(handler)
{
}

// ------------------------------------------------------- Public Class Methods
int Action::GetKey() const
{
	return key_;
}

std::string Action::GetName() const
{
	return name_;
}

std::function<void(void *)> Action::GetHandler() const
{
	return handler_;
}

bool Action::operator<(const Action &action) const
{
	return GetName() < action.GetName();
}

// ------------------------------------------------------ Private Class Methods
