#include "AVLtree.h"

int imax2(int a, int b)
    {
        if (a>b)
            return a;
        else
            return b;
    }

void avltree_free(struct avltree *tree)
{
    if (tree == NULL)
    {
        return;
    }
    avltree_free(tree->left);
    avltree_free(tree->right);
    free(tree);
}

struct avltree *avltree_lookup(struct avltree *tree, int key)
{
    while (tree != NULL)
    {
        if (key == tree->key)
        {
            return tree;
        }
        else if (key < tree->key)
        {
            tree = tree->left;
        }
        else
        {
            tree = tree->right;
        }
    }
    return tree;
}

struct avltree *avltree_create(int key, char *value)
{
    struct avltree *node;
    node = malloc(sizeof(*node));
    if (node != NULL)
    {
        node->key = key;
        node->value = value;
        node->left = NULL;
        node->right = NULL;
        node->height = 0;
    }
    return node;
}

int avltree_height(struct avltree *tree)
{
    return (tree != NULL) ? tree->height : -1;
}

int avltree_balance(struct avltree *tree)
{
    return avltree_height(tree->left) - avltree_height(tree->right);
}

struct avltree *avltree_left_rotate(struct avltree *tree)
{
    struct avltree *right;
    right = tree->right;
    tree->right = right->left;
    right->left = tree;
    tree->height = imax2(avltree_height(tree->left), avltree_height(tree->right)) + 1;
    right->height = imax2(avltree_height(right->right), tree->height) + 1;
    return right;
}

struct avltree *avltree_right_rotate(struct avltree *tree)
{
    struct avltree *left;
    left = tree->left;
    tree->left = left->right;
    left->right = tree;
    tree->height = imax2(avltree_height(tree->left), avltree_height(tree->right)) + 1;
    left->height = imax2(avltree_height(left->left), tree->height) + 1;
    return left;
}

struct avltree *avltree_leftright_rotate(struct avltree *tree)
{
    tree->left = avltree_left_rotate(tree->left);
    return avltree_right_rotate(tree);
}

struct avltree *avltree_rightleft_rotate(struct avltree *tree)
{
    tree->right = avltree_right_rotate(tree->right);
    return avltree_left_rotate(tree);
}

struct avltree *avltree_add(struct avltree *tree, int key, char *value)
{
    if (tree == NULL)
    {
        return avltree_create(key, value);
    }
    if (key < tree->key)
    {
        /* Insert into left subtree */
        tree->left = avltree_add(tree->left, key, value);
        if (avltree_height(tree->left) - avltree_height(tree->right) == 2)
        {
            /* Subtree is unbalanced */
            if (key < tree->left->key)
            {
                /* Left left case */
                tree = avltree_right_rotate(tree);
            }
            else
            {
                /* Left right case */
                tree = avltree_leftright_rotate(tree);
            }
        }
    }
    else if (key > tree->key)
    {
        /* Insert into right subtree */
        tree->right = avltree_add(tree->right, key, value);
        if (avltree_height(tree->right) - avltree_height(tree->left) == 2)
        {
            /* Subtree is unbalanced */
            if (key > tree->right->key)
            {
                /* Right right case */
                tree = avltree_left_rotate(tree);
            }
            else
            {
                /* Right left case */
                tree = avltree_rightleft_rotate(tree);
            }
        }
    }
    tree->height = imax2(avltree_height(tree->left),
                       avltree_height(tree->right)) +
                   1;
    return tree;
}
