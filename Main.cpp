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
	do {
		attempt = tri.suggest();
		cout << "next shoud: ";
		for (int i = 0; i < SIZE; i++) {
			cout << attempt[i] << " ";
		}
		cout << endl;
		cout << "input: ";
		for (int i = 0; i < SIZE; i++) {
			cin >> attempt[i];
		}
		pair<int, int> result;
		cout << "hit , blow: ";
		cin >> result.first >> result.second;
		res = tri.scan(attempt, result);
		cout <<"possible pattern : "<< res << endl;
	} while (res != 1);
	attempt = tri.suggest();
	cout << "next shoud: ";
	for (int i = 0; i < SIZE; i++) {
		cout << attempt[i] << " ";
	}
	cout << endl;
}