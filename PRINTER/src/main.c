#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "queue.h"
#include "task.h"
#include "printer.h"
#include "math.h"

#define MAX_TASKS 100  //Max heap
#define PAGE_RANGE 20 //Maximum pages per task
#define PAGE_RATE 40 //pages per minute the printer can print
#define SIM_TIME 100

int main()
{
    srand(time(NULL));

    struct minheap* h = create_heap(MAX_TASKS);

    //setting up the printer
    struct printer p;
    p.page_rate = PAGE_RATE;
    p.time_remaining = NULL;
    p.current_task = NULL;

    int ct = time(NULL);

    for (int i = 0; i < SIM_TIME; i++)
    {

        ct++;

        //The probability of a new task in queue is 50 %
        if (rand() % 2 && h->cur_size < MAX_TASKS)
        {
            insert_heap(h, create_task(ct, PAGE_RANGE));
        }
        
    
        printer_status(&p);
        display_heap(h);

        if (!is_busy(&p) && !is_empty(h)) //if printer is not busy and not empty start next task
        {
            start_next(&p, findmin(h)); //Start next print task with smallest number of pages
            delete_heap(h); //Remove from the binary heap
        }

        else if (is_busy(&p))
        {
            tick(&p);
        }

        printf("\n");
        

    }

    puts("SIMULATION ENDS");
}