import copy
import sys
import math
from collections import deque
from collections import defaultdict
import itertools
import heapq

input = sys.stdin.readline

def solution(queue1, queue2):
    q = queue1 + queue2
    target = sum(q) // 2

    i, j = 0, len(queue1)-1
    curr = sum(queue1)
    count = 0
    print(q)
    while i < len(q) and j < len(q):

        print(i,j)

        if curr == target:
            return count

        elif curr < target and j < len(q)-1:
            j += 1
            curr += q[j]

        else:
            curr -= q[i]
            i += 1

        count += 1

    return -1


queue1 = eval(input())
queue2 = eval(input())

print(solution(queue1, queue2))








