#include "pch.h"
#include "CppUnitTest.h"

#include "../source/StateMachine.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StateMachineTests
{
TEST_CLASS(StateMachineTests) {
    public:
	    
	static void TestFunction(void *){}

	TEST_METHOD(DefaultConstructor)
	{
		StateMachine machine;
		bool result = machine.IsValidAction('A');
		Assert::IsFalse(result);
		Assert::AreEqual(std::string(""), machine.GetState());
	}

	TEST_METHOD(SetStateValid)
	{
		const std::string state = "INITIAL STATE";
		StateMachine machine;
		bool result = machine.AddState(state);
		Assert::IsTrue(result);
		machine.SetState(state);
		Assert::AreEqual(state, machine.GetState());
	}

	TEST_METHOD(SetStateExeption)
	{
		const std::string state = "INITIAL STATE";
		StateMachine machine;
		auto function = [&]() { machine.SetState(state); };
		Assert::ExpectException<std::invalid_argument>(function);
	}

	TEST_METHOD(KeyActionTransitionException)
	{
		// Exception is a result of not calling SetState.
		const std::string from = "FROM";
		const std::string to = "TO";
		const std::string action = "Action A";
		const char key = 'A';
		bool result;
		StateMachine machine;
		result = machine.AddState(from);
		Assert::IsTrue(result);
		result = machine.AddState(to);
		Assert::IsTrue(result);
		result = machine.AddAction(key, action, nullptr);
		Assert::IsTrue(result);
		machine.CreateTransition(from, to, key);
		result = machine.IsValidAction(key);
		Assert::IsFalse(result);
		auto function = [&]() { machine.GetAction(key); };
		Assert::ExpectException<std::logic_error>(function);
	}

	TEST_METHOD(StringActionTransitionException)
	{
		// Exception is a result of not calling SetState.
		const std::string from = "FROM";
		const std::string to = "TO";
		const std::string action = "Action A";
		bool result;
		StateMachine machine;
		result = machine.AddState(from);
		Assert::IsTrue(result);
		result = machine.AddState(to);
		Assert::IsTrue(result);
		result = machine.AddAction(action, nullptr);
		Assert::IsTrue(result);
		machine.CreateTransition(from, to, action);
		auto function = [&] { machine.GetAction(); };
		Assert::ExpectException<std::logic_error>(function);
	}

	TEST_METHOD(ValidActionWithInitialState)
	{
		const std::string state = "STATE";
		const std::string action = "ACTION";
		const char key = 'A';
		StateMachine machine;
		Assert::IsTrue(machine.AddState(state));
		machine.SetState(state);
		Assert::IsTrue(machine.AddAction(
			key, state, &StateMachineTests::TestFunction));
		machine.CreateTransition(state, state, key);
		Assert::IsTrue(machine.IsValidAction(key));
	}

	TEST_METHOD(StateMachineInvalidActionException)
	{
		const std::string state = "STATE";
		const std::string action = "ACTION";
		const char key = 'A';
		StateMachine machine;
		Assert::IsTrue(machine.AddState(state));
		machine.SetState(state);
		Assert::IsTrue(machine.AddAction(
			key, state, &StateMachineTests::TestFunction));
		machine.CreateTransition(state, state, key);
		Assert::IsFalse(machine.IsValidAction('Z'));
		auto function = [&machine] { machine.UpdateState('Z'); };
		Assert::ExpectException<std::invalid_argument>(function);
	}

	TEST_METHOD(StateMachineWithCircularKeyAction)
	{
		const std::string FROM = "FROM";
		const std::string TO = "TO";
		const std::string ACTION = "Action A";
		const int key = 'A';
		bool result;

		StateMachine machine;

		result = machine.AddState(FROM);
		Assert::IsTrue(result);
		result = machine.AddState(TO);
		Assert::IsTrue(result);
		result = machine.AddAction(key, ACTION,
					   &StateMachineTests::TestFunction);
		Assert::IsTrue(result);
			
		machine.CreateTransition(FROM, TO, key);
		machine.CreateTransition(TO, FROM, key);

		machine.SetState(FROM);

		Assert::AreEqual(1u, machine.Actions());
		Assert::AreEqual(ACTION, machine.GetActions());
		Assert::AreEqual(FROM, machine.GetState());
			
		machine.UpdateState(key);
		
		Assert::AreEqual(1u, machine.Actions());
		Assert::AreEqual(ACTION, machine.GetActions());
		Assert::AreEqual(TO, machine.GetState());

		machine.UpdateState(key);

		Assert::AreEqual(1u, machine.Actions());
		Assert::AreEqual(ACTION, machine.GetActions());
		Assert::AreEqual(FROM, machine.GetState());
	}

	TEST_METHOD(StateMachineWithCircularStringAction)
	{
		const std::string FROM = "FROM";
		const std::string TO = "TO";
		const std::string ACTION = "ACTION";
		bool result;

		StateMachine machine;

		result = machine.AddState(FROM);
		Assert::IsTrue(result);
		result = machine.AddState(TO);
		Assert::IsTrue(result);
		result = machine.AddAction(ACTION,
					   &StateMachineTests::TestFunction);
		Assert::IsTrue(result);

		machine.CreateTransition(FROM, TO, ACTION);
		machine.CreateTransition(TO, FROM, ACTION);

		machine.SetState(FROM);

		Assert::AreEqual(0u, machine.Actions());
		Assert::AreEqual(FROM, machine.GetState());

		machine.UpdateState();

		Assert::AreEqual(0u, machine.Actions());
		Assert::AreEqual(TO, machine.GetState());

		machine.UpdateState();

		Assert::AreEqual(0u, machine.Actions());
		Assert::AreEqual(FROM, machine.GetState());
	}
};
}

