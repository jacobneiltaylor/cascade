/*
	
	cascade.h

	Part of Cascade: A C++ Thread Management Library based on std::thread

	Copyright Taylor Networks 2015. Licensed under the GNU GPL.

*/

#ifndef LIBCASCADE_BASE

#define LIBCASCADE_BASE

#define LIBCASCADE_VERSION 0.3.0

// Support symbol export on Windows platform
#ifdef _WIN32
	#ifdef _WINDLL
		#define LIBCASCADE_API __declspec(dllexport) 
	#else
		#define LIBCASCADE_API __declspec(dllimport) 
	#endif
#else
	#define LIBCASCADE_API
#endif

// STL Dependencies
#include <thread>
#include <mutex>
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
