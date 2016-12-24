# -*- coding: utf-8 -*-

data = range(11)
print data

##
## argument function
##

# even number check
filter_func = lambda x: x % 2 == 0
# twice
map_func = lambda x: 2*x
# summarise
reduce_func = lambda a,b: a+b

print "filter-->{}".format(filter(filter_func, data))
print "filter -> map-->{}".format(map(map_func, filter(filter_func, data)))
print "filter -> map -> reduce -->{}".format(reduce(reduce_func, map(map_func, filter(filter_func, data))))

##
## return value function
##

def sum_currying():
    def _fn(lst):
        return reduce(reduce_func, map(map_func, filter(filter_func , lst)))
    return _fn

cur_fn = sum_currying()

print "currying-->{}".format(cur_fn(data))
