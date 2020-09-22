#include "AVLtree.h"

int main(){
    struct avltree *test_tree = malloc(sizeof(struct avltree));
    char word = 24;
    char* c= &word;
    test_tree = avltree_add(test_tree, 10, c);
    test_tree = avltree_add(test_tree, 7, c);
    test_tree = avltree_add(test_tree, 8, c);
    test_tree = avltree_add(test_tree, 1, c);
    test_tree = avltree_add(test_tree, 5, c);
    test_tree = avltree_add(test_tree, 0, c);
    test_tree = avltree_add(test_tree, -4, c);
    test_tree = avltree_add(test_tree, -2, c);
    test_tree = avltree_add(test_tree, -3, c);
    test_tree = avltree_add(test_tree, -1, c);
    printf("%d", avltree_max(test_tree)->key);
    printf("%d\n",test_tree->left->left->key);
    return 0;
}