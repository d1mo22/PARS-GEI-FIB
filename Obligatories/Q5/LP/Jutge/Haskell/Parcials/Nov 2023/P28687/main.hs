import Data.Ratio

termes_cosinus :: Rational -> [Rational]
termes_cosinus x = zipWith (*) (cycle [1, -1]) (zipWith (/) (map (x ^) [0, 2 ..]) factorialesPares)

cosinus :: Rational -> Rational -> Rational
cosinus x n = sum (takeWhile (\term -> abs term >= n) (termes_cosinus x))

factorialesPares :: [Rational]
factorialesPares = map factorial [0, 2 ..]
  where
    factorial 0 = 1
    factorial n = n * factorial (n - 1)