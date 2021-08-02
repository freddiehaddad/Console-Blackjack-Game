#pragma once

//
// StateMachine - a graph structure mapping game actions available from a given
//                state.
//
// Setup
//
//	1. Create a StateMachine
//      2. Add states
//      2. Add actions
//	2. Create transitions
//
// Usage
//
//	1. Get the action via GetAction(key)
//      2. Perform the action
//	3. Update the state via UpdateState
//
// Example
//
//

// ------------------------------------------------------------ Project Headers
#include "Action.h"
#include "State.h"

// ------------------------------------------------------------ Library Headers
#include <functional>
#include <map>

// ----------------------------------------------------------- Class Definition
class StateMachine {
    public:
	StateMachine();

	bool AddState(std::string_view name);
	std::string GetState() const;
	void SetState(std::string_view name);
	void UpdateState();
	void UpdateState(int key);

	bool AddAction(int key, std::string_view name,
		       std::function<void(void *)> action);
	bool AddAction(std::string_view name,
		       std::function<void(void *)> action);
	std::function<void(void *)> GetAction() const;
	std::function<void(void *)> GetAction(int key) const;
	std::size_t Actions() const;
	std::string GetActions() const;
	bool IsValidAction(int key) const;

	void CreateTransition(std::string_view from, std::string_view to,
			      int action);
	void CreateTransition(std::string_view from, std::string_view to,
			      std::string_view action);

    private:
	Action GetAction_() const;
	Action GetAction_(int key) const;
	void CreateTransition_(std::string_view from, std::string_view to,
			       const Action &action);

	std::map<std::string, State> states_;
	std::map<int, Action> standardActions_;
	std::map<std::string, Action> automatedActions_;

	State currentState_;
	std::map<State, std::map<Action, State> > stateMachine_;
};
