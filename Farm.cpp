/*
 * Farm.cpp
 *
 *  Created on: Jun 18, 2020
 *      Author: cs313311797
 */

#include "Farm.h"

Farm::Farm(char* name ,Point& p, int amt, int rate_) : Structure(name,p, amt), rate(rate_){
	// TODO Auto-generated constructor stub

}

Farm::~Farm() {
	// TODO Auto-generated destructor stub
}

void Farm::update() {

	this->setNextAmount(this->getAmount() + rate);
	Structure::update();
}
