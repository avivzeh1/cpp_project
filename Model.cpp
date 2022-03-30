/*
 * Model.cpp
 *
 *  Created on: Jun 18, 2020
 *      Author: cs313311797
 */

#include "Model.h"
#include <cstring>
#include "Castle.h"
#include "Farm.h"
#include "Peasant.h"
#include "Thug.h"
#include <typeinfo>
#include <iostream>
#include<iomanip>
#include<cstdlib>
#include<cmath>
#include "Knight.h"

using namespace std;

Model & Model::getInstance() {

	if (inst == nullptr)
		inst = new Model(); //LAZY INIT !
	return *inst;
}

int Model::getTime() const {
	
	return time;
}

void Model::setTime(int time) {
	this->time = time;
}

Model::Model() :
		time(0) { /*...*/

}

void Model::addAgent(const char* name, string type, Point& p, string loc) {

	for (auto a : agents)
		if (strcmp(a->getName().get(), name) == 0)
			throw "error: agent is already exist";

	if (loc != "") { // if location is requaired for this agent (knight)
		bool isLoc = false;
		for (auto s : structures)
			if (strcmp(s->getName().get(), loc.c_str()) == 0) {
				p = s->getLocation();
				isLoc = true;
				break;
			}
		if (!isLoc)
			throw "error: start position doesn't exist";
	}

	shared_ptr<SimObj> newObj(new SimObj(name));
	objects.push_back(newObj);

	if (loc == "") { // locatin is not requaired for thug and peasant
		if (strcmp(type.c_str(), "Peasant") == 0) {
			shared_ptr<Agent> newAgent(new Peasant(name, p));
			agents.push_back(newAgent);
			;
		} else {
			shared_ptr<Agent> newAgent(new Thug(name, p));
			agents.push_back(newAgent);
		}

	} else {
		shared_ptr<Agent> newAgent(new Knight(name, p, loc));
		agents.push_back(newAgent);
	}
}

void Model::addStructure(string name, Point& p, int amount, int rate) {

	// remove ',' from the end of the name
	char name_[strlen(name.c_str())]; // space for the name including ',' without null
	strcpy(name_, name.c_str());
	name_[strlen(name.c_str()) - 1] = '\0';  // null instead of ','

	shared_ptr<SimObj> newObj(new SimObj(name_));
	objects.push_back(newObj);

	if (rate == -1) { // rate is not requaired for castle
		shared_ptr<Structure> newStruct(new Castle(name_, p, amount));
		structures.push_back(newStruct);
	} else {
		shared_ptr<Structure> newStruct(new Farm(name_, p, amount, rate));
		structures.push_back(newStruct);
	}

}

void Model::update() {

	time++;

	for (auto s : structures)
		s->update();
	for (auto a : agents)
		a->update();

}

const shared_ptr<View>& Model::getView() const {
	return view;
}

const vector<shared_ptr<Agent> >& Model::getAgents() const {
	return agents;
}

void Model::setAgents(const vector<shared_ptr<Agent> >& agents) {
	this->agents = agents;
}

const vector<shared_ptr<SimObj> >& Model::getObjects() const {
	return objects;
}

void Model::setObjects(const vector<shared_ptr<SimObj> >& objects) {
	this->objects = objects;
}

const vector<shared_ptr<Structure> >& Model::getStructures() const {
	return structures;
}

void Model::setStructures(const vector<shared_ptr<Structure> >& structures) {
	this->structures = structures;
}

void Model::status() {

	cout << endl;

	for (auto s : structures) {
		const char* type = typeid(*s.get()).name();
		cout << type + 1 << " " << s->getName().get() << " at postion ";
		s->getLocation().print();
		cout << ", Inventory: " << s->getAmount() << endl;
	}

	for (auto a : agents) {
		const char* type = typeid(*a.get()).name();
		cout << type + 1 << " " << a->getName().get() << " at postion ";
		a->getLocation().print();
		cout << " " << a->getState() << " ";

		if (a->getState() == "Heading on course")
			cout << std::fixed << a->getCourse() << " deg";
		if (a->getState() == "Heading to"
				|| a->getState() == "Loading packages at"
				|| a->getState() == "Unload packages at"
				|| a->getState() == "finish working at")
			cout << a->getDest();
		if (a->getState() == "Heading to position")
			a->getTar().print();
		cout << ", speed " << a->getSpeed() << " km/h";
		if (typeid(*a.get()) == typeid(Peasant) && a->getState() != "Dead")
			cout << ", supply: " << static_cast<Peasant*>(a.get())->getSupply()
					<< ", Health: "
					<< static_cast<Peasant*>(a.get())->getHealth();
		if (typeid(*a.get()) == typeid(Thug) && a->getState() != "Dead")
			cout << ", power: " << static_cast<Thug*>(a.get())->getPower();

		cout << endl;
	}
}

