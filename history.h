#ifndef HISTORY_H 
#define HISTORY_H

void add_to_history(char* str);
void read_history(int n);
void up_buttons(int n);
extern int file;
extern int fd;

#endif