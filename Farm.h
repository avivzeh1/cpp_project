/*
 * Farm.h
 *
 *  Created on: Jun 18, 2020
 *      Author: cs313311797
 */

#ifndef FARM_H_
#define FARM_H_

#include "Structure.h"

class Farm : public Structure{
	int rate;
public:
	Farm(char* name,Point& p, int amount, int rate);
	virtual ~Farm();
	void update();  //  update the detatils of this farm
};

#endif /* FARM_H_ */
