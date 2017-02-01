/* Author: Tyler Petrochko
 *
 * This is a modification of pi.c. I've removed all multiplication FLOPs
 * and some of the addition FLOPs, so that we can assume almost all of the
 * computation time is due to division FLOPs
 *
 * Ignore all output except the DivMFlop/s result.
 */
#include <stdio.h>
#include <math.h>
#include "timing.h"

#define STEPS (1000000000)
#define MILLION (1000000)
#define DIV_FLOPS_PER_SEC (1)

double f(double x){
  return (1.0 / x);
}

int main(){
  int i;
  double sum, inc, x;
  double start, end, cpu_start, cpu_end;

  // record start time
  timing(&start, &cpu_start);

  // init
  inc = 1.0 / (double) STEPS;
  x = inc / 2.0;
  sum = 0.0;

  for(i = 0; i < STEPS; i++){
    sum += f(x);
    x += inc;
  }
  timing(&end, &cpu_end);

  printf("Sin of pi is %f (should equal %f)\n", sin(4.0 * sum), 0.0);
  printf("Pi: %f\tWallclock time: %f\tCPU time: %f\tDivMFlop/s: %f\n", sum * 4.0, end - start, cpu_end - cpu_start,
      (STEPS * (double) DIV_FLOPS_PER_SEC) / (MILLION * (end - start)));
  return 0;
}

