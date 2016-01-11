#include<stdio.h>
#include<stdlib.h>
void initArr(float *arr, int N)
{
    for(int i=0; i < N; i++)
    arr[i] = rand() % 400 / (1 + rand() % 750 );
}

int main()
{
    float *vecx,*vecy;
    int size = 4000;

    
    //#pragma acc data pcreate(vecx[0:size]) pcopyout(vecy[0:size])
    #pragma acc data pcreate(vecx) pcopyout(vecy)
    {
        #pragma acc parallel loop
        for(int i=0; i<size; i++)
        {
            vecy[i] = 0.0f;
            vecx[i] = (float)(i+1);
        }
        
        #pragma acc parallel loop
        for(int i=0;i<size;i++)
        {
            vecy[i] = 2.0f * vecx[i] + vecy[i];
        }
    }

    return 0;
}

/* Changes observed 
 * 1. change line 15 #pragma acc data 
 * Compiler gives
 *pgcc -g -Minfo -acc -pg Trial.c -o trial.out
 * main:
 * 17, Accelerator kernel generated
 * Generating Tesla code
 * 18, #pragma acc loop gang, vector(128)  blockIdx.x threadIdx.x
 * 17, Generating copyout(vecy[:4000],vecx[:4000])
 * 24, Accelerator kernel generated
 * Generating Tesla code
 * 25, #pragma acc loop gang, vector(128)  blockIdx.x threadIdx.x 
 * 24, Generating copy(vecy[:4000])
 * Generating copyin(vecx[:4000])
 *
 * 2. change line 15
 *   #pragma acc data pcreate(vecx[0:size]) pcopyout(vecy[0:size])
 *pgcc -g -Minfo -acc -pg Trial.c -o trial.out
 *  main:
 *  17, Accelerator kernel generated
 *  Generating Tesla code
 *  18, #pragma acc loop gang, vector(128)  blockIdx.x threadIdx.x 
 *  17, Generating copyout(vecy[:4000],vecx[:4000])
 *  24, Accelerator kernel generated
 *  Generating Tesla code
 *  25, #pragma acc loop gang, vector(128)  blockIdx.x threadIdx.x 
 *  24, Generating copy(vecy[:4000])
 *  Generating copyin(vecx[:4000])
 * */
    
