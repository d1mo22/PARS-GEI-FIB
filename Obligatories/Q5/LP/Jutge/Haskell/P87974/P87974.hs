main :: IO ()
main = do
  nom <- getLine
  if last nom == 'a' || last nom == 'A'
    then putStrLn "Hola maca!"
    else putStrLn "Hola maco!"