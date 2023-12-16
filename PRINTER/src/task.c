#include "stdlib.h"
#include "time.h"
#include "task.h"

struct task* create_task(int ct, int p)
{
	struct task* t = (struct task*)malloc(sizeof(struct task));
	if (t == NULL) exit(1);
	t->time_stamp = ct;
	t->pages = rand() % p + 1; //Ran pages between 1-5 M
	return t;
}

int wait_time(struct task* t, int ct)
{
	return (t->time_stamp) - ct;
}