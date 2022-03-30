/*
 * Thug.h
 *
 *  Created on: Jun 18, 2020
 *      Author: cs313311797
 */

#ifndef THUG_H_
#define THUG_H_

#include "Agent.h"

class Thug : public Agent{
public:
	Thug(const char* name, Point& p);
	virtual ~Thug();
	int getNextPower() const;
	void setNextPower(int nextPower);
	int getPower() const;
	void setPower(int power);
	void attack(shared_ptr<Agent>& p);
	void update();
private:
	int power;
	int nextPower;
};

#endif /* THUG_H_ */
