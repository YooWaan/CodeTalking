# -*- coding: utf-8 -*-

from __future__ import division, print_function, absolute_import, unicode_literals

import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

plot_dir = './plot-data/'

files = ['amdar_py.tsv', 'amdar_go.tsv', 'amdar_scala.tsv']

def read_files(files):
    plot_df = None
    for f in files:
        df = pd.read_csv(plot_dir + f, delimiter='\s+', header=None).rename(columns={0:'sec', 1:'pid', 2:'cpu%', 3:'mem(kb)', 4:'etime'})
        hue = pd.Series([f for n in range(1, len(df.index)+1)])
        df['name'] = hue
        plot_df = df if plot_df is None else pd.concat([plot_df, df])

    return plot_df

def save_figure(y='cpu%', df=None, fname='fig.png'):
    sns.scatterplot(x='sec', y=y, hue='name', style='name', data=df)
    plt.savefig(fname)

args = sys.argv

ug = '''
  -amdar files....
'''

print('---> %s' % args.length)

if len(args) == 0:
    print(ug)
elif args[0] == '-amdar':
    save_figure(y='cpu%', df=read_files(args[1:]), fname='amdar01.png')

