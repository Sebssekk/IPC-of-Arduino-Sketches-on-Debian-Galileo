#include <Arduino.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <mqueue.h>

#define  led 4
#define TOREAD "_sensor"

void signal_callback_handler(int signum);
char call_handler_command[]="./Message_Handler ";
char command[50];
int status=0;

mqd_t mqd=NULL;

mq_attr attr = { 0, //mq_flags
		10, //mq_maxmsg
		50};//mq_msgsize
char buffer[50];
char QUE_PATH[20];
unsigned int priority;

void setup()
{
  printf("\nStart Led setup... \n");
  fflush(stdout);
  signal(SIGINT, signal_callback_handler);
  pinMode(led,OUTPUT);
  strcpy(QUE_PATH,"/queue");
  strcat(QUE_PATH,TOREAD);
  strcpy(command,call_handler_command);
  strcat(command,TOREAD);
  if ((mqd = mq_open(QUE_PATH, O_CREAT | O_RDWR, 0666, &attr)) == -1)
  {
      perror("mq_open");
      exit(1);
  }
}

void loop()
{
  if (system(command)==SIGINT)
      signal_callback_handler(SIGINT);
  if (mq_receive(mqd, buffer, sizeof(buffer), &priority) == -1)
  {
      perror("mq_recieve");
      exit(1);
  }
  printf("Received (%s): %s\n", (priority == 0) ? "NORMAL" : "URGENT", buffer);
  fflush(stdout);
  if (atoi(buffer)<20 && atoi(buffer)!=0)
    digitalWrite(led,HIGH);
  else
    digitalWrite(led,LOW);
  delay(10);
}


void signal_callback_handler(int signum)
{
  printf("signal_callback_handler of LED is working...\n" );
  fflush(stdout);
  digitalWrite(led,LOW);
  mq_close(mqd);
  exit(signum);
}


