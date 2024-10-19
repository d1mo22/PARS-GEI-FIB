main :: IO ()
main = do
  line <- getLine
  if line /= "*"
    then do
      let ws = words line
      let name = head ws
      let weight = read $ ws !! 1
      let height = read $ ws !! 2
      putStrLn (name ++ ": " ++ message (imc weight height))
      main
    else
      return ()

message :: (Ord a, Num a) => a -> String
message x
  | x < 18 = "magror"
  | x < 25 = "corpulencia normal"
  | x < 30 = "sobrepes"
  | x < 40 = "obesitat"
  | otherwise = "obesitat morbida"

imc :: (Fractional a) => a -> a -> a
imc w h = w / (h ^ 2)