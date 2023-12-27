#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
struct marble
{
    long long int a;
    long long int b;
};
typedef struct marble marble;
typedef marble *marblePtr;
typedef marblePtr journal;
marblePtr create_marble_data(long long int n)
{
    marblePtr M = (marblePtr)malloc(sizeof(marble) * n);
    M->a = 0;
    M->b = 0;
    return M;
}
void swap(long long int *a, long long int *b)
{
    long long int temp = *a;
    *a = *b;
    *b = temp;
}
long long int get_median(long long int *array)
{
    for (long long int i = 0; i < 2; i++)
    {
        long long int min = i;
        for (long long int j = i + 1; j < 3; j++)
        {
            if (array[min] > array[j])
                min = j;
        }
        swap(&array[i], &array[min]);
    }
    return array[1];
}
long long int find_pivot_index(marblePtr M, long long int low, long long int high)
{
    long long int x = (high + low) / 2;
    long long int array[3] = {M[low].a, M[x].a, M[high].a};
    long long int med = get_median(array);
    if (med == M[x].a)
        return x;
    else if (med == M[low].a)
        return low;
    else
        return high;
}
void swap_structs(marblePtr x, marblePtr y)
{
    marble temp = *x;
    *x = *y;
    *y = temp;
}
int compare(marble M, int pivot_a, int pivot_b)
{
    if (M.a < pivot_a)
        return -1;
    else if (M.a > pivot_a)
        return 1;
    else
    {
        if (M.b < pivot_b)
            return -1;
        else if (M.b > pivot_b)
            return 1;
        else
            return 0;
    }
}
long long int partition(marblePtr M, long long int low, long long int high, long long int pivot_index)
{
    swap_structs(&M[high], &M[pivot_index]);
    long long int pivot_a = M[high].a;
    long long int pivot_b = M[high].b;
    long long int j = low - 1;

    for (long long int i = low; i < high; i++)
    {
        int x = compare(M[i], pivot_a, pivot_b);
        if (x == -1)
            swap_structs(&M[i], &M[++j]);
    }

    swap_structs(&M[j + 1], &M[high]);
    return j + 1;
}
void quick_sort(marblePtr M, long long int low, long long int high)
{
    if (high - low == 1)
    {
        int x = compare(M[low], M[high].a, M[high].b);
        if (x == 1)
            swap_structs(&M[low], &M[high]);
    }
    if (low < high && (high - low) >= 2)
    {
        long long int pivot_index = find_pivot_index(M, low, high);
        long long int pivot_position = partition(M, low, high, pivot_index);
        quick_sort(M, low, pivot_position - 1);
        quick_sort(M, pivot_position + 1, high);
    }
}
void append_journal(marblePtr M, long long int *j2, long long int n)
{
    long long int min = INT_MIN;
    for (long long int i = 0; i < n; i++)
    {
        if (M[i].a >= min && M[i].b < min)
        {
            j2[i] = M[i].a;
        }
        else if (M[i].b < M[i].a)
        {
            j2[i] = M[i].b;
        }
        else
        {
            j2[i] = M[i].a;
        }
        min = j2[i];
    }
}
int main()
{
    long long int t;
    scanf("%lld", &t);
    while (t > 0)
    {
        long long int n;
        scanf("%lld", &n);
        marblePtr M = create_marble_data(n);
        for (long long int i = 0; i < n; i++)
            scanf("%lld", &M[i].a);
        for (long long int i = 0; i < n; i++)
            scanf("%lld", &M[i].b);
        long long int *j2 = (long long int *)malloc(sizeof(long long int) * n);
        quick_sort(M, 0, n - 1);
        // for(int i=0;i<n;i++)
        // {
        //     printf("%lld %lld\n",M[i].a,M[i].b);
        // }
        append_journal(M, j2, n);
        printf("%lld %lld\n", M[n - 1].a, j2[n - 1]);
        t--;
    }
}