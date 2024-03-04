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

string removeRightBlank(string str) {
	cout << str << ' ';
	cout << str[1] << '\n';
	int idx = str.size() - 1;
	while(idx >= 0 && str[idx] == ' ') idx--;

	cout << idx << '\n';

	return str.substr(0, idx + 1);
}

vector<pair<int, int>> getLength(string lengthLine) {
	stringstream ss(lengthLine);

	vector<pair<int, int>> length;
	string len;
	int pos = 0;

	while (getline(ss, len, ' ')) {
		//cout << len << '\n';
		length.push_back({pos, len.size()});
		pos += len.size() + 1;
	}

	// for (auto x : length) {
	// 	cout << x.first << ' ' << x.second << "\n";
	// }
	
	return length;
}

int findAttribute(string attributeLine, string targetAttribute, vector<pair<int, int>> length) {
	for (int i = 0; i<length.size(); i++) {
		string tmp = attributeLine.substr(length[i].X, length[i].Y);
		tmp = removeRightBlank(tmp);

		cout << tmp << ' ' << targetAttribute << '\n';
		if (tmp == targetAttribute) return i;
	}
	return -1;
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
		vector<pair<int, int>> length = getLength(lengthLine);
		
		// 2. ZONE과 ACTIVE attribute를 보려면 어디 부분을 substring으로 잡아야하는지 파악
		// ZONE_idx, ACTIVE_idx는 length 테이블을 볼 때 사용할 index
		int ZONE_idx = findAttribute(attributeLine, "ZONE", length);
		int ACTIVE_idx = findAttribute(attributeLine, "ACTIVE", length);

		cout << ZONE_idx << ' ' << ACTIVE_idx << '\n';

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
