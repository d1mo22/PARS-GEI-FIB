main :: IO ()
main = do
  content <- getContents
  print $ f content

f :: String -> Int
f = sum . map read . words