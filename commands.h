#ifndef COMMANDS_H  
#define COMMANDS_H

struct arr;
extern int high,low;
extern pid_t process[100];
extern pid_t fgprocess[100];
extern int fglow;
extern int fghigh;
void cd_command(struct arr command);
void ls_command(struct arr command);
void pinfo_command(struct arr command);
void commands(struct arr command);

#endif