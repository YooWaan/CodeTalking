# -*- coding: utf-8 -*-

from __future__ import division, print_function, absolute_import, unicode_literals

import sys
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

def read_files(files):
    print('fils {}'.format(files))
    plot_df = None
    for f in files:
        df = pd.read_csv(f, delimiter='\s+', header=None).rename(columns={0:'sec', 1:'pid', 2:'cpu%', 3:'mem(kb)', 4:'etime'})
        hue = pd.Series([f for n in range(1, len(df.index)+1)])
        df['name'] = hue
        plot_df = df if plot_df is None else pd.concat([plot_df, df])

    return plot_df

def save_figure(y='cpu%', df=None, fname='fig.png'):
    # sns.scatterplot(x='sec', y=y, hue='name', style='name', data=df)
    sns.lineplot(x='sec', y=y, hue='name', style='name', data=df)
    plt.savefig(fname)

args = sys.argv

ug = '''
  -amdar files....
'''

if len(args) == 0:
    print(ug)
elif args[1] in ['cpu%', 'mem(kb)']:
    save_figure(y=args[1], df=read_files(args[3:]), fname=args[2])

