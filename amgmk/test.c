#include <stdio.h>
#include <stdlib.h>

extern void Timer_Start(char *);
extern void Timer_Stop(char *);
extern void Timer_Print();

int main(int argc, char *argv[])
{
  Timer_Start("whole_program");

  for (int i=0; i < 100; i++) {
    Timer_Start("block1");
    printf("Hello\n");
    Timer_Stop("block1");

    Timer_Start("block2");
    printf("World!\n");
    Timer_Stop("block2");
  }

  Timer_Stop("whole_program");

  Timer_Print();
  return 0;
}
