countIf :: (Int -> Bool) -> [Int] -> Int
countIf p xs = length $ filter p xs

pam :: [Int] -> [Int -> Int] -> [[Int]]
pam xs fs = map (`map` xs) fs

pam2 :: [Int] -> [Int -> Int] -> [[Int]]
pam2 xs fs = map (\x -> map ($ x) fs) xs


filterFoldl :: (Int -> Bool) -> (Int -> Int -> Int) -> Int ->[Int] -> Int
filterFoldl p f n xs = foldl f n (filter p xs)

insert :: (Int -> Int -> Bool) -> [Int] -> Int -> [Int]
insert p xs y = takeWhile(not . p y) xs ++ y : dropWhile (not . p y)xs

insertionSort :: (Int -> Int -> Bool) -> [Int] -> [Int]
insertionSort f xs = foldl (insert f) [] xs
