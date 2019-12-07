#include "controller.h"

static struct worker_pool Workers;
static pthread_t logger;
static bool worked;


int createWorker(int index)
{
    int state = 0;
    Workers.pool[index] = (struct worker *)malloc(sizeof(struct worker));
    if (!Workers.pool[index])
    {
        printf("\nНе удалось аллоцировать память для воркера  %d", index);
        return -1;
    }
    Workers.pool[index]->tasks = NULL;
    Workers.pool[index]->workerId = index;
    Workers.pool[index]->count_task = 0;
    Workers.pool[index]->worked = true;
    state = sem_init(&(Workers.pool[index]->lock), 0, 1);
    if (state)
    {
        printf("Не удалось инициализировать семафор для %d задачи", index);
        return -2;
    }

    state = pthread_create(&Workers.pool[index]->thread, NULL, InitWorker, (void *)Workers.pool[index]);
    if (state)
    {
        printf("Не удалось создать поток для воркера %d\n", index);
        return -3;
    }

    return 0;
}
