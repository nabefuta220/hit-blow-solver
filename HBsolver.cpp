
#include "HBsolver.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <utility>
#include <vector>

#include "progress.hpp"

void HBsolver::init(std::vector<int> &list, int at, bool same_guard)
{
	if (at == this->size)
	{
		if (same_guard == true && this->is_same(list))
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

bool HBsolver::is_same(std::vector<int> sets)
{
	std::set<int> dict;
	for (int i : sets)
	{
		dict.insert(i);
	}
	return dict.size() != sets.size();
}

HBsolver::HBsolver(int size, int colar, bool same_guard)
{
	std::vector<int> single_list(size, 0);
	this->size = size;
	this->same_guard = same_guard;
	this->colar = colar;
	this->init(single_list, 0, same_guard);
}
int HBsolver::scan(
	std::vector<std::pair<std::vector<int>, std::pair<int, int>>> results)
{
	progressBar bar(this->candidate.size(), 30);

	std::pair<int, int> cheak;

	for (auto itr = this->candidate.begin(); itr != this->candidate.end();)
	{
		for (int i = 0; i < results.size(); i++)
		{
			cheak = cheak_diff(*itr, results[i].first);
			if (cheak != results[i].second)
			{
				itr = this->candidate.erase(itr);
			}
			else
			{
				itr++;
			}
		}
		bar.increase();
	}
	return this->candidate.size();
}
int HBsolver::scan(std::vector<int> attempt, std::pair<int, int> result)
{
	progressBar bar(this->candidate.size(), 30);

	if (attempt.size() != this->size)
	{
		return -1;
	}
	std::pair<int, int> cheak;

	for (auto itr = this->candidate.begin(); itr != this->candidate.end();)
	{
		cheak = cheak_diff(*itr, attempt);
		if (cheak != result)
		{
			itr = this->candidate.erase(itr);
		}
		else
		{
			itr++;
		}
		bar.increase();
	}
	return this->candidate.size();
}

std::pair<int, int> HBsolver::cheak_diff(std::vector<int> predict,
										 std::vector<int> ans)
{
	std::pair<int, int> res = std::make_pair(0, 0);
	if (predict.size() != ans.size())
		return std::make_pair(-1, -1);
	std::map<int, int> dict_predict, dict_ans;
	for (int i = 0; i < predict.size(); i++)
	{
		res.first += (predict[i] == ans[i]);
		dict_predict[predict[i]]++;
		dict_ans[ans[i]]++;
	}
	for (int i = 0; i < this->colar; i++)
	{
		res.second += std::min(dict_predict[i], dict_ans[i]);
	}
	res.second -= res.first;
	return res;
}

std::vector<int> HBsolver::suggest()
{
	std::pair<std::pair<int,int>, int> res = std::make_pair(std::make_pair(1 << 20,1), 0);//[worse patt , !can same ], num
	std::pair<int, int> cnt;
	int maxResult = this->pattern.size();
	if (maxResult == this->candidate.size())
	{
		return this->pattern[0];
	}
	std::map<std::pair<int, int>, int> results;
	if (this->candidate.size() == 1)
	{
		return this->candidate[0];
	}
	progressBar bar(pattern.size(), 30);
	for (int i = 0; i < pattern.size(); i++)
	{
		maxResult = 0;
		results = find_distrubution(this->pattern[i]);
		for (auto itr = results.begin(); itr != results.end(); itr++)
		{
			maxResult = std::max(maxResult, itr->second);
		}
		/*
		for (auto itr = this->candidate.begin(); itr != this->candidate.end();
			 itr++)
		{
			cnt = this->cheak_diff(this->pattern[i], *itr);
			results[cnt]++;
			maxResult = std::max(maxResult, results[cnt]);
			if (maxResult > res.first)
			{
				break;
			}
		}*/

		res = std::min(res, std::make_pair(std::make_pair(maxResult,(int)!(results[std::make_pair(this->size,0)])), i));
		bar.increase();
	}

	return this->pattern[res.second];
}
int HBsolver::getSize() const { return this->size; }
int HBsolver::getColar() const { return this->colar; }
std::vector<std::vector<int>> HBsolver::getCandidate() const
{
	return this->candidate;
}
std::map<std::pair<int, int>, int> HBsolver::find_distrubution(std::vector<int> list)
{
	std::pair<int, int> cnt;
	std::map<std::pair<int, int>, int> res;
	for (auto itr = this->candidate.begin(); itr != this->candidate.end();
		 itr++)
	{
		cnt = this->cheak_diff(list, *itr);
		res[cnt]++;
	}
	return res;
}