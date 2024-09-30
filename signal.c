#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t got_alarm = 0;

void handler(int signum)
{ 
  printf("Hello World!\n");
  got_alarm = 1;
  alarm(5); // Schedule next alarm
}

int main(int argc, char * argv[])
{
  signal(SIGALRM, handler);
  alarm(5); // Schedule first alarm

  while(1) {
    if (got_alarm) {
      printf("Turing was right!\n");
      got_alarm = 0;
    }
  }

  return 0; // This line will never be reached
}