#include "utils.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
void cd_execute(char **args,int pid)
{
  char *path=(char*)malloc(512*sizeof(char));
  char *temp;
  int i=1;
  while(args[i]!=NULL){
	  temp=concat(args[i]," ");
	  path=concat(path,temp);
	  i++;
  }
  	path[strlen(path)-1]='\0';
	/*if (path == NULL) {
	  printf("expected argument to \"cd\"\n");
	} */ 
    if (chdir(path) != 0) {
	  printf("No such file or directory\n");
	  kill(pid,SIGTERM);
	}
}
