#include <stdio.h>
#include <stdlib.h>
struct node
{
    int Element;
    struct node *NextNode;
};
typedef struct node node;
typedef struct node *PtrNode;
// PtrNode Head;

void Insert(PtrNode Head, int num)
{
    PtrNode new = (PtrNode)malloc(sizeof(node));
    if(new==NULL)
    exit;
    PtrNode temp;
    if(new==NULL)
    exit;
    new->Element = num;
    if (Head->NextNode == NULL)
    {
        // printf("1\n");
        Head->NextNode = new;
        new->NextNode = Head->NextNode;
        // printf("Head %d",(Head->NextNode)->Element);
    }
    else
    {
        // printf("2\n");
        temp = Head->NextNode;
        while (temp->NextNode != Head->NextNode)
            temp = temp->NextNode;

        new->NextNode = Head->NextNode;
        (temp)->NextNode = new;
        Head->NextNode = new;
        // printf("Head %d",(Head->NextNode)->Element);
    }
}

void Print(PtrNode Head)
{
    PtrNode temp;
    if(temp==NULL)
    exit;
    temp = Head->NextNode;
    if (temp == NULL)
    {
        printf("\n");
        return;
    }
    else
    {
        while (temp->NextNode != Head->NextNode)
        {
            printf("%d ", temp->Element);
            temp = temp->NextNode;
        }
        printf("%d\n", temp->Element);
    }
}
PtrNode Find(PtrNode Head, int num)
{
    PtrNode temp;
    if(temp==NULL)
    exit;
    temp = Head->NextNode;
    int flag = 0;
    if (Head->NextNode == NULL)
        return NULL;
    if (temp->Element == num)
    {
        return Head->NextNode;
    }
    while (temp->NextNode != (Head->NextNode))
    {
        if (temp->NextNode->Element == num)
        {
            temp->NextNode = temp->NextNode->NextNode;
            flag = 1;
            Insert(Head, num);
            break;
        }
        else
            temp = temp->NextNode;
    }
    if (flag == 0)
        return NULL;
    if (flag == 1)
        return Head->NextNode;
}
int main()
{
    int t;
    scanf("%d", &t);
    PtrNode Head = (PtrNode)malloc(sizeof(node));
    if(Head==NULL)
    exit;
    Head->Element = -1;
    Head->NextNode = NULL;
    while (t > 0)
    {
        char choice[6];
        scanf("%s", choice);
        if (choice[4] == '1')
        {
            int n;
            scanf("%d", &n);
            Insert(Head, n);
        }
        if (choice[4] == '2')
        {
            PtrNode check;
            int n;
            scanf("%d", &n);
            check = Find(Head, n);
        }
        if (choice[4] == '3')
        {
            Print(Head);
        }
        t--;
    }
}