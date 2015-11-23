
main = do
   xs <- getContents
   putStr (unlines $ reverse $ take 10 $ reverse $ lines xs)

