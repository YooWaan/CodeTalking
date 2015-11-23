#!/usr/bin/python
# -*- coding: utf-8 -*-
#


def func(ary):
   return reduce( lambda a,b   : a+b ,
          map(    lambda (i,x) : i*x ,
          zip(    range(0,len(ary), 1), ary) ))

print func([ 10, 20, 30, 40, 50 ])
