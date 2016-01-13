#include<stdio.h>
#include<sys/time.h>
#include<stdlib.h>

double seqmul(float* A,float* B,float *C ,int AW,int AH,int BW)
{
    for(int i=0;i<AH;i++){
        for(int j=0;j<BW;j++){
            float sum=0;
            for(int k=0;k<AW;k++){ 
                float a =  A[ i * AW + k] ;
                float b =  B[ k * BW + j];
                sum += a * b;
            }
            C[i*BW+j] = sum;
            
        }
    }
    return 0;
}

double pmul(float* A,float* B,float *C,int wA,int hA,int wB)
{

    #pragma acc enter data copyin(A[0:hA * wA],B[0:wA * wB])
    #pragma acc enter data create(C[0:hA * wB])
  
    #pragma acc data present(A[0:hA * wA], B[0:wA * wB], C[0:hA * wB])
    #pragma acc kernels loop independent
    for (unsigned int i = 0; i < hA; ++i) {
        #pragma acc loop independent
        for (unsigned int j = 0; j < wB; ++j) {
            float sum = 0;
            for (unsigned int k = 0; k < wA; ++k) {
                float a = A[i * wA + k];
                float b = B[k * wB + j];
                sum += a * b;
            }
            C[i * wB + j] = sum;
        }
    }
    #pragma acc exit data copyout(C[0:hA * wB])
    #pragma acc exit data delete(A[0:hA * wA],B[0:wA * wB])
    return 0;
}

void initMat(float *p, int size)
{
    
    for(int i=0;i<size;i++)
        p[i] = rand() % 10;
}

int main()
{
   /*
    * Generate random 1024*1024 matrix
    * Compare times in seq and parallel implementation
    * */ 
   float *MA,*MB,*MC;
   struct timeval ptimes,ptimee,ptimed,stimes,stimee,stimed;   
   //int MA[]={2,2,2,2,2,2,2,2}; 
   //int MB[]={2,2,2,2,1,1,1,1}; int MC[]={0,0,0,0,0,0,0,0};
   unsigned int AW=1000,AH=1000;
   unsigned int BW=1000,BH=1000;
   unsigned int CW=1000,CH=1000;

   MA = (float*) malloc(sizeof(float) * AW * AH);
   MB = (float*) malloc(sizeof(float) * BW * BH);
   MC = (float*) malloc(sizeof(float) * CW * CH);

   initMat(MA, AW * AH);
   initMat(MB, BW * BH);

   gettimeofday(&stimes, NULL);
   seqmul(MA,MB,MC,AW,AH,BW);
   gettimeofday(&stimee, NULL);

   gettimeofday(&ptimes, NULL);
   pmul(MA,MB,MC,AW,AH,BW);
   gettimeofday(&ptimee, NULL);

    timersub(&stimee,&stimes,&stimed);
    timersub(&ptimee,&ptimes,&ptimed);

    printf("Sequential time : %f. \n",stimed.tv_sec*1000.0 + stimed.tv_usec/1000.0);
    printf("Parallel time : %f. \n",ptimed.tv_sec*1000.0 + ptimed.tv_usec/1000.0);

    return 0;
}
