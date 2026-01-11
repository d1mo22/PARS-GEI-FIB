main :: IO ()
main = do
  name <- getLine
  if head name == 'A' || head name == 'a'
    then putStrLn "Hello!"
    else putStrLn "Bye!"
