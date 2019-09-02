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
