#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include "itostr.h"

#define MYID "00"

char* TOSEND[]={"01","02"};

char* call_handler_command="./Message_Handler ";
char command[30];
char num_char[10];

void signal_callback_handler(int signum)
{
  printf("signal_callback_handler is working...\n" );
  strcpy(command,call_handler_command);
  strcat(command,MYID);
  strcat(command," ");
  strcat(command,"d");
  int status=system(command);
  exit(signum);
}

int main (int argc, char* argv[])
{
  srand(time(NULL));
  int status=0,x=0;

  signal(SIGINT, signal_callback_handler);

  strcpy(command,call_handler_command);
    while (1)
    {
      sleep(2);
      int i = rand()%2;
      x+=10;
      strcat(command,TOSEND[i]);
      strcat(command," ");
      itostr(x,num_char);
      strcat(command,num_char);
      status= system(command);
      printf("I,m node1 and i've written: %s\n",command );
      command[18]='\0';
      if (x>150)
        break;
    }
  signal_callback_handler(SIGINT);
  return 0;
}
