flatten :: [[Int]] -> [Int]
flatten = foldr (++) []

myLength :: String -> Int
myLength x = sum $ map (const 1) x

myReverse :: [Int] -> [Int]
myReverse = foldl (flip (:)) []

countIn :: [[Int]] -> Int -> [Int]
countIn xs y = map (length . filter (== y)) xs

firstWord :: String -> String
firstWord s = takeWhile (/= ' ')(dropWhile (== ' ') s)
