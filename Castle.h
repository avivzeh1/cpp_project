/*
 * Castle.h
 *
 *  Created on: Jun 18, 2020
 *      Author: cs313311797
 */

#ifndef CASTLE_H_
#define CASTLE_H_

#include "Structure.h"

class Castle : public Structure{

public:
	Castle(char* name_, Point& point,int amt);
	virtual ~Castle();
};

#endif /* CASTLE_H_ */
