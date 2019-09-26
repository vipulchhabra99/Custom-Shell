#ifndef LINKEDLIST_H 
#define LINKEDLIST_H 

struct node { 
    pid_t pid; 
    struct node* next; 
};

void insert(pid_t pid,struct node **head);
void pop(pid_t pid,struct node **head);

#endif 