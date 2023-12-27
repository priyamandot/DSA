#include <stdio.h>
#include <stdlib.h>
#include<string.h>
long long int string_label(char ch)
{
    return (int)ch - 97 + 1;
}
// int length_str(char *str)
// {
//     int i = 0;
//     while (str[i] != '\0' && str[i] != ' ' && str[i] != '\n')
//     {
//         i++;
//     }
//     return i;
// }
struct hash
{
    long long int key1;
    long long int key2;
    char* str;
};
typedef struct hash hash;
hash* create_hash_array(int n)
{
    hash *h1 = (hash *)malloc(n * sizeof(hash));
    return h1;
}
long long int get_hash1(char *str, int len, int* prime)
{
    long long int sum=0,mod=1e9+9;
    for(int i=0;i<len;i++)
    {
        long long int label=string_label(str[i]);
        sum=(sum+(label*prime[label]))%mod;
    }
    return sum;
}
long long int get_hash2(char*str,int len, int*prime)
{
    long long int mul=1,mod=1e9+9;
    for(int i=0;i<len;i++)
    {
        long long int label=string_label(str[i]);
        mul=(mul*prime[label])%mod;
    }
    return mul;
}
void generate_primes(int* prime)
{
    int c=0;
    int i=3,flag=0,k=1;
    prime[0]=2;
    while(c<27)
    {
        flag=1;
        for(int j=2;j<i;j++)
        {
            if(i%j==0)
            {
            flag=0;
            break;
            }        
        }
        if(flag)
        {
            prime[k]=i;
            c++;
            k++;
        }
        i=i+2;
    }
}
void check_anagram(int n, int q, hash* h1, hash* h2)
{
    for(int i=0;i<q;i++)
    {
        int flag=0;
        for(int j=0;j<n;j++)
        {
            if(h2[i].key1==h1[j].key1 && h2[i].key2==h1[j].key2)
            {
                printf("%s ",h1[j].str);
                flag=1;
            }
        }
        if(flag)
        printf("\n");
        else
        printf("-1\n");
    }
}
int main()
{    
    int prime[27];
    generate_primes(prime);
    // for(int i=0;i<27;i++)
    // printf("%d=%d ",i,prime[i]);
    // printf("\n");
    int n, q;

    scanf("%d%d", &n, &q);
    hash* h1 = create_hash_array(n);
    hash* h2 = create_hash_array(q);
    // char **inputs = (char **)malloc(n * sizeof(char *));
    // for (int i = 0; i < n; i++)
    // {
    //     inputs[i] = (char *)malloc(10001 * sizeof(char));
    // }

    // char **queries = (char **)malloc(n * sizeof(char *));
    // for (int i = 0; i < q; i++)
    // {
    //     queries[i] = (char *)malloc(10001 * sizeof(char));
    // }
    int len = 0;
    for (int i = 0; i < n; i++)
    {
        char* a = (char*)malloc(10000);
        scanf("%s", a);
        h1[i].str = a;
        len = strlen(h1[i].str);
        h1[i].key1 = get_hash1(h1[i].str, len,prime);
        h1[i].key2 = get_hash2(h1[i].str, len,prime);
    }
    // for(int i=0;i<n;i++)
    // {
    //     printf("%s ",h1[i].str);
    //     printf("%lld ",h1[i].key1);
    //     printf("%lld ",h1[i].key2);
    //     printf("-----------------------\n");
    // }
    for (int i = 0; i < q; i++)
    {
        char* a = (char*)malloc(10000);
        scanf("%s", a);
        h2[i].str=a;
        len = strlen(h2[i].str);
        h2[i].key1 = get_hash1(h2[i].str, len,prime);
        h2[i].key2 = get_hash2(h2[i].str, len,prime);
    }
    // for(int i=0;i<q;i++)
    // {
    //     printf("%s ",h2[i].str);
    //     printf("%lld ",h2[i].key1);
    //     printf("%lld ",h2[i].key2);
    //     printf("-----------------------\n");
    // }
    check_anagram(n,q,h1,h2);
}