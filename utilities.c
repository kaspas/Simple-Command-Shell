//#include <sys/wait.h>
//#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <signal.h>
#define MAXSTR 512
#define MAXARG 64
#define DELIM " \t\n\r\a"
/*
void ignore_signals()
{
  signal(SIGINT, SIG_IGN);
  signal(SIGTERM, SIG_IGN);
  signal(SIGQUIT, SIG_IGN);
  signal(SIGTSTP, SIG_IGN);
}
void reset_signals()
{
  signal(SIGINT, SIG_DFL);
  signal(SIGTERM, SIG_DFL);
  signal(SIGQUIT, SIG_DFL);
  signal(SIGTSTP, SIG_DFL);
}
*/
char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1)+strlen(s2)+1);//+1 for the zero-terminator
    //in real code you would check for errors in malloc here
    if(!result)
   {
    printf("Error allocate memory!\n");
    exit(1);
   }  
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}
char *read_line(FILE *stream)
{
  int size = MAXSTR;
  char *line;
  line=(char *)malloc(size*sizeof(char));
  fgets(line,MAXSTR,stream);
  return line;
}

char **arguments(char *line)
{
  char **arg,**old_arg;
  int counter=0,size=MAXARG;
  arg=(char **)malloc(size*sizeof(char *));
  if(!arg)
  {
    printf("Error allocate memory!\n");
    exit(1);
  }
  char *token;
  char *saveptr;
  token=strtok_r(line,DELIM,&saveptr);
  while(token!=NULL)
  {
	arg[counter]=token;
    counter++;
    if(counter>=size){
      size+=MAXARG;
      old_arg=arg;
      arg=realloc(arg, size * sizeof(char*));
      if(!arg)
      {
      printf("Error allocate memory!\n");
      exit(1);
	  }
	  for(int i=0;i<counter;i++)
	    arg[i]=old_arg[i];
    }
    token=strtok_r(NULL,DELIM,&saveptr);
  }
  arg[counter]=NULL;
  return arg;
}

