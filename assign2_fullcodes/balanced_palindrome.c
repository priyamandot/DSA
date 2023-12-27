#include <stdio.h>

int top;

int length_str (char * str)
{
    int i=0;
    while(str[i]!='\0')
    {
        i++;
    }
    //printf("%d\n",i);
    return i;
}
char pop(char *str1)
{
    char ch;
    if (top == -1)
        return ' ';
    else
    {
        ch = str1[top];
        // if (ch == '(' || ch == ')' || ch == '{' || ch == '}' || ch == '[' || ch == ']')
        //     counter_balanced++;
        top--;
    }
    return ch;
}
char peek(char *str1)
{
    char ch;
    if (top == -1)
        return ' ';
    else
    {
        ch = str1[top];
        // if (ch == '(' || ch == ')' || ch == '{' || ch == '}' || ch == '[' || ch == ']')
        //     counter_balanced++;
        
    }
    return ch;
}
void push(char *str, char *reverse, int length)
{
    for (int k = 0; k < length; k++)
        reverse[++top] = str[k];
}
int check_palindrome(char *str)
{
    int len = length_str(str);
    top = -1;
    int flag = 0;
    char reverse[len];
    push(str, reverse, len);
    for (int i = 0; i < len; i++)
    {
        char ch = pop(reverse);
        if (ch != str[i])
        {
            flag = 1;
            break;
        }
    }
    if (flag == 0)
        return 1;
    else
        return 0;
}
/*int check_balanced(char *str)
{
    top=-1;
    int len=strlen(str);
    char ch[1];
    char c;
    int count=0;
    char brackets[10000];
    for(int k=0;k<len;k++)
    {
        
        if (str[k] == '(' || str[k] == ')' || str[k]== '{' || str[k]== '}' || str[k]== '[' || str[k] == ']')
        {
            ch[0]=str[k];
            push(ch,brackets,1);
            count++;
        }
    }
    int flag=0;
    if(count==0 || count%2!=0)
    return 0;
    for(int k=0;k<count/2;k++)
    {
        c=pop(brackets);
        if((int)brackets[k]-(int)c!=-2 && (int)brackets[k]-(int)c!=-1 )
        {
        flag=1;
        break;
        }
    }
    if (flag == 0 && count>0)
        return 1;
    else
        return 0;
}
*/
int good_check_balanced(char *str)
{
    int len=length_str(str);
    char brackets[10000];
    top=-1;
    char ch;
    int count=0;
    char c[1];
    int flag=0;
    for(int k=0;k<len;k++)
    {
      if (str[k] == '(' || str[k]== '{'  || str[k]== '[' )
        {
            c[0]=str[k];
            push(c,brackets,1);
            count++;
            continue;
        }  
      if (top==-1 && (str[k] == ')' ||  str[k]== '}' || str[k] == ']'))
        {
           flag=1;
           break;
        }
    if(top>-1 && (str[k] == ')' ||  str[k]== '}' || str[k] == ']'))
    {
        ch=peek(brackets);
        if(ch=='{')
        {
            if(str[k]=='}')
            pop(brackets);
            else if(str[k]==')' || str[k]==']')
            {
                flag=1;
                break;
            }
        }
        else if(ch=='(')
        {
            if(str[k]==')')
            pop(brackets);
            else if(str[k]=='}' || str[k]==']')
            {
                flag=1;
                break;
            }
        }
        else if(ch=='[')
        {
            if(str[k]==']')
            pop(brackets);
            else if(str[k]=='}' || str[k]==')')
            {
                flag=1;
                break;
            }
        }
        
    }
    }
     if (top==-1 && count>0 && flag!=1)
        return 1;
    else
        return 0;
}
int main()
{
    int t;
    scanf("%d", &t);
    int top = -1;
    char list[t][10000];
    char str[10000];

    int p,b;

    for (int i = 0; i < t; i++)
    {
        scanf("%s", list[i]);
        p=0,b=0;
        if(list[i][0]!='\0')
        {
        p = check_palindrome(list[i]);
        b = good_check_balanced(list[i]);
        }
        if (p == 0 && b == 0)
            printf("-1\n");
        else if (p == 1 && b == 1)
            printf("Balanced and Palindromic\n");
        else if (p == 1)
            printf("Palindromic\n");
        else
            printf("Balanced\n");
        // push(list,str,top);
    }
    // for (int i = 0; i < t; i++)
    // {
    //     printf("%s\n", list[i]);
    //     // push(list,str,top);
    // }
    // char reverse
}