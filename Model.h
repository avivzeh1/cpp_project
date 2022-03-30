/*
 * Model.h
 *
 *  Created on: Jun 18, 2020
 *      Author: cs313311797
 */

#ifndef MODEL_H_
#define MODEL_H_

#include <memory>
#include <vector>
#include "Agent.h"
#include "SimObj.h"
#include "Structure.h"
#include "View.h"

using namespace std;
class Model {

public:
	static Model &getInstance();
	/* other non-static members ... */
	Model(const Model&) = delete;
	Model& operator=(const Model&) = delete;
	Model(const Model&&) = delete;
	Model& operator=(const Model&&) = delete;
	void addAgent(const char* name, string type, Point& p, string loc = "");
	void addStructure(string name, Point& p, int amount, int rate = -1);
	void update(); // update all the objects in the system
	// getters and setters
	int getTime() const;
	void setTime(int time);
	const shared_ptr<View>& getView() const;
	const vector<shared_ptr<Agent> >& getAgents() const;
	void setAgents(const vector<shared_ptr<Agent> >& agents);
	const vector<shared_ptr<SimObj> >& getObjects() const;
	void setObjects(const vector<shared_ptr<SimObj> >& objects);
	const vector<shared_ptr<Structure> >& getStructures() const;
	void setStructures(const vector<shared_ptr<Structure> >& structures);
	void status(); // presents the state of the objects
	void agentOperation(const shared_ptr<Agent>& a, int op, double theta = -1,
			double speed = -1, string pname = "", string src = "", string dest =
					"", const Point& tar = Point(), string peasnt = ""); // called by the controller and gets the arguments for the specific command for agent
	void attach(const shared_ptr<View>& v); //add view to the model

	friend class Model_destroyer;
private:
	static Model *inst;
	vector<shared_ptr<Structure>> structures;
	vector<shared_ptr<Agent>> agents;
	vector<shared_ptr<SimObj>> objects; // structures and agents
	shared_ptr<View> view;
	int time;
	Model();
};

#endif /* MODEL_H_ */
