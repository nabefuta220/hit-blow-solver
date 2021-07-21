#ifndef __HBSOLVER_HPP

#include <utility>
#include <vector>
#define __HBSOLVER_HPP

class HBsolver {
private:
	int size;
	int colar;
	bool same_guard;
	/**
	 * 解答としてあり得る組み合わせ
	 */
	std::vector<std::vector<int>> pattern;
	/**
	 * 予想した色としてあり得る組み合わせ
	 */
	std::vector<std::vector<int>> candidate;
	/**
	 * 初期化
	 */
	void init(std::vector<int> &list, int at, bool same_guard);
	/**
	 * 同じ色が含まれるかを調べる
	 */
	bool is_same(std::vector<int> sets);

public:
	/**
	 * コンストラクタ
	 * colar色のsize個の全組み合わせを列挙する
	 */
	HBsolver(int size, int colar, bool same_guard);
	/**
	 * 予想とその解答からあり得る候補を絞り込む
	 */

	int scan(std::vector<int> attempt, std::pair<int, int> result);
	/**
	 * 2つの候補間の位置が同じ色の個数と、色が同じ個数を返す
	 */
	std::pair<int, int> cheak_diff(std::vector<int> predict,
	                               std::vector<int> ans);
	/**
	 *min-max法を用いて、次に出すべき候補を出力する
	 */
	std::vector<int> suggest();
	int getSize() const;
	int getColar() const;
	std::vector<std::vector<int>> getCandidate() const;
};
#endif
