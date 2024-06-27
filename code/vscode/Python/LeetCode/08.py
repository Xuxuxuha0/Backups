# 547. 省份数量
# 求连通分支数
from typing import *
import collections

# 广度优先搜索
class Solution:
    def findCircleNum(self, isConnected: List[List[int]]) -> int:
        cities = len(isConnected)
        visited = set()
        provinces = 0

        for i in range(cities):
            if i not in visited:
                # 创建一个deque并用列表初始化
                Q = collections.deque([i])
                while Q:
                    j = Q.popleft()
                    visited.add(j)
                    for k in range(cities):
                        if isConnected[j][k] == 1 and k not in visited:
                            Q.append(k)
                provinces += 1

        return provinces


# 并查集
class Solution:
    def findCircleNum(self, isConnected: List[List[int]]) -> int:
        def find(index: int) -> int:
            # 当parent[i]==i时，说明i是根
            if parent[index] != index:
                parent[index] = find(parent[index])
            return parent[index]

        def union(index1: int, index2: int):
            parent[find(index1)] = find(index2)

        cities = len(isConnected)
        parent = list(range(cities))

        for i in range(cities):
            for j in range(i + 1, cities):
                if isConnected[i][j] == 1:
                    # 把i的根作为j的根的子女
                    union(i, j)

        # parent[i]==i的值为1/0
        provinces = sum(parent[i] == i for i in range(cities))
        return provinces
