#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

volatile sig_atomic_t got_alarm = 0;
volatile sig_atomic_t program_running = 1;
time_t start_time;
int alarm_count = 0;

void alarm_handler(int signum)
{ 
  printf("Hello World!\n");
  got_alarm = 1;
  alarm_count++;
  alarm(1); // Schedule next alarm every second
}

void sigint_handler(int signum)
{
  time_t end_time = time(NULL);
  double elapsed_time = difftime(end_time, start_time);
  printf("\nProgram executed for %.0f seconds.\n", elapsed_time);
  printf("Number of alarms: %d\n", alarm_count);
  exit(0);
}

int main(int argc, char * argv[])
{
  start_time = time(NULL);

  signal(SIGALRM, alarm_handler);
  signal(SIGINT, sigint_handler);
  
  alarm(1); // Schedule first alarm

  while(program_running) {
    if (got_alarm) {
      printf("Turing was right!\n");
      got_alarm = 0;
    }
  }

  return 0; // This line will never be reached
}