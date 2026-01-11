flatten :: [[Int]] -> [Int]
flatten list = foldr (++) [] list

myLength :: String -> Int
myLength string = sum $ map (const 1) string

myReverse :: [Int] -> [Int]
myReverse list = foldl (flip (:)) [] list

countIn :: [[Int]] -> Int -> [Int]
countIn list needle = map (length . filter (== needle)) list

firstWord :: String -> String
firstWord text = takeWhile (/= ' ') (dropWhile (== ' ') text)
