#include <stdio.h>
#include <stdlib.h>
struct trees
{
    int num1 = 0;
    int num2 = 0;
    int weight = 0;
};
struct sets
{
    trees *set = 0;
    int numele = 0;
};
struct allsets
{
    sets *asets = 0;
    int numset = 0;
};
trees *Read_Graph(FILE *fp,int e) 
{
    trees *stack = (trees *)malloc(sizeof(trees)*e);
    for(int i = 0; i < e; i ++)
        fscanf(fp, "%d %d %d", &stack[i].num1, &stack[i].num2, &stack[i].weight);
    return stack;
}
void swap(trees *a, trees *b)
{
    trees temp = *a;
    *a = *b;
    *b = temp;
}
void sort(trees *data, int left, int right)
{
    int pivot, i, j;
    if (left >= right)
        return ;
    pivot = data[left].weight;
    i = left + 1;
    j = right;
    while (1)
    {
        while (i <= right)
        {
            if (data[i].weight > pivot)
            {
                break;
            }

            i ++;
        }
        while (j > left)
        {
            if (data[j].weight < pivot)
            {
                break;
            }

            j --;
        }
        if (i > j)
            break;

        swap(&data[i], &data[j]);
    }

    swap(&data[left], &data[j]);

    sort(data, left, j - 1);
    sort(data, j + 1, right);
}
void addedge(sets *edgeset, const trees stack)
{
    trees *add = (trees *)malloc(sizeof(trees)*(edgeset->numele + 1));
    for(int i = 0; i < edgeset->numele; i ++)
        add[i] = edgeset->set[i];
    free(edgeset->set);
    add[edgeset->numele]= stack;
    edgeset->set = add;
    edgeset->numele ++;
}
int find(allsets sets, int num)
{
    for(int i = 0; i < sets.numset; i ++)
    {
        for(int j = 0; j < sets.asets[i].numele; j ++)
        {
            if(num == sets.asets[i].set[j].num1 || num == sets.asets[i].set[j].num2)
                return i;
        }
    }
    return -1;
}
void copy(trees *to, trees * from, int num)
{
    for(int i = 0; i < num; i ++)
        to[i] = from[i];
}
int Kruskal(trees *stack,int e)
{
    int ele = 1;
    allsets alledgesets;
    alledgesets.asets = (sets *)malloc(sizeof(sets)*1);
    alledgesets.numset ++;
    alledgesets.asets[0].set = (trees *)malloc(sizeof(trees)*1);
    alledgesets.asets[0].numele = 0;
    addedge(&alledgesets.asets[0],stack[0]);
    for(int i = 1; i < e || ele < e; i ++)
    {
        int a = find(alledgesets,stack[i].num1),b = find(alledgesets,stack[i].num2);
        if(a == -1 && b == -1)
        {
            ele ++;
            sets *add = (sets *)malloc(sizeof(sets)*(alledgesets.numset + 1));
            for(int i = 0; i < alledgesets.numset; i ++)
                add[i] = alledgesets.asets[i];
            free(alledgesets.asets);
            add[alledgesets.numset].set = (trees *)malloc(sizeof(trees)*1);
            add[alledgesets.numset].numele = 0;
            addedge(&add[alledgesets.numset],stack[i]);
            alledgesets.asets = add;
            alledgesets.numset ++;
        }
        else if(a == -1 || b == -1)
        {
            ele ++;
            addedge(&alledgesets.asets[a],stack[i]);
        }
        else if(a != b)
        {
            ele ++;
            int all = alledgesets.asets[a].numele + alledgesets.asets[b].numele;
            trees *add = (trees *)malloc(sizeof(trees)*(all));
            for(int i = 0; i < alledgesets.asets[a].numele; i ++)
                add[i] = alledgesets.asets[a].set[i];
            for(int i = alledgesets.asets[a].numele; i < all; i ++)
                add[i] = alledgesets.asets[b].set[i];
            free(alledgesets.asets[a].set);
            free(alledgesets.asets[b].set);
            alledgesets.asets[b].numele = 0;
            for(int i = b; i < alledgesets.numset - 1; i ++)
                alledgesets.asets[i] = alledgesets.asets[i + 1];
            alledgesets.asets[alledgesets.numset - 1].numele = 0;
            alledgesets.numset --;
            alledgesets.asets[a].set = add;
            alledgesets.asets[a].numele = all;
        }
    }
    free(stack);
    copy(stack, alledgesets.asets[0].set,ele);
    if(ele < e)
        return 0;
    return ele;
}
void Print_MST(const trees *stack, int e)
{
    int totalweight = 0;
    for(int i = 0; i < e; i ++)
    {
        totalweight += stack[i].weight;
    }
    printf("%d\n",totalweight);
    for(int i = 0; i < e; i++)
        printf("%d %d %d\n",stack[i].num1,stack[i].num2,stack[i].weight);
}
int main()
{
    int v = 0,e = 0;
    trees *stack;
    FILE *fp = fopen("data.txt", "r");
    if(fp)//有flie才做
    {
        fscanf(fp, "%d %d", &v, &e);
        stack = Read_Graph(fp,e);
    }
    sort(stack, 0, e - 1);
    v = Kruskal(stack,v - 1);
    if(v == 0)
        printf("Fail\n");
    Print_MST(stack,v);
    return 0;
}
