#ifndef SHELL_CHECK_H  
#define SHELL_CHECK_H


extern struct node *all_process_link;
extern struct node *bg_processes;
extern int high,low;
extern pid_t process[100];
void status_check();

#endif