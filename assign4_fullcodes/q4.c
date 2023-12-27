#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
struct k_combats
{
    long long int *arr;
};
typedef struct k_combats k_combats;
typedef k_combats *comPtr;
comPtr create_list(int k, int m)
{
    comPtr list = (comPtr)malloc(sizeof(k_combats) * (m + 1));
    for (int i = 0; i < (m + 1); i++)
        list[i].arr = (long long int *)calloc((k + 1), sizeof(long long int));
    return list;
}
long long int get_max(comPtr list, int index, int schools, int exclude)
{
    int max = INT_MIN;
    for (int j = 1; j < schools; j++)
    {
        if (j != exclude)
        {
            int key = list[index].arr[j];
            if (key > max)
                max = key;
        }
    }
    return max;
}
void finding_max(long long int *max_array, int students, int schools, comPtr list, int exclude)
{
    for (int i = 1; i < students; i++)
    {
        max_array[i] = get_max(list, i, schools, exclude);
    }
}
void swap(long long int *a, long long int *b)
{
    long long int temp = *a;
    *a = *b;
    *b = temp;
}
int find_pivot(long long int *arr, int low, int high)
{
    int mid = low + (high - low) / 2;
    long long int a[3] = {arr[low], arr[mid], arr[high]};
    for (int i = 0; i < 2; i++)
    {
        int min_index = i;
        for (int j = i + 1; j < 2; j++)
        {
            if (a[j] < a[min_index])
                min_index = j;
        }
        swap(&a[i], &a[min_index]);
    }
    if (a[1] == arr[low])
        return low;
    if (a[1] == arr[high])
        return high;
    return mid;
}
int partition(long long int *arr, int low, int high, int pivot_index)
{
    swap(&arr[pivot_index], &arr[high]);
    int pivot = arr[high];
    int j = low - 1;
    for (int i = low; i < high; i++)
    {
        if (arr[i] < pivot)
            swap(&arr[i], &arr[++j]);
    }
    swap(&arr[j + 1], &arr[high]);
    return j + 1;
}
void quick_sort(long long int *arr, int low, int high)
{
    if (high - low == 1)
    {
        if (arr[high] < arr[low])
            swap(&arr[high], &arr[low]);
    }
    if (high > low && high - low >= 2)
    {
        int pivot_index = find_pivot(arr, low, high);
        int pivot_pos = partition(arr, low, high, pivot_index);
        quick_sort(arr, low, pivot_pos - 1);
        quick_sort(arr, pivot_pos + 1, high);
    }
}
int wins(long long int *sorted_j, long long int *max_array, int size)
{
    int count = 0;
    int start = 1;
    for (int i = 1; i < size; i++)
    {
        if (sorted_j[start] > max_array[i])
        {
            count++;
            start++;
        }
        else
        {
            for (int j = start + 1; j < size; j++)
            {
                if (sorted_j[j] > max_array[i])
                {
                    swap(&sorted_j[j], &sorted_j[i]);
                    start++;
                    count++;
                    break;
                }
            }

        }
    }
    return count;
}
int main()
{
    int t;
    scanf("%d", &t);
    while (t > 0)
    {
        int k, m;
        scanf("%d %d", &k, &m);
        // long long int *powers = (long long int *)malloc(sizeof(long long int) * (k * m + 1));
        comPtr list = create_list(k, m);
        // powers[0] = 0;
        int l = 1;
        for (int i = 1; i < ((k * m) + 1); i++)
        {
            int a;
            scanf("%d", &a);
            int x = i % k;
            if (x != 0)
                list[l].arr[x] = a;
            if (x == 0)
            {
                list[l].arr[k] = a;
                l++;
            }
           // printf("%d ", i);
        }
        int j;
        scanf("%d", &j);
        //printf("%d here", j);
        long long int *max_array = (long long int *)malloc(sizeof(long long int) * (m + 1));
        max_array[0] = 0;
        finding_max(max_array, m + 1, k + 1, list, j);
        long long int *sorted_j = (long long int *)malloc(sizeof(long long int) * (m + 1));
        sorted_j[0] = 0;
        //printf("okay \n");
        for (int i = 1; i < m + 1; i++)
        {
            sorted_j[i] = list[i].arr[j];
        }
        quick_sort(sorted_j, 0, m);
        quick_sort(max_array,0,m-1);
        //printf("wtf \n");
        // for(int i=0;i<(m+1);i++)
        // printf("%lld ",sorted_j[i]);

        // printf("\n");
        //printf("maybe \n");
        int count = wins(sorted_j, max_array, m + 1);

        printf("%d\n", count);
        t--;
    }
}