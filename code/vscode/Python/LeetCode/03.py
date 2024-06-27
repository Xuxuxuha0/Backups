# 剑指 Offer II 107. 矩阵中的距离

from typing import List
import collections  # 容器库,常用:deque、counter、namedtuple、defaultdict、OrderedDict、


class Solution:
    def updateMatrix(self, matrix: List[List[int]]) -> List[List[int]]:
        m, n = len(matrix), len(matrix[0])

        dist = [[0] * n for _ in range(m)]  # 注意格式

        zeroList = [
            (i, j) for i in range(m) for j in range(n) if matrix[i][j] == 0
        ]  # 将所有0的坐标以元组的形式添加进列表中

        q = collections.deque(zeroList)  # 使用双端队列容器，并用列表初始化它

        seen = set(zeroList)  # 集合类型

        # 广度优先搜索
        while q:
            i, j = q.popleft()
            for ni, nj in [(i - 1, j), (i + 1, j), (i, j - 1), (i, j + 1)]:
                if 0 <= ni < m and 0 <= nj < n and (ni, nj) not in seen:
                    dist[ni][nj] = dist[i][j] + 1
                    q.append((ni, nj))
                    seen.add((ni, nj))

        return dist
