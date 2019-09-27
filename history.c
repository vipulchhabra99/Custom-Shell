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

extern int file;

extern int fd;

void add_to_history(char* str){
        
        
        char error[] = "Unable to write history";
        int check = write(file,str,strlen(str));

        if(check < 0){
                printf("%s",error);
        }
}

void read_history(int n){

        char c;

        int l = 0;

        
        lseek(fd,0,SEEK_END);

        while(l < n+1 && lseek(fd,-1,SEEK_CUR) != -1){
                read(fd,&c,1);
                        
                lseek(fd,-1,SEEK_CUR);
                        
                if(c == '\n')
                        l++;
        }
                
        while(read(fd,&c,1) != 0){
                printf("%c",c);
        }

        lseek(fd,0,SEEK_END);

}

void up_buttons(int n){

        char c;

        int l = 0;

        
        lseek(fd,0,SEEK_END);

        while(l < n+1 && lseek(fd,-1,SEEK_CUR) != -1){
                read(fd,&c,1);
                        
                lseek(fd,-1,SEEK_CUR);
                        
                if(c == '\n')
                        l++;
        }
                
        while(read(fd,&c,1) != 0 && c != '\n'){
                printf("%c",c);
        }

        lseek(fd,0,SEEK_END);

}