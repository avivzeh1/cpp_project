/*
 * Thug.cpp
 *
 *  Created on: Jun 18, 2020
 *      Author: cs313311797
 */

#include "Thug.h"
#include "Peasant.h"

Thug::Thug(const char* name, Point& p): Agent(name, p) , power(20), nextPower(20){
	// TODO Auto-generated constructor stub

}

Thug::~Thug() {
	// TODO Auto-generated destructor stub
}

int Thug::getNextPower() const {
	return nextPower;
}

void Thug::setNextPower(int nextPower) {

	if(nextPower <= 20)
	this->nextPower = nextPower;
}

int Thug::getPower() const {
	return power;
}

void Thug::setPower(int power) {
	this->power = power;
}

void Thug::attack(shared_ptr<Agent>& p) {

	nextPower++;

	MovingObj::setNextSpeed(0);

	if(static_cast<Peasant*>(p.get())->getNextHealth() == 0 )
		p->setNextState("Dead");

	static_cast<Peasant*>(p.get())->setNextSupply(0);
	static_cast<Peasant*>(p.get())->setNextState("Stopped");


}

void Thug::update() {

	power = nextPower;
	Agent::update();
}
