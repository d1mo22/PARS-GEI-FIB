{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}

{-# HLINT ignore "Use foldr" #-}

myLength :: [Int] -> Int
myLength [] = 0
myLength (_ : xs) = 1 + myLength xs

myMaximum :: [Int] -> Int
myMaximum (x : xs) = max x (myMaximum xs)

mySuma :: [Int] -> Int
mySuma [] = 0
mySuma (x : xs) = x + mySuma xs

average :: [Int] -> Float
average x = fromIntegral (mySuma x) / fromIntegral (myLength x)

buildPalindrome :: [Int] -> [Int]
buildPalindrome [] = []
buildPalindrome x = reverse x ++ x

-- remove :: [Int] -> [Int] -> [Int]
-- flatten :: [[Int]] -> [Int]
-- oddsNevens :: [Int] -> ([Int], [Int])
-- primeDivisors :: Int -> [Int]