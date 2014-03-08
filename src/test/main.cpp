#include <iostream>

#include "Engine.h"

using namespace std;

int main(int argc, char** argv) {
	cout << "Hello World!" << endl;

	Engine engine(argc, argv);

	engine.execute();

	return 0;
}

