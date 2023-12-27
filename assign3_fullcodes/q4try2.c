#include<stdio.h>
#include<stdlib.h>
struct heap{
    int heapSize;
    int maxSize;
    int*arr;
};
typedef struct heap heap;
typedef heap* heapPtr;
void swap (int* a, int*b)
{
    int temp=*b;
    *b=*a;
    *a=temp;
}
heapPtr create_heap(int n)
{
    heapPtr H=(heapPtr)malloc(sizeof(heap));
    H->maxSize=n;
    H->heapSize=0;
    H->arr=(int*)calloc(n,sizeof(int));
    return H;
}
int parent(int i)
{
    return (i-1)/2;
}
int find_smallest(heapPtr H, int l, int r, int i)
{
    int res = i;
    if (H->arr[l] < H->arr[res])
        res = l;
    if (H->arr[r] < H->arr[res])
        res = r;
    return res;
}
void fix_heap(int index, heapPtr H)
{
    int i = index;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int smallest = i;
    if (l < H->heapSize && r < H->heapSize)
    {
        smallest = find_smallest(H, l, r, i);
    }
    else if (l < H->heapSize)
    {
        if (H->arr[l] < H->arr[i])
            smallest = l;
    }
    if (smallest != i)
    {
        swap(&H->arr[i], &H->arr[smallest]);
        fix_heap(smallest, H);
    }
}
void insert_heap(int x, heapPtr H)
{
    if(H->heapSize==0)
    {
        H->arr[0]=x;
        H->heapSize++;
        return;
    }
    int i=H->heapSize;
    H->arr[i]=x;
    H->heapSize++;
    while(H->arr[parent(i)]>H->arr[i])
    {
        swap(&H->arr[parent(i)],&H->arr[i]);
        int j = (i-1)/2;
        i=j;
    }
}
int get_min(heapPtr H)
{
    if(H->heapSize==1)
    {
        int min= H->arr[0];
        H->heapSize--;
        return min;
    }
    int min=H->arr[0];
    H->arr[0]=H->arr[--H->heapSize];
    fix_heap(0,H);
    return min;
}
int main()
{
    int n;
    scanf("%d",&n);
    heapPtr H=create_heap(n);
    int* input=(int*)malloc(sizeof(int)*n);
    for(int i=0;i<n;i++)
    {
        scanf("%d",&input[i]);
        insert_heap(input[i],H);
    }
    int* sorted=(int *)malloc(sizeof(int)*n);
    for(int i=0;i<n;i++)
    {
        sorted[i]=get_min(H);
    }
      for(int i=0;i<n;i++)
    {
        if(i==0 && sorted[0]==input[0])
        swap(&sorted[0],&sorted[1]);
        else if(i==n-1 && sorted[i]==input[i])
        swap(&sorted[i-1],&sorted[i]);
        else if(sorted[i]==input[i])
        swap(&sorted[i+1],&sorted[i]);
    }
    for(int i=0;i<n;i++)
    printf("%d ",sorted[i]);
    printf("\n");
    free(H->arr);
    free(sorted);
    free(input);
}