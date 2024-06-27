#include <iostream>
using namespace std;

typedef struct Node
{
    struct Node *left;
    struct Node *right;
    int height;
    int key;
} BTNode;

int Max(int a, int b) //辅助函数
{
    return (a > b) ? a : b;
}

int height(struct Node *N) //辅助函数
{
    if (N == NULL)
        return 0;
    return N->height;
}

BTNode *newNode(int key) //创建新节点
{
    struct Node *node = (BTNode *)malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return (node);
}

BTNode *ll_rotate(BTNode *y) // LL型 返回根节点
{
    //三个顺承的式子
    BTNode *x = y->left;
    y->left = x->right;
    x->right = y;
    //更新高度,必须先y再x
    y->height = Max(height(y->left), height(y->right)) + 1;
    x->height = Max(height(x->left), height(x->right)) + 1;

    return x;
}

BTNode *rr_rotate(BTNode *y) // RR型 返回根节点
{
    BTNode *x = y->right;
    y->right = x->left;
    x->left = y;

    y->height = Max(height(y->left), height(y->right)) + 1;
    x->height = Max(height(x->left), height(x->right)) + 1;

    return x;
}

int getBalance(BTNode *N) //平衡因子
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

BTNode *insert(BTNode *node, int key)
//插入新节点；该函数不管什么情况都要回溯，一直往上检测直到根节点。但实际上只要遇到第一次|bf|=2，就不用再处理了。所以key的值只会用到一次。
//再判断旋转时，先判断node.再根据node选择子女进行判断.
// node    2      -2
// child  left   right
{

    if (node == NULL)
        return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    node->height = 1 + Max(height(node->left), height(node->right));
    int bf = getBalance(node);

    if (bf > -2 && bf < 2) //平衡
        return node;

    if (bf == 2 && key < node->left->key) // LL型(node.bf=2，node.left.bf=1)  LL的含义：node的L高，node的左子女L高
        return ll_rotate(node);

    if (bf == -2 && key > node->right->key) // RR型(node.bf=-2，node.right.bf=-1)
        return rr_rotate(node);

    if (bf == 2 && key > node->left->key) // LR型(node.bf=2，node.left.bf=-1)  LR的含义：node的L高，node的左子女R高
    {
        node->left = rr_rotate(node->left);
        return ll_rotate(node);
    }

    if (bf == -2 && key < node->right->key) // RL型(node.bf=-2，node.right.bf=1)
    {
        node->right = ll_rotate(node->right);
        return rr_rotate(node);
    }
}

BTNode *minValueNode(BTNode *node) //用来求中序下的后一个结点
{
    BTNode *current = node;

    while (current->left != NULL)
        current = current->left;

    return current;
}

BTNode *deleteNode(BTNode *root, int key)
{

    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);

    else if (key > root->key)
        root->right = deleteNode(root->right, key);

    else // key=root->key
    {
        if ((root->left == NULL) || (root->right == NULL)) //至少有一边为空
        {
            BTNode *temp = root->left ? root->left : root->right; //尽可能赋值为不空的子女

            if (temp == NULL)
            {
                temp = root; //为了free
                root = NULL;
            }
            else
                *root = *temp; //修改root指针相当于修改了"二叉树指针之间的联系"，此时等同于root的双亲指向root的子女
            free(temp);
        }
        else //两边都不空
        {
            BTNode *temp = minValueNode(root->right);         //中序下root的直接后继
            root->key = temp->key;                            //直接后继代替root
            root->right = deleteNode(root->right, temp->key); //然后在右子树中把直接后继删掉
        }
    }

    if (root == NULL) //特殊处理
        return root;

    root->height = 1 + Max(height(root->left), height(root->right));
    int bf = getBalance(root);

    if (bf > -2 && bf < 2)
        return root;

    if (bf == 2 && getBalance(root->left) >= 0) // LL型
        return ll_rotate(root);

    if (bf == -2 && getBalance(root->right) <= 0) // RR型
        return rr_rotate(root);

    if (bf == 2 && getBalance(root->left) < 0) // LR型
    {
        root->left = rr_rotate(root->left);
        return ll_rotate(root);
    }

    if (bf == -2 && getBalance(root->right) > 0) // RL型
    {
        root->right = ll_rotate(root->right);
        return rr_rotate(root);
    }
}

void preOrder(struct Node *root) //先序遍历
{
    if (root != NULL)
    {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}
