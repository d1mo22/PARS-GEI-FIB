data Tree a = Empty | Node a (Tree a) (Tree a)
  deriving (Show)

instance Foldable Tree where
  foldr f acc Empty = acc
  foldr f acc (Node x left right) = foldr f (f x (foldr f acc right)) left

avg :: Tree Int -> Double
avg Empty = 0
avg x = fromIntegral (sum x) / fromIntegral (length x)

-- Concatenar amb espais tots els nodes del arbre
cat :: Tree String -> String
cat tree = unwords (catHelper tree)
  where
    catHelper :: Tree String -> [String]
    catHelper Empty = []
    catHelper (Node x left right) = [x] ++ catHelper left ++ catHelper right
