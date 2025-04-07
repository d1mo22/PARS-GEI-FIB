main :: IO ()
main = do
  line <- getLine
  if line /= "*"
    then do
      let name = head $ words line
      let weight = read $ head $ tail $ words line
      let height = read $ last $ words line
      putStrLn (name ++ ": " ++ bmi weight height)
      main
    else
      return ()

bmi :: (Ord a, Num a, Fractional a) => a -> a -> String
bmi w h
  | x < 18 = "underweight"
  | x < 25 = "normal weight"
  | x < 30 = "overweight"
  | x < 40 = "obese"
  | x > 40 = "severely obese"
  where
    x = w / (h * h)
