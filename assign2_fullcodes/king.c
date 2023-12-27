#include <stdio.h>
#include <stdlib.h>
struct node
{
    long long int val;
    struct node *child_left;
    struct node *child_right;
} node;
typedef struct node *ptrnode;
long long int sum, count;
struct queue
{
    struct node *N;
};
ptrnode Make_root(ptrnode tree, long long int x)
{
    ptrnode new = (ptrnode)malloc(sizeof(node));
    new->val = x;
    new->child_left = NULL;
    new->child_right = NULL;
    tree = new;
    return tree;
}
ptrnode Make_node(ptrnode tree, long long int x)
{
    ptrnode temp = tree;
    ptrnode parent = NULL;
    while (temp != NULL)
    {
        parent = temp;
        if (temp->val > x)
        {
            temp = temp->child_left;
        }
        else
        {
            temp = temp->child_right;
        }
    }
    ptrnode new = (ptrnode)malloc(sizeof(node));
    new->val = x;
    new->child_left = NULL;
    new->child_right = NULL;
    if (parent->val > x)
        parent->child_left = new;
    else
        parent->child_right = new;
    return tree;
}
void enqueue(ptrnode t, struct queue Q[], long long int index)
{
    Q[index].N = t;
}
void dequeue(struct queue Q[], long long int *front)
{
    count = count + Q[*front].N->val;
    printf("%lld ", (Q[*front]).N->val);
    (*front)++;
}
void traverse(ptrnode tree, struct queue Q[])
{
    ptrnode temp = tree;
    // printf("%d ",temp->val);
    
    long long int front = 0;
    long long int rear = -1;
    enqueue(temp, Q, ++rear);
    while (Q != NULL && front <= rear)
    {
        ptrnode curr = (Q[front]).N;
        dequeue(Q, &front);
        if (curr->child_left != NULL)
            enqueue(curr->child_left, Q, ++rear);
        if (curr->child_right != NULL)
            enqueue(curr->child_right, Q, ++rear);
    }
}
void inorder(ptrnode tree)
{
    if (tree == NULL)
        return;

    inorder(tree->child_left);
    // printf("%d ",tree->val);
    // tree->val+=sum;
    sum = sum + tree->val;
    tree->val = sum;
    inorder(tree->child_right);
    // tree->val+=sum;
    // sum=sum+tree->val;
}
int main()
{
    long long int n;
    scanf("%lld", &n);
    long long int elements[n];
    struct queue Q[n];
    scanf("%lld", &elements[0]);
    ptrnode tree = NULL;
    tree = Make_root(tree, elements[0]);
    for (int i = 1; i < n; i++)
    {
        scanf("%lld", &elements[i]);
        tree = Make_node(tree, elements[i]);
    }
    sum = 0;
    inorder(tree);
    traverse(tree, Q);
    printf("\n");
    printf("%lld\n",count);
}