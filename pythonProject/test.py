import sys
import heapq
from collections import deque, defaultdict
import itertools

input = sys.stdin.readline

a = set()

a.add((1,1))
a.add((1,2))
a.add((1,3))
a.add((1,4))

b = set(a)
b.remove((1,1))
print(a)
print(b)

