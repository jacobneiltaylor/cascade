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
				bool wait_reservation;
				unsigned int hardThreadLimit;
				unsigned int threadLimit;

				worker* lastWorker;
				threadHost* lastHost;

				std::queue<worker*> workerQueue;
				std::vector<threadHost*> threadHosts;
				std::map<std::string, std::mutex*> registeredMutexes;
				std::map<std::string, threadHost*> reservedThreads;

				void generateThreadHosts();
				unsigned int getFreeThreadHost();
				
				threadManager();
				threadManager(unsigned int softThreadLimit);
				threadManager(unsigned int softThreadLimit, bool oversub);

			public:

				static LIBCASCADE_API const char* libCascadeVersion();

				static LIBCASCADE_API threadManager* getInstance();
				static LIBCASCADE_API threadManager* getInstance(unsigned int softThreadLimit);
				static LIBCASCADE_API threadManager* getInstance(unsigned int softThreadLimit, bool oversub);

				static LIBCASCADE_API bool instanceAvailable();
				static LIBCASCADE_API void destroyInstance();

				static LIBCASCADE_API unsigned int hardwareThreads();

				LIBCASCADE_API void registerNewMutex(std::string name);
				LIBCASCADE_API void lock(std::string name);
				LIBCASCADE_API void unlock(std::string name);

				LIBCASCADE_API unsigned int getThreadLimit();
				LIBCASCADE_API unsigned int getHostCount();

				LIBCASCADE_API bool oversubEnabled();

				LIBCASCADE_API void addWorker(worker* newWorker);
				LIBCASCADE_API bool dispatchQueue(bool autostart = true);
				LIBCASCADE_API worker* getDispatchedWorker();
				LIBCASCADE_API threadHost* getDispatchedHost();
				LIBCASCADE_API unsigned int getQueueLength();

				LIBCASCADE_API void waitForWorkers(bool unreserved_only = false);

				LIBCASCADE_API unsigned int freeThreads();
				LIBCASCADE_API unsigned int idleThreads();
				LIBCASCADE_API unsigned int busyThreads();

				LIBCASCADE_API threadHost* reserveThread(std::string name);
				LIBCASCADE_API void releaseThread(std::string name);
		};
	}
}

#endif
