//
// Created by adam on 18.05.17.
//

#ifndef APPROXMONTECARLO_SCORE_H
#define APPROXMONTECARLO_SCORE_H

#include <mutex>

class ShootingBoard {
public:
	void incrementTotalSum();

	void incrementHitSum();

	long long getHitSum();

	long long getTotalSum();

private:
	long long totalSum = 0;
	long long hitSum = 0;
	std::mutex boardMutex;
};

#endif //APPROXMONTECARLO_SCORE_H
