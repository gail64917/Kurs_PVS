#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/file.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/select.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER 4096

struct FileDescSet
{
    fd_set set;
    int count;
};

struct letter_info
{
    char *to;
    char *from;
    FILE *file;
    char message[BUFFER];
};

struct FileDesc
{
    int id;
    char *domain;
    char *mx_record;
    struct sockaddr_in *addr;
    int current_state;
    int prev_state;
    int attempt;
    struct worker_task *task_pool;
    struct letter_info meta_data;
};

struct FileDescList
{
    struct FileDesc *fd;
    struct FileDescList *next;
};

struct domain_record
{
    char *domain;
    int workerId;
    struct domain_record *next;
};

struct worker_pool
{
    int count;
    struct worker **pool;
};

struct worker_task 
{
    int state;
    char *path;
    char *domain;
    struct worker_task *next;
};

struct worker
{
    pthread_t thread;
    sem_t lock;
    struct worker_task *tasks;
    int workerId;
    int count_task;
    bool worked;
};

struct network_controller
{
    struct FileDescSet readers;
    struct FileDescSet writers;
    struct FileDescSet handlers;
    struct FileDescList *socket_list;    
};



#endif //  STRUCTS_H
