data STree a = Nil | Node Int a (STree a) (STree a)
  deriving (Show)

instance Functor STree where
  fmap f Nil = Nil
  fmap f (Node x a fe fd) = Node x (f a) (fmap f fe) (fmap f fd)

isOk :: STree a -> Bool
isOk Nil = True
isOk (Node x a fe fd) = x == sumNodes (Node x a fe fd) && isOk fe && isOk fd

sumNodes :: STree a -> Int
sumNodes Nil = 0
sumNodes (Node _ _ fe fd) = 1 + sumNodes fe + sumNodes fd

nthElement :: STree a -> Int -> Maybe a
nthElement Nil _ = Nothing
nthElement (Node x a fe fd) n
  | not (isOk (Node x a fe fd)) = Nothing
  | n == root = Just a
  | n < root = nthElement fe n
  | otherwise = nthElement fd (n - root)
  where
    root = div x 2 + 1

inorder :: STree a -> [a]
inorder Nil = []
inorder (Node x a fe fd) = inorder fe ++ [a] ++ inorder fd

mapToElements :: (a -> b) -> STree a -> [Int] -> [Maybe b]
mapToElements f _ [] = []
mapToElements f (Node n a fe fd) (x : xs) = fmap f (nthElement (Node n a fe fd) x) : mapToElements f (Node n a fe fd) xs
