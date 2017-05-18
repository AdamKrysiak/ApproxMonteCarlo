//
// Created by adam on 18.05.17.
//
#include <iostream>
#include <fstream>
#include <queue>
#include <thread>
#include "Score.h"

void readRandom();

using namespace std;

queue<long long> RANDOM_QUEUE;

int main() {

	readRandom();
	srand(time(NULL));
	cout << Score::getSumCircle1();
	cout << rand() << endl;
	auto x = thread(readRandom);
	x.join();
}

void readRandom() {
	unsigned long long int random_value = 0; //Declare value to store data into
	size_t size = sizeof(random_value); //Declare size of data
	ifstream urandom("/dev/urandom", ios_base::in | ios_base::binary); //Open stream
	if (urandom) //Check if stream is open
	{
		while (true) {
			urandom.read(reinterpret_cast<char *>(&random_value), size); //Read from urandom
			if (urandom) //Check if stream is ok, read succeeded
			{
				RANDOM_QUEUE.push(random_value);
			} else //Read failed
			{
				cerr << "Failed to read from /dev/urandom" << endl;
			}
		}
		urandom.close(); //close stream
	} else //Open failed
	{
		cerr << "Failed to open /dev/urandom" << endl;
	}
}

