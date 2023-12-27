#include <stdio.h>
#include <stdlib.h>
#include<limits.h>
int *intersectionArray(int *arr1, int *arr2, int lenArr1, int lenArr2);
int countCharOccurrences(const char *str, int length, char ch);
char findFirstNonRepeatingChar(const char *str, int length);
char *findLongestCommonPrefix(char **strs, int numStr, int maxLen);
int *maxMin(int *arr, int lenArr);
void sort(int *arr, int len);
char *removeSubstring(char *str, int strLength, const char *substr, int substrLength);
int size, min;
int ind, k_maxmin,k_remove;


int *intersectionArray(int *arr1, int *arr2, int lenArr1, int lenArr2)
{
    
    // min=101;
    int num_arr1[10001];
    for (int i = 0; i < 10001; i++)
    {
        num_arr1[i] = 0;
    }
    int num_arr2[10001];
    for (int i = 0; i < 10001; i++)
    {
        num_arr2[i] = 0;
    }
    for (int i = 0; i < lenArr1; i++)
    {
        num_arr1[arr1[i]] = num_arr1[arr1[i]] + 1;
    }
    for (int i = 0; i < lenArr2; i++)
    {
        num_arr2[arr2[i]] = num_arr2[arr2[i]] + 1;
    }
    //int min = (lenArr1 <= lenArr2) ? lenArr1 : lenArr2;
    size = 0;
    for (int i = 0; i < 10001; i++)
    {
        if (num_arr1[i] <= num_arr2[i])
            size = size + num_arr1[i];
        if (num_arr1[i] > num_arr2[i])
            size = size + num_arr2[i];
    }
    int *intersec_arr = (int *)malloc(size * sizeof(int));
    int j = 0;
    for (int i = 0; i < 10001; i++)
    {
        if (num_arr1[i] <= num_arr2[i])
        {
            for (int h = 0; h < num_arr1[i]; h++)
            {
                intersec_arr[j] = i;
                j++;
            }
        }
        if (num_arr1[i] > num_arr2[i])
        {
            for (int h = 0; h < num_arr2[i]; h++)
            {
                intersec_arr[j] = i;
                j++;
            }
        }
    }
    return intersec_arr;
}
int countCharOccurrences(const char *str, int length, char ch)
{
    int count = 0;
    for (int i = 0; i < length; i++)
    {
        if (str[i] == ch)
            count++;
    }
    return count;
}
char findFirstNonRepeatingChar(const char *str, int length)
{
    int flag = 0;
    for (int i = 0; i < length; i++)
    {

        for (int j = 0; j < length; j++)
        {
            if (str[i] == str[j])
                flag++;
            if (flag > 1)
                break;
        }
        if (flag == 1)
            return str[i];
        flag = 0;
    }
    if (flag == 0)
        return 0;
}
char *findLongestCommonPrefix(char **strs, int numStr, int maxLen)
{
    char *prefix = (char *)malloc((maxLen + 1) * sizeof(char));
    int flag = 1;
    ind = 0;
    for (int i = 0; i < maxLen; i++)
    {
        flag = 1;
        for (int j = 1; j < numStr; j++)
        {
            if (strs[0][i] == strs[j][i])
                flag++;
        }

        if (flag == numStr)
        {
            prefix[ind] = strs[0][i];
            ind++;
        }
        else
            return prefix;
    }
}
int *maxMin(int *arr, int lenArr)
{
    int *result = (int *)malloc(lenArr * sizeof(int));
    result[0]=-1;
    int max_so_far=INT_MIN;
    int min_so_far=INT_MAX;
    k_maxmin=0;
    
    int max_array[lenArr];
    int min_array[lenArr];
    int k_max=0,k_min=0;
    for(int i=0;i<lenArr;i++)
    {
           
        if(arr[i]>max_so_far)
        {
            max_so_far=arr[i];
        }
        max_array[i]=max_so_far;
    }
    for(int i=lenArr-1;i>=0;i--)
    {
        
        if(arr[i]<min_so_far)
        {
             min_so_far=arr[i];
        }
        min_array[i]=min_so_far;
    }
    for(int x=0;x<lenArr;x++)
    {
        
            if(max_array[x]==min_array[x])
            result[k_maxmin++]=x;
        
    }
    return result;
}
char *removeSubstring(char *str, int strLength, const char *substr, int substrLength)
{
    k_remove=0;
    char *result = (char *)malloc(strLength* sizeof(char));
    int flag;
    result[0]=' ';
    for(int i=0;i<strLength;i++)
    {
        flag=0;
        if(str[i]==substr[0])
        {
            flag=1;
            for(int j=1;j<substrLength;j++)
            {
                if(str[i+j]==substr[j])
                flag++;
            }
        }
        if(flag!=substrLength && flag>0)
        {
            result[k_remove]=str[i];
            k_remove++;
        }
        if(flag==0)
        {
            result[k_remove]=str[i];
            k_remove++;
        }
        if(flag==substrLength)
        {
            i=i+substrLength-1;
        }
    }
    return result;
    
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
            int n1, n2;
            scanf("%d %d", &n1, &n2);
            int arr1[n1];
            for (int i = 0; i < n1; i++)
            {
                scanf("%d", &arr1[i]);
            }
            int arr2[n2];
            for (int i = 0; i < n2; i++)
            {
                scanf("%d", &arr2[i]);
            }
            int *intersec_arr;
            intersec_arr = intersectionArray(arr1, arr2, n1, n2);
            // printf("%d ",size);
            if (size == 0)
                printf("-1");
            else
            {
                for (int k = 0; k < size; k++)
                {
                    printf("%d ", intersec_arr[k]);
                }
                printf("\n");
            }
        }
        if (choice[4] == '2')
        {
            int n;
            scanf("%d", &n);
            n++;
            char str[n];
            scanf(" ");
            for (int i = 0; i < n; i++)
            {
                scanf("%c", &str[i]);
            }

            char ch;
            scanf("%c", &ch);
            const char *str1 = str;
            int count = countCharOccurrences(str1, n, ch);
            printf("%d", count);
            printf("\n");
        }
        if (choice[4] == '3')
        {
            int n;
            scanf("%d", &n);
            // n++;
            char str[n];
            scanf(" ");
            for (int i = 0; i < n; i++)
            {
                scanf("%c", &str[i]);
            }
            const char *str1 = str;
            char ch=0;
            ch = findFirstNonRepeatingChar(str1, n);
            if (ch == 0)
            {
                int c = -1;
                printf("%d", c);
            }
            else
                printf("%c", ch);
            printf("\n");
        }
        if (choice[4] == '4')
        {
            int n;
            scanf("%d ", &n);
            char **list = (char **)malloc(n * sizeof(char *));
            int max = 0;
            for (int i = 0; i < n; i++)
            {
                int n1;
                scanf("%d ", &n1);
                if (n1 <= min)
                    min = n1;
                if (n1 > max)
                    max = n1;
                list[i] = (char *)malloc(n1 * sizeof(char));

                scanf("%s", list[i]);
                // printf("%s\n",list[i]);
                // scanf(" ");
            }
            char *prefix = (char *)malloc((max + 1) * sizeof(char));
            prefix = findLongestCommonPrefix(list, n, max);
            if (prefix[0] == '\0')
                printf("-1");
            else
            {
                for (int i = 0; i < ind; i++)
                {
                    printf("%c", prefix[i]);
                }
            }
            printf("\n");
        }
        if (choice[4] == '5')
        {
            int n;
   
            scanf("%d", &n);
            int arr[n];
            for (int i = 0; i < n; i++)
            {
                scanf("%d", &arr[i]);
                
            }
            int *result = (int *)malloc(n * sizeof(int));
            result = maxMin(arr, n);
            if(result[0]==-1)
            {
                printf("-1");
            }
            else
            {
            for (int i = 0; i < k_maxmin; i++)
            {
                printf("%d ",result[i]);
            }
            
            }
            printf("\n"); 
        }
        if (choice[4] == '6')
        {
            int n,m;
            scanf("%d %d",&n,&m);
            char*str=(char*)malloc(sizeof(char)*(n+1));
            scanf("%s",str);
            char subStr[m+1];
            scanf("%s",subStr);
            const char* sub_str=subStr;
            char *result = (char *)malloc(n * sizeof(char));
            result = removeSubstring(str,n,sub_str,m);
            if(result[0]==' ')
            printf("-1");
            else
            {
            for (int i = 0; i < k_remove; i++)
                {
                    printf("%c", result[i]);
                }
            
            }
            printf("\n");
        }
        t--;
    }
}
