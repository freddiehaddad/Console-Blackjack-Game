// ------------------------------------------------------------ Project Headers
#include "Input.h"

// ------------------------------------------------------------ Library Headers
#include <iostream>
#include <sstream>
#include <string>

// --------------------------------------------------------------- Constructors
Input::Input(std::basic_istream<char> &stream) : stream_(stream)
{
}

// ------------------------------------------------------- Public Class Methods
char Input::GetCharacter() const
{
	std::string input;
	input = GetString();
	return input[0];
}

std::string Input::GetString() const
{
	std::string input;
	std::getline(stream_, input, '\n');
	return input;
}

// ------------------------------------------------------ Private Class Methods
void Input::FlushInputBuffer() const
{
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
