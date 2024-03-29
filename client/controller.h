#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include "structures.h"
#include "worker.h"
#include "dictionary.h"

#define STATE_START_INIT 0
#define STATE_FINISH_INIT 1
#define STATE_START_WORK 2
#define STATE_FINISH_WORK 3
#define STATE_FAIL_WORK -1

void InitController();
void Dispose();
struct worker_pool *GetWorkerPool();

int DelegateTaskToWorker(int workerIndex, struct worker_task *task);
int MostFreeWorker();



int createWorker(int index);

#endif // CONTROLLER_H
