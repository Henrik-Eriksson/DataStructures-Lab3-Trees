#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#include "queue.h"
#include <math.h>

void swap(struct minheap* h, int i, int j)
{
    struct task* temp = h->task[i];
    h->task[i] = h->task[j];
    h->task[j] = temp;
}

void moveup(struct minheap* h, int k)
{
    while (k > 1 && h->task[k]->pages < h->task[k / 2]->pages) 
    {
        swap(h, k, k / 2);
        k = k / 2;
    }
}

void movedown(struct minheap* h, int k) 
{
    int j;
    while (2 * k <= h->cur_size) 
    {
        j = 2 * k;
        if (j < h->cur_size && h->task[j]->pages > h->task[j + 1]->pages) 
        {
            j++;
        }

        if (h->task[k]->pages <= h->task[j]->pages)
        {
            break;
        }

        swap(h, k, j);
        k = j;
    }
}

struct minheap* create_heap(int m)
{
    struct minheap* h = (struct minheap*)malloc(sizeof(struct minheap));
    h->task = (struct task**)malloc(sizeof(struct task*) * (m + 1));
    h->cur_size = 0;
    h->max_size = m;
    return h;
}

int insert_heap(struct minheap* h, struct task* t) 
{
    if (h->cur_size == h->max_size) 
    {
        return -1;
    }
    h->cur_size++;
    h->task[h->cur_size] = t;
    moveup(h, h->cur_size);
    return 0;
}

int delete_heap(struct minheap* h) 
{
    if (h->cur_size == 0) 
    {
        return -1;
    }
    swap(h, 1, h->cur_size);
    h->cur_size--;
    movedown(h, 1);
    return 0;
}

struct task* findmin(struct minheap* h)
{
    if (h->cur_size == 0) 
    {
        return NULL;
    }
    return h->task[1];
}

void destroy_heap(struct minheap* h) 
{
    free(h->task);
    free(h);
}

void display_heap(struct minheap* h) 
{

    puts("TASKS IN QUEUE:");
    for (int i = 1; i <= h->cur_size; i++)
    {
        printf("TASK[arrived at the %dth second, %d pages]\n", wait_time(h->task[i], time(NULL)), h->task[i]->pages);
    }

    printf("\n");
}

int is_empty(struct minheap* h) 
{
    if (h->cur_size == 0) return 1;
    return 0;
}