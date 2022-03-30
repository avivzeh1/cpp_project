/*
 * Knight.h
 *
 *  Created on: Jun 18, 2020
 *      Author: cs313311797
 */

#ifndef KNIGHT_H_
#define KNIGHT_H_

#include <string>
#include <vector>
#include "Structure.h"

#include "Agent.h"

class Knight : public Agent{
public:
	Knight(const char* name, Point& p,string loc);
	virtual ~Knight();
	void update(); // updtate the knight to next time state
	const shared_ptr<Structure> findClosest(); // return smart pointer to the closest structure to this knight
	bool isVisited(const char *name); // gets the name of structure and return true id this knight visited this structure

private:
	vector<string> visited;  // include the structures that this knight visited
	string first; // the name of the structure the knight started from
	bool completed; // indicate that the knight tour is copleted
};

#endif /* KNIGHT_H_ */
