# 98. 验证二叉搜索树
from typing import *

# 定义树结点
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def isValidBST(self, root: Optional[TreeNode]) -> bool:
        # 假设node的val应该在(left,right)
        def judgeNode(node: TreeNode, lower=float("-inf"), higher=float("inf")) -> bool:
            if not node:
                return True

            val = node.val
            # 先判断node
            if val <= lower or val >= higher:
                return False
            # 再判断node的左右子树
            if not judgeNode(node.left, lower, val) or not judgeNode(
                node.right, val, higher
            ):
                return False
            return True

        return judgeNode(root)


# 把列表按层次序列创建为二叉树
def list_to_tree(lst):
    if not lst:
        return None
    # 创建根节点
    root = TreeNode(lst[0])
    # 按层级顺序创建节点，并将节点添加到父节点的左右子树中
    nodes = [root]
    i = 1
    while i < len(lst):
        parent = nodes.pop(0)
        if lst[i] is not None:
            left = TreeNode(lst[i])
            parent.left = left
            nodes.append(left)
        if i + 1 < len(lst) and lst[i + 1] is not None:
            right = TreeNode(lst[i + 1])
            parent.right = right
            nodes.append(right)
        i += 2
    return root


def main():
    nodeList = [2, 1, 3]
    root = list_to_tree(nodeList)
    s = Solution()
    # 类方法中的self就是对象s
    print(s.isValidBST(root))


# if __name__ == "_main_":
main()
