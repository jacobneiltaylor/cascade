#include "../include/cascade.h"

using namespace taylornet::cascade;

class queueWorker : public worker
{
private:
	bool done;
	threadManager* tm;
	void work();

public:
	queueWorker();
	~queueWorker();
	void stop();
};