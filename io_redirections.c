
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

void stream_processing(struct arr command){

        pid_t wpid;
        int last_output = 0;
        int status = 0;
        int last_input = 0;
        int append = 0;
        int input = 0,output = 0;
        int i = 0;
        int command_pointer = 0;  
           
        char *args[100] = {NULL};
        
        
        while(i < 100){

                command.arr[i][strcspn(command.arr[i],"\n")] = 0;

                if(strlen(command.arr[i]) == 0)
                        break;

                else{
                        
                        if(strcmp(command.arr[i],">") == 0) {
                                last_output = i;
                                output = 1; 
                                i += 2;     
                        }

                        else if(strcmp(command.arr[i],"<") == 0) {
                                last_input = i;
                                input = 1;
                                i += 2;
                        }

                        else if(strcmp(command.arr[i],">>") == 0){
                                last_output = i;
                                output = 1;
                                append = 1;
                                i+=2;
                        }

                        else{
                                args[command_pointer] = command.arr[i];
                                i++;
                                command_pointer++;
                        }
                                
                }

                        
        }

        args[command_pointer] = NULL;

        command.arr[last_output+1][strcspn(command.arr[last_output+1],"\n")] = 0;
        command.arr[last_input+1][strcspn(command.arr[last_input+1],"\n")] = 0;

        if(output == 1 && input == 0 && append == 0) {
                if(fork() == 0){
                        close(1);
                        int fd = open(command.arr[last_output+1],O_CREAT|O_WRONLY| O_TRUNC, 0644);
                        dup2(fd,1);
                        execvp(args[0],args);
                        close(fd);
                        exit(0);
                }
        }
        
        else if(input == 1 && output == 0 && append == 0) {
                if(fork() == 0){
                        close(0);
                        int fd = open(command.arr[last_input+1],O_RDONLY,0644);
                        dup2(fd,0);
                        execvp(args[0],args);
                        close(fd);
                        exit(0);
                }
        }

        else if(input == 1 && output == 1 && append == 0){
                if(fork() == 0){
                        int fd = open(command.arr[last_input+1],O_RDONLY,0644);
                        int fd2 = open(command.arr[last_output+1],O_CREAT|O_WRONLY|O_TRUNC, 0644);
                        close(1);
                        close(0);
                        dup2(fd2,1);
                        dup2(fd,0);
                        execvp(args[0],args);
                        close(fd);
                        close(fd2);
                        exit(0);
                }
        }

        if(output == 1 && input == 0 && append == 1) {
                if(fork() == 0){
                        close(1);
                        int fd = open(command.arr[last_output+1],O_WRONLY|O_APPEND,0644);
                        dup2(fd,1);
                        execvp(args[0],args);
                        close(fd);
                        exit(0);
                }
        }
        

        else if(input == 1 && output == 1 && append == 1){
                if(fork() == 0){
                        close(1);
                        close(0);
                        int fd = open(command.arr[last_input+1],O_RDONLY,0644);
                        int fd2 = open(command.arr[last_output+1],O_CREAT|O_WRONLY|O_APPEND, 0644);
                        dup2(fd2,1);
                        dup2(fd,0);
                        execvp(args[0],args);
                        close(fd);
                        close(fd2);
                        exit(0);
                }
        }
        

         
}