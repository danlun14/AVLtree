#include "AVLtree.h"

struct QueueAVL *Qinit()
{
    struct QueueAVL *Q = malloc(sizeof(struct QueueAVL));
    Q->head = NULL;
    Q->tail = NULL;
    Q->item_count = 0;
    return Q;
}

struct QueueAVL push(struct QueueAVL *queue, struct avltree *root)
{
    struct Node *list = malloc(sizeof(struct Node));
    list->root = root;
    list->next = NULL;
    if (root == NULL)
    {
        return *queue;
    }
    if (queue->tail == NULL)
    {
        queue->head = list;
        queue->item_count = 1;
    }
    else
    {
        queue->tail->next = list;
        queue->item_count++;
    }
    queue->tail = list;
    return *queue;
}

struct avltree *pop(struct QueueAVL *queue)
{
    int key = -1;
    if (queue->head == NULL)
    {
        return NULL;
    }
    if (queue->item_count == 1)
    {
        queue->tail = NULL;
    }
    struct Node *tmp = queue->head;
    queue->head = queue->head->next;
    struct avltree *root = tmp->root;
    //free(tmp);
    queue->item_count--;
    return root;
}

void avltree_print_dfs(struct avltree *root, int level)
{
    struct QueueAVL *Q = Qinit();
    int i = 0;
    int count_max = 1;
    push(Q, root);
    struct avltree *root2;
    while (1)
    {
        if (i == count_max)
        {
            level--;
            printf("\n");
            count_max = count_max * 2 + 1;
            if (level == 0)
            {
                return;
            }
        }
        root = pop(Q);
        if (root != NULL)
        {
            printf("%d ", root->key);
        }
        push(Q, root->left);
        push(Q, root->right);
        if (Q->head == NULL)
        {
            return;
        }
        i++;
    }
}

int imax2(int a, int b)
{
    if (a > b)
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

struct avltree *avltree_min(struct avltree *root)
{
    while (root->left != NULL)
    {
        root = root->left;
    }
    return root;
}

struct avltree *avltree_max(struct avltree *root)
{
    while (root->right != NULL)
    {
        root = root->right;
    }

    return root;
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
