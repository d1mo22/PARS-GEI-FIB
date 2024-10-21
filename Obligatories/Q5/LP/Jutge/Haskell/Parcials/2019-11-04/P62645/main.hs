main :: IO ()
main = do
  cnt <- getContents
  print $ f cnt

f :: String -> Int
f = sum . map s2i . words

s2i :: String -> Int
s2i = read