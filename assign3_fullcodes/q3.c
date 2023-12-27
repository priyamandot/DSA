#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
struct node
{
    long long int moves;
    long long int sum;
};
typedef struct node node;
typedef node *nodePtr;

struct heap
{
    int maxSize;
    int heapSize;
    long long int *neg_arr;
};
typedef struct heap heap;
typedef heap *heapPtr;

heapPtr create_heap(int size)
{
    heapPtr H = (heapPtr)malloc(sizeof(heap));
    H->maxSize = size;
    H->heapSize = 0;
    H->neg_arr = (long long int *)malloc(size * sizeof(long long int));
    return H;
}

nodePtr create_storage_node()
{
    nodePtr N = (nodePtr)malloc(sizeof(node));
    N->moves = 0;
    N->sum = 0;
    return N;
}

void add(long long int x, nodePtr store)
{
    store->moves = store->moves + 1;
    store->sum = store->sum + x;
}

void subtract(long long int x, nodePtr store)
{
    store->moves = store->moves -1;
    store->sum = store->sum - x;
}
void swap(long long int *a, long long int *b)
{
    long long int temp = *a;
    *a = *b;
    *b = temp;
}
int parent(int i)
{
    return (i - 1) / 2;
}

void insert_heap(long long int x, heapPtr H)
{
    if (H->heapSize == H->maxSize)
    {
        // printf("overflow/n");
        return;
    }
    int i = H->heapSize;
    H->neg_arr[i] = x;
    H->heapSize++;
    while (i > 0 && H->neg_arr[parent(i)] > H->neg_arr[i])
    {
        swap(&(H->neg_arr[parent(i)]), &H->neg_arr[i]);
        i = (i - 1) / 2;
    }
}
int find_smallest(heapPtr H, int l, int r, int i)
{
    int res = i;
    if (H->neg_arr[l] < H->neg_arr[res])
        res = l;
    if (H->neg_arr[r] < H->neg_arr[res])
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
        if (H->neg_arr[l] < H->neg_arr[i])
            smallest = l;
    }
    if (smallest != i)
    {
        swap(&H->neg_arr[i], &H->neg_arr[smallest]);
        fix_heap(smallest, H);
    }
}
long long int remove_min(heapPtr H)
{
    if (H->heapSize == 1)
    {
        long long int min= H->neg_arr[0];
        H->heapSize--;
        return min;
    }
    int min= H->neg_arr[0];
    H->neg_arr[0] = H->neg_arr[H->heapSize - 1];
    H->heapSize--;

    fix_heap(0, H);
    return min;
}
int main()
{
    long long int n;
    scanf("%lld", &n);

    long long int arr[n];

    // input
    nodePtr store = create_storage_node();

    // int count_negative = 0;
    int first_positive_index;
    int flag = 0;
    for (int i = 0; i < n; i++)
    {
        scanf("%lld", &arr[i]);
        if (flag == 0 && arr[i] >= 0)
        {
            first_positive_index = i;
            flag = 1;
        }
        // if (arr[i] < 0 && flag == 1)
        // {
        //     count_negative++;
        // }
    }

    heapPtr H = create_heap(n);

    for (int i = first_positive_index; i < n; i++)
    {
        insert_heap(arr[i], H);
        add(arr[i],store);
        //if (store->sum > 0)
        if (store->sum < 0)
        {
            long long int x=remove_min(H);
            subtract(x,store);
        }
    }
    // for (int i = 0; i < H->heapSize; i++)
    // {
    //     // printf("%lld ",H->neg_arr[i]);
    // }
    // printf("\n");
    // for (int i = 0; i < H->maxSize; i++)
    // {
    //     // printf("%d\n",H->heapSize);
    //     if (H->heapSize == 0)
    //         break;
    //     long long int x = H->neg_arr[0];
    //     if (store->sum + x < 0)
    //     {
    //         // printf("1\n");
    //         break;
    //         // continue;
    //     }
    //     if (store->sum + x >= 0)
    //     {
    //         store->sum = store->sum + x;
    //         store->moves++;
    //     }
    //     remove_min(H);
    // }
    // printf("ans\n");
    printf("%lld\n", store->moves);
}