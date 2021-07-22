#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <vector>
#define CLOAR 10
#define SIZE 4
#include "HBsolver.hpp"
// http://beechan.com/hit2.cgi
// https://www.gamesforthebrain.com/japanese/guesscolors/
using namespace std;
int main() {
	HBsolver tri = HBsolver(SIZE, CLOAR, true);
	int res      = 99;
	vector<int> attempt;
	vector<pair<vector<int>, pair<int, int>>> list;
	map<pair<int, int>, int> distri;
	do
	{
		attempt = tri.suggest();
		cout << "next shoud: ";
		for (int i = 0; i < SIZE; i++) {
			cout << attempt[i] << " ";
		}

		cout << "\n districution:" << endl;
		;
		distri = tri.find_distrubution(attempt);
		for (auto itr = distri.begin(); itr != distri.end();itr++){
			cout << "(" << itr->first.first << " " << itr->first.second << ") :" << itr->second << endl;
		}
			cout << "input: ";
		for (int i = 0; i < SIZE; i++) {
			cin >> attempt[i];
		}
		pair<int, int> result;
		cout << "hit , blow: ";
		cin >> result.first >> result.second;
		list.push_back(make_pair(attempt,result));
		cout << "submitted?[1/0]"<<endl;
		int i;
		cin >> i;
		
		if(i==1){
		res = tri.scan(attempt, result);
		list.clear();
		}
		cout <<"possible pattern : "<< res << endl;
	} while (res != 1);
	attempt = tri.suggest();
	cout << "next shoud: ";
	for (int i = 0; i < SIZE; i++) {
		cout << attempt[i] << " ";
	}
	cout << endl;
}