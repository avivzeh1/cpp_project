/*
 * Controller.h
 *
 *  Created on: Jun 18, 2020
 *      Author: cs313311797
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <memory>
#include "View.h"

using namespace std;
class Controller {
public:
	Controller();
	void run(char* args[]);
	virtual ~Controller();
private:
	shared_ptr<View> view;
};

#endif /* CONTROLLER_H_ */
