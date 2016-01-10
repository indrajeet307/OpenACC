#include<stdio.h>
#include<sys/time.h>
#include<stdlib.h>

void scount(int *A,unsigned int size,int *count)
{
    for(int i=0;i<size;i++)
    {
        if(A[i]/2 == 0) (*count)++;
    }
}

int pcount(int *A,int size)
{
    int count = 0;
    #pragma acc enter data copyin(A[0:size])
    #pragma acc data present(A[0:size])
    #pragma acc parallel loop reduction(+:count)
    for(int i=0;i<size;i++)
    {
        if(A[i]/2 == 0) count++;
    }
    return count;
}
void initMat(int *p, int size)
{
    
    for(int i=0;i<size;i++)
        p[i] = rand() % 1000;
}

int main()
{
    int *arr;
    int count = 0;
    unsigned int size = 5000*5000;
   struct timeval ptimes,ptimee,ptimed,stimes,stimee,stimed;   
    arr = (int*) malloc (sizeof(int) * size);

    initMat(arr,size);
    gettimeofday(&stimes, NULL);
        scount(arr,size,&count);
    gettimeofday(&stimee, NULL);

    printf("Count : %d\n",count);
    count = 0;

    gettimeofday(&ptimes, NULL);
        count = pcount(arr,size);
    gettimeofday(&ptimee, NULL);

    printf("Count : %d\n",count);

    timersub(&stimee,&stimes,&stimed);
    timersub(&ptimee,&ptimes,&ptimed);

    printf("Sequential time : %f. \n",stimed.tv_sec*1000.0 + stimed.tv_usec/1000.0);
    printf("Parallel time : %f. \n",ptimed.tv_sec*1000.0 + ptimed.tv_usec/1000.0);

    return 0;
}
