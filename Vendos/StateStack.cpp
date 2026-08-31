#include "StateStack.h"

void StateStack::pushState(std::unique_ptr<State>state)
{
	states.push(std::move(state));
}

void StateStack::popState()
{
	if (!states.empty())
		states.pop();
}

State* StateStack::top()
{
	return states.empty() ? nullptr : states.top().get();
}

bool StateStack::empty() const
{
	return states.empty();
}