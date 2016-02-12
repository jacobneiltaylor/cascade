#ifdef __TEST__

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

	int hardwareThreads = taylornet::cascade::threadManager::hardwareThreads();

	cout << "Hardware threads detected: " << hardwareThreads << "\n\n";

	cout << "Initialising threadManager with " << hardwareThreads-1 << " threads...\n\n";

	threadManager* tm = threadManager::getInstance(hardwareThreads-1, false);

	cout << "Thread manager has " << tm->getHostCount() << " thread hosts\n\n";

	cout << "Loading workers into thread queue...\n\n";

	for(unsigned int i = 0; i < tm->getHostCount(); i++)
	{
		//cout >>
		string str = SSTR("This is thread number " << i+1);

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

	system("pause");

	return false;
}
#endif
