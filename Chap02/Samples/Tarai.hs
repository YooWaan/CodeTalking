--  echo "tarai 10 5 0" | ghci Tarai.hs 
--  echo "tarai 20 10 0" | ghci Tarai.hs 

import System.Environment (getArgs)

tarai :: Int -> Int -> Int -> Int
tarai x y z
    | x <= y    = y
    | otherwise = tarai
                  (tarai (x - 1) y z)
                  (tarai (y - 1) z x)
                  (tarai (z - 1) x y)

main = do
  args <- getArgs
  let nums = map cv args where cv str = read str :: Int
  if length nums >= 3
    then print (tarai (nums !! 0) (nums !! 1) (nums !! 2))
    else print "illegal argument !!"

{--

  if length nums >= 3
     then print (tarai (nums !! 0) (nums !! 1) (nums !! 2))
     else print "illegal argument !!"

実際の処理はこれをしているだけ
taraiLess :: Int -> Int -> Int -> Int
taraiLess x y z
    | x <= y     = y
    | y <= z     = z
    | otherwise  = x
--}
