
def func(ary)
  sum = 0
  i = 0
  ary.each{|x| 
    sum += x * i
    i += 1
  }
  return sum
end

puts func([ 10,20,30,40,50 ]) 
