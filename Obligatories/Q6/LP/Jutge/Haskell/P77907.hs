absValue :: Int -> Int
absValue x
  | x < 0 = -x
  | otherwise = x

power :: Int -> Int -> Int
power _ 0 = 1
power x n 
  | even n = y * y
  | otherwise = y * y * x
  where
    y = power x n_halved
    n_halved = n `div` 2

isPrime :: Int -> Bool
isPrime n 
  | n <= 1 = False
  | n <= 3 = True
  | even n || n `mod` 3 == 0 = False
  | otherwise = not (teDivisors n 4)

teDivisors :: Int -> Int -> Bool
teDivisors n x 
  | x * x > n = False
  | mod n x == 0 = True
  | otherwise = teDivisors n (x+1)

slowFib :: Int -> Int
slowFib 0 = 0
slowFib 1 = 1
slowFib x = slowFib (x-1) + slowFib (x-2)

quickFib :: Int -> Int
quickFib n = fst (quickFibAux n)


quickFibAux :: Int -> (Int, Int)
quickFibAux n 
  | n == 0 = (0,0)
  | n == 1 = (1, 0)
  | otherwise = (a + b, a)
  where
    (a,b) = quickFibAux (n - 1)

