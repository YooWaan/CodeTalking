module MinNum
    ( runFunc,
      min1st,
      min2nd
    ) where

import Data.Array
import Data.Array.ST

import Data.List (partition)

sampleX  ::  [Int]
sampleX  = [08,23,09,00,12,11,01,10,13,07,41,04,14,21,05,17,03,19,02,06]

(\\)      ::  Eq a => [a] -> [a] -> [a]
us \\ vs  =   filter (`notElem` vs) us


-- Fist

min1st    :: [Int] -> Int
min1st xs = head ( [0 ..]  \\ xs )

-- Second


min2nd    :: [Int] -> Int
min2nd    = search . checklist

search    :: Array Int Bool -> Int
search    = length . takeWhile id . elems

checklist :: [Int] -> Array Int Bool
checklist xs = accumArray (||) False (0,n) (zip (filter (<= n) xs) (repeat True))
               where n = length xs

-- 3rd

min3rd    :: [Int] -> Int
min3rd    = find . countlist

find      :: Array Int Int -> Int
find      = fst . head . dropWhile ((0/=) . snd) . assocs

countlist :: [Int] -> Array Int Int
countlist xs = accumArray (+) 0 (0,n) (zip xs (repeat 1))
               where n = maximum xs


-- procedural

minprcd   :: [Int] -> Int
minprcd   = search . checklist'

checklist' :: [Int] -> Array Int Bool
checklist' xs = runSTArray (do
                  { a <- newArray (0,n) False;
                    sequence [writeArray a x True | x <- xs, x <= n];
                    return a })
                  where n = length xs

-- divide and conquer algorithm

mindiv     ::  [Int] -> Int
mindiv xs  =   minform 0 (length xs, xs)

minform         ::  Int -> (Int, [Int]) -> Int
minform a (n,xs)
  | n == 0      =   a
  | m == b - a  =   minform b (n-m, vs)
  | otherwise   =   minform a (m, us)
    where  (us,vs)  =  partition (< b) xs
           b        =  a + 1 + n `div` 2
           m        = length us


runFunc :: IO ()
runFunc = do
   putStrLn "first-----"
   print ( min1st sampleX )
   putStrLn "second-----"
   print ( min2nd sampleX )
   putStrLn "third-----"
   print ( min3rd sampleX )
   putStrLn "procedure-----"
   print ( minprcd sampleX )
   putStrLn "divide-----"
   print ( mindiv sampleX )
   putStrLn "done"

