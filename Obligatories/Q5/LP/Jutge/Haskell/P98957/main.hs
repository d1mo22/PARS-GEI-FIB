ones :: [Integer]
ones = repeat 1

nats :: [Integer]
nats = iterate (+ 1) 0

ints :: [Integer]
ints = tail $ concatMap (\x -> [x, -x]) nats

triangulars :: [Integer]
triangulars = map (\n -> n * (n + 1) `div` 2) nats

factorials :: [Integer]
factorials = scanl (*) 1 [1 ..]

fibs :: [Integer]
fibs = 0 : 1 : zipWith (+) fibs (tail fibs)

primes :: [Integer]
primes = garbell [2 ..]
  where
    garbell (p : xs) = p : garbell [x | x <- xs, x `mod` p /= 0]

merge :: [Integer] -> [Integer] -> [Integer]
merge (x : xs) (y : ys)
  | x < y = x : merge xs (y : ys)
  | y < x = y : merge (x : xs) ys
  -- Per eliminar els duplicats quan son iguals
  | otherwise = x : merge xs ys

hammings :: [Integer]
hammings = 1 : merge (map (2 *) hammings) (merge (map (3 *) hammings) (map (5 *) hammings))

lookNsay :: [Integer]
lookNsay = map read $ iterate next "1"
  where
    next :: String -> String
    next [] = []
    next xs =
      let (prefix, rest) = span (== head xs) xs
       in show (length prefix) ++ [head xs] ++ next rest

tartaglia :: [[Integer]]
tartaglia = iterate (\row -> zipWith (+) ([0] ++ row) (row ++ [0])) [1]
