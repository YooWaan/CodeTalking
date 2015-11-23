import Text.Printf (printf)

countChar :: String -> String -> Char -> String
countChar fmt str c = printf fmt
                      $ length
                      $ filter (== c) str

main = do
  putStrLn (countChar "a num %d" "a characters" 'a')
  putStrLn (countChar "c num %d" "a characters" 'c')
