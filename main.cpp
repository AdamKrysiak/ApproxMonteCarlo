//
// Created by adam on 18.05.17.
//
#include <iostream>
#include <fstream>
#include <queue>
#include <thread>
#include <cmath>
#include <condition_variable>
#include <algorithm>
#include "ShootingBoard.h"

void fillQueueWithRandoms();
void addOneRandom(unsigned long long int &random_value, size_t size, std::ifstream &urandom);
void countBoardHit(std::shared_ptr<ShootingBoard> scorePtr);
void countTotalHits(std::shared_ptr<ShootingBoard> totalScore, std::vector<std::shared_ptr<ShootingBoard>> scores);
void printPi(std::shared_ptr<ShootingBoard> scorePtr);
long long int getAndRemoveLast(std::queue<long long int> &collection);

std::queue<long long> RANDOM_QUEUE;
std::mutex RANDOM_QUEUE_MUTEX;
std::condition_variable RANDOM_ADDED_VARIABLE;

static const int THREAD_COUNT = 60;
bool STOP_CONDITION = false;
long RADIUS = 1000000000;

int main() {
	std::vector<std::shared_ptr<ShootingBoard>> scores;
	std::vector<std::thread> threads;

	auto randomFiller = std::thread(fillQueueWithRandoms);

	for (int i = 0; i < THREAD_COUNT; i++) {
		auto board = std::make_shared<ShootingBoard>();
		scores.push_back(board);
		threads.push_back(std::thread(countBoardHit, board));
	}
	auto totalScore = std::make_shared<ShootingBoard>();

	auto totalCounter = std::thread(countTotalHits, totalScore, scores);
	auto printer = std::thread(printPi, totalScore);

	for_each(threads.begin(), threads.end(), [](std::thread &th) { th.join(); });
	randomFiller.join();
	totalCounter.join();
	printer.join();
}

void fillQueueWithRandoms() {
	unsigned long long int random_value = 0;
	size_t size = sizeof(random_value);
	std::ifstream urandom("/dev/urandom", std::ios_base::in | std::ios_base::binary);
	if (urandom)
	{
		while (!STOP_CONDITION) {
			{
				std::lock_guard<std::mutex> lk(RANDOM_QUEUE_MUTEX);
				addOneRandom(random_value, size, urandom);
				addOneRandom(random_value, size, urandom);
			}
			RANDOM_ADDED_VARIABLE.notify_one();
		}
		urandom.close();
	} else
	{
		std::cerr << "Failed to open /dev/urandom" << std::endl;
	}
}

void addOneRandom(unsigned long long int &random_value, size_t size, std::ifstream &urandom) {
	urandom.read(reinterpret_cast<char *>(&random_value), size);
	RANDOM_QUEUE.push(random_value % (2 * RADIUS) - RADIUS);
}

void countBoardHit(std::shared_ptr<ShootingBoard> scorePtr) {
	while (!STOP_CONDITION) {
		std::unique_lock<std::mutex> lock(RANDOM_QUEUE_MUTEX);
		RANDOM_ADDED_VARIABLE.wait(lock);
		long long x = getAndRemoveLast(RANDOM_QUEUE);
		long long y = getAndRemoveLast(RANDOM_QUEUE);
		long long z = sqrt(pow(x, 2) + pow(y, 2));
		scorePtr->incrementTotalSum();
		if (z <= RADIUS) {
			scorePtr->incrementHitSum();
		}
	}
}

long long int getAndRemoveLast(std::queue<long long int> &collection) {
	long long temp = collection.front();
	collection.pop();
	return temp;
}

void countTotalHits(std::shared_ptr<ShootingBoard> totalScore, std::vector<std::shared_ptr<ShootingBoard>> scores) {
	while (!STOP_CONDITION) {
		long long hitSum = 0;
		long long totalSum = 0;

		for_each(scores.begin(), scores.end(), [&hitSum, &totalSum](std::shared_ptr<ShootingBoard> board) {
			hitSum += board->getHitSum();
			totalSum += board->getTotalSum();
		});

		totalScore->setHitSum(hitSum);
		totalScore->setTotalSum(totalSum);
	}
}

void printPi(std::shared_ptr<ShootingBoard> scorePtr) {
	while (!STOP_CONDITION) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
		if (scorePtr->getTotalSum() != 0) {
			double sumsRatio = (double) scorePtr->getHitSum() / (double) scorePtr->getTotalSum();
			double PI = 4.0f * sumsRatio;
			printf("%lli %.15f\n", scorePtr->getTotalSum(), PI);
		}
	}
}

