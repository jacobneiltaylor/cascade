#include "../include/cascade.h"
#include <iostream>
#include <sstream>

#define SSTR( x ) dynamic_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

using namespace taylornet::cascade;

class testWorker : public worker
{
private:

		std::string text;
		void work();

	public:

		testWorker(std::string text);
		~testWorker();
};
