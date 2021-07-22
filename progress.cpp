#include "progress.hpp"

#include <iostream>
progressBar::progressBar(int target, int segment)
{

	this->target = target;
	this->segment = segment;
	this->cnt = 0;
}

void progressBar::increase(int num)
{
	this->cnt += num;
	this->show();
}

void progressBar::increase() { this->increase(1); }

void progressBar::show()
{
	if (this->target == this->cnt)
	{
		std::cout << "\033[2K\rDone!" << std::endl;
	}
	else
	{
		std::cout << "\033[2K\r" << this->cnt << "/" << this->target;
		fflush(stdout);
	}
}
