#ifndef STATE_STACK_H
#define STATE_STACK_H

#include "StateMachine.h"
#include <stack>
#include "State.h"

class StateStack : public StateMachine
{
public:
	void pushState(std::unique_ptr<State>state) override;
	void popState() override;

	State* top() override;
	bool empty()const override;

private:
	std::stack<std::unique_ptr<State>>states;
};

#endif