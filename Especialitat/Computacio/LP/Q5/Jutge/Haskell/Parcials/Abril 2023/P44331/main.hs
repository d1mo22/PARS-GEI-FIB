main :: IO ()
main = do
  contents <- getContents
  mapM_ (print . evalExpr) (lines contents)

eval :: [String] -> [Int] -> Either String Int
eval [] [r] = Right r
eval ("+" : ws) (x : y : s) = eval ws ((y + x) : s)
eval ("*" : ws) (x : y : s) = eval ws ((y * x) : s)
eval ("-" : ws) (x : y : s)
  | x > y = Left "neg"
  | otherwise = eval ws ((y - x) : s)
eval ("/" : ws) (0 : y : s) = Left "div0"
eval ("/" : ws) (x : y : s)
  | y `mod` x /= 0 = Left "divE"
  | otherwise = eval ws (y `div` x : s)
eval (n : ws) s = eval ws (read n : s)

evalExpr :: String -> Either String Int
evalExpr s = eval (words s) []