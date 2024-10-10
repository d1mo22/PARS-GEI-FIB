data Tree a = Node a (Tree a) (Tree a) | Empty 
    deriving (Show)

size :: Tree a -> Int
size Empty = 0
size (Node x fd fe) = 1 + size fd + size fe

height :: Tree a -> Int
height Empty = 0;
height (Node x fd fe) = 1 + max (height fd) (height fe)

equal :: Eq a => Tree a -> Tree a -> Bool 
equal Empty Empty = True
equal _ Empty = False
equal Empty _ = False
equal (Node x fe fd) (Node y fe' fd') = x == y && equal fe fe' && equal fd fd'

isomorphic :: Eq a => Tree a -> Tree a -> Bool
isomorphic Empty Empty = True
isomorphic (Node x fe fd) (Node y fe' fd') = x == y && equal fe fd' && equal fd fe'

preOrder :: Tree a -> [a]
preOrder Empty = []
preOrder (Node x fe fd) = x : preOrder fe ++ preOrder fd

postOrder :: Tree a -> [a]
postOrder Empty = []
postOrder (Node x fe fd) = postOrder fe ++ postOrder fd ++ [x]

inOrder :: Tree a -> [a]
inOrder Empty = []
inOrder (Node x fe fd) = inOrder fe ++ [x] ++ inOrder fd

breadthFirst :: Tree a -> [a] 
breadthFirst Empty = []
breadthFirst x = bf [x]
    where
    bf [] = []
    bf (Empty : xs) = bf xs
    bf ((Node x fe fd) : xs) = x : bf (xs ++ [fe, fd])

build :: Eq a => [a] -> [a] -> Tree a
build [] [] = Empty
build [x] [y] = Node x Empty Empty
build (x : pre) ino = Node x (build epre eino) (build dpre dino)
    where
        eino = takeWhile (/=x) ino
        lastl = last eino
        dino = tail $ dropWhile (/= x) ino
        epre = takeWhile (/= lastl) pre ++ [lastl]
        dpre = tail $ dropWhile (/= lastl) pre

overlap :: (a -> a -> a) -> Tree a -> Tree a -> Tree a
overlap f Empty Empty = Empty
overlap f x Empty = x
overlap f Empty y = y
overlap f (Node x fe fd) (Node y fe' fd') = Node (f x y) (overlap f fe fe') (overlap f fd fd')