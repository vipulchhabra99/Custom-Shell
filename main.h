#ifndef MAIN_H 
#define MAIN_H 

struct arr {
        char arr[100][100];
};
void print_perms(mode_t st);
void add_to_history(char* str);
void read_history(int n);
void shellbasic(char* current_location);

void status_check();
void take_input(char* str);
struct arr tokenize(char *str);
void commands(struct arr commands);

#endif 