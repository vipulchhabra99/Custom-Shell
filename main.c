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

#include "shell_input.h"

#include "shell_path.h"

#include "commands.h"

#include "tokenize_command.h"

#include "status_check.h"

#include "history.h"

#include "main.h"


void print_perms(mode_t st) {
    char perms[11];
    if(st && S_ISREG(st)) perms[0]='-';
    else if(st && S_ISDIR(st)) perms[0]='d';
    else if(st && S_ISFIFO(st)) perms[0]='|';
    else if(st && S_ISSOCK(st)) perms[0]='s';
    else if(st && S_ISCHR(st)) perms[0]='c';
    else if(st && S_ISBLK(st)) perms[0]='b';
    else perms[0]='l';  // S_ISLNK
    perms[1] = (st && S_IRUSR) ? 'r':'-';
    perms[2] = (st && S_IWUSR) ? 'w':'-';
    perms[3] = (st && S_IXUSR) ? 'x':'-';
    perms[4] = (st && S_IRGRP) ? 'r':'-';
    perms[5] = (st && S_IWGRP) ? 'w':'-';
    perms[6] = (st && S_IXGRP) ? 'x':'-';
    perms[7] = (st && S_IROTH) ? 'r':'-';
    perms[8] = (st && S_IWOTH) ? 'w':'-';
    perms[9] = (st && S_IXOTH) ? 'x':'-';
    perms[10] = '\0';
    printf("%s", perms);
}

pid_t process[100];

int low = 1,high = 1;

int main() {

signal(SIGCHLD,status_check);

    char* initial_location = getenv("PWD");
    shellbasic(initial_location);
    char s[100] = "\0";

    while(1) {
      char buff[60] = "\0";
      take_input(buff);
      //printf("%s",buff);
        add_to_history(buff);
        struct arr comm;

        for(int i = 0;i < 100;i++){
                comm.arr[i][0] = '\0';
        }

        struct arr comm_split;

        for(int i = 0;i < 100;i++){
                comm_split.arr[i][0] = '\0';
        }

        comm_split = tokenize_comma(buff);
        

        for(int i = 0;i < 100;i++) {

                if(strlen(comm_split.arr[i]) != 0) {
                        comm = tokenize(comm_split.arr[i]);
      //printf("%s\n",commands.arr[0]);
                        commands(comm);
                }   
        }
      shellbasic(initial_location);

    }

    return 0;
}