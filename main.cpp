//
// Created by adam on 18.05.17.
//
#include <iostream>
#include <fstream>
#include <queue>
#include <thread>
#include <cmath>
#include <condition_variable>
#include "ShootingBoard.h"

using namespace std;

void readRandom();

void countHits(shared_ptr<ShootingBoard> scorePtr);
void printPi(shared_ptr<ShootingBoard> scorePtr);
long long int getAndRemoveLast(queue<long long int> &collection);
void addOneRandom(unsigned long long int &random_value, size_t size, ifstream &urandom);

void
countTotalHits(shared_ptr<ShootingBoard> scoreOne, shared_ptr<ShootingBoard> scoreTwo, shared_ptr<ShootingBoard> ptr);

queue<long long> RANDOM_QUEUE;
mutex randomQueueMutex;
condition_variable conditionVariable;

bool STOP_CONDITION = false;
long RADIUS = 1000000000;

int main() {
	auto scoreOne = make_shared<ShootingBoard>();
	auto scoreTwo = make_shared<ShootingBoard>();
	auto totalScore = make_shared<ShootingBoard>();

	auto randomFiller = thread(readRandom);

	auto counterOne = thread(countHits, scoreOne);
	auto counterTwo = thread(countHits, scoreTwo);

	auto printer = thread(printPi, totalScore);
	countTotalHits(totalScore, scoreOne, scoreTwo);
	randomFiller.join();
	counterOne.join();
	counterTwo.join();
	printer.join();

}

void printPi(shared_ptr<ShootingBoard> scorePtr) {
	while (!STOP_CONDITION) {
		if (scorePtr->getTotalSum() != 0) {
			double sumsRatio = (double) scorePtr->getHitSum() / (double) scorePtr->getTotalSum();
			double PI = 4.0f * sumsRatio;
			printf("%.15f\n", PI);
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}
}

void countHits(shared_ptr<ShootingBoard> scorePtr) {
	while (!STOP_CONDITION) {
		unique_lock<mutex> lock(randomQueueMutex);
		conditionVariable.wait(lock);

		long long x = getAndRemoveLast(RANDOM_QUEUE);
		long long y = getAndRemoveLast(RANDOM_QUEUE);
		long long z = sqrt(pow(x, 2) + pow(y, 2));
		scorePtr->incrementTotalSum();
		if (z <= RADIUS) {
			scorePtr->incrementHitSum();
		}
	}
}

void countTotalHits(shared_ptr<ShootingBoard> totalScore ,shared_ptr<ShootingBoard> scoreOne, shared_ptr<ShootingBoard> scoreTwo) {
	while (!STOP_CONDITION) {
		totalScore->setHitSum(scoreOne->getHitSum() + scoreTwo->getHitSum());
		totalScore->setTotalSum(scoreOne->getTotalSum() + scoreTwo->getTotalSum());
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
		while (!STOP_CONDITION) {
			{
				std::lock_guard<std::mutex> lk(mutex);
				addOneRandom(random_value, size, urandom);
				addOneRandom(random_value, size, urandom);
			}
			conditionVariable.notify_one();
		}
		urandom.close(); //close stream
	} else //Open failed
	{
		cerr << "Failed to open /dev/urandom" << endl;
	}
}

void addOneRandom(unsigned long long int &random_value, size_t size, ifstream &urandom) {
	urandom.read(reinterpret_cast<char *>(&random_value), size);
	RANDOM_QUEUE.push(random_value % (2 * RADIUS) - RADIUS);
}

