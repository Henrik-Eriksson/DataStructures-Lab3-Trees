#include "stdlib.h"
#include "math.h"
#include "printer.h"

/*
Function simulates one second of printing
Parameter: *p, points to printer
Remaining time is subtracted by one for every tick
*/

void tick(struct printer* p)
{
    printf("%d seconds to complete the current task\n", p->time_remaining);
    p->time_remaining--;
    if (!is_busy(p))       
    {
        p->current_task = NULL;
    }
}

/*
This function checks if the printer is busy
Parameter *p, the pointer which points to the printer
Return 1 if printer is busy and 0 if not
*/

int is_busy(struct printer* p)
{
    if (p->time_remaining != 0) return 1;
    return 0;
}

/*
This function starts the next printing task
Parameter: *p: (printer pointer) and *t: (task pointer)
*/

void start_next(struct printer* p, struct task* t)
{
    p->current_task = t;
    p->time_remaining = ceil(60 / p->page_rate) * t->pages; //CEILING FUNCTION NUMBERS UP REMAINDING TIME
}

/*
This function prints the status of the printer
Parameter: *p (printerpointer)
*/

void printer_status(struct printer* p)
{
    if (!is_busy(p))
    {
        puts("THE PRINTER IS NO LONGER BUSY!");
    }
    else
    {
        puts("THE PRINTER IS BUSY!");
    }
}

