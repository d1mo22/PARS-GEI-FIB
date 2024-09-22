eql :: [Int] -> [Int] -> Bool
eql [] [] = True
eql [] ys = False
eql xs [] = False
eql (x : xs) (y : ys)
  | x == y = eql xs ys
  | otherwise = False

prod :: [Int] -> Int
prod [] = 1
prod (x : xs) = x * prod xs

prodOfEvens :: [Int] -> Int
prodOfEvens [] = 1
prodOfEvens (x : xs)
  | even x = x * prodOfEvens xs
  | otherwise = prodOfEvens xs

powersOf2 :: [Int]
powersOf2 = [2 ^ n | n <- [0 ..]]

scalarProduct :: [Float] -> [Float] -> Float
scalarProduct [] ys = 0
scalarProduct xs [] = 0
scalarProduct (x : xs) (y : ys) = x * y + scalarProduct xs ys