#include "pch.h"
#include "CppUnitTest.h"

#include "../source/State.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StateTests
{
TEST_CLASS(StateTests) {
    public:
	TEST_METHOD(DefaultConstructor)
	{
		State state;
		Assert::IsTrue(state.GetName().empty());
	}

	TEST_METHOD(SingleArgumentConstructor)
	{
		const std::string name = "TEST";
		State state(name);
		Assert::AreEqual(name, state.GetName());
	}

	TEST_METHOD(StateComparisonEquality)
	{
		const std::string state1Name = "A";
		const std::string state2Name = "A";
		
		State state1(state1Name);
		State state2(state2Name);
		
		Assert::IsFalse(state1 < state2);
		Assert::IsFalse(state2 < state1);
	}

	TEST_METHOD(StateComparison)
	{
		const std::string state1Name = "A";
		const std::string state2Name = "B";
		
		State state1(state1Name);
		State state2(state2Name);
		
		Assert::IsTrue(state1 < state2);
		Assert::IsFalse(state2 < state1);
	}
};
}
