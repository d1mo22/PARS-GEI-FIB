main :: IO ()
main = do
  contents <- getContents
  mapM_ (print . evalExpr) (lines contents)

evalExpr :: String -> Either String Int
evalExpr s = eval (words s) []

eval :: [String] -> [Int] -> Either String Int
eval [] [r] = Right r
eval ("+" : ws) (x : y : s) = eval ws ((y + x) : s)
eval ("-" : ws) (x : y : s)
  | x > y = Left "neg"
  | otherwise = eval ws ((y - x) : s)
eval ("*" : ws) (x : y : s) = eval ws ((y * x) : s)
eval ("/" : ws) (x : y : s)
  | x == 0 = Left "div0"
  | y `mod` x /= 0 = Left "divE"
  | otherwise = eval ws ((y `div` x) : s)
eval (x : ws) s = eval ws (read x : s)
