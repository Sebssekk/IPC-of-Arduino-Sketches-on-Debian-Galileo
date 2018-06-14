
#include <Arduino.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int echo= 3; // Echo Pin
int trig=2; // Trigger Pin

#define TOSEND "_sensor"

void signal_callback_handler(int signum);
void itostr(long num,char num_char[]);

int status=0;
char call_handler_command[]="./Message_Handler ";
char command[50];
char num_char[10];
long  distance=0; // Duration used to calculate distance
char str[80];

void setup() {
 printf("Ultrasonic sensor in the setup...\n");
 fflush(stdout);
 signal(SIGINT, signal_callback_handler);
 pinMode(trig, OUTPUT_FAST);
 pinMode(echo, INPUT_FAST);
 printf("Ultrasonic sensor, pins setted..\n");
 fflush(stdout);
}

void loop() {
 printf("Ultrasonic sensor, starting the loop...\n");
 fflush(stdout);
 fastDigitalWrite(trig, LOW);
 delayMicroseconds(2);
//Sending a high pulse to trigger the Ultrasound Module
 fastDigitalWrite(trig, HIGH);
 delayMicroseconds(10); // tringging for 10 us

 fastDigitalWrite(trig, LOW);
 distance= pulseIn(echo, HIGH)/58.0; //receive the pulse back

 printf("Distance: %ld\n",distance);
 fflush(stdout);
 // Sending the distance to shared memory
 strcpy(command,call_handler_command);
 strcat(command,TOSEND);
 strcat(command," ");
 itostr(distance,num_char);
 strcat(command,num_char);
 printf("I,m node_sensor and i,ve written: %s\n",command);
 fflush(stdout);
 status= system(command);
 if (status==SIGINT)
    signal_callback_handler(SIGINT);
 //Delay for next reading.
 delayMicroseconds(30);
}

void signal_callback_handler(int signum)
{
  // Clean Shared region //
  printf("signal_callback_handler is working...\n" );
  strcpy(command,call_handler_command);
  strcat(command,TOSEND);
  strcat(command," ");
  strcat(command,"d");
  system(command);
  exit(signum);
}

void itostr(long num,char num_char[])
{
  printf("itostr is working with %ld\n",num);
  if (!num)
  {
    num_char[0]='0';
    num_char[1]='\0';
    return;
  }
  fflush(stdout);
  char dict[]={'0','1','2','3','4','5','6','7','8','9'};
  int e=0,i=0,x=0;
  char num_char1[10];
  while(num)
  {
    x=num%10;
    num_char1[i]=dict[x];
    num/=10;
    i+=1;
  }
  for (e=0;e<i;e++)
  {
    num_char[e]=num_char1[i-1-e];
  }
  num_char[e]='\0';
}

