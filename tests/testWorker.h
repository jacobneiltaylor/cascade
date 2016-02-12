#include "../include/cascade.h"
#include <chrono>
#include <iostream>
#include <sstream>
#include <random>

#define SSTR( x ) dynamic_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

using namespace taylornet::cascade;

class testWorker : public worker
{
	private:

		static std::mutex outputMutex;
		std::string text;
		void work();

	public:

		testWorker(std::string text);
		~testWorker();
};
