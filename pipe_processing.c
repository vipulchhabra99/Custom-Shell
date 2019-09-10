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

void pip_imp(int pipe_count,char *args[][100]){

        int i = 0;
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
        pid_t pid;

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

void pipe_processing(struct arr command) {

        int i = 0;
        int command_pointer = 0;
        int command_length = 0;
        int pipe_count = 0;
        int io_red = 0;
        pid_t pid;
        int input = 0;
        int output = 0;
        int append = 0;
        int in;

        in = 0;

        char *args[100][100] = {{NULL}};

        int io_po[100] = {-1};
        
        int io_po_size = 0;

        char new_command[100] = "\0";
        
        while(i < 100){

                if(strlen(command.arr[i]) == 0 )
                        break;

                else{ 
                        command.arr[i][strcspn(command.arr[i],"\n")] = 0;
                        command.arr[i][strcspn(command.arr[i]," ")] = 0;

                        if(strcmp(command.arr[i],"|") == 0) {
                                pipe_count++;
                                args[command_pointer][command_length] = NULL;
                                i++;
                                command_length = 0;
                                command_pointer++;
                        }

                        else{
                                if(strcmp(command.arr[i],">") == 0){
                                        output = 1;
                                        io_red = 1;
                                        io_po[io_po_size] = command_pointer;
                                        io_po_size++;
                                        i++;

                                }

                                else if(strcmp(command.arr[i],"<") == 0){
                                        input = 1;
                                        io_red = 1;
                                        io_po[io_po_size] = command_pointer;
                                        io_po_size++;
                                        i++;
                                }

                                else if(strcmp(command.arr[i],">>") == 0){
                                        append = 1;
                                        io_red = 1;
                                        io_po[io_po_size] = command_pointer;
                                        io_po_size++;
                                        i++; 
                                }

                                else{
                                        args[command_pointer][command_length] = command.arr[i];
                                        i++;
                                        command_length++;
                                }
                                
                        }
                                
                }

        }

        if(io_red == 0)
        pip_imp(pipe_count,args);

        if(io_red == 1){

                char *filename_input = NULL,*filename_output = NULL;
                
                if(input == 1 && output == 0 && append == 0){

                        for(i = 0;i < 100;i++){
                                if(args[0][i] == NULL)
                                break;
                        }

                        filename_input = args[0][i-1];
                        args[0][i-1] = NULL;
                }

                else if(input == 0 && output == 1 || input == 0 && append == 1){

                        for(i = 0;i < 100;i++){
                                if(args[pipe_count][i] == NULL)
                                break;
                        }

                        

                        filename_output = args[pipe_count][i-1];
                        args[pipe_count][i-1] = NULL;
                }

                else if(input == 1 && output == 1 || input == 1 && output == 1){

                        for(i = 0;i < 100;i++){
                                if(args[0][i] == NULL)
                                break;
                        }

                        filename_input = args[0][i-1];

                        args[0][i-1] = NULL;

                        for(i = 0;i < 100;i++){
                                if(args[pipe_count][i] == NULL)
                                break;
                        }

                        filename_output = args[pipe_count][i-1];

                        args[pipe_count][i-1] =NULL;

                }

                int pos_loc = 0;

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
                pid_t pid;

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

                                if(input == 1 && j == 0){

                                        fd[j] = open(filename_input,O_RDONLY,0644);
                                        dup2(fd[j],0);
                                }

                                if(output == 1 || append == 1 && command_count == pipe_count){

                                        if(output == 1) {
                                                fd[j+1] = open(filename_output,O_CREAT|O_WRONLY| O_TRUNC, 0644);
                                        }

                                        else
                                        fd[j+1] = open(filename_output,O_WRONLY|O_APPEND, 0644);

                                        dup2(fd[j+1],1);
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
 
                
}