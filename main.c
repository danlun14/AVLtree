#include "AVLtree.h"

int main()
{
    struct avltree *test_tree;
    char word = 2;
    char *c = &word;
    for (int i = 10; i < 50000; i++)
    {
        test_tree = avltree_add(test_tree, i, c);
    }
    //test_tree = avltree_add(test_tree, 4, c);
    /*test_tree = avltree_add(test_tree, 7, c);
    test_tree = avltree_add(test_tree, 8, c);
    test_tree = avltree_add(test_tree, 1, c);
    test_tree = avltree_add(test_tree, 5, c);
    test_tree = avltree_add(test_tree, 0, c);
    
    test_tree = avltree_add(test_tree, -2, c);
    test_tree = avltree_add(test_tree, -3, c);
    test_tree = avltree_add(test_tree, -1, c);*/
    struct avltree *test_tree2 = avltree_min(test_tree);
    printf("%d \n", test_tree2->key);
    //printf("%d\n", test_tree->key);
    avltree_print_dfs(test_tree, 4);
    return 0;
}