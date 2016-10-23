import Data.IORef

getclosure :: IORef Int -> IO Int
getclosure = do
  -- do not work
  -- cnt <- newIORef 0
  let f :: IORef Int -> IO Int; f cnt = modifyIORef cnt (+1) >> readIORef cnt
  f

main :: IO ()
main = do
  let n = (\x -> \y -> x+y) 1 2
  print n
  let f :: Int -> Int -> Int; f x y = x+y
  print (f 1 2)

  cnt <- newIORef 0
  let c = getclosure
  print =<< c cnt
  print =<< c cnt
  print =<< c cnt
