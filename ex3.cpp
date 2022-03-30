#include <iostream>
int test = 0;
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

//int main(int argc, char* args[]) {
//
//
//	try{
//	if(argc != 3)
//		throw "ERROR: number of input files is illegal";
//	Controller c;
//	c.run(args);
//	
//	}catch(const char *e){
//		cerr << e;
//	}
//
//	return 0;
//}

template<class T>
void swa(T& a, T& b) {
T tmp = {move(a)};
a = move(b);
b = move(tmp);
}

int main()
{
	int a = 5;
	int y = 42;
	int *arr = new int[10];
	arr[5] = 8;
swa(a,y);
printf("%d",arr[5]);
printf("%d",y);
return 0;
}
