A = {
    0: [1, 2, 3],
    1: [0, 2, 4, 5],
    2: [0, 1, 6],
    3: [0],
    4: [1],
    5: [1],
    6: [2]
}

def bfs(A):
    answer = []
    # TODO : BFS로 탐색하는 로직을 구현해주세요.
    # 방문한 노드를 순서대로 answer 리스트에 넣어서 리턴해주세요.

    return answer


def dfs(A):
    answer = []
    # TODO : DFS로 탐색하는 로직을 구현해주세요.
    # 방문한 노드를 순서대로 answer 리스트에 넣어서 리턴해주세요.

    return answer

# 아래는 체크함수입니다. 수정하실 필요 없습니다.
bfs_result = bfs(A)
dfs_result = dfs(A)

assert bfs_result == [0,1,2,3,4,5,6]
assert dfs_result == [0,1,4,5,2,6,3]
print('PASSED!')

