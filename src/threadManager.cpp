/*

	threadManager.cpp

	Part of Cascade: A C++ Thread Management Library based on std::thread

	Copyright Taylor Networks 2015. Licensed under the GNU GPL.

*/

#include "cascade.h"

namespace taylornet
{
	namespace cascade
	{
		threadManager* threadManager::tmInstance = nullptr;
		bool threadManager::initialised = false;

		const char* threadManager::libCascadeVersion()
		{
			return LIBCASCADE_VERSION;
		}

		void threadManager::generateThreadHosts()
		{
			for(unsigned int i = 0; i < this->threadLimit; i++)
			{
				threadHost* th = new threadHost();

				th->assignManager(this);

				this->threadHosts.push_back(th);
			}
		}

		unsigned int threadManager::getFreeThreadHost()
		{
			unsigned int freeIndex = 0;
			unsigned int hostCount = this->getHostCount();

			for(unsigned int i = 0; i < hostCount; i++)
			{
				if(this->threadHosts[i]->workerDone() && !this->threadHosts[i]->isReserved())
				{
					freeIndex = i;
					break;
				}
			}

			return freeIndex;
		}

		threadManager::threadManager()
		{
			this->lastWorker = nullptr;
			this->lastHost = nullptr;
			this->oversub = false;
			this->hardThreadLimit = hardwareThreads();
			this->threadLimit = this->hardThreadLimit;
			this->wait_reservation = false;
			this->generateThreadHosts();
		}

		threadManager::threadManager(unsigned int softThreadLimit)
		{
			this->lastWorker = nullptr;
			this->lastHost = nullptr;
			this->oversub = false;
			this->hardThreadLimit = hardwareThreads();
			this->threadLimit = this->hardThreadLimit;

			if(softThreadLimit > 0 && softThreadLimit < this->threadLimit)
			{
				this->threadLimit = softThreadLimit;
			}

			this->generateThreadHosts();
		}

		threadManager::threadManager(unsigned int softThreadLimit, bool oversub)
		{
			this->lastWorker = nullptr;
			this->lastHost = nullptr;
			this->oversub = oversub;
			this->hardThreadLimit = hardwareThreads();
			this->threadLimit = this->hardThreadLimit;

			if(softThreadLimit > 0 && (oversub || softThreadLimit < this->threadLimit))
			{
				this->threadLimit = softThreadLimit;
			}

			this->generateThreadHosts();
		}

		threadManager* threadManager::getInstance()
		{
			if(!initialised)
			{
				tmInstance = new threadManager();
				initialised = true;
			}

			return tmInstance;
		}

		threadManager* threadManager::getInstance(unsigned int softThreadLimit)
		{
			if(!initialised)
			{
				tmInstance = new threadManager(softThreadLimit);
				initialised = true;
			}

			return tmInstance;
		}

		threadManager* threadManager::getInstance(unsigned int softThreadLimit, bool oversub)
		{
			if(!initialised)
			{
				tmInstance = new threadManager(softThreadLimit, oversub);
				initialised = true;
			}

			return tmInstance;
		}

		bool threadManager::instanceAvailable()
		{
			return initialised;
		}

		void threadManager::destroyInstance()
		{
			if(initialised)
			{
				delete tmInstance;
				initialised = false;
			}
		}

		unsigned int threadManager::hardwareThreads()
		{
			return std::thread::hardware_concurrency();
		}

		void threadManager::registerNewMutex(std::string name)
		{
			this->registeredMutexes[name] = new std::mutex();
		}

		void threadManager::lock(std::string name)
		{
			this->registeredMutexes[name]->lock();
		}

		void threadManager::unlock(std::string name)
		{
			this->registeredMutexes[name]->unlock();
		}

		unsigned int threadManager::getThreadLimit()
		{
			return this->threadLimit;
		}

		unsigned int threadManager::getHostCount()
		{
			return this->threadHosts.size();
		}

		bool threadManager::oversubEnabled()
		{
			return this->oversub;
		}

		void threadManager::addWorker(worker* newWorker)
		{
			this->workerQueue.push(newWorker);
		}

		bool threadManager::dispatchQueue(bool autostart)
		{
			bool dispatchSuccess = false;

			if(!this->workerQueue.empty())
			{
				if(this->freeThreads() > 0 && !wait_reservation)
				{
					unsigned int freeHostIndex = getFreeThreadHost();
					threadHost* freeHost = this->threadHosts[freeHostIndex];
					worker* nextWorker = this->workerQueue.front();

					this->workerQueue.pop();

					freeHost->assignWorker_P(nextWorker);

					if(autostart)
					{
						freeHost->startThread();
					}

					dispatchSuccess = true;
					this->lastWorker = nextWorker;
					this->lastHost = freeHost;
				}
			}

			return dispatchSuccess;
		}

		worker* threadManager::getDispatchedWorker()
		{
			return this->lastWorker;
		}

		threadHost* threadManager::getDispatchedHost()
		{
			return this->lastHost;
		}

		unsigned int threadManager::getQueueLength()
		{
			return this->workerQueue.size();
		}

		void threadManager::waitForWorkers(bool unreserved_only)
		{
			for(int i = 0; i < this->getHostCount(); i++)
			{
				if(!(unreserved_only && this->threadHosts[i]->isReserved()) && !this->threadHosts[i]->workerDone())
				{
					this->threadHosts[i]->waitForWorker();
				}
			}
		}

		unsigned int threadManager::freeThreads()
		{
			unsigned int hostCount = this->getHostCount();
			unsigned int freeCount = 0;

			for (unsigned int i = 0; i < hostCount; i++)
			{
				if (!this->threadHosts[i]->threadRunning() && !this->threadHosts[i]->isReserved())
				{
					freeCount++;
				}
			}

			return freeCount;
		}

		unsigned int threadManager::idleThreads()
		{
			unsigned int hostCount = this->getHostCount();
			unsigned int idleCount = 0;

			for(unsigned int i = 0; i < hostCount; i++)
			{
				if(!this->threadHosts[i]->threadRunning())
				{
					idleCount++;
				}
			}

			return idleCount;
		}

		unsigned int threadManager::busyThreads()
		{
			return this->getHostCount() - this->idleThreads();
		}

		threadHost* threadManager::reserveThread(std::string name)
		{
			threadHost* reserved_thread = nullptr;
			this->wait_reservation = true;

			while (wait_reservation)
			{
				if (this->idleThreads() > 0)
				{
					reserved_thread = this->threadHosts[getFreeThreadHost()];

					reserved_thread->reserve();

					this->reservedThreads[name] = reserved_thread;

					wait_reservation = false;
				}
			}

			return reserved_thread;
		}

		threadHost* threadManager::retrieveReservation(std::string name)
		{
			return this->reservedThreads[name];
		}

		void threadManager::releaseThread(std::string name)
		{
			bool done = false;

			while (!done)
			{
				if (!this->reservedThreads[name]->threadRunning())
				{
					this->reservedThreads[name]->release();
					this->reservedThreads.erase(name);
					done = true;
				}
			}
		}
	}
}
