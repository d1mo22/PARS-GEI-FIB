eql :: [Int] -> [Int] -> Bool
eql [] [] = True
eql x [] = False
eql [] y = False
eql (x:xs) (y:ys)
  | x == y = eql xs ys
  | otherwise = False

prod :: [Int] -> Int
prod = foldl (*) 1

--Even == Parell Odd == Senar
prodOfEvens :: [Int] -> Int
prodOfEvens x = foldl (*) 1 (filter even x)

powersOf2 :: [Int]
powersOf2 = iterate (*2) 1  

scalarProduct :: [Float] -> [Float] -> Float
scalarProduct [] [] = 0
scalarProduct (x:xs) (y:ys) = x*y + scalarProduct xs ys
