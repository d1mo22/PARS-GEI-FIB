-- Recursivity
myFoldl :: (a -> b -> a) -> a -> [b] -> a
myFoldl f n [] = n
myFoldl f n (x : xs) = myFoldl f (f n x) xs

-- Recursivity
myFoldr :: (a -> b -> b) -> b -> [a] -> b
myFoldr f n [] = n
myFoldr f n (x : xs) = f x (myFoldr f n xs)

-- Recursivity
myIterate :: (a -> a) -> a -> [a]
myIterate f n = n : myIterate f (f n)

-- Recursivity
myUntil :: (a -> Bool) -> (a -> a) -> a -> a
myUntil b f n
  | b n = n
  | otherwise = myUntil b f (f n)

myMap :: (a -> b) -> [a] -> [b]
myMap f = myFoldl (\x y -> x ++ [f y]) [] 

myFilter :: (a -> Bool) -> [a] -> [a]
myFilter p = myFoldl (\x y -> if p y then x ++ [y] else x) []

myAll :: (a -> Bool) -> [a] -> Bool
myAll p = myFoldr (\x acc -> p x && acc) True

myAny :: (a -> Bool) -> [a] -> Bool
myAny p = myFoldr (\x acc -> p x || acc) False
--Do it with a foldl
-- Recursivity
myZip :: [a] -> [b] -> [(a, b)]
myZip _ [] = []
myZip [] _ = []
myZip (x : xs) (y : ys) = (x, y) : myZip xs ys

myZipWith :: (a -> b -> c) -> [a] -> [b] -> [c]
myZipWith f xs ys = foldr (\(x,y) as -> f x y : as) [] (zip xs ys)