void Model::agentOperation(const shared_ptr<Agent>& a, int op, double theta,
		double speed, string posname, string src, string dest, const Point& tar,
		string peasant) {

	if (a->getState() == "Dead")
		throw "This agent state is dead";

	bool srcExist = false, destExist = false, peasantExist = false, canAttack =
			true;
	;
	Point p, pd;

	;
	switch (op) {
	case 1: // course command
		if (speed != -1)
			a->setNextSpeed(speed);
		else if (typeid(*a.get()) == typeid(Peasant))
			a->setNextSpeed(5);
		if (typeid(*a.get()) == typeid(Knight))
			a->setNextSpeed(10);
		a->setNextState("Heading on course");
		a->setNextCourse(theta);
		break;
	case 2: //position command
		a->setNextTar(tar);
		a->setNextCourse(-1);
		a->setNextState("Heading to position");
		if (speed != -1)
			a->setNextSpeed(speed);
		else if (typeid(*a.get()) == typeid(Peasant))
			a->setNextSpeed(5);
		if (typeid(*a.get()) == typeid(Knight))
			a->setNextSpeed(10);

		break;
	case 3: // destination command
		for (auto s : structures)
			if (strcmp(dest.c_str(), s->getName().get()) == 0) {
				destExist = true;
				p = s->getLocation();
			}
		if (!destExist)
			throw "error: this destination doesn't exist";
		a->setNextState("Heading to");
		a->setNextCourse(-1);
		a->setNextSpeed(10);
		a->setNextDest(dest);
		a->setNextTar(p);
		break;
	case 4:
		a->stop();
		break;
	case 5: // attack command
		for (auto ag : agents)  //search the peasant
			if (strcmp(peasant.c_str(), ag->getName().get()) == 0
					&& typeid(*ag.get()) == typeid(Peasant)) {
				peasantExist = true;
				a->setNextState("Stopped");
				static_cast<Peasant*>(ag.get())->setNextHealth(
						static_cast<Peasant*>(ag.get())->getHealth() - 1);
				if (static_cast<Peasant*>(ag.get())->getNextHealth() == 0)
					ag->setNextState("Dead");
				p = ag->getNextLoc(); // peasant position  in the next hour
				a->setNextLoc(p); // the thug will be in the attack position
				if (static_cast<Thug*>(a.get())->getNextPower()
						<= static_cast<Peasant*>(ag.get())->getNextHealth())
					canAttack = false;

				for (auto aga : agents) // search knights near the peasant
					if (typeid(*a.get()) == typeid(Knight)) {
						Point k(aga->getNextLoc().x, aga->getNextLoc().y);
						if (pow(p.x - k.x, 2) + pow(p.y - k.y, 2)
								<= 0.25 * 0.25) { // if there is a knight in 2.5 km radius near the peasant
							canAttack = false;
						}
					}
				if (pow(a->getNextLoc().x - p.x, 2)
						+ pow(a->getNextLoc().y - p.y, 2) > 0.1 * 0.1) // if the peasant is not in 1 km radius near the thug
					canAttack = false;

				if (canAttack)
					static_cast<Thug*>(a.get())->attack(ag);
				else { // attack fail
					static_cast<Thug*>(a.get())->setNextPower(
							((Thug*) (a.get()))->getNextPower() - 1);
					if (static_cast<Thug*>(a.get())->getNextPower() == 0)
						static_cast<Thug*>(a.get())->setNextState("Dead");
				}
			}
		if (!peasantExist)
			throw "error: peasant doesn't exist";

		break;
	case 6: //start working command
		for (auto s : structures)
			if (strcmp(src.c_str(), s->getName().get()) == 0
					&& typeid(*s.get()) == typeid(Farm)) {  // search the farm
				srcExist = true;
				p = s->getLocation();
			}
		for (auto s : structures)
			if (strcmp(dest.c_str(), s->getName().get()) == 0
					&& typeid(*s.get()) == typeid(Castle)) { // search the castle

				pd = s->getLocation();
				destExist = true;
			}

		if (!srcExist)
			throw "farm doesn't exist, error: USAGE start_working FARM-NAME CASTLE-NAME";
		if (!destExist)
			throw "castle doesn't exist, error: USAGE start_working FARM-NAME CASTLE-NAME";
		static_cast<Peasant*>(a.get())->start_working(src, dest, p, pd);
		a->setNextState("Heading to");

		break;
	default:
		break;
	}
}

void Model::attach(const shared_ptr<View>& v) {
	this->view = view;
}

