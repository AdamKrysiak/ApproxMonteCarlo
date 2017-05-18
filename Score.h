//
// Created by adam on 18.05.17.
//

#ifndef APPROXMONTECARLO_SCORE_H
#define APPROXMONTECARLO_SCORE_H

class Score {
public:
	static void incrementSumRectangle1();
	static void incrementSumCircle1();
	static void incrementSumRectangle2();
	static void incrementSumCircle2();
	static long long getSumCircle1();
	static long long getSumCircle2();
	static long long getSumRectangle2();
	static long long getRectangle1();

private:
	static long long SUM_RECTANGLE_1;
	static long long SUM_CIRCLE_1;
	static long long SUM_RECTANGLE_2;
	static long long SUM_CIRCLE_2;
};
#endif //APPROXMONTECARLO_SCORE_H
