#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <mqueue.h>

#define MYID "01"

char* call_handler_command="./Message_Handler ";
char command[30];

mqd_t mqd;

void signal_callback_handler(int signum)
{
  printf("signal_callback_handler is working...\n" );
  strcpy(command,call_handler_command);
  strcat(command,MYID);
  strcat(command," ");
  strcat(command,"d");
  int status=system(command);
  mq_close(mqd);
  exit(signum);
}

int main (int argc, char* argv[])
{
  int status=0,x=0;

  signal(SIGINT, signal_callback_handler);

  struct mq_attr attr = {.mq_maxmsg = 10, .mq_msgsize = 50};
  char buffer[attr.mq_msgsize];
  char QUE_PATH[15];
  strcpy(QUE_PATH,"/queue");
  strcat(QUE_PATH,MYID);
  strcpy(command,call_handler_command);
  strcat(command,MYID);
  int priority;
  if ((mqd = mq_open(QUE_PATH, O_CREAT | O_RDWR, 0666, &attr)) == -1)
  {
      perror("mq_open");
      exit(1);
  }

    while (1)
    {
      sleep(1);
      status=system(command);
      if (mq_receive(mqd, buffer, sizeof(buffer), &priority) == -1)
      {
          perror("mq_recieve");
          exit(1);
      }
      printf("Received (%s): %s\n", (priority == 0) ? "NORMAL" : "URGENT", buffer);
      if (atoi(buffer)>130)
        break;
    }
  signal_callback_handler(1);
  return 0;
}
