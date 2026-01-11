import Data.Ratio

myUntil :: (a -> Bool) -> (a -> a) -> a -> a
myUntil p f x = head $ dropWhile p (iterate f x)

egypt :: Rational -> [Rational]
egypt r = reverse $ fst $ myUntil (\(_, frac) -> frac /= 0) nextStep ([], r)
  where
    nextStep (acc, 0) = (acc, 0)
    nextStep (acc, frac) = (unit : acc, residuo)
      where
        x = numerator frac
        y = denominator frac
        unit = 1 % ceiling (y % x)
        residuo = frac - unit

main :: IO ()
main = do
  line <- getLine
  let paraules = words line
  let x = (read $ head paraules) :: Integer
  let y = (read $ last paraules) :: Integer
  print $ egypt (x % y)
  main
