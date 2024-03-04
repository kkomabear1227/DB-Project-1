// Copyright 2022 Wook-shin Han
#include "project1.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <vector>
#include <utility>

using namespace std;

#define X first
#define Y second

string removeRightBlank(string str) {
	int p = str.size() - 1;
	while (p >= 0 && str[p]  == ' ') p--;

	return str.substr(0, p + 1);
}

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

set<int> makeSet(string link) {
	ifstream zonecost_table(link);
	string attributeLine;
	string lengthLine;

	getline(zonecost_table, attributeLine);
	getline(zonecost_table, lengthLine);

	// 1. attribute들의 길이 정보 파악
	map<int, int> length = getLength(lengthLine);

	int ZONEID_offset = attributeLine.find("ZONEID");
	int ZONEDESC_offset = attributeLine.find("ZONEDESC");

	//cout << length[ZONEID_offset] << ' ' << length[ZONEDESC_offset] << '\n';

	set<int> toronto;
	string line;
	while(getline(zonecost_table, line)) {
		//cout << line.substr(ZONEID_offset, length[ZONEID_offset]) << '/';
		//cout << line.substr(ZONEDESC_offset, length[ZONEDESC_offset]) << '\n';

		int zid = stoi(removeRightBlank(line.substr(ZONEID_offset, length[ZONEID_offset])));
		string zdesc = removeRightBlank(line.substr(ZONEDESC_offset, length[ZONEDESC_offset]));

		//cout << zid << ' ' << zdesc << '\n';
		if (zdesc == "Toronto") toronto.insert(zid);
	}

	zonecost_table.close();
	return toronto;
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
		// LNAME_offset도 필요 (출력에)
		int ZONE_offset = attributeLine.find("ZONE");
		int ACTIVE_offset = attributeLine.find("ACTIVE");
		int LNAME_offset = attributeLine.find("LNAME");

		//cout << ZONE_offset << ' ' << ACTIVE_offset << '\n';
		//cout << length[ZONE_offset] << ' ' << length[ACTIVE_offset] << '\n';

		// 3. Zonecost table을 바탕으로 set<int> toronto를 만든다.
		set<int> toronto = makeSet(argv[3]);

		// 4. 남은 Customer table을 보며 ACTIVE가 켜져있는지, ZONE이 toronto인지 확인 후 출력
		string query;
		while (getline(customer_table, query)) {
			int zone = stoi(removeRightBlank(query.substr(ZONE_offset, length[ZONE_offset])));
			int active = stoi(removeRightBlank(query.substr(ACTIVE_offset, length[ACTIVE_offset])));

			if (active && toronto.find(zone) != toronto.end()) {
				cout << removeRightBlank(query.substr(LNAME_offset, length[LNAME_offset])) << '\n';
			}
		}

		//std::ifstream table(argv[3]);
	}
	else if (std::string(argv[1]) == "q2") {
		std::cout << "query2\n";
	}

    return 0;
}
