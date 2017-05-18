//
// Created by adam on 18.05.17.
//

#include "Score.h"

long long Score::SUM_RECTANGLE_1 = 0;
long long Score::SUM_CIRCLE_1 = 0;
long long Score::SUM_RECTANGLE_2 = 0;
long long Score::SUM_CIRCLE_2 = 0;

void Score::incrementSumRectangle1() {
	Score::SUM_RECTANGLE_1++;
}

void Score::incrementSumCircle1() {
	Score::SUM_CIRCLE_1++;
}

void Score::incrementSumRectangle2() {
	Score::SUM_RECTANGLE_2++;
}

void Score::incrementSumCircle2() {
	Score::SUM_CIRCLE_2++;
}

long long Score::getRectangle1() {
	return Score::SUM_RECTANGLE_1;
}

long long Score::getSumRectangle2() {
	return Score::SUM_RECTANGLE_2;
}

long long Score::getSumCircle1() {
	return Score::SUM_CIRCLE_1;
}

long long Score::getSumCircle2() {
	return SUM_CIRCLE_2;
}
