/*
 * Agent.cpp
 *
 *  Created on: Jun 18, 2020
 *      Author: cs313311797
 */

#include "Agent.h"

Agent::Agent(const char* name_, Point& p) : MovingObj(p),
		SimObj(name_),state("Stopped"),nextState("Stopped"){

}

Agent::~Agent() {
	// TODO Auto-generated destructor stub
}


void Agent::update() {

	state = nextState;
	if(state == "Dead" || state == "Stopped")
		MovingObj::setNextSpeed(0);
	MovingObj::update();

}

const string& Agent::getState() const {
	return state;
}

void Agent::setState(const string& state) {
	this->state = state;
}

const string& Agent::getNextState() const {
	return nextState;
}

void Agent::setNextState(const string& nextState) {

	this->nextState = nextState;
}

void Agent::stop() {
	nextState = "Stopped";
	MovingObj::setNextSpeed(0);
}
