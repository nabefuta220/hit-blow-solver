#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <iterator>
#include <algorithm>
#define CLOAR 10
#define SIZE 4
// https://www.gamesforthebrain.com/japanese/guesscolors/
using namespace std;
class possible_list
{
private:
	int size;
	int colar;
	bool same_guard;
	/*
解答としてあり得る組み合わせ
	*/
	vector<vector<int>> pattern;
	/*
予想した色としてあり得る組み合わせ
	*/
	vector<vector<int>> candidate;
	/*
	初期化
	*/
	void init(vector<int> &list, int at, bool same_guard)
	{
		if (at == this->size)
		{
			if(same_guard==true && this->is_same(list))
				return;
			this->candidate.push_back(list);
			this->pattern.push_back(list);
			return;
		}
		for (int i = 0; i < this->colar; i++)
		{
			list[at] = i;
			init(list, at + 1, same_guard);
		}
	}
	/*
同じ色が含まれるかを調べる
	*/
	bool is_same(vector<int> sets)
	{
		set<int> dict;
		for (int i : sets)
		{
			dict.insert(i);
		}
		return dict.size() != sets.size();
	}

public:
	/*
コンストラクタ
colar色のsize個の全組み合わせを列挙する
	*/
	possible_list(int size, int colar, bool same_guard)
	{
		vector<int> single_list(size, 0);
		this->size = size;
		this->same_guard = same_guard;
		this->colar = colar;
		this->init(single_list, 0,same_guard);
	}
	/*
	予想とその解答からあり得る候補を絞り込む
	*/
	int scan(vector<int> attempt, pair<int, int> result)
	{
		int sum_count = this->candidate.size();
		int count = 0;

		if (attempt.size() != this->size)
		{
			return -1;
		}
		pair<int, int> cheak;

		for (auto itr = this->candidate.begin(); itr != this->candidate.end();)
		{
			count++;
			cheak = cheak_diff(*itr, attempt);
			if (cheak != result)
			{
				itr = this->candidate.erase(itr);
			}
			else
			{
				/*
				clog << "[ ";
				for (int i = 0; i < this->size; i++)
				{
					clog << (*itr)[i] << " ";
				}
				clog << " ]" << endl;
				*/
				itr++;
			}
			if(count > sum_count/20){
				cout <<count <<"/"<< sum_count<<endl;
				
			}
		}
		cout << endl;
		return this->candidate.size();
	}
	/*
	2つの候補間の位置が同じ色の個数と、色が同じ個数を返す
	*/
	pair<int, int> cheak_diff(vector<int> predict, vector<int> ans)
	{
		pair<int, int> res = make_pair(0, 0);
		if (predict.size() != ans.size())
			return make_pair(-1, -1);
		map<int, int> dict_predict, dict_ans;
		for (int i = 0; i < predict.size(); i++)
		{
			res.first += (predict[i] == ans[i]);
			dict_predict[predict[i]]++;
			dict_ans[ans[i]]++;
		}
		for (int i = 0; i < this->colar; i++)
		{
			res.second += min(dict_predict[i], dict_ans[i]);
		}
		res.second -= res.first;
		return res;
	}
	/*
min-max法を用いて、次に出すべき候補を出力する
	*/
	vector<int> suggest()
	{
		pair<int, int> res = make_pair(1 << 20, 0);
		pair<int, int> cnt;
		int maxResult = this->pattern.size();
		if (maxResult == this->candidate.size())
		{
			return this->pattern[0];
		}
		map<pair<int, int>, int> results;
		if(this->candidate.size()==1){
			return this->candidate[0];
		}
		for (int i = 0; i < pattern.size(); i++)
		{
			maxResult = 0;
			results.clear();
			for (auto itr = this->candidate.begin(); itr != this->candidate.end(); itr++)
			{
				cnt = this->cheak_diff(this->pattern[i], *itr);
				results[cnt]++;
			}
			for (auto itr = results.begin(); itr != results.end(); itr++)
			{
				maxResult = max(maxResult, itr->second);
			}
			res = min(res, make_pair(maxResult, i));
			/*
			clog << "this suggest : " <<maxResult<<" "<<i << endl;
			*/
		}
		clog << "cnt suggest : " << res.first << " " << res.second << endl;
		
		return this->pattern[res.second];
	}
	int getSize() const { return this->size; }
	int getColar() const { return this->colar; }
	vector<vector<int>> getCandidate() const { return this->candidate; }
};
int main()
{
	possible_list tri = possible_list(SIZE, CLOAR,true);
	int res = 99;
	vector<int> attempt;
	do
	{
		attempt = tri.suggest();
		cout << "next shoud: ";
		for (int i = 0; i < SIZE; i++)
		{
			cout << attempt[i] << " ";
		}
		cout << endl;
		cout << "input: ";
		for (int i = 0; i < SIZE; i++)
		{
			cin >> attempt[i];
		}
		pair<int, int> result;
		cout << "hit , blow: ";
		cin >> result.first >> result.second;
		res = tri.scan(attempt, result);
		cout << res << endl;
	} while (res != 1);
	attempt = tri.suggest();
	cout << "next shoud: ";
	for (int i = 0; i < SIZE; i++)
	{
		cout << attempt[i] << " ";
	}
	cout << endl;
}