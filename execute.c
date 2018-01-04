#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
void execute(char **argv,int pid)
{
  if (execvp(argv[0], argv) == -1) {
	
    printf("unknown: command error\n"); 
    kill(pid,SIGTERM);
    //_exit(0);
  }
  exit(0);
}
/*
void execute(char **argv)
{
  pid_t pid,wpid;
  int status;
  int i=0,on_background=0;
  while(argv[i]!=NULL)
  {
	if(strcmp(argv[i],"&")==0){
	  argv[i]=NULL;
	  on_background=1;
	}
	i++;
  }  	
  pid = fork();
  if (pid == 0) {
    // Child process
    reset_signals();
    if(on_background==1)
    {
	  printf("pid: %d\n",getpid());
	}	
    if (execvp(argv[0], argv) == -1) {
	  printf("unknown: command error\n"); 
    }
    exit(1);
  } else if (pid < 0) {
    // Error forking
    printf("Error forking\n");
  } else {
    // Parent process
    do {
	  if(on_background==1)
      {
	    break;
	  }	
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status) && !WIFSTOPPED(status));
  }

}
*/
