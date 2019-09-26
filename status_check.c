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

#include "linkedlist.h"

extern struct node *all_process_link;
extern struct node *bg_processes;


extern int high,low;
extern pid_t process[100];

void status_check(){
        int status;
        pid_t pid;

        int flag = 0;

        struct node *bg_processes_move = bg_processes;

        while(bg_processes_move != NULL) {

                pid = waitpid(bg_processes_move->pid,&status,WNOHANG);

                if(pid == bg_processes_move->pid) {
                        printf("[process with %d pid has completed]\n", pid);
                }

                bg_processes_move = bg_processes_move->next;
                pop(pid,&bg_processes);
                pop(pid,&all_process_link);
        }
        

        /*for(int i = 0;i < high; i++){
                pid = waitpid(process[i],&status,WNOHANG);

                //printf("%d %d\n",process[i],pid);

                if(pid == process[i]){
                        low = 0;
                        printf("[process with %d pid has completed]\n", pid);
                        process[i] = -10;
                        flag = 1;
                }
        }*/
        return;
}