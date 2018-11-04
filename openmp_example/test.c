#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define N 1048576*64
int A[N];
int B[N];

double calc_time(struct timespec start, struct timespec end) {
  double start_sec = (double)start.tv_sec*1000000000.0 + (double)start.tv_nsec;
  double end_sec = (double)end.tv_sec*1000000000.0 + (double)end.tv_nsec;

  if (end_sec < start_sec) {
    return 0;
  } else {
    return end_sec - start_sec;
  }
};

int main(int argc, char *argv[])
{
  struct timespec start_time, end_time;
  int i;
  int sum = 0;

  for (i=0; i<N; i++) {
    A[i] = atoi(argv[1]) + i;
  } //for i

  omp_set_num_threads(atoi(argv[2]));
  clock_gettime(CLOCK_MONOTONIC, &start_time);
#pragma omp parallel for default(shared) private(i)
  for (i=0; i<N; i++) {
    B[i] = A[i] * 2;
  } //for i
  clock_gettime(CLOCK_MONOTONIC, &end_time);

  for (i=0; i<N; i++) {
    sum += B[i];
  } //for i

  printf("Result=%d\n", sum);
  double elapsed_ns = calc_time(start_time, end_time);
  printf("Time=%f\n", elapsed_ns);

  return 0;
}
