/*
 * Code finds the summation of 1/n in the range 0 to MAX_NUM and reverse, both
 * sequentially and parallels
 * */
#include<stdio.h>
#define MAX_NUM 50000
float straight()
{
    int i=0;
    float sum=0;
    for(i=1;i<=MAX_NUM;i++)
    {
        sum+=1/(i*1.0);
    }
    printf("Summation is %f.\n",sum);
    return sum;
}

float reverse()
{
    int i=0;
    float sum=0;
    for(i=MAX_NUM;i>0;i--)
    {
        sum+=1/(i*1.0);
    }
    printf("Reverse Summation is %f.\n",sum);
    return sum;
}
float pstraight()
{
    int i=0;
    float sum=0;
    #pragma acc kernels 
    #pragma acc loop independent reduction(+:sum)
    for(i=1;i<=MAX_NUM;i++)
    {
        sum+=1/(i*1.0);
    }
    printf("Parallel Summation is %f.\n",sum);
    return sum;
}

float preverse()
{
    int i=0;
    float sum=0;
    #pragma acc kernels 
    #pragma acc loop independent reduction(+:sum)
    for(i=MAX_NUM;i>0;i--)
    {
        sum+=1/(i*1.0);
    }
    printf("Parallel Reverse Summation is %f.\n",sum);
    return sum;
}
int main()
{
   straight();
   reverse();
   pstraight();
   preverse();
   return 0;
}
