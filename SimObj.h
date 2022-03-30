/*
 * SimObj.h
 *
 *  Created on: Jun 18, 2020
 *      Author: cs313311797
 */

#ifndef SIMOBJ_H_
#define SIMOBJ_H_

#include <memory>
#include "Geometry.h"

using namespace std;
class SimObj {

	shared_ptr<char> name;

public:
	SimObj(const char* name_);
	virtual ~SimObj();
	virtual void update();
	const shared_ptr<char>& getName() const;
	void setName(const shared_ptr<char>& name);

};

#endif /* SIMOBJ_H_ */
