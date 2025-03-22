data Tree a = Node a (Tree a) (Tree a) | Empty deriving (Show)

size :: Tree a -> Int
size Empty = 0
size (Node _ fe fd) = 1 + size fe + size fd

height :: Tree a -> Int
height Empty = 0
height (Node _ fe fd) = 1 + max (height fe) (height fd)

equal :: (Eq a) => Tree a -> Tree a -> Bool
equal Empty Empty = True
equal Empty _ = False
equal _ Empty = False
equal (Node a fe fd) (Node b fe' fd') = a == b && equal fe fe' && equal fd fd'

isomorphic :: (Eq a) => Tree a -> Tree a -> Bool
isomorphic Empty Empty = True
isomorphic _ Empty = False
isomorphic Empty _ = False
isomorphic (Node a fe fd) (Node b fe' fd') = a == b && equal fe fd' && equal fd fe'

preOrder :: Tree a -> [a]
preOrder Empty = []
preOrder (Node a fe fd) = [a] ++ preOrder fe ++ preOrder fd

postOrder :: Tree a -> [a]
postOrder Empty = []
postOrder (Node a fe fd) = postOrder fe ++ postOrder fd ++ [a]

inOrder :: Tree a -> [a]
inOrder Empty = []
inOrder (Node a fe fd) = inOrder fe ++ [a] ++ inOrder fd

breadthFirst :: Tree a -> [a]
breadthFirst Empty = []
breadthFirst x = bf [x]
  where
    bf [] = []
    bf (Empty : xs) = bf xs
    bf ((Node x fe fd) : xs) = x : bf (xs ++ [fe, fd])

build :: (Eq a) => [a] -> [a] -> Tree a
build [] [] = Empty
build [x] [y] = Node x Empty Empty
build (x : pre) ino = Node x (build epre eino) (build dpre dino)
  where
    eino = takeWhile (/= x) ino
    lastl = last eino
    dino = tail $ dropWhile (/= x) ino
    epre = takeWhile (/= lastl) pre ++ [lastl]
    dpre = tail $ dropWhile (/= lastl) pre

overlap :: (a -> a -> a) -> Tree a -> Tree a -> Tree a
overlap f Empty Empty = Empty
overlap f x Empty = x
overlap f Empty x = x
overlap f (Node a fe fd) (Node b fe' fd') = Node (f a b) (overlap f fe fe') (overlap f fd fd')

t7 = Node 7 Empty Empty

t6 = Node 6 Empty Empty

t5 = Node 5 Empty Empty

t4 = Node 4 Empty Empty

t3 = Node 3 t6 t7

t2 = Node 2 t4 t5

t1 = Node 1 t2 t3

t1' = Node 1 t3 t2
