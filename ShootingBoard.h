//
// Created by adam on 18.05.17.
//

#ifndef APPROXMONTECARLO_SCORE_H
#define APPROXMONTECARLO_SCORE_H

class ShootingBoard {
public:
	void incrementTotalSum();

	void incrementHitSum();

	long long getHitSum();

	long long getTotalSum();

private:
	long long totalSum = 0;;
	long long hitSum = 0;;
};

#endif //APPROXMONTECARLO_SCORE_H
