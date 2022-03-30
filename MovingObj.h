/*
 * MovingObj.h
 *
 *  Created on: Jun 18, 2020
 *      Author: cs313311797
 */

#ifndef MOVINGOBJ_H_
#define MOVINGOBJ_H_

#include "Geometry.h"

class MovingObj {
public:
	MovingObj(Point p);
	virtual ~MovingObj();
	// getters and setters
	const string& getDest() const;
	void setDest(const string& dest);
	const string& getNextDest() const;
	void setNextDest(const string& nextDest);
	double getNextSpeed() const;
	void setNextSpeed(double nextSpeed);
	double getSpeed() const;
	void setSpeed(double speed);
	double getCourse() const;
	void setCourse(double course);
	double getNextCourse() const;
	void setNextCourse(double nextCourse);
	void update();
	const Point& getLocation() const;
	void setLocation(const Point& loc);
	const Point& getTar() const;
	void setTar(const Point& tar);
	const Point& getNextTar() const;
	void setNextTar(const Point& nextTar);
	const Point getNextLoc() const; // acumulate the position in the next time according to his speed
	bool isArrived();  // return true if the object arrived to his target 
	void setNextLoc(const Point& nextLoc);

private:
	Point loc; // current point position of this object
	Point nextLoc; // next point position of this object (after update)
	Point tar;  // current target point position of this object
	Point nextTar; // next target point position of this object (after update)
	string dest; // name of destination
	double speed;   // current speed of this object
	double nextSpeed; // next speed of this object
	string nextDest;  // next destination
	double course; // current course if the object is moving on course, -1 if not
	double nextCourse; //next course if the object is moving on course, -1 if not
	double distanceTarget;  // the distance from the target postion
	bool updateLoc;  // indicate that the object needs update positon (in case of thug attack a peasant and he is stopping in the attack location)
};

#endif /* MOVINGOBJ_H_ */
