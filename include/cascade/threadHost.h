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
				bool reserved;

				std::thread* thread;
				worker* assignedWorker;
				threadManager* manager;
				
				void assignManager(threadManager* manager);
				void assignWorker_P(worker* worker);

				void reserve();
				void release();

			public:

				LIBCASCADE_API threadHost();
				LIBCASCADE_API ~threadHost();

				LIBCASCADE_API void startThread();
				LIBCASCADE_API void syncThread(bool wait = true);
				LIBCASCADE_API bool threadRunning();
				LIBCASCADE_API std::thread::id getThreadId();

				LIBCASCADE_API void assignWorker(worker* worker);
				LIBCASCADE_API void waitForWorker();
				LIBCASCADE_API bool workerDone();

				LIBCASCADE_API void lock(std::string name);
				LIBCASCADE_API void unlock(std::string name);

				LIBCASCADE_API bool isReserved();

			friend class threadManager;
		};
	}
}

#endif
