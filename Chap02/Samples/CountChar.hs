import Text.Printf (printf)

countChar :: String -> Char -> Int
countChar str c = length $ filter (== c) str

countA :: String -> Int
countA str = countChar str 'a'

main = do
   printf "num %d\n" (countChar "a characters" 'a')
   printf "apply %d\n" (countA "a characters")
   printf "calc %d\n" ((2 ^) 4 :: Int)

