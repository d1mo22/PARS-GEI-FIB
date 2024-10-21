-- Es pot fer servir recursivitat
myFoldl :: (a -> b -> a) -> a -> [b] -> a
myFoldl _ a [] = a
myFoldl f a (b : bs) = myFoldl f (f a b) bs

myFoldr :: (a -> b -> b) -> b -> [a] -> b
myFoldr _ b [] = b
myFoldr f b (a : as) = f a (myFoldr f b as)

myIterate :: (a -> a) -> a -> [a]
myIterate f a = a : myIterate f (f a)

myZip :: [a] -> [b] -> [(a, b)]
myZip [] _ = []
myZip _ [] = []
myZip (x : xs) (y : ys) = (x, y) : myZip xs ys

myUntil :: (a -> Bool) -> (a -> a) -> a -> a
myUntil c f x
  | c x = x
  | otherwise = myUntil c f (f x)

myMap :: (a -> b) -> [a] -> [b]
myMap f = foldr (\c i -> f c : i) []

myFilter :: (a -> Bool) -> [a] -> [a]
myFilter f = foldr (\c i -> if f c then c : i else i) []

myAll :: (a -> Bool) -> [a] -> Bool
myAll f = foldr (\x acumulated -> f x && acumulated) True

myAny :: (a -> Bool) -> [a] -> Bool
myAny f = foldr (\x acumulated -> f x || acumulated) False

myZipWith :: (a -> b -> c) -> [a] -> [b] -> [c]
myZipWith f xs ys = foldr (\(x, y) as -> f x y : as) [] (zip xs ys)