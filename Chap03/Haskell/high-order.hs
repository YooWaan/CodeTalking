
filter_cond :: Int -> Bool 
filter_cond x = x `rem` 2 == 0

map_fn :: Int -> Int
map_fn x = 2 * x

reduce_fn :: Int -> Int -> Int
reduce_fn x y = x + y


currying :: ([Int] -> Int)
currying = do
  let f :: [Int] -> Int ; f li = foldl reduce_fn 0 (map map_fn (filter filter_cond li))
  f

main = do
  let li  = [0,1 .. 10]
  print (filter filter_cond li)
  print (map map_fn (filter filter_cond li))
  print (foldl reduce_fn 0 (map map_fn (filter filter_cond li)))

  let sumFn = currying
  print (sumFn li)
