-------------------------------- Apartat 1

multEq :: Int -> Int -> [Int]
multEq x y = [x ^ n * y ^ n | n <- [0 ..]]

-------------------------------- Apartat 2

selectFirst :: [Int] -> [Int] -> [Int] -> [Int]
selectFirst l1 l2 l3 = foldl (\x y -> if isSooner y l2 l3 then x ++ [y] else x) [] l1
  where
    isSooner _ [] _ = False
    isSooner x (a : as) []
      -- Si x esta en la lista l2 true
      | x == a = True
      | otherwise = isSooner x as []
    isSooner x (a : as) (b : bs)
      -- Si encontramos x en b antes que en a quiere decir que esta antes en l3
      | x == b = False
      -- Caso contrario
      | x == a = True
      | otherwise = isSooner x as bs

-------------------------------- Apartat 3

myIterate :: (a -> a) -> a -> [a]
myIterate f x = scanl (\a b -> f a) x [x | i <- [1 ..]]

-------------------------------- Apartat 4
type SymTab a = String -> Maybe a

empty :: SymTab a
empty _ = Nothing

get :: SymTab a -> String -> Maybe a
get x = x

set :: SymTab a -> String -> a -> SymTab a
set t k v s = if s == k then Just v else t s

-------------------------------- Apartat 5

data Expr a
  = Val a
  | Var String
  | Sum (Expr a) (Expr a)
  | Sub (Expr a) (Expr a)
  | Mul (Expr a) (Expr a)
  deriving (Show)

eval :: (Num a) => SymTab a -> Expr a -> Maybe a
eval t (Val a) = Just a
eval t (Var s) = t s
eval t (Sum e1 e2) = opera (+) t e1 e2
eval t (Sub e1 e2) = opera (-) t e1 e2
eval t (Mul e1 e2) = opera (*) t e1 e2

opera :: (Num a) => (a -> a -> a) -> SymTab a -> Expr a -> Expr a -> Maybe a
opera f t x y = do
  x' <- eval t x
  y' <- eval t y
  Just (f x' y')