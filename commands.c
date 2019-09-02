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


extern int low;
extern int high;

extern pid_t process[100];

void commands(struct arr command){

        command.arr[0][strcspn(command.arr[0],"\n")] = 0;
        if(strcmp(command.arr[0],"cd") == 0) {
                
                command.arr[1][strcspn(command.arr[1],"\n")] = 0;
                int x = chdir(command.arr[1]);

                if(x == -1){
                      printf("Given directory doesn't exist\n");
                }
        }

        else if(strcmp(command.arr[0],"pwd") == 0) {
                
                char working_dir[100] = "\0";
                printf("%s\n",getcwd(working_dir,100));
        }

        else if(strcmp(command.arr[0],"echo") == 0) {

                char instruction[] = "\0";
        
              for(int i = 1;i < 100;i++) {
                      if(strlen(command.arr[i]) == 0){
                              break;
                      }

                      else{
                        strcat(instruction,command.arr[i]);
                        strcat(instruction," ");
                      }
              }

              instruction[strcspn(instruction," ")] = 0;
              instruction[strcspn(instruction,"\n")] = 0;

              for(int i = 0;i < strlen(instruction); i++){
                      printf("%c",instruction[i]);
              }
              printf("\n");
        }
        

        else if(strcmp(command.arr[0],"ls") == 0) {
                
                int n;
                DIR* dir;
                struct dirent *d;
                struct dirent *file;
                struct stat sbuf;
                struct passwd pwent, * pwentp;
                struct group grp, * grpt;
                char working_dir[100] = "\0";
                char datestring[256] = "\0";
                char buf[128] = "\0";
                struct tm time;
                if(strlen(command.arr[1]) == 0) {
                        struct dirent **d1;
                        
                        n = scandir(".",&d1,NULL,alphasort);

                        if(n < 0) {

                                printf("Unable to perform the action! ");
                        }

                        else {
                                while(n--) {
                                        if(strcmp(d1[n]->d_name,".") != 0){
                                                if(strcmp(d1[n]->d_name, "..") != 0) {
                                                        printf("%s\n",d1[n]->d_name);
                                                }
                                        }
                                        
                                        free(d1[n]);
                                }

                                free(d1);
                        }
                }

                else{
                        dir = opendir(getcwd(working_dir,100));
                        command.arr[1][strcspn(command.arr[1],"\n")] = 0;
                        strcat(command.arr[0]," ");
                        strcat(command.arr[0],command.arr[1]);
                        
                        if(strcmp(command.arr[1],"-l") == 0){

                                while(file=readdir(dir)) {
                                        if(strcmp(file->d_name,".") != 0){
                                                if(strcmp(file->d_name,"..") != 0){
                                                        stat(file->d_name, &sbuf);
                                                        print_perms(sbuf.st_mode);
                                                        printf(" %d", (int)sbuf.st_nlink);
                                                        if (!getpwuid_r(sbuf.st_uid, &pwent, buf, sizeof(buf), &pwentp))
                                                        printf(" %s", pwent.pw_name);
                                                else
                                                        printf(" %d", sbuf.st_uid);
 
                                                if (!getgrgid_r (sbuf.st_gid, &grp, buf, sizeof(buf), &grpt))
                                                        printf(" %s", grp.gr_name);
                                                else
                                                        printf(" %d", sbuf.st_gid);
                                                
                                                printf(" %5d", (int)sbuf.st_size);
        
                                                localtime_r(&sbuf.st_mtime, &time);
                                        /* Get localized date string. */
                                                strftime(datestring, sizeof(datestring), "%F %T", &time);
 
                                                printf(" %s %s\n", datestring, file->d_name);
                                                }
                                        }
                                }
                                        


                        }
                

                        else if(strcmp(command.arr[1],"-a") == 0){

                                struct dirent **d1;
                                n = scandir(".",&d1,NULL,alphasort);

                                if(n < 0) {

                                        printf("Unable to perform the action! ");
                                }

                                else {
                                        while(n--) {
                                                printf("%s\n",d1[n]->d_name);
                                                free(d1[n]);
                                        }

                                        free(d);
                                }

                        }

                        else if(strcmp(command.arr[1],"-la") == 0 || strcmp(command.arr[1],"-al") == 0){
                                //printf("I am here");
                                while(file=readdir(dir)) {
                                        
                                        stat(file->d_name, &sbuf);
                                        print_perms(sbuf.st_mode);
                                        printf(" %d", (int)sbuf.st_nlink);
                                        if (!getpwuid_r(sbuf.st_uid, &pwent, buf, sizeof(buf), &pwentp))
                                                printf(" %s", pwent.pw_name);
                                        else
                                                printf(" %d", sbuf.st_uid);
 
                                        if (!getgrgid_r (sbuf.st_gid, &grp, buf, sizeof(buf), &grpt))
                                                printf(" %s", grp.gr_name);
                                        else
                                                printf(" %d", sbuf.st_gid);
                                                
                                        printf(" %5d", (int)sbuf.st_size);
        
                                        localtime_r(&sbuf.st_mtime, &time);
                                        /* Get localized date string. */
                                        strftime(datestring, sizeof(datestring), "%F %T", &time);
 
                                        printf(" %s %s\n", datestring, file->d_name);
                                }
                        }
                
                

                        else {
                                struct dirent **d1;
                                n = scandir(command.arr[1],&d1,NULL,alphasort);

                                if(n < 0) {

                                        printf("Unable to perform the action! ");
                                }

                                else {
                                        while(n--) {
                                                printf("%s\n",d1[n]->d_name);
                                                free(d1[n]);
                                        }

                                        free(d);
                                }
                        }
                }       
        }

        else if(strcmp(command.arr[0],"pinfo") == 0) {

                if(strlen(command.arr[1]) == 0) {

                        int pid = getpid();

                printf("pid -- %d\n",pid);

                char spid[10240] = "\0";
                char buffer[10240] = "\0";

                size_t bytes_read;

                sprintf(spid,"/proc/%d/status",pid);

                FILE *fp;

                fp = fopen(spid,"r");

                char ch = '\0';
                char status = '\0';

                bytes_read = fread(buffer,1,sizeof(buffer),fp);

                fclose(fp);

                buffer[bytes_read] = '\0';

                char* match = "\0";
                unsigned long int vmsize;

                match = strstr(buffer,"State");

                sscanf(match,"State:	%c",&status);

                printf("Status : %c\n",status);

                match = strstr(buffer,"VmSize");

                sscanf(match,"VmSize:	  %lu",&vmsize);

                printf("Memory : %lu\n",vmsize);

                sprintf(spid,"/proc/%d/cmdline",pid);

                fp = fopen(spid,"r");

                bytes_read = fread(buffer,1,sizeof(buffer),fp);

                buffer[bytes_read] = '\0';

                printf("Executable path : ");

                for(int i = 0;i <= bytes_read;i++) {
                        printf("%c",buffer[i]);
                }

                printf("\n");

                fclose(fp);
                }

                else{
                        
                int pid = atoi(command.arr[1]);

                printf("pid -- %d\n",pid);

                char spid[10240] = "\0";
                char buffer[10240] = "\0";

                size_t bytes_read;

                sprintf(spid,"/proc/%d/status",pid);

                FILE *fp;

                fp = fopen(spid,"r");

                char ch;
                char status;

                bytes_read = fread(buffer,1,sizeof(buffer),fp);

                fclose(fp);

                buffer[bytes_read] = '\0';

                char* match;
                unsigned long int vmsize;

                match = strstr(buffer,"State");

                sscanf(match,"State:	%c",&status);

                printf("Status : %c\n",status);

                match = strstr(buffer,"VmSize");

                sscanf(match,"VmSize:	  %lu",&vmsize);

                printf("Memory : %lu\n",vmsize);

                sprintf(spid,"/proc/%d/cmdline",pid);

                fp = fopen(spid,"r");

                bytes_read = fread(buffer,1,sizeof(buffer),fp);

                buffer[bytes_read] = '\0';

                printf("Executable path : ");

                for(int i = 0;i <= bytes_read;i++) {
                        printf("%c",buffer[i]);
                }

                printf("\n");

                fclose(fp);
                }

                

        }

        else if(!strcmp(command.arr[0], "exit")){
                exit(0);
        }

        else if(!strcmp(command.arr[0], "history")){

                if(strlen(command.arr[1]) == 0){
                        read_history(10);
                }

                else{
                        read_history(atoi(command.arr[1]));
                }
        }

        else {

                int i = 0;
                int background = 0;
                char *args[100];
                args[0] = "\0";

                while(i < 100){
                        //printf("%s\n",command.arr[i]);
                        if(strlen(command.arr[i]) == 0 )
                                break;

                        else{
                                command.arr[i][strcspn(command.arr[i],"\n")] = 0;
                                
                                if(strcmp(command.arr[i],"&") == 0 || strcmp(command.arr[i],"&\0") == 0) {
                                        background = 1;
                                        break;        
                                }

                                else{
                                        args[i] = command.arr[i];
                                        //printf("%s\n",command.arr[i]);
                                        i++;
                                }
                                
                        }

                        
                }

                args[i] = NULL;

                

                if(background == 1) {

                        pid_t childpid = fork();

                        process[high] = childpid;

                        //printf("Yes");
                        if(childpid == 0) {
                                setpgid(0,getpid());
                                exit(execvp(args[0],args));
                        
                        }
                        
                        if(high < 100)
                                high++;

                }

                if(background == 0){

                        pid_t childpid = fork();

                        pid_t wpid;

                        int status = 0;
                        
                        if(childpid == 0){
                                exit(execvp(args[0],args));
                                
                        }

                        else {
                                wait(NULL);
                        }

                        
                }
                
        }

        
 
}