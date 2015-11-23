#!/usr/bin/python
# -*- coding: utf-8 -*-

def func(ary):
   sum = 0
   for i, v in enumerate(ary):
       sum += i * v

   return sum

print func([10,20,30,40,50])
