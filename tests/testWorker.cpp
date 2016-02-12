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
	std::cout << text;
}

#endif
