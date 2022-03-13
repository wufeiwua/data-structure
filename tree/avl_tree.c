/* 二叉查找树 */
/* 性质：左节点永远比右节点的值小 */

#include <stdlib.h>
#include <stdio.h>
#include "binary_tree.h"
#define MAX(a, b) ((a) > (b) ? (a) : (b))

PtrNode FindMin(PtrNode rootNode);
PtrNode FindMax(PtrNode rootNode);
PtrNode InsertNode(int element, PtrNode rootNode);
PtrNode DeleteNode(int element, PtrNode rootNode);
int Height(PtrNode node);
// LL，右旋一次
PtrNode LLRotate(PtrNode node);
// LR，左旋一次 -> LL -> 右旋一次
PtrNode LRRotate(PtrNode node);
// RR 左旋一次
PtrNode RRRotate(PtrNode node);
// RL 右旋一次 -> RR -> 左旋一次
PtrNode RLRotate(PtrNode node);

/* =============== implementation ================ */

PtrTree MakeTree()
{
    PtrTree tree = (PtrTree)malloc(sizeof(BinaryTree));
    if (tree == NULL)
    {
        printf("cannot make a tree, out of space\n");
    }
    return tree;
}

PtrNode MakeEmpty(PtrNode rootNode)
{
    while (rootNode != NULL)
    {
        rootNode->left = MakeEmpty(rootNode->left);
        rootNode->right = MakeEmpty(rootNode->right);
        free(rootNode);
    }
    return NULL;
}

PtrNode GetRoot(PtrTree tree)
{
    return tree->root;
}

PtrNode Find(int element, PtrNode rootNode)
{
    PtrNode root = rootNode;
    if (root == NULL)
    {
        printf("not find, root node is NULL.\n");
        return NULL;
    }
    if (element < root->item)
    {
        return Find(element, root->left);
    }
    else if (element > root->item)
    {
        return Find(element, root->right);
    }
    else
    {
        return root;
    }
}

PtrNode Insert(int element, PtrTree tree)
{
    if (tree == NULL)
    {
        printf("cannot insert, the tree is NULL.\n");
        return NULL;
    }
    PtrNode node = InsertNode(element, tree->root);
    tree->root = node;
    return node;
}

PtrNode Delete(int element, PtrTree tree)
{
    PtrNode node = DeleteNode(element, tree->root);
    tree->root = node;
}

PtrNode InsertNode(int element, PtrNode rootNode)
{
    if (rootNode == NULL)
    {
        rootNode = (PtrNode)malloc(sizeof(TreeNode));
        if (rootNode == NULL)
        {
            printf("cannot insert, out of space.\n");
        }
        else
        {
            rootNode->item = element;
            rootNode->left = rootNode->right = NULL;
            rootNode->height = 0;
        }
    }
    else if (element < rootNode->item)
    {
        // ***递归插入到子节点***
        rootNode->left = InsertNode(element, rootNode->left);
        // 节点左边失衡
        if (Height(rootNode->left) - Height(rootNode->right) == 2)
        {
            // 左子树左边插入， LL 情形，向右旋转一次
            if (element < rootNode->left->item)
            {
                rootNode = LLRotate(rootNode);
            }
            // 左子树右边插入，LR 情形，向左旋再向右旋转
            else
            {
                rootNode = LRRotate(rootNode);
            }
        }
    }
    else if (element > rootNode->item)
    {
        // ***递归插入到子节点***
        rootNode->right = InsertNode(element, rootNode->right);
        // 节点右边失衡
        if (Height(rootNode->left) - Height(rootNode->right) == -2)
        {
            // 右子树右边插入， RR 情形，向左旋转一次
            if (element > rootNode->right->item)
            {
                rootNode = RRRotate(rootNode);
            }
            // 左子树右边插入，RL 情形，向右旋再向左旋转
            else
            {
                rootNode = RLRotate(rootNode);
            }
        }
    }
    else
    {
        // 节点在树中，不做任何处理
    }

    // 更新节点高度
    rootNode->height = MAX(Height(rootNode->left), Height(rootNode->right)) + 1;
    return rootNode;
}

PtrNode DeleteNode(int element, PtrNode rootNode)
{
    return rootNode;
}

PtrNode FindMin(PtrNode rootNode)
{
    PtrNode root = rootNode;
    while (root != NULL && root->left != NULL)
    {
        root = root->left;
    }
    return root;
}

PtrNode FindMax(PtrNode rootNode)
{
    PtrNode root = rootNode;
    while (root != NULL && root->right != NULL)
    {
        root = root->right;
    }
    return root;
}

int Height(PtrNode node)
{
    if (node == NULL)
    {
        return 0;
    }
    return node->height;
}

// LL，右旋一次
PtrNode LLRotate(PtrNode k2)
{
    /* X、Y、Z 是子树， k2 是旋转的根节点
                  通过一次右旋
             k2               k1
            /  \             /  \
           k1   Z    ==>    X    k2
          /  \                  /  \
         X    Y                Y    Z
     */

    // 右旋
    PtrNode k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;

    // 更新节点的高，比子树的高 1
    k2->height = MAX(Height(k2->left), Height(k2->right)) + 1;
    // k1->height = MAX(Height(k1->left), Height(k1->right)) + 1;
    // k1->right == k2
    k1->height = MAX(Height(k1->left), k2->height) + 1;

    // k1 将作为新的根节点
    return k1;
}

// RR 左旋一次
PtrNode RRRotate(PtrNode k2)
{
    /* X、Y、Z 是子树， k2 是旋转的根节点
                 通过一次左旋
          k2                  k1
         /  \                /  \
        X    k1    ==>      k2   Z
            /  \           /  \
            Y   Z         X    Y
     */

    // 左旋
    PtrNode k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;

    // 更新节点的高，比子树的高 1
    k2->height = MAX(Height(k2->left), Height(k2->right)) + 1;
    k1->height = MAX(Height(k1->right), k2->height) + 1;
    return k1;
}

// LR，左旋一次 -> LL -> 右旋一次
PtrNode LRRotate(PtrNode k3)
{
    /* 对于 LR ，k3 节点不平衡，但是一次单旋不能改变平衡状态，
    所以需要以 k1 为根，对 k2 做一次左单旋，转为 LL
    再以 k3 为根，对 k2 做一次右单旋
        k3               k3                  k2
       /  \             /  \                /  \
      k1   D           k2   D              k1   k3
     /  \      ==>    /  \       ==>      /  \  /  \
    A    k2          k1   C              A   B  C   D
        /  \        /  \
        B   C      A    B
    */
    k3->left = RRRotate(k3->left);
    return LLRotate(k3);
}

// RL 右旋一次 -> RR -> 左旋一次
PtrNode RLRotate(PtrNode k3)
{
    /* 和 LR 情形类似，不过反向操作，先做一次右单旋，再做一次左单旋

          k3              k3                     k2
         /  \            /  \                   /  \
        A    k1         A    k2                k3   k1
            /  \    ==>     /  \      ==>     /  \  /  \
            k2   D          B    k1          A   B  C   D
           /  \                 /  \
           B   C               C    D
     */
    k3->right = LLRotate(k3->right);
    return RRRotate(k3);
}