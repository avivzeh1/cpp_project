/*
 * Controller.cpp
 *
 *  Created on: Jun 18, 2020
 *      Author: cs313311797
 */

#include "Controller.h"

#include <cstring>
#include <iostream>
#include <typeinfo>
#include "Geometry.h"
#include<sstream>
#include "Model.h"
#include "SimObj.h"
#include "Thug.h"
#include <fstream>
#include "Peasant.h"
#include "Knight.h"

Controller::Controller() :
		view(new View()) {
	Model::getInstance().attach(view);
}

Controller::~Controller() {

}

void Controller::run(char* args[]) {

	ifstream f1(args[1]);
	ifstream f2(args[2]);
	char format;
	Point p;

	if (!f1 || !f2)
		throw "ERROR opening the specified file.";

	string input;

	while (!f1.eof()) {  //create castles
		string name = "";
		double x, y;
		int amount = -1;

		getline(f1, input); /*get the arguments for this command*/
		istringstream s(input); /*istringstream with the arguments for read each argument*/
		s >> name >> format >> x >> format >> y >> format >> format >> amount;

		if (name == "" || amount == -1 || !s.eof())
			throw "error: content of castles input file is illegal";

		p.x = x;
		p.y = y;
		Model::getInstance().addStructure(name, p, amount);
	}

	while (!f2.eof()) {  //create castles
		string name = "";
		double x, y;
		int amount = -1;
		int rate = -1;

		getline(f2, input); /*get the arguments for this command*/
		istringstream s(input); /*istringstream with the arguments for read each argument*/
		s >> name >> format >> x >> format >> y >> format >> format >> amount
				>> format >> rate;

		if (name == "" || amount == -1 || rate == -1 || !s.eof())
			throw "error: content of farms input file is illegal";

		p.x = x;
		p.y = y;
		Model::getInstance().addStructure(name, p, amount, rate);
	}

	while (cin.good()) {

		bool exe = false;

		try {
			cout << "Time " << Model::getInstance().getTime()
					<< ": Enter command: ";
			cin >> input;

			for (auto a : Model::getInstance().getAgents())
				if (strcmp(input.c_str(), a->getName().get()) == 0) {
					exe = true;

					string inp;
					cin >> inp;

					if (inp == "course") {

						if (typeid(*a.get()) == typeid(Peasant))
							throw "error: illegal command for this agent";

						getline(cin, input); /*get the arguments for this command*/
						istringstream s(input); /*istringstream with the arguments for read each argument*/
						double speed = -1;
						double theta;
						s >> theta >> speed;

						if (typeid(*a.get()) == typeid(Thug)) {

							if (speed == -1)
								throw "error: for this agent speed is required";

							Model::getInstance().agentOperation(a, 1, theta,
									speed);
						}
						else
						Model::getInstance().agentOperation(a, 1, theta);

					} else if (inp == "destination") {
						if (typeid(*a.get()) != typeid(Knight))
							throw "error: illegal command for this agent";

						string dest;
						cin >> dest;
						Model::getInstance().agentOperation(a, 3, -1, -1, "",
								"", dest);

					} else if (inp == "position") {

						if (typeid(*a.get()) == typeid(Peasant))
							throw "error: illegal command for this agent";

						double x, y;
						getline(cin, input); /*get the arguments for this command*/
						istringstream s(input); /*istringstream with the arguments for read each argument*/

						s >> format;
						if (format != '(')
							throw "error: USAGE position (x,y)";
						s >> x >> format;
						if (format != ',')
							throw "error: USAGE position (x,y)";
						s >> y >> format;
						if (format != ')')
							throw "error: USAGE position (x,y)";

						p.x = x;
						p.y = y;
						if (typeid(*a.get()) == typeid(Thug)) {
							double speed = -1;
							s >> speed;
							cerr << speed;
							if (speed == -1)
								throw "error: for this agent speed is required";

							Model::getInstance().agentOperation(a, 2, -1, speed,
									"", "", "", p);
						}
						else
							Model::getInstance().agentOperation(a, 2, -1, -1,
																"", "", "", p);

					} else if (inp == "stop")
						Model::getInstance().agentOperation(a, 4);

					else if (inp == "start_working") {
						if (typeid(*a.get()) != typeid(Peasant))
							throw "error: this agent can't work";
						string src = "", dest = "";
						getline(cin, input); /*get the arguments for this command*/
						istringstream s(input); /*istringstream with the arguments for read each argument*/

						s >> src >> dest;

						if (src == "" || dest == "" || !s.eof())
							throw "error: USAGE start_working FARM-NAME CASTLE-NAME";

						Model::getInstance().agentOperation(a, 6, -1, -1, "",
								src, dest);
					}
					else if(inp == "attack"){

						if (typeid(*a.get()) != typeid(Thug))
							throw "error: this agent can't attack";
						string peasant = "";
						cin >> peasant;
						if(peasant == "")
							throw "error: USAGE attack PEASNT-NAME";
						Model::getInstance().agentOperation(a, 5, -1, -1, "",
														"", "",p, peasant);

					}
					else
						throw "error: illegal command for agent";

				}

			if (input == "exit")
				return;
			else if (input == "show")
				view->draw();
			else if (input == "size") {
				int arg1 = 0;
				getline(cin, input); /*get the arguments for this command*/
				istringstream s(input); /*istringstream with the arguments for read each argument*/
				s >> arg1;

				if (arg1 == 0 || arg1 <= 6 || arg1 > 30 || !s.eof())
					throw "error: USAGE size INTEGER between 7-30.";
				view->set_size(arg1);
			} else if (input == "default")
				view->set_defaults();
			else if (input == "zoom") {
				double arg = 0;
				getline(cin, input); /*get the arguments for this command*/
				istringstream s(input); /*istringstream with the arguments for read each argument*/
				s >> arg;

				if (arg <= 0 || !s.eof())
					throw "error: USAGE zoom positive DOUBLE.";
				view->set_scale(arg);
			} else if (input == "pan") {
				double x, y;
				getline(cin, input); /*get the arguments for this command*/
				istringstream s(input); /*istringstream with the arguments for read each argument*/
				s >> x >> y;

				if (!s.eof())
					throw "error: USAGE size INTEGER between 7-30.";
				Point op(x, y);
				view->set_origin(op);

			} else if (input == "create") {
				string name = "", type = "", pos = "";
				double x, y;
				getline(cin, input); /*get the arguments for this command*/
				istringstream s(input); /*istringstream with the arguments for read each argument*/
				s >> name >> type;

				for (auto a : Model::getInstance().getAgents())
					if (strcmp(input.c_str(), a->getName().get()) == 0)
						throw "error: agent with the same name is already exist.";

				if (type == "Knight") {
					s >> pos;
					if (name == "" || type == "")
						throw "error: USAGE create NAME AGENT-TYPE POINT/POSITION-NAME ";
					Model::getInstance().addAgent(name.c_str(), type, p, pos);
				} else if (type == "Peasant" || type == "Thug") {
					if (s.eof())
						throw "position point is missing";
					s >> format >> x >> format >> y >> format;
					p.x = x;
					p.y = y;
					if (name == "" || type == "")
						throw "error: USAGE create NAME AGENT-TYPE POINT/POSITION-NAME ";
					Model::getInstance().addAgent(name.c_str(), type, p);
				} else
					throw "error: invalid type of agent";

			} else if (input == "status")
				Model::getInstance().status();
			else if (input == "go")
				Model::getInstance().update();
			else
				if(!exe)
				throw "error: illegal command";

		} catch (const char* e) {
			cout << e << endl;
			;
		}
	}

}
