//the interface for the printer ADT
//Written by He Tan, Feb 2022
#include "task.h"

#ifndef PRINTER_H_ /* Include guard */
#define PRINTER_H_

//declare the printer
struct printer {
    //the number of pages the printer can print in a minute 
    int page_rate;
    //the current task the printer is printing
    struct task* current_task;
    //the time (in seconds) remaining to complete the current task
    unsigned int time_remaining;
};

//do one second of printing, 
//i.e., the remaning time to complete the current task is subtracted one. 
//parameters:
//  *p, the pointer points to the printer
void tick(struct printer*);
//check whehter the printer is printing
//parameters:
//  *p, the pointer points to the printer
//return 1 (true) or 0 (false)
int is_busy(struct printer* p);
//start the next printing task
//parameters:
//  *p, the pointer points to the printer
//  *t, the pointer points to the printing task
void start_next(struct printer* p, struct task* t);
//display the printer's current status
//  *p, the pointer points to the printer
void printer_status(struct printer* p);


#endif