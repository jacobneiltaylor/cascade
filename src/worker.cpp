/*

	worker.cpp

	Part of Cascade: A C++ Thread Management Library based on std::thread

	Copyright Taylor Networks 2015. Licensed under the GNU GPL.

*/

#include "cascade.h"

namespace taylornet
{
	namespace cascade
	{
		void worker::lock(std::string name)
		{
			this->host->lock(name);
		}

		void worker::unlock(std::string name)
		{
			this->host->unlock(name);
		}

		worker::worker()
		{
			this->host = NULL;
			this->callback = NULL;
			this->selfDestruct = false;
			this->callbackSet = false;
			this->willAutoclean = false;
			this->assigned = false;
			this->done = false;
		}

		worker::~worker()
		{
			this->host = NULL;

			if(!this->callback)
			{
				delete this->callback;
			}
		}

		void worker::threadMain()
		{
			if(!this->done)
			{
				this->work();
				this->done = true;

				if(this->selfDestruct)
				{
					this->runCallback();
					this->runAutoclean();
				}
			}
		}

		void worker::setHost(threadHost* host)
		{
			this->assigned = true;
			this->host = host;
		}

		void worker::enableSelfDestruct()
		{
			this->enableAutoclean();
			this->selfDestruct = true;
		}

		void worker::setCallback(workerCallback* callback)
		{
			this->callbackSet = true;
			this->callback = callback;
		}

		void worker::runCallback()
		{
			if(this->callbackSet)
			{
				workerCallback localCallback = *callback;
				localCallback(this);
			}
		}

		void worker::enableAutoclean()
		{
			this->willAutoclean = true;
		}

		void worker::disableAutoclean()
		{
			this->willAutoclean = false;
		}

		void worker::runAutoclean()
		{
			if(this->willAutoclean)
			{
				delete this;
			}
		}

		bool worker::autocleanEnabled()
		{
			return this->willAutoclean;
		}

		void worker::resetWork()
		{
			this->done = false;
		}

		bool worker::workDone()
		{
			return this->done;
		}
	}
}
