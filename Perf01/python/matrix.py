# -*- coding: utf-8 -*-

import sys
from concurrent.futures import ThreadPoolExecutor, ProcessPoolExecutor, wait
from functools import reduce


def matrix_calc():
    start = int(sys.argv[1])
    end = int(sys.argv[2])
    
    futures = []
    with ThreadPoolExecutor(max_workers=32) as e:
    # with ProcessPoolExecutor(max_workers=16) as e:
        for i in range(start, end):
            futures.append(e.submit(matrix_mul, matrix(i), matrix_right(i)))

    result = wait(futures)
    return len(result.done)
        
def matrix(size):
    return [[i for n in range(i, i+size) ] for i in range(1, size+1)]

def matrix_right(size):
    return [[n for n in range(1, size+1)] for i in range(1, size+1)]

def matrix_mul(m1, m2):
    sz = len(m1)
    return [[reduce(lambda x,y: x+y ,[m1[i][m] * m2[m][n] for m in range(0,sz)]) for n in range(0,sz)] for i in range(0, sz)]

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
