#! /usr/bin/env python
'''
Description : 
FilePath    : /cpppython/interface.py
Author      : qxairobot@163.com
Date        : 2021-08-28 20:44:54
LastEditTime: 2021-08-30 10:43:15
Refer to    : https://github.com/QixuanAI
'''
from typing import Tuple

# 形参为两个数值，返回值为一个数值
def Add(a: int, b: int) -> int:
    print("[python]Function Add Called")
    print("[python]%d+%d=%d" % (a, b, a + b))
    return a + b

# 形参为列表，返回值为Tuple
def MinMax(l: list) -> Tuple[int, int]:
    print("[python]Function MinMax Called")
    l.sort()
    _min, _max = l[0], l[-1]
    print("[python]len:%d,min:%d,max:%d" % (len(l), _min, _max))
    return _min, _max

# 形参为一个数值，返回值为一维数组
def List(n: int) -> list:
    print("[python]Func List Called")
    ret = [x for x in range(n)]
    print("[python]got:", ret)
    return ret

# 形参为两个数值，返回值为多维数组
def SquareList(w: int, h: int) -> list:
    print("[python]Func SquareList Called")
    ret = [[(x + 1) * 10 + y + 1 for y in range(h)] for x in range(w)]
    print("[python]got:", ret)
    return ret

if __name__ == "__main__":
    List(5)
    MinMax([3,7,2,3,4,6])
