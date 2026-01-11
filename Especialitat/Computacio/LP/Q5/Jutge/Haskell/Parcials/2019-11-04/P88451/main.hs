{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}

{-# HLINT ignore "Use newtype instead of data" #-}

data Tree a = Empty | Node a (Tree a) (Tree a)

-- inorder = left root right
instance (Show a) => Show (Tree a) where
  show Empty = "()"
  show (Node x left right) = "(" ++ show left ++ "," ++ show x ++ "," ++ show right ++ ")"

instance Functor Tree where
  fmap f Empty = Empty
  fmap f (Node x left right) = Node (f x) (fmap f left) (fmap f right)

doubleT :: (Num a) => Tree a -> Tree a
doubleT = fmap (* 2)

data Forest a = Forest [Tree a] deriving (Show)

instance Functor Forest where
  fmap f (Forest trees) = Forest (map (fmap f) trees)

doubleF :: (Num a) => Forest a -> Forest a
doubleF = fmap (* 2)