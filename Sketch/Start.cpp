#include <signal.h>
#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
void* func(void* s)
{
  int* int_s=(int*)s;
  switch (*int_s)
  {
    case 0: {if(system("./sensor2.elf bar foo")==SIGINT)exit(SIGINT); };break;
    case 1: {if(system("./led.elf bar foo")==SIGINT)exit(SIGINT); };break;
    case 2: {if(system("./motor.elf bar foo")==SIGINT)exit(SIGINT); };break;
  }
}
int main(int argc, char*argv[])
{
  int reader2_f=2,reader1_f=1,writer_f=0;
  printf("I'm here..\n" );
 fflush(stdout);
  pthread_t writer,reader1,reader2;
  if(pthread_create(&writer,NULL,func,&writer_f))
  {
    fprintf(stderr, "Error creating thread_writer\n");
    return 1;
  }
  if (pthread_create(&reader1,NULL,func,&reader1_f))
  {
    fprintf(stderr, "Error creating thread_reader\n");
    return 1;
  }

  if (pthread_create(&reader2,NULL,func,&reader2_f))
  {
    fprintf(stderr, "Error creating thread_reader\n");
    return 1;
  }

  if (pthread_join(writer,NULL))
  {
    fprintf(stderr, "Error joining thread_writer\n");
    return 2;
  }
  if(pthread_join(reader1, NULL))
  {
    fprintf(stderr, "Error joining thread_reader\n");
    return 2;
  }

   if(pthread_join(reader2, NULL))
  {
    fprintf(stderr, "Error joining thread_reader\n");
    return 2;
  }

  return 0;
}
