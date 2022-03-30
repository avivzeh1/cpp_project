/*
 * Agent.h
 *
 *  Created on: Jun 18, 2020
 *      Author: cs313311797
 */

#ifndef AGENT_H_
#define AGENT_H_

#include <string>
#include "MovingObj.h"
#include "SimObj.h"

using namespace std;
class Agent : public MovingObj, public SimObj {
public:
	Agent(const char* name_, Point& point);
	virtual ~Agent();
	void update();  // update the next position and state of the agent
	// getters and setters
	const string& getState() const;
	void setState(const string& state);
	const string& getNextState() const;
	void setNextState(const string& nextState);
	void stop(); // set the next speed of this agent to 0 and the state to "Stooped"

private:
	string state;
	string nextState;

};

#endif /* AGENT_H_ */
