#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
struct Node
{
    struct avltree*root;
    struct Node *next;
};

struct QueueAVL
{
    struct Node *head;
    struct Node *tail;
    int item_count;
};

struct avltree
{
    int key;
    char *value;
    int height;
    struct avltree *left;
    struct avltree *right;
};

struct QueueAVL *Qinit();
struct avltree *avltree_add(struct avltree *root, int key, char *value);
struct avltree *avltree_lookup(struct avltree *root, int key);
struct avltree *avltree_delete(struct avltree *root, int key);;
struct avltree *avltree_min(struct avltree *root);
struct avltree *avltree_max(struct avltree *root);
void avltree_free(struct avltree *root);
void avltree_print_dfs(struct avltree *root, int level);