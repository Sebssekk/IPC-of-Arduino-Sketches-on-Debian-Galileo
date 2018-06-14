#include <Arduino.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <mqueue.h>
#include <Motor.h>

#define TOREAD "_sensor"

int EN1=7,ctrl11=6,ctrl01=5;
int EN2=12,ctrl12=11,ctrl02=10;

void signal_callback_handler(int signum);

Motor motor1(EN1,ctrl11,ctrl01);
Motor motor2(EN2,ctrl12,ctrl02);
char call_handler_command[]="./Message_Handler ";
char command[50];

mqd_t mqd=NULL;

mq_attr attr = { 0, //mq_flags
                10, //mq_maxmsg
                50};//mq_msgsize
char buffer[50];
char QUE_PATH[20];
unsigned int priority;

void setup()
{
  printf("\nStart motor setup... \n");
  fflush(stdout);
  motor1.setUp();
  motor1.enable(1);
  motor2.setUp();
  motor2.enable(1);
  signal(SIGINT, signal_callback_handler);
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
    {
      motor1.go_backward(255);
      motor2.go_backward(255);
    }
   
  else
    {
      motor1.go_ahead(255);
      motor2.go_ahead(255);
    }
  delay(10);
}

void signal_callback_handler(int signum)
{
  printf("signal_callback_handler of MOTOR is working...\n" );
  fflush(stdout);
  motor1.enable(0);
  motor2.enable(0);
  mq_close(mqd);
  exit(signum);
}

