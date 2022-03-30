#include <iostream>
#include "Controller.h"
#include "Model.h"

using namespace std;

Model *Model::inst = nullptr;

class Model_destroyer {
public:
	~Model_destroyer() {
		delete Model::inst;
// relying on friend permissions
	}
} md;

int main(int argc, char* args[]) {


	try{
	if(argc != 3)
		throw "ERROR: number of input files is illegal";
	Controller c;
	c.run(args);
	
	}catch(const char *e){
		cerr << e;
	}

	return 0;
}
