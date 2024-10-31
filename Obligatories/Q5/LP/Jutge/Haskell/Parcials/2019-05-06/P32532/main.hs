divisors :: Int -> [Int]
divisors n = [x | x <- [1 .. n], n `mod` x == 0]

nbDivisors :: Int -> Int
nbDivisors = length . divisors

moltCompost :: Int -> Bool
moltCompost n = null [x | x <- [1 .. n - 1], nbDivisors x >= nbDivisors n]