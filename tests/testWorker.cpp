#ifdef __TEST__

#include "testWorker.h"

testWorker::testWorker(std::string text)
{
	this->text = text;
}

testWorker::~testWorker()
{
	delete &text;
}

void testWorker::work()
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> gen(5, 15);

	int x = gen(rng);

	std::this_thread::sleep_for(std::chrono::milliseconds(x * 1000));

	this->lock("output");
	std::cout << text << "\nRandom number: " << x << "\n\n";
	this->unlock("output");
}

#endif
