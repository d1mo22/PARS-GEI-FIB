import Data.List (sort)

main :: IO ()
main = do
  content <- getContents
  let lines = sort $ words content
  let wordCount = countWords lines
  putStr $ unlines [word ++ " " ++ show count | (word, count) <- wordCount]

countWords :: [String] -> [(String, Int)]
countWords [] = []
countWords (w : ws) = countOccurrences w 1 ws

countOccurrences :: String -> Int -> [String] -> [(String, Int)]
countOccurrences word count [] = [(word, count)]
countOccurrences word count (w : ws)
  | word == w = countOccurrences word (count + 1) ws
  | otherwise = (word, count) : countOccurrences w 1 ws
