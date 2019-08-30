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

struct arr {
        char arr[100][100];
};

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

pid_t process[100];

int low = 1,high = 1;

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

void take_input(char* str) {

        char buff[1000] = "\0";
        int fd = 0;
        int i = 0;
        //status_check();

        for(int i = 0;i < 1000;i++) {
                scanf("%c",&buff[i]);
                if(buff[i] == '\n') {
                        break;
                }
        }

        strcpy(str,buff);
}

struct arr tokenize(char *str) {

        struct arr commands;

        for(int i = 0;i < 100;i++){
                commands.arr[i][0] = '\0';
        }

        char* ptr = strtok(str," ");
        

        int i = 0;

        while(ptr != NULL) {
                strcpy(commands.arr[i],ptr);
                ptr = strtok(NULL," ");
                i++;
        }

        return commands;
}


void commands(struct arr commands){

        

        commands.arr[0][strcspn(commands.arr[0],"\n")] = 0;
        if(strcmp(commands.arr[0],"cd") == 0) {
                
                commands.arr[1][strcspn(commands.arr[1],"\n")] = 0;
                int x = chdir(commands.arr[1]);

                if(x == -1){
                      printf("Given directory doesn't exist\n");
                }
        }

        else if(strcmp(commands.arr[0],"pwd") == 0) {
                
                char working_dir[100] = "\0";
                printf("%s\n",getcwd(working_dir,100));
        }

        else if(strcmp(commands.arr[0],"echo") == 0) {

                char instruction[] = "\0";
        
              for(int i = 1;i < 100;i++) {
                      if(strlen(commands.arr[i]) == 0){
                              break;
                      }

                      else{
                        strcat(instruction,commands.arr[i]);
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
        

        else if(strcmp(commands.arr[0],"ls") == 0) {
                
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
                if(strlen(commands.arr[1]) == 0) {
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
                        commands.arr[1][strcspn(commands.arr[1],"\n")] = 0;
                        strcat(commands.arr[0]," ");
                        strcat(commands.arr[0],commands.arr[1]);
                        
                        if(strcmp(commands.arr[1],"-l") == 0){

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
                

                        else if(strcmp(commands.arr[1],"-a") == 0){

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

                        else if(strcmp(commands.arr[1],"-la") == 0 || strcmp(commands.arr[1],"-al") == 0){
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
                                n = scandir(commands.arr[1],&d1,NULL,alphasort);

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

        else if(strcmp(commands.arr[0],"pinfo") == 0) {

                if(strlen(commands.arr[1]) == 0) {

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
                        
                int pid = atoi(commands.arr[1]);

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

        else if(!strcmp(commands.arr[0], "exit")){
                exit(0);
        }

        else if(!strcmp(commands.arr[0], "history")){

                if(strlen(commands.arr[1]) == 0){
                        read_history(10);
                }

                else{
                        read_history(atoi(commands.arr[1]));
                }
        }

        else {

                int i = 0;
                int background = 0;
                char *args[100];
                args[0] = "\0";

                while(i < 100){
                        //printf("%s\n",commands.arr[i]);
                        if(strlen(commands.arr[i]) == 0 )
                                break;

                        else{
                                commands.arr[i][strcspn(commands.arr[i],"\n")] = 0;
                                
                                if(strcmp(commands.arr[i],"&") == 0 || strcmp(commands.arr[i],"&\0") == 0) {
                                        background = 1;
                                        break;        
                                }

                                else{
                                        args[i] = commands.arr[i];
                                        //printf("%s\n",commands.arr[i]);
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
                        
                        //printf("NO");
                        
                        if(childpid == 0){
                                exit(execvp(args[0],args));
                                
                        }

                        else {
                                wait(NULL);

                                        //printf("%d",WEXITSTATUS(status));
                                

                                //printf("running parent now \n");
                        }

                        
                }
                
        }

        
 
}

struct arr tokenize_comma(char *str) {

        struct arr commands;

        for(int i = 0;i < 100;i++){
                commands.arr[i][0] = '\0';
        }

        char* ptr = strtok(str,";");
        

        int i = 0;

        while(ptr != NULL) {
                strcpy(commands.arr[i],ptr);
                ptr = strtok(NULL,";");
                i++;
        }

        return commands;
}




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