#pragma once

//
// State - Simple state descriptor for managing program state.
//

// ------------------------------------------------------------ Project Headers

// ------------------------------------------------------------ Library Headers
#include <string>

// ----------------------------------------------------------- Class Definition
class State {
    public:
	State();
	explicit State(std::string_view name);

	std::string GetName() const;

	bool operator<(const State &state) const;

    private:
	std::string name_;
};
