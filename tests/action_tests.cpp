#include "pch.h"
#include "CppUnitTest.h"

#include "../source/Action.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ActionTests
{
TEST_CLASS(ActionTests) {
    public:
	static void emptyFunction(void *){}
	static void someOtherFunction(void *){}

	TEST_METHOD(DefaultConstructor)
	{
		int key = '\0';
		std::string name("");
		std::function<void(void *)> function(nullptr);
		Action action;

		Assert::AreEqual(key, action.GetKey());
		Assert::AreEqual(name, action.GetName());
		Assert::IsNull(function.target<void (*)(void *)>());
	}

	TEST_METHOD(ThreeeArgumenmtConstructor)
	{
		int key = 'A';
		std::string name("Action");
		std::function<void(void *)> function(
			ActionTests::emptyFunction);
		    
		Action action(key, name, function);
		    
		Assert::AreEqual(key, action.GetKey());
		Assert::AreEqual(name, action.GetName());
		Assert::IsNotNull(function.target<void (*)(void *)>());
		Assert::IsTrue(ActionTests::emptyFunction ==
			       *function.target<void (*)(void *)>());
	}
};
}
