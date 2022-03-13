/* AVL树 */
/* 性质：左节点永远比右节点的值小，每个节点的高度差不超过 1 */

#include <stdlib.h>
#include <stdio.h>
#include "binary_tree.h"
#define MAX(a, b) ((a) > (b) ? (a) : (b))

PtrNode FindMin(PtrNode rootNode);
PtrNode FindMax(PtrNode rootNode);
PtrNode InsertNode(int element, PtrNode rootNode);
PtrNode DeleteNode(int element, PtrNode rootNode);
int Height(PtrNode node);
int GetBalance(PtrNode node);
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
    }
    else if (element > rootNode->item)
    {
        // ***递归插入到子节点***
        rootNode->right = InsertNode(element, rootNode->right);
    }
    else
    {
        // 节点在树中，不做任何处理
    }

    // 更新节点高度
    rootNode->height = MAX(Height(rootNode->left), Height(rootNode->right)) + 1;

    /* 插入和删除都一样存在 4 种情况 LL、RR、LR、RL */
    /*
    第一个平衡因子是当前节点的平衡状态
    balance = H(left) - H(right)
    如果这个高度高于 1 ，那么这个就是不平衡的。再插入之前，左节点或右节点肯定是平衡状态，而插入导致了不平衡
    如果左树更高： balance == 2 (> 1)
         1. 看左节点的平衡因子
         2. 如果平衡因子 大于或等于 0，说明节点是 插入到左节点的左边的，也就是 LL
         3. 如果平衡因子 小于 0， 说明节点是插入到左节点的右边的，也就是 LR
    如果右子树更高: balance == -2 (< -1)
         1. 看右节点的平衡因子
         2. 如果平衡因子 小于等于 0， 说明节点是插入到右节点的右边的(右边高度增加，现在变得更高)，也就是 RR
         3. 如果平衡因子 大于 0, 说明节点是插入到右节点的左边的（左边高度增加，变得更高），也就是 RL
     */
    int balance = GetBalance(rootNode);
    // LL
    if (balance == 2 && GetBalance(rootNode->left) >= 0)
    {
        rootNode = LLRotate(rootNode);
    }
    // LR
    if (balance == 2 && GetBalance(rootNode->left) < 0)
    {
        rootNode = LRRotate(rootNode);
    }
    // RR
    if (balance == -2 && GetBalance(rootNode->right) <= 0)
    {
        rootNode = RRRotate(rootNode);
    }
    // RL
    if (balance == -2 && GetBalance(rootNode->right) > 0)
    {
        rootNode = RLRotate(rootNode);
    }

    return rootNode;
}

PtrNode DeleteNode(int element, PtrNode rootNode)
{
    if (rootNode == NULL)
    {
        printf("cannot delete, element is not exist.\n");
        return NULL;
    }
    if (element < rootNode->item)
    {
        rootNode->left = DeleteNode(element, rootNode->left);
    }
    else if (element > rootNode->item)
    {
        rootNode->right = DeleteNode(element, rootNode->right);
    }
    else
    {
        if (rootNode->left != NULL && rootNode->right != NULL)
        {
            PtrNode min = FindMin(rootNode->right);
            rootNode->item = min->item;
            rootNode->right = DeleteNode(min->item, rootNode->right);
        }
        else
        {
            PtrNode temp = rootNode;
            if (rootNode->left != NULL && rootNode->right == NULL)
            {
                rootNode = rootNode->left;
            }
            else if (rootNode->left == NULL && rootNode->right != NULL)
            {
                rootNode = rootNode->right;
            }
            else
            {
                rootNode = NULL;
            }
            free(temp);
        }
    }
    // 删除的叶子节点
    if (rootNode == NULL)
    {
        return NULL;
    }

    // 更新高度
    rootNode->height = MAX(Height(rootNode->left), Height(rootNode->right)) + 1;

    int balance = GetBalance(rootNode);

    /*
     情况和插入节点一样，一开始节点是平衡的，但是删除节点导致了不平衡
     balance > 1 证明左边失去了平衡，左子树更高
     如果左子树更高:
         1. 看左节点的平衡因子 x
         2. 如果 x >=0， 说明左边还是更高，是 LL
         3. 如果 x < 0， 说明右边更高，是 LR
     如果右子树更高：
         1. 看右节点的平衡因子 y
         2. 如果 y >=0，说明左边还是更高，是 RL
         3. 如果 y <0 ，说明右节点跟高，是 RR
     */
    if (balance > 1 && GetBalance(rootNode->left) >= 0)
    {
        rootNode = LLRotate(rootNode);
    }
    if (balance > 1 && GetBalance(rootNode->left) < 0)
    {
        rootNode = LRRotate(rootNode);
    }
    if (balance < -1 && GetBalance(rootNode->right) >= 0)
    {
        rootNode = RLRotate(rootNode);
    }
    if (balance < -1 && GetBalance(rootNode->right) < 0)
    {
        rootNode = RRRotate(rootNode);
    }
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

int GetBalance(PtrNode node)
{
    if (node == NULL)
    {
        return 0;
    }
    return Height(node->left) - Height(node->right);
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