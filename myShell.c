#include "utils.h"
#include <stdio.h>

int main(int argc,char **argv)
{
  char *str;	
  if(argc==1)
    interactive_mode();
  if(argc==2){
	str=argv[1];
    batchmode(str);
  }
}
