module Main (main) where

main = print (func( [ 10, 20, 30, 40, 50 ] ))

func :: [Int] -> Int
func list = foldl (+) 0
           $ map( \(i,x) -> x*i )
           $ zip [0..] list

