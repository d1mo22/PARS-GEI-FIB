import Text.Parsec (parse)

data Temps = Temps Int Int

instance Show Temps where
  show (Temps x y) = pad x ++ ":" ++ pad y
    where
      pad n = if n < 10 then '0' : show n else show n

data Arbre a = Arbre a [Arbre a]

suma :: Temps -> Temps -> Temps
suma (Temps x1 y1) (Temps x2 y2) = Temps (x1 + x2 + carry) (mod totalMinutes 60)
  where
    totalMinutes = y1 + y2
    carry = totalMinutes `div` 60

sumes :: [Temps] -> Temps
sumes = foldr suma (Temps 0 0)

sumesArbre :: Arbre Temps -> Temps
sumesArbre (Arbre a []) = a
sumesArbre (Arbre a xs) = suma a (sumes (map sumesArbre xs))

main :: IO ()
main = do
  line <- getLine
  let values = words line
  print $ sumes $ parseTemps values

parseTemps :: [String] -> [Temps]
parseTemps [] = []
parseTemps (x : xs) = Temps (read h) (read m) : parseTemps xs
  where
    (h, _ : m) = break (== ':') x
