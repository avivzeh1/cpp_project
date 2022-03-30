/*
 * View.cpp
 *
 *  Created on: Jun 18, 2020
 *      Author: cs313311797
 */

#include "View.h"

#include <cmath>
#include <cstring>
#include <iostream>
#include <sstream>
#include "Model.h"

using namespace std;
View::View() {
	set_defaults();

}

View::~View() {
	// TODO Auto-generated destructor stub
}

bool View::get_subscripts(int &ix, int &iy, Point location) const {
	// adjust with origin and scale
	Cartesian_vector subscripts;
	subscripts.delta_x = (location.x - origin.x) / scale;
	subscripts.delta_y = (location.y - origin.y) / scale;
	// Truncate coordinates to appropriate integer after taking the floor.
	// The floor function will produce a floating point value that is
	// the greatest integer that is smaller than the argument, even for negative values.
	// So - 0.05 is floored to -1., which will be outside the array.
	if (ix == int(floor(subscripts.delta_x))
			&& iy == int(floor(subscripts.delta_y)))
		return true;

	// if out of range, return false
//	if ((ix < 0) || (ix >= size) || (iy < 0) || (iy >= size)) {
//		return false;
//	}
	return false;
}

void View::update_location() {

//	for(auto obj : objects)  // check iof the object is already exist
//		if(strcmp(name.c_str(),obj->getName().get()) == 0)
//

}

void View::update_remove(const std::string& name) {
}

void View::draw() const {

	cout << "Display size: " << size << ", scale: " << scale << ", origin: ";
	origin.print();
	cout << endl;

	int lnum = size * scale - scale + origin.y;

	stringstream s;
	s << lnum;
	string sp;
	s >> sp;
	int spaces = strlen(sp.c_str());
	spaces++;
	for (int i = 0; i < size; i++) {
		stringstream s;
		s << lnum;
		string sp;
		s >> sp;
		if (i % 3 == 0) {
			cout << lnum;
			for (unsigned int j = 0; j < spaces - strlen(sp.c_str()); j++)
				cout << " ";
		} else
			for (int j = 0; j < spaces; j++)
				cout << " ";
		for (int j = 0; j < size; j++) {
			bool isObj = false;
			int x = j, y = size - i - 1;
			for (auto obj : Model::getInstance().getStructures()) {
				if (get_subscripts(x, y, obj->getLocation())) {
					cout << obj->getName().get()[0] << obj->getName().get()[1];
					isObj = true;
					break;
				}
			}
			for (auto obj : Model::getInstance().getAgents()) {
				if (get_subscripts(x, y, obj->getLocation()) && !isObj) {
					cout << obj->getName().get()[0] << obj->getName().get()[1];
					isObj = true;
					break;
				}
			}
			if (!isObj) {
				cout << ". ";
			}
		}
		cout << endl;
		lnum -= scale;

	}
	lnum = origin.x;
	stringstream is;
	is << lnum;
	string num;
	is >> num;
	for (unsigned int j = 0; j < spaces - strlen(num.c_str()) + 1; j++)
		cout << " ";
	cout << lnum;
	for (int j = 0; j < size / 3; j++) {

		lnum += scale * 3;
		stringstream s;
		s << lnum;
		string sp;
		s >> sp;
		for (unsigned int i = 0; i < 6 - strlen(sp.c_str()); i++)
			cout << " ";

		cout << lnum;
	}
	cout << endl;
}

void View::set_size(int size) {
	this->size = size;
}

void View::set_scale(double scale) {
	this->scale = scale;
}

void View::set_origin(Point origin) {
	this->origin = origin;
}

void View::set_defaults() {

	size = 25;
	origin.x = 0;
	origin.y = 0;
	scale = 2;
}
