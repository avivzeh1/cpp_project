/*
 * Structure.cpp
 *
 *  Created on: Jun 18, 2020
 *      Author: cs313311797
 */

#include "Structure.h"

Structure::Structure(char* name, Point& p, int amt) : SimObj(name) , amount(amt), nextAmount(amt),loc(p){


}

Structure::~Structure() {
	// TODO Auto-generated destructor stub
}

int Structure::getAmount() const {
	return amount;
}

void Structure::setAmount(int amount) {
	this->amount = amount;
}

const Point& Structure::getLocation() const {
	return loc;
}

int Structure::getNextAmount() const {
	return nextAmount;
}

void Structure::setNextAmount(int nextAmount) {
	this->nextAmount = nextAmount;
}

void Structure::setLocation(const Point& loc) {
	this->loc = loc;
}

void Structure::update() {

	amount = nextAmount;
}
