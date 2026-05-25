#include <stdio.h>
#include <stdlib.h>

struct tnode {
    int data;
    int count;
    struct tnode *lchild;
    struct tnode *rchild;
};

struct tnode *tree_insert(struct tnode *p, int val);
struct tnode *tree_find(struct tnode *p, int val);
void tree_print(struct tnode *p);
int tree_height(struct tnode *p);
int tree_nodes(struct tnode *p);
int tree_counts(struct tnode *p);

int main()
{
    struct tnode *root = NULL;
    struct tnode *found;
    int n, x;

    printf("Enter the number of nodes\n");
    scanf("%d", &n);

    while (n-- > 0) {
        printf("Enter the data value\n");
        scanf("%d", &x);
        root = tree_insert(root, x);
    }

    printf("\nTree:\n");
    tree_print(root);

    printf("\nheight = %d\n", tree_height(root));
    printf("nodes = %d\n", tree_nodes(root));
    printf("counts = %d\n", tree_counts(root));

    printf("\nEnter value to find\n");
    scanf("%d", &x);
    found = tree_find(root, x);

    if (found != NULL)
        printf("%d found, count = %d\n", x, found->count);
    else
        printf("%d not found\n", x);

    return 0;
}

struct tnode *tree_insert(struct tnode *p, int val)
{
    if (p == NULL) {
        p = (struct tnode *)malloc(sizeof(struct tnode));
        if (p == NULL) {
            printf("Cannot allocate\n");
            exit(1);
        }

        p->data = val;
        p->count = 1;
        p->lchild = NULL;
        p->rchild = NULL;
        return p;
    }

    if (val < p->data)
        p->lchild = tree_insert(p->lchild, val);
    else if (val > p->data)
        p->rchild = tree_insert(p->rchild, val);
    else
        p->count++;

    return p;
}

struct tnode *tree_find(struct tnode *p, int val)
{
    if (p == NULL)
        return NULL;

    if (val == p->data)
        return p;

    if (val < p->data)
        return tree_find(p->lchild, val);

    return tree_find(p->rchild, val);
}

void tree_print(struct tnode *p)
{
    if (p != NULL) {
        tree_print(p->lchild);
        printf("%3d %3d\n", p->data, p->count);
        tree_print(p->rchild);
    }
}

int tree_height(struct tnode *p)
{
    int left, right;

    if (p == NULL)
        return 0;

    left = tree_height(p->lchild);
    right = tree_height(p->rchild);

    if (left > right)
        return left + 1;
    else
        return right + 1;
}

int tree_nodes(struct tnode *p)
{
    if (p == NULL)
        return 0;

    return tree_nodes(p->lchild) + tree_nodes(p->rchild) + 1;
}

int tree_counts(struct tnode *p)
{
    if (p == NULL)
        return 0;

    return tree_counts(p->lchild) + tree_counts(p->rchild) + p->count;
}
