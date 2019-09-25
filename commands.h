#ifndef COMMANDS_H  
#define COMMANDS_H

struct arr;
extern int high,low;
extern int all_high;
extern pid_t current_process;
extern pid_t process[100];
extern pid_t allprocess[1000];
void cd_command(struct arr command);
void ls_command(struct arr command);
void pinfo_command(struct arr command);
void commands(struct arr command);
int wait_for_job(int id);

#endif