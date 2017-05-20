//
// Created by adam on 18.05.17.
//

#include "ShootingBoard.h"

void ShootingBoard::incrementTotalSum() {
	totalSum++;
}

void ShootingBoard::incrementHitSum() {
	hitSum++;
}

long long ShootingBoard::getTotalSum() {
	return totalSum;
}

long long ShootingBoard::getHitSum() {
	return hitSum;
}