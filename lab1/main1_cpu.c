#include <stdio.h>
#include <math.h>

 
#define PI 3.14159265
#define uint unsigned int 


int main(int argc, char* argv[])
{
  const uint N = pow(10, 6);

  double array_sin[N];
  double sum_sin = 0.0;


  for(int i = 0; i < N; i++)
    array_sin[i] = sin(2*PI*i/N);
    
  for(int i = 0; i < N; i++) 
    sum_sin += array_sin[i];

  printf("Сумма sin = %2.5f\n", sum_sin);

  return 0;
}