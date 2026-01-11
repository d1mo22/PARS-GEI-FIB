import Data.Ratio

termes_cosinus :: Rational -> [Rational]
termes_cosinus a = zipWith (*) (cycle [1, -1]) (zipWith (/) (map (a ^) [0, 2 ..]) factorialesPares)

cosinus :: Rational -> Rational -> Rational
cosinus a e = sum (takeWhile (\x -> abs x >= e) (termes_cosinus a))

factorialesPares :: [Rational]
factorialesPares = map factorial [0, 2 ..]
  where
    factorial 0 = 1
    factorial x = x * factorial (x - 1)
