import Data.List

degree :: (Eq a) => [(a, a)] -> a -> Int
degree [] _ = 0
degree (x : xs) n
  | n == fst x || n == snd x = 1 + degree xs n
  | otherwise = degree xs n

-- Sense recursivitat
degree' :: (Eq a) => [(a, a)] -> a -> Int
degree' l x = foldl (\acc y -> if fst y == x || snd y == x then acc + 1 else acc) 0 l

neighbors :: (Ord a) => [(a, a)] -> a -> [a]
neighbors l x = sort $ neighbors' l x
  where
    neighbors' [] _ = []
    neighbors' (x : xs) n
      | n == fst x = snd x : neighbors' xs n
      | n == snd x = fst x : neighbors' xs n
      | otherwise = neighbors' xs n
