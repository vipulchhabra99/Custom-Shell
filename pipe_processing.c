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

#include "main.h"

void pipe_processing(struct arr command) {

        int i = 0;
        int command_pointer = 0;
        int command_length = 0;
        int pipe_count = 0;
        pid_t pid;
        int in;

        in = 0;

        char *args[100][100];
        args[0][0] = "\0";

        char new_command[100] = "\0";
        
        while(i < 100){

                if(strlen(command.arr[i]) == 0 )
                        break;

                else{

                        //printf("%s ",command.arr[i]);
                        
                        command.arr[i][strcspn(command.arr[i],"\n")] = 0;
                        command.arr[i][strcspn(command.arr[i]," ")] = 0;
                        //printf("%s\n",command.arr[i]);
                                
                        if(strcmp(command.arr[i],"|") == 0) {
                                pipe_count++;
                                args[command_pointer][command_length] = NULL;
                                i++;
                                command_length = 0;
                                command_pointer++;
                        }

                        else{
                               args[command_pointer][command_length] = command.arr[i];
                               i++;
                               command_length++;
                        }
                                
                }

        }

        int fd[2*pipe_count];

        for(i = 0;i < pipe_count;i++) {
                if(pipe(fd+i*2) < 0) {
                        perror("couldn't pipe");
                        exit(EXIT_FAILURE);
                }
        }

        int j = 0;
        int status;
        int command_count = 0;

        while(command_count < pipe_count+1){
                pid = fork();
                if(pid == 0){
                        if(command_count!= pipe_count){
                                if(dup2(fd[j+1],1) < 0){
                                        perror("dup2");
                                        exit(EXIT_FAILURE);
                                }
                        }

                        if(j != 0){
                                if(dup2(fd[j-2],0) < 0){
                                        perror("dup2");
                                        exit(EXIT_FAILURE);
                                }
                        }

                        for(i = 0;i < 2*pipe_count;i++){
                                close(fd[i]);
                        }

                        if(execvp(args[command_count][0],args[command_count]) < 0){
                                exit(EXIT_FAILURE);
                        }

                } else if(pid < 0){
                        exit(EXIT_FAILURE);
                }

                command_count += 1;
                j += 2;
        }

        for(i = 0;i < 2*pipe_count;i++){
                close(fd[i]);
        }

        for(i = 0;i < pipe_count+1;i++){
                wait(&status);
        }

}