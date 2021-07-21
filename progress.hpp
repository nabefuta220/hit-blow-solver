#ifndef __PROGREE_HPP
#define __PROGREE_HPP
class progressBar {
private:
	int target;
	int cnt;
	int segment;
	int lastShow;

public:
	/**
	 * コンストラクタ
	 * 目標の値と分割する値を決める
	 */
	progressBar(int target, int segment);
	/**
	 * cntをnum増やす
	 * その時に前回の表示からterget/segment分超えていれば現在の状況を表示する
	 */
	void increase(int num);
	/**
	 * cntを1増やす
	 */
	void increase();

	/**
	 * 現在の状況を表示する
	 * そのとき、cnt=targetならば代わりに"done!"と表示する
	 */
	void show();
};
#endif
