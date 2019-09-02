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