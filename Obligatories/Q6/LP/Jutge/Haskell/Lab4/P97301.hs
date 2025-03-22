fizzBuzz :: [Either Int String]
fizzBuzz = map fizz [0 ..]
  where
    fizz :: Int -> Either Int String
    fizz x
      | x `mod` 15 == 0 = Right "FizzBuzz"
      | x `mod` 3 == 0 = Right "Fizz"
      | x `mod` 5 == 0 = Right "Buzz"
      | otherwise = Left x
