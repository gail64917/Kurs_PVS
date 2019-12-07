#include <stdio.h>
#include "worker.h"

void InitWorker(void *info)
{
	struct worker *this_one = (struct worker*)info;
	printf("\tWorker %d start initing\n", this_one->workerId);
	return;
}
