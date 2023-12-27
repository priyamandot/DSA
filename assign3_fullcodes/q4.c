#include<stdio.h>
#include<stdlib.h>
void swap(int *a, int *b)
{
     int temp = *a;
    *a = *b;
    *b = temp;
}
int main()
{
    int n;
    scanf("%d",&n);
    int* arr= (int*)malloc(sizeof(int)*n);
    int* frequency=(int*)calloc((1e6+1),sizeof(int));
    for(int i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
        frequency[arr[i]]++;
    }
    int* sorted=(int*)malloc(sizeof(int)*n);
    int k=0;
    for(int i=0;i<(1e6+1) && k<n;i++)
    {
        if(frequency[i]>0)
        {
            sorted[k]=i;
            k++;
        }
    }
    for(int i=0;i<n;i++)
    {
        if(i==0 && sorted[0]==arr[0])
        swap(&sorted[0],&sorted[1]);
        else if(sorted[i]==arr[i])
        swap(&sorted[i+1],&sorted[i]);
    }
    for(int i=0;i<n;i++)
    printf("%d ",sorted[i]);
    printf("\n");
}