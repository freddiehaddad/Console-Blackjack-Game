#pragma once
//
// Input - wrapper around the C++ STD basic input stream reader.
//

// ------------------------------------------------------------ Project Headers

// ------------------------------------------------------------ Library Headers
#include <string>

// ----------------------------------------------------------- Class Definition
class Input {
    public:
	Input(std::basic_istream<char> &stream);

	char GetCharacter() const;
	std::string GetString() const;

    private:
	void FlushInputBuffer() const;

	std::basic_istream<char> &stream_;
};
