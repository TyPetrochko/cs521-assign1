#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "timing.h"
#include "dummy.h"

#define MILLION (1000000)

void benchmark(int N);
void init_rand(float *vector, int size); 

int main (int argc, char **argv) {
  int N;

  printf("N\tLength\tIter.\tWall\tCPU\tMFlop/s\n");

  for (N = 3; N <= 24; N++)
    benchmark(N);
}

void benchmark(int N){
  float *a, *b, *c, *d;
  int size;

  // this might have typecasting issues
  size = floor(pow(2.1, (float) N));

  a = malloc(sizeof(float) * size); 
  b = malloc(sizeof(float) * size); 
  c = malloc(sizeof(float) * size); 
  d = malloc(sizeof(float) * size);

  init_rand(a, size); // why not
  init_rand(b, size);
  init_rand(c, size);
  init_rand(d, size);

  int repeat, r, i;
  double start, end, cpu_start, cpu_end, runtime;
  
  runtime = 0.0;

  repeat = 1;
  for(; runtime < 1.0; repeat *= 2){
    // record start time
    timing(&start, &cpu_start);

    for(r = 0; r<repeat; ++r){
      // vector kernel
      for(i = 0; i < size; i++)
        a[i] = b[i] + c[i] * d[i];

      // don't let compiler remove this iteration
      if(a[N>>1]<0.0) dummy(a);
    }
    timing(&end, &cpu_end);
    runtime = end - start;
  }
  repeat /= 2;

  float mflops = (2.0 * size * repeat) / ((end - start) * MILLION);
  printf("%d\t%d\t%d\t%f\t%f\t%f\n", N, size, repeat, end - start, cpu_end - cpu_start, mflops);
}

void init_rand(float *vector, int size){
  float drand_max = 100.0 / (double) RAND_MAX;
  int i;
  for(i = 0; i < size; i++) 
    vector[i] = drand_max * (double) rand();
}

