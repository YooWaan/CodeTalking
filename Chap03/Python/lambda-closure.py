# -*- coding: utf-8 -*-

n = (lambda x,y: x+y)( 3, 3 )
print "calc = {}".format(n)

f = lambda x,y: x+y
print "func = {}".format(f(2,3))

def get_closure():
    def inc():
        inc.cnt += 1
        return inc.cnt
    inc.cnt = 0
    return inc


c = get_closure()

print "1 -> {}".format(c())
print "2 -> {}".format(c())
print "3 -> {}".format(c())
print "4 -> {}".format(c())


'''
 DO NOT WORK

def get_closure():
    cnt = 0
    def inc():
        cnt += 1
        return cnt
    return inc
'''


