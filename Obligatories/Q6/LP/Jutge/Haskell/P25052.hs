myLength :: [Int] -> Int
myLength [] = 0
myLength (x : xs) = 1 + myLength xs

myMaximum :: [Int] -> Int
myMaximum [x] = x
myMaximum (x : xs) = max x (myMaximum xs)

average :: [Int] -> Float
average x = fromIntegral (sum x) / fromIntegral (myLength x)

remove :: [Int] -> [Int] -> [Int]
remove [] _ = []
remove xs [] = xs
remove (x : xs) ys
  | x `elem` ys = remove xs ys
  | otherwise = x : remove xs ys

buildPalindrome :: [Int] -> [Int]
buildPalindrome x = reverse x ++ x

flatten :: [[Int]] -> [Int]
flatten = concat

oddsNevens :: [Int] -> ([Int], [Int])
oddsNevens [] = ([], [])
oddsNevens (x : xs)
  | even x = (evens, x : odds)
  | otherwise = (x : evens, odds)
  where
    (evens, odds) = oddsNevens xs

primeDivisors :: Int -> [Int]
primeDivisors x
  | x < 2 = []
  | otherwise = filter isPrime [d | d <- [2 .. x], x `mod` d == 0]

isPrime :: Int -> Bool
isPrime n
  | n <= 1 = False
  | n <= 3 = True
  | otherwise = not (teDivisors n 2)

teDivisors :: Int -> Int -> Bool
teDivisors n x
  | x * x > n = False
  | mod n x == 0 = True
  | otherwise = teDivisors n (x + 1)
