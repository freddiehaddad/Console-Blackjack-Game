#pragma once
//
// Action - a descriptor for game actions resulting from user input.
//

// ------------------------------------------------------------ Project Headers

// ------------------------------------------------------------ Library Headers
#include <functional>
#include <string>

// ----------------------------------------------------------- Class Definition
class Action {
    public:
	Action();
	Action(int key, std::string_view name,
	       const std::function<void(void *)> handler);

	int GetKey() const;
	std::string GetName() const;
	std::function<void(void *)> GetHandler() const;

	bool operator<(const Action &action) const;

    private:
	int key_;
	std::string name_;
	std::function<void(void *)> handler_;
};
