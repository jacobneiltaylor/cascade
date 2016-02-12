/*

	threadHost.h

	Part of Cascade: A C++ Thread Management Library based on std::thread

	Copyright Taylor Networks 2015. Licensed under the GNU GPL.

*/

#ifndef LIBCASCADE_CHILDTHREAD
#define LIBCASCADE_CHILDTHREAD

namespace taylornet
{
	namespace cascade
	{
		class threadHost
		{
			private:

				bool assigned;
				bool managed;
				//Future feature: reserved thread hosts - bool reserved;

				std::thread* thread;
				worker* assignedWorker;
				threadManager* manager;
				
				void assignManager(threadManager* manager);

			public:

				threadHost();
				~threadHost();

				void startThread();
				void syncThread(bool wait = true);
				bool threadRunning();
				std::thread::id getThreadId();

				void assignWorker(worker* worker);
				void waitForWorker();
				bool workerDone();


			friend class threadManager;
		};
	}
}

#endif
