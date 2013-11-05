#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "State.h"

template<class entity>
class StateMachine {

private:
	entity* owner;
	State<entity>* current_state;
	State<entity>* previous_state;

public:
	StateMachine(entity* owner) : owner(owner), 
								  current_state(NULL), 
								  previous_state(NULL) {} 
	virtual ~StateMachine() {}

	void set_current_state(State<entity>* ent) {current_state = ent;}
	void set_previous_state(State<entity>* ent)  {previous_state = ent;}

	State<entity>* get_current_state() const {return current_state;}
	State<entity>* get_previous_state() const {return previous_state;}

	void update() {current_state->start(owner);}

	void change_state(State<entity>* new_state) {
		this->previous_state = current_state;
		this->current_state->stop(owner);
		this->current_state = new_state;
		this->current_state->start(owner);
	}

	void revert_state() {
		change_state(previous_state);
	}

};

#endif