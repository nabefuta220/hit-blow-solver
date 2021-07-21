#include "progress.hpp"

#include <iostream>
progressBar::progressBar(int target, int segment) {
	this->lastShow = -1;
	this->target   = target;
	this->segment  = segment;
	this->cnt      = 0;
}

void progressBar::increase(int num) {
	this->cnt += num;
	if (this->cnt / (this->target / this->segment) !=
	    this->lastShow / (this->target / this->segment)) {
		this->show();
		this->lastShow = this->cnt;
	}
}

void progressBar::increase() { this->increase(1); }

void progressBar::show() {
	if (this->target == this->cnt) {
		std::cout << "Done!" << std::endl;
	} else {
		std::cout << this->cnt << "/" << this->target << std::endl;
	}
}
