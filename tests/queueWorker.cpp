#ifdef __TEST__

#include "queueWorker.h"
#include <iostream>

queueWorker::queueWorker()
{
	this->done = false;
	this->tm = threadManager::getInstance();
}

queueWorker::~queueWorker()
{
	this->done = true;
	this->tm = nullptr;
}

void queueWorker::work()
{
	while (!done)
	{
		this->tm->dispatchQueue();
	}
}

void queueWorker::stop()
{
	std::cout << "Queue Dispatcher Service stopped.\n\n";
	this->done = true;
}

#endif