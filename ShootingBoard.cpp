//
// Created by adam on 18.05.17.
//

#include "ShootingBoard.h"

void ShootingBoard::incrementTotalSum() {
	std::lock_guard<std::mutex> guard(boardMutex);
	totalSum++;
}

void ShootingBoard::incrementHitSum() {
	std::lock_guard<std::mutex> guard(boardMutex);
	hitSum++;
}

long long ShootingBoard::getTotalSum() {
	std::lock_guard<std::mutex> guard(boardMutex);
	return totalSum;
}

long long ShootingBoard::getHitSum() {
	std::lock_guard<std::mutex> guard(boardMutex);
	return hitSum;
}

void ShootingBoard::setTotalSum(long long newTotalSum) {
	std::lock_guard<std::mutex> guard(boardMutex);
	totalSum=newTotalSum;
}

void ShootingBoard::setHitSum(long long newHitSum) {
	std::lock_guard<std::mutex> guard(boardMutex);
	hitSum=newHitSum;
}
