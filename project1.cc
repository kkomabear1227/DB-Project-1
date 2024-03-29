// Copyright 2022 Wook-shin Han
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "project1.h"

using namespace std;

#define X first
#define Y second

string removeRightBlank(string str) {
  int p = str.size() - 1;
  while (p >= 0 && str[p] == ' ') p--;

  return str.substr(0, p + 1);
}

map<int, int> getLength(string lengthLine) {
  stringstream ss(lengthLine);

  map<int, int> length;
  string len;
  int pos = 0;

  while (getline(ss, len, ' ')) {
    // cout << len << '\n';
    length[pos] = len.size();
    pos += len.size() + 1;
  }

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

  // cout << length[ZONEID_offset] << ' ' << length[ZONEDESC_offset] << '\n';

  set<int> toronto;
  string line;
  while (getline(zonecost_table, line)) {
    // cout << line.substr(ZONEID_offset, length[ZONEID_offset]) << '/';
    // cout << line.substr(ZONEDESC_offset, length[ZONEDESC_offset]) << '\n';

    int zid = stoi(
        removeRightBlank(line.substr(ZONEID_offset, length[ZONEID_offset])));
    string zdesc =
        removeRightBlank(line.substr(ZONEDESC_offset, length[ZONEDESC_offset]));

    // cout << zid << ' ' << zdesc << '\n';
    if (zdesc == "Toronto") toronto.insert(zid);
  }

  zonecost_table.close();
  return toronto;
}

void query2(string link, map<int, set<string>> purchase) {
  ifstream product_table(link);
  string attributeLine;
  string lengthLine;

  getline(product_table, attributeLine);
  getline(product_table, lengthLine);

  // 1. attribute들의 길이 정보 파악
  map<int, int> length = getLength(lengthLine);

  int BARCODE_offset = attributeLine.find("BARCODE");
  int PRODDESC_offset = attributeLine.find("PRODDESC");

  string query;
  while (getline(product_table, query)) {
    int barcode = stoi(
        removeRightBlank(query.substr(BARCODE_offset, length[BARCODE_offset])));
    string proddesc = removeRightBlank(
        query.substr(PRODDESC_offset, length[PRODDESC_offset]));

    if (purchase[barcode].size() >= 2)
      cout << barcode << ' ' << proddesc << '\n';
  }
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

    // 2. ZONE과 ACTIVE attribute를 보려면 어디 부분을 substring으로
    // 잡아야하는지 파악 ZONE_offset, ACTIVE_offset은 length 테이블을 볼 때
    // 사용할 index LNAME_offset도 필요 (출력에)
    int ZONE_offset = attributeLine.find("ZONE");
    int ACTIVE_offset = attributeLine.find("ACTIVE");
    int LNAME_offset = attributeLine.find("LNAME");

    // cout << ZONE_offset << ' ' << ACTIVE_offset << '\n';
    // cout << length[ZONE_offset] << ' ' << length[ACTIVE_offset] << '\n';

    // 3. Zonecost table을 바탕으로 set<int> toronto를 만든다.
    set<int> toronto = makeSet(argv[3]);

    // 4. 남은 Customer table을 보며 ACTIVE가 켜져있는지, ZONE이 toronto인지
    // 확인 후 출력
    string query;
    while (getline(customer_table, query)) {
      int zone = stoi(
          removeRightBlank(query.substr(ZONE_offset, length[ZONE_offset])));
      int active = stoi(
          removeRightBlank(query.substr(ACTIVE_offset, length[ACTIVE_offset])));

      if (active && toronto.find(zone) != toronto.end()) {
        cout << removeRightBlank(
                    query.substr(LNAME_offset, length[LNAME_offset]))
             << '\n';
      }
    }

    // std::ifstream table(argv[3]);
  } else if (string(argv[1]) == "q2") {
    ifstream lineitem_table(argv[2]);
    string attributeLine;
    string lengthLine;

    getline(lineitem_table, attributeLine);
    getline(lineitem_table, lengthLine);

    // 1. attribute들의 길이 정보를 먼저 파악한다.
    // stringstream을 활용해 파싱하지 않고, substring으로 파싱할 예정
    map<int, int> length = getLength(lengthLine);

    int UNAME_offset = attributeLine.find("UNAME");
    int BARCODE_offset = attributeLine.find("BARCODE");

    map<int, set<string>> purchase;
    string line;
    while (getline(lineitem_table, line)) {
      string uname =
          removeRightBlank(line.substr(UNAME_offset, length[UNAME_offset]));
      int barcode = stoi(removeRightBlank(
          line.substr(BARCODE_offset, length[BARCODE_offset])));

      purchase[barcode].insert(uname);
    }

    query2(argv[3], purchase);
  }

  return 0;
}
