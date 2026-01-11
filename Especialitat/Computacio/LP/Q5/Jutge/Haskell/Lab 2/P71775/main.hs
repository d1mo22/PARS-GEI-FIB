countIf :: (Int -> Bool) -> [Int] -> Int
countIf f xs = length (filter f xs)

pam :: [Int] -> [Int -> Int] -> [[Int]]
pam xs fs = map (`map` xs) fs

pam2 :: [Int] -> [Int -> Int] -> [[Int]]
pam2 xs fs = map (\x -> map ($ x) fs) xs

filterFoldl :: (Int -> Bool) -> (Int -> Int -> Int) -> Int -> [Int] -> Int
filterFoldl c f y xs = foldl f y (filter c xs)

insert :: (Int -> Int -> Bool) -> [Int] -> Int -> [Int]
insert f xs y = takeWhile (not . f y) xs ++ y : dropWhile (not . f y) xs

insertionSort :: (Int -> Int -> Bool) -> [Int] -> [Int]
insertionSort f xs = foldl (insert f) [] xs