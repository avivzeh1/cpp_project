/*
 * MovingObj.cpp
 *
 *  Created on: Jun 18, 2020
 *      Author: cs313311797
 */

#include "MovingObj.h"
#include "Thug.h"
#include "Peasant.h"
#include "Knight.h"
#include<cmath>
#include <typeinfo>

MovingObj::MovingObj(Point p) : loc(p),nextLoc(p), tar(), nextTar(),
		dest(""), speed(0), nextSpeed(0), nextDest(""), course(-1), nextCourse(-1), distanceTarget(
				0),updateLoc(false) {

}

MovingObj::~MovingObj() {
	// TODO Auto-generated destructor stub
}

const string& MovingObj::getDest() const {
	return dest;
}

void MovingObj::setDest(const string& dest) {
	this->dest = dest;
}

const string& MovingObj::getNextDest() const {
	return nextDest;
}

void MovingObj::setNextDest(const string& nextDest) {
	this->nextDest = nextDest;
}

double MovingObj::getNextSpeed() const {
	return nextSpeed;
}

void MovingObj::setNextSpeed(double nextSpeed) {

	if (nextSpeed <= 30)
		this->nextSpeed = nextSpeed;
	else
		throw "error: max speed is 30 km/h";
}

double MovingObj::getSpeed() const {
	return speed;
}

void MovingObj::setSpeed(double speed) {
	this->speed = speed;
}

double MovingObj::getCourse() const {
	return course;
}

void MovingObj::setCourse(double course) {
	this->course = course;
}

double MovingObj::getNextCourse() const {
	return nextCourse;
}

void MovingObj::setNextCourse(double nextCourse) {
	this->nextCourse = nextCourse;
}

void MovingObj::update() {

	double pi = 2. * atan2(1., 0.);
	dest = nextDest;
	speed = nextSpeed;
	course = nextCourse;
	tar = nextTar;

	if(updateLoc){
		loc = nextLoc;
		updateLoc = false;
		return;
	}

	if (course != -1) { // heading on course
		Polar_vector newp;
		newp.theta = to_radians(course);
		newp.r = speed / 10;
		Cartesian_vector to(newp); // go to point
		loc.x += to.delta_y;
		loc.y += to.delta_x;
	} else {  // heading to target
		Polar_vector newp;
		newp.theta = atan2(tar.y - loc.y, tar.x - loc.x);

		if (newp.theta < 0.)
			newp.theta = 2. * pi + newp.theta; // normalize theta positive
		newp.r = speed / 10;
		Cartesian_vector to(newp); // go to point
		distanceTarget -= sqrt(
				to.delta_x * to.delta_x + to.delta_y * to.delta_y);  // update distance from target
		if (distanceTarget <= 0 && speed != 0) { // don't miss the target
			loc.x = tar.x;
			loc.y = tar.y;
		} else {
			loc.x += to.delta_x; 
			loc.y += to.delta_y;
		}

	}

}

const Point& MovingObj::getLocation() const {
	return loc;
}

void MovingObj::setLocation(const Point& loc) {
	this->loc = loc;
}

const Point& MovingObj::getTar() const {
	return tar;
}

void MovingObj::setTar(const Point& tar) {
	this->tar = tar;
}

const Point& MovingObj::getNextTar() const {
	return nextTar;
}

void MovingObj::setNextTar(const Point& nextTar) {
	distanceTarget = sqrt(
			(nextTar.x - loc.x) * (nextTar.x - loc.x)
					+ (nextTar.y - loc.y) * (nextTar.y - loc.y));
	this->nextTar = nextTar;
}

const Point MovingObj::getNextLoc() const {

	double pi = 2. * atan2(1., 0.);
	Point nextLoc = loc;
	double d = distanceTarget;

	if (course != -1) { // heading on course
		Polar_vector newp;
		newp.theta = to_radians(course);
		newp.r = nextSpeed / 10;
		Cartesian_vector to(newp); // go to point
		nextLoc.x += to.delta_y;
		nextLoc.y += to.delta_x;
	} else {  // heading to target
		Polar_vector newp;
		newp.theta = atan2(nextTar.y - loc.y, nextTar.x - loc.x);

		if (newp.theta < 0.)
			newp.theta = 2. * pi + newp.theta; // normalize theta positive
		newp.r = nextSpeed / 10;
		Cartesian_vector to(newp); // go to point
		d -= sqrt(
				to.delta_x * to.delta_x + to.delta_y * to.delta_y);
		if (d <= 0 && nextSpeed != 0) { // don't miss the target
			nextLoc.x = nextTar.x;
			nextLoc.y = nextTar.y;
		} else {
			nextLoc.x += to.delta_x;
			nextLoc.y += to.delta_y;
		}

	}

	return nextLoc;
}

bool MovingObj::isArrived() {

	return distanceTarget <= 0;
}

void MovingObj::setNextLoc(const Point& nextLoc) {
	updateLoc = true;
	this->nextLoc = nextLoc;
}
