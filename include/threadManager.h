/*

	threadManager.h

	Part of Cascade: A C++ Thread Management Library based on std::thread

	Copyright Taylor Networks 2015. Licensed under the GNU GPL.

*/



#ifndef LIBCASCADE_THREADMANAGER
#define LIBCASCADE_THREADMANAGER

namespace taylornet
{
	namespace cascade
	{

		class threadManager
		{
			private:

				static threadManager* tmInstance;
				static bool initialised;

				bool oversub;
				unsigned int hardThreadLimit;
				unsigned int threadLimit;

				worker* lastWorker;
				threadHost* lastHost;

				std::queue<worker*> workerQueue;
				std::vector<threadHost*> threadHosts;
				// Future feature: named hosts - std::map<std::string, threadHost*> namedHosts;

				void generateThreadHosts();
				unsigned int getFreeThreadHost();
				
				threadManager();
				threadManager(unsigned int softThreadLimit);
				threadManager(unsigned int softThreadLimit, bool oversub);

			public:

				static threadManager* getInstance();
				static threadManager* getInstance(unsigned int softThreadLimit);
				static threadManager* getInstance(unsigned int softThreadLimit, bool oversub);

				static bool instanceAvailable();
				static void destroyInstance();

				unsigned int getThreadLimit();
				unsigned int getHostCount();
				static unsigned int hardwareThreads();

				bool oversubEnabled();

				void addWorker(worker* newWorker);
				bool dispatchQueue(bool autostart = true);
				worker* getDispatchedWorker();
				threadHost* getDispatchedHost();
				unsigned int getQueueLength();

				void waitForWorkers();

				unsigned int freeThreads();
				unsigned int idleThreads();
				unsigned int busyThreads();
		};
	}
}

#endif
