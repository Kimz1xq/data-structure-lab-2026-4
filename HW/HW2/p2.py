import sys

## 입력 받는 코드입니다. 수정할 필요 없습니다.
sys.stdin = open('case.txt')
N, M = list(map(int,input().split()))
print(N, M)
concerts = []
for v in range(N):
    values = list(map(int, input().split()))
    concerts.append(values)
# print(concerts)
# [[1, 0, 0, 1, 1, 0], [1, 0, 1, 1, 0, 0], [1, 1, 1, 1, 0, 1], [0, 1, 1, 0, 1, 1], [0, 1, 0, 0, 1, 0]]
###################################

def count_stages(concerts):
    answer = 0
    # TODO : 콘서트 공간에서 무대의 개수를 계산해 반환해주는 함수를 작성해주세요.

    return answer

print(count_stages(concerts))
