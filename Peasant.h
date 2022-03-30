/*
 * Peasant.h
 *
 *  Created on: Jun 18, 2020
 *      Author: cs313311797
 */

#ifndef PEASANT_H_
#define PEASANT_H_

#include "Agent.h"


class Peasant : public Agent {
public:
	Peasant(const char* name, Point& p);
	Peasant(Peasant&& p);
	virtual ~Peasant();
	int getHealth() const;
	void setHealth(int health);
	int getNextHealth() const;
	void setNextHealth(int nextHealth);
	void start_working(string src, string dest,const Point& psrc,const Point& pd ); // set the working for the peasent
	int getNextSupply() const;
	void setNextSupply(int nextSupply);
	const string& getSrc() const;
	void setSrc(const string& src);
	int getSupply() const;
	void setSupply(int supply);
	void update();
	void setFinish(bool finish);
	void setLoad(bool load);
	void setUnload(bool unload);

private:
	int health;
	int nextHealth;
	int supply;
	int nextSupply;
	Point psrc;  // point of the farm that he wiil go
	string dest;
	Point pdest; // point of castle that he will go
	// indicate the state of the the peasent working
	bool load; 
	bool unload;
	bool finish;

};

#endif /* PEASANT_H_ */
