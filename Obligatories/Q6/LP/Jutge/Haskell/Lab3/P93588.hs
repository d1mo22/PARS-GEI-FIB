myMap :: (a -> b) -> [a] -> [b]
myMap f xs = [f x | x <- xs]

myFilter :: (a -> Bool) -> [a] -> [a]
myFilter p xs = [x | x <- xs, p x]

myZipWith :: (a -> b -> c) -> [a] -> [b] -> [c]
myZipWith op xs ys = [op x y | (x, y) <- zip xs ys]

thingify :: [Int] -> [Int] -> [(Int, Int)]
thingify xs ys = [(x, y) | x <- xs, y <- ys, x `mod` y == 0]

factors :: Int -> [Int]
factors n = [x | x <- [1 .. n], n `mod` x == 0]
