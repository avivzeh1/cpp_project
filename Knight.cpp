/*
 * Knight.cpp
 *
 *  Created on: Jun 18, 2020
 *      Author: cs313311797
 */

#include "Knight.h"

#include <memory>
#include <vector>
#include <cmath>
#include <cstring>
#include "Model.h"

Knight::Knight(const char* name, Point& p,string loc) :
		Agent(name, p), first(loc),completed(false) {

	visited.push_back(loc); // starting place

}

Knight::~Knight() {
	// TODO Auto-generated destructor stub
}

void Knight::update() {

	if (!MovingObj::isArrived()) { // if the knight not yet arrived to his target, update his position
		Agent::update();
		return;
	}
	if(completed){   // if the tour is completed stop the knight and resert his visited structures
		MovingObj::setNextSpeed(0);
		Agent::setNextState("Stopped");
		unsigned int size = visited.size();
		for(unsigned int i = 0; i < size; i++); //reset the memory of visited structures
			visited.pop_back();
		Agent::update();
		return;
	}

	// else find the next target and go there
	visited.push_back(MovingObj::getDest());
	shared_ptr<Structure> nextTar = findClosest();

	if (nextTar == nullptr) {  // if there is no next target for the knight, he finished, return to the first structure
		MovingObj::setNextDest(first);
		completed = true;

		for (auto s : Model::getInstance().getStructures())
			if (strcmp(first.c_str(), s->getName().get()) == 0)
				MovingObj::setNextTar(s->getLocation());

		Agent::update();
		return;
	}

	string next = nextTar->getName().get();
	MovingObj::setNextDest(next);
	MovingObj::setNextTar(nextTar->getLocation());

	Agent::update();

}

const shared_ptr<Structure> Knight::findClosest() {

	double min;
	shared_ptr<Structure> closest = nullptr;

	for (auto s : Model::getInstance().getStructures()){

		if (!isVisited(s->getName().get())){  // find strcture that was not visited 
			closest = s;
			min = pow(s->getLocation().x - this->getLocation().x, 2)
						+ pow(s->getLocation().y - this->getLocation().y, 2);
			break;
		}
	}

	if (closest == nullptr) // all structures are visited
		return nullptr;

	for (auto s : Model::getInstance().getStructures()) {
		double d = pow(s->getLocation().x - this->getLocation().x, 2)
				+ pow(s->getLocation().y - this->getLocation().y, 2);  // distance
		if (min >= d && !isVisited(s->getName().get())) {

			if (min != d)
				closest = s;
			else if (strcmp(closest->getName().get(), s->getName().get()) > 0)  // in case of equal distance
				closest = s;

			min = d;
		}
	}
	return closest;
}

bool Knight::isVisited(const char *name) {

	bool visit = false;

	for (auto s : visited)
		if (strcmp(name, s.c_str()) == 0)
			visit = true;

	return visit;

}

