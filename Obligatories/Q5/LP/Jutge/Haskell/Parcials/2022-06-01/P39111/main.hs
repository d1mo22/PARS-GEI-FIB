import Data.Binary.Builder (putInt32be)
import Data.List (sort)

type Pos = (Int, Int) -- la casella inferior esquerra es (1,1)

dins :: Pos -> Bool
dins p = fst p <= 8 && snd p <= 8 && fst p > 0 && snd p > 0

moviments :: Pos -> [Pos]
moviments p = filter dins [(x + dx, y + dy) | (dx, dy) <- [(2, 1), (2, -1), (-2, 1), (-2, -1), (1, 2), (-1, 2), (1, -2), (-1, -2)]]
  where
    (x, y) = p

potAnar3 :: Pos -> Pos -> Bool
potAnar3 p q = q `elem` concatMap moviments (concatMap moviments (moviments p))

potAnar3' :: Pos -> Pos -> Bool
potAnar3' p q =
  q `elem` (moviments p >>= moviments >>= moviments)

-- fst = x | snd = y
