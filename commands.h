#ifndef COMMANDS_H  
#define COMMANDS_H

struct arr;
extern int high,low;
extern pid_t process[100];
void cd_command(struct arr command);
void ls_command(struct arr command);
void pinfo_command(struct arr command);
void commands(struct arr command);

#endif