// ------------------------------------------------------------ Project Headers
#include "StateMachine.h"

// ------------------------------------------------------------ Library Headers
#include <algorithm>
#include <sstream>
#include <stdexcept>

// --------------------------------------------------------------- Constructors
StateMachine::StateMachine()
{
}

// ------------------------------------------------------- Public Class Methods
bool StateMachine::AddState(std::string_view name)
{
	auto result = states_.emplace(name, name);
	return result.second;
}

std::string StateMachine::GetState() const
{
	return currentState_.GetName();
}

void StateMachine::SetState(std::string_view name)
{
	auto i = states_.find(std::string(name));
	if (i == states_.end()) {
		throw std::invalid_argument("State not found!");
	}

	currentState_ = i->second;
}

void StateMachine::UpdateState()
{
	const Action &action = GetAction_();
	State &nextState = stateMachine_[currentState_][action];
	currentState_ = nextState;
}

void StateMachine::UpdateState(int key)
{
	if (!IsValidAction(key)) {
		throw std::invalid_argument("Action not found!");
	}

	const Action &action = GetAction_(key);
	State &nextState = stateMachine_[currentState_][action];
	currentState_ = nextState;
}

bool StateMachine::AddAction(int key, std::string_view name,
			     std::function<void(void *)> action)
{
	auto result = standardActions_.emplace(
		std::make_pair(key, Action(key, name, action)));
	return result.second;
}

bool StateMachine::AddAction(std::string_view name,
			     std::function<void(void *)> action)
{
	auto result = automatedActions_.emplace(
		std::make_pair(name, Action(0, name, action)));
	return result.second;
}

std::function<void(void *)> StateMachine::GetAction() const
{
	const Action &action = GetAction_();
	return action.GetHandler();
}

std::function<void(void *)> StateMachine::GetAction(int key) const
{
	const Action &action = GetAction_(key);
	return action.GetHandler();
}

std::size_t StateMachine::Actions() const
{
	auto s = stateMachine_.find(currentState_);
	std::size_t count = std::count_if(
		s->second.begin(), s->second.end(),
		[](const auto &pair) { return pair.first.GetKey() != 0; });
	return count;
}

std::string StateMachine::GetActions() const
{
	std::ostringstream stream;
	std::string string;

	const std::string separator = ", ";
	auto s = stateMachine_.find(currentState_);
	std::for_each(s->second.begin(), s->second.end(),
		      [&stream, &separator](const auto &pair) {
			      if (pair.first.GetKey() != 0) {
				      stream << pair.first.GetName()
					     << separator;
			      }
		      });

	string = stream.str();
	if (string.length() > separator.length()) {
		string.erase(string.length() - separator.length());
	}
	return string;
}

bool StateMachine::IsValidAction(int key) const
{
	// Look up the action: key -> action
	auto a = standardActions_.find(key);
	if (a == standardActions_.end()) {
		return false;
	}

	// Look up the available actions: currentState -> actions
	auto s = stateMachine_.find(currentState_);
	if (s == stateMachine_.end()) {
		return false;
	}

	// Check state action mapping
	const auto &action = a->second;
	const auto &stateActions = s->second;

	auto sa = stateActions.find(action);
	if (sa == stateActions.end()) {
		return false;
	}

	return true;
}

void StateMachine::CreateTransition(std::string_view from, std::string_view to,
				    int action)
{
	auto a = standardActions_.find(action);

	if (a == standardActions_.end()) {
		throw std::logic_error("Action not found!");
	}

	CreateTransition_(from, to, a->second);
}

void StateMachine::CreateTransition(std::string_view from, std::string_view to,
				    std::string_view action)
{
	auto a = automatedActions_.find(std::string(action));

	if (a == automatedActions_.end()) {
		throw std::logic_error("Action not found!");
	}

	CreateTransition_(from, to, a->second);
}

void StateMachine::CreateTransition_(std::string_view from, std::string_view to,
				     const Action &action)
{
	auto f = states_.find(std::string(from));
	auto t = states_.find(std::string(to));

	if (f == states_.end() || t == states_.end()) {
		throw std::logic_error("State not found!");
	}

	stateMachine_[f->second][action] = t->second;
}

// ------------------------------------------------------ Private Class Methods
Action StateMachine::GetAction_() const
{
	auto s = stateMachine_.find(currentState_);
	if (s == stateMachine_.end()) {
		throw std::logic_error("State not found!");
	}
	const Action &action = s->second.begin()->first;
	return action;
}

Action StateMachine::GetAction_(int key) const
{
	if (!IsValidAction(key)) {
		throw std::logic_error("Key not found!");
	}

	auto a = standardActions_.find(key);
	const Action &action = a->second;
	return action;
}
