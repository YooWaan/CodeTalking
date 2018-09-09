# -*- coding: utf-8 -*-

import sys
from concurrent.futures import ThreadPoolExecutor, ProcessPoolExecutor, wait
from functools import reduce


def wd(ss):
    is_word = True
    ch_cnt = len(ss)
    wd_cnt = 0
    lf_cnt = 0
    for i, c in enumerate(ss):
        if c == ' ':
            is_word = True
        elif c == '\n' or c == '\r':
            lf_cnt += 1
        else:
            if is_word:
                wd_cnt += 1
                is_word = False

    return ch_cnt, wd_cnt, lf_cnt


def count(fp):
    with ThreadPoolExecutor(max_workers=32) as e:
        futures = []
        size = 4096
        i = 0
        with open(fp, 'rb') as fin:
            while i != -1:
                by = fin.read(size)
                futures.append(e.submit(wd, by.decode('utf-8')))
                if len(by) == size:
                    fin.seek(size * i)
                    i += 1
                else:
                    i = -1

        result = wait(futures)
        return reduce(lambda x,y: (x[0]+y[0], x[1]+y[1], x[2]+y[2]), [rs.result() for rs in result.done])

def wc_cmd():
    times = int(sys.argv[1])
    files = sys.argv[2:]

    for i in range(1, times+1):
        idx = i % len(files)
        r = count(files[idx])
        print(r)


wc_cmd()

