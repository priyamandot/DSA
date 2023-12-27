#include <stdio.h>
#include <stdlib.h>
struct heap
{
    long long int maxSize;
    long long int heapSize;
    long long int *arr;
};
typedef struct heap heap;
typedef heap *heapPtr;
heapPtr create_heap(long long int n)
{
    heapPtr H = (heapPtr)malloc(sizeof(heap));
    H->maxSize = n;
    H->heapSize = 0;
    H->arr = (long long int *)malloc(sizeof(long long int) * n);
    return H;
}
void swap(long long int *a, long long int *b)
{
    long long int temp = *a;
    *a = *b;
    *b = temp;
}
long long int parent(long long int i)
{
    return (i - 1) / 2;
}
void insert_heap(long long int x, heapPtr H)
{
    if (H->heapSize == 0)
    {
        H->arr[H->heapSize++] = x;
        return;
    }
    long long int i = H->heapSize;
    H->arr[i] = x;
    H->heapSize++;
    while (i > 0 && H->arr[i] > H->arr[parent(i)])
    {
        swap(&H->arr[i], &H->arr[parent(i)]);
        i = (i - 1) / 2;
    }
}
long long int get_max(heapPtr H)
{
    return H->arr[0];
}
long long int find_largest(heapPtr H, long long int l, long long int r, long long int i)
{
    if (H->arr[l] > H->arr[i] && H->arr[l] >= H->arr[r])
        return l;
    if (H->arr[r] > H->arr[i] && H->arr[r] >= H->arr[l])
        return r;
    return i;
}
void fix_heap(long long int index, heapPtr H)
{
    long long int i = index;
    long long int l = 2 * i + 1;
    long long int r = 2 * i + 2;
    long long int largest = i;
    if (l < H->heapSize && r < H->heapSize)
    {
        largest = find_largest(H, l, r, i);
    }
    else if (l < H->heapSize)
    {
        if (H->arr[l] > H->arr[i])
            largest = l;
    }
    if (largest != i)
    {
        swap(&H->arr[i], &H->arr[largest]);
        fix_heap(largest, H);
    }
}
void replace(long long int index, heapPtr H)
{
    H->arr[0] = H->arr[0] - 1;
    fix_heap(0, H);
}
int main()
{
    long long int t;
    scanf("%lld", &t);
    while (t > 0)
    {
        long long int n, k;
        scanf("%lld%lld", &n, &k);
        heapPtr H = create_heap(n);
        long long int *scores = (long long int *)malloc(n * sizeof(long long int));
        for (long long int i = 0; i < n; i++)
        {
            scanf("%lld", &scores[i]);
            insert_heap(scores[i], H);
        }
        long long int score_happiness = 0;
        for (long long int i = 0; i < k; i++)
        {
            long long int x = get_max(H);
            if (x > 0)
            {
                score_happiness += x;
                replace(0, H);
            }
        }
        printf("%lld\n", score_happiness);
        t--;
    }
}