#include <stdio.h>
#include <stdlib.h>
struct tnode
{
   int data;
   int count;
   struct tnode *lchild, *rchild;
};

struct tnode *tree_find(struct tnode *p, int val);
struct tnode *tree_find(struct tnode *p, int val);
int tree_height(struct tnode *p);
int tree_nodes(struct tnode *p);
int tree_counts(struct tnode *p);

struct tnode *tree_insert(struct tnode *p, int val)
{
   if(p == NULL)  // создаем узел
   {
      p = (struct tnode *) malloc(sizeof(struct tnode)); /* insert the new node as root node*/
         if(p == NULL)
            {
              printf("Cannot allocate\n");  exit(0);
            }
       p->data = val;
       p->count = 1;
       p->lchild = p->rchild=NULL;

       return p;
   }
   if ( val < p->data )
    {
       p->lchild = tree_insert ( p->lchild, val);
       return p;
    }
   if ( val > p->data )
    {
        p->rchild = tree_insert ( p->rchild, val );
        return p;
     }
     p->count++;
     return p;
}
/* a function to binary tree in inorder */

void tree_print(struct tnode *p)
 {
      if(p != NULL)
        {
           tree_print(p->lchild);
            printf("%3d \%3d\n",p->data, p->count);
           tree_print(p->rchild);
        }
 }

int main()
{
   struct tnode *root = NULL;
   int n,x;
   printf("Enter the number of nodes\n");
   scanf("%d",&n);
   while( n-->0)
     {
         printf("Enter the data value\n");
         scanf("%d",&x);
         root = tree_insert(root,x);
    }
     tree_print(root);
     putchar ('\n');
     fflush(stdout);
}

