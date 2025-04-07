import Data.Ratio

myUntil :: (a -> Bool) -> (a -> a) -> a -> a
myUntil p f x = head $ dropWhile p (iterate f x)

egypt :: Rational -> [Rational]
egypt r = fst $ myUntil (\(_, frac) -> frac /= 0) nextStep ([], r)
  where
    nextStep (acc, 0) = (acc, 0)
    nextStep (acc, frac) = (acc ++ [unit], frac - unit)
      where
        n = numerator frac
        d = denominator frac
        nextDenom = ceiling (fromIntegral d / fromIntegral n)
        unit = 1 % nextDenom

main :: IO ()
main = do
  line <- getLine
  let paraules = words line
  let x = (read $ head paraules) :: Integer
  let y = (read $ last paraules) :: Integer
  print $ egypt (x % y)
  main
