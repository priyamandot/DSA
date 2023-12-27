#include <stdio.h>
#include <stdlib.h>

struct node
{
    int c;
    int v;
    struct node *next;
} node;
struct vertical
{
    int r;
    struct vertical *down;
    struct node *right;
} vertical;
int count;
typedef struct node *ptr;
typedef struct vertical *list;
void mul_values(list *start, int row, int col, int val)
{
    ptr new = (ptr)malloc(sizeof(node));
    ptr temp;
    // temp = (*head);
    new->v = val;
    new->c = col;
    new->next = NULL;
    list findrow = (list)malloc(sizeof(vertical));
    findrow = (*start);
    if (findrow->down != NULL)
    {
        while (findrow->r != row && findrow != NULL)
        {
            // printf("%d\n",findrow->r);
            findrow = findrow->down;
        }
    }
    if (findrow->right == NULL)
    {
        // printf("1\n");
        findrow->right = new;
        // printf("head %d",(*head)->element);
    }
    else
    {
        // printf("2\n");
        temp = findrow->right;
        while (temp->next != NULL)
            temp = temp->next;

        (temp)->next = new;

        // printf("head %d",(*head)->element);
    }
}
void values(list *start, list *row_head, ptr *col_ptr, int row, int col, int val)
{
    ptr new = (ptr)malloc(sizeof(node));
    //ptr temp;
    // temp = (*head);
    new->v = val;
    new->c = col;
    new->next = NULL;
    list findrow = (list)malloc(sizeof(vertical));
    findrow = (*row_head);
    // if (findrow->down != NULL)
    // {
    //     while (findrow->r != row && findrow != NULL)
    //     {
    //         // printf("%d\n",findrow->r);
    //         findrow = findrow->down;
    //     }
    // }
    if (findrow->right == NULL)
    {
        // printf("1\n");
        findrow->right = new;
        *col_ptr = new;
        // printf("head %d",(*head)->element);
    }
    else
    {
        // printf("2\n");
        // temp = findrow->right;
        // while (temp->next != NULL)
        //     temp = temp->next;

        (*col_ptr)->next = new;
        (*col_ptr) = new;

        // printf("head %d",(*head)->element);
    }
}
void add_row_node(list *start, list *row_head, int num_rows)
{
    //list temp;
    list new = (list)malloc(sizeof(vertical));
    new->r = num_rows;
    new->down = NULL;
    new->right = NULL;

    if ((*start) == NULL && (*row_head) == NULL)
    {
        (*start) = new;
        (*row_head) = new;
    }
    else
    {
        (*row_head)->down = new;
        (*row_head) = new;
    }
}
void add(list *final, int num_rows, list *matrix1, list *matrix2)
{
    // printf("here\n");
    ptr f_head = NULL;
    list row_head = NULL;
    // add_row_node(final, num_rows);
    list temp1, temp2;
    temp1 = (*matrix1);
    temp2 = (*matrix2);
    ptr col1, col2;
    // col1 = (*matrix1)->right;
    // col2 = (*matrix2)->right;

    int sum = 0, rx, ry;
    int init_rowx = -1;
    int init_rowy = -1;
    while (temp1 != NULL || temp2 != NULL)
    {
        if (temp1 != NULL)
        {
            col1 = temp1->right;
            rx = (temp1)->r;
        }
        if (temp2 != NULL)
        {
            col2 = temp2->right;
            ry = (temp2)->r;
        }

        // printf("in while\n");

        if (col1 != NULL && col2 != NULL)
        {

            while (col1 != NULL && col2 != NULL && rx == ry)
            {
                // printf("in first if\n");
                sum = 0;

                int cx = col1->c;
                int cy = col2->c;
                if (cx == cy)
                {
                    sum = (col1->v) + (col2->v);
                    if (sum != 0)
                    {
                        if (init_rowx < rx && init_rowy < ry)
                        {
                            add_row_node(final, &row_head, rx);
                            init_rowx = rx;
                            init_rowy = ry;
                        }
                        values(final, &row_head, &f_head, rx, cx, sum);
                        count++;
                    }
                    col1 = col1->next;
                    col2 = col2->next;
                }
                else if (cx < cy)
                {
                    if (init_rowx < rx)
                    {
                        add_row_node(final, &row_head, rx);
                        init_rowx = rx;
                    }
                    values(final, &row_head, &f_head, rx, cx, (col1->v));
                    count++;
                    col1 = col1->next;
                }
                else if (cx > cy)
                {
                    if (init_rowy < ry)
                    {
                        add_row_node(final, &row_head, ry);
                        init_rowy = ry;
                    }
                    values(final, &row_head, &f_head, ry, cy, (col2->v));
                    count++;
                    col2 = col2->next;
                }
            }
        }
        if ((col1 != NULL && rx <= ry) || (col2 == NULL && rx > ry))
        {
            // printf("in second if\n");
            do
            {
                if (init_rowx < temp1->r)
                {
                    add_row_node(final, &row_head, temp1->r);
                    init_rowx = temp1->r;
                }
                values(final, &row_head, &f_head, (temp1)->r, col1->c, col1->v);
                count++;
                col1 = col1->next;
            } while (col1 != NULL);
        }
        if ((col2 != NULL && rx >= ry) || (col1 == NULL && temp1 == NULL && rx < ry))
        {
            // printf("in third if\n");
            do
            {
                if (init_rowy < temp2->r)
                {
                    add_row_node(final, &row_head, temp2->r);
                    init_rowy = temp2->r;
                }
                values(final, &row_head, &f_head, (temp2)->r, col2->c, col2->v);
                count++;
                col2 = col2->next;
            } while (col2 != NULL);
        }
        if (rx == ry)
        {
            if (temp1 != NULL)
                temp1 = temp1->down;
            if (temp2 != NULL)
                temp2 = temp2->down;
        }
        else if (((rx < ry && temp1 != NULL) || (rx > ry && temp2 == NULL)) && col1 == NULL)
            temp1 = temp1->down;
        else if (((rx > ry && temp2 != NULL) || (rx < ry && temp1 == NULL)) && col2 == NULL)
            temp2 = temp2->down;
    }
}
void print(list final, int num_rows)
{
    list temp;
    ptr col;
    temp = final;
    for (int i = 0; i < num_rows; i++)
    {
        if (temp != NULL)
        {
            col = temp->right;
            while (col != NULL)
            {
                printf("%d %d %d\n", temp->r, col->c, col->v);
                col = col->next;
            }
        }
        temp = temp->down;
        if (temp == NULL)
            break;
    }
}
void transpose_add_row(list *start, int row, int col, int val)
{
    ptr new = (ptr)malloc(sizeof(node));
    ptr temp, prev, temp1;
    int flag;
    // temp = (*head);
    new->v = val;
    new->c = col;
    new->next = NULL;
    list findrow = (list)malloc(sizeof(vertical));
    findrow = (*start);
    if (findrow->down != NULL)
    {
        while (findrow->r != row && findrow != NULL)
        {
            // printf("%d\n",findrow->r);
            findrow = findrow->down;
        }
    }
    if (findrow->right == NULL)
    {
        // printf("1\n");
        findrow->right = new;
        // printf("head %d",(*head)->element);
    }
    else
    {
        flag = 0;
        temp = findrow->right;
        while (temp != NULL && col > temp->c)
        {
            flag++;
            prev = temp;
            temp = temp->next;
        }
        if (flag == 0)
        {
            new->next = temp;
            findrow->right = new;
        }
        else if (flag > 0 && temp == NULL)
        {
            prev->next = new;
        }
        else if (flag > 0 && temp != NULL)
        {
            temp1 = prev->next;
            prev->next = new;
            new->next = temp1;
        }
    }
}
void transpose_col_add(list *start, int num_col)
{
    int flag;
    list temp, temp1, prev;
    list new = (list)malloc(sizeof(vertical));
    new->r = num_col;
    new->down = NULL;
    new->right = NULL;
    if ((*start) == NULL)
    {
        (*start) = new;
        return;
    }
    else
    {
        flag = 0;
        temp = (*start);
        while (temp != NULL && num_col > temp->r)
        {
            flag++;
            prev = temp;
            temp = temp->down;
        }
        if (flag == 0)
        {
            // temp1->down=temp;
            new->down = temp;
            (*start) = new;
        }
        if (flag > 0 && temp == NULL)
        {
            prev->down = new;
        }
        if (flag > 0 && temp != NULL)
        {
            temp1 = prev->down;
            prev->down = new;
            new->down = temp1;
        }
        // else if(flag>0 )//&& flag<(elements_so_far-1))
        // {
        // temp1=temp;
        // new->down=temp1;
        // temp->down=new;
        // }
        // else
        // {
        //     temp=new;
        // }
    }
}
int check_col(list *start, int col)
{
    int flag = 0;
    list temp;
    temp = (*start);
    if (temp == NULL)
        return 1;
    while (temp != NULL)
    {
        if (temp->r == col)
        {
            flag = 1;
            break;
        }
        temp = temp->down;
    }
    if (flag == 0)
        return 1;
    else
        return 0;
}
void input_transpose(list *start, int n, int m, int k)
{
    int row, col, val;
    for (int i = 0; i < k; i++)
    {
        scanf("%d %d %d", &row, &col, &val);
        // col_check[col]++;
        if (check_col(start, col))
        {
            transpose_col_add(start, col);
        }
        transpose_add_row(start, col, row, val);
    }
}
int multiply(list matrix1, list matrix2, list *final, int n, int m, int l)//, int *arr_row, int *arr_col, int *arr_val)
{
    list temp1, temp2;
    ptr col1, col2;
    list row_head = NULL;
    ptr f_head = NULL;
    temp1 = matrix1;
    temp2=matrix2;
    //int r_index = 0, c_index = 0, v_index = 0;

    if (temp1 == NULL && temp2 == NULL)
        return 0;

    while (temp1 != NULL)
    {
        col1 = temp1->right;
        while (col1 == NULL)
        {
            temp1 = temp1->down;
            col1 = temp1->right;
        }
        temp2 = matrix2;
        while (temp2 != NULL)
        {
            col1 = temp1->right;
            col2 = temp2->right;
            while (col2 == NULL)
            {
                temp2 = temp2->down;
                col2 = temp2->right;
            }
            int sum = 0;
            int col_to_pass = -1;
            while (col1 != NULL)
            {
                if (col2 == NULL)
                    break;
                if (col1->c == col2->c)
                {
                    sum += (col1->v) * (col2->v);
                    col_to_pass = temp2->r;
                    col1 = col1->next;
                    col2 = col2->next;
                }
                else if (col1->c < col2->c)
                {
                    col1 = col1->next;
                }
                else if (col2->c < col1->c)
                {
                    col2 = col2->next;
                }
            }
            if (sum != 0)
            {
                if (check_col(final, temp1->r))
                {
                    add_row_node(final, &row_head,temp1->r);
                }

                values(final, &row_head,&f_head,temp1->r, col_to_pass, sum);
                count++;
                // arr_row[r_index++]=temp1->r;
                // arr_col[c_index++]=col_to_pass;
                // arr_val[v_index++]=sum;
            }
            temp2 = temp2->down;
        }
        temp1 = temp1->down;
    }
    return count;
}
int main()
{

    char choice[3];
    scanf("%s", choice);
    if (choice[0] == 'T' && choice[1] == 'R' && choice[2] == 'A')
    {

        list begin = NULL;
        int n, m, k;
        // int *col_check = (int *)malloc((m + 1) * sizeof(int));
        //  for (int i = 0; i <= m; i++)
        //  {
        //      col_check[i] = 0;
        //  }
        scanf("%d %d %d", &n, &m, &k);
        input_transpose(&begin, n, m, k);
        // add_row_node(&start, n);

        printf("%d\n", k);
        if (k != 0)
        {
            print(begin, m);
        }
        // print_transpose(head);
    }
    if (choice[0] == 'A' && choice[1] == 'D' && choice[2] == 'D')
    {
        count = 0;
        int n, m, k1, k2;
        scanf("%d %d %d %d", &n, &m, &k1, &k2);

        int row, col, val;

        list matrix1 = NULL;
        list m1_head = NULL;
        ptr m1_col = NULL;
        int init_row = -1;
        for (int i = 0; i < k1; i++)
        {
            scanf("%d %d %d", &row, &col, &val);
            if (init_row < row)
            {
                add_row_node(&matrix1, &m1_head, row);
                init_row = row;
            }
            values(&matrix1, &m1_head, &m1_col, row, col, val);
        }
        // printf("matrix1\n");
        // print(matrix1,n);
        // printf("\n");

        init_row = -1;

        list matrix2 = NULL;
        list m2_head = NULL;
        ptr m2_col = NULL;
        for (int i = 0; i < k2; i++)
        {
            scanf("%d %d %d", &row, &col, &val);
            if (init_row < row)
            {
                add_row_node(&matrix2, &m2_head, row);
                init_row = row;
            }
            values(&matrix2, &m2_head, &m2_col, row, col, val);
        }
        //  printf("matrix2\n");
        // print(matrix2,n);
        // printf("\n");
        list final = NULL;
        add(&final, n, &matrix1, &matrix2);
        printf("%d\n", count);
        print(final, count);
    }
    if (choice[0] == 'M' && choice[1] == 'U' && choice[2] == 'L')
    {
        int n, m, l, k1, k2;
        scanf("%d %d %d %d %d", &n, &m, &l, &k1, &k2);
        list matrix1 = NULL;
        list m1_head = NULL;
        ptr m1_col=NULL;
        int init_row = -1;
        int row, col, val;

        // int *arr_row = (int *)malloc((k1 + k2) * sizeof(int));
        // int *arr_col = (int *)malloc((k1 + k2) * sizeof(int));
        // int *arr_val = (int *)malloc((k1 + k2) * sizeof(int));

        for (int i = 0; i < k1; i++)
        {
            scanf("%d %d %d", &row, &col, &val);
            if (init_row < row)
            {
                add_row_node(&matrix1, &m1_head, row);
                init_row = row;
            }
            values(&matrix1, &m1_head, &m1_col, row, col, val);
        }

        list matrix2 = NULL;
        // list m2_head;
        input_transpose(&matrix2, m, l, k2);
        // printf("MATRIX1\n");
        // print(matrix1,k1);
        // printf("MATRIX2\n");
        // print(matrix2,k2);
        list final = NULL;

        int count= multiply(matrix1, matrix2, &final, n, m, l);//, arr_row, arr_col, arr_val);
        printf("%d\n", count);
        // for(int i=0;i<count;i++)
        // {
        //     printf("%d %d %d\n",arr_row[i],arr_col[i],arr_val[i]);
        // }
        print(final, count);
    }
}