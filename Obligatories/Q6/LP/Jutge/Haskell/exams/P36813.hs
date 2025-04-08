import Data.List (sort)

-- sort :: Ord a => [a] -> [a]

degree :: (Eq a) => [(a, a)] -> a -> Int
degree [] _ = 0
degree (x : xs) y
  | y == fst x || y == snd x = 1 + degree xs y
  | otherwise = degree xs y

degree' :: (Eq a) => [(a, a)] -> a -> Int
degree' l x = foldl (\acc y -> if x == fst y || x == snd y then acc + 1 else acc) 0 l

neighbors :: (Ord a) => [(a, a)] -> a -> [a]
-- neighbors l x = foldl (\neigh (a, b) -> if x == a then neigh ++ [b] else if x == b then neigh ++ [a] else neigh) [] l
neighbors l x = [if x == a then b else a | (a, b) <- l, x == a || x == b]
