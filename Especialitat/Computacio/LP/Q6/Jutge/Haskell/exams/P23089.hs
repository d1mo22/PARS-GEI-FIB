myUnfoldr :: (b -> Maybe (a, b)) -> b -> [a]
myUnfoldr f x = case f x of
  Nothing -> []
  Just (a, b) -> a : myUnfoldr f b

myReplicate :: a -> Int -> [a]
myReplicate x n = myUnfoldr f n
  where
    f 0 = Nothing
    f i = Just (x, i - 1)

myIterate :: (a -> a) -> a -> [a]
myIterate f x = myUnfoldr (\x -> Just (x, f x)) x

myMap :: (a -> b) -> [a] -> [b]
myMap f as = myUnfoldr f' as
  where
    f' [] = Nothing
    f' (a : as) = Just (f a, as)

data Bst a = Empty | Node a (Bst a) (Bst a)

instance (Show a) => Show (Bst a) where
  show Empty = "."
  show (Node a fe fd) = "(" ++ show a ++ " " ++ show fe ++ " " ++ show fd ++ ")"

add :: (Ord a) => a -> Bst a -> Bst a
add x Empty = Node x Empty Empty
add x (Node y l r)
  | x < y = Node y (add x l) r
  | x > y = Node y l (add x r)
  | otherwise = Node y l r

adder :: (Ord a) => (Bst a, [a]) -> Maybe (Bst a, (Bst a, [a]))
adder (t, []) = Nothing
adder (t, x : xs) = Just (t', (t', xs))
  where
    t' = add x t