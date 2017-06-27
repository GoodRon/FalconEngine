/*
 * Copyright (c) 2017, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include <fstream>
#include <iostream>

#include "helpers.h"

using namespace std;

string engine::helpers::readFile(const string& path) {
	ifstream file;
	file.open(path);
	if (!file.good()) {
		cerr << "Can't open file " << path << endl;
		return std::string();
	}

	string line;
	string content;
	while (getline(file, line)) {
		content += line;
	}
	return content;
}
