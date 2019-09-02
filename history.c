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

void add_to_history(char* str){
        
        FILE *file;
        char new_file[] = "history";
        char error[] = "Unable to write history";
        file = fopen(new_file, "a+");
        

        fputs(str,file);

        fclose(file);


}

void read_history(int n){

        int fd;

        char c;

        int l = 0;

        //printf("%d",n);

        char file[] = "history";

        char error[] = "Unable to write history";

        fd = open(file,O_RDONLY);
        if(fd < 0){
                printf("Error");
        } else {
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
        }

        


}