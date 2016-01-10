#include<stdio.h>
#include<sys/time.h>
#include<stdlib.h>
#include<sys/time.h>
double seqAdd(float* A,float* B,float* C ,float size)
{
    for(int i=0;i<size;i++)
        C[i] = A[i] + B[i];
    return 0;
}
/*
double pAdd(float* A,float* B,float* C ,float size)
{
    #pragma acc enter data copyin(A[0:size],B[0:size])
    #pragma acc enter data create(C[0:size])
    #pragma acc kernels loop present(A[0:size],B[0:size],C[0:size]) independent
    for(int i=0;i<size;i++)
        C[i] = A[i] * B[i];
    #pragma acc exit data copyout(C[0:size])
    #pragma acc exit data delete(A[0:size],B[0:size])
    return 0;
}*/

double pAdd(float* A,float* B,float* C ,float size)
{
    #pragma acc kernels
    {
    #pragma acc enter data create(C[0:size])
    for(int i=0;i<size;i++)
        C[i] = A[i] * B[i];
    }
    return 0;
}
void initMat(float *p, float size)
{
    
    for(int i=0;i<size;i++)
        p[i] = (rand() % 1000)/(1+ (rand()% 300));
}

float main()
{
   /*
    * Generate random 1024*1024 matrix
    * Compare times in seq and parallel implementation
    * */ 
   struct timeval startseq,endseq,startp,endp,dseq,dp;
   float *MA,*MB,*MC,*PC;
   float size=5000*5000; 
   MA = (float*) malloc(sizeof(float) * size);
   MB = (float*) malloc(sizeof(float) * size);
   MC = (float*) malloc(sizeof(float) * size);
   PC = (float*) malloc(sizeof(float) * size);

   initMat(MA, size);
   initMat(MB, size);

    gettimeofday(&startseq,NULL);
   seqAdd(MA,MB,MC,size);
    gettimeofday(&endseq,NULL);

    gettimeofday(&startp,NULL);
   pAdd(MA,MB,MC,size);
    gettimeofday(&endp,NULL);
   
   timersub(&endp,&startp,&dp);
   timersub(&endseq,&startseq,&dseq);
   printf(" %f\n", dp.tv_sec*1000.0+dp.tv_usec/1000.0);
   printf(" %f\n", dseq.tv_sec*1000.0+dseq.tv_usec/1000.0);
    return 0;
}
