#include <stdio.h>
#include <stdlib.h>

struct node
{
    int v;
    struct node *next;
    struct node *prev;
} node;
int count;
typedef struct node *Queue;

void Push(Queue head, int val);
int Pop(Queue head);
void Inject(Queue head, int val);
int popRear(Queue head);
void Print(Queue head);
void PrintReverse(Queue head);
int findElem(Queue head, int pos);
void removeKElems(Queue head, int k);

void Push(Queue head, int val)
{
    Queue new = (Queue)malloc(sizeof(node));
    new->v = val;
    new->next = NULL;
    new->prev = NULL;
    count++;
    if (head->next == NULL)
    {
        head->next = new;
        head->prev = new;
        new->next = new;
    }
    else
    {
        new->prev = head->prev;
        head->prev->next = new;
        new->next = head->next;
        head->prev = new;
    }
}
int Pop(Queue head)
{
    if (count == 0)
        return -1;
    if (count == 1)
    {
        count--;
        int x = head->next->v;
        head->next = NULL;
        head->prev = NULL;
        return x;
    }
    count--;
    int x = head->next->v;
    Queue temp = head->next->next;
    head->next->next = NULL;
    head->next = temp;
    head->next->prev = NULL;
    head->prev->next = head->next;
    return x;
}
void Print(Queue head)
{
    if (count == 0)
    {
        printf("-1\n");
        return;
    }
    if (count == 1)
    {
        printf("%d\n", head->next->v);
        return;
    }
    Queue temp = head->next;
    while (temp->next != head->next)
    {
        printf("%d ", temp->v);
        temp = temp->next;
    }
    printf("%d\n", temp->v);
}
void Inject(Queue head, int val)
{
    Queue new = (Queue)malloc(sizeof(node));
    new->v = val;
    new->next = NULL;
    new->prev = NULL;
    count++;
    if (head->next == NULL)
    {
        head->next = new;
        head->prev = new;
        new->next = new;
    }
    else
    {
        Queue temp = head->next;
        new->next = temp;
        temp->prev = new;
        head->prev->next = new;
        head->next = new;
    }
}
int popRear(Queue head)
{
    if (count == 0)
        return -1;
    if (count == 1)
    {
        count--;
        int x = head->prev->v;
        head->next = NULL;
        head->prev = NULL;
        return x;
    }
    count--;
    int x = head->prev->v;
    head->prev->prev->next = head->next;
    Queue temp = head->prev->prev;
    head->prev->prev = NULL;
    head->prev = temp;
    return x;
}
void PrintReverse(Queue head)
{
    if (count == 0)
    {
        printf("-1\n");
        return;
    }
    if (count == 1)
    {
        printf("%d\n", head->prev->v);
        return;
    }
    Queue temp = head->prev;
    while (temp->prev != NULL)
    {
        printf("%d ", temp->v);
        temp = temp->prev;
    }
    printf("%d\n", temp->v);
}
int findElem(Queue head, int pos)
{
    int c=1;
    Queue temp=head->next;
    while(c<pos)
    {
        c++;
        temp=temp->next;
    }
    return temp->v;
}
void removeKElems(Queue head, int k)
{
    int c=1;
    Queue temp= head->next;
    while(c<=k)
    {
        temp=temp->next;
        c++;
    }
    count=count-k;
    if(count>0)
    {
    temp->prev=NULL;
    head->next=temp;
    head->prev->next=temp;
    }
}
int main()
{
    count=0;
    Queue head = (Queue)malloc(sizeof(node));
    head->prev = NULL;
    head->next = NULL;
    head->v = -1;
    int t;
    scanf("%d", &t);
    char option[5];
    while (t > 0)
    {
        scanf("%s", option);
        if (option[4] == '1')
        {
            int num;
            scanf("%d", &num);
            Push(head, num);
        }
        else if (option[4] == '2')
        {
            printf("%d\n", Pop(head));
        }
        else if (option[4] == '3')
        {
            int num;
            scanf("%d", &num);
            Inject(head, num);
        }
        else if (option[4] == '4')
        {
            printf("%d\n", popRear(head));
        }
        else if (option[4] == '5')
        {
            Print(head);
        }
        else if (option[4] == '6')
        {
            PrintReverse(head);
        }
        else if (option[4] == '7')
        {
            int p;
            scanf("%d",&p);
            if(p==0 || p>count)
            printf("-1\n");
            else
            printf("%d\n",findElem(head,p));
        }
        else if (option[4] == '8')
        {
            int k;
            scanf("%d",&k);
            if(k<count)
            removeKElems(head,k);
            
            else if(k>=count)
            {
                head->next=NULL;
                head->prev=NULL;
                count=0;
            }
        }
        t--;
    }
}