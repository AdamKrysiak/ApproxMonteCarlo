//
// Created by adam on 18.05.17.
//
#include <iostream>
#include <fstream>
#include <queue>
#include <thread>
#include <cmath>
#include "ShootingBoard.h"

using namespace std;

void readRandom();

void addToSum(shared_ptr<ShootingBoard> scorePtr);

void printPi(shared_ptr<ShootingBoard> scorePtr);

long long int getAndRemoveLast(queue<long long int> &collection);

queue<long long> RANDOM_QUEUE;
bool STOP_CONDITION = false;
long RADIUS = 10000;

int main() {
	auto score = make_shared<ShootingBoard>();
	cout << rand() << endl;
	readRandom();
	addToSum(score);
	printPi(score);

}

void printPi(shared_ptr<ShootingBoard> scorePtr) {
	if (scorePtr->getTotalSum() != 0) {
		double sumsRatio = (double) scorePtr->getHitSum() / (double) scorePtr->getTotalSum();
		double PI = 4.0f * sumsRatio;
		printf("%.10f", PI);
	}
}

void addToSum(shared_ptr<ShootingBoard> scorePtr) {
	for (int i = 0; i < 9183; i++) {
		if (RANDOM_QUEUE.size() >= 2) {
			long long x = getAndRemoveLast(RANDOM_QUEUE);
			long long y = getAndRemoveLast(RANDOM_QUEUE);
			long long z = sqrt(pow(x, 2) + pow(y, 2));
			scorePtr->incrementTotalSum();
			if (z <= RADIUS) {
				scorePtr->incrementHitSum();
			}
		}
	}
}

long long int getAndRemoveLast(queue<long long int> &collection) {
	long long temp = collection.front();
	collection.pop();
	return temp;
}

void readRandom() {
	unsigned long long int random_value = 0; //Declare value to store data into
	size_t size = sizeof(random_value); //Declare size of data
	ifstream urandom("/dev/urandom", ios_base::in | ios_base::binary); //Open stream
	if (urandom) //Check if stream is open
	{
		for (int i = 0; i < 100000; i++) {
			urandom.read(reinterpret_cast<char *>(&random_value), size); //Read from urandom
			RANDOM_QUEUE.push(random_value % (2 * RADIUS) - RADIUS);
		}
		urandom.close(); //close stream
	} else //Open failed
	{
		cerr << "Failed to open /dev/urandom" << endl;
	}
}

