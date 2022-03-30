/*
 * SimObj.cpp
 *
 *  Created on: Jun 18, 2020
 *      Author: cs313311797
 */

#include "SimObj.h"

#include <cstring>

struct Point;

SimObj::SimObj(const char* name_): name(new char[strlen(name_)+1]){

	strcpy(name.get(),name_);

}

SimObj::~SimObj() {
	// TODO Auto-generated destructor stub
}


const shared_ptr<char>& SimObj::getName() const {
	return name;
}

void SimObj::setName(const shared_ptr<char>& name) {
	this->name = name;
}

void SimObj::update() {
}
