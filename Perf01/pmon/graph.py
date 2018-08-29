# -*- coding: utf-8 -*-

from __future__ import division, print_function, absolute_import, unicode_literals

import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

plot_dir = './plot-data/'

files = ['amdar_py.tsv', 'amdar_go.tsv', 'amdar_scala.tsv']

plot_df = None
for f in files:
    df = pd.read_csv(plot_dir + f, delimiter='\s+', header=None).rename(columns={0:'sec', 1:'pid', 2:'cpu%', 3:'mem(kb)', 4:'etime'})
    hue = pd.Series([f for n in range(1, len(df.index)+1)])
    df['name'] = hue
    plot_df = df if plot_df is None else pd.concat([plot_df, df])
    
    '''
    ax = df.plot(x="sec", y="cpu%", legend=False)
    ax2 = ax.twinx()
    df.plot(x="sec", y="mem(kb)", legend=False)
    ax.figure.legend()
    '''

    # sns.scatterplot(x='time', y='cpu%', df)

sns.scatterplot(x='sec', y='cpu%', hue='name', style='name', data=plot_df)
plt.savefig('fig.png')

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
'''
