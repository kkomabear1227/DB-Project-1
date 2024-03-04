// Copyright 2022 Wook-shin Han
#include "project1.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <utility>

//Problem: 공백이 2칸 이상이면 stringstream을 활용한 파싱이 이상하게 됨
std::string removeDuplicateBlank(std::string str) {
	int p = 0;
	//앞에 blank를 다 지운다.
	while(p < str.size() && str[p] == ' ') p++;

	std::string ret = "";
	if (p != str.size()) {
		ret += str[p];
		p++;
	}

	// 가운데 blank는 하나만 남긴다.
	for (int i = p; i<str.size(); i++) {
		if (str[i] == ' ') {
			if (ret[ret.size() - 1] != ' ') ret = ret + " ";
		}
		else {
			ret = ret + str[i];
		}
	}

	//뒤에 blank도 다 지운다.
	if (ret[ret.size() - 1] == ' ') ret = ret.substr(0, ret.size() - 1);

	return ret;
}

std::vector<std::string> getAttribute(char* link) {
	std::ifstream customer_table(link);
	std::string line;

	getline(customer_table, line);
	line = removeDuplicateBlank(line);
	std::stringstream ss(line);

	std::vector<std::string> attribute;
	std::string col;

	while (getline(ss, col, ' ')) {
		//std::cout << col << '\n';
		attribute.push_back(col);
	}

	if (attribute[12] == "ACTIVE") std::cout << "Hi\n";

	// for (auto x : attribute) {
	// 	std::cout << x << "i\n";
	// 	std::cout << x << "/\n";
	// }
	// std::cout << '\n';

	return attribute;
}

std::vector<std::pair<int, int>> getLength(char* link) {
	std::ifstream customer_table(link);
	std::string line;

	getline(customer_table, line);
	line = removeDuplicateBlank(line);
	std::stringstream ss2(line);

	//std::cout << line << '\n';		
	std::vector<std::pair<int, int>> length;
	std::string len;
	int pos = 0;

	while (getline(ss2, len, ' ')) {
		//std::cout << len << '\n';
		length.push_back({pos, len.size()});
		pos += len.size() + 1;
	}

	for (auto x : length) {
		std::cout << x.first << ' ' << x.second << '/';
	}
	std::cout << '\n';
	
	return length;
}

int main(int argc, char** argv) {
    if (std::string(argv[1]) == "q1") {
        std::vector<std::string> attribute = getAttribute(argv[2]);
		std::vector<std::pair<int, int>> length = getLength(argv[2]);

		//std::ifstream table(argv[3]);
	}
	else if (std::string(argv[1]) == "q2") {
		std::cout << "query2\n";
	}

    return 0;
}
