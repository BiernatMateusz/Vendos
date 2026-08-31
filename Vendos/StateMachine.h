#ifndef STATE_MACHINE
#define STATE_MACHINE

#include <memory>

class State;

class StateMachine
{
public:
	virtual ~StateMachine() = default;

	virtual void pushState(std::unique_ptr<State>state) = 0;
	virtual void popState() = 0;

	virtual State* top() = 0;
	virtual bool empty() const = 0;
};

#endif