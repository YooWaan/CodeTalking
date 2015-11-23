
emptyList :: Bool
emptyList = let x = undefined : x in null x

nullTake :: Int
nullTake = let x = undefined : x in length (take 10 x)

main = do
   print (take 10 [0..])   -- 無限の配列を扱う
   print (length [ undefined, undefined, undefined ]) -- 未定義な値の配列も扱える
   print emptyList  -- 空リストチェックに未定義を渡す
   print nullTake   -- 未定義な値を10回取得
--   x <- undefined
--   print (length(take 10 x))
