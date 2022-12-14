#include <stdio.h>
#include <math.h>

 
#define PI 3.14159265
#define uint unsigned int 

int main()
{
  const uint N = pow(10, 6);
  double array_sin[N];
  double sum_sin = 0.0;
  // float array_sin[N];
  // float sum_sin = 0.0;

  // pragma acc - показывает компилятору что это код для OpenACC
  // data - указывается перед действиями с данными
  // create - создает пространство для перечисленных переменных и освобождает его в конце области, но не копирует на устройство или с него.
  // copy - создает пространство для перечисленных переменных на устройстве, инициализируйте переменную, скопировав данные на устройство в начале области, 
  // копирует результаты обратно на хост в конце области и, наконец, освободит место на устройстве, когда закончит.
  #pragma acc data create(array_sin) copy(sum_sin)
   {
    // kernels - распараллеливание цикла на усмотрение компилятора. (Окружает циклы, которые должны выполняться на устройстве, обычно в виде последовательности операций ядра.)
    #pragma acc kernels 
    for(int i = 0; i < N; i++)
      array_sin[i] = sin(2*PI*i/N);
    // loop reduction - распараллеливания цикла с сокращением 
    // (Частная копия каждой переменной, массива или подмассива в списке выделяется для каждого потока, который выполняет цикл или циклы.
    // Значения для всех потоков объединяются оператором в конце циклов.)
    // т.е. в нашем случае массив синусов разделяется на части, каждая часть складывается внутри себя, а потом все части складываются между собой. 
    #pragma acc kernels loop reduction(+:sum_sin)
    for(int i = 0; i < N; i++)
      sum_sin += array_sin[i];

   }

  printf("Сумма sin = %2.5f\n", sum_sin);

  return 0;
}
