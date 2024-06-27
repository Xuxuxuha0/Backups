#include "../headfile/AVL.h"
int main()
{
  BTNode *root = NULL;
  root = insert(root, 9);
  root = insert(root, 5);
  root = insert(root, 10);
  root = insert(root, 0);
  root = insert(root, 6);
  root = insert(root, 11);
  root = insert(root, -1);
  root = insert(root, 1);
  root = insert(root, 2);
  printf("前序遍历：\n");
  preOrder(root);
  /* The constructed AVL Tree would be
                   9
                  /  \
                 1    10
               /  \     \
              0    5     11
             /    /  \
            -1   2    6
  */

  root = deleteNode(root, 10);
  printf("\n");
  printf("前序遍历：\n");
  preOrder(root);
  /* The AVL Tree after deletion of 10
                 1
               /   \
              0     9
            /     /  \
          -1     5     11
               /  \
              2    6
  */
  return 0;
}