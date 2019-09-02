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

void shellbasic(char* current_location) {

        
        char hostname[100];
        char workingdir[100];
        int size = strlen(current_location);
        gethostname(hostname,size);

        char* new_location = getcwd(workingdir,100);
        if(strlen(new_location) == size){
            printf("%s@%s:~",getenv("USER"),hostname);
        }
        else {   
                printf("%s@%s:~",getenv("USER"),hostname);
                
                //printf("%s",getcwd(workingdir,100));
                for(int i = size;i <strlen(workingdir); i++ ){
                        printf("%c",workingdir[i]);
                }
                printf(" ");
        }
}