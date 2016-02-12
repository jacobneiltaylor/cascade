#ifdef __TEST__

#define TEST_THREADCOUNT 7

#include "testWorker.h"

using namespace std;
using namespace taylornet::cascade;

int main()
{
	cout << "=================================\n"
		 << " |                             | \n"
		 << " | The LibCascade Test Program | \n"
		 << " |                             | \n"
		 << " |  Copyright Taylor Networks  | \n"
		 << " |        2015 - 2016          | \n"
		 << " |                             | \n"
		 << "=================================\n\n\n";

	cout << "Hardware threads detected: " << taylornet::cascade::threadManager::hardwareThreads() << "\n\n";

	cout << "Initialising threadManager with " << TEST_THREADCOUNT << " threads...\n\n";

	threadManager* tm = threadManager::getInstance(TEST_THREADCOUNT, true);

	cout << "Thread manager has " << tm->getHostCount() << " thread hosts\n\n";

	cout << "Loading workers into thread queue...\n\n";using namespace taylornet::cascade;

	for(unsigned int i = 0; i < tm->getHostCount(); i++)
	{
		//cout >>
		string str = SSTR("This is thread number " << i+1 << "\n");

		testWorker* newWorker = new testWorker(str);
		tm->addWorker(newWorker);
	}

	cout << "Thread queue length is " << tm->getQueueLength() << ".\n\n";

	cout << "Starting threads...\n\n";

	for(unsigned int j = 0; tm->getQueueLength() > 0; j++)
	{
		tm->dispatchQueue();
	}

	cout << "Waiting for threads...\n\n";

	tm->waitForWorkers();

	return false;
}
#endif
