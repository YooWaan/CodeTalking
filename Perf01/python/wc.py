# -*- coding: utf-8 -*-

import sys
from concurrent.futures import ThreadPoolExecutor, wait
from functools import reduce


def matrix_calc():
    start = int(sys.argv[1])
    end = int(sys.argv[2])
    
    futures = []
    with ThreadPoolExecutor(max_workers=8) as e:
        for i in range(start, end):
            left = matrix(i)
            right = matrix_right(i)
            futures.append(e.submit(matrix_mul, left, right))

        result = wait(futures)
        # print(len(result.done))


def matrix(size):
    return [[i for n in range(i, i+size) ] for i in range(1, size+1)]

    '''
    num = lambda x: x if x <= size else size*2 - x
    return [[num(n) for n in range(i, i+size) ] for i in range(1, size+1)]
    '''

def matrix_right(size):
    return [[n for n in range(1, size+1)] for i in range(1, size+1)]
    '''
    num = lambda x: x if x > 0 else -1 * x + 2
    return [[num(n-size) for n in reversed(range(i+1, i+size+1))] for i in reversed(range(1, size+1))]
    '''


def matrix_mul(m1, m2):
    sz = len(m1)
    return [reduce(lambda x,y: x+y ,[m1[n][i] * m2[i][n] for n in range(0,sz)]) for i in range(0, sz)]


def show_matrix(mat):
    print('-----------------------')
    for m in mat:
        print(','.join(map(str, m)))
    print('-----------------------')



def count():

    with open('README.md', 'rb') as fin:

        print('tel {}'.format(fin.tell()))

        by = fin.read(255)
        print('len {} {}'.format(len(by), str(by)))

        fin.seek(255)
        print('tel {}'.format(fin.tell()))
        by = fin.read(255)
        print('len {} {}'.format(len(by), str(by)))


matrix_calc()

#
