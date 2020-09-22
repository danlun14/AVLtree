#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

struct avltree
{
    int key;
    char *value;
    int height;
    struct avltree *left;
    struct avltree *right;
};

struct avltree *avltree_add(struct avltree *root, int key, char *value);
struct avltree *avltree_lookup(struct avltree *root, int key);
struct avltree *avltree_delete(struct avltree *root, int key);;
struct avltree *avltree_min(struct avltree *root);
struct avltree *avltree_max(struct avltree *root);
void avltree_free(struct avltree *root);
//void avltree_print_dfs(avltree *root, int level);