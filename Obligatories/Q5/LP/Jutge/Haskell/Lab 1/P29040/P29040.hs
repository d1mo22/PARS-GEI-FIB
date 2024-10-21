insert :: [Int] -> Int -> [Int]
insert [] y = [y]
insert (x : xs) y
  | x > y = y : x : xs
  | otherwise = x : insert xs y

isort :: [Int] -> [Int]
isort [] = []
isort (x : xs) = insert (isort xs) x

remove :: [Int] -> Int -> [Int]
remove [] _ = []
remove (x : xs) y
  | y == x = xs
  | otherwise = x : remove xs y

ssort :: [Int] -> [Int]
ssort [] = []
ssort [x] = [x]
ssort (x : xs)
  | m < x = m : ssort (x : remove xs m)
  | otherwise = x : ssort xs
  where
    m = minimum xs

merge :: [Int] -> [Int] -> [Int]
merge [] [] = []
merge x [] = x
merge [] x = x
merge (x : xs) (y : ys)
  | x > y = y : merge (x : xs) ys
  | otherwise = x : merge xs (y : ys)

msort :: [Int] -> [Int]
msort [] = []
msort [x] = [x]
msort xs = merge (msort left) (msort right)
  where
    (left, right) = splitAt (div (length xs) 2) xs

qsort :: [Int] -> [Int]
qsort [] = []
qsort (p : xs) = qsort menors ++ [p] ++ qsort majors
  where
    menors = [x | x <- xs, x < p]
    majors = [x | x <- xs, x >= p]

genQsort :: (Ord a) => [a] -> [a]
genQsort [] = []
genQsort (p : xs) = genQsort menors ++ [p] ++ genQsort majors
  where
    menors = [x | x <- xs, x < p]
    majors = [x | x <- xs, x >= p]