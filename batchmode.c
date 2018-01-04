#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"

#define MAXSTR 512

char *built_instr[]={	
	"quit",
	"cd"
};


int batchmode(char *arg)
{
 // ignore_signals();	
  FILE *fp;
  int pid,wpid;
  int status,counter=0,i=0;
  /* FILE EMPTY??*/
  int len;

   fp = fopen(arg, "r");
   if( fp == NULL )  {
      perror ("Error opening file");
      return(-1);
   }
   fseek(fp, 0, SEEK_END);//get cursor at the end of file

   len = ftell(fp);//find the current position
   if(len==0){
     printf("File is empty! \n");
     kill(getpid(),SIGTERM);
   }
   fclose(fp);//close for reset

   /* EXECUTION BATCHMODE*/
  
  
  int size = MAXSTR,k=0;
  char **args;
  char *ext="";
  fp=fopen(arg,"r");
  char *line,*token,*ptr,**str,**argu;
  line=(char *)malloc(size*sizeof(char));
  str=(char **)malloc(sizeof(char *));
  while(fgets(line,MAXSTR,fp)!=NULL){
  //  printf("%s",line);
    str[i]=(char *)malloc(size*sizeof(char ));
    strcpy(str[i],line);
    i++;
    argu=(char **)realloc(str,(i+1)*sizeof(char *));
    if(argu!=NULL){
      str=argu;
    }
    else{
      free(str);
      printf("Error (re)allocating memory\n");
      exit(1);
    }
    if(feof(fp)) break;  
  }
  str[i]=NULL;
  int j=0;
  while(str[j]!=NULL){
    token=strtok_r(str[j],";",&ptr);
    while(token!=NULL){
      args=arguments(token);
      if(args[0]==NULL){
    }
      else if(strcmp(args[0],built_instr[0])==0){
        ext=built_instr[0];
        args[0]=NULL;
      }
      /*else if(strcmp(args[0],built_instr[1])==0){
        cd_execute(args,getpid());
        args[0]=NULL;
      }	  */
      pid=fork();
      if(pid==0){
        execute(args,pid);
       }else if (pid < 0) {
    // Error forking
        printf("Error forking\n");
      }
      counter++;//counting children
      token=strtok_r(NULL,";",&ptr);
   }
   while(k<=counter){
      wpid=wait(&status);
      k++;
    }
    k=0;
    counter=0;	
    if(strcmp(ext,"quit")==0){
		printf("Exiting Batch mode with 'quit'...\n");
      exit(1);
    }
    j++;
  }
}

