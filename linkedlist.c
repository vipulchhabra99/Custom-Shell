#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <sys/types.h>

#include <sys/wait.h>

#include <unistd.h>

#include <limits.h>

#include <dirent.h>

#include <sys/stat.h>

#include <sys/dir.h>

#include <pwd.h>

#include <sys/stat.h>

#include <sys/dir.h>

#include <pwd.h>

#include <grp.h>

#include <time.h>

#include <locale.h>

#include <grp.h>

#include <time.h>

#include <locale.h>

#include <fcntl.h>

struct node { 
    pid_t pid; 
    struct node* next; 
};

struct node *newnode(pid_t pid) {
    struct node *temp = malloc(sizeof(struct node));
    temp->pid = pid;
    temp->next = NULL;
    return temp;
}

void insert(pid_t pid,struct node **head) {

    struct node *new_node = newnode(pid);
    struct node *temp = *head;

    if(*head == NULL){
        *head = new_node;
    }

    else{
        while(temp->next!= NULL){
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

void printelem(struct node **head){

    struct node *temp = *head;

    while(temp != NULL){
        printf("%d\n",temp->pid);
        temp = temp->next;
    }

    printf("\n\n");
    
}

void pop(pid_t pid,struct node **head) {

    struct node* temp = *head, *prev; 
 
    if (temp != NULL && temp->pid == pid) 
    { 
        *head = temp->next;  
        free(temp);              
        return; 
    } 

    while (temp != NULL && temp->pid != pid) 
    { 
        prev = temp; 
        temp = temp->next; 
    } 
   
    if (temp == NULL) return; 
  
    prev->next = temp->next; 
  
    free(temp);

    
}

/*int main() {

    struct node *head = NULL;

    insert(10,&head);
    insert(20,&head);
    insert(30,&head);
    insert(40,&head);
    insert(50,&head);
    printelem(&head);

    pop(20,&head);
    //pop(50);
    //pop(50);
    //pop(50);
    //pop(50);
    //pop(50);
    printelem(&head);
}*/
