# -*- coding: utf-8 -*-

from __future__ import division, print_function, absolute_import, unicode_literals

import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

files = ['./result/amdar_py.tsv', './result/amdar_go.tsv']

'''
for f in files:
    df = pd.read_csv(f, delimiter='\s+', header=None).rename(columns={0:'pid', 1:'cpu%', 2:'mem(kb)', 3:'time'})
    rownum = pd.Series([n for n in range(1, len(df.index)+1)])
    # print(rownum)
    df['point'] = rownum
    # print(df)

    sns.scatterplot(x='point', y='cpu%', data=df)
    # sns.scatterplot(x='time', y='cpu%', df)

plt.savefig('cpu.png')
'''

for f in files:
    df = pd.read_csv(f, delimiter='\s+', header=None).rename(columns={0:'pid', 1:'cpu%', 2:'mem(kb)', 3:'time'})
    rownum = pd.Series([n for n in range(1, len(df.index)+1)])
    # print(rownum)
    df['point'] = rownum
    # print(df)

    sns.scatterplot(x='point', y='mem(kb)', data=df)
    # sns.scatterplot(x='time', y='cpu%', df)

plt.savefig('mem.png')
