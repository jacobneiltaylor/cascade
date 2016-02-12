/*
	
	cascade.h

	Part of Cascade: A C++ Thread Management Library based on std::thread

	Copyright Taylor Networks 2015. Licensed under the GNU GPL.

*/

#ifndef LIBCASCADE_BASE

#define LIBCASCADE_BASE

#define LIBCASCADE_VERSION 0.1

// STL Dependencies
#include <thread>
#include <queue>
#include <vector>
#include <map>
#include <functional>

// Forward Declarations
namespace taylornet
{
	namespace cascade
	{
		class worker;
		class threadHost;
		class threadManager;
	}
}

// Library Header Files
#include "worker.h"
#include "threadHost.h"
#include "threadManager.h"

#endif
