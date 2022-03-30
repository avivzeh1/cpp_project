/*
 * Peasant.cpp
 *
 *  Created on: Jun 18, 2020
 *      Author: cs313311797
 */

#include "Peasant.h"
#include<cstring>
#include "Model.h"

Peasant::Peasant(const char* name, Point& p) :
		Agent(name, p), health(10), nextHealth(10), supply(0), nextSupply(0), load(
				false), unload(false), finish(false) {

}

Peasant::~Peasant() {

}

int Peasant::getHealth() const {
	return health;
}

void Peasant::setHealth(int health) {
	this->health = health;
}

int Peasant::getNextHealth() const {
	return nextHealth;
}

void Peasant::setNextHealth(int nextHealth) {
	this->nextHealth = nextHealth;
}

void Peasant::start_working(string src_, string dest_, const Point& psrc,
		const Point& pd) {
	if (load && !finish)
		throw "error: The peasant is busy";
	load = false;
	unload = false;
	finish = false;
	pdest = pd;
	dest = dest_;
	Agent::setNextState("Heading to");
	MovingObj::setNextDest(src_);
	MovingObj::setNextTar(psrc);
	MovingObj::setNextSpeed(5);

}

int Peasant::getNextSupply() const {
	return nextSupply;
}

void Peasant::setNextSupply(int nextSupply) {
	this->nextSupply = nextSupply;
}

int Peasant::getSupply() const {
	return supply;
}

void Peasant::setSupply(int supply) {
	this->supply = supply;
}

void Peasant::update() {

	supply = nextSupply;
	health = nextHealth;
	Agent::update();

	if (this->getState() == "Stopped") {
		load = false;
		unload = false;
		finish = false;
		return;

	}

	if (MovingObj::isArrived()) {

		for (auto s : Model::getInstance().getStructures())
			if (strcmp(MovingObj::getDest().c_str(), s->getName().get()) == 0) {
				if (!load) { // arrived to farm
					MovingObj::setSpeed(0); // stop for the next hour for load
					nextSupply = s->getAmount();
					load = true;
					Agent::setState("Loading packages at");
					if (nextSupply > 5)
						nextSupply = 5;
					s->setNextAmount(s->getAmount() - nextSupply);

				} else {

					if (!unload) {  // go from farm to castle after loading
						MovingObj::setNextDest(dest);
						MovingObj::setDest(dest);
						MovingObj::setNextTar(pdest);
						Agent::setState("Heading to");
						unload = true;

					} else { // arrived to castle
						Agent::setNextState("Unload packages at");
						MovingObj::setNextSpeed(0); // finish the work;

						if (finish) {
							Agent::setNextState("finish working at");
							s->setNextAmount(s->getAmount() + supply);
							nextSupply = 0;
							nextHealth++;
							if (nextHealth > 20)
								nextHealth = 20;
						}

						finish = true; // in the next hour
					}
				}
			}
	}
}

void Peasant::setFinish(bool finish) {
	this->finish = finish;
}

void Peasant::setLoad(bool load) {
	this->load = load;
}

void Peasant::setUnload(bool unload) {
	this->unload = unload;
}
