#include "StateManager.h"
#include "State.h"
#include "Main_meniu_state.h"
StateManager::StateManager()
{
	this->states = new std::stack<State*>;
}

void StateManager::add_state(State *state)
{
	this->states->push(state);
}

void StateManager::revome_state()
{
	if (this->states->size() > 0) {
		delete this->states->top();
		this->states->pop();
	}
}

void StateManager::switch_state(State *state)
{
	this->state_to_change = state;
}

void StateManager::save_current_state(STATE_NAME name)
{
	std::ofstream stream;
	stream.open("Settings/LastState.txt", std::ofstream::out | std::ofstream::trunc);
	stream << name;
	stream.close();
}

  State* StateManager::get_state()
{
	//remove state
	if (this->states->empty()) {
		return nullptr;
	}
	if (this->states->top()->quit) {
		this->revome_state();
	}
	// switch state
	if (this->state_to_change) {
		delete this->states->top();
		this->states->pop();
		this->states->push(this->state_to_change);
		this->state_to_change = nullptr;
	}
	if (!this->states->empty()) {
		return this->states->top();
	}
	return nullptr;
}

StateManager::~StateManager()
{
	while (!this->states->empty()) {
		delete this->states->top();
		this->states->pop();
	}
}
