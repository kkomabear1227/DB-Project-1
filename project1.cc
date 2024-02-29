// Copyright 2022 Wook-shin Han
#include "project1.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

std::string removeDuplicateBlank(std::string str) {
	int p = 0;
	while(p < str.size() && str[p] == ' ') p++;

	std::string ret = "";
	if (p != str.size()) {
		ret += str[p];
		p++;
	}

	for (int i = p; i<str.size(); i++) {
		if (str[i] == ' ') {
			if (ret[ret.size() - 1] != ' ') ret = ret + " ";
		}
		else {
			ret = ret + str[i];
		}
	}

	return ret;
}

int main(int argc, char** argv) {
    std::cout << argv[1] << ' ' << argv[2] << ' ' << argv[3] << '\n';
    if (std::string(argv[1]) == "q1") {
        std::ifstream customer_table(argv[2]);
		std::string line;

		getline(customer_table, line);
		line = removeDuplicateBlank(line);
		std::stringstream ss(line);

		std::cout << line << '\n';
		std::vector<std::string> attribute;
		std::string col;

		while (getline(ss, col, ' ')) {
			//std::cout << col << '\n';
			attribute.push_back(col);
		}

		getline(customer_table, line);
		line = removeDuplicateBlank(line);
		std::stringstream ss2(line);

		//std::cout << line << '\n';		
		std::vector<int> length;
		std::string len;

		while (getline(ss2, len, ' ')) {
			//std::cout << len << '\n';
			length.push_back(len.size());
		}
		

		//std::ifstream table(argv[3]);
	}
	else if (std::string(argv[1]) == "q2") {
		std::cout << "query2\n";
	}

    return 0;
}
