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

		void threadManager::generateThreadHosts()
		{
			for(unsigned int i = 0; i < this->threadLimit; i++)
			{
				this->threadHosts[i] = new threadHost();
			}
		}

		unsigned int threadManager::getFreeThreadHost()
		{
			unsigned int freeIndex;
			unsigned int hostCount = this->getHostCount();

			for(unsigned int i = 0; i < hostCount; i++)
			{
				if(this->threadHosts[i]->workerDone())
				{
					freeIndex = i;
					i = hostCount;
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

		unsigned int threadManager::getThreadLimit()
		{
			return this->threadLimit;
		}

		unsigned int threadManager::getHostCount()
		{
			return this->threadHosts.size();
		}

		unsigned int threadManager::hardwareThreads()
		{
			return std::thread::hardware_concurrency();
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
				if(this->freeThreads() > 0)
				{
					threadHost* freeHost = this->threadHosts[getFreeThreadHost()];
					worker* nextWorker = this->workerQueue.front();

					this->workerQueue.pop();

					freeHost->assignWorker(nextWorker);

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

		void threadManager::waitForWorkers()
		{
			for(int i = 0; i < this->getHostCount(); i++)
			{
				if(!this->threadHosts[i]->workerDone())
				{
					this->threadHosts[i]->waitForWorker();
				}
			}
		}

		unsigned int threadManager::freeThreads()
		{
			return this->idleThreads();
		}

		unsigned int threadManager::idleThreads()
		{
			unsigned int hostCount = this->getHostCount();
			unsigned int idleCount = 0;

			for(unsigned int i = 0; i < hostCount; i++)
			{
				if(this->threadHosts[i]->threadRunning())
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
	}
}
