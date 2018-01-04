#include <stdio.h>
#include <string.h>
#include "utils.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAXSTR 512

#define DELIM " \t\n\r\a"
char *built_in_str[]={	
	"quit",
	"cd"
};

int interactive_mode()
{
  //ignore_signals();
  int pid,wpid;
  int status,counter=0,i=0;
  char **args;
  char *ext="";
  char *line,*token,*ptr;
  while(1)
  {
    printf("kasparidis_8157> ");  
    line = read_line(stdin);
    token=strtok_r(line,";",&ptr);
    while(token!=NULL){
      args=arguments(token);
      if(args[0]==NULL){
      }
      else if(strcmp(args[0],built_in_str[0])==0){
        ext=built_in_str[0];
        args[0]=NULL;
      }
      /*else if(strcmp(args[0],built_in_str[1])==0){
        cd_execute(args,getpid());
        args[0]=NULL;
      }	  */
      pid=fork();
      if (pid == 0) {
		execute(args,pid);
      }else if (pid < 0) {
    // Error forking
        printf("Error forking\n");
      }
      counter++;
      token=strtok_r(NULL,";",&ptr);
    }
    while(i<=counter){
      wpid=wait(&status);
      i++;
    }	
    if(strcmp(ext,"quit")==0){
	  printf("Exiting ...\n");

      exit(1);
    }
  }
}


