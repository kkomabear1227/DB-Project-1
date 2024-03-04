// Copyright 2022 Wook-shin Han
#include "project1.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <utility>

using namespace std;

#define X first
#define Y second

map<int, int> getLength(string lengthLine) {
	stringstream ss(lengthLine);

	map<int, int> length;
	string len;
	int pos = 0;

	while (getline(ss, len, ' ')) {
		//cout << len << '\n';
		length[pos] = len.size();
		pos += len.size() + 1;
	}

	// for (auto x : length) {
	// 	cout << x.first << ' ' << x.second << "\n";
	// }
	
	return length;
}

int main(int argc, char** argv) {
    if (string(argv[1]) == "q1") {
		ifstream customer_table(argv[2]);
		string attributeLine;
		string lengthLine;

		getline(customer_table, attributeLine);
		getline(customer_table, lengthLine);

		// 1. attribute들의 길이 정보를 먼저 파악한다.
		// stringstream을 활용해 파싱하지 않고, substring으로 파싱할 예정
		map<int, int> length = getLength(lengthLine);
		
		// 2. ZONE과 ACTIVE attribute를 보려면 어디 부분을 substring으로 잡아야하는지 파악
		// ZONE_offset, ACTIVE_offset은 length 테이블을 볼 때 사용할 index
		int ZONE_offset = attributeLine.find("ZONE");
		int ACTIVE_offset = attributeLine.find("ACTIVE");

		//cout << ZONE_offset << ' ' << ACTIVE_offset << '\n';
		//cout << length[ZONE_offset] << ' ' << length[ACTIVE_offset] << '\n';

		// 3. Zonecost table을 바탕으로 set<int> toronto를 만든다.
		// set<int> toronto = makeSet(argv[3]);

		// 4. 남은 Customer table을 보며 ACTIVE가 켜져있는지, ZONE이 toronto인지 확인 후 출력

		//std::ifstream table(argv[3]);
	}
	else if (std::string(argv[1]) == "q2") {
		std::cout << "query2\n";
	}

    return 0;
}
