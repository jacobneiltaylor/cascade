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

				virtual LIBCASCADE_API void work()=0;

			public:

				LIBCASCADE_API void threadMain();

				LIBCASCADE_API worker();
				LIBCASCADE_API virtual ~worker();
				
				LIBCASCADE_API void setCallback(workerCallback* callback);
				LIBCASCADE_API void runCallback();

				LIBCASCADE_API void enableAutoclean();
				LIBCASCADE_API void disableAutoclean();
				LIBCASCADE_API void runAutoclean();
				LIBCASCADE_API bool autocleanEnabled();

				LIBCASCADE_API void resetWork();
				LIBCASCADE_API bool workDone();

			friend class threadHost;
		};
	}
}

#endif
