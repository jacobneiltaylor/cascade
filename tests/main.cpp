#ifdef __TEST__

#include "testWorker.h"
#include "queueWorker.h"

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

	cout << "=== Library Information ===\n";
	cout << "Test program compiled against: " << LIBCASCADE_VERSION << "\n";
	cout << "Installed library version: " << taylornet::cascade::threadManager::libCascadeVersion() << "\n\n";

	int hardwareThreads = taylornet::cascade::threadManager::hardwareThreads();

	cout << "Hardware threads detected: " << hardwareThreads << "\n\n";

	cout << "Initialising threadManager with " << hardwareThreads-1 << " threads...\n\n";

	threadManager* tm = threadManager::getInstance(hardwareThreads-1, false);

	cout << "Thread manager has " << tm->getHostCount() << " thread hosts\n\n";

	cout << "Registering mutex...\n\n";

	tm->registerNewMutex("output");

	cout << "Reserving queueWorker threadHost...\n\n";

	threadHost* reserved_thread = tm->reserveThread("queuehost");

	cout << "Assigning queueWorker to reserved threadHost...\n\n";

	queueWorker* dispatcher = new queueWorker();
	reserved_thread->assignWorker(dispatcher);

	cout << "Loading workers into thread queue...\n\n";

	for(unsigned int i = 0; i < tm->freeThreads(); i++)
	{
		string str = SSTR("This is thread number " << i+1);

		testWorker* newWorker = new testWorker(str);
		tm->addWorker(newWorker);
	}

	cout << "Thread queue length is " << tm->getQueueLength() << ".\n\n";

	cout << "Starting threads...\n\n";

	reserved_thread->startThread();

	cout << "Waiting for threads...\n\n";

	tm->waitForWorkers(true);

	cout << "Stopping queueWorker...\n\n";

	dispatcher->stop();

	system("pause");

	return false;
}
#endif
