/*
 * Structure.h
 *
 *  Created on: Jun 18, 2020
 *      Author: cs313311797
 */

#ifndef STRUCTURE_H_
#define STRUCTURE_H_

#include <string>
#include "Geometry.h"
#include "SimObj.h"

using namespace std;

class Structure : public SimObj {

	int amount;
	int nextAmount;
	Point loc;
public:
	Structure(char* name, Point& point,int amt);
	virtual ~Structure();
	int getAmount() const;
	void setAmount(int amount);
	const Point& getLocation() const;
	void setLocation(const Point& loc);
	int getNextAmount() const;
	void setNextAmount(int nextAmount);
	void update();
};

#endif /* STRUCTURE_H_ */
