----------------------------------------------------------- Romans
value :: Char -> Int
value 'I' = 1
value 'V' = 5
value 'X' = 10
value 'L' = 50
value 'C' = 100
value 'D' = 500
value 'M' = 1000

-- I, II, III, IV, V, VI, VII, VIII, IX, X, XI

roman2int :: String -> Int
roman2int "" = 0
roman2int [x] = value x
roman2int (x : y : s)
  | value x < value y = -value x + roman2int (y : s)
  | otherwise = value x + roman2int (y : s)

roman2int' :: String -> Int
roman2int' s = snd $ foldr f (0, 0) s
  where
    f c (prev, acc)
      | value c < prev = (value c, acc - value c)
      | otherwise = (value c, acc + value c)

----------------------------------------------------------- Taylor sqrt
taylor :: Float -> Float -> Float
taylor x tx = 0.5 * (tx + x / tx)

arrels :: Float -> [Float]
arrels x = iterate (taylor x) x

diff :: Float -> (Float, Float) -> Bool
diff e (n1, n2) = abs (n1 - n2) > e

arrel :: Float -> Float -> Float
arrel x e = snd (head (dropWhile (diff e) (zip (arrels x) (tail $ arrels x))))

----------------------------------------------------------- Arbres
data LTree a = Leaf a | Node (LTree a) (LTree a)

instance (Show a) => Show (LTree a) where
  show (Leaf x) = "{" ++ show x ++ "}"
  show (Node a b) = "<" ++ show a ++ "," ++ show b ++ ">"

build :: [a] -> LTree a
build [x] = Leaf x
build l = Node (build l1) (build l2)
  where
    len = div (length l + 1) 2
    l1 = take len l
    l2 = drop len l

zipLTrees :: LTree a -> LTree b -> Maybe (LTree (a, b))
zipLTrees (Node t1 t2) (Leaf y) = Nothing
zipLTrees (Leaf x) (Node t1 t2) = Nothing
zipLTrees (Leaf x) (Leaf y) = Just (Leaf (x, y))
zipLTrees (Node t1 t2) (Node t3 t4) = do
  tx <- zipLTrees t1 t3
  ty <- zipLTrees t2 t4
  return (Node tx ty)