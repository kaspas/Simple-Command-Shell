#include <stdio.h>

int interactive_mode();
void execute(char **argv,int pid);
char **arguments(char *line);
char *read_line(FILE *stream);

char* concat(const char *s1, const char *s2);
void cd_execute(char **args,int pid);
void reset_signals();
void ignore_signals();
int batchmode(char *arg);





