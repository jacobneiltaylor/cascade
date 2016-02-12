/*

	worker.h

	Part of Cascade: A C++ Thread Management Library based on std::thread

	Copyright Taylor Networks 2015. Licensed under the GNU GPL.

*/

#ifndef LIBCASCADE_WORKER
#define LIBCASCADE_WORKER

namespace taylornet
{
	namespace cascade
	{
		class worker
		{
			typedef std::function<void(worker*)> workerCallback;

			private:

				bool assigned;
				bool done;
				bool willAutoclean;
				bool callbackSet;
				bool selfDestruct;

				threadHost* host;
				workerCallback* callback;

				void setHost(threadHost* host);
				void enableSelfDestruct();

			protected:

				virtual void work()=0;

			public:

				void threadMain();

				worker();
				virtual ~worker();
				
				void setCallback(workerCallback* callback);
				void runCallback();

				void enableAutoclean();
				void disableAutoclean();
				void runAutoclean();
				bool autocleanEnabled();

				void resetWork();
				bool workDone();

			friend class threadHost;
		};
	}
}

#endif
