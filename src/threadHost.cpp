/*

	threadHost.cpp

	Part of Cascade: A C++ Thread Management Library based on std::thread

	Copyright Taylor Networks 2015. Licensed under the GNU GPL.

*/


#include "cascade.h"

namespace taylornet
{
	namespace cascade
	{
		threadHost::threadHost()
		{
			this->assigned = false;
			this->managed = false;
			this->reserved = false;

			this->thread = NULL;
			this->assignedWorker = NULL;
			this->manager = NULL;
		}

		threadHost::~threadHost()
		{
			if(this->thread)
			{
				if(!this->thread->joinable())
				{
					delete this->thread;
				}
				else
				{
					this->thread->detach();
					delete this->thread;
				}
			}

			if(!this->assigned)
			{
				delete this->assignedWorker;
			}
		}

		void threadHost::assignManager(threadManager* manager)
		{
			this->manager = manager;
		}

		void threadHost::reserve()
		{
			if (!reserved)
			{
				this->assignedWorker = nullptr;
				this->reserved = true;
			}
			else
			{
				throw new std::runtime_error("Cannot reserve a reserved thread");
			}
		}

		void threadHost::release()
		{
			if (reserved)
			{
				this->assignedWorker = nullptr;
				this->reserved = false;
			}
			else
			{
				throw new std::runtime_error("Cannot released an unreserved thread");
			}
		}

		void threadHost::startThread()
		{
			if(assigned)
			{
				this->thread = new std::thread(&worker::threadMain, this->assignedWorker);
			}
		}

		void threadHost::syncThread(bool wait)
		{
			if(this->threadRunning())
			{
				if(!this->workerDone() && wait)
				{
					this->waitForWorker();
				}

				if(this->workerDone())
				{
					this->thread->join();

					this->assignedWorker->runCallback();
					this->assignedWorker->runAutoclean();
				}
				else
				{
					this->thread->detach();
				}

				delete this->thread;
			}
		}

		bool threadHost::threadRunning()
		{
			bool retval = false;

			if (this->thread != nullptr)
			{
				retval = this->thread->joinable();
			}

			return retval;
		}

		std::thread::id threadHost::getThreadId()
		{
			return this->thread->get_id();
		}

		void threadHost::assignWorker(worker* worker)
		{
			if (this->reserved)
			{
				this->assignWorker_P(worker);
			}
			else
			{
				throw new std::runtime_error("Unreserved threads cannot be assigned workers directly");
			}
		}

		void threadHost::assignWorker_P(worker* worker)
		{
			this->assigned = true;
			this->assignedWorker = worker;
			this->assignedWorker->setHost(this);
		}

		void threadHost::waitForWorker()
		{
			bool ready = false;

			while(!ready)
			{
				if(this->workerDone())
				{
					ready = true;
				}
			}
		}

		bool threadHost::workerDone()
		{
			bool retval = true;

			if (this->assignedWorker != nullptr)
			{
				retval = this->assignedWorker->workDone();
			}

			return retval;
		}

		void threadHost::lock(std::string name)
		{
			this->manager->lock(name);
		}

		void threadHost::unlock(std::string name)
		{
			this->manager->unlock(name);
		}

		bool threadHost::isReserved()
		{
			return this->reserved;
		}
	}
}
