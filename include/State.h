#ifndef STATE_H
#define STATE_H

template <class entity>
class State {

public:
	virtual ~State() {}
	virtual void start(entity*) = 0;
	virtual void stop(entity*) = 0;
};

#endif