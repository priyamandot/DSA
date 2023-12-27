#include <stdio.h>
long long int string_label(char ch)
{
    return (int)ch - 97 + 1;
}
void create_power_array(long long int *power, int n)
{
    long long int mod = 1e9 + 7;
    power[0] = 1;
    for (int i = 1; i < n; i++)
    {
        power[i] = (power[i - 1] % mod * 101 % mod) % mod;
    }
}
void create_prefix(long long int *prefix, char *string, long long int *power, int n)
{
    long long int mod = 1e9 + 7;
    prefix[0] = 0;
    prefix[1] = string_label(string[0]);
    for (int i = 2; i < n; i++)
    {
        prefix[i] = (prefix[i - 1] % mod + (string_label(string[i - 1]) % mod * power[i - 1] % mod) % mod) % mod;
    }
}
void create_suffix(long long int *suffix, char *string, long long int *power, int n)
{
    long long int mod = 1e9 + 7;
    suffix[0] = 0;
    suffix[1] = string_label(string[n - 2]);
    int k = n - 3;
    for (int i = 2; i < n; i++)
    {
        suffix[i] = (suffix[i - 1] % mod + (string_label(string[k]) % mod * power[i - 1] % mod) % mod) % mod;
        k--;
    }
}
void check_queries(int q, int n, long long int *prefix, long long int *suffix, long long int *power)
{
    long long int S, P;
    n--;
    while (q > 0)
    {

        long long int mod = 1e9 + 7;
        int l, r;
        scanf("%d%d", &l, &r);
        // size = r - l;
        if (r == l)
            printf("YES\n");
        else
        {
            S = (suffix[n - l + 1] - suffix[n - r] + mod) % mod;
            P = (prefix[r] - prefix[l - 1] + mod) % mod;
            // printf("%lld     %lld\n",S,P);
            //  if (r != n)
            //      S = (suffix[r] - suffix[l - 1] + mod) % mod;
            //  else
            //      S = suffix[size];
            //  if(l!=n)
            //  P = (prefix[r - 1]- prefix[l - 2]+ mod) % mod;
            //  else
            //  P=prefix[size];

            if (l < n - r + 1)
            {
                int factor = n - r + 1 - l;
                long long int Q = (power[factor] * P) % mod;
                if (Q == S)
                    printf("YES\n");
                else
                    printf("NO\n");
            }
            else if (l > n - r + 1)
            {
                int factor = l - 1 - n + r;
                long long int Q = (power[factor] * S) % mod;
                if (P == Q)
                    printf("YES\n");
                else
                    printf("NO\n");
            }
            else
            {
                if (P == S)
                    printf("YES\n");
                else
                    printf("NO\n");
            }
        }
        q--;
    }
}
int main()
{
    int n, q;
    scanf("%d%d", &n, &q);
    char string[n + 1];
    scanf("%s", string);
    long long int prefix[n + 1];
    long long int suffix[n + 1];
    long long int power[n + 1];
    // printf("%s",string);
    create_power_array(power, n + 1);
    // for (int i = 0; i < n+1; i++)
    // {
    //     printf("%lld ", power[i]);
    // }
    // printf("\n");
    create_suffix(suffix, string, power, n + 1);
    create_prefix(prefix, string, power, n + 1);
    // for (int i = 0; i < n+1; i++)
    // {
    //     printf("%lld ", prefix[i]);
    // }
    // printf("\n");

    // for (int i = 0; i < n+1; i++)
    // {
    //     printf("%lld ", suffix[i]);
    // }
    // printf("\n");
    check_queries(q, n + 1, prefix, suffix, power);
}