#include <stdio.h>
#include <stdlib.h>

void reverseString(char *str, int length);
int *uniqueElements(int *arr, int length);
char *compressString(char *str, int length);
int **transpose(int **matrix, int NumRow, int NumCol);
int j, f;

void reverseString(char *str, int length)
{
    int start = 0, end = length - 1;
    for (int i = 0; i < length / 2; i++)
    {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}
int *uniqueElements(int *arr, int length)
{
    int *unique_arr = (int *)malloc(length * sizeof(int));
    int *num_arr=(int*)malloc(10001*sizeof(int));
    for(int i=0;i<10001;i++)
    {
        num_arr[i]=-1;
    }
    j = 0;
    
    for (int i = 0; i < length; i++)
    {
        if(num_arr[arr[i]]==-1)
        {
            unique_arr[j] = arr[i];
            num_arr[arr[i]]=-2;
            j++;
        }
    }
    free(num_arr);
    // printf("\n");
    return unique_arr;
}
char *compressString(char *str, int length)
{
    char *cmpres_string = (char *)malloc((2 * length) * sizeof(char));
    f = 0;
    int count, c1;
    // char buffer[10000];
    for (int i = 0; i < length; i = i + c1)
    {
        count = 0;
        cmpres_string[f] = str[i];
        for (int m = i; m < length; m++)
        {
            if (str[i] != str[m])
                break;
            if (str[i] == str[m])
                count++;
        }
        int c = count, digits = 0, r;
        c1 = count;
        while (count > 0)
        {
            digits++;
            count = count / 10;
        }
        for (int g = 0; g < digits; g++)
        {
            r = c % 10;
            cmpres_string[f + digits - g] = r + 48;
            c = c / 10;
        }

        // cmpres_string[f + 1] = count+48;
        f = f + digits + 1;
    }
    return cmpres_string;
}
int **transpose(int **matrix, int NumRow, int NumCol)
{
    int **transposed_matrix = (int **)malloc(NumCol * sizeof(int *));
    for (int i = 0; i < NumCol; i++)
    {
        transposed_matrix[i] = (int *)malloc(NumRow * sizeof(int));
        // assert(transposed_matrix!=NULL);
    }
    for (int r = 0; r < NumRow; r++)
    {
        for (int c = 0; c < NumCol; c++)
        {
            transposed_matrix[c][r] = matrix[r][c];
        }
    }
    for (int h = 0; h < NumRow; h++)
    {
        free(matrix[h]);
    }
    free(matrix);
    return transposed_matrix;
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t != 0)
    {
        char choice[5];
        scanf("%s", choice);
        if (choice[4] == '1')
        {
            int length1;
            scanf("%d", &length1);
            // char* str1=(char*)malloc(length1*sizeof(char));
            char str[length1+1];
            for (int i = 0; i < length1+1; i++)
            {
                scanf("%c", &str[i]);
            }
            ;
            reverseString(str, length1+1);
            for (int i = 0; i < length1+1; i++)
            {
                printf("%c", str[i]);
            }
            printf("\n");
        }
        if (choice[4] == '2')
        {
            int n;
            scanf("%d", &n);
            char str[n];
            scanf("%s", str);
            char *result;
            result = compressString(str, n);
            for (int i = 0; i < f; i++)
            {
                printf("%c", result[i]);
            }
            printf("\n");
            free(result);
        }
        if (choice[4] == '3')
        {
            int n;
            scanf("%d", &n);
            int arr[n];
            for (int i = 0; i < n; i++)
            {
                scanf("%d", &arr[i]);
            }
            int *p;
            p = uniqueElements(arr, n);
            for (int i = 0; i < j; i++)
            {
                printf("%d ", p[i]);
            }
            printf("\n");
            free(p);
        }

        if (choice[4] == '4')
        {
            int r, c;
            scanf("%d %d", &r, &c);
            int **matrix = (int **)malloc(r * sizeof(int *));
            for (int i = 0; i < r; i++)
            {
                matrix[i] = (int *)malloc(c * sizeof(int));
                // assert(transposed_matrix!=NULL);
            }

            for (int i = 0; i < r; i++)
            {
                for (int k = 0; k < c; k++)
                {
                    scanf("%d", &matrix[i][k]);
                }
            }

            int **result;
            result = transpose(matrix, r, c);
            for (int i = 0; i < c; i++)
            {
                for (int k = 0; k < r; k++)
                {
                    printf("%d ", result[i][k]);
                }
                printf("\n");
            }
            for (int h = 0; h < c; h++)
            {
                free(result[h]);
            }
            free(result);
        }
        t--;
    }
}