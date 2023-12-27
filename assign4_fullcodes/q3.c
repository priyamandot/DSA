#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
struct info
{
    int size;
    char *item;
};
typedef struct info info;
typedef info *infoPtr;
infoPtr create_list(int n)
{
    infoPtr L = (infoPtr)malloc(sizeof(info) * n);
    return L;
}
void swap_structs(infoPtr a, infoPtr b)
{
    info temp = *a;
    *a = *b;
    *b = temp;
}
int compare(info a, info b)
{
    int as = a.size;
    int bs = b.size;
    int i = 0;
    int min = as;
    if (bs < as)
        min = bs;
    for (i = 0; i < min; i++)
    {
        if (a.item[i] == b.item[i])
            continue;
        else if ((i + 1) % 2 == 0)
        {
            if ((int)a.item[i] > (int)b.item[i])
                return -1;
            else
                return 1;
        }
        else if ((i + 1) % 2 != 0)
        {
            if ((int)a.item[i] < (int)b.item[i])
                return -1;
            else
                return 1;
        }
    }
    if (i == as && as % 2 != 0)
        return -1;
    if (i == bs && bs % 2 == 0)
        return -1;
    return 1;
}
info get_median(infoPtr median)
{
    for (int i = 0; i < 2; i++)
    {
        int min = i;
        for (int j = i + 1; j < 3; j++)
        {
            int x = compare(median[i], median[j]);
            if (x == 1)
                min = j;
        }
        swap_structs(&median[i], &median[min]);
    }
    return median[1];
}
int find_pivot_index(infoPtr L, int low, int high)
{
    int mid = low + (high - low) / 2;
    info median[3] = {L[low], L[mid], L[high]};
    info med = get_median(median);
    if (med.item == L[low].item)
        return low;
    if (med.item == L[high].item)
        return high;
    else
        return mid;
}
int partition(infoPtr L, int low, int high, int pivot_index)
{
    swap_structs(&L[high], &L[pivot_index]);
    int j = low - 1;
    for (int i = low; i < high; i++)
    {
        int x = compare(L[i], L[high]);
        if (x == -1)
            swap_structs(&L[i], &L[++j]);
    }
    swap_structs(&L[j + 1], &L[high]);
    return j + 1;
}
void quick_sort(infoPtr L, int low, int high)
{
    if (high - low == 1)
    {
        int x = compare(L[low], L[high]);
        if (x == 1)
            swap_structs(&L[low], &L[high]);
    }
    if (low < high && (high - low) >= 2)
    {
        int pivot_index = find_pivot_index(L, low, high);
        int pivot_position = partition(L, low, high, pivot_index);
        quick_sort(L, low, pivot_position - 1);
        quick_sort(L, pivot_position + 1, high);
    }
}
void print_list(infoPtr L, int n)
{
    for (int i = 0; i < n; i++)
        printf("%s\n", L[i].item);
}
int main()
{
    int t;
    scanf("%d", &t);
    while (t > 0)
    {
        int n;
        scanf("%d", &n);
        infoPtr L = create_list(n);
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &L[i].size);
            L[i].item = (char *)malloc(sizeof(char) * (L[i].size + 1));
            scanf("%s", L[i].item);
        }
        quick_sort(L, 0, n - 1);
        print_list(L, n);
        t--;
    }
}