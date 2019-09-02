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

extern int high,low;
extern pid_t process[100];

void status_check(){
        int status;
        pid_t pid;

        int flag = 0;

        for(int i = low;i < high; i++){
                pid = waitpid(process[i],&status,WNOHANG);

                //printf("%d %d\n",process[i],pid);

                if(pid == process[i]){
                        low = i+1;
                        printf("[process with %d pid has completed]\n", pid);
                        process[i] = -10;
                        flag = 1;
                }
        }

}